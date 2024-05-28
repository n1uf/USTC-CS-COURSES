#ifndef _BITREE_CPP_
#define _BITREE_CPP_
//��������ص�ʵ�ִ��� 
#include <stdio.h>
#include <stdlib.h>


//���������ݵ�����,�����ǿ��Դ�Ŷ�����ݵĽṹ������ 
typedef struct
{
	int id;
	int value; 
} ElemType; 

//����������Ľ�� 
typedef struct tnode
{
	ElemType data;
	struct tnode *lchild;
	struct tnode *rchild;
} bNode;

#include "showGT.h"  //չʾ����ͼ��API 


/***-����Ĵ����ǽ����ʺ��� visit() �Ĳ�ͬʵ�ַ�ʽ��ʵ�ֶԵ������Ĵ���������ͨ����Ϊ���������������Ĳ��� ***/ 

//��ӡĳ��������Ϣ,����Elemtype�Ķ�����޸�,�򵥰汾��������洢��ַ�� 
void bPrintNode(bNode *a)
{ 
	printf("\n(id = %2d) = %5d",a->data.id,a->data.value); 
}

//��ӡĳ��������Ϣ,����Elemtype�Ķ�����޸�,��ϸ�汾������洢��ַ�� 
void cPrintNode(bNode *a)
{ 
	printf("\n*(addr = %lx):(id=%2d)= %5d",a,a->data.id,a->data.value); 
}


/***-����Ĵ��������ֲ�ͬ�Ĺ������������㷨���Ѿ�������Ϣ�Ĳ�ͬ����ͬ ***/ 

//����������������������������볤��Ϊlen����������value
//value�����0��Ԫ��Ϊ����value������value���κ͸��Ƚϣ����ȸ�С���ͺ͸����������Ƚϣ�������������Ƚϣ�
//�������ƣ����Ƚ�ʱ������������������Ϊ�գ����Ը�valueֵ�����µ����ڵ㣬����Ϊ��Ӧ������������������ 
bNode *buildBTreeByValue(int *value,int len)
{
	// ��ʼ�����ڵ㣬idΪ0��valueΪvalue[0] 
	bNode *root = (bNode *)malloc(sizeof(bNode));
	if (!root) exit(0);
	int idx = 0;
	root->data.id = idx;				// ��ʼ��id 
	root->data.value = value[idx];		// ��ʼ��value 
	root->lchild = root->rchild = NULL;	// ��ʼ�����Һ���ָ�� 
	cPrintNode(root);
	
	for(idx=1;idx<len;++idx)
	{
		// �����½ڵ� 
		bNode *t = (bNode *)malloc(sizeof(bNode));
		if (!t) exit(0);
		t->data.id = idx;
		t->data.value = value[idx];
		t->lchild = t->rchild = NULL;
		cPrintNode(t);		
		
		// �����½ڵ��ڶ�������׼ȷλ�� 
		bNode *q; // p��˫�׽��
		
		// value[idx]С������������� ��������������� 
		for(bNode *p=root;p;(value[idx] < p->data.value)? p = p->lchild:p = p->rchild)
			q = p;
		(value[idx]<q->data.value)? q->lchild = t: q->rchild = t;  //���½ڵ����������
		printf(", �丸�ڵ��ַ %lx",q);
	}	
	return root;
} 

