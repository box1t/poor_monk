#include <vector>
#include <string>


std::string CommonPrefix(const std::vector<std::string>& words) {
    std::string longest_prefix = "";
    if (words.size() == 0) {
        return longest_prefix;
    }

    while (words[0][0] == words[i][j]) {
        longes_prefix += words[i][j];  
    }


    for (int i = 0; i < words[i]; ++i) {
        for (int j = 0; j < words[i][j]; ++j) {
            
        }
    }

    return longest_prefix;
}

/*
Я понимаю, как сравнить 2 строки.
Окей. Напиши этот код.



Я не понимаю, как сравнить n строк.
А почему бы не сделать одну строку основной, и к ней прикладывать все?
Почему бы не сделать 1 строку - longest prefix? И модернизировать условие, если вектор пуст.

*/

