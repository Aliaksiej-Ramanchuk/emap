#include "number_calculator.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const static unsigned MAX_NESTING_VALUE = 100;

static bool g_exprIsOK = true;
static stringstream g_expression;
static eTokenValue g_currentToken = eTokenValue::PRINT;
static double g_numberValue = 0;
static int g_bracketsCount = 0;
static unsigned g_nestingChecker = 0;

void numberCalculator()
{
    system("CLS");

    cout << "\n ˳���� �����������.\n";
    cout << " ������� �������� ���������� ������.\n";
    cout << " ����������� ������������ � ������ ��������� +, -, *, /, ^, () � ��������� �������� ���������.\n";
    cout << " �������:\n";
    cout << "         �����: 2.5 + (3^2 - 4 * 5)/11\n";
    cout << "         ����: 1.5\n";

    char answer;
    do
    {
        cout << "\n �������:\n";
        cout << "  1 ��> ������� �������� ������������� ������\n";
        cout << "  2 ��> �������� � ������� ����\n";
        cout << "  3 ��> ������ � ��������\n";

        do {
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (answer)
            {
            case '1':
            {
                cout << "\n ������� ����������� �����:\n";
                string exp;
                getline(cin, exp);

                g_expression.str("");
                g_expression.clear();
                g_exprIsOK = true;
                g_numberValue = 0;
                g_bracketsCount = 0;
                g_nestingChecker = 0;

                g_expression << exp;

                getToken();

                try {
                    exp = to_string(expr(false));
                }
                catch (CalcException& err)
                {
                    g_exprIsOK = false;
                    cerr << "\n �������: " << err.what() << '\n';
                }
                catch (...) {
                    g_exprIsOK = false;
                    cerr << "\n ���, �� ����� ����������� �����...\n";
                }

                if (g_exprIsOK) {
                    cout << "\n �������� ������: " << exp << '\n';
                }
                break;
            }
            case '2':
                return;
            case '3':
                exit(0);
            default:
                cout << " ���������� ����. ������� ���� ���:\n";
                break;
            }
        } while ((answer < '1') || (answer > '3'));
    } while (true);
}

double expr(bool get)
{
    if (++g_nestingChecker > MAX_NESTING_VALUE) {
        throw CalcException("����� �������� �����");
    }

    double left = term(get);

    while (true)
    {
        if (g_exprIsOK)
        {
            switch (g_currentToken)
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
    if (++g_nestingChecker > MAX_NESTING_VALUE) {
        throw CalcException("����� �������� �����");
    }

    double left = power(get);
    while (true)
    {
        if (g_exprIsOK)
        {
            switch (g_currentToken)
            {
            case eTokenValue::MUL:
                left *= power(true);
                break;
            case eTokenValue::DIV:
                if (double d = power(true)) {
                    left /= d;
                    break;
                }
                else {
                    throw CalcException("�������� �� 0");
                }
            case eTokenValue::LP:
                throw CalcException("�������� �������� �������� (");
            case eTokenValue::RP:
                g_bracketsCount--;
                if (g_bracketsCount < 0) {
                    throw CalcException("�������� �������� �������� )");
                }
                return left;
            case eTokenValue::NUMBER:
                throw CalcException("�������� ��������� ����������� ������");
            default:
                return left;
            }
        }
        else {
            return 1;
        }
    }
}

double power(bool get)
{
    if (++g_nestingChecker > MAX_NESTING_VALUE) {
        throw CalcException("����� �������� �����");
    }

    double left = prim(get);
    while (true)
    {
        if (g_exprIsOK)
        {
            switch (g_currentToken)
            {
            case eTokenValue::POW:
            {
                double powerValue = power(true);
                if ((left == 0) && (powerValue == 0)) {
                    throw CalcException("���������� 0 � ������� 0");
                }
                left = pow(left, powerValue);
            }
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

double prim(bool get)
{
    if (++g_nestingChecker > MAX_NESTING_VALUE) {
        throw CalcException("����� �������� �����");
    }

    if (get) {
        getToken();
    }
    if (g_exprIsOK)
    {
        switch (g_currentToken)
        {
        case eTokenValue::NUMBER:
        {
            double v = g_numberValue;
            getToken();
            return v;
        }
        case eTokenValue::PLUS:
            return prim(true);
        case eTokenValue::MINUS:
            return -prim(true);
        case eTokenValue::LP:
        {
            g_bracketsCount++;
            double e = expr(true);
            if ((g_exprIsOK) && (g_currentToken != eTokenValue::RP)) {
                throw CalcException("�������� )");
            }
            getToken();
            return e;
        }
        default:
            throw CalcException("������ �������� �����");
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
        if (!g_expression.get(ch)) {
            return g_currentToken = eTokenValue::PRINT;
        }
    } while (ch != '\n' && isspace((unsigned char)ch));

    switch (ch)
    {
    case '\n':
    case 0:
        return g_currentToken = eTokenValue::PRINT;
    case '^':
    case '*':
    case '/':
    case '+':
    case '-':
    case '(':
    case ')':
        return g_currentToken = (eTokenValue)ch;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
        g_expression.putback(ch);
        g_expression >> g_numberValue;
        return g_currentToken = eTokenValue::NUMBER;
    default:
        throw CalcException((string)"�������� �������� ����� " + ch);
    }
}