#include<iostream>
#include "prefix trees.h"
#include <string>

using namespace std;

TrieNode* getNewNode() {//���������� ���� � ������ ������
	struct TrieNode* pNode = new TrieNode;//�������� ������ ��� ����� ����
	pNode->isEndOfWord = false;//������������� ���� ����� ����� � false
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
	{
		pNode->children[i] = nullptr;//�������������� ����� ������� ����������
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
// ����������� ������� �������� ����� �� ������
TrieNode* remove(TrieNode* root, string key, int depth = 0)
{
	// ���� ������ ������
	if (!root)
		return nullptr;
	// ���� ����� �� ����� �����
	if (depth == key.size()) {
		// ���� ���� ������ �� ����� �����
		// ������� ������� �����
		if (root->isEndOfWord)
			root->isEndOfWord = false;
		// ���� ���� �� �������� ���������, ������� ���
		if (isEmpty(root)) {
			delete (root);
			root = nullptr;
		}

		return root;
	}

	// ���� �� ����� �� ����� ����� ��� ����������, 
	// ��� ��� ��� � ������, ���������� �������� ��� �������
	// ���������������� �������
	int index = key[depth] - 'a';
	root->children[index] = remove(root->children[index], key, depth + 1);
	// ���� � ����� ��� ��������� �����
	// (������ ������ ���� ��� �������� �������),
	// � �� �� ������������� ������ ������.
	if (isEmpty(root) && root->isEndOfWord == false) {
		delete (root);
		root = nullptr;
	}
	// ���������� ����� ������
	return root;
}