//���������,���볤��Ϊlen������edge��value,�±꼴Ϊ�����id��
//edge[id]��ʾ���Ϊid�Ľ���˫�׽��ı��(0~len-1) ��������˫�ױ��Ϊ-1 
//value�����¼�˽���������valueֵ
//�㷨˼�룺Ϊÿ����㹹��һ����㣬�����ǵĵ�ַ����һ��ָ�������У�Ȼ������edge����Щ������ӳɶ����� 
bNode *buildBTreeByEdge(int *value, int *edge, int len)
{
	bNode **allnodes= (bNode **)malloc(sizeof(bNode *)*len);//len��ָ��
	if (!allnodes) exit(0);
	
	// ��ʼ��ÿһ��ָ�� 
	for(int i=0;i<len;++i)
	{
		allnodes[i] = (bNode *)malloc(sizeof(bNode));
		if (!(allnodes[i])) exit(0);
		allnodes[i]->data.id = i;
		allnodes[i]->data.value = value[i];
		allnodes[i]->lchild = allnodes[i]->rchild = NULL;
	} 
	
	// �������������������� 
	bNode *root;
	for(int i=0;i<len;++i)
	{
		// û�е����ڵ� 
		if (edge[i]!=-1)
			(allnodes[edge[i]]->lchild == NULL)? allnodes[edge[i]]->lchild = allnodes[i]: allnodes[edge[i]]->rchild = allnodes[i];
		// �����ڵ� 
		else
			root = allnodes[i];
	}
	return root; 
} 

//�ݹ��㷨�����������,���볤��Ϊlen=2n+1������prelist���������Ľڵ�����Ϊn 
//��������prelist[i],�������������ս�㣬��ֵΪNULLNODE��prelist����n+1��NULLNODE 
#define NULLNODE -9999 
bNode *buildBTreeByPrelist(int *prelist,int len)
{
	bNode *t;
	static int idx = 0; //�ݹ���ÿ�ε���������Ҫ���ʵġ����⡱�����þ�̬������ȫ�ֱ��� 
	if (prelist[idx] == NULLNODE){
		idx++;
		return NULL;
	}
	if (!(t=(bNode *)malloc(sizeof(bNode *)))) exit(0);
	t->data.value = prelist[idx];
	t->data.id = idx;
	idx++; //׼������prelist[idx]����һ�����ݹ������,idx�޷������β��б� 
	t->lchild = buildBTreeByPrelist(prelist,len);
	t->rchild = buildBTreeByPrelist(prelist,len);		
	return t;
}//���prelist�е������޷�ȫ�����뵽һ�ö���������μ�⣿����������� idx<len-1) 
//ѧϰ�β��б����޷���ʾ������ġ�����ʱ��ʱ������ȫ�ֱ�����̬����������

//�ݹ��㷨(�������)����������� ��������������pre����������in���Լ��������и��Ե��Ͻ�pu,iu���½�pl,il
bNode *buildBTreeByPI(int *pre, int pl, int pu, int *in, int il, int iu)
{
	printf("\n%d-%d,%d-%d",pl,pu,il,iu);
	// ÿ�εݹ鶼ͨ�����ڵ�λ�÷ֿ��������������� 
	int il1,iu1,il2,iu2,pl1,pl2,pu1,pu2; 
	if (pu-pl!=iu-il) exit(0); //���������� 
	if (pu-pl<0) return NULL;  //������Ϊ�գ����ؿս��/���� 
	bNode *t = (bNode *)malloc(sizeof(bNode));
	if (!t) exit(0);
	// ȷ�����ڵ�λ�� 
	t->data.value = pre[pl];
	t->data.id = pl;
	for(int i=il;i<=iu;++i){
		if (in[i]==pre[pl])
		{	// �������½� 
			// �и���������
			// iu1 il1Ϊ������Ѱ�ҵ����½磬2Ϊ���Һ���Ѱ�� 
			iu1 = i-1;
			il1 = il;
			il2 = i+1;
			iu2 = iu;  
			// �и��������� 
			// pu1 pl1Ϊ������Ѱ�ҵ����½磬2Ϊ���Һ���Ѱ��
			pl1 = pl+1;
			pu1 = pl+(iu1-il1+1);
			pl2 = pu1+1;
			pu2 = pu;  
		}
	}
	// �ݹ� 
	t->lchild = buildBTreeByPI(pre,pl1,pu1,in,il1,iu1);
	t->rchild = buildBTreeByPI(pre,pl2,pu2,in,il2,iu2);
	return t; 
} 

