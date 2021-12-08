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
	//case1:如果bt是叶子节点
	if (bt->leftChild == NULL && bt->rightChild == NULL)
	{
		p = bt;
		bt = NULL;
		delete p;
	}
	//case2a:如果bt没有右子树,只有左子树
	else if (bt->rightChild == NULL)
	{
		p = bt;
		bt = bt->leftChild;
		delete p;
	}
	//case2b:如果bt没有左子树，只有右子树
	else if (bt->leftChild == NULL)
	{
		p = bt;
		bt = bt->rightChild;
		delete p;
	}
	/*case3:bt既有左子树又有右子树：找目标节点左子树中最大的值X_l或者右子树中最小的值X_r来代替要删除的目标节点。
	1.如果选的是X_l，那么要先将X_l替换bt,再将X_l的左子树（因为X_l为左子树的最大值，X_l不可能有右子树）连接到X_l的parent的左/右child；
	2.如果选的是X_r,那么只需要用X_r替换bt,再将X_r的左子树（一定为空指针，因为X_r为最小，不会有子树。此处连接是为了防止野指针），
	连接到X_r的parent的左/右child（找X_r:向右下走一次，然后一直往左下走到底，就找到了X_r）*/
	
	//此处用X_l为例子
	else
	{
		BSNode* parent, * pre;
		parent = bt;//parent是pre的parent
		pre = bt->leftChild;//往左下，准备在左子树中寻找最大值

		//找X_l：向左下走一次抵达第一个节点，如果还有右子树，然后一直往右下走，就找到了X_l；如果没有右子树，则该第一个节点就是X_l。
		//假如往左下走一次之后还有有右子树,while就会运行：
		while (pre->rightChild != NULL)
		{
			parent = pre;
			pre = pre->rightChild; //找到X_l并赋值给pre
		}
		bt->data = pre->data; //找到X_l之后，将bt的值替换为X_l的值
		if (parent != bt)//假如while运行过（即左下走一次之后还有右子树），那么parent的值就会变化，不再等于bt。此时把X_l的左子树连接到X_l的parent的右child
		{
			parent->rightChild = pre->leftChild;
		}
		else if (parent == bt)//假如while没运行过（即左下走一次之后没有右子树），那么parent的值就不会变化，等于bt。此时把X_l的左子树连接到parent/bt的左child
		{
			parent->leftChild = pre->leftChild;
		}
		delete pre; //替换完成后X_l的值到了bt上，清除原X_l节点
	}
	//此处以X_r为例子
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

		//虽然pre->leftChild一定是NULL，但为了防止野指针，一定要连接
		if(parent == bt)
			parent->rightChild = pre->leftChild;//或parent->rightChild = NULL;
		if (parent != bt)
			parent->leftChild = pre->leftChild;//或parent->leftChild = NULL;
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

	//删除BS树
	int deleteNode;
	cout << "请输入要删除的节点：";
	cin >> deleteNode;
	cout << endl;
	BST.deleteBST(deleteNode);
	cout << "删除后的inOrder：" << endl;
	BST.inOrder();
	cout << endl;
}