#pragma once
#include<iostream>
#include<string>
using namespace std;
enum Balance_factor { LH = -1, EH, RH };
template<class Type>
struct node {
public:
	Type data;
	int key;
	node<Type> *left;
	node<Type> *right;
	Balance_factor balance;
	node(){}
	node(Type x,int key) {
		data = x;
		this->key = key;
		left = NULL;
		right = NULL;
		balance = EH;
	}
};

template<class Type>
class AVLTree {
public:
	node<Type> *root;

	AVLTree() {
		root = NULL;
	}

	node<Type>* rotateRight(node<Type> *&root) {
		node<Type> *tempPtr = root->left;
		root->left = tempPtr->right;
		tempPtr->right = root;
		return tempPtr;
	}

	node<Type>* rotateLeft(node<Type> *&root) {
		node<Type> *tempPtr = root->right;
		root->right = tempPtr->left;
		tempPtr->left = root;
		return tempPtr;
	}

	node<Type>* leftBalance(node<Type> *root, bool &taller) {
		node<Type> *leftTree = root->left;
		if (leftTree->balance == LH) {
			root = rotateRight(root);
			root->balance = EH;
			leftTree->balance = EH;
			taller = false;
		}
		else {
			node<Type> *rightTree = leftTree->right;
			if (rightTree->balance == LH) {
				root->balance = RH;
				leftTree->balance = EH;
			}
			else if (rightTree->balance == EH) {
				leftTree->balance = EH;
			}
			else {
				root->balance = EH;
				leftTree->balance = LH;
			}
			rightTree->balance = EH;
			root->left = rotateLeft(leftTree);
			root = rotateRight(root);
			taller = false;
		}
		return root;
	}

	node<Type>* rightBalance(node<Type> *root, bool &taller) {
		node<Type> *rightTree = root->right;
		if (rightTree->balance == RH) {
			root = rotateLeft(root);
			root->balance = EH;
			rightTree->balance = EH;
			taller = false;
		}
		else {
			node<Type> *leftTree = rightTree->left;
			if (leftTree->balance == RH) {
				root->balance = LH;
				rightTree->balance = EH;
			}
			else if (leftTree->balance == EH) {
				rightTree->balance = EH;
			}
			else {
				root->balance = EH;
				rightTree->balance = RH;
			}
			leftTree->balance = EH;
			root->right = rotateRight(rightTree);
			root = rotateLeft(root);
			taller = false;
		}
		return root;
	}

	node<Type>* AVLInsert(node<Type> *newPtr, bool &taller) {
		if (root == NULL) {
			root = newPtr;
			taller = true;
			return root;
		}
		AVLTree<Type> *temp = new AVLTree<Type>();
		if (newPtr->key < root->key) {
			temp->root = root->left;
			root->left = temp->AVLInsert(newPtr, taller);
			if (taller == true) {
				if (root->balance == LH) {
					root = leftBalance(root, taller);
				}
				else if (root->balance == EH) {
					root->balance = LH;
				}
				else {
					root->balance = EH;
					taller = false;
				}
			}
		}
		else {
			temp->root = root->right;
			root->right = temp->AVLInsert(newPtr, taller);
			if (taller == true) {
				if (root->balance == LH) {
					root->balance = EH;
					taller = false;
				}
				else if (root->balance == EH) {
					root->balance = RH;
				}
				else {
					root = rightBalance(root, taller);
				}
			}

		}
		return root;
	}

	node<Type>* deleteRightBalance(node<Type> *&root, bool &shorter) {
		if (root->balance == LH) root->balance = EH;
		else if (root->balance == EH) {
			root->balance = RH;
			shorter = false;
		}
		else {
			node<Type> *rightTree = root->right;
			node<Type> *leftTree;
			if (rightTree->balance == LH) {
				leftTree = rightTree->left;
				if (leftTree->balance == LH) {
					rightTree->balance = RH;
					root->balance = EH;
				}
				else if (leftTree->balance == EH) {
					root->balance = LH;
					rightTree->balance = EH;
				}
				else {
					root->balance = LH;
					rightTree->balance = EH;
				}
				leftTree->balance = EH;
				root->right = rotateRight(rightTree);
				root = rotateLeft(root);
			}
			else {
				if (rightTree->balance != EH) {
					root->balance = EH;
					rightTree->balance = EH;
				}
				else {
					root->balance = RH;
					rightTree->balance = LH;
					shorter = false;
				}
				root = rotateLeft(root);
			}
		}
		return root;
	}

	node<Type>* deleteLeftBalance(node<Type> *&root, bool &shorter) {
		if (root->balance == RH) root->balance = EH;
		else if (root->balance == EH) {
			root->balance = LH;
			shorter = false;
		}
		else {
			node<Type> *leftTree = root->left;
			node<Type> *rightTree;
			if (leftTree->balance == RH) {
				rightTree = leftTree->right;
				if (rightTree->balance == RH) {
					leftTree->balance = LH;
					root->balance = EH;
				}
				else if (rightTree->balance == EH) {
					root->balance = RH;
					leftTree->balance = EH;
				}
				else {
					root->balance = RH;
					leftTree->balance = EH;
				}
				rightTree->balance = EH;
				root->left = rotateLeft(leftTree);
				root = rotateRight(root);
			}
			else {
				if (leftTree->balance != EH) {
					root->balance = EH;
					leftTree->balance = EH;
				}
				else {
					root->balance = LH;
					leftTree->balance = RH;
					shorter = false;
				}
				root = rotateRight(root);
			}
		}
		return root;
	}

	node<Type>* AVLDelete(int deletekey, bool &shorter, bool &success) {
		if (root == NULL) {
			shorter = false;
			success = false;
			return NULL;
		}
		AVLTree *temp = new AVLTree();
		if (deletekey < root->key) {
			temp->root = root->left;
			root->left = temp->AVLDelete(deletekey, shorter, success);
			if (shorter == true) {
				root = deleteRightBalance(root, shorter);
			}
		}
		else if (deletekey > root->key) {
			temp->root = root->right;
			root->right = temp->AVLDelete(deletekey, shorter, success);
			if (shorter == true) {
				root = deleteLeftBalance(root, shorter);
			}
		}
		else {
			node<Type> *deleteNode = root;
			if (root->right == NULL) {
				node<Type> *newRoot = root->left;
				success = true;
				shorter = true;
				delete deleteNode;
				return newRoot;
			}
			else if (root->left == NULL) {
				node<Type> *newRoot = root->right;
				success = true;
				shorter = true;
				delete deleteNode;
				return newRoot;
			}
			else {
				node<Type> *exchPtr = root->left;
				while (exchPtr->right != NULL) {
					exchPtr = exchPtr->right;
				}
				root->key = exchPtr->key;
				temp->root = root->left;
				root->left = temp->AVLDelete(exchPtr->key, shorter, success);
				if (shorter == true) {
					root = deleteRightBalance(root, shorter);
				}
			}
		}
		return root;
	}

	 bool AVLSearch(node<Type>* &node,int key) {
		node = root;
		while (node != NULL) {
			if (key < node->key) node = node->left;
			else if (key > node->key) node = node->right;
			else if (key == node->key) return 1;
		}
		return 0;
	}
};

