#include <iostream>
#include <cstdlib> // For std::atoi
#include "create_requests.h"
//#include "enums.h"
#include "utils.h"
#include "elevator_DLL.h"

// Node constructor
Node::Node(int floor, bool up, bool down) : floor_index(floor), stop_up(up), stop_down(down), prev(nullptr), next(nullptr) {}

// DoublyLinkedList constructor
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

/// A function to set the value of stop_up and stop_dn using indices
// the index should be wrt head

// Function to set the floor index of a node specified by its index
// and direction in which it should stop
void DoublyLinkedList::set_stop_up_down_using_index_direction(int index, DIR direction) {
    //if (index < 1) {
    //    throw std::invalid_argument("Index should be greater than or equal to 1.");
    //}

    Node* current = head;
    int currentIndex = 0;

    while (current != nullptr) {
        if (currentIndex == index) {
            if (direction==UP)
            {
                current->stop_up = true;
            }
            if (direction==DOWN)
            {
                current->stop_down = true;
            }
            return;
        }
        current = current->next;
        currentIndex++;
    }
    throw std::out_of_range("Index is out of range.");
}


void DoublyLinkedList::set_up_down_stops_ER(std::vector<std::pair<int, DIR>> ER)
{
    for (int i=0;i<ER.size();i++)
    {
        int ER_floor_index=ER[i].first;

        // detect the index of the floor within the DLL
        // the index should be wrt head
        int idx_wrt_head = head->floor_index - ER_floor_index;

        // use the index to set the stop up/down within the DLL
        DIR ER_DIR = ER[i].second;

        set_stop_up_down_using_index_direction(idx_wrt_head, ER_DIR);
    }
}

void DoublyLinkedList::set_up_down_stops_IR(std::vector<int> IR, Node * current_node, DIR direction)
{
    for (int i=0;i<IR.size();i++)
    {
        int IR_floor_index=IR[i];

        // detect the index of the floor within the DLL
        // the index should be wrt head
        int idx_wrt_head = head->floor_index - IR_floor_index;

        DIR IR_DIR;
        // determine direction using current floor and direction of lifts travel
        if (current_node->floor_index < IR_floor_index)
        {
            IR_DIR = UP;
        }
        if (current_node->floor_index > IR_floor_index)
        {
            IR_DIR = DOWN;
        }

        set_stop_up_down_using_index_direction(idx_wrt_head, IR_DIR);
    }
}

void DoublyLinkedList::extend_DLL(std::pair<int,int> min_max_request)
{
    // find the topmost and bottom most floor
    int lowest_floor_requested = min_max_request.first;

    int highest_floor_requested = min_max_request.second;

    int DLL_highest_floor = head->floor_index;
    int DLL_lowest_floor = tail->floor_index;

    if (highest_floor_requested > DLL_highest_floor)
    {
    // add nodes on above of current top(head) node
        for (int i=DLL_highest_floor+1;i<=highest_floor_requested;i++)
        {
            // add a new node
            insertAtHead(i);
        }
    }

    if (lowest_floor_requested < DLL_lowest_floor)
    {
        // add nodes below current bottom(tail) node
        for (int i=DLL_lowest_floor-1;i>=lowest_floor_requested;i--)
        {
            // add new node
            insertAtTail(i);
        }
    }
}

/// add nodes based on IR //////
/// Add new head, tail, and intermediate floors based on requests and elevator movement direction
void DoublyLinkedList::add_new_head_tail_intermediate_floors_IR(std::vector<int> IR)
{
    if (IR.size()==0)
    {
        return;
    }

    // find the topmost and bottom most floor in IR
    std::pair<int, int> min_max_IR = findMinMax_vec(IR);

    extend_DLL(min_max_IR);
}

/// add nodes based on IR //////
/// Add new head, tail, and intermediate floors based on requests and elevator movement direction
void DoublyLinkedList::add_new_head_tail_intermediate_floors_ER(std::vector<std::pair<int, DIR> > ER)
{
    if (ER.size()==0)
    {
        return;
    }

    std::pair<int, int> min_max_ER = findMinMax_vec_first_element(ER);

    extend_DLL(min_max_ER);
}

/*
void DoublyLinkedList::delete_current_node_if_head_or_tail(Node * current_node)
{
    /// delete node if current node is at top or bottom of the DLL
    if (current_node == head){
        deleteHead();
    }

    if (current_node == tail){
        deleteTail();
    }
}
*/

void DoublyLinkedList::insertAtHead(int value) {
    Node* newNode = new Node(value, false, false); // add a floor with no stoppage
    if (head == nullptr) {
        head = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}


// Member function definition to insert a node at the tail of the list
void DoublyLinkedList::insertAtTail(int value) {
    Node* newNode = new Node(value, false, false); // add a floor with no stoppage
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

/*
// Traverse the doubly linked list in forward direction
void DoublyLinkedList::DLL_Traversal(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        // Output data of the current node
        // cout << current->data << " ";
        current = current->next;
    }
    //std::cout << std::endl;
}
*/

// Delete the head node
void DoublyLinkedList::deleteHead() {
    if (head == nullptr) {
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    delete temp;
}

// Delete the tail node
void DoublyLinkedList::deleteTail() {
    if (tail == nullptr) {
        return;
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    }
    delete temp;
}

/*
// Reset stops once serviced
void DoublyLinkedList::reset_stops_once_serviced() {
    // Implementation
}
*/

// Count the number of nodes in the list
int DoublyLinkedList::countNodes() {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

/*
// Display the linked list
void DoublyLinkedList::display() {
    Node* current = head;
    while (current) {
        std::cout << "Floor " << current->floor_index << ": Stop Up - " << (current->stop_up ? "True" : "False") << ", Stop Down - " << (current->stop_down ? "True" : "False") << std::endl;
        current = current->next;
    }
}
*/

// Find movement direction of STATIONARY lift from internal requests and external requests
DIR find_direction_from_IR_ER(int current_floor, std::vector<int> IR,
                              std::vector<std::pair<int, DIR>> ER) {
    unsigned int num_requests_IR = IR.size();
    unsigned int num_requests_ER = ER.size();
    unsigned int first_request;
    DIR predicted_direction;

    if (num_requests_IR >= 1) {
        first_request = IR[0];
        predicted_direction = (first_request > current_floor) ? UP : DOWN;
    } else if (num_requests_ER >= 1) {
        first_request = ER[0].first;
        predicted_direction = (first_request > current_floor) ? UP : DOWN;
    } else {
        predicted_direction = STATIONARY;
    }
    return predicted_direction;
}

void DoublyLinkedList::printFloorValues() {
    Node* current = tail;
    std::cout << "Floor values in DLL from tail to head:" << std::endl;
    while (current != nullptr) {
        std::cout << current->floor_index << " ";
        current = current->prev;
    }
    std::cout << std::endl;

    current = head;
    std::cout << "Floor values in DLL from head to tail:" << std::endl;
    while (current != nullptr) {
        std::cout << current->floor_index << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

