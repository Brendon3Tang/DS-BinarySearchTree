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
	//����Ϊ�ջ��ߵ���Ҷ�ӽڵ����/���ӽڵ㣨Ҳ�ǿսڵ㣩�������������
	if (newNode == NULL)
	{
		newNode = new BSNode;//�ȴ���һ���µĽڵ�ռ�
		newNode->data = key;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
	}
	else //������Ϊ�գ����߻�û�е����ʺ���ӽڵ��λ��ʱ
	{
		//����½ڵ�С�ڵ�ǰ�ڵ㣬��������������ݹ�Ѱ��λ��
		if (key < newNode->data)
			insert(newNode->leftChild, key);
		//����½ڵ���ڵ�ǰ�ڵ㣬��������������ݹ�Ѱ��λ��
		else if (key > newNode->data)
			insert(newNode->rightChild, key);
		//����½ڵ���ڵ�ǰ�ڵ㣬�˳��ݹ飬�޷����
		else
		{
			cout << "�ýڵ��Ѵ��ڣ��޷��ظ����룡" << endl;
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
		cout << "��ɾ���ڵ㣺" << bt->data << endl;
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
	//����BS��
	const int arrLen = 5;
	int arr[arrLen] = { 63, 90, 70, 55, 58 };
	BinarySearchTree BST(arr, arrLen);

	//���BS��
	cout << "inOrder��" << endl;
	BST.inOrder();
	cout << endl;

	//��ѰBS��
	BSNode* result = NULL;
	result = BST.searchBST(89);
	if(result == NULL)
		cout << "δ�ҵ��ڵ㣡" << endl;
	else if (result->data == 55)
		cout << "���ҵ��ڵ㣡" << endl;
}