#include "NonComparisonSorts.h"
#include <iostream>
#include <cmath>
#include <algorithm>

// ---------------------------------------------------------------------------
// Counting Sort
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: cpp_diagrams.md #1 -- Steps 1a, 1b, 1c (Count Phase)
// ? SEE DIAGRAM: cpp_diagrams.md #2 -- Step 2 (Placement Phase)
//
void counting_sort(std::vector<int>& data) {
    // TODO: Implement counting sort
    //   1. Find the min and max values
    //   2. Create a count array of size (max - min + 1)
    //   3. Count occurrences of each value
    //   4. Overwrite data with sorted values using
	if (data.size() <= 1) return; // Already sorted
	int min_val = *std::min_element(data.begin(), data.end());
	int max_val = *std::max_element(data.begin(), data.end());
	int k = max_val - min_val + 1;
	std::vector<int> count(k, 0);
    for (int num : data) {
        count[num - min_val]++;
	}

	int inx = 0;
    for (int i = 0; i < k; ++i) {
        while (count[i] > 0) {
            data[inx++] = i + min_val;
            count[i]--;
        }
    }


}

// ---------------------------------------------------------------------------
// Bucket Sort
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: cpp_diagrams.md #3 -- Steps 1a, 1b (Distribution Phase)
// ? SEE DIAGRAM: cpp_diagrams.md #4 -- Steps 2-3 (Sort + Concatenate)
//
void bucket_sort(std::vector<int>& data, int num_buckets) {
    // TODO: Implement bucket sort
    //   1. Find the min and max values to determine bucket ranges
    //   2. Create num_buckets empty buckets (vectors)
    //   3. Distribute each element into its bucket
    //   4. Sort each bucket (use insertion sort or std::sort)
    //   5. Concatenate all buckets back into data
	if (data.size() <= 1) return; // Already sorted
	int min_val = *std::min_element(data.begin(), data.end());
	int max_val = *std::max_element(data.begin(), data.end());

    if (min_val == max_val) return;
	int range = max_val - min_val + 1;
	int range_per_bucket = static_cast<int>(std::ceil(static_cast<double>(range) / num_buckets));

	std::vector<std::vector<int>> buckets(num_buckets);
    for (int num : data) {
        int bucket_idx = (num - min_val) / range_per_bucket;
        if (bucket_idx >= num_buckets) bucket_idx = num_buckets - 1; // Handle edge case for max_val
        buckets[bucket_idx].push_back(num);
	}
	int inx = 0;
    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());
        for (int num : bucket) {
            data[inx++] = num;
        }
	}

}

// ---------------------------------------------------------------------------
// Radix Sort (LSD)
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: cpp_diagrams.md #5 -- Step 0 + Pass 1 Detail
// ? SEE DIAGRAM: cpp_diagrams.md #6 -- Passes 2-3 (Stability in Action)
//
static void counting_sort_by_digits(std::vector<int>& data, int exp) {
    int n = static_cast<int>(data.size());

    std::vector<int> output(n); // output array
    int count[10] = { 0 }; // count array for digits 0-9

    for (int i = 0; i < n; i++) {
        int digit = (data[i] / exp) % 10;
        count[digit]++;
    }
    // Update count[i] to contain the actual position of this digit in output[]
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }
    // Build the output array
    for (int i = n - 1; i >= 0; --i) {
        int digit = (data[i] / exp) % 10;
        output[count[digit] - 1] = data[i];
        count[digit]--;
    }
    data = output; // Copy the output array back to data
    // Copy the output array back to data
    for (int i = 0; i < n; ++i) {
        data[i] = output[i];
    }
}
void radix_sort(std::vector<int>& data) {
    // TODO: Implement radix sort (LSD)
    //   1. Find the maximum value to determine the number of digits
    //   2. For each digit position (ones, tens, hundreds, ...):
    //      a. Use counting sort on that digit
    //   3. After all digit passes, data is sorted
	if (data.size() <= 1) return; // Already sorted
	int max_val = *std::max_element(data.begin(), data.end());
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        counting_sort_by_digits(data, exp);
	}

}

// ---------------------------------------------------------------------------
// Utility
// ---------------------------------------------------------------------------
void print_vector(const std::vector<int>& data, const std::string& label) {
    if (!label.empty()) std::cout << label << ": ";
    std::cout << "[";
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i];
        if (i + 1 < data.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

