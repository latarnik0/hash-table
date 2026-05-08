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

unsigned int hashFunction2(std::string value){
    unsigned int hash_value = 0;
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
        unsigned int index = hash(s, hashFunction1);

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

int main(){
    return 0;
}