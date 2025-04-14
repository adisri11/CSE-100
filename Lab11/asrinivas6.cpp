#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <iomanip>  // Needed for std::setw
using namespace std;

struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    // Constructor for leaf nodes
    Node(char c, int f) {
        character = c;
        frequency = f;
        left = nullptr;
        right = nullptr;
    }

    // Constructor for internal nodes
    Node(Node* l, Node* r) {
        character = '\0';  // Internal nodes don't represent a character
        frequency = l->frequency + r->frequency;
        this->left = l;    // Correct assignment to member variable
        this->right = r;
    }
};

// Recursively print the tree in a sideways format
void printTree(Node* root, int indent = 0) {
    if(root == nullptr)
        return;
    
    // Recursively print the right subtree, increasing indentation
    printTree(root->right, indent + 4);

    // Print indentation spaces
    if(indent)
        cout << setw(indent) << ' ';

    // Use '*' (or any marker) for internal nodes (where character is '\0')
    if(root->character == '\0')
        cout << "*" ;
    else
        cout << root->character;
    
    cout << " (" << root->frequency << ")" << "\n";

    // Recursively print the left subtree
    printTree(root->left, indent + 4);
}

void Huffman(vector<Node*>& nodes) {  // Pass vector by reference for efficiency
    while(nodes.size() > 1) {
        int min = -1;
        int next = -1;

        // Find the two nodes with the smallest frequency
        for(int i = 0; i < nodes.size(); i++){
            if(min == -1 || nodes[i]->frequency < nodes[min]->frequency) {
                next = min;
                min = i;
            } else if (next == -1 || nodes[i]->frequency < nodes[next]->frequency) {
                next = i;
            }
        }

        // Combine the two minimum frequency nodes
        Node* combine = new Node(nodes[min], nodes[next]);

        // Erase the two nodes in the correct order to avoid index issues
        if(min > next) {
            nodes.erase(nodes.begin() + min);
            nodes.erase(nodes.begin() + next);
        } else {
            nodes.erase(nodes.begin() + next);
            nodes.erase(nodes.begin() + min);
        }

        // Add the new combined node
        nodes.push_back(combine);
    }
}

int main() {
    int symbols = 6;
    vector<Node*> nodes;
    int freq;

    // Read frequency for each symbol (assuming input for 6 symbols)
    for(int i = 0; i < symbols; i++){
        cin >> freq;
        nodes.push_back(new Node('A' + i, freq));
    }

    // Build the Huffman tree; after this call, nodes vector will contain one element: the root node.
    Huffman(nodes);

    // Print the Huffman tree starting from the root
    if(!nodes.empty()) {
        cout << "Huffman Tree:\n";
        printTree(nodes[0]);
    }

    // Optionally, print each symbol; this is unchanged from your original code
    for(int i = 0; i < symbols; i++){
        cout << char('A' + i) << ":" << "\n";
    }

    return 0;
}
