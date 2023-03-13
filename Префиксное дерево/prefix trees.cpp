#include<iostream>
#include "prefix trees.h"
#include <string>

using namespace std;

TrieNode* getNewNode() {//возвращаем узел с путыми детьми
	struct TrieNode* pNode = new TrieNode;//выделяем память под новый узел
	pNode->isEndOfWord = false;//устанавливаем флаг конца слова в false
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
	{
		pNode->children[i] = nullptr;//инициализируем детей нулевым указателем
	}
	return pNode;
}


void insert(TrieNode* root, string key) {
	auto current = root;
	for (int i = 0; i < key.size(); i++)
	{
		if (current->children[key[i] - 'a'] != nullptr) {
			current = current->children[key[i] - 'a'];
		}
		else {
			current->children[key[i]-'a']=getNewNode();
			current = current->children[key[i] - 'a'];

		}
	}
}
bool search(struct TrieNode* root, string key) {
	TrieNode* node = root;
	for (size_t i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!node->children[index])
			return false;
		node = node->children[index];
	}
	return (node != nullptr && node->isEndOfWord);
}
bool isEmpty(TrieNode* root) {
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->children[i])
			return false;
	}
	return true;
}
// Рекурсивная функция удаления ключа из дерева
TrieNode* remove(TrieNode* root, string key, int depth = 0)
{
	// Если дерево пустое
	if (!root)
		return nullptr;
	// Если дошли до конца ключа
	if (depth == key.size()) {
		// Этот узел больше не конец слова
		// поэтому снимаем метку
		if (root->isEndOfWord)
			root->isEndOfWord = false;
		// Если ключ не является префиксом, удаляем его
		if (isEmpty(root)) {
			delete (root);
			root = nullptr;
		}

		return root;
	}

	// Пока не дошли до конца ключа или определили, 
	// что его нет в дереве, рекурсивно вызываем для ребенка
	// соответствующего символа
	int index = key[depth] - 'a';
	root->children[index] = remove(root->children[index], key, depth + 1);
	// Если у корня нет дочернего слова
	// (удален только один его дочерний элемент),
	// и он не заканчивается другим словом.
	if (isEmpty(root) && root->isEndOfWord == false) {
		delete (root);
		root = nullptr;
	}
	// возвращаем новый корень
	return root;
}