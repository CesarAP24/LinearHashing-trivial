#ifndef BUCKET_H
#define BUCKET_H
#include "forward_list.h"
#include <string>
#include <iostream>
#include "hash_function.h"



//sobrecarga de to_string para string
std::string to_string(std::string s){
    return s;
}



using namespace std;

template <typename K, typename V>
struct Data{
    K key;
    V value;

    Data(K key, V value){
        this->key = key;
        this->value = value;
    }

    Data(){
        this->key = K();
        this->value = V();
    }

    friend std::ostream& operator<<(std::ostream& os, const Data& d){
        os << d.key << ":" << d.value;
        return os;
    }
};

template <typename K, typename V>
struct Bucket{
    ForwardList<Data<K, V>>* list;
    Bucket* next = nullptr;
    bool overflowed = false;
    int max_collisions = 2;

    Bucket(){
        this->list = new ForwardList<Data<K, V>>();
        this->max_collisions = 2;
    }

    Bucket(int max_collisions){
        this->list = new ForwardList<Data<K, V>>();
        this->max_collisions = max_collisions;
    }

    ~Bucket(){
        delete this->list;
        if(this->next != nullptr){
            delete this->next;
        }
    }


    struct b_iterator{
        Bucket<K, V>* current;

        b_iterator(){
            this->current = nullptr;
        }

        b_iterator(const b_iterator& other){
            this->current = other.current;
        }

        b_iterator& operator=(const b_iterator& other){
            this->current = other.current;
            return *this;
        }

        b_iterator(Bucket* current){
            this->current = current;
        }

        b_iterator& operator++(){
            this->current = this->current->next;
            return *this;
        }

        bool operator!=(const b_iterator& other){
            return this->current != other.current;
        }

        Bucket& operator*(){
            return *this->current;
        }

        Bucket* operator->(){
            return this->current;
        }
    };

    void insert(K key, V value){
        Bucket* current = this;
        while (current->overflowed){
            if (current->next == nullptr){
                current->next = new Bucket<K, V>(this->max_collisions);
                current->next->overflowed = true;
                current = current->next;
                break;
            }
            current = current->next;
        }

        if (current->list->count < this->max_collisions){
            current->list->push_back(Data<K, V>(key, value));
        }
        else{
            current->overflowed = true;
            current->insert(key, value);
        }
    }

    void remove(K key){
        typename Bucket<K, V>::b_iterator it;
        typename Bucket<K, V>::b_iterator prev;
        for (it = this->begin(); it != this->end(); ++it){
            for (auto it2 = it->list->begin(); it2 != it->list->end(); ++it2){ //it2 es el bucket actual
                if ((*it2).key == key){
                    if(it->list->count <= 1 && it->next != nullptr){
                        (*prev).next = (*it).next;
                        delete it.current;
                    }else{
                        this->list->erase(it2);
                    }
                    return;
                }
            }
            prev = it;
        }

    }

    bool search(K key){
        for (auto it = this->begin(); it != this->end(); ++it){
            for (auto it2 = it->list->begin(); it2 != it->list->end(); ++it2){
                if ((*it2).key == key){
                    return true;
                }
            }
        }
        return false;
    }

    V get(K key){
        for(auto it=this->begin(); it!= this->end(); ++it){
            for(auto it2 = it->list->begin(); it2 != it->list->end(); ++it2){
                if((*it2).key == key){
                    return (*it2).value;
                }
            }
        }
        return V();
    }



    b_iterator begin(){
        return b_iterator(this);
    }

    b_iterator end(){
        return b_iterator(nullptr);
    }

    bool is_overflowed(){
        return this->overflowed;
    }

    string toString(){
        string result = "";
        for (auto it = this->begin(); it != this->end(); ++it){
            result += "[";
            for (auto it2 = it->list->begin(); it2 != it->list->end(); ++it2){
                result += to_string((*it2).key) + ":" + to_string((*it2).value);
                if (it2->next != nullptr){
                    result += ", ";
                }
            }
            result += "]";

            if (it->next != nullptr){
                result += " -> ";
            }
        }
        return result;
    }

    std::string getBucketInfo() const {
        std::string info = "Overflowed: " + std::to_string(overflowed) + "\n";
        info += "Max Collisions: " + std::to_string(max_collisions) + "\n";

        for (auto it = begin(); it != end(); ++it) {
            info += "  [";
            for (auto it2 = it->list->begin(); it2 != it->list->end(); ++it2) {
                info += to_string((*it2).key) + ":" + to_string((*it2).value);
                if (it2->next != nullptr) {
                    info += ", ";
                }
            }
            info += "]";

            if (it->next != nullptr) {
                info += " -> ";
            }
            info += "\n";
        }

        return info;
    }

};


template <typename K, typename V>
Bucket<K, V>* split_bucket(Bucket<K, V>*& bucket, int N, int B, int B_prime){
    Bucket<K, V>* Bhelper = new Bucket<K, V>(bucket->max_collisions);
    Bucket<K, V>* B_prime_helper = new Bucket<K, V>(bucket->max_collisions);

    //insertar los elementos de this en Bhelper o B_prime_helper
    for (auto it = bucket->begin(); it != bucket->end(); ++it){
        for (auto it2 = it->list->begin(); it2 != it->list->end(); ++it2){
            int index = hash_function((*it2).key, N*2);
            if (index == B_prime){
                B_prime_helper->insert((*it2).key, (*it2).value);
            }
            else{
                Bhelper->insert((*it2).key, (*it2).value);
            }
        }
    }

    delete bucket;
    bucket = nullptr;
    bucket = Bhelper;

    return B_prime_helper;
}
#endif // BUCKET_H