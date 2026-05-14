
// Write a C program to calculate the distance between two points.
// Note: x1, y1, x2, y2 are all double values.

#include <iostream>
#include <cmath>

/*
Вычисляем квадрат расстояния, поскольку это l2 евклидова норма.
Это система из двух координат.
И здесь же появляется теорема пифагора, если возвести корень в квадрат.
Длина гипотенузы есть корень из сумм длин катетов прямоугольного треугольника.
*/

double count_square_distance(double x1, double y1, double x2, double y2) {
    return pow(pow((x2 - x1), 2) + pow((y2 - y1), 2), 0.5);
    //return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

int main() {
    double x1, y1, x2, y2;
    
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << count_square_distance(x1, y1, x2, y2);
}
