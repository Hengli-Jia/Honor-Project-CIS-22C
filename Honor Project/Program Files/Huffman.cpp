#include "Huffman.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

Huffman::Huffman() : root(nullptr) {}

Huffman::~Huffman() { freeTree(root); }

void Huffman::freeTree(HuffmanNode* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

HuffmanNode* Huffman::build(HuffmanNode* left, HuffmanNode* right) {
    int freq = 0;
    if (left) freq += left->frequency;
    if (right) freq += right->frequency;
    HuffmanNode* merged = new HuffmanNode('\0', freq);
    merged->left = left;
    merged->right = right;
    return merged;
}

void Huffman::printTreeHelper(const HuffmanNode* node, const std::string& indent, bool isRight) const {
    if (!node) return;
    printTreeHelper(node->right, indent + (isRight ? "        " : " |      "), true);

    std::cout << indent;
    if (isRight) std::cout << " /";
    else std::cout << " \\";
    std::cout << "----- ";
    if (!node->left && !node->right)
        std::cout << "'" << node->character << "'(" << node->frequency << ")" << std::endl;
    else
        std::cout << "*(" << node->frequency << ")" << std::endl;

    printTreeHelper(node->left, indent + (isRight ? " |      " : "        "), false);
}

void Huffman::printCodeHelper(const HuffmanNode* node, const std::string& prefix) const {
    if (!node) return;
    if (!node->left && !node->right) {
        std::cout << node->character << ": " << prefix << std::endl;
    }
    printCodeHelper(node->left, prefix + "0");
    printCodeHelper(node->right, prefix + "1");
}

std::string Huffman::getCodeHelper(const HuffmanNode* node, char ch, std::string path) const {
    if (!node) return "";
    if (!node->left && !node->right) {
        if (node->character == ch) return path;
        return "";
    }
    std::string left = getCodeHelper(node->left, ch, path + "0");
    if (!left.empty()) return left;
    return getCodeHelper(node->right, ch, path + "1");
}

std::string Huffman::encode(const std::string text) const {
    std::string encoded;
    for (char c : text) {
        encoded += encodeHelper(root, c, "");
    }
    return encoded;
}

std::string Huffman::encodeHelper(const HuffmanNode* node, char ch, const std::string& path) const {
    if (!node) return "";
    if (!node->left && !node->right) {
        if (node->character == ch) return path;
        return "";
    }
    std::string left = encodeHelper(node->left, ch, path + "0");
    if (!left.empty()) return left;
    return encodeHelper(node->right, ch, path + "1");
}

std::string Huffman::decode(const std::string code) const {
    std::string result;
    int idx = 0;
    while (idx < static_cast<int>(code.size())) {
        decodeHelper(root, code, idx, result);
    }
    return result;
}

void Huffman::decodeHelper(const HuffmanNode* node, const std::string& code, int& idx, std::string& result) const {
    if (!node) return;
    if (!node->left && !node->right) {
        result += node->character;
        return;
    }
    if (idx < static_cast<int>(code.size())) {
        if (code[idx] == '0')
            decodeHelper(node->left, code, ++idx, result);
        else if (code[idx] == '1')
            decodeHelper(node->right, code, ++idx, result);
    }
}

