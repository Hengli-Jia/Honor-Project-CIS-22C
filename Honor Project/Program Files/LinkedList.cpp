#include "LinkedList.h"
#include <iostream>

LinkedListNode::LinkedListNode(HuffmanNode* node) : huffmanNode(node), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr), length(0) {}

void LinkedList::insertSorted(LinkedListNode* newNode) {
    length++;
    if (!head || newNode->huffmanNode->frequency < head->huffmanNode->frequency) {
        newNode->next = head;
        head = newNode;
        return;
    }
    LinkedListNode* current = head;
    while (current->next && current->next->huffmanNode->frequency <= newNode->huffmanNode->frequency) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void LinkedList::removeFirstTwo(HuffmanNode*& first, HuffmanNode*& second) {
    if (!head || !head->next) {
        first = nullptr;
        second = nullptr;
        return;
    }
    LinkedListNode* firstNode = head;
    LinkedListNode* secondNode = head->next;
    first = firstNode->huffmanNode;
    second = secondNode->huffmanNode;
    head = secondNode->next;
    delete firstNode;
    delete secondNode;
    length -= 2;
}

void LinkedList::print() const {
    LinkedListNode* current = head;
    while (current) {
        if (current->huffmanNode->character != '\0')
            std::cout << current->huffmanNode->character << ": ";
        std::cout << current->huffmanNode->frequency << std::endl;
        current = current->next;
    }
}

LinkedList::~LinkedList() {
    while (head) {
        LinkedListNode* temp = head;
        head = head->next;
        delete temp;
    }
}
