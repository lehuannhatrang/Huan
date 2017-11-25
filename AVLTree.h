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
	node(Type x,int key);
};

template<class Type>
class AVLTree {
public:
	node<Type> *root;
	AVLTree();
	node<Type>* rotateRight(node<Type> *&root);
	node<Type>* rotateLeft(node<Type> *&root);

	node<Type>* leftBalance(node<Type> *root, bool &taller);

	node<Type>* rightBalance(node<Type> *root, bool &taller);

	node<Type>* AVLInsert(node<Type> *newPtr, bool &taller);

	node<Type>* deleteRightBalance(node<Type> *&root, bool &shorter);

	node<Type>* deleteLeftBalance(node<Type> *&root, bool &shorter);

	node<Type>* AVLDelete(int deletekey, bool &shorter, bool &success);


};

