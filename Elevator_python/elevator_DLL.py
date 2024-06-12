class Node:
    def __init__(self, floor, stop_up, stop_down):
        self.floor_index=floor
        self.stop_up=stop_up
        self.stop_down=stop_down

        self.next = None
        self.prev = None

class DoublyLinkedList:

    def __init__(self):
        self.head=None
        self.tail=None

    def insertAtHead(self, val):
        #

    def insertAtTail(self, val):
        #

    def deleteHead(self):
        #

    def deleteTail(self):
        #

    def counNodes(self):
        #

    def printFloorValues(self):
        #

    def set_stop_up_down_using_index_direction(self, index, direction):

    #

    def add_new_head_tail_intermediate_floors_IR(self):
        #

    def add_new_head_tail_intermediate_floors_ER(self):
        #

    def set_up_down_stops_ER(self, list_ER):
        #

    def set_up_down_stops_ER(self, list_IR, current_node, direction):
        #


    def extend_DLL(self, min_max_request):
        #


