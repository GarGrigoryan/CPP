#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template <typename T>
struct Node {
	T data;
	int level;
	Node<T>* left;
	Node<T>* right;
	Node(T data, int level = -1, Node<T>* left = nullptr, Node<T>* right = nullptr) :data(data), left(left), right(right),level(level){}
};

template <typename T>
class BinarySearchTree {
private:
	Node<T>* root;
	Node<T>* Insert(Node<T>*, T);
	Node<T>* Find(Node<T>*, T);
	Node<T>* Delete(Node<T>*, T);
	int CountTwoChild(Node<T>*);
	void DeleteLeaves(Node<T>*&);
	int CountHeightRecursive(Node<T>*);
public:
	BinarySearchTree();
	~BinarySearchTree();
	void Insert(T);
	void InsertIterativeLevel(T);
	void PrintLevelOrder();
	bool Find(T);
	void Delete(T);
	int CountTwoChild();
	int CountTwoChildIterative();
	void DeleteLeaves();
	void DeleteLeavesIterative();
	void ClearRecursive(Node<T>*);
	int CountHeightRecursive();
	int CountHeightIterative();
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree() {
	root = nullptr;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	ClearRecursive(root);
	root = nullptr;
	cout << "Tree is deleted" << endl;
}

template <typename T>
Node<T>* BinarySearchTree<T>::Insert(Node<T>* obj, T value) {
	if (obj == nullptr) {
		return new Node<T>(value);
	}
	if (value < obj->data) {
		obj->left = Insert(obj->left, value);
	}
	if (value > obj->data) {
		obj->right = Insert(obj->right, value);
	}
	return obj;
}

template<typename T>
void BinarySearchTree<T>::InsertIterativeLevel(T data)
{
	if (root == nullptr) {
		root = new Node<T>(data, 0);
		return;
	}
	queue <Node<T>*> q;
	q.push(root);
	while (!q.empty()) {
		Node<T>* temp = q.front();
		if (temp->left != nullptr) {
			temp->left = new Node<T>(data, temp->level + 1);
			break;
		}
		else {
			q.push(temp->left);
		}
		if (temp->right != nullptr) {
			temp->right = new Node<T>(data, temp->level + 1);
			break;
		}
		else {
			q.push(temp->right);
		}
		q.pop();
	}
}

template <typename T>
void BinarySearchTree<T>::Insert(T value) {
	root = Insert(root, value);
}

template <typename T>
void BinarySearchTree<T>::PrintLevelOrder() {
	if (root == nullptr) {
		cout << "Tree is empty" << endl;
		return;
	}
	queue <Node<T>*> q;
	q.push(root);
	while (!q.empty()) {
		size_t count = q.size();
		while (count > 0) {
			cout << q.front()->data << ' ';
			if (q.front()->left != nullptr) {
				q.push(q.front()->left);
			}
			if (q.front()->right != nullptr) {
				q.push(q.front()->right);
			}
			q.pop();
			--count;
		}
		cout << endl;
	}
}

template<typename T>
Node<T>* BinarySearchTree<T>::Find(Node<T>* obj, T data) {
	if (obj == nullptr || obj->data == data) {
		return obj;
	}
	if (data > obj->data) {
		return Find(obj->right, data);
	}
	else {
		return Find(obj->left, data);
	}
}

template <typename T>
bool BinarySearchTree<T>::Find(T data) {
	return Find(root, data) != 0;
}

template <typename T>
Node<T>* BinarySearchTree<T>::Delete(Node<T>* obj, T data) {
	if (obj == nullptr) {
		return obj;
	}
	if (data > obj->data) {
		obj->right = Delete(obj->right, data);
	}
	else if (data < obj->data) {
		obj->left = Delete(obj->left, data);
	}
	else {
		if (obj->left == nullptr) {
			Node<T>* temp = obj->right;
			delete obj;
			return temp;
		}
		else if (obj->left == nullptr) {
			Node<T>* temp = obj->left;
			delete obj;
			return temp;
		}
		Node<T>* temp = obj->right;
		while (temp->left) {
			temp = temp->left;
		}
		obj->data = temp->data;
		obj->right = Delete(obj->right, temp->data);
	}
	return obj;
}

template <typename T>
void BinarySearchTree<T>::Delete(T data) {
	root = Delete(root, data);
}

template <typename T>
int BinarySearchTree<T>::CountTwoChild(Node<T>* obj) {
	if (obj == nullptr) {
		return 0;
	}
	return (obj->left && obj->right) + CountTwoChild(obj->left) + CountTwoChild(obj->right);
}

template <typename T>
int BinarySearchTree<T>::CountTwoChild() {
	return CountTwoChild(root);
}

template<typename T>
int BinarySearchTree<T>::CountTwoChildIterative()
{
	if (root == nullptr) {
		return 0;
	}
	int count = 0;
	stack<Node<T>*> s;
	s.push(root);
	while (!s.empty()) {
		Node<T>* temp = s.top();
		s.pop();
		if (temp->right && temp->left) {
			count++;
		}
		if (temp->right) {
			s.push(temp->right);
		}
		if (temp->left) {
			s.push(temp->left);
		}
	}
	return count;
}

template <typename T>
void BinarySearchTree<T>::DeleteLeaves(Node<T>*& obj) {
	if (obj == nullptr) {
		return;
	}
	if (obj->left == nullptr && obj->right == nullptr) {
		delete obj;
		obj = nullptr;
		return;
	}
	if (obj->left) {
		DeleteLeaves(obj->left);
	}
	if (obj->right) {
		DeleteLeaves(obj->right);
	}
}

template <typename T>
void BinarySearchTree<T>::DeleteLeaves() {
	DeleteLeaves(root);
}

template<typename T>
void BinarySearchTree<T>::DeleteLeavesIterative()
{
	if (root == nullptr) {
		return;
	}
	queue <pair<Node<T>*, Node<T>*>> q;
	q.push({ root,nullptr });
	while (!q.empty()) {
		auto temp = q.front();
		Node<T>* parent = temp.second;
		Node<T>* child = temp.first;
		q.pop();
		if (child->left != nullptr) {
			q.push({ child->left, child });
		}
		if (child->right != nullptr) {
			q.push({ child->right, child });
		}
		if (child->left == nullptr && child->right == nullptr) {
			if (parent != nullptr) {
				if (parent->left == child) {
					parent->left = nullptr;
				}
				else {
					parent->right = nullptr;
				}
			}
			else {
				root = nullptr;
			}
			delete child;
		}
	}
}

template <typename T>
void BinarySearchTree<T>::ClearRecursive(Node<T>* temp) {
	if (temp == nullptr) {
		return;
	}
	ClearRecursive(temp->left);
	ClearRecursive(temp->right);
	delete temp;
}

template<typename T>
int BinarySearchTree<T>::CountHeightRecursive(Node<T>* leaf)
{
	if (leaf == nullptr) {
		return 0;
	}
	else {
		int heightleft = CountHeightRecursive(leaf->left);
		int heightright = CountHeightRecursive(leaf->right);
		return (heightleft > heightright) ? heightleft + 1 : heightright + 1;
	}
}

template<typename T>
int BinarySearchTree<T>::CountHeightRecursive()
{
	return CountHeightRecursive(root);
}

template<typename T>
int BinarySearchTree<T>::CountHeightIterative()
{
	if (root == nullptr) {
		return 0;
	}
	queue<Node<T>*> q;
	q.push(root);
	int height = 0;
	int nodecount;
	while (!q.empty()) {
		++height;
		nodecount = q.size();
		while (nodecount > 0) {
			Node<T>* temp = q.front();
			if (temp->left != nullptr) {
				q.push(temp->left);
			}
			if (temp->right != nullptr) {
				q.push(temp->right);
			}
			q.pop();
			--nodecount;
		}
	}
	return height;
}

int main() {
	BinarySearchTree<int> kechi;
	kechi.Insert(50);
	kechi.Insert(10);
	kechi.Insert(60);
	kechi.Insert(80);
	kechi.Insert(200);
	kechi.Insert(30);
	kechi.Insert(56);
	kechi.InsertIterativeLevel(5);
	kechi.PrintLevelOrder();
	cout << kechi.Find(4) << endl;
	cout << endl;
	cout << "Height is (recursive) : " << kechi.CountHeightRecursive() << endl;
	cout << "Height is (iterative) : " << kechi.CountHeightIterative() << endl;
	kechi.DeleteLeaves();
	kechi.PrintLevelOrder();
	cout << "Nodes with two children (recursive) : " << kechi.CountTwoChild() << endl;
	cout << "Nodes with two children (iterative) : " << kechi.CountTwoChildIterative() << endl;
	kechi.Insert(2000);
	kechi.Insert(2200);
	kechi.Insert(3000);
	kechi.Insert(3300);
	kechi.PrintLevelOrder();
	cout << endl;
	kechi.DeleteLeavesIterative();
	kechi.PrintLevelOrder();
}