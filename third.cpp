#include <iostream>
using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b) {unsigned  long long t = b; b = a % b; a = t; }
    return a;
}

unsigned long long powLL(long long base, int exp) {
    unsigned long long result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}

// Рекурсивное вычисление числа Эйлера
unsigned long long eulerianNumber(int n, int k) {
    if (n == 0 && k == 0) return 1;
    if (k < 0 || k >= n) return 0;
    
    return (n - k) * eulerianNumber(n - 1, k - 1) + (k + 1) * eulerianNumber(n - 1, k);
}

int main() {
    int a, b;
    cout << "Введите а и b: ";
    cin >> a >> b;

    if (a > 10 || a < 1 || b > 10 || b < 1){
        cout << "Числа должны бать от 1 до 10" << endl;
        return 0;
    }
    if (b == 1) {
        cout << "infinity" << endl;
        return 0;
    }
    
    // Вычисляем числитель
    unsigned long long numerator = 0;
    for (int k = 0; k < a; k++) {
        numerator += eulerianNumber(a, k) * powLL(b, a - k);
    }
    
    // Вычисляем знаменатель
    unsigned long long denominator = powLL(b - 1, a + 1);
    
    // Сокращаем дробь
    unsigned long long g = gcd(numerator, denominator);
    cout << numerator / g << "/" << denominator / g << endl;
    
    return 0;
}
