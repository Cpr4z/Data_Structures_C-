#include "AVL.h"
#include <iostream>
#include <queue>
#include <stack>


size_t AVL::height(Node* node) {
	return node ? node->height : 0;
}
int AVL::bfactor(Node* node) {
	return height(node->right) - height(node->left);
}
void AVL::fix_height(Node* node) {
	size_t h_left = height(node->left);
	size_t h_right = height(node->right);
	node->height = (h_left > h_right ? h_left : h_right) + 1;
}
AVL::Node* AVL::rotateRight(Node* node) 
{
	Node* q = node->left;
	node->left = q->left;
	q->right = node;
	fix_height(node);
	fix_height(q);

	return q;
}
AVL::Node* AVL::rotateLeft(Node* node) {
	Node* q = node->right;
	node->left = q->left;
	q->right = node;
	fix_height(node);
	fix_height(q);

	return q;
}
AVL::Node* AVL::balance(Node* const node) {
	fix_height(node);
	if (bfactor(node) == 2) {
		if (bfactor(node->right) < 0)
			node->right = rotateRight(node->right);
		return rotateLeft(node);
	}
	if (bfactor(node) == -2) {
		if (bfactor(node->left) > 0)
			node->right = rotateLeft(node->left);
		return rotateRight(node);
	}
	return node;
}
const AVL::Node* AVL::bfs(const int& key)const
{
	if (AVL::_root == nullptr) //если в дереве нет элементов 
		return nullptr;

	std::queue<Node*> q;//создаем очередь

	q.push(_root);//добавляем в очередь корневой элемент

	while (q.empty() == false)//пока в очереди есть элементы
	{
		Node* node = q.front();//берем первый элемент из очереди
		q.pop();//удаляем первый элемент очереди
		if (node->key == key)//если находим node с нужным нам key то возвращаем указатель 
			return node;
		if (node->left != nullptr)//если левый ребенок не равен nullptr, то добавляем его в очередь
			q.push(node->left);
		if (node->right != nullptr)//аналогично
			q.push(node->right);

	}
}
const AVL::Node* AVL::dfs( const int& key)
{
	Node* current = _root;
	dfs(current, key);
	return nullptr;
}
AVL::Node* AVL::dfs(Node* current,const int& key) 
{
	if (current->key == key) {
		return current;
	}
	else if (current->left != nullptr)
	{
		current = current->left;
		dfs(current,key);
	}
	else {
		current = current->right;
		dfs(current, key);
	}	
}
	void AVL::insert(int&& key) 
	{
		Node* node = new Node(key);
		_root = insert(AVL::_root,node);

	}
	AVL::Node* AVL::insert(Node* root, Node* const node)
	{
		if (!root)//если 
			return node;
		if (node->key < root->key)//если ключ вставляемого значения меньше, чем корень, то двигемся по левому поддереву 
			root->left = insert(root->left, node);
		else
			root->right = insert(root->right, node);//если наоборот, то двигаемся по правому дереву

		return balance(root);
	}
	AVL:: Node* AVL::removemin(Node* node)
	{
		if (!node->left)
			return node->right;

		node->left = removemin(node->left);

		return balance(node);
	}

	// поиск узла с минимальным ключом в дереве
	// всегда будет в левом поддереве, из-за условия построения bst

	AVL::Node* AVL::findmin(Node* node)//нахождение минимального элемента
	{
		return node->left ? findmin(node->left) : node;
	}

	void AVL::delete_node(const int& key)//удаление элемента
	{
		_root = delete_node(_root, key);
	}

	AVL::Node* AVL::delete_node(Node* node, const int& key)
	{
		if (!node)
			return 0;

		if (key < node->key)
			node->left = delete_node(node->left, key);
		else if (key > node->key)
			node->right = delete_node(node->right, key);
		else //  k == p->key
		{
			Node* q = node->left;
			Node* r = node->right;
			delete node;

			if (!r)
				return q;

			Node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}

		return balance(node);
	}
	const AVL::Node* dfs(const AVL::Node* node, int& key) 
	{
		if (node->key == key)
		{
			return node;
		}
		else if (node->key < key)
		{
			dfs(node->right, key);
		}
		else if (node ->key > key) 
		{
			dfs(node->left, key);
		}
		return nullptr;
	}
	int main() {
		
		return 0;
	}




















