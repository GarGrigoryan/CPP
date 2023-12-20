#include <iostream>
using namespace std;
template <class T>
struct Node {
	Node<T>* previous;
	Node<T>* next;
	T data_;
	Node(T data = 0):data_(data),previous(NULL),next(NULL) {}
};

template <class T>
class DoubleList {
private:
	Node<T>* head;
	Node<T>*last;
	int size;
public:
	DoubleList() :head(NULL),last(NULL), size(0) {};
	void insertItem(T data) {
		Node<T>* new_node = new Node<T>(data);
		size++;
		if (head == NULL) {
			head = new_node;
			last = new_node;
			return;
		}
		Node<T>* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new_node;
		new_node->previous =  temp;
		last = new_node;
		return;
	}
	void insertItemAt(int index, T data) {
		if (index > size) {
			cout << "Index is greater than the size ! " << endl;
			return;
		}
		if (index < 0) {
			cout << "Invalid index ! " << endl;
			return;
		}
		if (index == size) {
			insertItem(data);
			return;
		}
		size++;
		Node<T>* new_node = new Node<T>(data);
		if (index == 0) {
			new_node->next = head;
			head->previous = new_node;
			head = new_node;
			return;
		}
		if (index < size / 2) {
			Node<T>* temp = head;
			for (int i = 1; i < index; i++) {
				temp = temp->next;
			}
			new_node->next = temp->next;
			new_node->previous = temp;
			temp->next = new_node;
			new_node->next->previous = new_node;
			return;
		}
		if (index >= size / 2) {
			Node<T>* temp = last;
			for (int i = 0; i < size - index - 2; ++i)
			{
				temp = temp->previous;
			}
			new_node->previous = temp->previous;
			new_node->next = temp;
			temp->previous = new_node;
			new_node->previous->next = new_node;
		}
	}
	void deleteItem(int index) {
		if (index > size) {
			cout << "Index is greater than the size ! " << endl;
			return;
		}
		if (head == NULL) {
			cout << "List is empty ! " << endl;
			return;
		}
		if (index < 0) {
			cout << "Invalid index !" << endl;
		}
		size--;
		if (index == 0) {
			Node<T>* temp = head;
			head = head->next;
			head->previous = NULL;
			delete temp;
			return;
		}
		if (index == size) {
			Node<T>* temp = last;
			last = last->previous;
			last->next = NULL;
			delete temp;
			return;
		}
		if (index < size / 2) {
			Node<T>* temp = head;
			for (int i = 0; i < index; i++) {
				temp = temp->next;
			}
			temp->previous->next = temp->next;
			temp->next->previous = temp->previous;
			delete temp;
			return;
		}
		if (index >= size / 2) {
			Node<T>* temp = last;
			for (int i = 0; i < size - index; i++) {
				temp = temp->previous;
			}
			temp->next->previous = temp->previous;
			temp->previous->next = temp->next;
			delete temp;
			return;
		}
	}
	void printFromBeginning() {
		if (head == NULL) {
			cout << "List is empty ! " << endl;
			return;
		}
		Node<T>* temp = head;
		while (temp != NULL) {
			cout << temp->data_ << " ";
			temp = temp->next;
		}
		cout << endl;
		return;
	}
	void printFromEnd() {
		if (last == NULL) {
			cout << "List is empty!" << endl;
			return;
		}
		Node<T>* temp = last;
		while (temp != NULL) {
			cout << temp->data_ << " ";
			temp = temp->previous;
		}
		cout << endl;
		return;
	}
	int getSize() { return size; }

	DoubleList(const DoubleList& obj) {
		size = obj.size;
		if (obj.head == NULL) {
			head = NULL;
			last = NULL;
			return;
		}
		head = new Node<T>(obj.head->data_);
		Node<T>* temp = head;
		Node<T>* obj_temp = obj.head;
		while (obj_temp->next != NULL) {
			temp->next = new Node<T>(obj_temp->next->data_);
			temp->next->previous = temp;
			obj_temp = obj_temp->next;
			temp = temp->next;
		}
		last = temp;
		return;
	}
	~DoubleList() {
		Node<T>* temp;
		while (head) {
			temp = head;
			head = temp->next;
			delete temp;
		}
		size = 0;
	}
};

int main() {
	DoubleList<int> list;
	for (int i = 0; i < 10; i++)
	{
		list.insertItem(i * 10);
	}
	DoubleList<int> list2 = list;
	list.printFromBeginning();
	cout << "size = " << list.getSize() << endl;
	list.printFromEnd();
	cout << "size = " << list.getSize() << endl;
	list.insertItemAt(7, 35);
	list.printFromBeginning();
	cout << "size = " << list.getSize() << endl;
	list.printFromEnd();
	cout << "size = " << list.getSize() << endl;
	list.deleteItem(8);
	list.printFromBeginning();
	list.printFromEnd();
	cout << "size = " << list.getSize() << endl;
	cout << "////////////////////////////////" << endl;
	list2.printFromBeginning();
	list2.printFromEnd();
	return 0;
}