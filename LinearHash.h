#include "bucket.h"
#include <string>
#include <iostream>

template <typename K, typename V>
class LinearHash{
    private:
        int N; //initial size
        Bucket<K, V>** table;
        int sp; //split pointer
        int size; //number of buckets
        int capacity; //capacity of the table
        int max_collisions = 0;
    public:
        LinearHash(int N, int max_collisions): N(N), max_collisions(max_collisions){
            this->table = new Bucket<K, V>*[N*2];
            this->sp = 0;
            this->size = N;
            this->capacity = N*2;
            for (int i = 0; i < N; i++){
                this->table[i] = new Bucket<K, V>(max_collisions);
            }
        }

        ~LinearHash(){
            delete[] this->table;
        }

        void put(K key, V value){
            int index = hash_function(key, this->N);
            if (index < this->sp){
                index = hash_function(key, this->N*2);
            }

            this->table[index]->insert(key, value);

            if (this->table[index]->overflowed){
                this->split();
            }
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
            int B = this->sp;
            int B_prime = B + this->N;

            if (B_prime >= this->capacity){
                this->rezise();
            }

            this->table[B_prime] = split_bucket(this->table[B], this->N, B, B_prime);
            size++;

            if (this->sp == N-1){
                this->sp = 0;
                this->N *= 2;
            } else {
                this->sp++;
            }
        }

        void rezise(){
            int new_capacity = this->capacity * 2;
            Bucket<K, V>** new_table = new Bucket<K, V>*[new_capacity];

            for (int i = 0; i < this->capacity; i++){
                new_table[i] = this->table[i];
            }

            delete[] this->table;
            this->table = new_table;
            this->capacity = new_capacity;
        }

        std::string toString(){
            string result = "";
            for (int i = 0; i < this->size; i++){
                result += to_string(i) + ": " + this->table[i]->toString() + "\n";
            }
            return result;
        }

        void print(){
            cout << this->toString() << endl;
        }
};