/*** ��������������������  ***/ 
//���Ҹ������p�ĸ��ڵ� , t�ǿ�ʱ����ʾ�Ѿ��ҵ����Ͳ���Ҫ�ݹ���ã�ֱ�ӷ��� 
bNode *parent(bNode *root, bNode *p)
{
	bNode *t = NULL;
	if (!root || root==p) return NULL;//���޸��ڵ㣬����Ҳû��p�ĸ��ڵ� 
	
	if (p && (root->lchild==p || root->rchild==p)) return root;
	if (root->lchild && !t) t = parent(root->lchild,p);
	if (root->rchild && !t) t = parent(root->rchild,p);
	return t; 
} 

//�ɽ���id�����Ըĳ������������ֵ�����ҽ�㣬���ؽ��ָ�� ��(��������� 
bNode *locateByID(bNode *root, int id)
{
	if (!root) return NULL;
	if (root->data.id==id) return root; 
	bNode *t = locateByID(root->lchild,id);
	if (t) return t;
	return locateByID(root->rchild,id);
}

//���ú����������������������Ļ������ٸ������Ҳ������Һ����ˣ������Ҳ����Һ��� 
void DestroyBTree(bNode *root)
{
	if (root->lchild) {DestroyBTree(root->lchild);root->lchild=NULL;}
	if (root->rchild) {DestroyBTree(root->rchild);root->rchild=NULL;}
	if (!root->lchild && !root->rchild) {root = NULL;}
	free(root);
}



//���Ժ���ֵ������������valueֵ+1
void add1(bNode *a)
{
	a->data.value += 1;
} 

/***-����Ĵ�����ʵ�������������������ͺ��������ģ�壬������������Ĳ������ڶ����ǵ��޸� ***/ 
//�������������
void preTraverseTree(bNode *root,void (*ptrf)(bNode *a))
{
	if (root){//�ݹ���� 
		(*ptrf)(root); 
		preTraverseTree(root->lchild,(*ptrf));
		preTraverseTree(root->rchild,(*ptrf));
	}
}

//�������������  
void inTraverseTree(bNode *root,void (*ptrf)(bNode *a))
{
	if (root){ //�ݹ���� 
		inTraverseTree(root->lchild,(*ptrf));
		(*ptrf)(root);	
		inTraverseTree(root->rchild,(*ptrf));
	}
}

//������������� 
void postTraverseTree(bNode *root,void (*ptrf)(bNode *a))
{
	if (root){//�ݹ����	
		postTraverseTree(root->lchild,(*ptrf));
		postTraverseTree(root->rchild,(*ptrf));
		(*ptrf)(root);
	}
}

/***-����Ĵ�������������������������������������(��ʽ����)��ʽ��� ***/ 
//���¹���һ����ʽ���У���Ŷ������Ľ��ĵ�ַ�����ڲ������������ 
struct qNode
{ //���н�� 
	bNode *ptr;  //���еĽڵ�������������Ƕ���������ָ�� 
	struct qNode *next; //���е���һ����㣬�����ǵ����� 
};

typedef struct queue
{
	struct qNode *front;
	struct qNode *rear;
}linkQueue;

