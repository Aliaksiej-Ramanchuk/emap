#include "number_calculator.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

static bool exprIsOK = true;
static stringstream expression;
static eTokenValue curr_tok;
static double numberValue;
static int bracketsCount;

void numberCalculator()
{
    system("CLS");

    cout << "\n �������� �����������.\n";
    cout << " ��������� �������� ��������� ��������������� ���������.\n";
    cout << " ������������ ������������� � ��������� ���������� + , -, *, / , () � ���������� �������� ����������.\n";
    cout << " ������:\n";
    cout << "         ���������: 2.5 + (3 - 4 * 5)/17\n";
    cout << "         ���������: 1.5\n";

    char answer;
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
                string exp;
                getline(cin, exp);

                expression.clear();
                exprIsOK = true;
                numberValue = 0;
                bracketsCount = 0;

                expression << exp;

                getToken();
                exp = to_string(expr(false));

                if (exprIsOK) {
                    cout << "\n �������� ���������: " << exp << '\n';
                }
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
        if (exprIsOK)
        {
            switch (curr_tok)
            {
            case eTokenValue::PLUS:
                left += term(true);
                break;
            case eTokenValue::MINUS:
                left -= term(true);
                break;
            default:
                return left;
            }
        }
        else {
            return 1;
        }
    }
}

double term(bool get)
{
    double left = prim(get);
    while (true)
    {
        if (exprIsOK)
        {
            switch (curr_tok)
            {
            case eTokenValue::MUL:
                left *= prim(true);
                break;
            case eTokenValue::DIV:
                if (double d = prim(true)) {
                    left /= d;
                    break;
                }
                else {
                    exprIsOK = false;
                    cerr << "\n ������: ������� �� 0\n";
                    return 1;
                }
            case eTokenValue::RP:
                bracketsCount--;
                if (bracketsCount < 0)
                {
                    exprIsOK = false;
                    cerr << "\n ������: �������� ����������� �������� )\n";
                    return 1;
                }
                else {
                    return left;
                }
            case eTokenValue::NUMBER:
                exprIsOK = false;
                cerr << "\n ������: ��������� ����������� ���������� �����\n";
                return 1;
            default:
                return left;
            }
        }
        else {
            return 1;
        }
    }
}


double prim(bool get)
{
    if (get) {
        getToken();
    }
    if (exprIsOK)
    {
        switch (curr_tok)
        {
        case eTokenValue::NUMBER:
        {
            double v = numberValue;
            getToken();
            return v;
        }
        case eTokenValue::MINUS:
            return -prim(true);
        case eTokenValue::LP:
        {
            bracketsCount++;
            double e = expr(true);
            if ((exprIsOK) && (curr_tok != eTokenValue::RP))
            {
                exprIsOK = false;
                cerr << "\n ������: ��������� )\n";
                return 1;
            }
            getToken();
            return e;
        }
        default:
            exprIsOK = false;
            cerr << "\n ������: ��������� ��������� ���������\n";
            return 1;
        }
    }
    else {
        return 1;
    }
}

eTokenValue getToken()
{
    char ch;

    do
    {
        if (!expression.get(ch)) {
            return curr_tok = eTokenValue::PRINT;
        }
    } while (ch != '\n' && isspace(ch));

    switch (ch)
    {
    case '\n':
    case 0:
        return curr_tok = eTokenValue::PRINT;
    case '*':
    case '/':
    case '+':
    case '-':
    case '(':
    case ')':
        return curr_tok = (eTokenValue)ch;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
        expression.putback(ch);
        expression >> numberValue;
        return curr_tok = eTokenValue::NUMBER;
    default:
        exprIsOK = false;
        cerr << "\n ������: �������� ����������� ������ " << ch << "\n";
        return curr_tok = eTokenValue::ERR_SYMBOL;
    }
}