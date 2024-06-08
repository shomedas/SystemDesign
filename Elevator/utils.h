#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <set>
#include "enums.h"

int findMaxLowerValue(const std::vector<int>& vec, int givenValue);
int findMinHigherValue(const std::vector<int>& vec, int givenValue);

void removeIfExists(std::vector<int>& vec, int value);
void removePairFromVector(std::vector<std::pair<int, DIR> >& vec,
                          const std::pair <int, DIR> & pairToRemove);

bool pair_exists_in_vector(std::vector<std::pair<int, DIR> >vec,
                                    const std::pair <int, DIR> pairToDetect);

void removeDuplicate_ER(std::vector<std::pair<int, DIR> >& vec);
void removeDuplicates_IR(std::vector<int>& vec);

std::pair<int, int> findMinMax_vec(const std::vector<int>& vec);
std::pair<int, int> findMinMax_vec_first_element(const std::vector<std::pair<int, DIR>>& pair_vec);

#endif // UTILS_H
