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
    void printTree(const HuffmanNode* node, std::string indent = "", bool isRight = false) const;
    void printCode(const HuffmanNode* node, std::string prefix = "") const;
    std::string getCode(const char ch) const;
    std::string encode(const std::string text) const;
    std::string decode(const std::string code) const;
    void setRoot(HuffmanNode* node) { root = node; }
    HuffmanNode* getRoot() const { return root; }

private:
    HuffmanNode* root;
    bool getCodeHelper(const HuffmanNode* node, char ch, std::string& path) const;
    void encodeHelper(const HuffmanNode* node, const std::string& str, std::string codeMap[128]) const;

};

#endif // HUFFMAN_H