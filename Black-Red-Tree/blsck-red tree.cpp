#include <iostream>
#include "black-red tree.h"

void RBTree::insert(int key)
{
    Node* z = new Node(key);
    insert(root, z);
};

RBTree::Node* RBTree::search(int key)
{
    return search(RBTree::root, key);
}   

RBTree::Node* RBTree::search(RBTree::Node* node, int key) const
{
    if (node == nullptr || node->key == key)
        return node;
    else
        if (key > node->key)
            return search(node->right, key);
        else
            return search(node->left, key);
}

void RBTree::insert(Node* root, Node* node)
{
    Node* currentNode = root;
    Node* parentNode = nullptr;

    while (currentNode != nullptr)//���� ������� ������� �� ����� ������
    {
        parentNode = currentNode;
        if (node->key > currentNode->key)//���� ���� ����������� Node ������ ��� ���� ������� Node,�� ��������� � ������ �������
            currentNode = currentNode->right;
        else
            currentNode = currentNode->left;//���� ��������, �� � �����
    }
    node->parent = parentNode;//����������� ����������� Node � �������� �������� ������� Node

    if (parentNode != nullptr)//
    {
        if (node->key > parentNode->key)
            parentNode->right = node;
        else
            parentNode->left = node;
    }
    else
        root = node;

    node->color = Red;
    InsertFixUp(root, node);
};
void RBTree::InsertFixUp(Node*& root, Node* node) {
    Node* parent;
    parent = node->parent;
    while (node != RBTree::root && parent->color == Red)
    {
        Node* gparent = parent->parent;
        if (gparent->left == parent)
        {
            Node* uncle = gparent->right;
            if (uncle != nullptr && uncle->color == Red)
                // block 2
            {
                parent->color = Black;
                uncle->color = Black;
                gparent->color = Red;
                node = gparent;
                parent = node->parent;
            }
            // block 3
            else
                // block 4
            {
                if (parent->right == node)
                {
                    leftRotate(root, parent);
                    swap(node, parent);
                }
                rightRotate(root, gparent);
                gparent->color = Red;
                parent->color = Black;
                break;
            }
            // block 5
        }
        else
        {
            Node* uncle = gparent->left;
            if (uncle != nullptr && uncle->color == Red)
                // block 6
            {
                gparent->color = Red;
                parent->color = Black;
                uncle->color = Black;

                node = gparent;
                parent = node->parent;
            }
            // block 7
            else
                // block 8
            {
                if (parent->left == node)
                {
                    rightRotate(root, parent);
                    swap(parent, node);
                }
                leftRotate(root, gparent);
                parent->color = Black;
                gparent->color = Red;
                break;
            }
            // block 9
        }
    }
    root->color = Black;
}
}
void RBTree::remove(int key)
{
    Node* deletenode = search(root, key);
    if (deletenode != nullptr)
        remove(root, deletenode);
}

void RBTree::remove(Node*& root, Node* node)
{
    Node* child;
    Node* parent;
    Color color;
    // ���� ����� � ������ �� ���������� ���� �� ����
    if (node->left != nullptr && node->right != nullptr)
    {
        Node* replace = node;
        // ������� ����-�������� (����� ������ ���� ������� ��������� �������� ����)
        replace = node->right;
        while (replace->left != nullptr)
        {
            replace = replace->left;
        }

        // ��������� ���� �� �������� ������
        if (node->parent != nullptr)
        {
            if (node->parent->left == node)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        }
        else
            root = replace;
        // ��������� ������ ��������� ����������� �������� � ����
        child = replace->right;
        parent = replace->parent;
        color = replace->color;

        // ���� ���������� ������������ ����� ������
        if (parent == node)
            parent = replace;
        else
        {
            // ���� �������� ����
            if (child != nullptr)
                child->parent = parent;
            parent->left = child;

            replace->right = node->right;
            node->right->parent = replace;
        }
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;
        if (color == Black)
            removeFixUp(root, child, parent);

        delete node;
        return;
    }
    // ����� ��������� ���� ����� ������ ����� (������) ����, ������� �������� ���� ���������� ����
    if (node->left != nullptr)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    color = node->color;
    if (child)
    {
        child->parent = parent;
    }
    // ��������� ���� �� ������
    if (parent)
    {
        if (node == parent->left)
            parent->left = child;
        else
            parent->right = child;
    }
    // ��������� ���� - ������
    else
        RBTree::root = child;

    if (color == Black && root)
    {
        removeFixUp(root, child, parent);
    }
    delete node;

}
