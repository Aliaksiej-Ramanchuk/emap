#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H

#include <string>

const char ENGLISH_ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char BELARUSIAN_ALPHABET[] = "�����Ũ�ǲ����������ӡ�����'�����";
const char RUSSIAN_ALPHABET[] = "�����Ũ��������������������������";

enum class eCipherMode { DECRYPT_MODE, ENCRYPT_MODE };

void caesarCipher();	// ��������-���������� ������

// ������� (��-)���������� ��� ������ ����� ������
void encodeDecodeWithCaesar(std::string& strText, std::string& strNewText, const char* pALPHABET, eCipherMode& CIPHER_MODE);

char charToUpper(const char& LETTER);    // ����������� ������� � ������� �������

#endif