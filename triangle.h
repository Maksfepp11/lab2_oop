#ifndef TRIANGLE_H  
#define TRIANGLE_H  

#include <iostream>  //  бібліотеки для ввід/вивід потоками
#include <cmath>     // Підключення математичних функцій 
#include <vector>    // Підключення  контейнера vector
using namespace std; 


struct Point {
    double x, y; // точка має координати x та y
};


struct Triangle {
    Point A, B, C; // Трикутник має три вершини: A, B, C

    double area() const;       // Метод для обчислення площі трикутника
    bool contains(const Point &P) const;  // Метод для перевірки, чи належить точка трикутнику
    bool degenerate() const;  // Метод для перевірки, чи трикутник вироджений (нульова площа)
    bool on_border(const Point &P) const;  // Метод для перевірки, чи точка на межі трикутника
};

// Функція для обчислення відстані між двома точками
double distance(const Point &p1, const Point &p2);

// Функція для обчислення площі трикутника за формулою Герона
double heronArea(const Triangle &t);

// Функція для обчислення площі трикутника за допомогою формули Гауса
double gaussArea(const Triangle &t);

// Функція для обчислення векторного добутку між трьома точками
double cross_product(const Point &p1, const Point &p2, const Point &p3);

#endif 

 