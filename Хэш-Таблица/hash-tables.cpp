#include"hash_tables.h"
#include <string.h>
#include <iostream>

#define NAMELENGHT 10



HashTable::HashTable()//выделение памяти, инициализация
{
    mem_size = 8;
    chain_tops = new ChainNode * [mem_size];
    for (size_t i = 0; i < mem_size; i++)
    {
        chain_tops[i] = nullptr;
    }
    count = 0;
}
HashTable::~HashTable()//прибираем за собой
{
    for (size_t i = 0; i < mem_size; i++)
    
        if (chain_tops != nullptr)
            delete chain_tops[i];
    delete[] chain_tops;
    
}
int HashTable::hash_func(FruitName fr_name)
{
    int sum = 0, i = 0;
    for (; i < strlen(fr_name); i++) {
        sum += fr_name[i];
    }
    return sum % mem_size;
}
void HashTable::add(FruitName fr_name, int fr_count)
{
    int index = hash_func(fr_name);
    if (chain_tops[index] != nullptr) {
        ChainNode* newNode = new ChainNode(fr_name, fr_count);
        newNode->next = chain_tops[index];
        chain_tops[index] = newNode;
    }
    else {
        chain_tops[index] = new ChainNode(fr_name, fr_count);
    }
    count++;
}

void HashTable::del(FruitName fr_name) {
    int index = hash_func(fr_name);
    if (!strcmp(chain_tops[index]->fruit_name, fr_name)) {
        ChainNode* tmpNode = chain_tops[index];
        chain_tops[index] = chain_tops[index]->next;
        delete tmpNode;
        count--;
        return;
    }

    ChainNode* currNode = chain_tops[index]->next;
    ChainNode* prevNode = nullptr;
    while (currNode != nullptr) {
        if (!strcmp(currNode->fruit_name, fr_name)) {
            prevNode->next = currNode->next;
            delete currNode;
            count--;
        }
        prevNode = currNode;
        currNode = currNode->next;

    }
}
int HashTable::find(FruitName fr_name) {
    int index = hash_func(fr_name);
    if (chain_tops[index] != nullptr) {
        ChainNode* currNode = chain_tops[index];
        while (currNode != nullptr) {
            if (!strcmp(currNode->fruit_name, fr_name))
                return currNode->fruit_count;
            currNode = currNode->next;
        }
    }
    return -1;
}
void HashTable::print(FruitName fr_name)
{
    int index = hash_func(fr_name);
    if (chain_tops[index] != nullptr) {
        std::cout << chain_tops[index] << std::endl;
        return;
    }
    else {
        std::cout << "This object don't exists" << std::endl;
        return;
    }
}