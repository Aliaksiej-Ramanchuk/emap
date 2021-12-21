#include "number_calculator.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include "calc_exception.h"
using namespace std;

const static unsigned MAX_NESTING_VALUE = 100;
const static double MIN_POS_VALUE = 0.00000000001;
const static double MAX_VALUE_FOR_FACTORIAL = 150.0;
const static double MAX_VALUE_FOR_EXPONENT = 600.0;

static stringstream g_expression;
static eTokenValue g_currentToken = eTokenValue::PRINT;
static UniversalExprType g_numberValue{ 0 };
static string g_stringValue = "";
static int g_parenthesesCount = 0;
static int g_bracesCount = 0;
static unsigned g_nestingChecker = 0;

void numberCalculator()
{
    system("CLS");

    cout << "\n �����������.\n";
    cout << " ������� �������� ���������� ������.\n";

    char answer;
    do
    {
        cout << "\n �������:\n";
        cout << "  1 ��> ������� �������� ������\n";
        cout << "  2 ��> ��� ���������� ��������\n";
        cout << "  3 ��> �������� � ������� ����\n";
        cout << "  4 ��> ������ � ��������\n";

        do {
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (answer)
            {
            case '1':
            {
                cout << "\n ������� �����:\n";
                string expressionString;
                getline(cin, expressionString);

                g_expression.str("");
                g_expression.clear();
                g_numberValue = UniversalExprType(0.0);
                g_parenthesesCount = 0;
                g_bracesCount = 0;
                g_nestingChecker = 0;

                g_expression << expressionString;

                try
                {
                    UniversalExprType expressionResult = expr(true);
                    cout << "\n �������� ������: " << setprecision(10) << expressionResult << '\n';
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
                cout << "\n ��� ���������� �������� ��� ���:         ������� ������:          ����:\n";
                cout << "  +                     ���������              2+3                      5\n";
                cout << "  -                     ��������              4-5                      -1\n";
                cout << "  *                     ��������               4*2                      8\n";
                cout << "  /                     ��������               7/2                      3.5\n";
                cout << "  ( )                   ����                  4*(2+3)                  20\n";
                cout << "  ^                     ������������           3^2                      9\n";
                cout << "  !                     ���������              4!                       24\n";
                cout << "  abs, abs()            ������                 abs-4, abs(-4)           4\n";
                cout << "  sqrt, sqrt()          ��������� ������       sqrt4, sqrt(4)           2\n";
                cout << "  root, root()          ��������� ������       root9, root(9)           3\n";
                cout << "  root[n], root[n]()    ������ n-� ������     root[3]8, root[3](8)     2\n";
                cout << "  lg, lg()              ���������� ��������    lg10, lg(10)             1\n";
                cout << "  log, log()            ���������� ��������    log100, log(100)         2\n";
                cout << "  ln, ln()              ���������� ��������    ln7.389056099, ln(e^2)   2\n";
                cout << "  log[n], log[n]()      �������� �� ������ n   log[2]8, log[2](8)       3\n";
                cout << "  exp, exp()            ����������             exp2, exp(2)             7.389056099\n";
                cout << "  sin, sin()            ����                  sin0, sin(pi)            0\n";
                cout << "  cos, cos()            ������                cos0, cos(pi/2)          1\n";
                cout << "  tan, tan()            �������                tan0, tan(pi)            0\n";
                cout << "  cot, cot()            ���������              cot1.570796, cot(pi/2)   0\n";
                cout << endl;
                cout << "\n ��� ���������� �������� ��� �������:      ������� ������:          ����:\n";
                cout << "  +                     ���������              {1, 2} + {3, -1}         { 4, 1 }\n";
                cout << "                                               {3, -1} + 4              { 7, 3 }\n";
                cout << "  -                     ��������              {1, 2} - {3, -1}         { -2, 3 }\n";
                cout << "                                               {3, -1} - 4              { -1, -5 }\n";
                cout << "  *                     �������� (���������)   {1, 2} * {3, -1}         1\n";
                cout << "                                               {3, -1} * 4              { 12, -4 }\n";
                cout << "  /                     �������� �� ��        {3, -1} / 2              { 1.5, -0.5 }\n";
                break;
            case '3':
                return;
            case '4':
                exit(0);
            default:
                cout << " ���������� ����. ������� ���� ���:\n";
                break;
            }
        } while ((answer < '1') || (answer > '4'));
    } while (true);
}

UniversalExprType expr(bool get)
{
    if (++g_nestingChecker > MAX_NESTING_VALUE) {
        throw CalcException("����� �������� �����");
    }

    UniversalExprType left = term(get);

    while (true)
    {
        switch (g_currentToken)
        {
        case eTokenValue::PLUS:
            left = left + term(true);
            break;
        case eTokenValue::MINUS:
            left = left - term(true);
            break;
        default:
            g_nestingChecker--;
            return left;
        }
    }
}

UniversalExprType term(bool get)
{
    if (++g_nestingChecker > MAX_NESTING_VALUE) {
        throw CalcException("����� �������� �����");
    }

    UniversalExprType left = prim(get);
    while (true)
    {
        switch (g_currentToken)
        {
        case eTokenValue::MUL:
            left = left * prim(true);
            break;
        case eTokenValue::DIV:
        {
            UniversalExprType right = prim(true);
            if (right.exprType == eExprType::NUMBER)
            {
                if (right.value) {
                    left = left / right;
                }
                else {
                    throw CalcException("������ �������� �� 0");
                }
            }
            else {
                throw CalcException("������ ����� ����� �� ��");
            }
        }
            break;
        case eTokenValue::NUMBER:
        case eTokenValue::LP:
        case eTokenValue::LB:
            left = left * prim(false);
            break;
        case eTokenValue::RP:
            g_parenthesesCount--;
            if (g_parenthesesCount < 0) {
                throw CalcException("�������� �������� �������� )");
            }
            g_nestingChecker--;
            return left;
        case eTokenValue::RB:
            g_bracesCount--;
            if (g_bracesCount < 0) {
                throw CalcException("�������� �������� �������� }");
            }
            g_nestingChecker--;
            return left;
        default:
            g_nestingChecker--;
            return left;
        }
    }
}

UniversalExprType prim(bool get)
{
    if (++g_nestingChecker > MAX_NESTING_VALUE) {
        throw CalcException("����� �������� �����");
    }

    UniversalExprType value{ 0.0 };

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
    case eTokenValue::LB:
    {
        g_bracesCount++;

        UniversalExprType vec;
        vec.exprType = eExprType::VECTOR;

        while (g_currentToken != eTokenValue::RB)
        {
            getToken();

            if (g_currentToken == eTokenValue::PRINT) {
                throw CalcException("�������� }");
            }

            vec.values.push_back(expr(false));
        }

        value = vec;

        getToken();
    }
        break;
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
        string stringValue = g_stringValue;

        if ((stringValue == "sin") ||
            (stringValue == "cos") ||
            (stringValue == "tan") ||
            (stringValue == "cot"))
        {
            value = prim(true);

            if (stringValue == "sin")
            {
                if (value.exprType != eExprType::NUMBER) {
                    throw CalcException("����� ��� ��� ����� ������� ����");
                }

                value.value = sin(value.value);
            }
            else if (stringValue == "cos")
            {
                if (value.exprType != eExprType::NUMBER) {
                    throw CalcException("����� ��� ��� ����� ������� ������");
                }

                value.value = cos(value.value);
            }
            else if (stringValue == "tan")
            {
                if (value.exprType != eExprType::NUMBER) {
                    throw CalcException("����� ��� ��� ����� ������� �������");
                }

                if (std::abs(cos(value.value)) > MIN_POS_VALUE) {
                    value.value = sin(value.value) / cos(value.value);
                }
                else {
                    throw CalcException((string)"������ ������� ������� pi/2");
                }
            }
            else if (stringValue == "cot")
            {
                if (value.exprType != eExprType::NUMBER) {
                    throw CalcException("����� ��� ��� ����� ������� ���������");
                }
                    
                if (std::abs(sin(value.value)) > MIN_POS_VALUE) {
                    value = cos(value.value) / sin(value.value);
                }
                else {
                    throw CalcException((string)"������ ������� ��������� 0");
                }
            }
        }
        else if (stringValue == "log") {
            UniversalExprType base{ 10.0 };
            getToken();
            if (g_currentToken == eTokenValue::LSB)
            {
                base = expr(true);
                if (base.exprType != eExprType::NUMBER) {
                    throw CalcException("������ ��������� ������ ���� ����");
                }

                if (base.value < MIN_POS_VALUE) {
                    throw CalcException("������ ��������� ������ ���� �������� ����");
                }
                if (std::abs(base.value - 1.0) < MIN_POS_VALUE) {
                    throw CalcException("������ ��������� �� ���� ���� ����� 1");
                }
                if (g_currentToken != eTokenValue::RSB) {
                    throw CalcException("�������� ]");
                }
                getToken();
            }

            value = prim(false);
            if (value.exprType != eExprType::NUMBER) {
                throw CalcException("����� ��� ��� ����� ������� ��������");
            }

            if (value.value < MIN_POS_VALUE) {
                throw CalcException("������ ������� �������� �������� ��� �� ����");
            }
            value.value = log(value.value) / log(base.value);
        }
        else if (stringValue == "lg")
        {
            value = prim(true);
            if (value.exprType != eExprType::NUMBER) {
                throw CalcException("����� ��� ��� ����� ������� ��������");
            }

            if (value.value < MIN_POS_VALUE) {
                throw CalcException("������ ������� �������� �������� ��� �� ����");
            }
            value.value = log(value.value) / log(10.0);
        }
        else if (stringValue == "ln")
        {
            value = prim(true);
            if (value.exprType != eExprType::NUMBER) {
                throw CalcException("����� ��� ��� ����� ������� ��������");
            }

            if (value.value < MIN_POS_VALUE) {
                throw CalcException("������ ������� �������� �������� ��� �� ����");
            }
            value.value = log(value.value);
        }
        else if (stringValue == "sqrt")
        {
            value = prim(true);
            if (value.exprType != eExprType::NUMBER) {
                throw CalcException("����� ��� ��� ����� ������� ��������� ������");
            }

            if (value.value < 0.0) {
                throw CalcException("������ ������� ��������� ������ � �������� ���");
            }
            value.value = sqrt(abs(value.value));
        }
        else if (stringValue == "root")
        {
            UniversalExprType rootDegree{ 2.0 };

            getToken();
            if (g_currentToken == eTokenValue::LSB)
            {
                rootDegree = expr(true);
                if (rootDegree.exprType != eExprType::NUMBER) {
                    throw CalcException("�������� ������ ������ ���� ����");
                }

                if (rootDegree.value < MIN_POS_VALUE) {
                    throw CalcException("�������� ������ ������ ���� ����������� ����");
                }

                double intPartOfRootDegree = 0.0;
                double fracPartOfRootDegree = modf(rootDegree.value, &intPartOfRootDegree);

                if ((fracPartOfRootDegree < MIN_POS_VALUE) && (intPartOfRootDegree >= 1.0)) {
                    rootDegree = intPartOfRootDegree;
                }
                else {
                    throw CalcException("�������� ������ ������ ���� ����������� ����");
                }

                if (g_currentToken != eTokenValue::RSB) {
                    throw CalcException("�������� ]");
                }

                getToken();
            }
            
            value = prim(false);
            if (value.exprType != eExprType::NUMBER) {
                throw CalcException("������ ����� ������� ����� � ���");
            }

            bool negValueFlag = (value.value < 0.0);

            if (negValueFlag && !(fmod(rootDegree.value, 2))) {
                throw CalcException("������ ������� ������ ������ ������ � �������� ���");
            }

            value.value = pow(abs(value.value), 1.0 / rootDegree.value);
            if (negValueFlag) {
                value.value *= -1;
            }
        }
        else if (stringValue == "exp")
        {
            value = prim(true);
            if (value.exprType != eExprType::NUMBER) {
                throw CalcException("���������� ����� ������� ����� �� ���");
            }

            if (value.value > MAX_VALUE_FOR_EXPONENT) {
                throw CalcException("����� ������ �������� ����������");
            }
            value.value = exp(value.value);
        }
        else if (stringValue == "abs") {
            value = prim(true);
            if (value.exprType != eExprType::NUMBER) {
                throw CalcException("���������� ������� ����� ������� ����� ��� ���");
            }

            value.value = abs(value.value);
        }
        else {
            throw CalcException((string)"�������� �������� ����� " + stringValue[0]);
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
            UniversalExprType powerValue = prim(true);
            if (powerValue.exprType != eExprType::NUMBER) {
                throw CalcException("�������� ������ ������ ���� ����");
            }

            double intPartOfPower = 0.0;
            double fracPartOfPower = modf(powerValue.value, &intPartOfPower);

            if (abs(fracPartOfPower) < MIN_POS_VALUE)
            {
                fracPartOfPower = 0.0;
                powerValue = intPartOfPower;
            }

            if (value.exprType == eExprType::NUMBER)
            {
                if ((abs(value.value) < MIN_POS_VALUE) && (powerValue.value <= MIN_POS_VALUE)) {
                    throw CalcException("0 ����� �������� ����� � �������� �������");
                }

                if ((value.value < 0.0) && (fracPartOfPower)) {
                    throw CalcException("������ �������� ������� �� � �������� �������");
                }

                value.value = pow(value.value, powerValue.value);
            }
            else if (value.exprType == eExprType::VECTOR)
            {
                if ((powerValue.value < MIN_POS_VALUE) || (fracPartOfPower)) {
                    throw CalcException("�������� ������ ������� ������ ���� ����������� ����");
                }

                UniversalExprType result{ value };
                for (double i = 1.0; i < powerValue.value; i++) {
                    result = result * value;
                }
                value = result;
            }
        }
            break;
        case eTokenValue::FACT:
        {
            if (value.exprType != eExprType::NUMBER) {
                throw CalcException("��������� ����� ������� ����� ��� ���");
            }

            if (value.value < 0.0) {
                throw CalcException("������ ������� ��������� �������� ���");
            }
            if (value.value > MAX_VALUE_FOR_FACTORIAL) {
                throw CalcException("����� ������ �������� ����������");
            }

            double intPartOfValue;
            double fracPartOfValue = modf(value.value, &intPartOfValue);

            if (fracPartOfValue < MIN_POS_VALUE) {
                value.value = factorial((unsigned long long)intPartOfValue);
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
    case '{':
    case '}':
    case ',':
        return g_currentToken = (eTokenValue)ch;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
    {
        string strNumber = "";
        unsigned dotsCount = 0;
        if (ch == '.') {
            dotsCount++;
        }
        strNumber.push_back(ch);

        while (g_expression.get(ch) && (isdigit(ch) || ch == '.'))
        {
            if (ch == '.' && dotsCount++) {
                throw CalcException("�� �� ���� ���������� ������� ����������� ������");
            }
            strNumber.push_back(ch);
        }
        g_expression.putback(ch);

        double number = stod(strNumber);

        double intPartOfNumber;
        double fracPartOfNumber = modf(number, &intPartOfNumber);
        if (abs(fracPartOfNumber) < MIN_POS_VALUE) {
            number = intPartOfNumber;
        }

        g_numberValue = (UniversalExprType)number;

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

            if (CONSTANTS.find(g_stringValue) != CONSTANTS.end())
            {
                g_numberValue = CONSTANTS.at(g_stringValue);
                return g_currentToken = eTokenValue::NUMBER;
            }
            else {
                return g_currentToken = eTokenValue::WORD;
            }
        }
        else {
            throw CalcException((string)"�������� �������� ����� " + ch);
        }
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