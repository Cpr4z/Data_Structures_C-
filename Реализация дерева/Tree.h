#pragma once
#define SIZE 10
class Tree { // ����� ������

    
    

private:
    struct Node;
    
    struct Node { // ��������� ����
        

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
        int number; // ����� �������

        Node* parent; // ������������ �������
        Node* children[SIZE]; // ������ �������� ������
        int childCount; // ���������� �����        
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