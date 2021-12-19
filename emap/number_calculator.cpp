#include "number_calculator.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const static unsigned MAX_NESTING_VALUE = 100;
const static double MIN_POS_VALUE = 0.00000000001;

static stringstream g_expression;
static eTokenValue g_currentToken = eTokenValue::PRINT;
static double g_numberValue = 0;
static string g_stringValue = "";
static int g_parenthesesCount = 0;
static unsigned g_nestingChecker = 0;

void numberCalculator()
{
    system("CLS");

    cout << "\n ˳���� �����������.\n";
    cout << " ������� �������� ���������� ������.\n";
    cout << " ����������� ������������ � ������ ��������� +, -, *, /, ^, () � ��������� �������� ���������.\n";
    cout << " ����������� ������������ sin(), cos(), tan(), cot().\n";
    cout << " �������:\n";
    cout << "         �����: 2.5 + (3^2 - 4 * 5)/11 + cos(0)\n";
    cout << "         ����: 2.500000\n";

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
                g_numberValue = 0;
                g_parenthesesCount = 0;
                g_nestingChecker = 0;

                g_expression << exp;

                getToken();

                try
                {
                    exp = to_string(expr(false));
                    cout << "\n �������� ������: " << exp << '\n';
                }
                catch (CalcException& err) {
                    cerr << "\n �������: " << err.what() << '\n';
                }
                catch (...) {
                    cerr << "\n ���, �� ����� ����������� �����...\n";
                }
            }
            break;
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
        switch (g_currentToken)
        {
        case eTokenValue::PLUS:
            left += term(true);
            break;
        case eTokenValue::MINUS:
            left -= term(true);
            break;
        default:
            g_nestingChecker--;
            return left;
        }
    }
}

double term(bool get)
{
    if (++g_nestingChecker > MAX_NESTING_VALUE) {
        throw CalcException("����� �������� �����");
    }

    double left = prim(get);
    while (true)
    {
        switch (g_currentToken)
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
                throw CalcException("�������� �� 0");
            }
        case eTokenValue::LP:
            left *= prim(false);
            break;
        case eTokenValue::RP:
            g_parenthesesCount--;
            if (g_parenthesesCount < 0) {
                throw CalcException("�������� �������� �������� )");
            }
            g_nestingChecker--;
            return left;
        case eTokenValue::NUMBER:
            throw CalcException("�������� �������� �� " + to_string(g_numberValue));
        default:
            g_nestingChecker--;
            return left;
        }
    }
}

