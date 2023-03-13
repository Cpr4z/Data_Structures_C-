#pragma once
#include <string.h>

#define NAMELENGTH 10  // Зафиксируем длину имени

typedef char FruitName[NAMELENGTH]; // тип имя фрукта

class HashTable { // хеш-таблица
public:

    HashTable();
    ~HashTable();
    void add(FruitName fr_name, int fr_count);

private:

    enum enPairStatus {
        free, // свободен
        engaged, //занят
        deleted //удален
    };

    struct Pair { // пара ключ-значение

        Pair() : // конструктор по умолчанию
            fruit_name(""),
            fruit_count(-1),
            status(enPairStatus::free) {

        }
        Pair(FruitName fr_name, int fr_count) : // конструктор копирования
            fruit_count(fr_count),
            status(enPairStatus::engaged) {
            strcpy(fruit_name, fr_name);
        }
        Pair& operator = (const Pair& other) { //  оператор присваивания
            fruit_count = other.fruit_count;
            strcpy(fruit_name, other.fruit_name);
            status = other.status;

            return *this;
        }

        FruitName fruit_name; // имя фрукта (ключ)
        int fruit_count; // количество фрукта (значение)

        enPairStatus status; // состояние ячейки
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