#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FileCrypt)
{
    ui->setupUi(this);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(5);
    ui->progressBar->setValue(0);
    ui->encryptButton->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString filepath;
void MainWindow::on_browseBotten_clicked()
{
    //choosinf file location via the browsing botten
    const QString desktop=QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    filepath=QFileDialog::getOpenFileName(this,tr("Open File"),desktop,"All Files (*.*)");
    ui->pathLineEdit->setText(filepath);
}

// Encrypt function using EVP
QByteArray encryptAES(const QByteArray &plaintext, const QByteArray &key, const QByteArray &iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    QByteArray encryptedData(plaintext.size() + EVP_MAX_BLOCK_LENGTH, Qt::Uninitialized);
    int len = 0, ciphertext_len = 0;

    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()));
    EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(encryptedData.data()), &len, reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size());
    ciphertext_len = len;

    EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(encryptedData.data()) + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    encryptedData.resize(ciphertext_len);  // Resize to actual ciphertext length
    return encryptedData;
}

// Decrypt function using EVP
QByteArray decryptAES(const QByteArray &ciphertext, const QByteArray &key, const QByteArray &iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    QByteArray decryptedData(ciphertext.size(), Qt::Uninitialized);
    int len = 0, plaintext_len = 0;

    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, reinterpret_cast<const unsigned char*>(key.data()), reinterpret_cast<const unsigned char*>(iv.data()));
    EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(decryptedData.data()), &len, reinterpret_cast<const unsigned char*>(ciphertext.data()), ciphertext.size());
    plaintext_len = len;

    EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(decryptedData.data()) + len, &len);
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    decryptedData.resize(plaintext_len);  // Resize to actual plaintext length
    return decryptedData;
}

// SHA256 function
QByteArray hashPasswordSHA256(const QString &password) {
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hash(EVP_MAX_MD_SIZE, Qt::Uninitialized);
    unsigned int hashLength = 0;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, passwordBytes.data(), passwordBytes.size());
    EVP_DigestFinal_ex(ctx, reinterpret_cast<unsigned char*>(hash.data()), &hashLength);
    EVP_MD_CTX_free(ctx);

    hash.resize(hashLength); // Resize to actual hash length
    return hash.toHex(); // Convert to hex for readability
}

// AES Key generating function --- 16 bytes = 128 bits
QByteArray generateAESKey(int size = 16) {
    QByteArray key(size, Qt::Uninitialized);

    if (RAND_bytes(reinterpret_cast<unsigned char*>(key.data()), size) != 1) {
        QWidget window;
        QMessageBox::information(&window, "Message",  "Error generating random AES encryption key!!!");
    }

    return key;
}

// Function to generate a random IV
QByteArray generateAESIV(int size = 16) { // Default: 16 bytes for AES-CBC
    QByteArray iv(size, Qt::Uninitialized);
    if (RAND_bytes(reinterpret_cast<unsigned char*>(iv.data()), size) != 1) {
        QWidget window;
        QMessageBox::information(&window, "Message",  "Error generating random IV!!!");
        return QByteArray(); // Return empty if generation fails
    }
    return iv;
}

