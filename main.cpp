#include <iostream>
#include <string>

constexpr int TABLE_CAPACITY = 10;

// ===== HASHING FUNCTIONS =====
unsigned int hashFunction1(std::string value){
    unsigned int hash_value = 0;
    for(int i=0; i<value.length(); ++i){
        hash_value += value[i];
        hash_value *= value[i] - i;
    }
    return hash_value % TABLE_CAPACITY;
}

// szablon ponieważ będą 3 różne funkcje haszowania
template <typename HashFunction>
unsigned int hash(std::string value, HashFunction H){
    // TODO
    return 0;
}

// ======== STRUCTS ========
struct Entry{
    std::string value;
    Entry* next;

    Entry(std::string s){
        value = s;
        next = nullptr;
    }
};

struct HashTable{
    int size;
    Entry* table[TABLE_CAPACITY];

    HashTable() {
        size = 0;
        for(int i=0; i < TABLE_CAPACITY; ++i){
            table[i] = nullptr;
        }
    }

    void insert(std::string s){
        unsigned int index = hash(s, hashFunction1);
        Entry* new_entry = new Entry(s);
        
        new_entry->next = table[index];
        table[index] = new_entry;
    }

    void remove(std::string s){

    }

};

int main(){
    return 0;
}