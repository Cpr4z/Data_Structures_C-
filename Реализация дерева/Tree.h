#pragma once
#define SIZE 10
class Tree { // класс дерево

    
    

private:
    struct Node;
    
    struct Node { // структура узла
        

        Node(int _number, Node* _parent = nullptr) :
            number(_number),
            parent(_parent),
            childCount(0)
        { }
        ~Node()
        {
            for (int i = 0; i < childCount; i++)
            {
                delete children[i];
            }
        }
        void addChild(Node* newChild) {
            children[childCount++] = newChild;
        }
        //void delChild(Node* child);
        int number; // номер мершины

        Node* parent; // родительская вершина
        Node* children[SIZE]; // список дочерних вершин
        int childCount; // количество детей        
    };


   
    Node* getNodeByNumber(int number, Node* current);
    Node* root;
public:
    void delChild(Node* child);
    Tree();
    ~Tree();
    void setRoot(int number);
    void addNode(int newNodeNumber, int parentNodeNumber);
    void delNode(int number);

};