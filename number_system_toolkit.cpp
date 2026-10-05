#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// --------------------------------------------------
// Get digit value
// Example: 'A' -> 10, 'B' -> 11, '5' -> 5
// --------------------------------------------------
int digitValue(char ch)
{
    ch = toupper(ch);

    if (ch >= '0' && ch <= '9')
        return ch - '0';

    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;

    return -1;
}

// --------------------------------------------------
// Get character for digit value
// Example: 10 -> A
// --------------------------------------------------
char digitChar(int value)
{
    if (value < 10)
        return '0' + value;

    return 'A' + (value - 10);
}

// --------------------------------------------------
// Validate number according to base
// --------------------------------------------------
bool isValid(string num, int base)
{
    if (num.empty())
        return false;

    int start = 0;

    // Negative numbers only allowed for decimal
    if (num[0] == '-')
    {
        if (base != 10)
            return false;

        start = 1;
    }

    if (start == num.length())
        return false;

    for (int i = start; i < num.length(); i++)
    {
        int value = digitValue(num[i]);

        if (value < 0 || value >= base)
            return false;
    }

    return true;
}

// --------------------------------------------------
// Convert any base number to decimal
// --------------------------------------------------
long long toDecimal(string num, int base)
{
    bool negative = false;

    if (num[0] == '-')
    {
        negative = true;
        num = num.substr(1);
    }

    long long decimal = 0;

    for (char ch : num)
    {
        int digit = digitValue(ch);

        decimal = decimal * base + digit;
    }

    if (negative)
        decimal = -decimal;

    return decimal;
}

// --------------------------------------------------
// Convert decimal to another base
// --------------------------------------------------
string fromDecimal(long long decimal, int base)
{
    if (decimal == 0)
        return "0";

    bool negative = false;

    if (decimal < 0)
    {
        negative = true;
        decimal = -decimal;
    }

    string result = "";

    while (decimal > 0)
    {
        int remainder = decimal % base;

        result += digitChar(remainder);

        decimal /= base;
    }

    reverse(result.begin(), result.end());

    if (negative)
        result = "-" + result;

    return result;
}

// --------------------------------------------------
// Display positional ledger
// Example:
// 101101
//
// 1 * 2^5 = 32
// 0 * 2^4 = 0
// ...
// --------------------------------------------------
void showLedger(string num, int base)
{
    cout << "\n----- Positional Ledger -----\n";

    long long total = 0;
    int n = num.length();

    for (int i = 0; i < n; i++)
    {
        int digit = digitValue(num[i]);
        int power = n - 1 - i;

        long long value = digit;

        for (int j = 0; j < power; j++)
            value *= base;

        cout << digit << " * "
             << base << "^"
             << power << " = "
             << value << endl;

        total += value;
    }

    cout << "-----------------------------\n";
    cout << "Decimal = " << total << endl;
}

// --------------------------------------------------
// Convert one number
// --------------------------------------------------
void convertNumber()
{
    int fromBase, toBase;
    string number;

    cout << "\nAvailable Bases:\n";
    cout << "2  - Binary\n";
    cout << "8  - Octal\n";
    cout << "10 - Decimal\n";
    cout << "16 - Hexadecimal\n";

    cout << "\nEnter source base: ";
    cin >> fromBase;

    cout << "Enter target base: ";
    cin >> toBase;

    cout << "Enter number: ";
    cin >> number;

    // Validation
    if (!isValid(number, fromBase))
    {
        cout << "\nError: Invalid digit for base "
             << fromBase << ".\n";
        return;
    }

    // Convert to decimal
    long long decimal = toDecimal(number, fromBase);

    cout << "\nValid input!\n";

    cout << number << " (Base "
         << fromBase << ")";

    cout << " = "
         << decimal << " (Decimal)\n";

    // Show positional calculation
    if (fromBase != 10)
        showLedger(number, fromBase);

    // Convert decimal to target base
    string result = fromDecimal(decimal, toBase);

    cout << "\nResult: "
         << result
         << " (Base "
         << toBase << ")\n";
}

// --------------------------------------------------
// Arithmetic
// --------------------------------------------------
void arithmetic()
{
    int base;
    string a, b;
    char op;

    cout << "\nEnter working base (2 / 8 / 10 / 16): ";
    cin >> base;

    cout << "Enter first number: ";
    cin >> a;

    cout << "Enter operator (+ - * /): ";
    cin >> op;

    cout << "Enter second number: ";
    cin >> b;

    // Validate operands
    if (!isValid(a, base))
    {
        cout << "Error: Invalid first operand.\n";
        return;
    }

    if (!isValid(b, base))
    {
        cout << "Error: Invalid second operand.\n";
        return;
    }

    // Convert to decimal
    long long decimalA = toDecimal(a, base);
    long long decimalB = toDecimal(b, base);

    cout << "\n----- Calculation Steps -----\n";

    cout << a << " -> Decimal = "
         << decimalA << endl;

    cout << b << " -> Decimal = "
         << decimalB << endl;

    long long result;

    switch (op)
    {
    case '+':

        result = decimalA + decimalB;
        break;

    case '-':

        result = decimalA - decimalB;
        break;

    case '*':

        result = decimalA * decimalB;
        break;

    case '/':

        if (decimalB == 0)
        {
            cout << "Error: Division by zero.\n";
            return;
        }

        result = decimalA / decimalB;
        break;

    default:

        cout << "Invalid operator.\n";
        return;
    }

    cout << "\nDecimal result = "
         << result << endl;

    // Convert result back to original base
    string finalResult = fromDecimal(result, base);

    cout << "Result in Base "
         << base << " = "
         << finalResult << endl;
}

// --------------------------------------------------
// Main Menu
// --------------------------------------------------
int main()
{
    int choice;

    while (true)
    {
        cout << "\n====================================\n";
        cout << "       NUMBER SYSTEM TOOLKIT\n";
        cout << "====================================\n";

        cout << "1. Convert Number System\n";
        cout << "2. Arithmetic Operations\n";
        cout << "3. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            convertNumber();
            break;

        case 2:
            arithmetic();
            break;

        case 3:
            cout << "\nProgram ended.\n";
            return 0;

        default:
            cout << "\nInvalid choice!\n";
        }
    }

    return 0;
}