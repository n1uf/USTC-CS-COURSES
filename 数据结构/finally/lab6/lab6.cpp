#ifndef _HUFFMANTREE_CPP_
#define _HUFFMANTREE_CPP_
//哈夫曼树 ：分配连续存储空间存储树 

#include <stdio.h>
#include <stdlib.h>

//编码的最大长度 
#define MCL 30 
//定义叶节点数,8bit的unsigned char 
#define n 256
//定义结点总数，2n-1 
#define m 511 

#define codetype unsigned long long

//定义树结点，包括三个指针父节点，左右孩子 
/*typedef struct HTNode {
	unsigned char id;
	long w;
	int parent, lchild, rchild;
} HTNode;*/

// 改为三叉链表
typedef struct HTNode{
	unsigned id;
	long w; 
  	struct HTNode * parent,* lchild, * rchild;
} HTNode; 


typedef struct {
	codetype code; //前面都是0，最后len位是编码 
	int len;   //编码长度 
} HCode;      //哈夫曼编码表

void printHtree1(HTNode ht[]); //函数声明 

void DestroyTree(HTNode *root){
	if (root->lchild) {DestroyTree(root->lchild);root->lchild=NULL;}
	if (root->rchild) {DestroyTree(root->rchild);root->rchild=NULL;}
	if (!root->lchild && !root->rchild)
		free(root);  //左右子树均为空时释放根结点空间
}

/*** 以下代码哈夫曼树生成 ***/
//构造哈夫曼树/二叉树,输入长度为n=256的权向量w（每个字符出现的次数）
HTNode *createHTree(long* w) {
	long allw = 0;    //allw为总权值
	int numZero = 0;  
	HTNode *node[m];   //用一个结点的指针数组寻找各个结点
	for (int i = 0; i < m; ++i) {
		node[i] = (HTNode *)malloc(sizeof(HTNode)); //创建结点
	    if (!node[i]) 
			exit(0);   //检验是否分配空间成功
		node[i]->id = i;
		//printf("%d\n",node[i]->id);
		node[i]->parent = node[i]->lchild = node[i]->rchild = NULL;  //初始化，双亲和孩子结点均指向空
		node[i]->w = 0;
		if (i < n) {
			node[i]->w = w[i];
			if (w[i] == 0) numZero++; //统计没出现的字符个数 
			allw += w[i];
		}
	} //初始化哈夫曼树，每个结点构成一棵树 

	int i = n, j;
	long min1, min2;
	while (i < m - numZero) {
		min1 = min2 = allw + 10; //设置最大的w值 
		unsigned pos1, pos2;
		for (j = 0; j < i; j++) {
			if (node[j]->w == 0) //忽略权值为0的结点 
				continue;
			if (node[j]->parent == NULL)   //只找某棵树的根结点进行比较
				if (node[j]->w < min1) {
					pos2 = pos1;
					min2 = min1;  //原本的最小变为第二小
					pos1 = j;
					min1 = node[j]->w;
				} //min1<min2,找到比min1更小的ht[j].w，那么min1替代min2， ht[j].w替代min1
				else {
					if (node[j]->w < min2) { //min1 <= node[j].w < min2 
						pos2 = j;
						min2 = node[j]->w;   //则min2变为node[j].w
					}
				}
		}//内层for结束，找到pos1,pos2最小的两个权值，准备构造非叶节点

		node[i]->lchild = node[pos1];  //小权值为左孩子
		node[pos1]->parent =node[i];
		node[i]->rchild = node[pos2];  //另一个为右孩子
		node[pos2]->parent =node[i];   //同时要改变子结点的父结点
		//printf("%d\n",node[i]->id);
		node[i]->w = min1 + min2;    //新的树根结点权值为2者相加
		i++;   //进入下一个循环
	}
	
	//释放空间
	//for(i = m - numZero; i < m; i++)
	//	free(node[i]);
	for(i = 0; i < m; i++)
		if(node[i]->w = 0)
			free(node[i]);
	return node[m-numZero-1]; //返回哈夫曼树的根结点
}      

