#include <bits/stdc++.h>

using namespace std;

class Tree{

    struct Node{
        Node* l = nullptr;
        Node* r = nullptr;
        int key;
        int height = 0;
        string value;

        Node(int k, string v){
            l = nullptr;
            r = nullptr;
            key = k;
            value = v;
            height = 1;
        }
    };

    Node* root = nullptr;

public:

    Tree(int k, string v){
        root = new Node(k, v);
    }

    void insert(int key, string value){
        insert_(root, key, value);
    }

    Node* insert_(Node* p, int key, string value){
        if(p == nullptr || !p){
            return new Node(key, value);
        }

        if(key < p->key){
            p->l = insert_(p->l, key, value);
        } else {
            p->r = insert_(p->r, key, value);
        }

        return balance(p);
    }

    string get(int key){
        return get_(root, key);
    }

    string get_(Node* p, int key){
        if(p == nullptr){
            return "Not found!";
        }

        if(p->key == key){
            return p->value;
        }
        if(key < p->key){
            return get_(p->l, key);
        } else {
            return get_(p->r, key);
        }
    }

    int height(Node *p){
        return (p != nullptr) ? p->height : 0;
    }

    void fixHeight(Node *p){
        p->height = max(height(p->l), height(p->r)) + 1;
    }

    int factor(Node *p){
        return height(p->r) - height(p->l);
    }

    Node* rotateRight(Node *p){
        Node *q = p->l;
        p->l = q->r;
        q->r = p;
        fixHeight(p);
        fixHeight(q);
        return q;
    }

    Node* rotateLeft(Node *q){
        Node *p = q->r;
        q->r = p->l;
        p->l = q;
        fixHeight(q);
        fixHeight(p);
        return p;
    }

    Node* balance(Node *p){
        fixHeight(p);
        if(factor(p) == 2){
            if(factor(p->r) < 0)
                p->r = rotateRight(p->r);
            return rotateLeft(p);
        }
        if(factor(p) == -2){
            if(factor(p->l) > 0)
                p->l = rotateLeft(p->l);
            return rotateRight(p);
        }
        return p;
    }

    void inOrder(){
        _inOrder(root);
    }

    void _inOrder(Node* p){
        cout << "Key: " << p->key << "; Value: " << p->value << endl;
        if(p->l != nullptr)
            _inOrder(p->l);
        if(p->r != nullptr)
            _inOrder(p->r);
    }


};

int main()
{
    Tree* tree = new Tree(10, "landa");
    tree->insert(2, "anabel");
    tree->insert(24, "axio");
    tree->insert(1, "Gendalf");
    tree->insert(10, "de ja vu");
    tree->insert(90, "Ist me?");
    tree->insert(100, "Muse");
    tree->inOrder();
    cout << tree->get(2) << endl;
    cout << tree->get(3) << endl;
    cout << tree->get(10) << endl;
    return 0;
}
