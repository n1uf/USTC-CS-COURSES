#ifndef _NETWORK_CPP_
#define _NETWORK_CPP_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAXVERTEX 100
#define MAXEDGE 20000

//����ṹ��
typedef struct Vertex {
	int id;//�����ţ�Ψһ��
	int w;//����Ȩֵ
	int degree;//����Ķ�
	int edges[MAXVERTEX];//�ߵı��
} Vertex;

//�߽ṹ��
typedef struct Edge {
	int id;//�ߵı�ţ�Ψһ��
	int h;//��ͷ������
	int t;//��β������
	int w;//Ȩֵ
} Edge;

//ͼ�ṹ��
typedef struct Graph {
	Vertex v[MAXVERTEX];// ��������
	Edge e[MAXEDGE];// ������
	int nv;// ������
	int ne;// ����
	int vidmax;// �������id		do
	int eidmax;// �����id		do
	bool dirctional;// t:����ͼ��f:����ͼ
	bool weighted;// t:��Ȩͼ��f:��Ȩͼ
} Graph;

#include "showgt.h"

//����һ�����ͼ������n�����㣬ÿ������������������ߵĸ���Ϊp
int randgengraph(int n, float p, bool directional, bool weighted, const char* filename, int seed) {
	srand(seed);
	char* content = (char*)malloc(5000000);
	if (!content) {
		printf("����洢�ռ�ʧ�ܣ�\n");
		exit(0);
	}
	FILE* fp = fopen(filename, "wb");
	if (!fp) {
		printf("����ͼ�ļ�%sʱʧ�ܣ�\n",filename);
		exit(0);
	}
	long offset = 0;//content��ǰ��д��λ��
	int ne = 0;//���ɱ���
	for (int i = 0; i < n; i++)
		offset += sprintf(content + offset, "%3d %5d\n", i, rand() % 100);//д�붥��ı�źͶ������Ȩֵ
	int pn = (int)(10000 * p);
	if (directional) {//����ͼ
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if (i != j && rand() % 10000 < pn) {
					offset += sprintf(content + offset, "%3d %3d %4d\n", i, j, weighted ? rand() % 100 : 1);
					ne++;
				}
	}
	else {//����ͼ
		for(int i = 0; i < n; i++)
			for(int j = i; j < n; j++)
				if (i != j && rand() % 10000 < pn) {
					offset += sprintf(content + offset, "%3d %3d %4d\n", i, j, weighted ? rand() % 100 : 1);
					ne++;
				}
	}
	char ch[40];
	int sz = sprintf(ch, "%d %7d %5s %5s\n", n, ne, weighted ? "true" : "flase", directional ? "true" : "flase");
	fwrite(&ch, sz, 1, fp);//д��ͼ�Ķ������ͱ���
	fwrite(content, offset, 1, fp);//д��ͼ�Ķ���ͱߵ���Ϣ
	fclose(fp);
	free(content);
}

//���ļ��ж���ͼ�����ڴ�������ͼ�ı�ʾ
void initGraphFromFile(Graph* g, const char* gfile) {
	FILE* fp = fopen(gfile, "r");
	if (!fp) {
		printf("��ȡͼ�����ļ�����\n");
		exit(0);
	}
	char bv[10];
	//��ȡͼ�Ļ�����Ϣ
	fscanf(fp, "%u%u%s", &(g->nv), &(g->ne), bv);
	//printf("%d %d %s", g->ne, g->nv, bv);
	g->weighted = strcmp(bv, "true") == 0 ? true : false;
	fscanf(fp, "%s", bv);
	g->dirctional = strcmp(bv, "true") == 0 ? true : false;
	//��ȡ������Ϣ
	for (int i = 0; i < g->nv; i++) {
		fscanf(fp, "%d%d", &(g->v[i].id), &(g->v[i].w));
		g->v[i].degree = 0;
		//printf("����%d-Ȩ%d\n", g->v[i].id, g->v[i].w);
	}
	//��ȡ����Ϣ
	for (unsigned long i = 0; i < g->ne; i++) {
		fscanf(fp, "%u%u%d", &(g->e[i].h), &(g->e[i].t), &(g->e[i].w));
		//printf("��:%u-%u=>%d\n", g->e[i].h, g->e[i].t, g->e[i].w);
		g->e[i].id = i;
		unsigned h, t;
		h = g->e[i].h;
		t = g->e[i].t;
		g->v[h].edges[g->v[h].degree++] = i;	// ���� 
		if(g->dirctional==false)
			g->v[t].edges[g->v[t].degree++] = i;	// ��� 
	}
	g->vidmax = g->nv - 1;	// do
	g->eidmax = g->ne - 1;	// do
	fclose(fp);
}

