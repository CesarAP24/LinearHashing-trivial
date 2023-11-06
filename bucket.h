#include "forward_list.h"
#include <string>
#include <iostream>


template <typename K, typename V>
struct Data{
    K key;
    V value;

    Data(K key, V value){
        this->key = key;
        this->value = value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Data& d){
        os << d.key << ":" << d.value;
        return os;
    }
};

template <typename K, typename V>
struct bucket{
    ForwardList<Data<K, V>>* list;
    bucket* next = nullptr;
    int count = 0;
    bool overflowed = false;

    bucket(){
        //TO DO
    }

    ~bucket(){
        if(this->next != nullptr){
            delete this->next;
        }
    }

    void insert(K key, V value){
        //TO DO
    }

    void remove(K key){
        //TO DO
    }

    bool search(K key){
        //TO DO
    }
};