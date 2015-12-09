//Geoff Overfield
//Basic Templated Binary Tree

#include <iostream>
using namespace std;

#ifndef HEADER_H
#define HEADER_H

template <class T>
struct Node
{
public:
	T x;
	T data;
	Node *left;
	Node *right;
	Node();
	Node(T a)
	{
		x = a;
		left = NULL;
		right = NULL;
	}

	//Overloaded Operators
	bool operator < (Node<T> &pnt)
	{
		if (this->x < pnt.x) return false;
		else return true;
	}

	bool operator == (Node<T> &p)
	{
		if (this->x == p.x) return false;
		else return true;
	}

	bool operator = (Node<T> &p)
	{
		if (this->x = p.x) return false;
		else return true;
	}
private:
};

template <class T>
Node<T>::Node()
{
	left = NULL;
	right = NULL;
}

template <class T>
class BST
{
public:
	T x;
	BST();
	~BST();
	void Insert(T &);
	void Delete(T &);
	void InOrder(Node<T> *);
	void PostOrder(Node<T> *);
	void PreOrder(Node<T> *);
	Node<T> *Search(T &);
	size_t Size();
	bool isEmpty();
	void Clear(Node<T> *);
	void TravPre();
	void TravPost();
	void TravIn();
	
private:
	size_t size;
	Node<T> *root;

};


template <class T>
BST<T>::BST()
{
	root = NULL;
	size = 0;
}

template <class T>
BST<T>::~BST()
{
	Clear(root);
}

template <class T>
void BST<T>::Insert(T &data)
{
	Node<T> *newNode = new Node<T>(data);
	Node<T> *parent = NULL;
	Node<T> *curr = root;
	if (isEmpty())
	{
		root = newNode;
		size++;
		return;
	}
	while (curr)
	{
		parent = curr;
		curr = newNode->x > curr->x ? curr->right : curr->left;
	}
	if (newNode->x < parent->x)
	{
		parent->left = newNode;
		size++;
	}
	else if (newNode->x > parent->x)
	{
		parent->right = newNode;
		size++;
	}
}

template <class T>
void BST<T>::Delete(T &data)
{
	if (IsEmpty())
	{
		throw std::runtime_error("Invalid Action");
	}

	Node<T> *curr = root;
	Node<T> *parent = NULL;

	//============================================================================================================================
	//====================================================SEARCHING FOR LEAF======================================================
	//============================================================================================================================
	while (curr)
	{
		if (curr->x == data)
			break;
		else
		{
			parent = curr;
			curr = data > curr->x ? curr->right : curr->left;
		}
	}
	if (curr == NULL)
	{
		cout << "Information not found......." << endl << endl;
		return;
	}

	//============================================================================================================================
	//==================================================CASE 1 - DELETING LEAF====================================================
	//============================================================================================================================
	if (curr->left == NULL && curr->right == NULL)
	{
		if (parent->left == curr)
			parent->left = NULL;
		else parent->right = NULL;
		delete curr;
		size--;
		return;
	}

	//============================================================================================================================
	//==============================================CASE 2 - NODE WITH SINGLE CHILD===============================================
	//============================================================================================================================
	if ((curr->left == NULL && curr->right != NULL) || (curr->left != NULL && curr->right == NULL))
	{
		if (curr->left == NULL && curr->right != NULL)
		{
			if (parent->left == curr)
			{
				parent->left = curr->left;
			}
			else
			{
				parent->right = curr->right;
			}
		}
		else if (curr->left != NULL && curr->right == NULL)
		{
			if (parent->left == curr)
			{
				parent->left = curr->left;
			}
			else
			{
				parent->right = curr->right;
			}
		}
		delete curr;
		size--;
	}

	//============================================================================================================================
	//==============================================CASE 3 - NODE WITH TWO CHILDREN===============================================
	//============================================================================================================================

	else if (curr->left != NULL && curr->right != NULL)
	{
		Node<T> *cur_right = curr->right;
		if (curr->right->left == NULL && curr->right->right == NULL)
		{
			curr->x = curr->right->x;
			delete curr->right;
			curr->right = NULL;
		}
		else
		{
			if (curr->right->left != NULL)
			{
				Node<T> * left_cur;
				Node<T> * left_cur_parent;
				left_cur_parent = curr->right;
				left_cur = curr->right->left;
				while (left_cur->left != NULL)
				{
					left_cur_parent = left_cur;
					left_cur = left_cur->left;
				}
				curr->x = left_cur->x;
				delete left_cur;
				left_cur_parent->left = NULL;
			}
			else
			{
				Node<T> *temp = curr->right;
				curr->x = temp->x;
				curr->right = temp->right;
				delete temp;
			}
		}
		size--;
	}
}

template <class T>
void BST<T>::InOrder(Node<T> *node)
{
	if (node != NULL)
	{
		if (node->left)
			InOrder(node->left);
		cout << node->x << "\t";
		if (node->right)
			InOrder(node->right);
	}
}

template <class T>
void BST<T>::PostOrder(Node<T> *node)
{
	if (node->left)
		PostOrder(node->left);
	if (node->right)
		PostOrder(node->right);
	cout << node->x << "\t";
}

template <class T>
void BST<T>::PreOrder(Node<T> *node)
{
	cout << node->x << "\t";
	if (node->left)
		PreOrder(node->left);
	if (node->right)
		PreOrder(node->right);
}

template <class T>
Node<T> *BST<T>::Search(T &data)
{
	Node<T> *current = root;
	while (current)
	{
		if (current->data == item1)
		{
			return current;
		}
		else
		{
			if (item1 < current->data)
			{
				current = current->left;
			}
			else current = current->right;
		}
	}
	return NULL;
}

template <class T>
size_t BST<T>::Size()
{
	return size;
}

template <class T>
bool BST<T>::isEmpty()
{
	return bool(root == NULL);
}

template <class T>
void BST<T>::Clear(Node<T> *node)
{
	if (node)
	{
		if (node->left) Clear(node->left);
		if (node->right) Clear(node->right);
		delete node;
	}
}

template <class T>
void BST<T>::TravIn()
{
	InOrder(root);
}

template <class T>
void BST<T>::TravPre()
{
	PreOrder(root);
}

template <class T>
void BST<T>::TravPost()
{
	PostOrder(root);
}
#endif