#ifndef _BITREE_CPP_
#define _BITREE_CPP_
//二叉树相关的实现代码 
#include <stdio.h>
#include <stdlib.h>


//定义存放数据的类型,假设是可以存放多个数据的结构体类型 
typedef struct
{
	int id;
	int value; 
} ElemType; 

//定义二叉树的结点 
typedef struct tnode
{
	ElemType data;
	struct tnode *lchild;
	struct tnode *rchild;
} bNode;

#include "showGT.h"  //展示树和图的API 


/***-下面的代码是结点访问函数 visit() 的不同实现方式，实现对单个结点的处理，函数名通常作为二叉树遍历函数的参数 ***/ 

//打印某个结点的信息,依据Elemtype的定义而修改,简单版本（不输出存储地址） 
void bPrintNode(bNode *a)
{ 
	printf("\n(id = %2d) = %5d",a->data.id,a->data.value); 
}

//打印某个结点的信息,依据Elemtype的定义而修改,详细版本（输出存储地址） 
void cPrintNode(bNode *a)
{ 
	printf("\n*(addr = %lx):(id=%2d)= %5d",a,a->data.id,a->data.value); 
}


/***-下面的代码是四种不同的构建二叉树的算法，已经输入信息的不同而不同 ***/ 

//构造二叉树（二叉排序树），输入长度为len的整数数组value
//value数组第0个元素为根的value，后续value依次和根比较，若比根小，就和根的左子树比较；否则和右子树比较；
//依次类推，若比较时遇到左子树或右子树为空，则以该value值构建新的树节点，并称为对应的左子树或右子树。 
bNode *buildBTreeByValue(int *value,int len)
{
	// 初始化根节点，id为0，value为value[0] 
	bNode *root = (bNode *)malloc(sizeof(bNode));
	if (!root) exit(0);
	int idx = 0;
	root->data.id = idx;				// 初始化id 
	root->data.value = value[idx];		// 初始化value 
	root->lchild = root->rchild = NULL;	// 初始化左右孩子指针 
	cPrintNode(root);
	
	for(idx=1;idx<len;++idx)
	{
		// 生成新节点 
		bNode *t = (bNode *)malloc(sizeof(bNode));
		if (!t) exit(0);
		t->data.id = idx;
		t->data.value = value[idx];
		t->lchild = t->rchild = NULL;
		cPrintNode(t);		
		
		// 查找新节点在二叉树的准确位置 
		bNode *q; // p的双亲结点
		
		// value[idx]小于则进入左子树 ，否则进入右子树 
		for(bNode *p=root;p;(value[idx] < p->data.value)? p = p->lchild:p = p->rchild)
			q = p;
		(value[idx]<q->data.value)? q->lchild = t: q->rchild = t;  //将新节点链入二叉树
		printf(", 其父节点地址 %lx",q);
	}	
	return root;
} 

//构造二叉树,输入长度为len的数组edge和value,下标即为结点编号id，
//edge[id]表示编号为id的结点的双亲结点的编号(0~len-1) ，根结点的双亲编号为-1 
//value数组记录了结点的数据域value值
//算法思想：为每个结点构造一个结点，将它们的地址存在一个指针数组中；然后依据edge将这些结点链接成二叉树 
bNode *buildBTreeByEdge(int *value, int *edge, int len)
{
	bNode **allnodes= (bNode **)malloc(sizeof(bNode *)*len);//len个指针
	if (!allnodes) exit(0);
	
	// 初始化每一个指针 
	for(int i=0;i<len;++i)
	{
		allnodes[i] = (bNode *)malloc(sizeof(bNode));
		if (!(allnodes[i])) exit(0);
		allnodes[i]->data.id = i;
		allnodes[i]->data.value = value[i];
		allnodes[i]->lchild = allnodes[i]->rchild = NULL;
	} 
	
	// 从左子树往右子树构造 
	bNode *root;
	for(int i=0;i<len;++i)
	{
		// 没有到根节点 
		if (edge[i]!=-1)
			(allnodes[edge[i]]->lchild == NULL)? allnodes[edge[i]]->lchild = allnodes[i]: allnodes[edge[i]]->rchild = allnodes[i];
		// 到根节点 
		else
			root = allnodes[i];
	}
	return root; 
} 