// storing the encryption keys and IVs
bool appendKeysToFile(const QByteArray &key, const QByteArray &iv, QString pass) {
    //hashing the password
    QByteArray hash = hashPasswordSHA256(pass);
    //checking if the password has been used before
    QFile keysRetrieve("keys.txt");
    if (!keysRetrieve.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QWidget window;
        QMessageBox::information(&window, "Message",  "Failed to open the encryption keys storage.");
        keysRetrieve.close();
        return 0;
    }
    QTextStream in(&keysRetrieve);
    //searching for the password in the key.txt
    while (!in.atEnd()) {
        QString s=in.readLine();
        QByteArray pass_possible = QByteArray::fromHex(s.right(s.length() - s.lastIndexOf('/') - 1).toUtf8());
        if(hash == pass_possible)
        {
            QWidget window;
            QMessageBox::information(&window, "Message",  "ERROR: Password has been used before, please enter a new password");
            keysRetrieve.close();
            return false;
        }
    }
    keysRetrieve.close();
    //appending the key to the storage file
    QFile file("keys.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) { // Append mode
        QWidget window;
        QMessageBox::information(&window, "Message",  "Failed to store AES key in ./keys.txt");
        file.close();
        return false;
    }
    //each line will represent AES_key/IV/Password
    QTextStream out(&file);
    out << key.toHex() << "/" << iv.toHex() << "/" << hash.toHex() << '\n';
    file.close();
    qDebug() << "Keys and IV appended successfully!";
    return true;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->encryptButton->isChecked())
    {
        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly)) {
            QWidget window;
            QMessageBox::information(&window, "Message",  "Failed to open the file.");
            file.close();
            return;
        }
        QByteArray fileData = file.readAll();
        file.close();
        ui->progressBar->setValue(1);
        //generating AES key
        QByteArray key = generateAESKey(16);
        ui->progressBar->setValue(2);
        //generating AES IV
        QByteArray IV = generateAESIV(16);
        ui->progressBar->setValue(3);
        //Encrypting the file
        QByteArray encryptedData = encryptAES(fileData, key, IV);
        ui->progressBar->setValue(4);
        int lastSlashIndex = filepath.lastIndexOf('/'); // Find the last '/'
        QString result = filepath.left(lastSlashIndex); // Keep everything before it
        result += "/Encrypted_" + filepath.right(filepath.length() - filepath.lastIndexOf('/') - 1);
        //storing the AES key and IV mapped to a password for simple retrieval
        if(!appendKeysToFile(key,IV,ui->passwordLineEdit->text()))
        {
            ui->progressBar->setValue(0);
            return;
        }
        QFile encryptedFile(result);
        if (encryptedFile.open(QIODevice::WriteOnly)) {
            encryptedFile.write(encryptedData);
            encryptedFile.close();
            ui->progressBar->setValue(5);
            QWidget window;
            QMessageBox::information(&window, "Message",  "File Encrypted Successfully");
        } else {
            QWidget window;
            QMessageBox::information(&window, "Message",  "Failed to write the encrypted file.");
        }
    }
    if(ui->decryptButton->isChecked())
    {
        //reading the encrypted file
        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly)) {
            QWidget window;
            QMessageBox::information(&window, "Message",  "Failed to open the file.");
            return;
        }
        QByteArray fileData = file.readAll();
        file.close();
        ui->progressBar->setValue(1);
        //retrieving the key and IV via the password
        QFile keysRetrieve("keys.txt");
        if (!keysRetrieve.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QWidget window;
            QMessageBox::information(&window, "Message",  "Failed to open the encryption keys storage.");
            file.close();
            return;
        }
        QTextStream in(&keysRetrieve);
        QString pass = ui->passwordLineEdit->text();
        QByteArray hash = hashPasswordSHA256(pass);
        ui->progressBar->setValue(2);
        QByteArray key,IV;
        //searching for the password in the key.txt file to retrieve the AES key and IV
        bool pass_found=0;
        while (!in.atEnd()) {
            QString s=in.readLine();
            QByteArray pass_possible = QByteArray::fromHex(s.right(s.length() - s.lastIndexOf('/') - 1).toUtf8());
            if(hash == pass_possible)
            {
                s = s.left(s.lastIndexOf('/'));
                IV = QByteArray::fromHex(s.right(s.length() - s.lastIndexOf('/') - 1).toUtf8());
                s = s.left(s.lastIndexOf('/'));
                key = QByteArray::fromHex(s.toUtf8());
                pass_found = 1;
                break;
            }
        }
        if(!pass_found)
        {
            QWidget window;
            QMessageBox::information(&window, "Message", "Incorrect Password");
            ui->progressBar->setValue(0);
            keysRetrieve.close();
            return;
        }
        keysRetrieve.close();
        ui->progressBar->setValue(3);
        int lastSlashIndex = filepath.lastIndexOf('/'); // Find the last '/'
        QString result = filepath.left(lastSlashIndex); // Keep everything before it
        result += "/Decrypted_" + filepath.right(filepath.length() - filepath.lastIndexOf('/') - 1);
        //Decrypting the file
        QFile decryptedFile(result);
        QByteArray decryptedData = decryptAES(fileData, key, IV);
        ui->progressBar->setValue(4);
        if (decryptedFile.open(QIODevice::WriteOnly)) {
            decryptedFile.write(decryptedData);
            decryptedFile.close();
            ui->progressBar->setValue(5);
            QWidget window;
            QMessageBox::information(&window, "Message",  "File Decrypted Successfully");
        } else {
            QWidget window;
            QMessageBox::information(&window, "Message",  "Failed to write the decrypted file");
        }
    }
}
