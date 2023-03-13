#pragma once
#include <string.h>

#define NAMELENGTH 10  // ����������� ����� �����

typedef char FruitName[NAMELENGTH]; // ��� ��� ������

class HashTable { // ���-�������
public:

    HashTable();
    ~HashTable();
    void add(FruitName fr_name, int fr_count);

private:

    enum enPairStatus {
        free, // ��������
        engaged, //�����
        deleted //������
    };

    struct Pair { // ���� ����-��������

        Pair() : // ����������� �� ���������
            fruit_name(""),
            fruit_count(-1),
            status(enPairStatus::free) {

        }
        Pair(FruitName fr_name, int fr_count) : // ����������� �����������
            fruit_count(fr_count),
            status(enPairStatus::engaged) {
            strcpy(fruit_name, fr_name);
        }
        Pair& operator = (const Pair& other) { //  �������� ������������
            fruit_count = other.fruit_count;
            strcpy(fruit_name, other.fruit_name);
            status = other.status;

            return *this;
        }

        FruitName fruit_name; // ��� ������ (����)
        int fruit_count; // ���������� ������ (��������)

        enPairStatus status; // ��������� ������
    };

    int hash_func(FruitName fr_name, int offset);

    Pair* array;
    int mem_size;
    int count;
};

HashTable::HashTable() {
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}
HashTable::~HashTable() {
    delete[] array;
}