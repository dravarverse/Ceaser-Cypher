#include <iostream>
#include <string>
#include <fstream>

std::string encryptText(std::string plaintext, int shift);
std::string decryptText(std::string cyphertext, int shift);
void processCommand(const std::string &command);
void encryptTextFile(std::string filePath, int shift);
void decryptTextFile(std::string filePath, int shift);
int main()
{

    std::string command;
    bool event = true;

    std::cout << "Ceaser Cypher" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Type 'help' for available commands." << std::endl;

    while (event)
    {
        std::cout << "> ";

        if (!std::getline(std::cin >> std::ws, command))
        {
            break;
        }
        if (command == "exit")
        {
            break;
        }

        processCommand(command);
    }

    return 0;
}

void processCommand(const std::string &command)
{
    std::string plainText, cypherText, filePath;
    int shift;
    if (command == "help")
    {
        std::cout << "Use commands 'help', 'encrypt', 'decrypt', 'advance', 'exit'" << std::endl;
    }
    else if (command == "encrypt")
    {
        std::cout << "\nEnter plaintext: ";
        std::getline(std::cin >> std::ws, plainText);
        std::cout << "Enter shift: ";
        std::cin >> shift;
        std::cout << "Encrypted Text: " << encryptText(plainText, shift) << "\n"
                  << std::endl;
    }
    else if (command == "decrypt")
    {
        std::cout << "\nEnter cyphertext: ";
        std::getline(std::cin >> std::ws, cypherText);
        std::cout << "Enter shift: ";
        std::cin >> shift;
        std::cout << "Decrypted Text: " << decryptText(cypherText, shift) << "\n"
                  << std::endl;
    }
    else if (command == "advance")
    {
        char mode;
        std::cout << "\nMode (e/d): ";
        std::cin >> mode;
        if (mode == 'e')
        {
            std::cout << "Enter path (.txt only): ";
            std::getline(std::cin >> std::ws, filePath);
            std::cout << "Enter shift: ";
            std::cin >> shift;
            encryptTextFile(filePath, shift);
        }
        else if (mode == 'd'){
            std::cout << "Enter path (.txt only): ";
            std::getline(std::cin >> std::ws, filePath);
            std::cout << "Enter shift: ";
            std::cin >> shift;
            decryptTextFile(filePath, shift);
        }
        else{
            std::cout << "Invalid Input" << std::endl;
        }
    }

    else
    {
        std::cout << "Invalid Input" << std::endl;
    }
}

std::string encryptText(std::string plaintext, int shift)
{
    for (char &ch : plaintext)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            ch = 'A' + (ch - 'A' + shift + 26) % 26;
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            ch = 'a' + (ch - 'a' + shift + 26) % 26;
        }
    }

    return plaintext;
}

std::string decryptText(std::string cyphertext, int shift)
{
    for (char &ch : cyphertext)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            ch = 'A' + (ch - 'A' - shift + 26) % 26;
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            ch = 'a' + (ch - 'a' - shift + 26) % 26;
        }
    }

    return cyphertext;
}

void encryptTextFile(std::string filePath, int shift)
{
    std::fstream textFile(filePath);

    if (!textFile.is_open())
    {
        throw std::invalid_argument("File Not exist");
    }

    std::string line;
    std::ofstream encryptedFile("./encrypted.txt");
    while (getline(textFile, line))
    {
        if (!encryptedFile.is_open())
        {
            throw std::invalid_argument("File didn't opened successfully");
        }
        std::string encryptedText = encryptText(line, shift);

        encryptedFile << encryptedText << std::endl;
    }
    encryptedFile.close();
    textFile.close();
}

void decryptTextFile(std::string filePath, int shift)
{

    std::fstream encryptedFile(filePath);

    if (!encryptedFile.is_open())
    {
        throw std::invalid_argument("File Not exist");
    }

    std::string cypherLine;
    std::ofstream decryptedFile("./decrypted.txt");
    while (getline(encryptedFile, cypherLine))
    {
        if (!decryptedFile.is_open())
        {
            throw std::invalid_argument("File didn't opened successfully");
        }
        std::string decryptedText = decryptText(cypherLine, shift);

        decryptedFile << decryptedText << std::endl;
        std::cout << decryptedText << std::endl;
    }
    encryptedFile.close();
    decryptedFile.close();
}
