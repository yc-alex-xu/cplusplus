#include <iostream>
using namespace std;

typedef struct node
{
	int key;
	node *left, *right;
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

	node *r = new node{PreOrder[pbegin], NULL, NULL}; // 构造根节点

	int idx = findRoot(InOrder, ibegin, iend, PreOrder[pbegin]); // root's position in InOrder
	int sizeLeft = idx - ibegin;
	// 确定左子树、右子树 前序、中序遍历结果, 递归求解 */
	r->left = buildTree(PreOrder, pbegin + 1, sizeLeft + pbegin + 1, InOrder, ibegin, idx);
	r->right = buildTree(PreOrder, sizeLeft + pbegin + 1, pend, InOrder, idx + 1, iend);
	return r;
}

void traverse(node *r)
{
	if (r == NULL)
		return;

	cout << "key:" << r->key << "\t";
	if (r->left != NULL)
	{
		cout<< "left===>" << r->left->key;
	}

	if (r->right != NULL)
	{
		cout<< "\tright===>" << r->right->key;
	}
	cout << endl;
	traverse(r->left);
	traverse(r->right);
}

int main()
{
	int PreOrder[] = {43, 12, 8, 32, 16, 35, 78, 56, 88, 83, 121, 97};
	int InOrder[] = {8, 12, 16, 32, 35, 43, 56, 78, 83, 88, 97, 121};

	int len = sizeof(PreOrder) / sizeof(PreOrder[0]);
	node *r = buildTree(PreOrder, 0, len, InOrder, 0, len);
	traverse(r);

	return 0;
}
