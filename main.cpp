#include <iostream>
#include <string>

constexpr int TABLE_SIZE = 10;

struct Entry{
    std::string value;
};

struct HashTable{
    int size;
    Entry* table[TABLE_SIZE];
};

// ===================

unsigned int hashFunction1(std::string value){
    unsigned int hash_value = 0;
    for(int i=0; i<value.length(); ++i){
        hash_value += value[i];
        hash_value *= value[i] - i;
    }
    return hash_value % TABLE_SIZE;
}

template <typename HashFunction>
int hash(std::string value, HashFunction H){
    // TODO
    return 0;
}


int main(){
    std::string s = "Jablko";
    std::cout<<s<<" --> "<<hashFunction1(s);
}