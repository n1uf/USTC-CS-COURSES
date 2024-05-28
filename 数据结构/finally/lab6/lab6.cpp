#ifndef _HUFFMANTREE_CPP_
#define _HUFFMANTREE_CPP_
//�������� �����������洢�ռ�洢�� 

#include <stdio.h>
#include <stdlib.h>

//�������󳤶� 
#define MCL 30 
//����Ҷ�ڵ���,8bit��unsigned char 
#define n 256
//������������2n-1 
#define m 511 

#define codetype unsigned long long

//��������㣬��������ָ�븸�ڵ㣬���Һ��� 
/*typedef struct HTNode {
	unsigned char id;
	long w;
	int parent, lchild, rchild;
} HTNode;*/

// ��Ϊ��������
typedef struct HTNode{
	unsigned id;
	long w; 
  	struct HTNode * parent,* lchild, * rchild;
} HTNode; 


typedef struct {
	codetype code; //ǰ�涼��0�����lenλ�Ǳ��� 
	int len;   //���볤�� 
} HCode;      //�����������

void printHtree1(HTNode ht[]); //�������� 

void DestroyTree(HTNode *root){
	if (root->lchild) {DestroyTree(root->lchild);root->lchild=NULL;}
	if (root->rchild) {DestroyTree(root->rchild);root->rchild=NULL;}
	if (!root->lchild && !root->rchild)
		free(root);  //����������Ϊ��ʱ�ͷŸ����ռ�
}

/*** ���´�������������� ***/
//�����������/������,���볤��Ϊn=256��Ȩ����w��ÿ���ַ����ֵĴ�����
HTNode *createHTree(long* w) {
	long allw = 0;    //allwΪ��Ȩֵ
	int numZero = 0;  
	HTNode *node[m];   //��һ������ָ������Ѱ�Ҹ������
	for (int i = 0; i < m; ++i) {
		node[i] = (HTNode *)malloc(sizeof(HTNode)); //�������
	    if (!node[i]) 
			exit(0);   //�����Ƿ����ռ�ɹ�
		node[i]->id = i;
		//printf("%d\n",node[i]->id);
		node[i]->parent = node[i]->lchild = node[i]->rchild = NULL;  //��ʼ����˫�׺ͺ��ӽ���ָ���
		node[i]->w = 0;
		if (i < n) {
			node[i]->w = w[i];
			if (w[i] == 0) numZero++; //ͳ��û���ֵ��ַ����� 
			allw += w[i];
		}
	} //��ʼ������������ÿ����㹹��һ���� 

	int i = n, j;
	long min1, min2;
	while (i < m - numZero) {
		min1 = min2 = allw + 10; //��������wֵ 
		unsigned pos1, pos2;
		for (j = 0; j < i; j++) {
			if (node[j]->w == 0) //����ȨֵΪ0�Ľ�� 
				continue;
			if (node[j]->parent == NULL)   //ֻ��ĳ�����ĸ������бȽ�
				if (node[j]->w < min1) {
					pos2 = pos1;
					min2 = min1;  //ԭ������С��Ϊ�ڶ�С
					pos1 = j;
					min1 = node[j]->w;
				} //min1<min2,�ҵ���min1��С��ht[j].w����ômin1���min2�� ht[j].w���min1
				else {
					if (node[j]->w < min2) { //min1 <= node[j].w < min2 
						pos2 = j;
						min2 = node[j]->w;   //��min2��Ϊnode[j].w
					}
				}
		}//�ڲ�for�������ҵ�pos1,pos2��С������Ȩֵ��׼�������Ҷ�ڵ�

		node[i]->lchild = node[pos1];  //СȨֵΪ����
		node[pos1]->parent =node[i];
		node[i]->rchild = node[pos2];  //��һ��Ϊ�Һ���
		node[pos2]->parent =node[i];   //ͬʱҪ�ı��ӽ��ĸ����
		//printf("%d\n",node[i]->id);
		node[i]->w = min1 + min2;    //�µ��������ȨֵΪ2�����
		i++;   //������һ��ѭ��
	}
	
	//�ͷſռ�
	//for(i = m - numZero; i < m; i++)
	//	free(node[i]);
	for(i = 0; i < m; i++)
		if(node[i]->w = 0)
			free(node[i]);
	return node[m-numZero-1]; //���ع��������ĸ����
}      

//��������������㣬���������� (��������� ���id��w
void printHtree0(HTNode *root) {
	if (root){//�ݹ���� 
		printf("%3d->%5d\n", root->id , root->w);
		if(root->parent)
		    printf("%d\n",root->parent->id);
		printHtree0(root->lchild);
		printHtree0(root->rchild);
	}
}