//递归算法：构造二叉树,输入长度为len=2n+1的数组prelist，二叉树的节点数量为n 
//先序序列prelist[i],若序列中遇到空结点，其值为NULLNODE，prelist中有n+1个NULLNODE 
#define NULLNODE -9999 
bNode *buildBTreeByPrelist(int *prelist,int len)
{
	bNode *t;
	static int idx = 0; //递归中每次调用自身都需要访问的“特殊”变量用静态变量或全局变量 
	if (prelist[idx] == NULLNODE){
		idx++;
		return NULL;
	}
	if (!(t=(bNode *)malloc(sizeof(bNode *)))) exit(0);
	t->data.value = prelist[idx];
	t->data.id = idx;
	idx++; //准备访问prelist[idx]的下一个数据构建结点,idx无法放入形参列表 
	t->lchild = buildBTreeByPrelist(prelist,len);
	t->rchild = buildBTreeByPrelist(prelist,len);		
	return t;
}//如果prelist中的数据无法全部放入到一棵二叉树，如何检测？（构造结束后 idx<len-1) 
//学习形参列表中无法表示子问题的“特征时”时，采用全局变量或静态变量来处理

//递归算法(先序遍历)：构造二叉树 ，输入先序序列pre和中序序列in，以及两个序列各自的上界pu,iu和下界pl,il
bNode *buildBTreeByPI(int *pre, int pl, int pu, int *in, int il, int iu)
{
	printf("\n%d-%d,%d-%d",pl,pu,il,iu);
	// 每次递归都通过根节点位置分开左子树和右子树 
	int il1,iu1,il2,iu2,pl1,pl2,pu1,pu2; 
	if (pu-pl!=iu-il) exit(0); //检查输入参数 
	if (pu-pl<0) return NULL;  //若序列为空，返回空结点/空树 
	bNode *t = (bNode *)malloc(sizeof(bNode));
	if (!t) exit(0);
	// 确定根节点位置 
	t->data.value = pre[pl];
	t->data.id = pl;
	for(int i=il;i<=iu;++i){
		if (in[i]==pre[pl])
		{	// 更新上下界 
			// 切割中序序列
			// iu1 il1为向左孩子寻找的上下界，2为向右孩子寻找 
			iu1 = i-1;
			il1 = il;
			il2 = i+1;
			iu2 = iu;  
			// 切割先序序列 
			// pu1 pl1为向左孩子寻找的上下界，2为向右孩子寻找
			pl1 = pl+1;
			pu1 = pl+(iu1-il1+1);
			pl2 = pu1+1;
			pu2 = pu;  
		}
	}
	// 递归 
	t->lchild = buildBTreeByPI(pre,pl1,pu1,in,il1,iu1);
	t->rchild = buildBTreeByPI(pre,pl2,pu2,in,il2,iu2);
	return t; 
} 

/*** 二叉树的其它基本操作  ***/ 
//查找给定结点p的父节点 , t非空时，表示已经找到，就不需要递归调用，直接返回 
bNode *parent(bNode *root, bNode *p)
{
	bNode *t = NULL;
	if (!root || root==p) return NULL;//根无父节点，空树也没有p的父节点 
	
	if (p && (root->lchild==p || root->rchild==p)) return root;
	if (root->lchild && !t) t = parent(root->lchild,p);
	if (root->rchild && !t) t = parent(root->rchild,p);
	return t; 
} 

//由结点的id（可以改成其它数据域的值）查找结点，返回结点指针 。(先序遍历） 
bNode *locateByID(bNode *root, int id)
{
	if (!root) return NULL;
	if (root->data.id==id) return root; 
	bNode *t = locateByID(root->lchild,id);
	if (t) return t;
	return locateByID(root->rchild,id);
}

