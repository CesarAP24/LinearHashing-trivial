#include <string>
#include <cstring>
#include <iostream>

template <typename T>
int hash_function(T key, int capacity){
    return key % capacity;
}

int hash_function(std::string key, int capacity){
    int sum = 0;
    for(int i = 0; i < key.length(); i++){
        sum += key[i];
    }
    return sum % capacity;
}

int hash_function(char* key, int capacity){
    int sum = 0;
    for(int i = 0; i < strlen(key); i++){
        sum += key[i];
    }
    return sum % capacity;
}