#pragma once
#include <string>
#include <iostream>

// ======= HASH TABLE =======
// --- single record ---
struct Entry{
    std::string value;
    Entry* next;

    Entry(std::string s){
        value = s;
        next = nullptr;
    }
};

// --- main Hash Table ---
template <typename HashFunction>
struct HashTable{
    int size;
    int capacity;
    Entry** table;

    HashTable(int new_capacity) {
        size = 0;
        capacity = new_capacity;

        table = new Entry*[capacity];

        for(int i=0; i < capacity; ++i){
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < capacity; ++i) {
            Entry* current = table[i];
            while (current != nullptr) {
                Entry* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table; 
    }

    void insert(std::string s){
        HashFunction hash;
        unsigned int index = hash(s) % capacity;
        Entry* new_entry = new Entry(s);
        
        new_entry->next = table[index];
        table[index] = new_entry;
    }

    void remove(std::string s){
        HashFunction hash;
        unsigned int index = hash(s) % capacity;

        if(table[index] == nullptr){
            std::cout<<"No such element"<<std::endl;
            return;
        }

        if(table[index]->value == s){
            Entry* temp = table[index];
            table[index] = table[index]->next;
            delete temp;
            size--;
            return;
        }

        Entry* prev = nullptr;
        Entry* current = table[index];

        while(current != nullptr){
            if(current->value == s){
                prev->next = current->next;
                delete current;
                size--;
                break;
            } else {
                prev = current;
                current = current->next;
            }
        }
        return;
    }
};