//采用后序遍历销毁树。先序遍历的话先销毁根结点就找不到左右孩子了，中序找不到右孩子 
void DestroyBTree(bNode *root)
{
	if (root->lchild) {DestroyBTree(root->lchild);root->lchild=NULL;}
	if (root->rchild) {DestroyBTree(root->rchild);root->rchild=NULL;}
	if (!root->lchild && !root->rchild) {root = NULL;}
	free(root);
}



//测试函数值，结点数据域的value值+1
void add1(bNode *a)
{
	a->data.value += 1;
} 

/***-下面的代码是实现先序遍历、中序遍历和后序遍历的模板，大多数二叉树的操作基于对它们的修改 ***/ 
//先序遍历二叉树
void preTraverseTree(bNode *root,void (*ptrf)(bNode *a))
{
	if (root){//递归出口 
		(*ptrf)(root); 
		preTraverseTree(root->lchild,(*ptrf));
		preTraverseTree(root->rchild,(*ptrf));
	}
}

//中序遍历二叉树  
void inTraverseTree(bNode *root,void (*ptrf)(bNode *a))
{
	if (root){ //递归出口 
		inTraverseTree(root->lchild,(*ptrf));
		(*ptrf)(root);	
		inTraverseTree(root->rchild,(*ptrf));
	}
}

//后序遍历二叉树 
void postTraverseTree(bNode *root,void (*ptrf)(bNode *a))
{
	if (root){//递归出口	
		postTraverseTree(root->lchild,(*ptrf));
		postTraverseTree(root->rchild,(*ptrf));
		(*ptrf)(root);
	}
}

/***-下面的代码用于线索化二叉树：层序遍历结果以链表(链式队列)形式输出 ***/ 
//以下构成一个链式队列，存放二叉树的结点的地址，用于层序遍历二叉树 
struct qNode
{ //队列结点 
	bNode *ptr;  //队列的节点包括的数据域是二叉树结点的指针 
	struct qNode *next; //队列的下一个结点，队列是单链表 
};

typedef struct queue
{
	struct qNode *front;
	struct qNode *rear;
}linkQueue;

//从二叉树生成层序遍历的队列：分层线索化。输入二叉树，输出队列
//将该队列当成单链表遍历一次，可以实现层序遍历
//该算法也可以稍作修改即得到“层序遍历”算法（尝试一下） 
linkQueue *ToHiraQueue(bNode *root)
{
	linkQueue *hQueue = (linkQueue *)malloc(sizeof(linkQueue));
	if (!hQueue) exit(0);
	if (!root){
		hQueue->front = NULL;
		hQueue->rear = NULL;
		return hQueue;
	}
	
	struct qNode *head; //线索化过程中的队头(不能修改hQueue->front，防止丢失)，队尾直接用hQueue->rear 
	struct qNode *t = (struct qNode *)malloc(sizeof(struct qNode)); //创建队列哨兵结点（头结点，不存放有效数据的结点） 
	if (!t) exit(0);
	hQueue->front = hQueue->rear = head = t; //此时是空队列 
	 
	//root入队
	t = (struct qNode *)malloc(sizeof(struct qNode)); //创建队列结点 
	if (!t) exit(0);
	t->ptr = root;  //数据域赋值，指针next可以不用赋值(why?) 
	// 因为是队头，无需用到t->next 
	hQueue->rear->next = t;
	hQueue->rear = t;
	
	while(head != hQueue->rear){//队列不空 ,head是哨兵结点，数据无效，有效数据从head->next开始 
		head = head->next; //出队（模拟出队，因为要返回线索化的队列，所以不能修改队列的头指针)	
		//printf("de-%lx,",head->ptr);	//打印语句，调试用，查看入队、出队过程 
		if (head->ptr->lchild) { //head->next存放数据（结点）的左孩子非空，构建新队列结点，入队 
			t = (struct qNode *)malloc(sizeof(struct qNode));
			if (!t) exit(0);
			t->ptr = head->ptr->lchild;	//新结点的数据域赋值 
			hQueue->rear->next = t; //新节点接到队列尾部
			hQueue->rear = t;
			//printf("en-%lx,",t->ptr); //打印语句，调试用，查看入队、出队过程 
		}
		if (head->ptr->rchild) { //head存放数据（结点）的右孩子非空，构建新队列结点，入队 
			t = (struct qNode *)malloc(sizeof(struct qNode));
			if (!t) exit(0);
			t->ptr = head->ptr->rchild;	//新结点的数据域赋值 
			hQueue->rear->next = t; //新节点接到队列尾部	
			hQueue->rear = t;	
			//printf("en-%lx,",t->ptr);//打印语句，调试用，查看入队、出队过程 
		}	
	} 
	return hQueue;
} //思考如何实现先序/中序/后序遍历的线索化？并输出线索化后的队列

