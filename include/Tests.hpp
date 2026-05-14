#pragma once 
#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <cstdlib>
#include "HashTable.hpp"
#include "HashingFunctions.hpp"

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

// ======= TEST FUNCTION =======
template <typename HashFunc>
void testHashFunction(std::string hashAlgorithm) {
    
    std::vector<double> fill_percentage = {0.99};
    
    for(float f : fill_percentage){
        for(int capacity = 1000000; capacity <= 100000000; capacity *= 10){
            HashTable<HashFunc> ht(capacity);

            std::cout << "\n--- | N = " << capacity << " | FILL = " << f << " | " << hashAlgorithm << " | ---" << std::endl;

            // filling the table
            std::vector<std::string> values;
            values.reserve(f * capacity);

            for(int i = 0; i < f * capacity; ++i) {
                values.push_back(randomString());
            }

            
            // insert() time measure
            auto start = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < values.size(); ++i){
                ht.insert(values[i]);
            }
            auto end = std::chrono::high_resolution_clock::now();
            double avg_ins = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / static_cast<double>(values.size());
            std::cout << "Average time INSERT operation (ns):  " << avg_ins << std::endl;
            

            // remove() time measure 
            auto startR = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < values.size(); ++i){
                ht.remove(values[i]);
            }
            auto endR = std::chrono::high_resolution_clock::now();
            double avg_rem = std::chrono::duration_cast<std::chrono::nanoseconds>(endR - startR).count() / static_cast<double>(values.size());
            std::cout << "Average time REMOVE operation (ns):  " << avg_rem << std::endl;
        }
    }
}

void test(){
    //testHashFunction<stupidHash>("STUPID HASH");
    //testHashFunction<simpleHash>("SIMPLE HASH");
    testHashFunction<seedHash>("DJB2 HASH");
    testHashFunction<polynomialHash>("POLYNOMIAL ROLL HASH");
}