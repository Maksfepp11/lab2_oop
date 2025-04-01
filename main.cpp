#include "triangle.h"
#include <iostream>
#include <vector>

int main() {
    Triangle t;
    
    std::cout << "Введіть координати трикутника (x1 y1 x2 y2 x3 y3): ";
    std::cin >> t.A.x >> t.A.y >> t.B.x >> t.B.y >> t.C.x >> t.C.y;

    if (t.degenerate()) {
        std::cout << "Трикутник вироджений!\n";
        return 1;
    }

    int choice;
    do {
        std::cout << "Оберіть метод перевірки приналежності точки трикутнику:\n";
        std::cout << "1 - Метод площ\n";
        std::cout << "2 - Метод векторного добутку\n";
        std::cout << "Ваш вибір: ";
        std::cin >> choice;

        if (choice != 1 && choice != 2) {
            std::cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 1 && choice != 2);

    int n;
    std::cout << "Введіть кількість точок: ";
    std::cin >> n;

    std::vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        std::cout << "Введіть координати точки " << i + 1 << " (x y): ";
        std::cin >> points[i].x >> points[i].y;
    }

    std::cout << "\nПеревірка точок:\n";
    for (const auto &p : points) {
        bool isInside = false;

        if (choice == 1) {
            isInside = t.contains(p, 1); // Метод площі
        } else if (choice == 2) {
            isInside = t.on_border(p); // Метод векторного добутку
            if (!isInside) {
                isInside = t.contains(p, 2); // Якщо точка не всередині, перевіряємо, чи на межі
            }
        }

        if (isInside) {
            std::cout << "Точка (" << p.x << ", " << p.y << ") належить трикутнику.\n";
        } else {
            std::cout << "Точка (" << p.x << ", " << p.y << ") не належить трикутнику.\n";
        }
    }

    return 0;
}

