#include "Binary_Heap.h"
#include <iostream>
using namespace std;
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    // провер€ем свойство дл€ левого поддерева
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;

    // провер€ем свойство дл€ правого поддерева
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;

    // если не выполнено, обмениваем, с родителем
    // вызываем снова дл€ индекса, не удовлетвор€ющего условию
    if (smallest != i)
    {
        std::swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

int MinHeap::extractMin()
{
    if (heap_size <= 0)
        return INT_MAX;

    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    // —охран€ем минимальное значение, и удал€ем его из кучи
    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;

    // ¬осстанавливаем свойство
    MinHeapify(0);
    return root;
}

MinHeap MinHeap::buildHeap(int* arr, size_t size)
{
    MinHeap h(size);
    h.heap_size = size;
    copy(arr, arr + size, h.harr);
    for (int i = size / 2; i >= 0; i--)
    {
        h.MinHeapify(i);
    }

    return h;
}

void heapSort(int*& arr, size_t size)
{
    // —троим кучу
    MinHeap h = h.buildHeap(arr, size);
    for (size_t i = 0; i < size; i++)
    {
        // »звлекаем корень
        arr[i] = h.extractMin();
        // ¬осстанавливаем свойство
        h.MinHeapify(0);
    }
}