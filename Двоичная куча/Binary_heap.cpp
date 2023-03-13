#include "Binary_Heap.h"
#include <iostream>
using namespace std;
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    // ��������� �������� ��� ������ ���������
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;

    // ��������� �������� ��� ������� ���������
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;

    // ���� �� ���������, ����������, � ���������
    // �������� ����� ��� �������, �� ���������������� �������
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

    // ��������� ����������� ��������, � ������� ��� �� ����
    int root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;

    // ��������������� ��������
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
    // ������ ����
    MinHeap h = h.buildHeap(arr, size);
    for (size_t i = 0; i < size; i++)
    {
        // ��������� ������
        arr[i] = h.extractMin();
        // ��������������� ��������
        h.MinHeapify(0);
    }
}