#ifndef _NETWORK_CPP_
#define _NETWORK_CPP_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAXVERTEX 100
#define MAXEDGE 20000

//顶点结构体
typedef struct Vertex {
	int id;//顶点编号（唯一）
	int w;//顶点权值
	int degree;//顶点的度
	int edges[MAXVERTEX];//边的编号
} Vertex;

//边结构体
typedef struct Edge {
	int id;//边的编号（唯一）
	int h;//边头顶点编号
	int t;//边尾顶点编号
	int w;//权值
} Edge;

//图结构体
typedef struct Graph {
	Vertex v[MAXVERTEX];// 顶点数组
	Edge e[MAXEDGE];// 边数组
	int nv;// 顶点数
	int ne;// 边数
	int vidmax;// 顶点最大id		do
	int eidmax;// 边最大id		do
	bool dirctional;// t:有向图，f:无向图
	bool weighted;// t:带权图，f:等权图
} Graph;

#include "showgt.h"

//生成一个随机图，包括n个顶点，每个顶点和其它顶点连边的概率为p
int randgengraph(int n, float p, bool directional, bool weighted, const char* filename, int seed) {
	srand(seed);
	char* content = (char*)malloc(5000000);
	if (!content) {
		printf("分配存储空间失败！\n");
		exit(0);
	}
	FILE* fp = fopen(filename, "wb");
	if (!fp) {
		printf("生成图文件%s时失败！\n",filename);
		exit(0);
	}
	long offset = 0;//content当前的写入位置
	int ne = 0;//生成边数
	for (int i = 0; i < n; i++)
		offset += sprintf(content + offset, "%3d %5d\n", i, rand() % 100);//写入顶点的编号和顶点随机权值
	int pn = (int)(10000 * p);
	if (directional) {//有向图
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if (i != j && rand() % 10000 < pn) {
					offset += sprintf(content + offset, "%3d %3d %4d\n", i, j, weighted ? rand() % 100 : 1);
					ne++;
				}
	}
	else {//无向图
		for(int i = 0; i < n; i++)
			for(int j = i; j < n; j++)
				if (i != j && rand() % 10000 < pn) {
					offset += sprintf(content + offset, "%3d %3d %4d\n", i, j, weighted ? rand() % 100 : 1);
					ne++;
				}
	}
	char ch[40];
	int sz = sprintf(ch, "%d %7d %5s %5s\n", n, ne, weighted ? "true" : "flase", directional ? "true" : "flase");
	fwrite(&ch, sz, 1, fp);//写入图的顶点数和边数
	fwrite(content, offset, 1, fp);//写入图的顶点和边的信息
	fclose(fp);
	free(content);
}

//从文件中读入图，在内存中生成图的表示
void initGraphFromFile(Graph* g, const char* gfile) {
	FILE* fp = fopen(gfile, "r");
	if (!fp) {
		printf("读取图数据文件出错！\n");
		exit(0);
	}
	char bv[10];
	//读取图的基本信息
	fscanf(fp, "%u%u%s", &(g->nv), &(g->ne), bv);
	//printf("%d %d %s", g->ne, g->nv, bv);
	g->weighted = strcmp(bv, "true") == 0 ? true : false;
	fscanf(fp, "%s", bv);
	g->dirctional = strcmp(bv, "true") == 0 ? true : false;
	//读取顶点信息
	for (int i = 0; i < g->nv; i++) {
		fscanf(fp, "%d%d", &(g->v[i].id), &(g->v[i].w));
		g->v[i].degree = 0;
		//printf("顶点%d-权%d\n", g->v[i].id, g->v[i].w);
	}
	//读取边信息
	for (unsigned long i = 0; i < g->ne; i++) {
		fscanf(fp, "%u%u%d", &(g->e[i].h), &(g->e[i].t), &(g->e[i].w));
		//printf("边:%u-%u=>%d\n", g->e[i].h, g->e[i].t, g->e[i].w);
		g->e[i].id = i;
		unsigned h, t;
		h = g->e[i].h;
		t = g->e[i].t;
		g->v[h].edges[g->v[h].degree++] = i;	// 出度 
		if(g->dirctional==false)
			g->v[t].edges[g->v[t].degree++] = i;	// 入度 
	}
	g->vidmax = g->nv - 1;	// do
	g->eidmax = g->ne - 1;	// do
	fclose(fp);
}

