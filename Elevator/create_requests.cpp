#include <iostream>
//#include <vector>
#include <random>
#include <unordered_set>
#include <set>
#include <utility> // for std::pair
#include <string> // for std::string
#include <algorithm>

#include "enums.h"
#include "utils.h"

////////////////// CAPTURE EXTERNAL REQUESTS FROM USER interactively////////////////

// Function to convert string to DIR enum
DIR stringToDir(const std::string& str) {
    if (str == "UP") {
        return UP;
    } else if (str == "DOWN") {
        return DOWN;
    } else {
        throw std::invalid_argument("Invalid direction");
    }
}

// Function to interactively populate vector of pairs
std::vector<std::pair<int, DIR>> get_ER() {
    std::vector<std::pair<int, DIR>> pairs;
    bool done = false;

    while (!done) {
        // Prompt for integer value
        std::cout << "Enter ER (floor value with direction) (or -1 to finish): ";
        int value;
        std::cin >> value;

        if (value == -1) {
            done = true;
        } else {
            // Prompt for direction
            std::cout << "Enter direction (UP/DOWN): ";
            std::string directionStr;
            std::cin >> directionStr;

            try {
                DIR direction = stringToDir(directionStr);
                pairs.push_back(std::pair<int, DIR>(value, direction));
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid direction. Please enter UP or DOWN." << std::endl;
            }
        }
    }

    return pairs;
}

///////////////////// Function to capture internal_requests from user interactively

// Function to interactively populate a vector of integers
std::vector<int> get_IR() {
    std::vector<int> integers;
    bool done = false;

    std::cout << "Enter IR (floor values) (enter -1 to finish):" << std::endl;

    while (!done) {
        int value;
        std::cin >> value;

        if (value == -1) {
            done = true;
        } else {
            integers.push_back(value);
        }
    }

    return integers;
}

void merge_and_remove_duplicate_IR(std::vector<int>& existing_IR,
                                   const std::vector<int>& new_IR) {
    // Add new requests to the existing requests
    existing_IR.insert(existing_IR.end(), new_IR.begin(), new_IR.end());

    // Sort the combined vector
    std::sort(existing_IR.begin(), existing_IR.end());

    // Remove duplicates
    auto last = std::unique(existing_IR.begin(), existing_IR.end());

    // Resize the vector to remove the undefined values left by std::unique
    existing_IR.erase(last, existing_IR.end());
}

// Custom comparator for std::pair<int, DIR>
bool compare_pairs(const std::pair<int, DIR>& a, const std::pair<int, DIR>& b) {
    return a.first < b.first || (a.first == b.first && a.second < b.second);
}

void merge_and_remove_duplicate_ER(std::vector<std::pair<int, DIR>>& existing_ER,
                                   const std::vector<std::pair<int, DIR>>& new_ER) {
    // Add new requests to the existing requests
    existing_ER.insert(existing_ER.end(), new_ER.begin(), new_ER.end());

    // Sort the combined vector using custom comparator
    std::sort(existing_ER.begin(), existing_ER.end(), compare_pairs);

    // Remove duplicates
    auto last = std::unique(existing_ER.begin(), existing_ER.end());

    // Resize the vector to remove the undefined values left by std::unique
    existing_ER.erase(last, existing_ER.end());
}

void display_pending_IR(std::vector<int>& existing_IR){
    std::cout << "PENDING IR" << std::endl;
    if (existing_IR.size()==0)
    {
        std::cout << " None"<< std::endl;
        return;
    }
    for (int i=0;i<existing_IR.size();i++)
    {
        std::cout << existing_IR[i] << std::endl;
    }
}

void display_pending_ER(std::vector<std::pair<int, DIR>>& existing_ER){

    std::cout << "PENDING ER" << std::endl;
    if (existing_ER.size()==0)
    {
        std::cout << " None"<< std::endl;
        return;
    }
    for (int i=0;i<existing_ER.size();i++)
    {
        std::cout << existing_ER[i].first << "," << existing_ER[i].second<< std::endl;
    }
}
