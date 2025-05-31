#ifndef LINKEDLIST_H  
#define LINKEDLIST_H  

#include "Huffman.h"  

struct LinkedListNode {  
    HuffmanNode* huffmanNode; 
    LinkedListNode* next;  

    LinkedListNode(HuffmanNode* node);  
};  

class LinkedList {  
private:  
    LinkedListNode* head;  
    int length;  

public:  
    LinkedList();  
    ~LinkedList();  

    void insertSorted(HuffmanNode* huffmanNode);  
    void removeFirstTwo(HuffmanNode*& first, HuffmanNode*& second);  
    void print() const;  

    int getLength() const { return length; }  
    LinkedListNode* getHead() const { return head; }  
    bool isEmpty() const { return length == 0; }  
}; 

#endif // LINKEDLIST_H