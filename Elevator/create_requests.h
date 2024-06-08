#ifndef REQUESTS_H
#define REQUESTS_H

#include <vector>
#include "enums.h"

///////////// CAPTURE user requests in IR and ER

// function to capture external_requests from user
std::vector<std::pair<int, DIR> > get_ER();

// function to capture internal_requests from user
std::vector<int> get_IR();

///////////// DELETE PROCESSED requests in IR and ER

// function to delete an external_requests once serviced
void delete_ER(std::vector<std::pair<int, DIR> > & ER, std::pair<int, DIR> request);

// function to delete an internal_requests once serviced
void delete_IR(std::vector<int> & IR, int idx);

void merge_and_remove_duplicate_IR(std::vector<int>& existing_IR,
                                   const std::vector<int>& new_IR);

void merge_and_remove_duplicate_ER(std::vector<std::pair<int, DIR>>& existing_ER,
                                   const std::vector<std::pair<int, DIR>>& new_ER);

void display_pending_IR(std::vector<int>& existing_IR);
void display_pending_ER(std::vector<std::pair<int, DIR>>& existing_ER);

#endif
