

```c++
##### Юнит-тесты

Контракты функции:

- предусловие (precondition / expect)
- постусловие (postcondition / ensure)
- инвариант (precondition + postcondition / invariant)

Приведите примеры контрактов (exception-ы исключаем из рассмотрения, "сейчас про них ничего не знаем"):

double sqrt(double x);
bool binary_search(int *arr, int n, int value);
unsigned read_n(std::istream& is);

Типы функциональных тестов:

- позитивный сценарий
- негативный сценарий
- граничные условия

Приведите примеры тестов на функции `sqrt`, `binary_search`, `read_n`

Для упражнения напишем тесты на функцию, считающую длину ломаной

// polyline.h
#pragma once
#include <vector>

struct Point
{
	float x;
	float y;
};

float get_polyline_len(const std::vector<Point>& polyline);

// polyline.cpp
#include "polyline.h"
#include <cmath>

float get_polyline_len(const std::vector<Point>& polyline)
{
    float rv = 0;
    for (int i = 1; i < polyline.size(); ++i)
    {
        const Point prev = polyline[i - 1];
        const Point curr = polyline[i];
        const float dx = curr.x - prev.x;
        const float dy = curr.y - prev.y;
        rv += std::sqrt(dx * dx + dy * dy);
    }
    return rv;
}

// polyline_test.cpp
#include "polyline.h"
#include "gtest/gtest.h"

TEST(get_polyline_len, empty_polyline)
{
	std::vector<Point> empty_poly;
	const double len = get_polyline_len(empty_poly);
	EXPECT_EQ(0, len);
}

TEST(get_polyline_len, single_point_polyline)
{
	std::vector<Point> poly{{1,1}};
	const double len = get_polyline_len(poly);
	EXPECT_EQ(0, len);
}

// ???
```

