#include <string.h>

#define NAMELENGTH 10  // Зафиксируем длину имени

typedef char FruitName[NAMELENGTH]; // тип имя фрукта

class HashTable { // Хеш-таблица

public:

    HashTable();
    ~HashTable();
    void add(FruitName fr_name, int fr_count);
    void del(FruitName fr_name);
    int find(FruitName fr_name);
    void print(FruitName fr_name);

private:
    struct ChainNode { // узел в списке
        FruitName fruit_name; // ключ
        int fruit_count; // значение

        ChainNode* next; // указатель на следующий узел в списке
        ChainNode(FruitName _fn, int _fc) :
            fruit_count(_fc) {
            strcpy(fruit_name, _fn);
            next = nullptr;
        }
        ~ChainNode() {
            if (next != nullptr)
                delete next;
        }
    };
    int hash_func(FruitName fr_name); // хеш-функция для поиска индекса

    ChainNode** chain_tops; // массив указателей на списки
    int mem_size; // количество выделенной памяти
    int count; // количество добавленных пар ключ-значение

};