#include "BinaryTree.h"
#include <iostream>


bool BinaryTree::isRoot(Node* check) {
    return check == root;
}
bool BinaryTree::isLeaf(Node* check) {
    return check->leftChild == nullptr
        && check->rightChild == nullptr;
}
void BinaryTree::addInt(int newData) {
	if (root == 0)
		root = new Node(newData);
	else {
		Node* current = root;
		Node* newNode = 0;
		while (newNode == 0) {
			if (current->data >= newData) {//���� ������� ����� � Node ������ ��� ����� ����� �� ���� �� ����� �����
				
				if (current->leftChild != 0) {//���� ����� ������� �������� �������� �� ������, �� ������������ �������� �������� ������ �������
					current = current->leftChild;
					continue;
				}
				newNode = new Node(newData, current);//���� ��� ������ �������, �� ������� ����� Node
				current->leftChild = newNode;
			}
			else//���� �� ������ �����
			{
				if (current->rightChild != 0) {
					current = current->rightChild;
					continue;
				}
				else {
					newNode = new Node(newData, current);
					current->rightChild = newNode;
				}

			}
		}
	}
}
void BinaryTree::print() {
	Node* queue[100];

	int queueCounter = 0;

	queue[queueCounter++] = root;
	while(queueCounter!=0){
		Node* current = queue[0];
		
		queueCounter--;

		for (int i = 0; i < queueCounter; i++) {
			queue[i] = queue[i + 1];
		}


		if (current->parent)
			std::cout << current->parent->data;
		std::cout << " " << current->data << std::endl;
		if (current->leftChild)
			queue[queueCounter++] = current->leftChild;
		if (current->rightChild)
			queue[queueCounter++] = current->rightChild;
	
	}
}
BinaryTree::Node* BinaryTree::findNodeByData(int finddata)
{
    Node* curr = root;
    while (curr)//���� ��������� �� ������� ������� �� ����� nullptr
    {
        if (curr->data == finddata)//���� ������� �������� ����� ���� ��������, ������� ����
        {
            return curr;
        }
        if (curr->data > finddata)//���� ������� �������� ������ ��� �� ��������, ������� ����, �� ���� � ����� ���������
        {
            curr = curr->leftChild;
        }
        else//���� ������, �� ���� � ������ ���������
        {
            curr = curr->rightChild;
        }
    }
    return nullptr;//���� �������� ���, �� ���������� nullptr
}
// �������� ��������
BinaryTree::Node* BinaryTree::treeMax(Node* x) {
	while (x->rightChild != nullptr)
		x = x->rightChild;
	return x;
}
BinaryTree::Node* BinaryTree::treeMin(Node* y) {
	while (y->leftChild != nullptr)
		y = y->leftChild;
	return y;
}
void BinaryTree::TransPlant(Node* U, Node* V) {
	if (U->parent == nullptr) {//���� �� ������� ������, ����� �� ��������� ������������ ������� ������ ������
		root = V;
	}
	else if (U == U->parent->leftChild){//���� ��������� ������� �������� ����� �������� 
		U->parent->leftChild = V;
	}
	else {//���� ��������� ������� �������� ������ �������� ������ ��������
		U->parent->rightChild = V;
	}
	if (V != nullptr)
		V->parent = U->parent;
}
void BinaryTree::delInt(int deldata) {
    Node* foundForDel = findNodeByData(deldata);
    if (foundForDel == nullptr)
        return; // ������ ������ ����� ��� � ������
    // ����� ����� ����
    if (isLeaf(foundForDel)) { // ���� ��� ����, ������ ������ ���
        delLeaf(foundForDel);
    }
    else {
        // ���� �� ����, �� �������� �������
        if (foundForDel->leftChild == nullptr || foundForDel->rightChild == nullptr) {
            // ������, ����� � ���� ������ ���� ��������
            delNodeWithOneChild(foundForDel);
        }
        else {
            // ���� ������ ������� ������ ���������
            Node* mostright = foundForDel->leftChild;
            while (mostright->rightChild != nullptr)
                mostright = mostright->rightChild;

            // �������� ������ �� ������� ������ ������ � ��������� ����  
            foundForDel->data = mostright->data;

            // ������� ������ ������� (�� ����� ��������� ������ ����� ����)
            if (mostright->leftChild != nullptr)
                delNodeWithOneChild(mostright);
            else
                delLeaf(mostright);
        }
    }
}

// ��������� ��� �������� ���� child ������ ���������
// ���� newChild ������ child (��� ����������� �������� ����)
void BinaryTree::setNewChild(Node* child, Node* newChild = nullptr) {
    Node* parent = child->parent;//��������� �� �������� child
    if (parent != nullptr) {//���� � ��������� ������� ���� ��������
        if (parent->leftChild == child) {//���� ��������� ������� �������� ����� ��������
            parent->leftChild = newChild;
        }
        else {
            parent->rightChild = newChild;//���� �������� ������ ��������
        }
    }
}

// ������� ���� � ����� �������� ����� �� ������
void BinaryTree::delNodeWithOneChild(Node* delNode) {
    if (delNode->leftChild != nullptr) {
        // ���� ����� ����� ����
        if (isRoot(delNode)) {
            root = delNode->leftChild;
        }
        else {
            setNewChild(delNode, delNode->leftChild);
        }
        delNode->leftChild->parent = delNode->parent;
        delNode->leftChild = nullptr;
    }
    else {
        // ���� ������ ����
        if (isRoot(delNode)) {
            root = delNode->rightChild;
        }
        else {
            setNewChild(delNode, delNode->rightChild);
        }
        delNode->rightChild->parent = delNode->parent;
        delNode->rightChild = nullptr;
    }
    // ������� ����
    delete delNode;
}
// ������� ���� �� ������
void BinaryTree::delLeaf(Node* leaf) {
    if (isRoot(leaf)) { // ������, ����� � ������ ����� ���� �������� ����
        // �������� ������
        root = nullptr;
    }
    else {
        // �������� ��������� �� ��������� ���� � ��������
        setNewChild(leaf);
    }
    // ������� �������� ����
    delete leaf;
}
    
