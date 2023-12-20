#include <iostream> 
using namespace std;

template <typename T>
struct Node {
	T data;
	Node<T>* ptr;
	Node(T data = 0):data(data),ptr(NULL) {}
};

template <typename T>
class Stack {
private:
	size_t size;
	Node<T>* top;
public:
	Stack() :size(0), top(nullptr) {};
	void Push(T data) {
		Node<T>* new_node = new Node<T>(data);
		new_node->ptr = top;
		top = new_node;
		size++;
	}
	void Print() {
		if (top == NULL) {
			cout << "Stack is empty !";
		}
		Node<T>* temp = top;
		while (temp != NULL) {
			cout << temp->data << endl;
			temp = temp->ptr;
		}
		cout << endl;
	}
	void Pop() {
		if (top == NULL) {
			cout << "Stack is empty !";
			return;
		}
		Node<T>* temp = top;
		top = top->ptr;
		delete temp;
	}
	T getData() {
		return top->data;
	}
	bool isEmpty() {
		return size == 0;
	}
	~Stack() {
		Node<T>* temp = top;
		while (temp != NULL){
			delete temp;
			temp = temp->ptr;
		}
	}
	Stack(const Stack& obj) {
		size = obj.size;
		if (size == 0) {
			return;
		}
		Node<T>* temp = obj.top;
		top = new Node<T>(temp->data);
		Node<T>* temp_this = top;
		temp = temp->ptr;
		while (temp != NULL) {
			temp_this->ptr = new Node<T>(temp->data);
			temp = temp->ptr;
			temp_this = temp_this->ptr;
		}
	}
};

int main() {
	Stack<int> stack;
	stack.Push(3);
	stack.Push(5);
	stack.Push(7);
	Stack<int> stack2 = stack;
	stack.Print();
	stack.Pop();
	stack.Push(10);
	stack.Print();
	stack2.Print();
	return 0;
}