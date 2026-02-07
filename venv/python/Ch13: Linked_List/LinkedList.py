from List_node import *

class LinkedList:
    def __init__(self):
        self.head = None


    def node_append(self, value):
        new_node = Node(value)
        if self.head == None:
            self.head = new_node
        else:
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = new_node



    def node_prepend(self,value):
        new_node = Node(value)
        new_node.next = self.head
        self.head = new_node


    def node_deletion(self,value):
        current = self.head
        print(current)
        if self.head is None:
            print("theres litteraly nothing to delete what are you doing")
            return
        elif self.head.value == value:
            self.head = self.head.next
            return
        else:
            prev = None
            while current is not None and current.value != value:
                prev = current
                current = current.next
            if current is None:
                print("Didnt find this value")
                return
            prev.next = current.next




    def print_nodes(self):
        current = self.head
        print(current.value)
        while current.next is not None:
            current = current.next
            print(current.value)
                    
                
