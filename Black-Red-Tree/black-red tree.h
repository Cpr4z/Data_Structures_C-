#pragma once
enum Color { Black, Red };
class RBTree {
    struct Node
    {
        int key;
        Color color;
        Node* left;
        Node* right;
        Node* parent;
        Node(int k) :
            key(k), color(Red), parent(nullptr),
            left(nullptr), right(nullptr) { };
    };
    Node* root;
   void insert(int key);
   void insert(Node* root, Node* node);
   void InsertFixUp(Node*& root, Node* node);
   Node* search(int key);
   Node* search(Node* node, int key) const;
    
};