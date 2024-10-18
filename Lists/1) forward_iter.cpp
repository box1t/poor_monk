#include <iostream>
#include <forward_list>
#include <unordered_map>

// Найти максимальный элемент в списке.


/*

// 2 (-). элемент для доп памяти. завести вектор, его отсортировать. - это лишнее действие. ПРОМАХ.

// 3 (+). Завести максимальный элемент, равный нулю. Если текущий больше максимального - он максимальный.

int main() {
    std::forward_list<int> lst {3, 2, 5, 4, 8, 1};
    int max = 0;
    for (std::forward_list<int>::iterator iter = lst.begin(); iter != lst.end(); ++iter) {
        if(*iter > max) {
            max = *iter;
        }
        ++iter;
    }    
    std::cout << max << std::endl;
}

*/


// 1. Завести мапку. (но в сишном стайле мапки нет!)


int main() {
    std::forward_list<int> lst {3, 2, 5, 4, 8,1};
    std::unordered_map<int, int> mapka;
}
// Пройтись по списку, заполнить мапку? а смысл? чем это отличается от работы с итератором?
// Ты просто вспоминаешь тут, как работает мапка, не более. Но задача про СПИСОК.
