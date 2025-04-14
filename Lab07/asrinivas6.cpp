#include <iostream>
#include <string.h>
using namespace std;

struct Node{
    int root;
    Node* left;
    Node* right;
    Node* parent;
};

Node* create(int x){
    Node* node = new Node();
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    node->root = x;
    return node;
}

void insert(Node* &T, int z){
    Node*insert = create(z);
    Node* x = T;
    Node* y = nullptr;

    while(x != nullptr){
        y = x;
        if(insert->root < x->root){
            x = x->left;
        } else {
            x = x->right;
        }
    }

    insert->parent = y;

    if(y == nullptr){
        T = insert;
    } else if (insert->root < y->root){
        y->left = insert;
    } else{
        y->right = insert;
    }
}

void Transplant(Node* &T, Node* u, Node* v){
    if(u->parent == nullptr){
        T = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if(v != nullptr){
        v->parent = u->parent;
    }
}

Node* TreeMin(Node* z){
    while(z->left != nullptr){
        z = z->left;
    }
    return z;
}

Node* search(Node* x, int k){
    if(x == nullptr || k == x->root){
        return x;
    }

    if(k < x->root){
        return search(x->left, k);
    } else{
        return search(x->right, k);
    }
}

void Tree_delete(Node* &T, int x){
    Node* z = search(T, x);
    if(z->left == nullptr){
        Transplant(T,z,z->right);
    } else if (z->right == nullptr){
        Transplant(T,z,z->left);
    } else{
        Node* y = TreeMin(z->right);
        if(y != z->right){
            Transplant(T,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        } 
        Transplant(T,z,y);
        y->left = z->left;
        y->left->parent = y;
    }
}

void inorder_walk(Node* x){
    if(x != nullptr){
        inorder_walk(x->left);
        cout << x->root << endl;
        inorder_walk(x->right);
    }
}

void preorder(Node* x){
    if(x != nullptr){
        cout << x->root <<endl;
        preorder(x->left);
        preorder(x->right);
    }

}

void postorder(Node* x){
    if(x != nullptr){
        postorder(x->left);
        postorder(x->right);
        cout << x->root <<endl;
    }

}

int main(int argc, char **argv) {
    string input;
    Node* T = nullptr;

    cin>>input;

    while(input != "e"){
        if(input == "oin"){
            inorder_walk(T);
        } else if (input == "opre"){
            preorder(T);
        } else if (input == "opost"){
            postorder(T);
        } else if (input[0] == 'i'){
            char i = input[1];
            int value = i - '0';
            int length = input.length();
            if(length > 2){
                int index = 2;
                while(input[index] != '\0'){
                    if(input[index] != '\0'){
                        i = input[index];
                        value = value*10 + (i-'0');
                        index++;
                    }
                }
            }
            insert(T, value);
        } else if (input[0] == 'd'){
            char i = input[1];
            int value = i - '0';
            int length = input.length();
            if(length > 2){
                int index = 2;
                while(input[index] != '\0'){
                    if(input[index] != '\0'){
                        i = input[index];
                        value = value*10 + (i-'0');
                        index++;
                    }
                }
            }
            Tree_delete(T, value);
        } else{
            cout << "Not a valid input. Please try again" << endl;
        }

        cin>>input;
    }

    

}

