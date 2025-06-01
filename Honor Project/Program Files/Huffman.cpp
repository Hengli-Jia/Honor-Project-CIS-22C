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

void Huffman::printCode() const {
    printCodeHelper(root, "");
}

void Huffman::printCodeHelper(const HuffmanNode* node, const std::string& prefix) const {
    if (!node) return;
    if (!node->left && !node->right) {
        std::cout << node->character << ": " << prefix << std::endl;
    }
    printCodeHelper(node->left, prefix + "0");
    printCodeHelper(node->right, prefix + "1");
}

void Huffman::printTree() const {
    printTreeHelper(root, "", false);
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

std::string Huffman::getCode(const char ch) const {
    std::string code;
    if (getCodeHelper(root, ch, code))
        return code;
    return "";
}

std::string Huffman::encode(const std::string text) const {
    std::string codeMap[128];
    encodeHelper(root, "", codeMap);
    std::string encoded;
    for (char c : text) {
        encoded += codeMap[c];
    }
    return encoded;
}

std::string Huffman::decode(const std::string code) const {
    std::string decoded;
    const HuffmanNode* node = root;
    for (char bit : code) {
        if (bit == '0') node = node->left;
        else if (bit == '1') node = node->right;
        if (!node->left && !node->right) {
            decoded += node->character;
            node = root;
        }
    }
    return decoded;
}

bool Huffman::getCodeHelper(const HuffmanNode* node, char ch, std::string& path) const{
    if (!node) return false;
    if (!node->left && !node->right) {
        if (node->character == ch) return true;
        return false;
    }
    path.push_back('0');
    if (getCodeHelper(node->left, ch, path)) return true;
    path.pop_back();
    path.push_back('1');
    if (getCodeHelper(node->right, ch, path)) return true;
    path.pop_back();
    return false;
}

void Huffman::encodeHelper(const HuffmanNode* node, const std::string& str, std::string codeMap[128]) const {
    if (!node) return;
    if (!node->left && !node->right) {
        if (node->character >= char(0) && node->character <= char(127))
            codeMap[node->character] = str;
    }
    encodeHelper(node->left, str + "0", codeMap);
    encodeHelper(node->right, str + "1", codeMap);
}
