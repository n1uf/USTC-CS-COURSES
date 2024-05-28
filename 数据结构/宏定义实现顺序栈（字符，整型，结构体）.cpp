#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100		//初始的栈的容量 
#define STACKINCREMENT 10		//增量 

/*宏定义实现栈的操作 #号起到连接作用，这样stack ## _stackbase_ptr就可以代表
  int_stackbase_ptr等三种不同类型数据的有关参量*/ 

//初始化，开辟栈空间，初始化栈指针和栈大小 
#define initStack(stack) stack ## _stackbase_ptr = (stack *)malloc(sizeof(stack) * STACK_INIT_SIZE);\
						 if(stack ## _stackbase_ptr){\
						   stack ## _stacktop_ptr = stack ## _stackbase_ptr;\
						   stack ## _stacksize = STACK_INIT_SIZE;\
						 }else exit(0)

//判断栈空，空则返回true 
#define stackEmpty(stack) stack ## _stackbase_ptr == stack ## _stacktop_ptr ? 1:0

//取栈顶元素，存在e中，先确定栈非空，再取栈顶
#define getTop(stack, e) stack ## _stackbase_ptr == stack ## _stacktop_ptr ? 0 : (e = *(stack ## _stacktop_ptr -\
1), 1)						/* 这里用逗号表达式，取值逗号后的1，同时也进行了取栈顶元素的操作，后面的逗号表达式同理 */ 

//清空栈
#define clearStack(stack) stack ## _stacktop_ptr = stack ## _stackbase_ptr

//删除栈空间 
#define destroyStack(stack) free(stack ## _stackbase_ptr)

//求栈的长度 
#define stackLength(stack) stack ## _stacktop_ptr - stack ## _stackbase_ptr

//出栈，先判断栈非空，再取栈顶然后将top指针下移 
#define pop(stack,e) (stack ## _stackbase_ptr == stack ## _stacktop_ptr)? 0:(e =*(-- stack ## _stacktop_ptr),1)

/* 入栈，先判断栈空间大小是否超过了预先分配的空间，如果超过，则使用增量拓展空间，移动栈顶指针到新的空间的最底层，
   把栈的大小改为原先的大小加上增量。最后将元素置入，并将top指针上移 */ 