//�Ӷ��������ɲ�������Ķ��У��ֲ���������������������������
//���ö��е��ɵ��������һ�Σ�����ʵ�ֲ������
//���㷨Ҳ���������޸ļ��õ�������������㷨������һ�£� 
linkQueue *ToHiraQueue(bNode *root)
{
	linkQueue *hQueue = (linkQueue *)malloc(sizeof(linkQueue));
	if (!hQueue) exit(0);
	if (!root){
		hQueue->front = NULL;
		hQueue->rear = NULL;
		return hQueue;
	}
	
	struct qNode *head; //�����������еĶ�ͷ(�����޸�hQueue->front����ֹ��ʧ)����βֱ����hQueue->rear 
	struct qNode *t = (struct qNode *)malloc(sizeof(struct qNode)); //���������ڱ���㣨ͷ��㣬�������Ч���ݵĽ�㣩 
	if (!t) exit(0);
	hQueue->front = hQueue->rear = head = t; //��ʱ�ǿն��� 
	 
	//root���
	t = (struct qNode *)malloc(sizeof(struct qNode)); //�������н�� 
	if (!t) exit(0);
	t->ptr = root;  //������ֵ��ָ��next���Բ��ø�ֵ(why?) 
	// ��Ϊ�Ƕ�ͷ�������õ�t->next 
	hQueue->rear->next = t;
	hQueue->rear = t;
	
	while(head != hQueue->rear){//���в��� ,head���ڱ���㣬������Ч����Ч���ݴ�head->next��ʼ 
		head = head->next; //���ӣ�ģ����ӣ���ΪҪ�����������Ķ��У����Բ����޸Ķ��е�ͷָ��)	
		//printf("de-%lx,",head->ptr);	//��ӡ��䣬�����ã��鿴��ӡ����ӹ��� 
		if (head->ptr->lchild) { //head->next������ݣ���㣩�����ӷǿգ������¶��н�㣬��� 
			t = (struct qNode *)malloc(sizeof(struct qNode));
			if (!t) exit(0);
			t->ptr = head->ptr->lchild;	//�½���������ֵ 
			hQueue->rear->next = t; //�½ڵ�ӵ�����β��
			hQueue->rear = t;
			//printf("en-%lx,",t->ptr); //��ӡ��䣬�����ã��鿴��ӡ����ӹ��� 
		}
		if (head->ptr->rchild) { //head������ݣ���㣩���Һ��ӷǿգ������¶��н�㣬��� 
			t = (struct qNode *)malloc(sizeof(struct qNode));
			if (!t) exit(0);
			t->ptr = head->ptr->rchild;	//�½���������ֵ 
			hQueue->rear->next = t; //�½ڵ�ӵ�����β��	
			hQueue->rear = t;	
			//printf("en-%lx,",t->ptr);//��ӡ��䣬�����ã��鿴��ӡ����ӹ��� 
		}	
	} 
	return hQueue;
} //˼�����ʵ������/����/������������������������������Ķ���

/*** ������һЩ����Ӧ�� ***/ 
//��������ĸ߶�/��� 
int deepth(bNode *root)
{
	if (!root) return 0;
	int d = deepth(root->lchild);
	int n = deepth(root->rchild);
	return (d>n)? d+1 : n+1; 
}

//���������Ϊ2�Ľ����Ŀ 
int node2(bNode *root)
{
	int c=0;
	if (!root) return 0;
	if (root->lchild && root->rchild) c=1;	
	return c+node2(root->lchild)+node2(root->rchild);
}

//���������Ϊ1�Ľ����Ŀ  
int node1(bNode *root)
{
	int c=0;
	if (!root) return 0;
	if ((!root->lchild && root->rchild) ||(root->lchild && !root->rchild))  c=1;	
	return c+node1(root->lchild)+node1(root->rchild);
}

//���������Ϊ0�Ľ����Ŀ (Ҷ�ӽ����Ŀ�� 
int node0(bNode *root)
{
	if (!root) return 0;
	if (!root->lchild && !root->rchild) return 1;	
	return node0(root->lchild)+node0(root->rchild);
}

//���������Ϊ0�Ľ����Ŀ��value֮�� 
int value0(bNode *root)
{
	if (!root) return 0;
	if (!root->lchild && !root->rchild) return root->data.value;	
	return value0(root->lchild)+value0(root->rchild);
}


/*** ��Ŀ ***/
//�ɽ���value�����Ըĳ������������ֵ�����ҽ�㣬���ؽ��ָ�� ��(��������� 
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

//ɾ���ڵ�value = x �Ľڵ㼰������
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

//����id1��id2����Ĺ�ͬ����
int locate_ancestor(bNode *root,int id1,int id2)
{
	// p1, q1��d1��id2��Ӧ�Ľڵ� 
	bNode *p1;
	bNode *q1;
	
	// ����ѭ�����Ϸֱ�����Ѱ�Ҹ��ڵ� 
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

//����idֵ��������ڵ㵽id���·��
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
			printf("��");
		else
			printf("��");
	}
}

