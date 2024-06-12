#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <vector>
#include <utility>
#include "enums.h"

struct Node {
    bool stop_up;
    bool stop_down;
    int floor_index;
    Node* prev;
    Node* next;
    Node(int floor, bool stop_up, bool stop_down);
};

class DoublyLinkedList {
public:
    Node* head;           // Top most floor in list of requests
    Node* tail;           // Bottom most floor in list of requests
//    Node* current_node;   // Indicates current floor
    //DIR direction;

    DoublyLinkedList();

    /// This function modifies the DLL using the external, internal requests,
    /// current floor value and lift direction
    /*
    void add_new_head_tail_intermediate_floors(std::vector<int> IR,
                                               std::vector<std::pair<int, DIR>> ER,
                                               Node * current_node, DIR direction);
    */

    void add_new_head_tail_intermediate_floors_IR(std::vector<int> IR);
    void add_new_head_tail_intermediate_floors_ER(std::vector<std::pair<int, DIR> > ER);

    //void delete_current_node_if_head_or_tail(Node * current_node);

    void set_stop_up_down_using_index_direction(int index, DIR direction);

    void set_up_down_stops_IR(std::vector<int> IR, Node * current_node,
                                                DIR direction);

    void extend_DLL(std::pair<int,int> min_max_request);

    void set_up_down_stops_ER(std::vector<std::pair<int, DIR> > ER);

    //void DLL_Traversal(Node* head);
    void deleteHead();
    void deleteTail();
    void insertAtHead(int value);
    void insertAtTail(int value);
    //void reset_stops_once_serviced();
    //void set_stop_up_down_using_index_direction(int idx);
    int countNodes();
    //void set_current_node(Node* node);
    //void display();
    void printFloorValues();
};

DIR find_direction_from_IR_ER(int current_floor, std::vector<int> IR, std::vector<std::pair<int, DIR>> ER);

#endif // DOUBLY_LINKED_LIST_H

