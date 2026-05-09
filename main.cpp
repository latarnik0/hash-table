#include <iostream>
#include <string>

constexpr int TABLE_CAPACITY = 10;

// ======= HASH TABLE =======
// --- single node ---
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
    Entry* table[TABLE_CAPACITY];

    HashTable() {
        size = 0;
        for(int i=0; i < TABLE_CAPACITY; ++i){
            table[i] = nullptr;
        }
    }

    void insert(std::string s){
        HashFunction hash;
        unsigned int index = hash(s) % TABLE_CAPACITY;
        Entry* new_entry = new Entry(s);
        
        new_entry->next = table[index];
        table[index] = new_entry;
    }

    void remove(std::string s){
        HashFunction hash;
        unsigned int index = hash(s) % TABLE_CAPACITY;

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

// ======= HASHING FUNCTIONS =======
// --- simple custom hashing function ---
struct simpleHash {
    unsigned int operator()(std::string value){
        unsigned int hash_value = 0;
        for(int i=0; i<value.length(); ++i){
            hash_value += value[i];
            hash_value *= value[i] - i;
        }
        return hash_value;
    }
};

// --- seed-based hashing function (djb2 algorithm) ---
struct seedHash {
    unsigned int operator()(std::string value){
        unsigned int hash_value = 5381; // seed
        for(char c : value){
            hash_value = ((hash_value << 5) + hash_value) + c;
        }
        return hash_value;
    }
};

// --- polynomial rolling hash ---
struct polynomialHash {
    unsigned int operator()(std::string &s){
        unsigned int n = s.length();
        unsigned int p = 31, m = 1e9 + 7;
        unsigned int hash_value = 0;
        unsigned int pPow = 1;

        for(int i = 0; i < n; ++i){
            hash_value = (hash_value + (s[i] - 'a' + 1) * pPow) % m;
            pPow = (pPow * p) % m;
        }
        return hash_value;
    }
};



int main(){
    // HashTable<simpleHash> ht1;
    // HashTable<seedHash> ht2;
    // HashTable<polynomialHash> ht3;
    return 0;
}