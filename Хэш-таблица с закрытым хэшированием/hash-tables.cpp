#include"hash-tables closed.h"

int HashTable::hash_func(FruitName fr_name,int offset)
{
	int sum = 0,i=0;
	for (;  i<strlen(fr_name); i++)
	{
		sum += fr_name[i];
	}
	return (sum % mem_size + offset) % mem_size;

}
void HashTable::add(FruitName fr_name, int fr_count) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(fr_name, i);
        if (array[index].status != enPairStatus::engaged) {
            // найдена пуста€ €чейка, занимаем ее
            break;
        }
    }
    if (i >= mem_size) return; // все перебрали, нет места

    // кладем в свободную €чейку пару
    array[index] = Pair(fr_name, fr_count);
    count++;
}
