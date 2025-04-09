#include "triangle.h"  

extern int choice;  // Оголошення змінної choice

double distance(const Point &p1, const Point &p2) {
    // Функція для обчислення відстані між двома точками за формулою відстані
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double heronArea(const Triangle &t) {
    // Функція для обчислення площі трикутника за формулою Герона
    double a = distance(t.A, t.B);  // Відстань між точками A і B
    double b = distance(t.B, t.C);  // Відстань між точками B і C
    double c = distance(t.C, t.A);  // Відстань між точками C і A
    double s = (a + b + c) / 2;     // Півпериметр трикутника
    return sqrt(s * (s - a) * (s - b) * (s - c));  // Площа за формулою Герона
}

double gaussArea(const Triangle &t) {
    // Функція для обчислення площі трикутника за допомогою формули Гауса
    return 0.5 * fabs(t.A.x * (t.B.y - t.C.y) + t.B.x * (t.C.y - t.A.y) + t.C.x * (t.A.y - t.B.y));
}

double cross_product(const Point &p1, const Point &p2, const Point &p3) {
    // Функція для обчислення векторного добутку між трьома точками (перетин площин)
    return ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}

double Triangle::area() const {
    // Метод для обчислення площі трикутника. Вибір методу залежить від змінної choice
    if (choice == 1) {
        return heronArea(*this);  // Використовуємо формулу Герона, якщо вибрано метод 1
    } else {
        return gaussArea(*this);  // Використовуємо формулу Гауса, якщо вибрано метод 2
    }
}

bool Triangle::contains(const Point &P) const {
    // Метод для перевірки, чи належить точка трикутнику
    if (degenerate()) return false;  // Якщо трикутник вироджений, точка не може належати трикутнику

    if (choice == 1) {
        // Якщо вибрано метод площі (Герон)
        double S1 = heronArea({A, B, P});  // Площа трикутника, утвореного точками A, B і P
        double S2 = heronArea({B, C, P});  // Площа трикутника, утвореного точками B, C і P
        double S3 = heronArea({C, A, P});  // Площа трикутника, утвореного точками C, A і P
        double S_main = area();  // Площа основного трикутника

        // Якщо сума площ трикутників дорівнює площі основного трикутника (з точністю до похибки), точка всередині
        return fabs(S_main - (S1 + S2 + S3)) < 1e-9;
    } else {
        // Якщо вибрано метод векторного добутку
        double CP1 = cross_product(A, B, P);  // Векторний добуток для точки P та сторін AB
        double CP2 = cross_product(B, C, P);  // Векторний добуток для точки P та сторін BC
        double CP3 = cross_product(C, A, P);  // Векторний добуток для точки P та сторін CA

        // Якщо всі векторні добутки мають однаковий знак або всі негативні, точка всередині трикутника
        return (CP1 >= 0 && CP2 >= 0 && CP3 >= 0) || (CP1 <= 0 && CP2 <= 0 && CP3 <= 0);
    }
}

bool Triangle::degenerate() const {
    // Метод для перевірки, чи є трикутник виродженим (площа майже нульова)
    return area() < 1e-9;
}

bool Triangle::on_border(const Point &P) const {
    // Метод для перевірки, чи належить точка межі трикутника
    return (fabs(cross_product(A, B, P)) < 1e-9 &&  // Точка на межі між A і B
            min(A.x, B.x) <= P.x && P.x <= max(A.x, B.x) &&
            min(A.y, B.y) <= P.y && P.y <= max(A.y, B.y)) ||

           (fabs(cross_product(B, C, P)) < 1e-9 &&  // Точка на межі між B і C
            min(B.x, C.x) <= P.x && P.x <= max(B.x, C.x) &&
            min(B.y, C.y) <= P.y && P.y <= max(B.y, C.y)) ||

           (fabs(cross_product(C, A, P)) < 1e-9 &&  // Точка на межі між C і A
            min(C.x, A.x) <= P.x && P.x <= max(C.x, A.x) &&
            min(C.y, A.y) <= P.y && P.y <= max(C.y, A.y));
}
