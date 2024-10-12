#include <iostream>

class EncryptionStrategy {
public:
  virtual void encrypt(const std::string &data) = 0;
};

class AESEncryption : public EncryptionStrategy {
public:
  void encrypt(const std::string &data) override {
    std::cout << "Encrypting data using AES." << std::endl;
  }
};

class BlowfishEncryption : public EncryptionStrategy {
public:
  void encrypt(const std::string &data) override {
    std::cout << "Encrypting data using Blowfish." << std::endl;
  }
};

class FileEncryptor {
private:
  EncryptionStrategy *strategy;

public:
  void setStrategy(EncryptionStrategy *strat) { strategy = strat; }

  void encryptFile(const std::string &data) {
    if (strategy) {
      strategy->encrypt(data);
    } else {
      std::cout << "No encryption strategy set!" << std::endl;
    }
  }
};

// 使用方式
int main() {
  FileEncryptor encryptor;
  encryptor.setStrategy(new AESEncryption());
  encryptor.encryptFile("Sensitive data");

  encryptor.setStrategy(new BlowfishEncryption());
  encryptor.encryptFile("More sensitive data");

  return 0;
}
