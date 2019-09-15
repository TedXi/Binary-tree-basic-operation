#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;

typedef struct BTNode {
	int data;
	struct BTNode *lChild;
	struct BTNode *rChild;
}BiTNode;

//控制台输入先序创建二叉树
void Console_CreateBiTree(BiTNode **T)
{
	int ch;
	scanf("%d", &ch);
	if (ch == -1)
	{
		*T = NULL;
		return;
	}
	else
	{
		*T = (BiTNode *)malloc(sizeof(BiTNode));
		(*T)->data = ch;
		printf("输入%d的左子节点( <- )：", ch);
		Console_CreateBiTree(&((*T)->lChild));
		printf("输入%d的右子节点( -> )：", ch);
		Console_CreateBiTree((&(*T)->rChild));
	}

	return;
}

void Array_CreatBiTree(BiTNode **T, char *data_prior, char* data_in) {

}

//先序遍历二叉树
void PreOrderBiTree(BiTNode *T)
{
	if (T == NULL)
	{
		return;
	}
	else
	{
		printf("%d ", T->data);
		PreOrderBiTree(T->lChild);
		PreOrderBiTree(T->rChild);
	}
}

//先序非递归遍历二叉树
void PreOrderBiTree_norecursion(BiTNode *T) {
	stack<BiTNode *> s;
	BiTNode *p = T;
	s.push(p);
	while (s.size() != 0)//栈中没有元素就要结束，不设p!=null，因为访问最后一个元素的时候栈为空指针不为空，下一个循环栈取不出来东西，会报错。其实在循环的末尾添加p=null也可解决这个问题，但是更慢
	{
		p = s.top(); s.pop();
		printf("%d ", p->data);
		if (p->rChild != NULL)	 //先压栈右子树是因为后进先出，左子树应该比右子树先访问
			s.push(p->rChild);
		if (p->lChild != NULL)	 //如果左子树存在的话，这样下一个循环弹出来的就是左子树
			s.push(p->lChild);
	}
}

//中序遍历二叉树
void MiddleOrderBiTree(BiTNode *T)
{
	if (T == NULL)
	{
		return;
	}
	else
	{
		MiddleOrderBiTree(T->lChild);
		printf("%d ", T->data);
		MiddleOrderBiTree(T->rChild);
	}
}

void MiddleOrderBiTree_norecursion(BiTNode *T) {
	stack<BiTNode *> s;
	BiTNode *p = T;
	while (p !=NULL || s.size() != 0)			//判空条件
	{
		if (p != NULL) {						//如果当前节点的左孩子不为空
			s.push(p);							//当前节点压栈
			p = p->lChild;						//p变成p->lchild
		}
		else
		{
			p = s.top(); s.pop();				
			printf("%d ", p->data);				//中序遍历弹栈必访问
			p = p->rChild;						//访问比转向右子树
		}
	}
}

//后续遍历二叉树
void PostOrderBiTree(BiTNode *T)
{
	if (T == NULL)
	{
		return;
	}
	else
	{
		PostOrderBiTree(T->lChild);
		PostOrderBiTree(T->rChild);
		printf("%d ", T->data);
	}
}

//后序非递归遍历二叉树
void PostOrderBiTree_norecursion(BiTNode *T) {				
	stack<BiTNode *> stack;									//初始化栈
	BiTNode *p = T;											//p为遍历时使用的节点指针
	BiTNode *r = NULL;										//r为上一次访问过的节点指针
	while (p != NULL || stack.size() != 0) {				//p不为空，栈也不为空则还有节点没有被遍历到
		if (p != NULL) {									//如果p为空
			stack.push(p);									//将p压栈
			p = p->lChild;									//p变为p的左子树
		}
		else												//若p为空
		{
			p = stack.top();								//获取栈顶元素
			if (p->rChild != NULL && p->rChild != r) {		//如果获取到的栈顶元素为没有访问过的右子树
				p = p->rChild;								//p变为p的右子树
				stack.push(p);								//p压栈
				p = p->lChild;								//p变为p的左子树
			}
			else											//如果获取到的栈顶元素没有右子树或右子树已访问过
			{
				stack.pop();								//弹栈
				printf("%d ", p->data);						//访问获取到的栈顶元素
				r = p;										//设置上次访问过的元素
				p = NULL;									//p置空
			}
		}
	}
}

//从左向右层次遍历二叉树
void LevelOrder_l2r(BiTNode *T) {
	queue<BiTNode *> q;
	BiTNode *p = T;
	q.push(p);
	for(; q.size() != 0;)
	{
		p = q.front(); q.pop();
		printf("%d ", p->data);
		if (p->lChild != NULL)
			q.push(p->lChild);
		if (p->rChild != NULL)
			q.push(p->rChild);
	}
}

//二叉树的深度
int TreeDeep(BiTNode *T)
{
	int deep = 0;
	if (T != NULL)
	{
		int leftdeep = TreeDeep(T->lChild);
		int rightdeep = TreeDeep(T->rChild);
		deep = leftdeep >= rightdeep ? leftdeep + 1 : rightdeep + 1;
	}

	return deep;
}

