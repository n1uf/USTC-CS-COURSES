#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100		//��ʼ��ջ������ 
#define STACKINCREMENT 10		//���� 

/*�궨��ʵ��ջ�Ĳ��� #�����������ã�����stack ## _stackbase_ptr�Ϳ��Դ���
  int_stackbase_ptr�����ֲ�ͬ�������ݵ��йز���*/ 

//��ʼ��������ջ�ռ䣬��ʼ��ջָ���ջ��С 
#define initStack(stack) stack ## _stackbase_ptr = (stack *)malloc(sizeof(stack) * STACK_INIT_SIZE);\
						 if(stack ## _stackbase_ptr){\
						   stack ## _stacktop_ptr = stack ## _stackbase_ptr;\
						   stack ## _stacksize = STACK_INIT_SIZE;\
						 }else exit(0)

//�ж�ջ�գ����򷵻�true 
#define stackEmpty(stack) stack ## _stackbase_ptr == stack ## _stacktop_ptr ? 1:0

//ȡջ��Ԫ�أ�����e�У���ȷ��ջ�ǿգ���ȡջ��
#define getTop(stack, e) stack ## _stackbase_ptr == stack ## _stacktop_ptr ? 0 : (e = *(stack ## _stacktop_ptr -\
1), 1)						/* �����ö��ű��ʽ��ȡֵ���ź��1��ͬʱҲ������ȡջ��Ԫ�صĲ���������Ķ��ű��ʽͬ�� */ 

//���ջ
#define clearStack(stack) stack ## _stacktop_ptr = stack ## _stackbase_ptr

//ɾ��ջ�ռ� 
#define destroyStack(stack) free(stack ## _stackbase_ptr)

//��ջ�ĳ��� 
#define stackLength(stack) stack ## _stacktop_ptr - stack ## _stackbase_ptr

//��ջ�����ж�ջ�ǿգ���ȡջ��Ȼ��topָ������ 
#define pop(stack,e) (stack ## _stackbase_ptr == stack ## _stacktop_ptr)? 0:(e =*(-- stack ## _stacktop_ptr),1)

/* ��ջ�����ж�ջ�ռ��С�Ƿ񳬹���Ԥ�ȷ���Ŀռ䣬�����������ʹ��������չ�ռ䣬�ƶ�ջ��ָ�뵽�µĿռ����ײ㣬
   ��ջ�Ĵ�С��Ϊԭ�ȵĴ�С�������������Ԫ�����룬����topָ������ */ 
