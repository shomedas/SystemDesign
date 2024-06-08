#include "utils.h"
//#include <vector>
#include <utility>
#include <algorithm>
#include <climits>    // Required for INT_MAX
#include <stdexcept>

int findMaxLowerValue(const std::vector<int>& vec, int givenValue) {
    int maxLowerValue = -1; // Assuming all vector elements are positive

    // Iterate over the sorted vector to find the highest value less than givenValue
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] < givenValue) {
            maxLowerValue = vec[i]; // Update maxLowerValue
        } else {
            break; // Stop loop when current element >= givenValue
        }
    }
    return maxLowerValue;
}

// Function to find the lowest value in a vector that is higher than a given value
int findMinHigherValue(const std::vector<int>& vec, int givenValue) {
    int minHigherValue = INT_MAX; // Initialize to a large value (assuming all vector elements are positive)

    // Iterate over the vector to find the lowest value greater than givenValue
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] > givenValue && vec[i] < minHigherValue) {
            minHigherValue = vec[i]; // Update minHigherValue
        }
    }

    return minHigherValue;
}

void removeIfExists(std::vector<int>& vec, int value) {
    // Find the element in the vector
    std::vector<int>::iterator it = std::find(vec.begin(), vec.end(), value);

    // If element is found, erase it from the vector
    if (it != vec.end()) {
        vec.erase(it);
    }
}

// Define a pair type for convenience
typedef std::pair<int, DIR> IntDirPair;


// Function to remove a specific pair from the vector
//void removePairFromVector(std::vector<IntDirPair>& vec, const IntDirPair& pairToRemove)
void removePairFromVector(std::vector<std::pair<int, DIR> >& vec,
                          const std::pair <int, DIR> & pairToRemove)
{
    // Use std::find to locate the pair in the vector
    std::vector<IntDirPair>::iterator it = std::find(vec.begin(), vec.end(), pairToRemove);

    // Check if the pair was found
    if (it != vec.end()) {
        // If found, erase the pair from the vector
        vec.erase(it);
    }
}

bool pair_exists_in_vector(std::vector<std::pair<int, DIR> > vec,
                                    const std::pair <int, DIR> pairToDetect)
{
    // Use std::find to locate the pair in the vector
    std::vector<IntDirPair>::iterator it = std::find(vec.begin(), vec.end(), pairToDetect);

    // Check if the pair was found
    if (it != vec.end()) {
        // If found, return true
        return true;
    }
    else
    {
        return false;
    }
}

void removeDuplicate_ER(std::vector<std::pair<int, DIR>>& vec) {
    std::set<std::pair<int, DIR>> uniquePairs;

    // Insert all pairs into a set to filter duplicates
    for (const auto& pair : vec) {
        uniquePairs.insert(pair);
    }

    // Clear the original vector and insert unique pairs back
    vec.clear();
    vec.insert(vec.end(), uniquePairs.begin(), uniquePairs.end());
}

void removeDuplicate_IR(std::vector<int>& vec) {
    // Sort the vector
    std::sort(vec.begin(), vec.end());

    // Use std::unique to remove consecutive duplicates
    auto it = std::unique(vec.begin(), vec.end());

    // Erase the elements from it to end
    vec.erase(it, vec.end());
}

std::pair<int, int> findMinMax_vec(const std::vector<int>& vec) {
    if (vec.empty()) {
        throw std::runtime_error("The vector is empty.");
    }

    auto min_max = std::minmax_element(vec.begin(), vec.end());
    return { *min_max.first, *min_max.second };
}


std::pair<int, int> findMinMax_vec_first_element(const std::vector<std::pair<int, DIR>>& pair_vec) {
    if (pair_vec.empty()) {
        throw std::runtime_error("The vector is empty.");
    }

    int min_value = std::numeric_limits<int>::max();
    int max_value = std::numeric_limits<int>::min();

    for (size_t i = 0; i < pair_vec.size(); ++i) {
        if (pair_vec[i].first < min_value) {
            min_value = pair_vec[i].first;
        }
        if (pair_vec[i].first > max_value) {
            max_value = pair_vec[i].first;
        }
    }

    return std::make_pair(min_value, max_value);
}
