#include <iostream>
#include <string>
#include "caesar_endecoder.h"

using std::cin;
using std::cout;
using std::string;

void caesarEnDecoder()
{
    system("CLS");

    cout << "\n ��������-���������� ������.\n";
    cout << "�������� ����������� � ����������� ����� �� ����������, ���������� � ��������� �����.\n";

    const char* pALPHABET = BELARUSIAN_ALPHABET;
    string strText, strNewText;
    eCipherMode cipherMode;

    int choice = 0;
    string choiceInput = "";

    while (true)
    {
        cout << "\n �������:\n";
        cout << "  1 ��> ����������� ����� ��� �������� ����� ������\n";
        cout << "  2 ��> ����������� ����� ��� �������� ����� ������\n";
        cout << "  3 ��> �������� � ������� ����\n";
        cout << "  4 ��> ������ � ��������\n";

        while (true)
        {
            getline(cin, choiceInput);

            try
            {
                for (char ch : choiceInput)
                {
                    if (!isdigit(ch)) {
                        throw std::out_of_range("����� ������ ���� ����� ����");
                    }
                }

                choice = stoi(choiceInput);

                if ((choice < 1) || (choice > 4)) {
                    throw std::out_of_range("����� ������ ���� �� 1 �� 4");
                }

                break;
            }
            catch (...) {
                cout << " ���������� ����. ����������� ���� ���:\n";
            }
        }

        switch (choice)
        {
        case 1:
            cipherMode = eCipherMode::ENCRYPT_MODE;
            break;
        case 2:
            cipherMode = eCipherMode::DECRYPT_MODE;
            break;
        case 3:
            return;
        case 4:
            exit(0);
        default:
            cout << "�� �� ������ ������ ���� �����.\n";
            break;
        }

        strText.clear();
        strNewText.clear();

        cout << "\n ������� ���� ������:\n";
        cout << "  1 ��> ����������\n";
        cout << "  2 ��> ����������\n";
        cout << "  3 ��> ���������\n";

        while (true)
        {
            getline(cin, choiceInput);

            try
            {
                for (char ch : choiceInput)
                {
                    if (!isdigit(ch)) {
                        throw std::out_of_range("����� ������ ���� ����� ����");
                    }
                }

                choice = stoi(choiceInput);

                if ((choice < 1) || (choice > 3)) {
                    throw std::out_of_range("����� ������ ���� �� 1 �� 3");
                }

                break;
            }
            catch (...) {
                cout << " ���������� ����. ����������� ���� ���:\n";
            }
        }

        switch (choice)
        {
        case 1:
            pALPHABET = ENGLISH_ALPHABET;
            break;
        case 2:
            pALPHABET = BELARUSIAN_ALPHABET;
            break;
        case 3:
                pALPHABET = RUSSIAN_ALPHABET;
                break;
        default:
            cout << "�� �� ������ ������ ���� �����.\n";
            break;
        }

        cout << "\n ������� �����:\n";
        getline(cin, strText);

        cipherWithCaesar(strText, strNewText, pALPHABET, cipherMode);

        cout << "\n ����� �����" << ((cipherMode == eCipherMode::DECRYPT_MODE) ? " ��" : " ") << "����������:\n";
        cout << strNewText << '\n';
    }
}

void cipherWithCaesar(string& strText, string& strNewText, const char* pALPHABET, eCipherMode& CIPHER_MODE)
{
    cout << "\n ������� �������� ����� ��� ����� �����:\n";

    int delta = 0;
    string deltaInput;
    
    while (true)
    {
        try
        {
            getline(cin, deltaInput);
            delta = stoi(deltaInput);
            break;
        }
        catch (...) {
            cout << " ���������� ����. ����������� ���� ���:\n";
        }
    }

    if (CIPHER_MODE == eCipherMode::DECRYPT_MODE) {
        delta *= -1;
    }

    const int ALPHABET_LENGTH = strlen(pALPHABET);

    delta %= ALPHABET_LENGTH;
    if (delta < 0) {
        delta += ALPHABET_LENGTH;
    }

    if (delta)
    {
        const int TEXT_LENGTH = strText.length();
        const char* pLETTER;

        for (int i = 0; i < TEXT_LENGTH; i++)
        {
            pLETTER = strchr(pALPHABET, charToUpper(strText[i]));
            if (pLETTER) {
                pLETTER = pALPHABET + ((pLETTER - pALPHABET + delta) % ALPHABET_LENGTH);
            }
            else {
                pLETTER = &strText[i];
            }

            strNewText += *pLETTER;
        }
    }
    else {
        strNewText = strText;
    }
}

char charToUpper(const char& LETTER)
{
    if (('a' <= LETTER) && (LETTER <= 'z')) {
        return LETTER + 'A' - 'a';
    }
    else if (('�' <= LETTER) && (LETTER <= '�')) {
        return LETTER + '�' - '�';
    }
    else if (LETTER == '�') {
        return '�';
    }
    else if (LETTER == '�') {
        return '�';
    }
    else if (LETTER == '�') {
        return '�';
    }
    else {
        return LETTER;
    }
}