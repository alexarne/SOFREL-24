#pragma once
#include <vector>

// (i), Insertion sort
std::vector<int> sort(const std::vector<int>& A) {
    std::vector<int> sorted(A);
    for (int i = 1; i < sorted.size(); ++i) {
        for (int j = i-1; j >= 0; --j) {
            if (sorted[j] > sorted[j+1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            } else {
                break;
            }
        }
    }
    return sorted;
}


// (ii)
bool membership_sorted(const std::vector<int>& A, int key) {
    int lo = 0, hi = A.size()-1;
    while (lo <= hi) {
        int mid = (lo+hi) / 2;
        if (A[mid] == key) {
            return true;
        } else if (A[mid] > key) {
            hi = mid-1;
        } else {
            lo = mid+1;
        }
    }
    return false;
}

// (iii)
bool membership_unsorted(const std::vector<int>& A, int key) {
    std::vector<int> sorted = sort(A);
    bool res = membership_sorted(sorted, key);
    return res;
}