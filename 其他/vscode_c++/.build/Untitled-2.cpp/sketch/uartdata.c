#define uint32 unsigned int
#define ALL_PARA 3 //需要小于16
#define MAX_LEN 16	//接收的数据的最大长度
#define FLASH_START_ADD 0xffffff00  //储存flash的开始地址

#define send_byte(n)	printf("%x,",n)

//*数据类型定义，高4位为数据的字节数*//
#define char_type 		(0x01	+(sizeof(char)		<<4))
#define int_type 		(0x02	+(sizeof(int)		<<4))
#define float_type 		(0x03	+(sizeof(float)		<<4))
#define double_type 	(0x04	+(sizeof(double)	<<4))
/////////////////

#include <stdio.h>

struct PARA
{
	char *name;
	void *val;
	int add;
	char id;
	char type;
}para[ALL_PARA];
//*默认全局变量*//
char recive;
char recive_datas[MAX_LEN];

char cmd;
char temp;
char data_len=0;
///////////////

/*
**每当接收到一个数据时执行一次该函数
**
*/
void get_cmd(char data)
{
	/* //如果此函数不放在串口中断函数中，可以使用这段代码来判断是否开始处理数据
	if (!recive_flag)
		return;
	recive_flag=0;
	*/
	if (!data_len)	//data_len为0时，即不需要接收数据，只接收命令
	{
		
		temp=data;	//暂存命令，待接收完数据以后再给命令
		switch (data & 0x0f)	//取后4位，前四位为id数据
		{
			case 0: break;
			case 1: data_len=para[data>>4].type>>4; break;
			case 2: break;
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: break; 
			default:
				break;
		}
	}
	else	//data_len不为0时，即需要接收数据，不接收命令
	{
		recive_datas[--data_len]=data;
	}
	if (!data_len)
	{
		cmd=temp; //没有要接收的数据了，可以执行命令了
	}
}

void get_para(char *p,char id)
{
	switch (para[id].type)
	{	
		//*将数值强制转换，直接将保存的数据数组强制转换为数据的类型*//
		case char_type	:	*(char *)para[id].val	=*(char *)p;	break;
		case int_type	:	*(int *)para[id].val	=*(int *)p;		break;
		case float_type	:	*(float *)para[id].val	=*(float *)p;	break;
		case double_type:	*(double *)para[id].val	=*(double *)p;	break;
		default:
			break;
	}
}

void send_para_val(char id)
{
	//*type的高4位为数据的字节数*//
	char len=para[id].type>>4;

	while(len--)
	{
		send_byte(*(char *)(para[id].val+len));
	}
}

void send_para_name(char id)
{
	char len=0;

	//*VC测试使用这段代码*//
	send_byte(para[id].type);
	printf(para[id].name);
	printf(" ");
	return;
	//*单片机使用这段代码*//
	send_byte(para[id].type);
	do
	{
		send_byte(*(para[id].name+len));
	}while(*(para[id].name+len++));
}

save_para(char id)
{

}

read_para(char id)
{

}

void do_cmd(char cmd)
{
	switch (cmd & 0x0f)	//取后4位，前四位为id数据
	{
		case 0: break;
		case 1: get_para(recive_datas,cmd>>4); 	break; //上位机给参数值
		case 2: send_byte(ALL_PARA); 			break; //告知上位机一共有多少个参数
		case 3: send_para_name(cmd>>4); 		break; //给上位机参数的名称
		case 4: send_para_val(cmd>>4);			break; //给上位机当前参数的值
		case 5: save_para(cmd>>4); 				break; //下位机保存当前参数值
		case 6: read_para(cmd>>4);				break; //下位机读取保存的值给参数 
		default:
			break;
	}
}

void def_para(char *name,char *p,char type,char id)
{
	//*定义一个需要调参的参数*//
	para[id].name=name;
	para[id].val=p;
	para[id].id=id;
	para[id].type=type;
	para[id].add=FLASH_START_ADD+id*16;
}

int main()
{
	char i;
	int a=0x1234;
	int b=0x5678;
	int c=0x1111;

	def_para("a",(char *)&a,int_type,0);
	def_para("b",(char *)&b,int_type,1);
	def_para("c",(char *)&c,int_type,2);

	printf("有参数%d个，为：\n",ALL_PARA);
	for(i=0;i<ALL_PARA;i++)
		do_cmd(3+(i<<4));
	printf("\n");
	while (1)
	{

		if(data_len)
			printf("输入数据：");
		else
			printf("输入命令：");
		scanf("%x",&recive);
		get_cmd(recive);

		if(data_len)
			printf("数据模式\n");
		else
			printf("命令模式\n");

		do_cmd(cmd);
		printf("\n当前命令为%x\n",cmd);
		printf("a=%x,b=%x,c=%x\n",a,b,c);
		cmd=0;

	}	
	return 0;
}


