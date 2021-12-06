#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H
#include <string>

const char ENGLISH_ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char RUSSIAN_ALPHABET[] = "�����Ũ��������������������������";

enum eCipherMode { DECRYPT_MODE, ENCRYPT_MODE };

void caesarCipher();					// ��������-���������� ������
const char* chooseAlphabet();           // ����� �������� ������: ���������� ���� �������
eCipherMode chooseMode();               // ����� ������ ������: ���������� ���� ������������
bool getText(std::string& strText);          // ���� ������ ��� (��-)����������
bool getTextFromFile(std::string& strText);  // ������ ������ �� �����
void putText(std::string& strNewText);          // ����� ������ ����� (��-)����������
void putTextInFile(std::string& strNewText);    // ������ ������ � ���� ����� (��-)����������

// ������� (��-)���������� ��� ������ ����� ������
void encodeDecodeWithCaesar(std::string& strText, std::string& strNewText, const char* pALPHABET, eCipherMode& CIPHER_MODE);

char charToUpper(const char& LETTER);   // ����������� ������� � ������� �������

#endif