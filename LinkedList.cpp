#include <iostream>
using namespace std;
template <typename T>
struct Node {
	Node<T>* next;
	T data;
	Node(T data) {
		this->data = data;
		next = NULL;
	}
};

template <typename T>
class List {
private:
	Node<T>* head;
	int size;
public:
	List() {
		head = NULL;
		size = 0;
	}
	void insert_item(T data) {
		Node<T>* new_node = new Node<T>(data);
		size++;
		if (head == NULL) {
			head = new_node;
			return;
		}
		Node<T>* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new_node;
		return;
	}
	void insert_item_at(int index, T data) {
		Node<T>* new_node = new Node<T>(data);
		if (index > size) {
			cout<< "Index bigger than size" << endl;
		}
		Node<T>* temp = head;
		if (index == 0) {
			new_node->next = head;
			head = new_node;
			size++;
			return;
		}
		for (int i = 1; i < index; i++) {
			temp = temp->next;
		}
		new_node->next = temp->next;
		temp->next = new_node;
		size++;
		return;
	}
	void delete_item(int index) {
		if (head == NULL) {
			cout << "The list is empty." << endl;
			return;
		}
		if (index >= size) {
			cout << "Index is incorrect." << endl;
			return;
		}
		Node<T>* temp = head;
		if (index == 0) {
			head = head->next;
			delete temp;
			size--;
			return;
		}
		for (int i = 1; i < index; i++) {
			temp = temp->next;
		}
		Node<T>* temp2 = temp->next;
		temp->next = temp2->next;
		delete temp2;
		--size;
	}
	void print() {
		Node<T>* temp = head;
		while (temp != NULL) {
			cout <<temp->data << " ";
			temp = temp->next;
		}
		cout << endl<<endl;
		return;
	}
	int get_length() {
		return size;
	}
	List(const List& obj) {
		size = obj.size;
		if (obj.head == NULL) {
			head = NULL;
			return;
		}
		head = new Node<T>(obj.head->data);
		Node<T>* temp = head;
		Node<T>* obj_temp = obj.head;
		while (obj_temp->next != NULL) {
			temp->next = new Node<T>(obj_temp->next->data);
			obj_temp = obj_temp->next;
			temp = temp->next;
		}
	}
	~List() {
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
	List<double> list;
	int n, k;
	cout << "n = ";
	cin >> n;
	cout << endl;
	for (int i = 1; i <= n; i++)
	{
		list.insert_item(1.7);
	}
	list.print();
	List<double> list2 = list;
	cout <<"Size = "<< list.get_length() << endl;
	list.delete_item(1);
	list.print();
	cout << "Size = " << list.get_length() << endl;
	list.insert_item_at(n-2, 35);
	list.print();
	cout <<"Size = "<< list.get_length() << endl;
	list2.print();
	return 0;
}