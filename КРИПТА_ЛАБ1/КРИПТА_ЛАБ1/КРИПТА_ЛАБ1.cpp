#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

const string alphabetOdd = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string alphabetEven = "ZYXWVUTSRQPONMLKJIHGFEDCBA";

char encryptChar(char c, string alphabet, int shift) {
    if (c >= 'A' && c <= 'Z') {
        int pos = (c - 'A' + shift + 26) % 26;
        return alphabet[pos];
    }
    else if (c >= 'a' && c <= 'z') {
        int pos = (c - 'a' + shift + 26) % 26;
        return tolower(alphabet[pos]);
    }
    return c;
}

char decryptChar(char c, string alphabet, int shift) {
    if (c >= 'A' && c <= 'Z') {
        int pos = alphabet.find(c);
        return 'A' + (pos - shift + 26) % 26;
    }
    else if (c >= 'a' && c <= 'z') {
        int pos = alphabet.find(toupper(c));
        return tolower('A' + (pos - shift + 26) % 26);
    }
    return c;
}

string encryptText(string text, int shift) {
    string encrypted = text;
    for (int i = 0; i < text.size(); i++) {
        if (i % 2 == 0) {
            encrypted[i] = encryptChar(text[i], alphabetEven, shift);
        }
        else {
            encrypted[i] = encryptChar(text[i], alphabetOdd, shift);
        }
    }
    return encrypted;
}

string decryptText(string text, int shift) {
    string decrypted = text;
    for (int i = 0; i < text.size(); i++) {
        if (i % 2 == 0) {
            decrypted[i] = decryptChar(text[i], alphabetEven, shift);
        }
        else {
            decrypted[i] = decryptChar(text[i], alphabetOdd, shift);
        }
    }
    return decrypted;
}

void encryptFile(string inFileName, string outFileName, int shift) {
    ifstream inputFile(inFileName);
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла: " << inFileName << endl;
        return;
    }

    ofstream outputFile(outFileName);
    if (!outputFile.is_open()) {
        cerr << "Ошибка создания файла: " << outFileName << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        string encryptedLine = encryptText(line, shift);
        outputFile << encryptedLine << endl;
    }

    inputFile.close();
    outputFile.close();
}

void decryptFile(string inFileName, string outFileName, int shift) {
    ifstream inputFile(inFileName);
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла: " << inFileName << endl;
        return;
    }

    ofstream outputFile(outFileName);
    if (!outputFile.is_open()) {
        cerr << "Ошибка создания файла: " << outFileName << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        string decryptedLine = decryptText(line, shift);
        outputFile << decryptedLine << endl;
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    int shift, mode;

    string inFile = "text/text.txt";
    string encrypted = "encrypted/encrypted.txt";
    string decrypted = "decrypted/decrypted.txt";

    while (true) {
        cout << "1 - Зашифровать\n2 - Расшифровать\nВведите режим: ";
        cin >> mode;

        cout << "Введите сдвиг: ";
        cin >> shift;

        if (mode == 1) {
            encryptFile(inFile, encrypted, shift);
            cout << "Шифрование завершено\n\n" << endl;
        }

        else if (mode == 2) {
            decryptFile(encrypted, decrypted, shift);
            cout << "Расшифровка завершена\n\n" << endl;
        }
        else return 0;
    }

    return 0;
}
