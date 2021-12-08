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

bool BinarySearchTree::deleteBST(BSNode*& bt, int key)
{
	if (bt == NULL)
		return false;

	if (bt->data == key)
		deleteNode(bt);
	else if (key < bt->data)
		return deleteBST(bt->leftChild, key);
	else if (key > bt->data)
		return deleteBST(bt->rightChild, key);
	return true;
}

void BinarySearchTree::deleteNode(BSNode*& bt)
{
	BSNode* p = NULL;
	//case1:���bt��Ҷ�ӽڵ�
	if (bt->leftChild == NULL && bt->rightChild == NULL)
	{
		p = bt;
		bt = NULL;
		delete p;
	}
	//case2a:���btû��������,ֻ��������
	else if (bt->rightChild == NULL)
	{
		p = bt;
		bt = bt->leftChild;
		delete p;
	}
	//case2b:���btû����������ֻ��������
	else if (bt->leftChild == NULL)
	{
		p = bt;
		bt = bt->rightChild;
		delete p;
	}
	/*case3:bt������������������������Ŀ��ڵ�������������ֵX_l��������������С��ֵX_r������Ҫɾ����Ŀ��ڵ㡣
	1.���ѡ����X_l����ôҪ�Ƚ�X_l�滻bt,�ٽ�X_l������������ΪX_lΪ�����������ֵ��X_l�������������������ӵ�X_l��parent����/��child��
	2.���ѡ����X_r,��ôֻ��Ҫ��X_r�滻bt,�ٽ�X_r����������һ��Ϊ��ָ�룬��ΪX_rΪ��С���������������˴�������Ϊ�˷�ֹҰָ�룩��
	���ӵ�X_r��parent����/��child����X_r:��������һ�Σ�Ȼ��һֱ�������ߵ��ף����ҵ���X_r��*/
	
	//�˴���X_lΪ����
	else
	{
		BSNode* parent, * pre;
		parent = bt;//parent��pre��parent
		pre = bt->leftChild;//�����£�׼������������Ѱ�����ֵ

		//��X_l����������һ�εִ��һ���ڵ㣬���������������Ȼ��һֱ�������ߣ����ҵ���X_l�����û������������õ�һ���ڵ����X_l��
		//������������һ��֮������������,while�ͻ����У�
		while (pre->rightChild != NULL)
		{
			parent = pre;
			pre = pre->rightChild; //�ҵ�X_l����ֵ��pre
		}
		bt->data = pre->data; //�ҵ�X_l֮�󣬽�bt��ֵ�滻ΪX_l��ֵ
		if (parent != bt)//����while���й�����������һ��֮����������������ôparent��ֵ�ͻ�仯�����ٵ���bt����ʱ��X_l�����������ӵ�X_l��parent����child
		{
			parent->rightChild = pre->leftChild;
		}
		else if (parent == bt)//����whileû���й�����������һ��֮��û��������������ôparent��ֵ�Ͳ���仯������bt����ʱ��X_l�����������ӵ�parent/bt����child
		{
			parent->leftChild = pre->leftChild;
		}
		delete pre; //�滻��ɺ�X_l��ֵ����bt�ϣ����ԭX_l�ڵ�
	}
	//�˴���X_rΪ����
	/*else
	{
		BSNode* pre, *parent;
		parent = bt;
		pre = bt->rightChild;
		while (pre->leftChild != NULL)
		{
			parent = pre;
			pre = pre->leftChild;
		}
		bt->data = pre->data;

		//��Ȼpre->leftChildһ����NULL����Ϊ�˷�ֹҰָ�룬һ��Ҫ����
		if(parent == bt)
			parent->rightChild = pre->leftChild;//��parent->rightChild = NULL;
		if (parent != bt)
			parent->leftChild = pre->leftChild;//��parent->leftChild = NULL;
		delete pre;
		pre = NULL;
	}*/
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

	//ɾ��BS��
	int deleteNode;
	cout << "������Ҫɾ���Ľڵ㣺";
	cin >> deleteNode;
	cout << endl;
	BST.deleteBST(deleteNode);
	cout << "ɾ�����inOrder��" << endl;
	BST.inOrder();
	cout << endl;
}