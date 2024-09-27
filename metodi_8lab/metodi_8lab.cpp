#include <iostream>
#include <cmath>

using namespace std;

double equation(double x) {
    return cos(x) - 1.0 / (x - 2.0);
}

double derivative(double x) {
    return -sin(x) + 1.0 / pow(x - 2.0, 2);
}

double tangentMethod(double initialGuessA, double initialGuessB, double epsilon, int maxIterations) {
    setlocale(0, "RUS");

    // Инициализация начальных значений
    double xA = initialGuessA;
    double xB = initialGuessB;

    // Проверка знаков функции на концах интервала
    if (equation(xA) * equation(xB) > 0) {
        cerr << "Ошибка: функция должна менять знак на концах интервала." << endl;
        return numeric_limits<double>::quiet_NaN();
    }

    // Процесс итераций
    for (int i = 0; i < maxIterations; ++i) {
        double f_xA = equation(xA);
        double f_prime_xA = derivative(xA);

        if (abs(f_prime_xA) < 1e-10) {
            cerr << "Деление на ноль. Метод касательных не применим." << endl;
            return numeric_limits<double>::quiet_NaN();
        }

        double xA_new = xA - f_xA / f_prime_xA;

        if (abs(xA_new - xA) < epsilon) {
            return xA_new;
        }

        xA = xA_new;
    }

    cerr << "Достигнуто максимальное количество итераций. Решение не найдено." << endl;
    return numeric_limits<double>::quiet_NaN();
}

int main() {
    setlocale(0, "RUS");

    // Ввод начальных значений и точности
    double initialGuessA, initialGuessB;
    double epsilon;

    cout << "Введите начальное значение a: ";
    cin >> initialGuessA;

    cout << "Введите начальное значение b: ";
    cin >> initialGuessB;

    cout << "Введите точность: ";
    cin >> epsilon;

    // Задаем максимальное количество итераций
    int maxIterations = 1000;

    // Ищем корень уравнения с использованием метода касательных
    double result = tangentMethod(initialGuessA, initialGuessB, epsilon, maxIterations);

    if (!isnan(result)) {
        cout << "Приближенный корень: " << result << endl;
    }

    return 0;
}
