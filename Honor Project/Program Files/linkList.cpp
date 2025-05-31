#include "linkList.h"
#include "huffman.h"
#include <iostream>

// Node 构造函数
Node::Node(TreeNode* t) : treeNode(t), next(nullptr) {}

// LinkedList 构造函数
LinkedList::LinkedList() : head(nullptr), length(0) {}

// 有序插入 TreeNode，按频率升序
void LinkedList::insertSorted(TreeNode* treeNode) {
    Node* newNode = new Node(treeNode);
    length++;
    if (!head || treeNode->frequency < head->treeNode->frequency) {
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next && current->next->treeNode->frequency <= treeNode->frequency) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

// 移除前两个节点，并返回它们的 TreeNode 指针
void LinkedList::removeFirstTwo(TreeNode*& first, TreeNode*& second) {
    if (!head || !head->next) {
        first = nullptr;
        second = nullptr;
        return;
    }
    Node* firstNode = head;
    Node* secondNode = head->next;
    first = firstNode->treeNode;
    second = secondNode->treeNode;
    head = secondNode->next;
    delete firstNode;
    delete secondNode;
    length -= 2;
}

// 打印链表（调试用）
void LinkedList::print() const {
    Node* current = head;
    while (current) {
        if (current->treeNode->character != '\0')
            std::cout << current->treeNode->character << ": ";
        std::cout << current->treeNode->frequency << std::endl;
        current = current->next;
    }
}

// 析构函数
LinkedList::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}