// ����һ����ͼ
Graph* initGraph(bool directional, bool weighted){
	Graph * g = (Graph *)malloc(sizeof(Graph));
	g->nv = g->ne = 0;
	g->dirctional = directional;
	g->weighted = weighted;
	g->vidmax = -1;	// do
	g->eidmax = -1;	// do
	return g;
}

//��ӡ�ڽӱ����Ϣ
void printgraph(Graph* g) {
	// do
	printf("ͼ�Ļ�����Ϣ:������(%u)-����(%lu)-��������id(%u)-�ߵ����id(%lu)-%s-%s\n", g->nv, g->ne, g->vidmax, g->eidmax, g->weighted ? "��Ȩͼ" : "��Ȩͼ", g->dirctional ? "����ͼ" : "����ͼ");
	for (int i = 0; i < g->nv; i++) {
		printf("ID(%u)-��(%d)-Ȩ(%d)-�߱� t(eid|w):%u", g->v[i].id, g->v[i].degree, g->v[i].w, g->v[i].id);
		for (int j = 0; j < g->v[i].degree; j++) {
			unsigned long e = g->v[i].edges[j];
			if (g->v[i].id == g->e[e].h)
				printf("->%u(%d)", g->e[e].t, g->e[e].w);
			else 
				printf("->%u(%d)", g->e[e].h, g->e[e].w);
		}
		printf("\n");
	}
}

//���Ҹ�����ŵĶ��㣬�����䶥�������±�
int getVexIdx(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return i;
	printf("input wrong vertex id in getVexIdx()!\n");
	exit(0);
}

//���Ҹ�����ŵĶ��㣬������Ȩֵ
int getVexW(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].w;
	printf("input wrong vertex id in getVexW()!\n");
	exit(0);
}

//���Ҹ�����ŵĶ��㣬�������
int getVexDegree(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].degree;
	printf("input wrong vertex id in getVexDegree()!\n");
	exit(0);
}

//���Ҹ�����ŵĶ���,���������б�
int* getEdgesByNode(Graph* g, int id, int* ne) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id) {
			*ne = g->v[i].degree;
			return g->v[i].edges;
		}
	printf("input wrong vertex id in getEdgesByNode()!\n");
	exit(0);
}

//���Ҹ�����ŵıߣ�������������±�
int getEdgeIdx(Graph* g, int id) {
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return i;
	printf("input wrong edge id in getEdgeIdx()!\n");
	exit(0);
}

//���Ҹ�����ŵıߣ�������Ȩֵ
int getEdgeW(Graph* g, int id) {
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return g->e[i].w;
	printf("input wrong edge id in getEdgeW()!\n");
	exit(0);
}

//���Ҹ�����ŵıߣ���������������
void getVexByEdge(Graph* g, int id, int *h, int *t) {
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id) {
			*h = g->e[i].h;
			*t = g->e[i].t;
			return ;
		}		
	printf("input wrong edge id in getVexByEdge()!\n");
	exit(0);
}

//ͨ��Ȩֵ���Ҷ�����
int locateVex(Graph* g, int w) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].w == w)
			return g->v[i].id;
	return -1;
}

//ͨ��Ȩֵ���ұ߱��
int locateEdge(Graph* g, int w) {
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].w == w)
			return g->e[i].id;
	return -1;
}

//���û�ı䶥��Ȩֵ
void setVexW(Graph* g, int id, int w) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
		{
			g->v[i].w = w;
			return ; 
		}
	printf("input wrong vertex id in setVexW()!\n");
	exit(0);
}

//���û�ı��Ȩֵ
void setEdgeW(Graph* g, int id, int w) {
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
		{
			g->e[i].w = w;
			return ;
		}
	printf("input wrong edge id in setEdgeW()!\n");
	exit(0);
}

//ɾ����
void deleteEdge(Graph* g, int id) {
	int ne = g->ne;
	if(id == g->eidmax)	// do
		g->eidmax --;
	for(int i = 0; i < g->ne; i ++)
	{
		if(g->e[i].id == id)
		{
			g->v[g->e[i].h].degree --;
			if(!g->dirctional)
				g->v[g->e[i].t].degree --;
			for(int j = i; j < g->ne; j ++)
			{
				g->e[j] = g->e[j + 1]; 
			}
			g->ne --;
			break;
		}
	}
	if(ne == g->ne)
		printf("cannot find the edge!\n");
}


