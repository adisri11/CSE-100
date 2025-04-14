#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

struct Node{
    int key;
    int value;
    Node* next;
    Node* parent;
};

struct Values{
    Node* x;
    int count;
};

Values returnvalues(Node* x, int count){
    Values v;
    v.x = x;
    v.count = count;

    return v;
}

Node* create(int x){
    Node* node = new Node();
    node->next = nullptr;
    node->parent = nullptr;
    node->key = 0;
    node->value = x;
    return node;
}

Values List_Search(Node*& L, int k){
    Node* x = L;
    int count = 0;
    while(x != nullptr && x->value != k){
        x = x->next;
        count++;
    }

    Values r = returnvalues(x, count);
    return r;
}

void List_Insert(Node*& L, int x){
    Node* insert = create(x);
    insert->next = L;
    if (L != nullptr){
        L->parent = insert;
    }
    L = insert;
}

void List_Delete(Node*& L, int x){
    Values r  = List_Search(L, x);
    Node* z = r.x;
    if(z == nullptr){
        cout << x << ":DELETE_FAILED;\n";
        return; 
    }

    if(z->parent != nullptr){
        z->parent->next = z->next;
    }
    else{
        L = z->next;
    }

    if(z->next != nullptr){
        z->next->parent = z->parent;
    }

    cout << x << ":DELETED;\n";

    delete z;
}

class HashTable{
    vector<Node*> table;
    int buckets;
    int* c;

    int hash(int k){
        return k % buckets;
    }

public:
    HashTable(int size){
        buckets = size;
        c = new int[buckets];
        table.resize(buckets, nullptr);
    }

    ~HashTable() {
        for (int i = 0; i < buckets; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    void hash_insert(int x){
        int place = hash(x);
        c[place]++;
        List_Insert(table[place], x);
    }

    void hash_delete(int x){
        int place = hash(x);
        c[place]--;
        List_Delete(table[place], x);
    }

    void hash_search(int x){
        int place = hash(x);
        Values r = List_Search(table[place], x);
        int s = r.count;
        Node* z = r.x;
        if(s < c[place]){
            cout << x << ":FOUND_AT"<< place << "," << s << ";\n";
        } else {
            cout << x << ":NOT_FOUND;\n";
        }
    }

    void print(){
        for(int i = 0; i < buckets; i++){
            cout << i << ":";
            Node* index = table[i];
            while(index != nullptr){
                cout<< index->value << "->";
                index = index->next;
            }
            cout << ";" << endl;
        }
    }

};



int main(int argc, char **argv) {
    string input;
    int m;

    cin>>m;
    HashTable t(m);

    cin>>input;
    while(input != "e"){
        if(input == "o"){
            t.print();
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
            t.hash_insert(value);
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
            t.hash_delete(value);
        } else if (input[0] == 's'){
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
            t.hash_search(value);
            } else{
            cout << "Not a valid input. Please try again" << endl;
        }

        cin>>input;
    }

    

}