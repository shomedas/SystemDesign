#include <iostream>

#include "elevator_DLL.h"
#include "create_requests.h"
#include "enums.h"
#include "utils.h"

int main(int argc, char *argv[]) {

    /// create the DLL representing the dynamic path of the lift
    DoublyLinkedList DLL_floors;

    int start_floor = 2;
    int total_floors = 10;

    Node * start_node = new Node(start_floor, false, false);

    DLL_floors.head=start_node;
    DLL_floors.tail=start_node;

    DIR current_direction = STATIONARY;
    unsigned int current_floor;

    std::vector<int> pending_IR;
    std::vector<std::pair<int, DIR> > pending_ER;

    Node * current_node = start_node;

    while(true)
    {
        current_floor = current_node->floor_index;

        /// Display current floor ///
        std::cout << "Current floor="<< current_floor << std::endl;

        /// at current floor if current direction and node direction match
        /// we need to modify the current_nodes stop_up or stop_down value
        ///  also remove current floor from request once it is serviced at the current floor

        if((current_direction==UP && current_node->stop_up==true)||
           (current_direction==DOWN && current_node==DLL_floors.tail && current_node->stop_up==true))
        {
            std::cout << "STOPPING while going UP at floor="<< current_node->floor_index<< std::endl;
            current_node->stop_up=false;
            /// remove current floor from pending list of IR and ER
            removeIfExists(pending_IR, current_node->floor_index);

            std::pair<int, DIR> current_pair(current_node->floor_index, UP);
            removePairFromVector(pending_ER, current_pair);
        }

        if((current_direction==DOWN  && current_node->stop_down==true)||
           (current_direction==UP && current_node==DLL_floors.head && current_node->stop_down==true))
        {
            std::cout << "STOPPING while going DOWN at floor="<< current_node->floor_index<< std::endl;
            current_node->stop_down=false;
            /// remove current floor from pending list of IR and ER
            removeIfExists(pending_IR, current_node->floor_index);

            std::pair<int, DIR> current_pair(current_node->floor_index, DOWN);
            removePairFromVector(pending_ER, current_pair);
        }

        /// DISPLAY pending IR and ER to user
        /// so that the same are not entered again

        display_pending_IR(pending_IR);
        display_pending_ER(pending_ER);

        /// capture Internal and external requests at current floor
        std::vector<int> new_IR = get_IR();
        std::vector<std::pair<int, DIR> > new_ER = get_ER();

        /// concatenate new_IR with pending_IR
        merge_and_remove_duplicate_IR(pending_IR, new_IR);
        merge_and_remove_duplicate_ER(pending_ER, new_ER);

        /// If the lift is stationary, set lift DIRECTION from
        /// current requests and current floor location
        /// else use the current direction and the lift DLL to
        /// add new nodes and update the current DLL

        if (current_direction==STATIONARY)
        {
            // find lift direction from IR and ER
            current_direction = find_direction_from_IR_ER(current_floor, new_IR, new_ER);
        }

        /// add the new nodes to the elevator DLL using IR, ER, and the DIRECTION
        DLL_floors.add_new_head_tail_intermediate_floors_IR(new_IR);
        DLL_floors.add_new_head_tail_intermediate_floors_ER(new_ER);


        // also set stop_up and stop_down for each floor using IR and ER
        DLL_floors.set_up_down_stops_ER(new_ER);
        DLL_floors.set_up_down_stops_IR(new_IR, current_node,current_direction);

        /// set the next floor and direction reversal if count nodes > 1
        if (DLL_floors.countNodes()>1)
        {
            if (current_node==DLL_floors.head)
            {
                std::pair<int, DIR> temp_pair(current_node->floor_index, UP);

                current_node = current_node->next;
                if (!pair_exists_in_vector(pending_ER, temp_pair))
                {
                    //DLL_floors.delete_current_node_if_head_or_tail(current_node->prev);
                    DLL_floors.deleteHead();
                }
                current_direction = DOWN;
            }
            else if (current_node==DLL_floors.tail)
            {
                std::pair<int, DIR> temp_pair(current_node->floor_index, DOWN);

                current_node = current_node->prev;//can only go up
                if (!pair_exists_in_vector(pending_ER, temp_pair))
                {
                    //DLL_floors.delete_current_node_if_head_or_tail(current_node->next);
                    DLL_floors.deleteTail();
                }
                current_direction = UP;
            }
            else
            {
                if (current_direction==UP)
                {
                    current_node = current_node->prev;
                }
                if (current_direction==DOWN)
                {
                    current_node = current_node->next;
                }
            }
        }
        else
        {
            current_direction = STATIONARY;
        }

        /// Display LIFT DIRECTION ///
        switch (current_direction)
        {
            case UP:
                std::cout << "Going UP" << std::endl;
                break;
            case DOWN:
                std::cout << "Going DOWN" << std::endl;
                break;
            case STATIONARY:
                std::cout << "STATIONARY" << std::endl;
                break;
        }
        std::cout << "=============================================================" << std::endl;

    }
    return 0;
}
