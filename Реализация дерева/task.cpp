#include "Tree.h"
#include <iostream>



void Tree::delNode(int number) //����� �������� ������ Node
{
	Node* DelNode =getNodeByNumber(number, root);//������� ������ Node
	if (DelNode == nullptr)//nullptr ���� �� ������� ������ Node
		return;

	delChild(DelNode);
	return;
}

void Tree::delChild(Node* child)//����� ���������� ����� ��������� �������� �������� ��� ��������� �������
{
	Node* parentNode = child->parent;

	if (parentNode->childCount == 1)//� ������������ ������� ������ ���� �������
	{
		if (child->childCount == 0) {//���� � ��������� ������� ��� �����, �� ������ ������� �������
			parentNode->childCount = (parentNode->childCount) - 1;
			delete child;
			return;
		}
		if (child->childCount == 1)//���� � ���������� Node 1 �������
		{
			parentNode->children[0] = child->children[0];
			delete child;
			return;
		}
		else {
			parentNode->childCount = (parentNode->childCount) + 1;
			parentNode->children[0] = child->children[0];
			parentNode->children[1] = child->children[1];
			delete child;
			return;
		}
	}



	else //���� � ������������ Node ���� 2 �������
	{
		if (child->childCount == 0) //� ��������� Node ���� 0 �����
		{
			parentNode->childCount = (parentNode->childCount) - 1;

			delete child;
			return;
		}
		else if (child->childCount == 1)// � �������� Node ���� 1 �������
		{
			parentNode->children[0] = child->children[0];
			delete child;
			return;
		}
		else //� ��������� Node ���� 2 �������
		{
			if (child->children[0] <= child->children[1]) //���� ����� ������� ������, �� ������� ���
			{
				delChild(child->children[0]);
				delete child;
			}
			else //���� ������ ������� ������, �� ������� ���
			{
				delChild(child->children[1]);
				delete child;
			}
		}
	}











