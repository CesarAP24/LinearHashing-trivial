#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <iostream>
#include <string>


template <typename T>
struct Node{
    T data;
    Node<T>* next;
    Node(T data){
        this->data = data;
        this->next = nullptr;
    }

    ~Node(){
        if(this->next != nullptr){
            delete this->next;
        }
    }
};


template <typename T>
struct ForwardList{
    Node<T>* head;
    Node<T>* tail;
    int count;

    struct fl_iterator{
        Node<T>* current;

        fl_iterator(const fl_iterator& other){
            this->current = other.current;
        }

        fl_iterator& operator=(const fl_iterator& other){
            this->current = other.current;
            return *this;
        }

        fl_iterator(){
            this->current = nullptr;
        }

        fl_iterator(Node<T>* current){
            this->current = current;
        }

        fl_iterator& operator++(){
            this->current = this->current->next;
            return *this;
        }

        bool operator!=(const fl_iterator& other){
            return this->current != other.current;
        }

        bool operator==(const fl_iterator& other){
            return this->current == other.current;
        }

        Node<T>* operator->(){
            return this->current;
        }

        T& operator*(){
            return this->current->data;
        }

        friend std::ostream& operator<<(std::ostream& os, const fl_iterator& it){
            os << it.current;
            return os;
        }
    };

    ForwardList(){
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }

    ForwardList(T data){
        this->head = new Node<T>(data);
        this->tail = this->head;
        this->count = 1;
    }

    void push_back(T data){
        Node<T>* new_node = new Node<T>(data);
        if(this->head == nullptr){
            this->head = new_node;
            this->tail = new_node;
        }else{
            this->tail->next = new_node;
            this->tail = new_node;
        }
        this->count++;
    }

    void erase(fl_iterator& it){
        if(it.current == this->head){
            this->head = this->head->next;
            it.current->next = nullptr;
            delete it.current;
            it.current = this->head;
        }else{
            Node<T>* current = this->head;
            while(current->next != it.current){
                current = current->next;
            }
            current->next = it.current->next;
            it.current->next = nullptr;
            delete it.current;
            it.current = current->next;
        }
        this->count--;
    }

    void print(){
        if(this->head == nullptr){
            std::cout << "[]" << std::endl;
        }else{
            std::cout << "[";
            Node<T>* current = this->head;
            while(current->next != nullptr){
                std::cout << current->data << ", ";
                current = current->next;
            }
            std::cout << current->data << "]" << std::endl;
        }
    }

    void clear(){
        if(this->head != nullptr){
            delete this->head;
        }
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }

    bool search(T data){
        Node<T>* current = this->head;
        while(current != nullptr){
            if(current->data == data){
                return true;
            }
            current = current->next;
        }
        return false;
    }

    //cout

    friend std::ostream& operator<<(std::ostream& os, const ForwardList<T>& list){
        if(list.head == nullptr){
            os << "[]" << std::endl;
        }else{
            os << "[";
            Node<T>* current = list.head;
            while(current->next != nullptr){
                os << current->data << ", ";
                current = current->next;
            }
            os << current->data << "]";
        }
        return os;
    }

    ~ForwardList(){
        if(this->head != nullptr){
            delete this->head;
        }
    }


    //begin

    fl_iterator begin(){
        return fl_iterator(this->head);
    }

    //end

    fl_iterator end(){
        return nullptr;
    }

    void push_front(T data){
        Node<T>* new_node = new Node<T>(data);
        if(this->head == nullptr){
            this->head = new_node;
            this->tail = new_node;
        }else{
            new_node->next = this->head;
            this->head = new_node;
        }
        this->count++;
    }


};
#endif // FORWARD_LIST_H