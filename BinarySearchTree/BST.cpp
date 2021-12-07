#include "BST.h";

BinarySearchTree::BinarySearchTree(int array[], int arrLen)
{
	this->root = NULL;
	for (int i = 0; i < arrLen; i++)
	{
		insert(this->root, array[i]);
	}
}

void BinarySearchTree::insert(BSNode*& newNode, int key)
{
	//当树为空或者到达叶子节点的左/右子节点（也是空节点），即可添加数据
	if (newNode == NULL)
	{
		newNode = new BSNode;//先创建一个新的节点空间
		newNode->data = key;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
	}
	else //当树不为空，或者还没有到达适合添加节点的位置时
	{
		//如果新节点小于当前节点，则继续往左子树递归寻找位置
		if (key < newNode->data)
			insert(newNode->leftChild, key);
		//如果新节点大于当前节点，则继续往右子树递归寻找位置
		else if (key > newNode->data)
			insert(newNode->rightChild, key);
		//如果新节点等于当前节点，退出递归，无法添加
		else
		{
			cout << "该节点已存在，无法重复加入！" << endl;
			return;
		}
	}
}

void BinarySearchTree::release(BSNode* bt)
{
	if (bt == NULL)
		return;
	else
	{
		release(bt->leftChild);
		release(bt->rightChild);
		cout << "已删除节点：" << bt->data << endl;
		delete bt;
		bt = NULL;
	}
}

void BinarySearchTree::inOrder(BSNode* bt)
{
	if (bt == NULL)
		return;
	else
	{
		inOrder(bt->leftChild);
		cout << bt->data << " ";
		inOrder(bt->rightChild);
	}
}

bool BinarySearchTree::deleteBST(BSNode* bt, int key)
{
	return false;
}

bool BinarySearchTree::deleteNode(BSNode*& bt)
{
	return false;
}

BSNode* BinarySearchTree::searchBST(BSNode* bt, int key)
{
	if (bt == NULL)
		return NULL;
	else if (bt->data == key)
		return bt;
	else if (key < bt->data)
		searchBST(bt->leftChild, key);
	else if (key > bt->data)
		searchBST(bt->rightChild, key); 
	
}

int main()
{
	//创建BS树
	const int arrLen = 5;
	int arr[arrLen] = { 63, 90, 70, 55, 58 };
	BinarySearchTree BST(arr, arrLen);

	//输出BS树
	cout << "inOrder：" << endl;
	BST.inOrder();
	cout << endl;

	//搜寻BS树
	BSNode* result = NULL;
	result = BST.searchBST(89);
	if(result == NULL)
		cout << "未找到节点！" << endl;
	else if (result->data == 55)
		cout << "已找到节点！" << endl;
}