#define push(stack,e) if (stack ## _stacktop_ptr - stack ## _stackbase_ptr >= stack ## _stacksize){\
						stack ## _stackbase_ptr = (stack *)realloc(stack ## _stackbase_ptr, \
						   (stack ## _stacksize + STACKINCREMENT) * sizeof(stack));\
						if(! stack ## _stacktop_ptr) exit(0);\
						stack ## _stacktop_ptr = stack ## _stackbase_ptr + stack ## _stacksize;\
						stack ## _stacksize += STACKINCREMENT;}\
						*(stack ## _stacktop_ptr ++) = e;\
						printf("入栈成功\n") 
						

//顺序整数栈
unsigned int_stacksize;
int *int_stacktop_ptr;
int *int_stackbase_ptr;

//顺序字符栈
unsigned char_stacksize;
char *char_stacktop_ptr;
char *char_stackbase_ptr;

//结构体栈 
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
	
	//整型栈的操作 
	initStack(int);
	
	int x;
	if(pop(int, x))									//出栈操作 
		printf("出栈成功，出栈元素为 %d \n", x); 
	else
		printf("栈空，不能出栈\n");
	
	printf("栈中有 %d 个元素\n", stackLength(int));
	
	if(getTop(int, x))								//取栈顶操作 
		printf("栈顶元素是 %d \n", x);
	else
		printf("栈空，无法取栈顶\n");
		 
			
	push(int, 6);									//入栈一个元素 
	printf("栈中有 %d 个元素\n", stackLength(int));	//查看栈中元素个数 
	
	push(int, 7);
	push(int, 8);									//入栈两个元素 
	
	printf("栈中有 %d 个元素\n", stackLength(int));
	
	if(pop(int, x))									//出栈 
		printf("出栈成功，出栈元素为 %d \n", x); 
	else
		printf("栈空，不能出栈\n");
		
	printf("栈中有 %d 个元素\n", stackLength(int));
	
	if(getTop(int, x))								//取栈顶元素，查看出栈是否成功
		printf("栈顶元素是 %d \n", x);
	else
		printf("栈空，无法取栈顶\n");
			
	clearStack(int);
	destroyStack(int);								//清空栈删除栈空间 
	
	printf("------------------\n");
	
	
	//字符型栈操作 
	initStack(char);
	
	char y;
	if(pop(char, y))								//出栈操作 
		printf("出栈成功，出栈元素为 %c ", y);
	else
		printf("栈空，无法出栈\n");
	
	printf("栈中有 %d 个元素\n", stackLength(char));//查看栈中元素个数 
	
	if(getTop(char, y))								//取栈顶元素 
		printf("栈顶元素是 %c \n", y);
	else
		printf("栈空，无法取栈顶\n");
	
	push(char, '1');								//入栈元素 
	printf("栈中有 %d 个元素\n", stackLength(char));//查看元素个数 
	
	push(char, 'b');
	printf("栈中有 %d 个元素\n", stackLength(char));
	
	if(pop(char, y))								//出栈
		printf("出栈成功，出栈元素为 %c \n", y);
	else
		printf("栈空，无法出栈\n");
	
	if(getTop(char, y))								//取栈顶元素，检查出是否成功 
		printf("栈顶元素是 %c \n", y);
	else
		printf("栈空，无法取栈顶\n");
	
	if(pop(char, y))								//再次出栈 
		printf("出栈成功，出栈元素为 %c \n", y);
	else
		printf("栈空，无法出栈\n");
	
	if(pop(char, y))
		printf("出栈成功，出栈元素为 %c \n", y);
	else
		printf("栈空，无法出栈\n");
	
	clearStack(char);
	destroyStack(char);								//清空栈删除栈 
	
	printf("------------------\n");
	
	//结构体栈操作 
	initStack(tnode);
	
	int i = 0;
	tnode z;
	tnode temp1, temp2;								//用temp取结构体中的data，从而进行入栈操作 
	
	for(i = 0; i < 10; i ++)						//给temp中的data分别赋值 
	{
		temp1.data[i] = i;
	}
	
	for(i = 0; i < 10; i ++)
	{
		temp2.data[i] = i + 10;
	}
	
	if(pop(tnode, z))
	{
		printf("出栈成功，出栈数组为\n");
		for(i = 0; i < 10; i ++)
			printf("%d ", z.data[i]);
		printf("\n");
	}
	else
		printf("栈空，不能出栈\n");
	
	printf("栈中有 %d 个元素\n", stackLength(tnode));
	
	if(getTop(tnode, z))							//每一次取栈顶时取的都是top下的位置，即i - 1位置 
	{
		printf("栈顶元素是");
		for(i = 0; i < 10; i ++)
			printf("栈顶元素是 %d \n", z.data[i]);
	}	
	else
		printf("栈空，无法取栈顶\n");
	
	
	push(tnode, temp1);
	printf("栈中有 %d 个元素\n", stackLength(tnode));
	
	push(tnode, temp2);
	printf("栈中有 %d 个元素\n", stackLength(tnode));
	
	if(getTop(tnode, z))
	{
		printf("栈顶为");
		for(i = 0; i < 10; i ++)
			printf("%d ", z.data[i]);
		printf("\n");
	}
	else
		printf("栈空，无法取栈顶\n");
	
	if(pop(tnode, z))								//出栈三次，查看出栈情况 
	{
		printf("出栈成功，出栈数组为\n");
		for(i = 0; i < 10; i ++)
			printf("%d ", z.data[i]);
		printf("\n");
	}
	else
		printf("栈空，不能出栈\n");
		
	if(pop(tnode, z))								
	{
		printf("出栈成功，出栈数组为\n");
		for(i = 0; i < 10; i ++)
			printf("%d ", z.data[i]);
		printf("\n");
	}
	else
		printf("栈空，不能出栈\n");
	
	if(pop(tnode, z))								
	{
		printf("出栈成功，出栈数组为\n");
		for(i = 0; i < 10; i ++)
			printf("%d ", z.data[i]);
		printf("\n");
	}
	else
		printf("栈空，不能出栈\n");
	
	
	clearStack(tnode);
	destroyStack(tnode);							//清空栈，删除栈空间 
	return 0;
}