/*** 下面是一些典型应用 ***/ 
//求二叉树的高度/深度 
int deepth(bNode *root)
{
	if (!root) return 0;
	int d = deepth(root->lchild);
	int n = deepth(root->rchild);
	return (d>n)? d+1 : n+1; 
}

//求二叉树度为2的结点数目 
int node2(bNode *root)
{
	int c=0;
	if (!root) return 0;
	if (root->lchild && root->rchild) c=1;	
	return c+node2(root->lchild)+node2(root->rchild);
}

//求二叉树度为1的结点数目  
int node1(bNode *root)
{
	int c=0;
	if (!root) return 0;
	if ((!root->lchild && root->rchild) ||(root->lchild && !root->rchild))  c=1;	
	return c+node1(root->lchild)+node1(root->rchild);
}

//求二叉树度为0的结点数目 (叶子结点数目） 
int node0(bNode *root)
{
	if (!root) return 0;
	if (!root->lchild && !root->rchild) return 1;	
	return node0(root->lchild)+node0(root->rchild);
}

//求二叉树度为0的结点数目的value之和 
int value0(bNode *root)
{
	if (!root) return 0;
	if (!root->lchild && !root->rchild) return root->data.value;	
	return value0(root->lchild)+value0(root->rchild);
}


/*** 题目 ***/
//由结点的value（可以改成其它数据域的值）查找结点，返回结点指针 。(先序遍历） 
bNode *locateByvalue(bNode *root, int value)
{
	if (!root) return NULL;
	if (root->data.value==value) return root; 
	bNode *t = locateByvalue(root->lchild,value);
	if (t) return t;
	return locateByvalue(root->rchild,value);
}

/*void delete_valuex(bNode *root, int x)
{
    if (!root)
        return;
    if (root->data.value == x)
    {
    	DestroyBTree(root);
	}
    delete_valuex(root->lchild, x);
    delete_valuex(root->rchild, x);
}*/

//删除节点value = x 的节点及其子树
int DelValue(bNode *root,int x)
{
	bNode *p;
	bNode *q;
	q = locateByvalue(root,x);
	for(;q;q = locateByvalue(root,x))
	{
		p = parent(root,q);
		if(p->lchild == q)
			p->lchild = NULL;
		else
			p->rchild = NULL;
	}
} 

//查找id1和id2最近的共同祖先
int locate_ancestor(bNode *root,int id1,int id2)
{
	// p1, q1是d1和id2对应的节点 
	bNode *p1;
	bNode *q1;
	
	// 两层循环向上分别向上寻找父节点 
	p1 = locateByID(root,id1);
	for(;p1;p1 = parent(root,p1))
	{
		q1 = locateByID(root,id2);
		for(;q1;q1 = parent(root,q1))
		{
			if(q1 == p1) return p1->data.id;
		}
	}
	bNode *ERR = NULL;
	return ERR->data.id;
} 

//给定id值，输出根节点到id结点路径
void id_path(bNode *root,int id)
{
	bNode *p;
	bNode *q;
	int flag[100] = {0},n = 0;
	p = locateByID(root,id);
	q = parent(root,p);
	for(;q;q = parent(root,p))
	{
		if(q->lchild == p)
			flag[n] = 0;
		else
			flag[n] = 1;
		p = q;
		n++;
	}
	n --;
	for(;n>=0;n--) 
	{
		if(flag[n] == 0)
			printf("左");
		else
			printf("右");
	}
}

int globle_value_max = 0;
int globle_value_min = 9999;

