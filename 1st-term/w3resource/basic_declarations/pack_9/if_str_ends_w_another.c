// Write a C program that accepts two strings and checks whether the second string is present in the last part of the first string.

/*
// Write a C program that accepts two strings and checks whether the second string is present in the last part of the first string.

#include <stdio.h>

int main() {
    char str1[100];
    char str2[100];

    fgets(str1, sizeof(str1), stdin);
    fgets(str2, sizeof(str2), stdin);

    int i = 0;
    int j = 0;

    while (str1[i] != '\0') {
        ++i;
    }

    while (str2[j] != '\0') {
        ++j;
    }

    // Если убрать проверку i из условия while, программа попадет в ловушку, когда вторая строка длиннее первой. 
    // Если строка не входит (ни полностью, ни частично так, чтобы дойти до начала str2), цикл while прервется досрочно из-за несовпадения символов
    while (i >= 0 && j >= 0 && str1[i] == str2[j]) {
        --i;
        --j;
    }

    // Почему мы сравниваем именно j?
    if (j < 0) {
        printf("present");
    }
    else {
        printf("not present");
    }

}

*/


#include <stdio.h>
#include <string.h>

int main() {

    char str1[100];
    char str2[100];

    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin); // fgets работает с сохранением '\n' перед '\0'

    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);

    /*
    // Убираем "\n" после fgets. Если не убрать \n, strlen посчитает его как часть длины слова, и математика индексов собьется
    // string complement span (длина начального сегмента строки, не содержащего заданные символы). 
    // Простыми словами: она сканирует строку str с самого начала и возвращает индекс первого встреченного символа "\n"
    // Если "\n" не найден, она возвращает индекс завершающего нуля '\0'

    Зачем вообще убирать символ переноса строки \n?
    1. Ломается вся математика длин 
    2. Сравнение строк всегда будет давать "Не совпадает"
    3. Уродливый вывод на экран (двойные переносы) printf("Привет, %s!\n", name);
    */
    str1[strcspn(str1, "\n")] = '\0';  // "\n" в двойных кавычках используется только потому, что функция strcspn требует на вход строку (массив), а не одиночный символ
    str2[strcspn(str2, "\n")] = '\0'; // Двойные кавычки здесь были бы грубой ошибкой, так как нельзя впихнуть строку в одну ячейку char.

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    // Проверка 2: Сравниваем ВСЕ символы второй строки
    int found = 1; // Предполагаем, что строка найдена, пока не доказано обратное

    // Если вторая строка длиннее первой - она не может быть концом
    if (len2 > len1) {
        found = 0;
    }
    else {
        // Проверяем последние символы первой строки
        for (int i = 0; i < len2; i++) {
            // позиция, где должно начинаться совпадение.
            // Чтобы подстрока поместилась ровно в конец, она обязана начинаться с индекса: Стартовый индекс = Общая длина - Длина искомого хвоста
            // Переменная i в цикле for как раз и есть шаг от этого стартового индекса
            // i прибавляем к индексу, потому что идем по хвосту (концу) str1 слева направо, не проверяя начало str1
            
            if (str1[len1 - len2 + i] != str2[i]) {
                // Нашли первое несовпадение -> значит вся строка НЕ совпадает
                found = 0;
                break;
            }
        }
    }
    if (found) {
        printf("Second string is present at the end of first string\n");
    }
    else {
        printf("Second string is not present at the end\n");
    }
    return 0;
}