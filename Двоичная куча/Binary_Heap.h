#pragma once
class MinHeap {
	int* harr;//��������� �� ������ ���������
	int capacity;//������������ ������ ����
	int heap_size;//������� ����� ��������� ����
private:
	//�������-��������� ��� ��������� ��������, � ������� �� ������� ����
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
	void MinHeapify(int);//�������������� �������� ���� ��� ��������� � ������ �� �������
	int extractMin();//�������� ����� �� ������
	int getMin() // ��������� ������������ �������� - �����
	{	
		return harr[0];
	}
	MinHeap buildHeap(int* arr, size_t size);
	void insertKey(int k);//������� ����� ��������

};