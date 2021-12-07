#pragma once
#include <iostream>
using namespace std;

struct BSNode
{
	int data;
	BSNode* leftChild, * rightChild;
};

class BinarySearchTree
{
private:
	BSNode* root;

public:
	BinarySearchTree(int array[], int arrLen);

	~BinarySearchTree() { release(root); };

	BSNode* searchBST(int key) { return searchBST(root, key); };

	bool deleteBST(int key) { return deleteBST(root, key); };

	void inOrder() { inOrder(root); };

private:
	void insert(BSNode*& newNode, int key);

	void release(BSNode* bt);

	void inOrder(BSNode* bt);

	bool deleteBST(BSNode* bt, int key);

	bool deleteNode(BSNode*& bt);

	BSNode* searchBST(BSNode* bt, int key);
};