//ɾ�����㣬ͬʱ��������ı�ȫ��ɾ��
void deleteVex(Graph* g, int id) {
	int nv = g->nv;
	if(id == g->vidmax)	// do
		g->vidmax --;
	for(int i = 0; i < g->nv; i ++)
	{
		if(g->v[i].id == id)
		{
			for(int j = 0; j <= g->v[i].degree; j ++)
			{
				deleteEdge(g, g->v[i].edges[j]);
			}
			for(int j = i; j < g->nv; j ++)
			{
				g->v[j] = g->v[j + 1];
			}
			g->nv --;
			break;
		}
	}
	for(int i = 0; i < g->ne; i ++)
	{
		if(g->e[i].h == id || g->e[i].t == id)
		{
			deleteEdge(g, g->e[i].id);
		}
	}
	if(nv == g->nv)
		printf("cannot find the vertex!\n");
}


//���Ӷ���
void addVex(Graph* g, int w) {
	int nv = g->nv;
	g->nv ++;
	g->v[nv].id = g->vidmax + 1;	// do
	g->vidmax ++;
	g->v[nv].degree = 0;
	g->v[nv].w = w;
}

//���ӱ�
void addEdge(Graph* g, int w, int h, int t) {
	int ne = g->ne;
	g->ne ++;
	g->e[ne].id = g->eidmax + 1;	// do
	g->eidmax ++;
	g->e[ne].w = w;
	g->e[ne].h = h;
	g->e[ne].t = t;
	g->v[h].degree ++;
	if(!g->dirctional)
		g->v[t].degree ++;
}

bool K[MAXVERTEX] = {false};

void dfs(Graph *g, int v)
{
	for (int i = 0; i < g->nv; i++)
	{
		if (g->v[i].id == v)
		{
			printf("%d ", g->v[i].id);
			K[i] = true;
			for (int I = 0; I < g->v[i].degree; I++)
			{
				int vexx = g->e[g->v[i].edges[I]].t;
				if(vexx == i)
				{
					vexx = g->e[g->v[i].edges[I]].h;
				}
				if(K[vexx] == false)
				{
					dfs(g,g->v[vexx].id);
				}
			}
			return;
		}
	}
}

int main() {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	if (!g) {
		printf("error\n");
		exit(0);
	}	
	randgengraph(10, 0.2, 1, 1, "graph.txt", 5);
	initGraphFromFile(g, "graph.txt");
	printgraph(g);
	saveGraph(g,"net.html");
	puts("�Ѿ����ɳ�ʼͼ��");
	
	printf("%d\n", g->v[8].id);
	printf("%d\n", g->v[8].degree);
	printf("%d\n", g->nv);
	
	getchar();
	deleteVex(g, 3);
	saveGraph(g,"net.html");
	puts("ɾ������idΪ3�Ľ�㣡"); 
	
	printf("%d\n", g->v[8].id);
	printf("%d\n", g->v[8].degree);
	printf("%d\n", g->nv);
	
	getchar(); 
	addVex(g, 30);
	addEdge(g, 50, 8, 10);
	saveGraph(g,"net.html");
	puts("�Ѿ������ȨΪ30�Ķ����ȨΪ50��ͷβ���Ϊ8��10�ıߣ�"); 
	
	printf("%d\n", g->v[8].id);
	printf("%d\n", g->v[8].degree);
	printf("%d\n", g->nv);
	getchar();
	int *h = (int *)malloc(sizeof(int));
	int *t = (int *)malloc(sizeof(int));
	getVexByEdge(g, 5, h, t);
	printf("idΪ5�ıߵ�ͷβ���idΪ%d��%d\n", *h, *t);
	
	getchar(); 
	addVex(g, 66);
	addEdge(g, 50, 5, 11);
	saveGraph(g,"net.html");
	puts("�Ѿ������ȨΪ60�Ķ����ȨΪ50��ͷβ���Ϊ5��11�ıߣ�"); 
	
	
	getchar(); 
	setVexW(g, 6, 99);
	setEdgeW(g, 15, 100);
	saveGraph(g,"net.html");
	puts("������idΪ6�Ķ���ȨΪ99��idΪ15�ı�ȨΪ100");
	
} 
#endif
