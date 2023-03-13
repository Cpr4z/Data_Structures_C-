#include "Tree.h"
#include <iostream>



void Tree::delNode(int number) //метод удаления нужной Node
{
	Node* DelNode =getNodeByNumber(number, root);//находим нужную Node
	if (DelNode == nullptr)//nullptr если не находим нужную Node
		return;

	delChild(DelNode);
	return;
}

void Tree::delChild(Node* child)//метод присвоения детей удаленной вершнины родителю для удаленной вершины
{
	Node* parentNode = child->parent;

	if (parentNode->childCount == 1)//у родительской вершины только один ребенок
	{
		if (child->childCount == 0) {//если у удаляемой вершины нет детей, то просто удаляем вершину
			parentNode->childCount = (parentNode->childCount) - 1;
			delete child;
			return;
		}
		if (child->childCount == 1)//если у удалеяемой Node 1 ребенок
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



	else //если у родительской Node есть 2 ребенка
	{
		if (child->childCount == 0) //у удаляемой Node есть 0 детей
		{
			parentNode->childCount = (parentNode->childCount) - 1;

			delete child;
			return;
		}
		else if (child->childCount == 1)// у удалемой Node усть 1 ребенок
		{
			parentNode->children[0] = child->children[0];
			delete child;
			return;
		}
		else //у удаляемой Node есть 2 ребенка
		{
			if (child->children[0] <= child->children[1]) //если левый ребенок меньше, то удаляем его
			{
				delChild(child->children[0]);
				delete child;
			}
			else //если правый ребенок меньше, то удаляем его
			{
				delChild(child->children[1]);
				delete child;
			}
		}
	}