int globle_value_max = 0;
int globle_value_min = 9999;

void GetMaxMinvalue(bNode *root)
{	// �ݹ������value����Сvalue 
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
	
	printf("\n���Զ��������� value:");
	bNode *t1 = buildBTreeByValue(val,n); //������ֵ�������ɶ�����
	preTraverseTree(t1,add1); //����������� 
	printf("\n���������");
	inTraverseTree(t1,cPrintNode);  //����������� 
	printf("\n���������");
	postTraverseTree(t1,cPrintNode);//���Ժ������� 
	DestroyBTree(t1);
	
	printf("\n���Զ��������� edge :");
	int edge[7]={5,6,6,1,2,2,-1}; //���ӱ�����
	
	t1 = buildBTreeByEdge(val,edge,7); //������ֵ����ͱ����ɶ����� 
	printf("\n���������");
	preTraverseTree(t1,bPrintNode); //�����������
	
	inTraverseTree(t1,add1);  //����������� 
	printf("\n���������");
	postTraverseTree(t1,cPrintNode);//���Ժ������ 
	DestroyBTree(t1);
	
	printf("\n���Զ��������� Prelist:");
	int prelist[15]={17,32,41,NULLNODE,NULLNODE,NULLNODE,13,7,NULLNODE,NULLNODE,16,22,NULLNODE,NULLNODE,NULLNODE};
	t1 = buildBTreeByPrelist(prelist,15);
	printf("\n���������");
	preTraverseTree(t1,cPrintNode); //����������� 
	printf("\n���������");
	inTraverseTree(t1,cPrintNode);  //����������� 
	printf("\n���������");
	postTraverseTree(t1,bPrintNode);//���Ժ������� 
	
	//���Բ���������
	printf("\n���Բ���������:");
	linkQueue *qlist =  ToHiraQueue(t1);
	for(struct qNode *p = qlist->front;p!=qlist->rear;p = p->next)
		printf("%d, ",p->next->ptr->data.value); //��ӡ���������� 
	printf("\n");
	
	//���Խ����Һ��󸸽ڵ� 
	printf("\n���Խ����Һ��󸸽ڵ�:");
	bNode *tn = locateByID(t1,2);
	if (!tn) 
		printf("\nû�ҵ����");
	else{
		cPrintNode(tn);
		printf("\n���ڵ�Ϊ��"); 
		tn=parent(t1,tn);
		if (!tn)
			printf("û�ҵ�");
		else
			cPrintNode(tn); 
	}	
	DestroyBTree(t1);
	
	//�����������к��������й��������
	printf("\n���Զ��������� PI:");
	int pre[]={17,32,20,13,7,16,22};
	int in[]={20,32,17,7,13,22,16};
	t1=buildBTreeByPI(pre,0,6,in,0,6); 
	if (t1)
	{
		printf("\n���������");
		preTraverseTree(t1,cPrintNode); //����������� 
		printf("\n���������");
		inTraverseTree(t1,cPrintNode);  //����������� 
		printf("\n���������");
		postTraverseTree(t1,cPrintNode);//���Ժ������� 
	}
	
	saveTree(t1,"sg.html");
	
	printf("\n���������ȣ�"); 
	printf("%d", locate_ancestor(t1, 4, 6));
	
	printf("\n������·����");
	id_path(t1, 4);
	
	printf("\n����value��ֵ��");
	GetMaxMinvalue(t1);
	printf("%d", globle_value_max - globle_value_min);
	
	printf("\n����ɾ������");
	DelValue(t1, 13);
	//delete_valuex(t1, 13);
	getchar();
	puts("ɾ���ɹ�");
	saveTree(t1,"sg.html");
	
	DestroyBTree(t1);
	return 1;
}

#endif
