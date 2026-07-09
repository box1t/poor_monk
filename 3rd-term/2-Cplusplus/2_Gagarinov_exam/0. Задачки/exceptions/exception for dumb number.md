

```c++

#include <iostream>
#include <math.h>
#include <stdexcept>

void simple(int a) {
    int countDel = 0;
    for(int i=1; i<=sqrt(a); i++){
        if(a%i==0){
            countDel+=1;
        }
        if(countDel>1){
            throw std::string("BAD NUM");   
        }
    }
}

int main() {
    try {
        simple(14);
    }
    catch(const std::string& ex) {
        std::cout<<ex<<std::endl;
    }
    return 0;
}

```

```c++
#include <iostream>
#include <stdexcept>

void simpleAction(int a) {
    int studentsCounter = 0;
    for(int i=1; i<=27; ++i){
        if(studentsCounter<10){
            throw std::string("BAD NUM");   
        }
    }
}

int main() {
    try {
        simple(14);
    }
    catch(const std::string& ex) {
        std::cout<<ex<<std::endl;
    }
    return 0;
}

```


