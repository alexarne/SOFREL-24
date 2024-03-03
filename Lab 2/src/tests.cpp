#include <iostream>
#include <fstream>
#include "implementations.hpp"
#include <functional>

const int NUM_CASES = 200;
const bool STOP_ON_FAILURE = true;
const int MAXIMUM_ARRAY_SIZE = 100;     // Maximum array size in random testing

const int ARRAY_SIZE = 20;              // The array size in pairwise testing
const int DEFAULT_VALUE = 0;            // Default values for pairwise testing
const int N = 2;                        // The N in N-wise testing

const std::vector<int> VALUES({1, 2, 3, 4, 5});     // Possible values 
int random_value() {
    return VALUES[rand() % VALUES.size()];
}

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
        printf("X");
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
    int counter = 0;
    printf("Testing random test cases...\n");
    std::ofstream file = create_file("random_tests.txt");
    for (int i = 0; i < NUM_CASES; ++i) {
        int size = rand() % MAXIMUM_ARRAY_SIZE;
        std::vector<int> A(size);
        for (int& elem : A) elem = random_value();
        int key = random_value();
        append_to_file(file, A, key);
        ++counter;
        if (!evaluate(A, key) && STOP_ON_FAILURE) break;
    }
    file.close();
    printf("\nExecuted %i tests\n\n", counter);
}

std::vector<int> parameters(ARRAY_SIZE+1, DEFAULT_VALUE);

void test_pairwise() {
    int counter = 0;
    printf("Testing pairwise test cases...\n");
    std::ofstream file = create_file("pairwise_tests.txt");
    std::function<void(int, int)> permutate;
    bool keep_testing = true;
    permutate = [&](int index, int remaining_assignments) {
        // If at end, write to file
        if (index >= parameters.size()) {
            std::vector<int> A(parameters.begin()+1, parameters.end());
            int key = parameters[0];
            ++counter;
            if (!evaluate(A, key) && STOP_ON_FAILURE) keep_testing = false;
            append_to_file(file, A, key);
            return;
        }

        // Do not toggle parameter and continue
        permutate(index+1, remaining_assignments);
        if (!keep_testing) return;

        // Toggle parameter and continue (if possible)
        if (remaining_assignments > 0) {
            parameters[index] = VALUES[rand() % VALUES.size()];
            permutate(index+1, remaining_assignments-1);
        }

        // Revert
        parameters[index] = DEFAULT_VALUE;
    };
    permutate(0, N);
    printf("\nExecuted %i tests\n\n", counter);
}

int main(void) {
    srand(time(NULL)); 
    test_random();
    test_pairwise();
}