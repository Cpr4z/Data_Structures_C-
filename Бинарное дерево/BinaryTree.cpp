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
			if (current->data >= newData) {//если текущее число в Node больше чем новое число то идем по левой ветке
				
				if (current->leftChild != 0) {//если левый ребенок текущего элемента не пустой, то присваеваием текущему элементу левого ребенка
					current = current->leftChild;
					continue;
				}
				newNode = new Node(newData, current);//если нет левого ребенка, то создаем новую Node
				current->leftChild = newNode;
			}
			else//идем по правой ветке
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
    while (curr)//пока указатель на текущий элемент не равен nullptr
    {
        if (curr->data == finddata)//если текущее значение равно тому значению, которое ищем
        {
            return curr;
        }
        if (curr->data > finddata)//если текущее значение больше чем то значение, которое ищем, то идем в левое поддерево
        {
            curr = curr->leftChild;
        }
        else//если меньше, то идем в правое поддерево
        {
            curr = curr->rightChild;
        }
    }
    return nullptr;//если элемента нет, то возвращаем nullptr
}
// удаление элемента
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
	if (U->parent == nullptr) {//если мы удаляем корень, тогда мы назначаем перемещаемый элемент корнем дерева
		root = V;
	}
	else if (U == U->parent->leftChild){//если удаляемая вершина является левым ребенком 
		U->parent->leftChild = V;
	}
	else {//если удаляемая вершина является правым ребенком своего родителя
		U->parent->rightChild = V;
	}
	if (V != nullptr)
		V->parent = U->parent;
}
void BinaryTree::delInt(int deldata) {
    Node* foundForDel = findNodeByData(deldata);
    if (foundForDel == nullptr)
        return; // такого целого числа нет в дереве
    // такое целое есть
    if (isLeaf(foundForDel)) { // если это лист, просто удалим его
        delLeaf(foundForDel);
    }
    else {
        // если не лист, то удаление сложнее
        if (foundForDel->leftChild == nullptr || foundForDel->rightChild == nullptr) {
            // случай, когда у узла только один дочерний
            delNodeWithOneChild(foundForDel);
        }
        else {
            // ищем правый элемент левого поддерева
            Node* mostright = foundForDel->leftChild;
            while (mostright->rightChild != nullptr)
                mostright = mostright->rightChild;

            // записали данные из правого вместо данных в удаляемом узле  
            foundForDel->data = mostright->data;

            // удалили правый элемент (он может содержать только левый узел)
            if (mostright->leftChild != nullptr)
                delNodeWithOneChild(mostright);
            else
                delLeaf(mostright);
        }
    }
}

// установка для родителя узла child нового дочернего
// узла newChild вместо child (для дальнейшего удаления узла)
void BinaryTree::setNewChild(Node* child, Node* newChild = nullptr) {
    Node* parent = child->parent;//указатель на родителя child
    if (parent != nullptr) {//если у удаляемой вершины есть родитель
        if (parent->leftChild == child) {//если удаялемая вершина является левым ребенком
            parent->leftChild = newChild;
        }
        else {
            parent->rightChild = newChild;//если является правым ребенком
        }
    }
}

// удалить узел с одним дочерним узлом из дерева
void BinaryTree::delNodeWithOneChild(Node* delNode) {
    if (delNode->leftChild != nullptr) {
        // если имеет левый узел
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
        // если правый узел
        if (isRoot(delNode)) {
            root = delNode->rightChild;
        }
        else {
            setNewChild(delNode, delNode->rightChild);
        }
        delNode->rightChild->parent = delNode->parent;
        delNode->rightChild = nullptr;
    }
    // удаляем узел
    delete delNode;
}
// удалить лист из дерева
void BinaryTree::delLeaf(Node* leaf) {
    if (isRoot(leaf)) { // случай, когда в дереве всего один корневой узел
        // забываем корень
        root = nullptr;
    }
    else {
        // обнуляем указатель на удаляемый узел у родителя
        setNewChild(leaf);
    }
    // удаляем листовой узел
    delete leaf;
}
    
