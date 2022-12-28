//
// Created by Ilyas on 21.12.2021.
//

#ifndef INC_3LABA_MENUFUNC_H
#define INC_3LABA_MENUFUNC_H

#define maxCacheSize 1000
#define maxNumber 10000
#define maxLength 1000

#define maxNumberOfElementsOnThePage 200
#define minNumberOfElementsOnThePage 5
#define maxNumberOfWordsInTheString 1000
#define minNumberOfWordsInTheString 100

int randomNumber(){
    return rand() % maxNumber;
}

int randomLength(){
    while(true){
        int length = rand() % maxLength;
        if (length != 0)
            return length;
    }
}

int randomLengthInRange(int down, int up){
    while(true){
        int number;
        number = randomLength();
        if (number <= up and number >= down)
            return number;
    }
}

std::string randomString(const int length) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(length);

    for (int i = 0; i < length; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

std::string randomStringWithSpace(const int maxLengthOfWord) {
    int numberOfWords = randomLengthInRange(minNumberOfWordsInTheString,maxNumberOfWordsInTheString);
    std::string str;
    for (int i = 0; i < numberOfWords; i++){
        str += randomString(randomLengthInRange(1,maxLengthOfWord));
        str+= " ";
    }
    return str;
}


int getNumberInRange(int down, int up){
    while(true){
        int number;
        std::cin >> number;
        if (number <= up and number >= down)
            return number;
    }
}

int factorial(int x){
    if (x == 0)
        return 1;
    return x * factorial(x - 1);
}

int min(int a,int b){
    if (a<b)
        return a;
    return b;
}
#endif //INC_3LABA_MENUFUNC_H
