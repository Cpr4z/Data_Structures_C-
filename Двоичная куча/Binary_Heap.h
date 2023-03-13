#pragma once
class MinHeap {
	int* harr;//указатель на массив жлементов
	int capacity;//максимальный размер кучи
	int heap_size;//текущее число элементов кучи
private:
	//функции-помощники для получения родителя, и сыновей по индексу узла
	int parent(int i)
	{
		return (i - 1) / 2;
	}
	int left(int i)
	{

		return (2 * i + 1);
	}
	int right(int i)
	{
		return (2 * i + 2);
	}
public:
	MinHeap(int capacity);
	void MinHeapify(int);//восстановление свойства кучи для поддерева с корнем по индексу
	int extractMin();//удаление корня из дерева
	int getMin() // Получение минимального элемента - корня
	{	
		return harr[0];
	}
	MinHeap buildHeap(int* arr, size_t size);
	void insertKey(int k);//вставка новго элемента

};