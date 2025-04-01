#include "triangle.h"
#include <cmath>


double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double heronArea(const Triangle &t) {
    double a = distance(t.A, t.B);
    double b = distance(t.B, t.C);
    double c = distance(t.C, t.A);
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double gaussArea(const Triangle &t) {
    return 0.5 * fabs(t.A.x * (t.B.y - t.C.y) + t.B.x * (t.C.y - t.A.y) + t.C.x * (t.A.y - t.B.y));
}

double crossProduct(const Point &A, const Point &B, const Point &C) {
    return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
}

double Triangle::area(int method) const {
    return (method == 1) ? heronArea(*this) : gaussArea(*this);
}

bool Triangle::contains(const Point &P, int method) const {
    if (degenerate()) return false;

    if (method == 1) {
        double S1 = heronArea({A, B, P});
        double S2 = heronArea({B, C, P});
        double S3 = heronArea({C, A, P});
        double S_main = area(1);
        return fabs(S_main - (S1 + S2 + S3)) < 1e-9;
    }
    double CP1 = crossProduct(A, B, P);
    double CP2 = crossProduct(B, C, P);
    double CP3 = crossProduct(C, A, P);

    // Якщо хоча б один векторний добуток нульовий, то точка на межі
    if (fabs(CP1) < 1e-9 || fabs(CP2) < 1e-9 || fabs(CP3) < 1e-9) {
        return true;
    }
    
    return (CP1 >= 0 && CP2 >= 0 && CP3 >= 0) || (CP1 <= 0 && CP2 <= 0 && CP3 <= 0);
}

bool Triangle::degenerate() const {
    return area(1) < 1e-9;
}

bool Triangle::on_border(const Point &P) const {
    return contains(P, 2) && (fabs(crossProduct(A, B, P)) < 1e-9 || fabs(crossProduct(B, C, P)) < 1e-9 || fabs(crossProduct(C, A, P)) < 1e-9);
}


void runCode() {
    int method;
    cout << "Оберіть метод перевірки приналежності:\n1 - Метод площі (Герон)\n2 - Метод векторного добутку\nВаш вибір: ";
    cin >> method;
    if (method != 1 && method != 2) method = 1;

    Triangle t;
    cout << "Введіть координати трикутника (x1 y1 x2 y2 x3 y3): ";
    cin >> t.A.x >> t.A.y >> t.B.x >> t.B.y >> t.C.x >> t.C.y;
    
    cout << "Площа трикутника: " << t.area(method) << endl;
    if (t.degenerate()) {
        cout << "Трикутник вироджений!" << endl;
        return;
    }
    
    int n;
    cout << "Введіть кількість точок: ";
    cin >> n;
    vector<Point> points(n);

    for (int i = 0; i < n; ++i) {
        cout << "Введіть координати точки " << i + 1 << " (x y): ";
        cin >> points[i].x >> points[i].y;

        if (t.on_border(points[i])) {
            cout << "Точка лежить на межі трикутника." << endl;
        } else if (t.contains(points[i], method)) {
            cout << "Точка належить трикутнику." << endl;
        } else {
            cout << "Точка не належить трикутнику." << endl;
        }
    }
}