#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>

struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char c, int f) : character(c), frequency(f), left(nullptr), right(nullptr) {}
};

class Huffman {
public:
    Huffman();
    ~Huffman();
    void freeTree(HuffmanNode* node);
    HuffmanNode* build(HuffmanNode* left, HuffmanNode* right);

    void printTree() const { printTreeHelper(root, "", false); }
    void printCode() const { printCodeHelper(root, ""); }
    std::string getCode(const char ch) const { return getCodeHelper(root, ch, ""); }
    std::string encode(const std::string text) const;
    std::string decode(const std::string code) const;

    void setRoot(HuffmanNode* node) { root = node; }
    HuffmanNode* getRoot() const { return root; }

private:
    HuffmanNode* root;
    void printTreeHelper(const HuffmanNode* node, const std::string& indent, bool isRight) const;
    void printCodeHelper(const HuffmanNode* node, const std::string& prefix) const;
    std::string getCodeHelper(const HuffmanNode* node, char ch, std::string path) const;
    std::string encodeHelper(const HuffmanNode* node, char ch, const std::string& path) const;
    void decodeHelper(const HuffmanNode* node, const std::string& code, int& idx, std::string& result) const;
};

#endif // HUFFMAN_H
