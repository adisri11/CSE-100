#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

struct Node{
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char c, int f){
        character = c;
        frequency = f;
        left = nullptr;
        right = nullptr;
    }

    Node(Node* left, Node* right){
        character = '\0';
        frequency = left->frequency + right->frequency;
        this->left = left;
        this->right = right;
    }
};

void getCodes(Node* root, string code, string codes[]) {
    if (!root->left && !root->right) {
        codes[root->character - 'A'] = code;  
        return;
    }

    if (root->left)
        getCodes(root->left, code + "0", codes);
    if (root->right)
        getCodes(root->right, code + "1", codes);
}

void Huffman(vector<Node*> &nodes){
    while(nodes.size() > 1){
        int min = -1;
        int next = -1;

        for(int i = 0; i < nodes.size(); i++){
            if(min == -1 || nodes[i]->frequency < nodes[min]->frequency){
                next = min;
                min = i;
            } else if (next == -1 || nodes[i]->frequency < nodes[next]->frequency) {
                next = i;
            }
        }

        Node* combine = new Node(nodes[min], nodes[next]);

        if(min > next){
            nodes.erase(nodes.begin() + min);
            nodes.erase(nodes.begin() + next);
        } else {
            nodes.erase(nodes.begin() + next);
            nodes.erase(nodes.begin() + min);
        }

        nodes.push_back(combine);
    }
}

int main(){
    const int symbols = 6;
    vector<Node*> nodes;
    int freq;
    string codes[symbols];

    for(int i = 0; i < symbols; i++){
        cin >> freq;
        nodes.push_back(new Node('A' + i, freq));
    }

    Huffman(nodes);   

    Node* node = nodes[0];

    getCodes(node, "", codes);

    for(int i = 0; i < symbols; i++){
        cout << char('A' + i) << ":" << codes[i] << "\n";
    }
}