//给定二叉树根结点，遍历二叉树 (先序遍历） 输出id和w
void printHtree0(HTNode *root) {
	if (root){//递归出口 
		printf("%3d->%5d\n", root->id , root->w);
		if(root->parent)
		    printf("%d\n",root->parent->id);
		printHtree0(root->lchild);
		printHtree0(root->rchild);
	}
}

//由结点的id（可以改成其它数据域的值）查找结点，返回结点指针 。(先序遍历） 
HTNode *locateByID(HTNode *root, int id) {
	if (!root) 
		return NULL;
	if (root->id == id) 
		return root;    //找到目标值时返回相应结点
	HTNode *t = locateByID(root->lchild,id);  //否则在左右子树中递归查找
	if (t) return t;
	return locateByID(root->rchild,id);
}

/*
//直接当数组打印出来，调试用
void printHtree1(HTNode ht[]){
	printf("\n哈夫曼树(数组次序)：\n");
	for(int i=0;i<m;++i)
		if (i<n)
			printf("%2x %3d -> %5d => p:%3d lc:%3d rc:%3d\n",ht[i].id,ht[i].id, ht[i].w, ht[i].parent, ht[i].lchild,ht[i].rchild);
		else
			printf("%2x %3d -> %5d => p:%3d lc:%3d rc:%3d\n",ht[i].id,ht[i].id+256, ht[i].w, ht[i].parent, ht[i].lchild,ht[i].rchild);
}
*/

/*** 以下代码分析文件和从文件中生成哈夫曼编码表 ***/

