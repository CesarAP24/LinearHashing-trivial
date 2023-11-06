#include "bucket.h"
#include <string>
#include <iostream>
#include "hash_function.h"

template <typename K, typename V>
class LinearHash{
    private:
        int N; //initial size
        bucket<K, V>* table;
        int sp; //split pointer
        int size; //number of buckets
        int capacity; //capacity of the table
        int max_collisions = 0;
    public:
        LinearHash(int N, int max_collisions): N(N), max_collisions(max_collisions){
            this->table = new bucket<K, V>[N];
            this->sp = 0;
            this->size = 0; 
            this->capacity = N*2;
        }

        ~LinearHash(){
            delete[] this->table;
        }

        void put(K key, V value){
            //TO DO
        }

        void erase(K key){
            //TO DO
        }

        bool search(K key){
            //TO DO
            return false;
        }

        V get(K key){
            //TO DO
            return V();
        }

        void split(){
            //TO DO
        }

        std::string toString(){
            //TO DO
            return "";
        }

        void print(){
            //TO DO
        }
};