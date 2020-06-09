#include <iostream>
using namespace std;

/** node DS */
typedef struct node
{
	int key;
	node *left,*right;
} node;

int findRoot(int A[], int begin, int end, int key)
{
	for (int i = begin; i < end; i++)
	{
		if (key == A[i])
			return i;
	}

	return -1;
}

/** 重构二叉树, 参数: PreOrder[pbegin ... pend]
  *                     InOrder[ibegin ... iend]
  * end 属于不能用的
  */
node *buildTree(int *PreOrder, int pbegin, int pend,
				int *InOrder, int ibegin, int iend)
{
	if (pbegin >= pend || ibegin >= iend)
		return NULL; // 出口, 无节点情况

	node *pRoot = new node{PreOrder[pbegin], NULL, NULL}; // 构造根节点

	int r = findRoot(InOrder, ibegin, iend, PreOrder[pbegin]); // root's position in InOrder

	// 确定左子树、右子树 前序、中序遍历结果, 递归求解 */
	pRoot->left = buildTree(PreOrder, pbegin + 1, (r - ibegin) + pbegin + 1, InOrder, ibegin, r);
	pRoot->right = buildTree(PreOrder, (r - ibegin) + pbegin + 1, pend, InOrder, r + 1, iend);
	cout << "root:" << PreOrder[pbegin] << endl;

	return pRoot;
}

/** 中序遍历 */
void inOrderTraverse(node *pRoot)
{
	if (pRoot == NULL)
		return;

	cout << "key:" << pRoot->key << endl;
	if (pRoot->left != NULL)
	{
		cout << pRoot->key << "left===>" << pRoot->left->key << endl;
		inOrderTraverse(pRoot->left);
	}

	if (pRoot->right != NULL)
	{
		cout << pRoot->key << "right===>" << pRoot->right->key << endl;
		inOrderTraverse(pRoot->right);
	}
}

int main()
{
	int PreOrder[] = {43, 12, 8, 32, 16, 35, 78, 56, 88, 83, 121, 97};
	int InOrder[] = {8, 12, 16, 32, 35, 43, 56, 78, 83, 88, 97, 121};

	int len = sizeof(PreOrder) / sizeof(PreOrder[0]);
	node *pRoot = buildTree(PreOrder, 0, len, InOrder, 0, len);
	//inOrderTraverse(pRoot);

	return 0;
}