// 生成一个空图
Graph* initGraph(bool directional, bool weighted){
	Graph * g = (Graph *)malloc(sizeof(Graph));
	g->nv = g->ne = 0;
	g->dirctional = directional;
	g->weighted = weighted;
	g->vidmax = -1;	// do
	g->eidmax = -1;	// do
	return g;
}

//打印邻接表的信息
void printgraph(Graph* g) {
	// do
	printf("图的基本信息:顶点数(%u)-边数(%lu)-顶点的最大id(%u)-边的最大id(%lu)-%s-%s\n", g->nv, g->ne, g->vidmax, g->eidmax, g->weighted ? "加权图" : "等权图", g->dirctional ? "有向图" : "无向图");
	for (int i = 0; i < g->nv; i++) {
		printf("ID(%u)-度(%d)-权(%d)-边表 t(eid|w):%u", g->v[i].id, g->v[i].degree, g->v[i].w, g->v[i].id);
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

//查找给定编号的顶点，返回其顶点数组下标
int getVexIdx(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return i;
	printf("input wrong vertex id in getVexIdx()!\n");
	exit(0);
}

//查找给定编号的顶点，返回其权值
int getVexW(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].w;
	printf("input wrong vertex id in getVexW()!\n");
	exit(0);
}

//查找给定编号的顶点，返回其度
int getVexDegree(Graph* g, int id) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].degree;
	printf("input wrong vertex id in getVexDegree()!\n");
	exit(0);
}

//查找给定编号的顶点,返回其所有边
int* getEdgesByNode(Graph* g, int id, int* ne) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id) {
			*ne = g->v[i].degree;
			return g->v[i].edges;
		}
	printf("input wrong vertex id in getEdgesByNode()!\n");
	exit(0);
}

//查找给定编号的边，返回其边数组下标
int getEdgeIdx(Graph* g, int id) {
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return i;
	printf("input wrong edge id in getEdgeIdx()!\n");
	exit(0);
}

//查找给定编号的边，返回其权值
int getEdgeW(Graph* g, int id) {
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return g->e[i].w;
	printf("input wrong edge id in getEdgeW()!\n");
	exit(0);
}

//查找给定编号的边，返回其两个顶点
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

//通过权值查找顶点编号
int locateVex(Graph* g, int w) {
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].w == w)
			return g->v[i].id;
	return -1;
}

//通过权值查找边编号
int locateEdge(Graph* g, int w) {
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].w == w)
			return g->e[i].id;
	return -1;
}

//设置或改变顶点权值
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

//设置或改变边权值
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

//删除边
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


//删除顶点，同时与其关联的边全部删除
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


//增加顶点
void addVex(Graph* g, int w) {
	int nv = g->nv;
	g->nv ++;
	g->v[nv].id = g->vidmax + 1;	// do
	g->vidmax ++;
	g->v[nv].degree = 0;
	g->v[nv].w = w;
}

//增加边
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
	puts("已经生成初始图！");
	
	printf("%d\n", g->v[8].id);
	printf("%d\n", g->v[8].degree);
	printf("%d\n", g->nv);
	
	getchar();
	deleteVex(g, 3);
	saveGraph(g,"net.html");
	puts("删除掉了id为3的结点！"); 
	
	printf("%d\n", g->v[8].id);
	printf("%d\n", g->v[8].degree);
	printf("%d\n", g->nv);
	
	getchar(); 
	addVex(g, 30);
	addEdge(g, 50, 8, 10);
	saveGraph(g,"net.html");
	puts("已经添加了权为30的顶点和权为50，头尾结点为8和10的边！"); 
	
	printf("%d\n", g->v[8].id);
	printf("%d\n", g->v[8].degree);
	printf("%d\n", g->nv);
	getchar();
	int *h = (int *)malloc(sizeof(int));
	int *t = (int *)malloc(sizeof(int));
	getVexByEdge(g, 5, h, t);
	printf("id为5的边的头尾结点id为%d和%d\n", *h, *t);
	
	getchar(); 
	addVex(g, 66);
	addEdge(g, 50, 5, 11);
	saveGraph(g,"net.html");
	puts("已经添加了权为60的顶点和权为50，头尾结点为5和11的边！"); 
	
	
	getchar(); 
	setVexW(g, 6, 99);
	setEdgeW(g, 15, 100);
	saveGraph(g,"net.html");
	puts("更改了id为6的顶点权为99，id为15的边权为100");
	
} 
#endif