//�ɽ���id�����Ըĳ������������ֵ�����ҽ�㣬���ؽ��ָ�� ��(��������� 
HTNode *locateByID(HTNode *root, int id) {
	if (!root) 
		return NULL;
	if (root->id == id) 
		return root;    //�ҵ�Ŀ��ֵʱ������Ӧ���
	HTNode *t = locateByID(root->lchild,id);  //���������������еݹ����
	if (t) return t;
	return locateByID(root->rchild,id);
}

/*
//ֱ�ӵ������ӡ������������
void printHtree1(HTNode ht[]){
	printf("\n��������(�������)��\n");
	for(int i=0;i<m;++i)
		if (i<n)
			printf("%2x %3d -> %5d => p:%3d lc:%3d rc:%3d\n",ht[i].id,ht[i].id, ht[i].w, ht[i].parent, ht[i].lchild,ht[i].rchild);
		else
			printf("%2x %3d -> %5d => p:%3d lc:%3d rc:%3d\n",ht[i].id,ht[i].id+256, ht[i].w, ht[i].parent, ht[i].lchild,ht[i].rchild);
}
*/

/*** ���´�������ļ��ʹ��ļ������ɹ���������� ***/

//��filename�ж����ƶ�ȡ�ַ���ͳ��ÿ���ַ����ֵĴ�����д��w������ 
//w���鳤��Ϊ256������ַ�����256����ôû���ֵ��ַ�ȨֵΪ0  
unsigned char* parseFile(const char filename[], long* w, long* fsize) {
	FILE* fp = fopen(filename, "rb");  //������ֻ��ģʽ
	if (fp == NULL) {
		printf("Can not open the File!\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_END);   //��ָ���Ƶ��ļ���β��
	*fsize = ftell(fp);       //��ȡָ�뵱ǰλ�ã�����ȡ�ļ��ַ�������
	rewind(fp);               //��ָ��ָ���ļ�ͷ
	unsigned char* dataArray;
	dataArray = (unsigned char*)malloc(sizeof(unsigned char) * (*fsize));
	if (!dataArray) {
		printf("Memory is not enough!\n");
		exit(0);
	}
	fread(dataArray, sizeof(unsigned char), *fsize, fp);   //��ȡ��ѹ���ļ��������������ݶ�ȡ��dataArray
	fclose(fp);   //�ر��ļ�

	for (int i = 0; i < n; ++i) //Ȩֵ��� 
		w[i] = 0;
    
	for (int i = 0; i < *fsize; ++i) //Ȩֵ+1������Ӧ�ַ����� 
		w[dataArray[i]]++;    //������ĳ���ַ�����������Ӧ��w��һ

	return dataArray;
}

//�����κ��ַ�c���õ����Ĺ���������, ��genCodes()���� 
void getCode(HTNode *root, int c, codetype* code1, int* clen1) {
	int clen = 0;        //���볤�� 
	codetype code = 0;   //���� 

	int size = sizeof(code);  //��������bits�� 
	codetype mask = 1ull << (size * 8 - 1); //���λΪ1����Ϊ0�������������λΪ1 (���룿)

	HTNode *p = locateByID(root, c);  //��λ����c�Ľ���λ��
	//printf("%d %d \n",p->id, (p->parent)->id);
	HTNode *p_parent = p->parent;
	while (p_parent) {   //��δ��������ʱ����Ѱ�Ҹ����
		code = code >> 1;  //����һλ������ʱ���λ��Ϊ0
		(p_parent->lchild == p) ? code : (code = code | mask); //������Һ��ӣ���ô���λ����Ϊ1���������������λ����0 
		clen++;
		//printf("%u\n", code);
		p = p->parent;
		p_parent = p_parent->parent;  //�������ƶ�
	}
    
	//code��ǰ��clenλ�ǹ��������룬�����ƶ������
	code = code >> (size * 8 - clen);
	//printf("0x%x-%d\n",code,clen);
	*code1 = code;  //����ֵ 
	*clen1 = clen;  //����ֵ 
}

//�ӹ�������ht���������ı����hc�����hcΪencode()��������� 
void getHCodes(HCode hc[], HTNode *root, long w[256]) {
	for (int i = 0; i < n; ++i)
	{
		//printf("%d times\n", i);
		if(w[i] > 0)  //��w��=0ʱ�������
			getCode(root, i, &(hc[i].code), &(hc[i].len));
	}
}

/*** ����Ϊ�����ʵ�� ***/

//����,ԭ��olen������orgi��ѹ�������Ϊ��nlen������newc����Ҫ���ñ����hc  (�������û���Ϲ�������)
void encode(unsigned char* orgi, long olen, unsigned char* newc, long* nlen, HCode hc[]) {
	int sizec = sizeof(unsigned int);  //Ҫȷ���ַ��������󳤶�ҪС��sizec*8-8 
	long i = 0; //orgi���±� 
	long j = 0; //newc���±� 
	newc[j] = 0;
	codetype code;
	int len;
	int usedbits = 0; //newc[j]�б�ռ�õ�bits�� 
	while (i < olen) {//��ԭʼ��������ַ����� 
		int idx = orgi[i]; //���hc�±�
		code = hc[idx].code;  //�ӱ�����ȡ���ȼ�����
		len = hc[idx].len;
		while (len + usedbits >= 8) {//code��Ҫ����usedbits����һ�Σ�Ȼ���newc[j]λ����� ������
			codetype code1 = code >> len + usedbits - 8;
			newc[j] = newc[j] | code1; //����ǰһ�������ַ� 
			len = len + usedbits - 8;      //code������Ч����
			usedbits = 0;
			newc[++j] = 0;
			//printf("\n����ĵ� %d ���ַ�Ϊ��#%2x\n",j-1,newc[j-1]);
		}//ѭ����ʹ��len+usedbits <8
		//��code��ǰ���λ��0,��Ϊ��Чλ��len
		code = code & ((1ull << len) - 1); //code�ͺ���k��1������ȫΪ0�����ݽ����룬��������lenλ 
		code = code << 8 - len - usedbits;//��ǰ�ƶ�����λ 
		newc[j] = newc[j] | code;
		usedbits = len + usedbits;
		i++;
	}
	*nlen = j + 1;
}

//�����������������뵽�ļ���(�����޷�����)
/*void printHtree_file(HTNode *root, FILE *fp) {
	if (root){//�ݹ���� 
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

//���ɺͱ���ѹ���ļ�,��ѹ���ļ�fin��ָ���ļ���fout�������õĹ������������ļ� 
void zip(char fin[], char fout[]) {
	HCode hc[n]={0};    //�ṹ�����飬��ʾ����������� :code,len�����ڱ����ļ� 
	long wDist[256]; //�����ַ��ķֲ����ַ����ļ��г��ֵĴ����� 
	long fsize;      //�ļ����� 
	//��ȡ�ļ����ݣ�������ѹ���ļ�������Ȩֵ����wDist,�ļ�����content�ͳ���fsize 
	unsigned char* content = parseFile(fin, wDist, &fsize);

	// ����ѹ������H����		 
	HTNode *ht = createHTree(wDist); //root�ǹ�������ht�ĸ������±� 
	//printHtree0(ht);  //��������������
	getHCodes(hc, ht, wDist);	//���������ı����,���ڱ����ļ� 
    //printhc(hc);   //��ӡ����
    
	//����Ĵ������ڲ��Թ������� 
	//printHtree1(ht); //�����������������ӡ���� 	
	//printHtree0(ht,root); //��������������� 
	//saveTree(ht,root,"aa1.html"); //ͼ��չʾ�������� , ���ȵ���showgt.h
	
	// ��ʼѹ��
	unsigned char* zipContent; //����������	
	long zipsize;//ѹ�����ļ���С 
	zipContent = (unsigned char*)malloc(sizeof(unsigned char) * (fsize + 10000)); //ѹ������ļ����ܸ��󣬿��ǽ�fsize����һ�� 
	if (!zipContent) {
		printf("The memory is not enough!\n");
		exit(0);
	}
	encode(content, fsize, zipContent, &zipsize, hc); //����󷵻س���zipsize������zipContent 

	FILE* fp = fopen(fout, "wb");
	if (fp == NULL) {
		printf("Can not open the file!\n");
		exit(0);
	}
	//long ht_size = sizeof(HTNode) * m;      //���������Ĵ�С 
	//fwrite(&ht_size, sizeof(ht_size), 1, fp);//������������Ĵ�С
	//long hc_size = sizeof(HCode) * n;      //�����������Ĵ�С 
	//fwrite(&hc_size, sizeof(hc_size), 1, fp);//��������������Ĵ�С
	//fwrite(&root, sizeof(root), 1, fp);      //��������������ڵ���±�
	//fwrite(ht, sizeof(HTNode), m, fp);       //����������� ������Ҫ�õ� 
	//�����������Ϸ���д�룬�������������������뵽�ļ��У������޷�����
	//fwrite(hc, sizeof(HCode), n, fp);   //����ѡ����������(�����Ҳ��̫�У���Ϊ�������Ҫһһ�ȶԣ�ʱ�临�Ӷȸ�)
	fwrite(&zipsize, sizeof(zipsize), 1, fp);//����������ݵĴ�С 
	fwrite(&fsize, sizeof(fsize), 1, fp);    //����ԭʼ���ݵĴ�С 
	fwrite(wDist, sizeof(wDist), 1, fp);  //��Ȩֵд�룬���������ع���������
	
	fwrite(zipContent, sizeof(unsigned char), zipsize, fp);//������������� 
	fclose(fp);

	free(zipContent);	//�ͷ��ļ�����
	free(content);
	printf("The compressed file: %s has been generated!\n", fout);
	DestroyTree(ht);
}


//��ȡѹ���ļ�����ѹ 
void unzip(char zfile[], char ofile[]) {
	FILE* fp = fopen(zfile, "rb");
	if (fp == NULL) {
		printf("Can not open the file to read!\n");
		exit(0);
	}
	long zipsize1, fsize1;
	//int root; //���ĸ�����±� 
	//fread(&ht_size1, sizeof(ht_size1), 1, fp); //���������Ĵ�С(�ֽ����� 
	//fread(&hc_size1, sizeof(hc_size1), 1, fp); //�����������Ĵ�С(�ֽ�����
	fread(&zipsize1, sizeof(zipsize1), 1, fp); //ѹ�������ݵĴ�С 
	fread(&fsize1, sizeof(fsize1), 1, fp);     //��ѹ�����ݵĴ�С (ԭ)
	//fread(&root, sizeof(root), 1, fp);         //�������������±� 

	unsigned char* zcontent = (unsigned char*)malloc(zipsize1);//��Ŷ�ȡ�ı������� 
	unsigned char* ocontent = (unsigned char*)malloc(fsize1);//���������� 
	//HCode hc1[n];
	//fread(hc1, hc_size1, 1, fp);//��ȡ�����������
	long w1[n];
	fread(w1, sizeof(w1), 1, fp);   //��ȡȨֵ����  
	fread(zcontent, zipsize1, 1, fp); //��ȡ��������
	fclose(fp);
	
	//����w1[]���¹�����������ht1
    HTNode *root = createHTree(w1); //root�ǹ�������ht�ĸ������±� 
    
	fp = fopen(ofile, "wb");
	if (fp == NULL) {
		printf("Can not decompress!\n");
		exit(0);
	}

	HTNode *p = root; //�Ӹ���㿪ʼ 
	int j, k = 0, i = 0;//zcontent���±� k,ocontent���±�i 
	while (i < fsize1) {//����д���ѹ�����ݵ�ÿ���ֽ� 
		j = 128; //10000000 
		while (j > 0) {
			if ((zcontent[k] & j) > 0) 
			{ //������ 1
				if (p->rchild == NULL) 
				{
					ocontent[i++] = p->id;
					p = root;//��������һ���ַ��ĵ�һ��bit 
					j = j << 1;
				}
				else
					p = p->rchild;
			}
			else
			{//������ 0
				if (p->lchild == NULL) 
				{
					ocontent[i++] = p->id;
					p = root;//��������һ���ַ��ĵ�һ��bit 
					j = j << 1;
				}
				else
					p = p->lchild;
			}
			j = j >> 1; //j����whileѭ��8�Σ����zcontent[k]��ÿһλ 
		}
		k++;//׼����ȡ��һ���ַ� 
	}
//	for(int i = 0; i<fsize1; i++) 
//	{
//		printf("%d:%d \n",i , ocontent[i]);
//	}
	fwrite(ocontent, fsize1, 1, fp);	// ����ѹ����д���ļ�
	fclose(fp);
	free(ocontent);
	free(zcontent);
	printf("The file: %s has been decompressed to: %s !\n", zfile, ofile);
	DestroyTree(root);
}

int check(char file1[], char file2[]){	// ����1˵���ļ�һ��������0˵���ļ���һ��
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

	/*char infile[256] = "string.c"; 		//  ��ѹ���ļ���
	char zfile[256] = "string.c.myzip"; 		//  ѹ���ļ���
	char ofile[256] = "myout_string.c";	//	��ѹ�ļ���
	zip(infile, zfile);	// ѹ��
	unzip(zfile, ofile); // ��ѹ */
	
	// ѹ��һ��ͼƬ
	/*char infile1[256] = "LUO.jpg"; 		//  ��ѹ���ļ���
	char zfile1[256] = "LUO.jpg.myzip"; 		//  ѹ���ļ���
	char ofile1[256] = "myout_LUO.jpg";	//	��ѹ�ļ���
	zip(infile1, zfile1);	// ѹ��
	unzip(zfile1, ofile1); // ��ѹ*/
    
    
    // ѹ��һ��ͼƬ
    zip("pic.png","pic.png.myzip");
	unzip("pic.png.myzip","myout_pic.png");
	printf("%d\n",check("pic.png","myout_pic.png"));
	// ѹ��һ��pdf
	zip("lab6.pdf","lab6.pdf.myzip");
	unzip("lab6.pdf.myzip","myout_lab6.pdf");
	printf("%d\n",check("lab6.pdf","myout_lab6.pdf"));
	// ѹ��һ���ļ�
	zip("test","test.myzip");
	unzip("test.myzip","myout_test");
	printf("%d\n",check("test","myout_test"));
	return 1;
	
}

#endif