//从filename中二进制读取字符，统计每个字符出现的次数，写入w并返回 
//w数组长度为256，如果字符不足256，那么没出现的字符权值为0  
unsigned char* parseFile(const char filename[], long* w, long* fsize) {
	FILE* fp = fopen(filename, "rb");  //二进制只读模式
	if (fp == NULL) {
		printf("Can not open the File!\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_END);   //将指针移到文件结尾处
	*fsize = ftell(fp);       //获取指针当前位置（即获取文件字符数量）
	rewind(fp);               //将指针指向文件头
	unsigned char* dataArray;
	dataArray = (unsigned char*)malloc(sizeof(unsigned char) * (*fsize));
	if (!dataArray) {
		printf("Memory is not enough!\n");
		exit(0);
	}
	fread(dataArray, sizeof(unsigned char), *fsize, fp);   //读取待压缩文件，将二进制数据读取到dataArray
	fclose(fp);   //关闭文件

	for (int i = 0; i < n; ++i) //权值清空 
		w[i] = 0;
    
	for (int i = 0; i < *fsize; ++i) //权值+1，若对应字符出现 
		w[dataArray[i]]++;    //若读到某个字符，则其编码对应的w加一

	return dataArray;
}

//输入任何字符c，得到它的哈夫曼编码, 被genCodes()调用 
void getCode(HTNode *root, int c, codetype* code1, int* clen1) {
	int clen = 0;        //编码长度 
	codetype code = 0;   //编码 

	int size = sizeof(code);  //编码的最大bits数 
	codetype mask = 1ull << (size * 8 - 1); //最高位为1其它为0，用来设置最高位为1 (掩码？)

	HTNode *p = locateByID(root, c);  //定位代表c的结点的位置
	//printf("%d %d \n",p->id, (p->parent)->id);
	HTNode *p_parent = p->parent;
	while (p_parent) {   //当未到达根结点时不断寻找父结点
		code = code >> 1;  //右移一位，即此时最高位变为0
		(p_parent->lchild == p) ? code : (code = code | mask); //如果是右孩子，那么最高位设置为1，否则是左孩子最高位就是0 
		clen++;
		//printf("%u\n", code);
		p = p->parent;
		p_parent = p_parent->parent;  //向根结点移动
	}
    
	//code的前面clen位是哈夫曼编码，将其移动到最后
	code = code >> (size * 8 - clen);
	//printf("0x%x-%d\n",code,clen);
	*code1 = code;  //返回值 
	*clen1 = clen;  //返回值 
}

//从哈夫曼树ht生成完整的编码表hc，输出hc为encode()的输入参数 
void getHCodes(HCode hc[], HTNode *root, long w[256]) {
	for (int i = 0; i < n; ++i)
	{
		//printf("%d times\n", i);
		if(w[i] > 0)  //当w！=0时求其编码
			getCode(root, i, &(hc[i].code), &(hc[i].len));
	}
}

/*** 以下为编解码实现 ***/

//编码,原长olen的内容orgi，压缩编码后为长nlen的内容newc，需要利用编码表hc  (这个部分没用上哈夫曼树)
void encode(unsigned char* orgi, long olen, unsigned char* newc, long* nlen, HCode hc[]) {
	int sizec = sizeof(unsigned int);  //要确保字符编码的最大长度要小于sizec*8-8 
	long i = 0; //orgi的下标 
	long j = 0; //newc的下标 
	newc[j] = 0;
	codetype code;
	int len;
	int usedbits = 0; //newc[j]中被占用的bits数 
	while (i < olen) {//对原始数据逐个字符处理 
		int idx = orgi[i]; //获得hc下标
		code = hc[idx].code;  //从编码表获取长度及编码
		len = hc[idx].len;
		while (len + usedbits >= 8) {//code需要左移usedbits长的一段，然后和newc[j]位或操作 （？）
			codetype code1 = code >> len + usedbits - 8;
			newc[j] = newc[j] | code1; //填满前一个编码字符 
			len = len + usedbits - 8;      //code现在有效长度
			usedbits = 0;
			newc[++j] = 0;
			//printf("\n编码的第 %d 个字符为：#%2x\n",j-1,newc[j-1]);
		}//循环，使得len+usedbits <8
		//将code的前面各位清0,因为有效位是len
		code = code & ((1ull << len) - 1); //code和后面k个1，其它全为0的数据进行与，保留后面len位 
		code = code << 8 - len - usedbits;//向前移动若干位 
		newc[j] = newc[j] | code;
		usedbits = len + usedbits;
		i++;
	}
	*nlen = j + 1;
}

//将哈夫曼树先序输入到文件中(但是无法读出)
/*void printHtree_file(HTNode *root, FILE *fp) {
	if (root){//递归出口 
		fwrite(root, sizeof(HTNode), 1, fp); 
		printHtree_file(root->lchild);
		printHtree_file(root->rchild);
	}
}*/

void printhc(HCode hc[])
{
	for(int i = 0; i < n; i++)
		printf("%u - %d\n",hc[i].code, hc[i].len);
}

//生成和保存压缩文件,被压缩文件fin，指定文件名fout，将所用的哈夫曼树存入文件 
void zip(char fin[], char fout[]) {
	HCode hc[n]={0};    //结构体数组，表示哈夫曼编码表 :code,len，用于编码文件 
	long wDist[256]; //保存字符的分布（字符在文件中出现的次数） 
	long fsize;      //文件长度 
	//获取文件内容，分析待压缩文件，返回权值向量wDist,文件内容content和长度fsize 
	unsigned char* content = parseFile(fin, wDist, &fsize);

	// 生成压缩树（H树）		 
	HTNode *ht = createHTree(wDist); //root是哈夫曼树ht的根结点的下标 
	//printHtree0(ht);  //输出哈夫曼树检查
	getHCodes(hc, ht, wDist);	//生成完整的编码表,用于编码文件 
    //printhc(hc);   //打印编码
    
	//下面的代码用于测试哈夫曼树 
	//printHtree1(ht); //将哈夫曼树按数组打印出来 	
	//printHtree0(ht,root); //先序遍历哈夫曼树 
	//saveTree(ht,root,"aa1.html"); //图形展示哈夫曼树 , 请先导入showgt.h
	
	// 开始压缩
	unsigned char* zipContent; //编码后的内容	
	long zipsize;//压缩后文件大小 
	zipContent = (unsigned char*)malloc(sizeof(unsigned char) * (fsize + 10000)); //压缩后的文件可能更大，考虑将fsize扩大一点 
	if (!zipContent) {
		printf("The memory is not enough!\n");
		exit(0);
	}
	encode(content, fsize, zipContent, &zipsize, hc); //编码后返回长度zipsize的内容zipContent 

	FILE* fp = fopen(fout, "wb");
	if (fp == NULL) {
		printf("Can not open the file!\n");
		exit(0);
	}
	//long ht_size = sizeof(HTNode) * m;      //哈夫曼树的大小 
	//fwrite(&ht_size, sizeof(ht_size), 1, fp);//保存哈夫曼树的大小
	//long hc_size = sizeof(HCode) * n;      //哈夫曼编码表的大小 
	//fwrite(&hc_size, sizeof(hc_size), 1, fp);//保存哈夫曼编码表的大小
	//fwrite(&root, sizeof(root), 1, fp);      //保存哈夫曼树根节点的下标
	//fwrite(ht, sizeof(HTNode), m, fp);       //保存哈夫曼树 ，解码要用到 
	//链表不能用以上方法写入，若将哈夫曼树先序输入到文件中，可能无法读出
	//fwrite(hc, sizeof(HCode), n, fp);   //所以选择输出编码表(编码表也不太行，因为解码过程要一一比对，时间复杂度高)
	fwrite(&zipsize, sizeof(zipsize), 1, fp);//保存编码内容的大小 
	fwrite(&fsize, sizeof(fsize), 1, fp);    //保存原始内容的大小 
	fwrite(wDist, sizeof(wDist), 1, fp);  //将权值写入，可以用于重构哈夫曼树
	
	fwrite(zipContent, sizeof(unsigned char), zipsize, fp);//保存编码后的内容 
	fclose(fp);

	free(zipContent);	//释放文件内容
	free(content);
	printf("The compressed file: %s has been generated!\n", fout);
	DestroyTree(ht);
}


//读取压缩文件，解压 
void unzip(char zfile[], char ofile[]) {
	FILE* fp = fopen(zfile, "rb");
	if (fp == NULL) {
		printf("Can not open the file to read!\n");
		exit(0);
	}
	long zipsize1, fsize1;
	//int root; //树的根结点下标 
	//fread(&ht_size1, sizeof(ht_size1), 1, fp); //哈夫曼树的大小(字节数） 
	//fread(&hc_size1, sizeof(hc_size1), 1, fp); //哈夫曼编码表的大小(字节数）
	fread(&zipsize1, sizeof(zipsize1), 1, fp); //压缩后内容的大小 
	fread(&fsize1, sizeof(fsize1), 1, fp);     //被压缩内容的大小 (原)
	//fread(&root, sizeof(root), 1, fp);         //哈夫曼树根的下标 

	unsigned char* zcontent = (unsigned char*)malloc(zipsize1);//存放读取的编码数据 
	unsigned char* ocontent = (unsigned char*)malloc(fsize1);//解码后的数据 
	//HCode hc1[n];
	//fread(hc1, hc_size1, 1, fp);//读取哈夫曼编码表
	long w1[n];
	fread(w1, sizeof(w1), 1, fp);   //读取权值数组  
	fread(zcontent, zipsize1, 1, fp); //读取编码数据
	fclose(fp);
	
	//根据w1[]重新构建哈夫曼树ht1
    HTNode *root = createHTree(w1); //root是哈夫曼树ht的根结点的下标 
    
	fp = fopen(ofile, "wb");
	if (fp == NULL) {
		printf("Can not decompress!\n");
		exit(0);
	}

	HTNode *p = root; //从根结点开始 
	int j, k = 0, i = 0;//zcontent的下标 k,ocontent的下标i 
	while (i < fsize1) {//依次写入解压后数据的每个字节 
		j = 128; //10000000 
		while (j > 0) {
			if ((zcontent[k] & j) > 0) 
			{ //向右走 1
				if (p->rchild == NULL) 
				{
					ocontent[i++] = p->id;
					p = root;//解码了下一个字符的第一个bit 
					j = j << 1;
				}
				else
					p = p->rchild;
			}
			else
			{//向左走 0
				if (p->lchild == NULL) 
				{
					ocontent[i++] = p->id;
					p = root;//解码了下一个字符的第一个bit 
					j = j << 1;
				}
				else
					p = p->lchild;
			}
			j = j >> 1; //j控制while循环8次，求出zcontent[k]的每一位 
		}
		k++;//准备读取下一个字符 
	}
//	for(int i = 0; i<fsize1; i++) 
//	{
//		printf("%d:%d \n",i , ocontent[i]);
//	}
	fwrite(ocontent, fsize1, 1, fp);	// 将解压内容写入文件
	fclose(fp);
	free(ocontent);
	free(zcontent);
	printf("The file: %s has been decompressed to: %s !\n", zfile, ofile);
	DestroyTree(root);
}

int check(char file1[], char file2[]){	// 返回1说明文件一样，返回0说明文件不一样
	FILE *fp1 = fopen(file1,"rb"), *fp2 = fopen(file2,"rb");
	unsigned fsize1,fsize2;
	fseek(fp1, 0, SEEK_END);	fseek(fp2, 0, SEEK_END);
	fsize1 = ftell(fp1);		fsize2 = ftell(fp2);
	rewind(fp1);				rewind(fp2);
	if(fsize1 != fsize2) return 0;
    char c1,c2;	
	/*for(int i=0;i<fsize2;i++)
	{
		fread(&c2,1,1,fp2);
		printf("%d %d\n",i,c2);
	}*/
	rewind(fp2);
	for(unsigned i = 0; i < fsize1; ++i){
		fread(&c1,1,1,fp1);		fread(&c2,1,1,fp2);
		if(c1 != c2) return printf("at fsize = %d, c1 is %d, c2 is %d\n",i,c1,c2);
	}
	fclose(fp1);				fclose(fp2);
	return 1;
}


int main() {

	/*char infile[256] = "string.c"; 		//  被压缩文件名
	char zfile[256] = "string.c.myzip"; 		//  压缩文件名
	char ofile[256] = "myout_string.c";	//	解压文件名
	zip(infile, zfile);	// 压缩
	unzip(zfile, ofile); // 解压 */
	
	// 压缩一个图片
	/*char infile1[256] = "LUO.jpg"; 		//  被压缩文件名
	char zfile1[256] = "LUO.jpg.myzip"; 		//  压缩文件名
	char ofile1[256] = "myout_LUO.jpg";	//	解压文件名
	zip(infile1, zfile1);	// 压缩
	unzip(zfile1, ofile1); // 解压*/
    
    
    // 压缩一个图片
    zip("pic.png","pic.png.myzip");
	unzip("pic.png.myzip","myout_pic.png");
	printf("%d\n",check("pic.png","myout_pic.png"));
	// 压缩一个pdf
	zip("lab6.pdf","lab6.pdf.myzip");
	unzip("lab6.pdf.myzip","myout_lab6.pdf");
	printf("%d\n",check("lab6.pdf","myout_lab6.pdf"));
	// 压缩一个文件
	zip("test","test.myzip");
	unzip("test.myzip","myout_test");
	printf("%d\n",check("test","myout_test"));
	return 1;
	
}

#endif

