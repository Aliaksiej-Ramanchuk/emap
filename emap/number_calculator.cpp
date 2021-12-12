#include "number_calculator.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

static eTokenValue curr_tok = eTokenValue::PRINT;
static map<string, double> table;

void numberCalculator()
{
    system("CLS");

    cout << "\n �������� �����������.\n";
    cout << " ��������� �������� ��������� ��������������� ���������.\n";
    cout << " ������������ ������������� � ��������� ���������� + , -, *, / , () � ���������� �������� ����������.\n";
    cout << " ������������ ������������� � ��������� �������� pi � e.\n";
    cout << " ������:\n";
    cout << "         ���������: 2.5 + (3 - 4 * 5)/17\n";
    cout << "         ���������: 1.5\n";

    table["pi"] = 3.14159265358;
    table["e"] = 2.7182818284;

    char answer;
    string expression;
    do
    {
        cout << "\n ��������:\n";
        cout << "  1 ��> ��������� �������� ��������������� ���������\n";
        cout << "  2 ��> ������� � ������� ����\n";
        cout << "  3 ��> ����� �� ���������\n";

        do {
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (answer)
            {
            case '1':
            {
                cout << "\n ������� �������������� ���������:\n";
                /*while (cin)
                {
                    getToken();
                    if (curr_tok == eTokenValue::END) {
                        break;
                    }
                    if (curr_tok == eTokenValue::PRINT) {
                        continue;
                    }
                    cout << "\n �������� ���������: " << expr(false) << '\n';
                    break;
                }*/
                break;
            }
            case '2':
                return;
            case '3':
                exit(0);
            default:
                cout << " ������������ ����. ������� ��� ���:\n";
                break;
            }
        } while ((answer < '1') || (answer > '3'));
    } while (true);
}

double expr(bool get)
{
    double left = term(get);

    while(true)
    {
        switch (curr_tok)
        {
        case eTokenValue::PLUS:
            left +=term (true);
            break;
        case eTokenValue::MINUS:
            left -= term(true);
            break;
        default:
            return left;
        }
    }
}

double term(bool get)
{
    double left = prim(get);
    while(true)
    {
        switch (curr_tok)
        {
        case eTokenValue::MUL:
            left *= prim(true);
            break;
        case eTokenValue::DIV:
            if (double d = prim(true)) {
                left /= prim(true);
                break;
            }
            else {
                return error("������� �� 0");
            }
        default:
            return left;
        }
    }
}

static double numberValue;
static string stringValue;

double prim(bool get)
{
    if (get) {
        getToken();
    }

    switch (curr_tok)
    {
    case eTokenValue::NUMBER:
    {
        double v = numberValue;
        getToken();
        return v;
    }
    case eTokenValue::NAME:
    {
        double& v = table[stringValue];
        if (getToken() == eTokenValue::ASSIGN) {
            v = expr(true);
        }
        return v;
    }
    case eTokenValue::MINUS:
        return -prim(true);
    case eTokenValue::LP:
    {
        double e = expr(true);
        if (curr_tok != eTokenValue::RP) {
            return error("��������� )");
        }
        getToken();
        return e;
    }
    default:
        return error("��������� ��������� ���������");
    }
}

eTokenValue getToken()
{
    char ch = 0;
    cin >> ch;

    switch (ch)
    {
    case 0:
        return curr_tok = eTokenValue::END;
    case ';':
    case '*':
    case '/':
    case '+':
    case '-':
    case '(':
    case ')':
    case '=':
        return curr_tok = eTokenValue(ch);
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
        cin.putback(ch);
        cin >> numberValue;
        return curr_tok = eTokenValue::NUMBER;
    default:
        if (isalpha(ch))
        {
            cin.putback(ch);
            cin >> stringValue;
            return curr_tok = eTokenValue::NAME;
        }
        error("������������ �������");
        return curr_tok = eTokenValue::PRINT;
    }
}

int no_of_errors;

int error(const string& s)
{
    no_of_errors++;
    cerr << "������: " << s << '\n';
    return 1;
}