void GetMaxMinvalue(bNode *root)
{	// 递归找最大value和最小value 
	if (root)
	{
		if(root->data.value > globle_value_max)
			globle_value_max = root->data.value;
		if(root->data.value < globle_value_min)
			globle_value_min = root->data.value;
		GetMaxMinvalue(root->lchild);
		GetMaxMinvalue(root->rchild);
	}
}

int main(){
	int val[]={22,32,6,12,75,9,88,13,41,7,16,17};
	int n = 12;
	
	printf("\n测试二叉树生成 value:");
	bNode *t1 = buildBTreeByValue(val,n); //测试由值数组生成二叉树
	preTraverseTree(t1,add1); //测试先序遍历 
	printf("\n中序遍历：");
	inTraverseTree(t1,cPrintNode);  //测试中序遍历 
	printf("\n后序遍历：");
	postTraverseTree(t1,cPrintNode);//测试后续遍历 
	DestroyBTree(t1);
	
	printf("\n测试二叉树生成 edge :");
	int edge[7]={5,6,6,1,2,2,-1}; //增加边数组
	
	t1 = buildBTreeByEdge(val,edge,7); //测试由值数组和边生成二叉树 
	printf("\n先序遍历：");
	preTraverseTree(t1,bPrintNode); //测试先序遍历
	
	inTraverseTree(t1,add1);  //测试中序遍历 
	printf("\n后序遍历：");
	postTraverseTree(t1,cPrintNode);//测试后序遍历 
	DestroyBTree(t1);
	
	printf("\n测试二叉树生成 Prelist:");
	int prelist[15]={17,32,41,NULLNODE,NULLNODE,NULLNODE,13,7,NULLNODE,NULLNODE,16,22,NULLNODE,NULLNODE,NULLNODE};
	t1 = buildBTreeByPrelist(prelist,15);
	printf("\n先序遍历：");
	preTraverseTree(t1,cPrintNode); //测试先序遍历 
	printf("\n中序遍历：");
	inTraverseTree(t1,cPrintNode);  //测试中序遍历 
	printf("\n后序遍历：");
	postTraverseTree(t1,bPrintNode);//测试后续遍历 
	
	//测试层序线索化
	printf("\n测试层序线索化:");
	linkQueue *qlist =  ToHiraQueue(t1);
	for(struct qNode *p = qlist->front;p!=qlist->rear;p = p->next)
		printf("%d, ",p->next->ptr->data.value); //打印线索化链表 
	printf("\n");
	
	//测试结点查找和求父节点 
	printf("\n测试结点查找和求父节点:");
	bNode *tn = locateByID(t1,2);
	if (!tn) 
		printf("\n没找到结点");
	else{
		cPrintNode(tn);
		printf("\n父节点为："); 
		tn=parent(t1,tn);
		if (!tn)
			printf("没找到");
		else
			cPrintNode(tn); 
	}	
	DestroyBTree(t1);
	
	//测试先序序列和中序序列构造二叉树
	printf("\n测试二叉树生成 PI:");
	int pre[]={17,32,20,13,7,16,22};
	int in[]={20,32,17,7,13,22,16};
	t1=buildBTreeByPI(pre,0,6,in,0,6); 
	if (t1)
	{
		printf("\n先序遍历：");
		preTraverseTree(t1,cPrintNode); //测试先序遍历 
		printf("\n中序遍历：");
		inTraverseTree(t1,cPrintNode);  //测试中序遍历 
		printf("\n后序遍历：");
		postTraverseTree(t1,cPrintNode);//测试后续遍历 
	}
	
	saveTree(t1,"sg.html");
	
	printf("\n测试找祖先："); 
	printf("%d", locate_ancestor(t1, 4, 6));
	
	printf("\n测试找路径：");
	id_path(t1, 4);
	
	printf("\n测试value差值：");
	GetMaxMinvalue(t1);
	printf("%d", globle_value_max - globle_value_min);
	
	printf("\n测试删子树：");
	DelValue(t1, 13);
	//delete_valuex(t1, 13);
	getchar();
	puts("删除成功");
	saveTree(t1,"sg.html");
	
	DestroyBTree(t1);
	return 1;
}

#endif
