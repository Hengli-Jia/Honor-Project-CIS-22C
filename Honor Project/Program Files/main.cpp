#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
using namespace std;
#include "LinkedList.h"

void printMenu() {
    cout << "\nMenu:\n";
    cout << "1. Print the character weights (frequencies)\n";
    cout << "2. Print Tree (Right-Root-Left ¨C indented format)\n";
    cout << "3. Print the Huffman codes as strings for all characters in the list\n";
    cout << "4. Enter one character ¨C print its Huffman code as a string\n";
    cout << "5. Enter a word ¨C print its ASCII binary representation and its Huffman code\n";
    cout << "6. Enter an encoded word, decode it, then display it\n";
    cout << "7. Enter the name of a text file, encode it, and save it to another file\n";
    cout << "8. Enter the name of the encoded file, decode it, then save it to another file\n";
    cout << "9. Quit\n";
    cout << "Enter your choice: ";
}

int main() {
    string input;
    int letterCount[128] = { 0 };

    cout << "Enter a string to analyze (type END on a new line to finish):\n";
    string line;
    while (getline(cin, line)) {
        if (line == "END") break;
        input += line + '\n'; 
    }

    for (char c : input) {
        letterCount[c]++;
    }

    LinkedList list;
    for (int i = 0; i < 127; i++) {
        if (letterCount[i] > 0) {
            HuffmanNode* node = new HuffmanNode((char)i, letterCount[i]);
            list.insertSorted(node);
        }
    }

    Huffman tree;
    while (list.getLength() > 1) {
        HuffmanNode* first;
        HuffmanNode* second;
        list.removeFirstTwo(first, second);

        HuffmanNode* merged = tree.build(first, second);
        list.insertSorted(merged);
    }
    tree.setRoot(list.getHead()->huffmanNode);

    int choice;
    do {
        printMenu();
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer

        switch (choice) {
        case 1: // Print character frequencies
            cout << "Letter frequencies:\n";
            for (int i = 0; i < 127; i++) {
                if (letterCount[i] > 0) {
                    cout << char(i) << ": " << letterCount[i] << endl;
                }
            }
            break;
        case 2: // Print Huffman tree (Right-Root-Left, indented)
            cout << "Huffman Tree (Right-Root-Left):\n";
            tree.printTree(tree.getRoot());
            break;
        case 3: // Print Huffman codes for all characters
            cout << "Huffman codes for all characters:\n";
            tree.printCode(tree.getRoot());
            break;
        case 4: { // Print Huffman code for one character
            cout << "Enter a character: ";
            char ch;
            cin >> ch;
            string code = tree.getCode(ch);
            if (!code.empty())
                cout << "Huffman code for '" << ch << "': " << code << endl;
            else
                cout << "Character not found in the tree.\n";
            break;
        }
        case 5: { // Print ASCII and Huffman code for a word
            cout << "Enter a word: ";
            string word;
            cin >> word;
            cout << "ASCII binary: ";
            for (char c : word) {
                cout << bitset<8>(static_cast<unsigned char>(c));
            }
            cout << "\nHuffman code: " << tree.encode(word) << endl;
            break;
        }
        case 6: { // Decode an encoded word
            cout << "Enter an encoded word (as 0s and 1s): ";
            string encoded;
            cin >> encoded;
            string decoded = tree.decode(encoded);
            cout << "Decoded string: " << decoded << endl;
            break;
        }
        case 7: { // Encode file and save
            string inputFileName, encodedFileName;
            cout << "Enter the name of the text file to encode: ";
            cin >> inputFileName;
            ifstream inputFile(inputFileName);
            if (!inputFile) {
                cerr << "Failed to open input file.\n";
                break;
            }
            string fileContent((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
            inputFile.close();
            string encoded = tree.encode(fileContent);
            cout << "Enter the name of the file to save the encoded data: ";
            cin >> encodedFileName;
            ofstream encodedFile(encodedFileName);
            if (!encodedFile) {
                cerr << "Failed to open encoded file for writing.\n";
                break;
            }
            encodedFile << encoded;
            encodedFile.close();
            cout << "Encoding complete. Encoded data saved to " << encodedFileName << endl;
            break;
        }
        case 8: { // Decode file and save
            string encodedInputFileName, decodedFileName;
            cout << "Enter the name of the encoded file to decode: ";
            cin >> encodedInputFileName;
            ifstream encodedInputFile(encodedInputFileName);
            if (!encodedInputFile) {
                cerr << "Failed to open encoded input file.\n";
                break;
            }
            string encodedContent((istreambuf_iterator<char>(encodedInputFile)), istreambuf_iterator<char>());
            encodedInputFile.close();
            string decoded = tree.decode(encodedContent);
            cout << "Enter the name of the file to save the decoded data: ";
            cin >> decodedFileName;
            ofstream decodedFile(decodedFileName);
            if (!decodedFile) {
                cerr << "Failed to open decoded file for writing.\n";
                break;
            }
            decodedFile << decoded;
            decodedFile.close();
            cout << "Decoding complete. Decoded data saved to " << decodedFileName << endl;
            break;
        }
        case 9:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}