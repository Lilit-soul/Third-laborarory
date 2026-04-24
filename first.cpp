#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Функция, заданная графически (три участка)
double func(double x) {
    // Участок 1: [-5, -2] - линейная
    if (x <= -2.0) {
        return (1.0/3.0) * (x + 2.0);
    }
    
    // Участок 2: (-2, 2) - тангенс
    if (x < 2.0) {
        return tan(x / 2.0);
    }
    
    // Участок 3: [2, 5] - линейная
    return 0.5 * x - 1.5;
}

int main() {
    double x_start = -5.0;
    double x_end = 5.0;
    double dx = 0.2;
    
    cout << "  Отрезок [-5; -2]: y = (1/3)*(x+2)" << endl;
    cout << "  Отрезок [-2;  2]: y = tg(x/2)" << endl;
    cout << "  Отрезок [ 2;  5]: y = 0.5*x - 1.5" << endl;
    cout << endl;
    
    cout << fixed << setprecision(6);
    cout << "    x     |      y      | Отрезок" << endl;
    cout << "-------------------------------------" << endl;
    
    for (double x = x_start; x <= x_end + 1e-9; x += dx) {
        double y;
        string segment;
        
        if (x <= -2.0) {
            y = (1.0/3.0) * (x + 2.0);
            segment = "[-5; -2]";
        }
        else if (x < 2.0) {
            y = tan(x / 2.0);
            segment = "[-2; 2]";
        }
        else {
            y = 0.5 * x - 1.5;
            segment = "[2; 5]";
        }
        
        // Отметка точек разрыва
        if (fabs(x + 2.0) < 1e-7) {
            cout << fixed << setprecision(1) << setw(6) << x;
            cout << "  " << fixed << setprecision(6) << setw(15) << y;
            cout << "   " << segment << "  (разрыв справа)" << endl;
        }
        else if (fabs(x - 2.0) < 1e-7) {
            cout << fixed << setprecision(1) << setw(6) << x;
            cout << "  " << fixed << setprecision(6) << setw(15) << y;
            cout << "   " << segment << "  (разрыв слева)" << endl;
        }
        else {
            cout << fixed << setprecision(1) << setw(6) << x;
            cout << "  " << fixed << setprecision(6) << setw(15) << y;
            cout << "   " << segment << endl;
        }
    }
    
    cout << endl;
    cout << "Примечание: в точках x = -2 и x = 2 - разрывы функции" << endl;
    
    return 0;
}
