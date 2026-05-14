// Break amount into smallest banknotes

#include <iostream>
#include <vector>

/*
Complexity: O(n)
Pros: simple af
Cons: a lot of the same code, not optimal, not modular
*/

int main() {
    int input_banknotes;
    std::cin >> input_banknotes; // 3661. cases: 1, 2, 5, 10, 50, 100. greedy algo. each time choose max, then - smallest. you need counter for each var.
    std::vector<int> banknotes_amount;
    

    while (input_banknotes > 0) {

        if (input_banknotes / 100 > 0) {
            int poltosi = input_banknotes / 100;
            banknotes_amount.push_back(poltosi);
            input_banknotes = input_banknotes - poltosi * 100;
            std::cout << "100 - " << poltosi << std::endl;
        }
        else if (input_banknotes / 50 > 0) {
            int poltosi = input_banknotes / 50;
            banknotes_amount.push_back(poltosi);
            input_banknotes = input_banknotes - poltosi * 50;
            std::cout << "50 - " << poltosi << std::endl;
        }
        else if (input_banknotes / 10 > 0) {
            int poltosi = input_banknotes / 10;
            banknotes_amount.push_back(poltosi);
            input_banknotes = input_banknotes - poltosi * 10;
            std::cout << "10 - " << poltosi << std::endl;
        }
        else if (input_banknotes / 5 > 0) {
            int poltosi = input_banknotes / 5;
            banknotes_amount.push_back(poltosi);
            input_banknotes = input_banknotes - poltosi * 5;
            std::cout << "5 - " << poltosi << std::endl;
        }
        else if (input_banknotes / 2 > 0) {
            int poltosi = input_banknotes / 2;
            banknotes_amount.push_back(poltosi);
            input_banknotes = input_banknotes - poltosi * 2;
            std::cout << "2 - " << poltosi << std::endl;
        }
        else if (input_banknotes / 1 > 0) {
            int poltosi = input_banknotes / 1;
            banknotes_amount.push_back(poltosi);
            input_banknotes = input_banknotes - poltosi * 1;
            std::cout << "1 - " << poltosi << std::endl;
        }
    }
}