double prim(bool get)
{
    if (++g_nestingChecker > MAX_NESTING_VALUE) {
        throw CalcException("����� �������� �����");
    }

    double value = 0.0;

    if (get) {
        getToken();
    }
    switch (g_currentToken)
    {
    case eTokenValue::NUMBER:
    {
        value = g_numberValue;
        getToken();
        break;
    }
    case eTokenValue::PLUS:
        value = prim(true);
        break;
    case eTokenValue::MINUS:
        value = -prim(true);
        break;
    case eTokenValue::LP:
    {
        g_parenthesesCount++;
        value = expr(true);
        if (g_currentToken != eTokenValue::RP) {
            throw CalcException("�������� )");
        }
        getToken();
    }
    break;
    case eTokenValue::WORD:
    {
        if ((g_stringValue == "sin") ||
            (g_stringValue == "cos") ||
            (g_stringValue == "tan") ||
            (g_stringValue == "cot"))
        {
            value = prim(true);

            if (g_stringValue == "sin") {
                value = sin(value);
            }
            else if (g_stringValue == "cos") {
                value = cos(value);
            }
            else if (g_stringValue == "tan") {
                if (std::abs(cos(value)) > MIN_POS_VALUE) {
                    value = sin(value) / cos(value);
                }
                else {
                    throw CalcException((string)"������ ������� ������� pi/2");
                }
            }
            else if (g_stringValue == "cot") {
                if (std::abs(sin(value)) > MIN_POS_VALUE) {
                    value = cos(value) / sin(value);
                }
                else {
                    throw CalcException((string)"������ ������� ��������� 0");
                }
            }
        }
        else if (g_stringValue == "log") {
            double base = 10.0;
            getToken();
            if (g_currentToken == eTokenValue::LSP)
            {
                base = expr(true);
                if (base < MIN_POS_VALUE) {
                    throw CalcException("������ ��������� ������ ���� �������� ����");
                }
                if (std::abs(base - 1.0) < MIN_POS_VALUE) {
                    throw CalcException("������ ��������� �� ���� ���� ����� 1");
                }
                if (g_currentToken != eTokenValue::RSP) {
                    throw CalcException("�������� ]");
                }
                getToken();
            }
            value = prim(false);
            if (value < MIN_POS_VALUE) {
                throw CalcException("������ ������� �������� �������� ��� �� ����");
            }
            value = log(value) / log(base);
        }
        else if (g_stringValue == "ln") {
            value = prim(true);
            if (value < MIN_POS_VALUE) {
                throw CalcException("������ ������� �������� �������� ��� �� ����");
            }
            value = log(value);
        }
        else {
            throw CalcException((string)"�������� �������� ����� " + g_stringValue[0]);
        }
    }
        break;
    default:
        throw CalcException("������ �������� �����");
    }

    while (true)
    {
        switch (g_currentToken)
        {
        case eTokenValue::POW:
        {
            double powerValue = prim(true);
            if ((abs(value) < MIN_POS_VALUE) && (powerValue <= MIN_POS_VALUE)) {
                throw CalcException("0 ����� �������� ����� � �������� �������");
            }

            double intPart = 0.0;
            double fracPartOfPower = modf(powerValue, &intPart);
            if (abs(fracPartOfPower) < MIN_POS_VALUE)
            {
                fracPartOfPower = 0.0;
                powerValue = intPart;
            }
            if ((value < 0.0) && (fracPartOfPower)) {
                throw CalcException("������ �������� ������� �� � �������� �������");
            }
            value = pow(value, powerValue);
        }
            break;
        case eTokenValue::FACT:
        {

            if (value < 0.0) {
                throw CalcException("������ ������� ��������� �������� ���");
            }
            if (value > 150.0) {
                throw CalcException("����� ������ �������� ����������");
            }

            double intPartOfValue;
            double fracPartOfValue = modf(value, &intPartOfValue);

            if (fracPartOfValue < MIN_POS_VALUE) {
                value = factorial((unsigned long long)intPartOfValue);
            }
            else {
                throw CalcException("������ ������� ��������� ��������� ���");
            }

            getToken();
        }
            break;
        default:
            g_nestingChecker--;
            return value;
        }
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
    case '!':
    case '^':
    case '*':
    case '/':
    case '+':
    case '-':
    case '(':
    case ')':
    case '[':
    case ']':
        return g_currentToken = (eTokenValue)ch;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
    {
        g_expression.putback(ch);
        g_expression >> g_numberValue;
        double intPartOfNumber;
        double fracPartOfNumber = modf(g_numberValue, &intPartOfNumber);
        if (abs(fracPartOfNumber) < MIN_POS_VALUE) {
            g_numberValue = intPartOfNumber;
        }
        return g_currentToken = eTokenValue::NUMBER;
    }

    default:
        if (isalpha(ch))
        {
            g_stringValue = ch;
            while (g_expression.get(ch) && isalpha(ch)) {
                g_stringValue.push_back(ch);
            }
            g_expression.putback(ch);
            return g_currentToken = eTokenValue::WORD;
        }
        throw CalcException((string)"�������� �������� ����� " + ch);
    }
}

long double factorial(unsigned long long value)
{
    long double result = 1;
    for (unsigned long long i = 2; i <= value; i++) {
        result *= i;
    }

    return result;
}