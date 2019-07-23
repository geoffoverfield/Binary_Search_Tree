//Geoff Overfield
//Basic Templated Binary Tree

#include <iostream>
using namespace std;

#ifndef BINARYTREE_H
#define BINARYTREE_H

template <class T>
struct Node
{
public:
	T nodeData;
	T secondaryData;
	Node *left;
	Node *right;
	Node()
    {
        left = NULL;
        right = NULL;
    }
	Node(T a)
	{
		nodeData = a;
		left = NULL;
		right = NULL;
	}

	//Overloaded Operators
	bool operator < (Node<T> &pnt)
	{
		if (this->nodeData < pnt.nodeData) return true;
		else return false;
	}

	bool operator == (Node<T> &p)
	{
		if (this->nodeData == p.nodeData) return true;
		else return false;
	}

	bool operator = (Node<T> &p)
	{
		if (this->nodeData = p.nodeData) return true;
		else return false;
	}
private:
};

template <class T>
class BST
{
public:
	T nodeData;
    
	BST()
    {
        root = NULL;
        size = 0;
    }
    
	~BST()
    {
        Clear(root);
    }
    
	void Insert(T& data)
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
            curr = newNode->nodeData > curr->nodeData ? curr->right : curr->left;
        }
        if (newNode->nodeData < parent->nodeData)
        {
            parent->left = newNode;
            size++;
        }
        else if (newNode->nodeData > parent->nodeData)
        {
            parent->right = newNode;
            size++;
        }
    }
    
	void Delete(T& pSearch)
    {
        if (IsEmpty())
        {
            throw std::runtime_error("Invalid Action");
        }
        
        Node<T> *curr = root;
        Node<T> *parent = NULL;
        
        //====================================================SEARCHING FOR LEAF======================================================
        while (curr)
        {
            if (curr->nodeData == pSearch.nodeData)
                break;
            else
            {
                parent = curr;
                curr = pSearch.nodeData > curr->nodeData ? curr->right : curr->left;
            }
        }
        if (curr == NULL)
        {
            cout << "Information not found......." << endl << endl;
            return;
        }
        
        //==================================================CASE 1 - DELETING LEAF====================================================
        if (curr->left == NULL && curr->right == NULL)
        {
            if (parent->left == curr)
                parent->left = NULL;
            else parent->right = NULL;
            delete curr;
            size--;
            return;
        }
        
        //==============================================CASE 2 - NODE WITH SINGLE CHILD===============================================
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
        
        //==============================================CASE 3 - NODE WITH TWO CHILDREN===============================================
        else if (curr->left != NULL && curr->right != NULL)
        {
            Node<T> *cur_right = curr->right;
            if (curr->right->left == NULL && curr->right->right == NULL)
            {
                curr->nodeData = curr->right->nodeData;
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
                    curr->nodeData = left_cur->nodeData;
                    delete left_cur;
                    left_cur_parent->left = NULL;
                }
                else
                {
                    Node<T> *temp = curr->right;
                    curr->nodeData = temp->nodeData;
                    curr->right = temp->right;
                    delete temp;
                }
            }
            size--;
        }
    }
    
	Node<T> *Search(T& pSearch)
    {
        Node<T> *current = root;
        while (current)
        {
            if (current->nodeData == pSearch.nodeData)
            {
                return current;
            }
            else
            {
                current = pSearch.nodeData > curr->nodeData ? curr->right : curr->left;
            }
        }
        return NULL;
    }

	size_t getSize()
    {
        return size;
    }
    
    int getDepth(Node* root)
    {
        if (root == NULL) return 0;
        
        int left = getDepth(root->left);
        int right = getDepth(root->right);
        return max(left, right) +1;
    }

    int getNumberOfLeafNodes()
    {
        size_t iReturn = 0;
        Node *curr = root;
        while (curr)
        {
            if (!curr->left && !curr->right) iReturn++;
            else if (curr-left) curr = curr->left;
            else curr = curr->right;
        }
        
        return iReturn;
    }

	bool isEmpty()
    {
        return bool(root == NULL);
    }
    
    bool isIdentical(BST* pOther)
    {
        if (root == NULL && pOther->root == NULL) return true;
        if (root == NULL || pOther->root == NULL) return false;
        
        Node* curr = root;
        Node* other = pOther->root;
        
        while(curr && other)
        {
            if (curr->nodeData != other->nodeData) return false;
            else
            {
                if (curr-left && other->left)
                {
                    curr = curr->left;
                    other = other->left;
                }
                else if (curr->right && other->right)
                {
                    curr = curr->right;
                    other = other->right;
                }
                else return false;
            }
        }
        
        return true;
    }

	void Clear(Node<T> *node)
    {
        if (node)
        {
            if (node->left) Clear(node->left);
            if (node->right) Clear(node->right);
            delete node;
        }
    }

    void TraverseInOrderFromNode(Node<T> *)
    {
        if (node != NULL)
        {
            if (node->left)
                TraverseInOrderFromNode(node->left);
            cout << node->nodeData << "\t";
            if (node->right)
                TraverseInOrderFromNode(node->right);
        }
    }
    
    void TraversePreOrderFromNode(Node<T> *)
    {
        cout << node->nodeData << "\t";
        if (node->left)
            TraversePreOrderFromNode(node->left);
        if (node->right)
            TraversePreOrderFromNode(node->right);
    }
    
    void TraversePostOrderFromNode(Node<T> *)
    {
        if (node->left)
            TraversePostOrderFromNode(node->left);
        if (node->right)
            TraversePostOrderFromNode(node->right);
        cout << node->nodeData << "\t";
    }

    void TraverseInOrderFromRoot()
    {
        TraverseInOrderFromNode(root);
    }
    
	void TraversePreOrderFromRoot()
    {
        TraversePreOrderFromNode(root);
    }

	void TraversePostOrderFromRoot()
    {
        TraversePostOrderFromNode(root);
    }
    
    void TraverseByLevel()
    {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        
        Node* temp;
        while(!q.empty())
        {
            temp = q.front();
            q.pop();
            cout << temp->nodeData << endl;
            if (temp->left)
                q.push(temp->left);
            if (q->right)
                q.push(temp->right);
        }
    }
    
private:
	size_t size;
	Node<T> *root;
};

#endif
