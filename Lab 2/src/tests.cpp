#include <iostream>
#include <fstream>
#include "implementations.hpp"

const int NUM_CASES = 20;
const bool STOP_ON_FAILURE = false;
const int MAXIMUM_ARRAY_SIZE = 10000;
const int DEFAULT_VALUE = 0;

bool oracle(const std::vector<int>& A, int key) {
    for (int elem : A) {
        if (elem == key) return true;
    }
    return false;
}

bool evaluate(const std::vector<int>& A, int key) {
    if (membership_unsorted(A, key) == oracle(A, key)) {
        printf(".");
        std::cout << std::flush;
        return true;
    } else {
        printf("FAILURE");
        std::cout << std::flush;
        return false;
    }
}

std::ofstream create_file(std::string name) {
    return std::ofstream(name);
}

void append_to_file(std::ofstream& file, const std::vector<int>& A, int key) {
    file << key << " " << A.size();
    for (int elem : A) file << " " << elem;
    file << "\n";
}

void test_random() {
    printf("Testing random test cases...\n");
    std::ofstream file = create_file("random_tests.txt");
    for (int i = 0; i < NUM_CASES; ++i) {
        int size = rand() % MAXIMUM_ARRAY_SIZE;
        std::vector<int> A(size);
        for (int& elem : A) elem = rand();
        int key = rand();
        append_to_file(file, A, key);
        if (!evaluate(A, key) && STOP_ON_FAILURE) break;
    }
    file.close();
    printf("\n");
}

void test_pairwise() {
    printf("Testing pairwise test cases...\n");
    std::ofstream file = create_file("pairwise_tests.txt");
    
    printf("\n");
}

int main(void) {
    srand(time(NULL)); 
    test_random();
    test_pairwise();
}