#define push(stack,e) if (stack ## _stacktop_ptr - stack ## _stackbase_ptr >= stack ## _stacksize){\
						stack ## _stackbase_ptr = (stack *)realloc(stack ## _stackbase_ptr, \
						   (stack ## _stacksize + STACKINCREMENT) * sizeof(stack));\
						if(! stack ## _stacktop_ptr) exit(0);\
						stack ## _stacktop_ptr = stack ## _stackbase_ptr + stack ## _stacksize;\
						stack ## _stacksize += STACKINCREMENT;}\
						*(stack ## _stacktop_ptr ++) = e;\
						printf("��ջ�ɹ�\n") 
						

//˳������ջ
unsigned int_stacksize;
int *int_stacktop_ptr;
int *int_stackbase_ptr;

//˳���ַ�ջ
unsigned char_stacksize;
char *char_stacktop_ptr;
char *char_stackbase_ptr;

//�ṹ��ջ 
typedef struct node
{
	int data[10];
	float x, y;
} tnode;

unsigned tnode_stacksize;
tnode *tnode_stacktop_ptr;
tnode *tnode_stackbase_ptr;


int main()
{
	
	//����ջ�Ĳ��� 
	initStack(int);
	
	int x;
	if(pop(int, x))									//��ջ���� 
		printf("��ջ�ɹ�����ջԪ��Ϊ %d \n", x); 
	else
		printf("ջ�գ����ܳ�ջ\n");
	
	printf("ջ���� %d ��Ԫ��\n", stackLength(int));
	
	if(getTop(int, x))								//ȡջ������ 
		printf("ջ��Ԫ���� %d \n", x);
	else
		printf("ջ�գ��޷�ȡջ��\n");
		 
			
	push(int, 6);									//��ջһ��Ԫ�� 
	printf("ջ���� %d ��Ԫ��\n", stackLength(int));	//�鿴ջ��Ԫ�ظ��� 
	
	push(int, 7);
	push(int, 8);									//��ջ����Ԫ�� 
	
	printf("ջ���� %d ��Ԫ��\n", stackLength(int));
	
	if(pop(int, x))									//��ջ 
		printf("��ջ�ɹ�����ջԪ��Ϊ %d \n", x); 
	else
		printf("ջ�գ����ܳ�ջ\n");
		
	printf("ջ���� %d ��Ԫ��\n", stackLength(int));
	
	if(getTop(int, x))								//ȡջ��Ԫ�أ��鿴��ջ�Ƿ�ɹ�
		printf("ջ��Ԫ���� %d \n", x);
	else
		printf("ջ�գ��޷�ȡջ��\n");
			
	clearStack(int);
	destroyStack(int);								//���ջɾ��ջ�ռ� 
	
	printf("------------------\n");
	
	
	//�ַ���ջ���� 
	initStack(char);
	
	char y;
	if(pop(char, y))								//��ջ���� 
		printf("��ջ�ɹ�����ջԪ��Ϊ %c ", y);
	else
		printf("ջ�գ��޷���ջ\n");
	
	printf("ջ���� %d ��Ԫ��\n", stackLength(char));//�鿴ջ��Ԫ�ظ��� 
	
	if(getTop(char, y))								//ȡջ��Ԫ�� 
		printf("ջ��Ԫ���� %c \n", y);
	else
		printf("ջ�գ��޷�ȡջ��\n");
	
	push(char, '1');								//��ջԪ�� 
	printf("ջ���� %d ��Ԫ��\n", stackLength(char));//�鿴Ԫ�ظ��� 
	
	push(char, 'b');
	printf("ջ���� %d ��Ԫ��\n", stackLength(char));
	
	if(pop(char, y))								//��ջ
		printf("��ջ�ɹ�����ջԪ��Ϊ %c \n", y);
	else
		printf("ջ�գ��޷���ջ\n");
	
	if(getTop(char, y))								//ȡջ��Ԫ�أ������Ƿ�ɹ� 
		printf("ջ��Ԫ���� %c \n", y);
	else
		printf("ջ�գ��޷�ȡջ��\n");
	
	if(pop(char, y))								//�ٴγ�ջ 
		printf("��ջ�ɹ�����ջԪ��Ϊ %c \n", y);
	else
		printf("ջ�գ��޷���ջ\n");
	
	if(pop(char, y))
		printf("��ջ�ɹ�����ջԪ��Ϊ %c \n", y);
	else
		printf("ջ�գ��޷���ջ\n");
	
	clearStack(char);
	destroyStack(char);								//���ջɾ��ջ 
	
	printf("------------------\n");
	
	//�ṹ��ջ���� 
	initStack(tnode);
	
	int i = 0;
	tnode z;
	tnode temp1, temp2;								//��tempȡ�ṹ���е�data���Ӷ�������ջ���� 
	
	for(i = 0; i < 10; i ++)						//��temp�е�data�ֱ�ֵ 
	{
		temp1.data[i] = i;
	}
	
	for(i = 0; i < 10; i ++)
	{
		temp2.data[i] = i + 10;
	}
	
	if(pop(tnode, z))
	{
		printf("��ջ�ɹ�����ջ����Ϊ\n");
		for(i = 0; i < 10; i ++)
			printf("%d ", z.data[i]);
		printf("\n");
	}
	else
		printf("ջ�գ����ܳ�ջ\n");
	
	printf("ջ���� %d ��Ԫ��\n", stackLength(tnode));
	
	if(getTop(tnode, z))							//ÿһ��ȡջ��ʱȡ�Ķ���top�µ�λ�ã���i - 1λ�� 
	{
		printf("ջ��Ԫ����");
		for(i = 0; i < 10; i ++)
			printf("ջ��Ԫ���� %d \n", z.data[i]);
	}	
	else
		printf("ջ�գ��޷�ȡջ��\n");
	
	
	push(tnode, temp1);
	printf("ջ���� %d ��Ԫ��\n", stackLength(tnode));
	
	push(tnode, temp2);
	printf("ջ���� %d ��Ԫ��\n", stackLength(tnode));
	
	if(getTop(tnode, z))
	{
		printf("ջ��Ϊ");
		for(i = 0; i < 10; i ++)
			printf("%d ", z.data[i]);
		printf("\n");
	}
	else
		printf("ջ�գ��޷�ȡջ��\n");
	
	if(pop(tnode, z))								//��ջ���Σ��鿴��ջ��� 
	{
		printf("��ջ�ɹ�����ջ����Ϊ\n");
		for(i = 0; i < 10; i ++)
			printf("%d ", z.data[i]);
		printf("\n");
	}
	else
		printf("ջ�գ����ܳ�ջ\n");
		
	if(pop(tnode, z))								
	{
		printf("��ջ�ɹ�����ջ����Ϊ\n");
		for(i = 0; i < 10; i ++)
			printf("%d ", z.data[i]);
		printf("\n");
	}
	else
		printf("ջ�գ����ܳ�ջ\n");
	
	if(pop(tnode, z))								
	{
		printf("��ջ�ɹ�����ջ����Ϊ\n");
		for(i = 0; i < 10; i ++)
			printf("%d ", z.data[i]);
		printf("\n");
	}
	else
		printf("ջ�գ����ܳ�ջ\n");
	
	
	clearStack(tnode);
	destroyStack(tnode);							//���ջ��ɾ��ջ�ռ� 
	return 0;
}
