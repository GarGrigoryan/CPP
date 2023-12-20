#include <iostream>
using namespace std;

template <typename T>
class Queue {
private:
	T* arr;
	int capacity;
	int front;
	int rear;
	int count;
public:
	Queue(int size = 0);
	~Queue();
	void dequeue();
	void enqueue(int);
	T getFront();
	int size();
	bool isEmpty();
	bool isFull();
};

template<typename T>
Queue<T>::Queue(int size)
{
	arr = new int[size];
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;
}

template<typename T>
Queue<T>::~Queue()
{
	delete[] arr;
}

template<typename T>
void Queue<T>::dequeue()
{
	if (isEmpty())
	{
		cout << "Queue is empty!" << endl;
		return;
	}
	T item = arr[front];
	front = (front + 1) % capacity;
	count--;
	return;
}

template<typename T>
void Queue<T>::enqueue(int item)
{
	if (isFull())
	{
		cout << "Queue is full!" << endl;
	}
	rear = (rear + 1) % capacity;
	arr[rear] = item;
	count++;
	return;
}

template<typename T>
T Queue<T>::getFront()
{
	if (isEmpty())
	{
		cout << "Queue is empty!" << endl;
	}
	return arr[front];
}

template<typename T>
int Queue<T>::size()
{
	return count;
}

template<typename T>
bool Queue<T>::isEmpty()
{
	return count == 0;
}

template<typename T>
bool Queue<T>::isFull()
{
	return count == capacity;
}

int main() {
	Queue<int> myQueue(10);
	for (int i = 0; i < 10; ++i) {
		myQueue.enqueue(i);
	}
	for (int i = 0; i < 10; i++)
	{
		cout << myQueue.getFront() << endl;
		myQueue.dequeue();
	}
	
}
