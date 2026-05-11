#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <ctime>


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
    int capacity;
    Entry* table;

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

int randomLength(){
    return rand() % 101;
}

std::string randomString() {
    int len = randomLength();
    const char alfabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string result = "";
    result.reserve(len);

    for(int i = 0; i < len; ++i) {
        result += alfabet[rand() % (sizeof(alfabet) - 1)];
    }
    return result;
}

void test(){
    srand(time(NULL));
    long long SIMPLE_INS_TIME = 0, SIMPLE_REM_TIME = 0;

    for(int capacity = 1000; capacity <= 1000000; capacity *= 10){
        HashTable<simpleHash> ht1(capacity);

        std::cout<<"--- | N = "<<capacity<<" | SIMPLE HASH | LOAD = 70% | ---"<<std::endl;

        // filling 70% of the table
        std::vector<std::string> values;
        values.reserve(0.7 * capacity);

        for(int i=0; i < 0.7*capacity; ++i) {
            values.push_back(randomString());
        }

        std::cout<<"Insert measure in progress..."<<std::endl;
        // insert() time measure
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < values.size(); ++i){
            ht1.insert(values[i]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double avg_ins = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / static_cast<double>(values.size());
        std::cout<<"Avarage time INSERT operation (ns):  "<<avg_ins<<std::endl;

        std::cout<<"Remove measure in progress..."<<std::endl;
        // remove() time measure 
        auto startR = std::chrono::high_resolution_clock::now();
        for(int i = 0; i <= values.size(); ++i){
            ht1.remove(values[i]);
        }
        auto endR = std::chrono::high_resolution_clock::now();
        double avg_rem = std::chrono::duration_cast<std::chrono::nanoseconds>(endR - startR).count() / static_cast<double>(values.size());
        std::cout<<"Avarage time REMOVE operation (ns):  "<<avg_rem<<std::endl;

    }
}


int main(){
    return 0;
}