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
        new_node = Node(val, False, False)

        if self.head==None:
            self.head=self.tail=new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head =  new_node

    def insertAtTail(self, val):
        new_node = Node(val, False, False)

        if self.head==None:
            self.head=self.tail = new_node
        else:
            self.tail.next = new_node
            new_node.prev = self.tail
            self.tail = new_node

    def deleteHead(self):
        if self.head==None:
            return
        else:
            self.head = self.head.next


    def deleteTail(self):
        if self.tail == None:
            return
        if self.head==self.tail:
            self.head=self.tail=None
        else:
            self.tail = self.tail.prev
            self.tail.next = None

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


