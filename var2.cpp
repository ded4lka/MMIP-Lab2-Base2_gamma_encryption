#include <iostream>
#include <bitset>
#include <string>

// Функция шифрования (гаммирования)
std::string GammaEncrypt(std::string plainText, std::string key) {
    std::string encryptedText = "";
    int j = 0;
    for (int i = 0; i < plainText.length(); i++) {
        if (j > key.length()) j = 0;
        
        // Приведение всех полей к двоичному коду
        std::bitset<8> plainTextBit(plainText[i]);
        std::bitset<8> keyTextBit(key[j]);
        
        // Приведение к двоичному коду результата операции XOR
        std::bitset<8> encrypted_bit(plainTextBit ^ keyTextBit);
        
        // Приведение бита к unsigned long int и добавление к шифру
        encryptedText += char(encrypted_bit.to_ulong());
        j++;
    }
    return encryptedText;
}

// Функция дешифрования
std::string GammaDecrypt(std::string encryptedText, std::string key) {
    std::string decryptedText = "";
    
    // Вызов функции шифрования для зашифрованного текста даёт исходный текст
    decryptedText = GammaEncrypt(encryptedText, key);
    return decryptedText;
}

// Функция проверки строки на наличие не букв
bool CheckString(std::string text) {
    for (int i = 0; i < text.size(); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z') || (text[i] == ' '))
        {
            return true;
        }
        else
            return false;
    }
}

// Функция проверки ключа на наличие не цифр
bool CheckInt(std::string key) {
    auto it = key.begin();
    while (it != key.end() && isdigit(*it)) {
        it++;
    }
    return !key.empty() && it == key.end();
}

int main() {
    std::string plainText;

    std::cout << "Enter the text you want to encrypt: ";
    std::getline(std::cin, plainText);
    while (!CheckString(plainText)) {
        std::cin.clear();
        std::cout << "Invalid Input. The text can only contain Latin letters. Try again: ";
        std::getline(std::cin, plainText);
    }
    std::cout << "\n";

    std::string key;
    std::cout << "Enter the encryption key: ";
    std::getline(std::cin, key);
    while (!CheckInt(key)) {
        std::cout << "Invalid Input. The key can only contain numbers. Try again: ";
        std::getline(std::cin, key);
    }
    std::cout << "\n";

    std::string encryptedText = GammaEncrypt(plainText, key);
    std::string decryptedText = GammaDecrypt(encryptedText, key);
    
    std::cout << "Encrypted data: " << encryptedText << std::endl;
    std::cout << "Decrypted data: " << decryptedText << std::endl;
    return 0;
}
