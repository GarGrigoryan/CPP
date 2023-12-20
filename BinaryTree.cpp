#include <iostream>
#include <Stack>
#include <Queue>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node<T>* left;
	Node<T>* right;
	Node(T data, Node<T>* left = nullptr, Node<T>* right = nullptr):data(data),left(left),right(right){}
};

template <typename T>
class Tree {
private:
	Node<T>* root;
	Node<T>* Search(T, Node<T>*);
	void TraversePreorder(Node<T>*); //uxix
	void TraversePostorder(Node<T>*); //hakadardz
	void TraverseInorder(Node<T>*); //simetrik
public:
	Tree();
	~Tree();
	Tree(const Tree&);
	Node<T>* Copy(Node<T>*);
	bool Search(T);
	void SetRoot(Node<T>*);
	Node<T>* GetRoot();
	void Insert(T);
	void ClearIterative();
	void ClearRecursive(Node<T>*);
	void CleanLeft(Node<T>*);
	void ClearRight(Node<T>*);
	void TraversePreorder();
	void TraversePostorder();
	void TraverseInorder();
	void TraversePreorderIterative();
	void TraversePostorderIterative();
	void TraverseInorderIterative();
	void PrintLevelOrder();
};

template <typename T>
Tree<T>::Tree()
{
	root = nullptr;
}

template <typename T>
Tree<T>::~Tree()
{
	ClearIterative();
	cout << "Tree is deleted" << endl;
}

template <typename T>
Tree<T>::Tree(const Tree& obj)
{
	root = Copy(obj.root);
}

template <typename T>
Node<T>* Tree<T>::Copy(Node<T>* obj)
{
	if (obj == nullptr) {
		return nullptr;
	}
	Node* temp = new Node(obj->data);
	temp->left = Copy(obj->left);
	temp->right = Copy(obj->right);
	return temp;
}

template <typename T>
Node<T>* Tree<T>::Search(T data, Node<T>* temp)
{
	if (temp == NULL) {
		return nullptr;
	}
	if (temp->data == data) {
		return temp;
	}
	Node* temp1 = Search(data, temp->left);
	if (temp1 != nullptr) {
		return temp1;
	}
	return Search(data, temp->right);
}

template <typename T>
bool Tree<T>::Search(T data)
{
	return Search(data, root) != NULL;
}

template <typename T>
void Tree<T>::SetRoot(Node<T>* root1)
{
	root = root1;
}

template <typename T>
Node<T>* Tree<T>::GetRoot() {
	return root;
}

template <typename T>
void Tree<T>::Insert(T data)
{
	if (root == nullptr) {
		root = new Node<T>(data);
		return;
	}
	queue <Node<T>*> Queue;
	Queue.push(root);
	while (!Queue.empty()) {
		Node<T>* temp = Queue.front();
		if (Queue.front()->left == nullptr) {
			Queue.front()->left = new Node<T>(data);
			return;
		}
		else {
			Queue.push(Queue.front()->left);
		}
		if (Queue.front()->right == nullptr) {
			Queue.front()->right = new Node<T>(data);
			return;
		}
		else {
			Queue.push(Queue.front()->right);
		}
		Queue.pop();
	}
}

template <typename T>
void Tree<T>::ClearIterative()
{
	if (root == nullptr) {
		return;
	}
	queue <Node<T>*> Queue;
	Queue.push(root);
	root = nullptr;
	while (!Queue.empty()) {
		if (Queue.front()->left != nullptr) {
			Queue.push(Queue.front()->left);
		}
		if (Queue.front()->right != nullptr) {
			Queue.push(Queue.front()->right);
		}
		Node<T>* temp = Queue.front();
		delete temp;
		Queue.pop();
	}
}

template <typename T>
void Tree<T>::ClearRecursive(Node<T>* temp) {
	if (temp == nullptr) {
		return;
	}
	ClearRecursive(temp->left);
	ClearRecursive(temp->right);
	delete temp;
}

template <typename T>
void Tree<T>::CleanLeft(Node<T>* temp)
{
	if (temp == nullptr || temp->left == nullptr) {
		return;
	}
	ClearRecursive(temp->left);
	temp->left = nullptr;
}

