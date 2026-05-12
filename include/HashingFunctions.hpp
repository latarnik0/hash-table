#pragma once
#include <string>

// ======= HASHING FUNCTIONS =======
// --- hashing function to test worst case ---
struct stupidHash {
    unsigned int operator()(std::string value){
        return 0;
    }
};

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