//非递归遍历二叉树的深度
int TreeDeep_norecursion(BiTNode *T) {
	int deep = 0;
	stack<BiTNode *> s;					//利用后序遍历完成，在遍历每一个节点时，栈中的内容即为节点到根节点的路径
	BiTNode *p = T;
	BiTNode *r = NULL;
	while (p != NULL || s.size() != 0) {
		if (p != NULL) {
			s.push(p);
			p = p->lChild;
		}
		else
		{
			p = s.top();
			if (p->rChild != NULL && p->rChild != r) {
				p = p->rChild;
				s.push(p);
				p = p->lChild;
			}
			else
			{
				if (deep < s.size())	//注意这里要先求高度，然后再弹栈，不然高度需要加一
					deep = s.size();
				s.pop();
				r = p;
				p = NULL;
			}
		}
	}
	return deep;
}

//判断是否为完全二叉树，返回满足完全二叉树的最后一个节点
int IsCompleteBiTree(BiTNode *T) {											//使用层次遍历
	int no_child = 0;
	queue<BiTNode*> q;
	BiTNode *p = T;
	q.push(p);
	while (p != NULL && q.size() != 0) {									//判空条件
		p = q.front(); q.pop();
		if (p->lChild != NULL)
			q.push(p->lChild);
		if (p->rChild != NULL)
			q.push(p->rChild);												//层次遍历的一般内容，不需要visit
		if (no_child == 0 && (p->lChild == NULL || p->rChild == NULL)) {	//如果现在找到了一个缺少子节点的节点
			if (p->lChild == NULL && p->rChild != NULL) {					//如果是左子树没有而右子树存在，说明不是完全二叉树
				no_child = p->data;											//取当前节点的值
				break;														//退出
			}
			no_child = 1;													//如果是缺少右子树或者左右两个都没有，那么记录下来，以后的节点都不能有子树了
			continue;														//继续循环
		}
		if (no_child == 1 && (p->lChild != NULL || p->rChild != NULL)) {	//如果已经记录到后面的节点不能拥有子树，却拥有了，那么说明不是完全二叉树
			no_child = p->data;												//取当前节点的值
			break;															//退出
		}
	}
	return no_child;
}

//双分支节点的个数
int DoubleForkCount(BiTNode *T) {											//使用后续非递归遍历
	stack<BiTNode *> s;
	BiTNode *p = T;
	BiTNode *r = NULL;
	int dfcount = 0;
	while (p != NULL || s.size() != 0)
	{
		if (p != NULL) {
			s.push(p);
			p = p->lChild;
		}
		else
		{
			p = s.top();
			if (p->rChild != NULL && p->rChild != r) {
				p = p->rChild;
				s.push(p);
				p = r->lChild;
			}
			else
			{
				s.pop();
				if (p->lChild != NULL && p->rChild != NULL)					//对节点进行的访问就是看有没有两个儿子
					dfcount++;
				r = p;
				p = NULL;
			}
		}
	}
	return dfcount;
}

//叶子节点个数
int LeafCount(BiTNode *T)
{
	static int count;
	if (T != NULL)
	{
		if (T->lChild == NULL && T->rChild == NULL)
		{
			count++;
		}
		LeafCount(T->lChild);
		LeafCount(T->rChild);
	}
	return count;
}

//代权路径长度
int WPL(BiTNode *T) {										//使用中序非递归遍历求树的带权路径长度（叶子节点的值之和）
	stack<BiTNode *> s;
	BiTNode *p = T;
	int val = 0;
	while (p != NULL || s.size() != 0) {					//判空条件
		if (p != NULL) {
			s.push(p);
			p = p->lChild;
		}
		else
		{
			p = s.top(); s.pop();
			if (p->lChild == NULL && p->rChild == NULL)		//中序遍历，弹栈必访问
				val += p->data;
			p = p->rChild;									//拐向右子树
		}
	}
	return val;
}

//主函数
int main(int argc, const char *argv[])
{
	BiTNode *T;
	int depth, leafCount = 0;
	printf("请输入第一个节点的值，-1表示没有叶节点：\n");
	Console_CreateBiTree(&T);

	printf("先序遍历二叉树：");
	PreOrderBiTree(T);
	printf("\n");

	printf("先序非递归遍历二叉树：");
	PreOrderBiTree_norecursion(T);
	printf("\n");

	printf("中序遍历二叉树：");
	MiddleOrderBiTree(T);
	printf("\n");

	printf("中序非递归遍历二叉树：");
	MiddleOrderBiTree_norecursion(T);
	printf("\n");
	
	printf("后续遍历二叉树：");
	PostOrderBiTree(T);
	printf("\n");

	printf("后续非递归遍历二叉树：");
	PostOrderBiTree_norecursion(T);
	printf("\n");

	printf("从左到右层次遍历二叉树：");
	LevelOrder_l2r(T);
	printf("\n");

	depth = TreeDeep(T);
	printf("树的深度为：%d\n", depth);

	depth = TreeDeep_norecursion(T);
	printf("非递归遍历树的深度为：%d\n", depth);

	leafCount = LeafCount(T);
	printf("叶子节点个数:%d\n", leafCount);

	int dfcount = DoubleForkCount(T);
	printf("双分支节点的个数:%d\n",dfcount);

	int is_comBiT = IsCompleteBiTree(T);
	printf("满足满二叉树的最后节点值:%d\n", is_comBiT);

	int wpl = WPL(T);
	printf("代权路径长度：%d\n", wpl);

	return 0;
}