template <typename T>
void Tree<T>::ClearRight(Node<T>* temp)
{
	if (temp == nullptr || temp->right == nullptr) {
		return;
	}
	ClearRecursive(temp->right);
	temp->right = nullptr;
}

template <typename T>
void Tree<T>::TraversePreorder(Node<T>* temp)
{
	if (temp != nullptr) {
		cout << temp->data << ' ';
		TraversePreorder(temp->left);
		TraversePreorder(temp->right);
	}

}

template <typename T>
void Tree<T>::TraversePreorder()
{
	cout << "Traverse preorder" << endl;
	TraversePreorder(root);
	cout << endl;
}

template <typename T>
void Tree<T>::TraversePostorder(Node<T>* temp) {
	if (temp != nullptr) {
		TraversePostorder(temp->left);
		TraversePostorder(temp->right);
		cout << temp->data << ' ';
	}
}

template <typename T>
void Tree<T>::TraversePostorder() {
	cout << "Traverse postorder" << endl;
	TraversePostorder(root);
	cout << endl;
}

template <typename T>
void Tree<T>::TraverseInorder(Node<T>* temp) {
	if (temp != nullptr) {
		TraverseInorder(temp->left);
		cout << temp->data << ' ';
		TraverseInorder(temp->right);
	}
}

template <typename T>
void Tree<T>::TraverseInorder() {
	cout << "Traverse inorder" << endl;
	TraverseInorder(root);
	cout << endl;
}

template <typename T>
void Tree<T>::TraversePreorderIterative()
{
	if (!root) {
		return;
	}
	cout << "Traverse Preorder Iterative" << endl;
	stack<Node<T>*> st;
	st.push(root);
	while (!st.empty()) {
		Node* temp = st.top();
		cout << temp->data << ' ';
		st.pop();
		if (temp->right) {
			st.push(temp->right);
		}
		if (temp->left) {
			st.push(temp->left);
		}
	}
	cout << endl;
}

template <typename T>
void Tree<T>::TraversePostorderIterative()
{
	if (!root) {
		return;
	}
	cout << "Traverse Postorder Iterative" << endl;
	stack<Node<T>*> st;
	stack<int> output;
	st.push(root);
	while (!st.empty()) {
		Node* temp = st.top();
		output.push(temp->data);
		st.pop();
		if (temp->left) {
			st.push(temp->left);
		}
		if (temp->right) {
			st.push(temp->right);
		}
	}
	while (!output.empty()) {
		cout << output.top() << ' ';
		output.pop();
	}
	cout << endl;
}

template <typename T>
void Tree<T>::TraverseInorderIterative()
{
	if (!root) {
		return;
	}
	cout << "Traverse Inorder Iterative" << endl;
	stack<Node<T>*> st;
	Node* temp = root;
	while (temp || !st.empty()) {
		while (temp) {
			st.push(temp);
			temp = temp->left;
		}
		temp = st.top();
		st.pop();
		cout << temp->data << ' ';
		temp = temp->right;
	}
	cout << endl;
}

template <typename T>
void Tree<T>::PrintLevelOrder()
{
	if (root == nullptr) {
		cout << "Tree is empty" << endl;
		return;
	}
	queue <Node<T>*> Queue;
	Queue.push(root);
	while (!Queue.empty()) {
		size_t count = Queue.size();
		while (count > 0) {
			cout << Queue.front()->data << ' ';
			if (Queue.front()->left != nullptr) {
				Queue.push(Queue.front()->left);
			}
			if (Queue.front()->right != nullptr) {
				Queue.push(Queue.front()->right);
			}
			Queue.pop();
			--count;
		}
		cout << endl;
	}
}

int main() {
	Tree<int> dub;
	dub.Insert(1);
	dub.Insert(2);
	dub.Insert(3);
	dub.Insert(4);
	dub.Insert(5);
	dub.Insert(6);
	dub.Insert(7);
	dub.Insert(8);
	/*dub.TraversePreorder();
	dub.TraversePostorder();
	dub.TraverseInorder();
	dub.TraversePreorderIterative();
	dub.TraversePostorderIterative();
	dub.TraverseInorderIterative();*/
	dub.PrintLevelOrder();
}