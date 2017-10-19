#include<stdio.h>//头文件 输入、输出函数
#include<stdlib.h>//头文件 常用子函数
#include<conio.h>//头文件 调用DOS控制台I/O 使用getch()不用回车键入
#include<time.h>//头文件 时间
#include<windows.h>//头文件 窗口 嗡鸣音
#include<string.h>//头文件 字符串处理

#define MAX_NUMBER 9876//数字最大值
#define MIN_NUMBER 1023//数值最小值
char PASSWORD[7]="000000";//密码初始值
struct SCORE//姓名分数结构题
{
	char name[10];
	int score;
};
struct SCORE stu[4];

void gotoxy(int x,int y);//gotoxy坐标函数
int Table();//界面函数
void Rule();//规则函数
void Password();//密码重置函数
void WriteFile();//写文件函数
void DescendingSort();//倒序排列成绩函数
void ReadFile();//读文件函数
int MakeNumber(void);//生成随机数函数（游戏函数内）
void GuessNumber(int number);//猜数函数（游戏函数内）
void Game();//游戏函数
void Grade();//成绩输出函数

int main()//主函数
{
	int n;
	system("color 1E");//背景颜色与字体颜色
	while(1)//死循环
		{
			n=Table();//界面函数
			switch(n)//判断
			{
			case 1:
				Game();//1进入游戏
				break;
			case 2:
				Rule();//2进入规则
				break;
			case 3:
				ReadFile();//3读文件输出成绩
			    Grade();
				break;
			case 4:
				Password();//4重置密码
				break;
			case 5:
				exit(0);//退出
			default:
					break;
			}
		}
	return 0;
}

void gotoxy(int x,int y)//gotoxy坐标函数
{
	COORD coord={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int Table()//界面函数
{
	int i;
	system("cls");
	gotoxy(37,2);
	printf("猜数游戏");
	gotoxy(15,6);
	printf("1.开始游戏");
	gotoxy(15,8);
	printf("2.规则");
	gotoxy(15,10);
	printf("3.显示最高成绩");
	gotoxy(15,12);
	printf("4.设置密码");
	gotoxy(15,14);
	printf("5.退出");
	gotoxy(25,19);
	printf("请选择");
	scanf("%d",&i);
	return i;
}

void Rule()//规则函数
{
	system("cls");
	printf("\t\t 游戏规则 \n");
	printf("1.输入所猜4位不同的数字。\n");
    printf("2.若数字和位置均等同，玩家胜利。\n");
	printf("3.每猜一次，均给出提示信息(x,y)，x表示数字、位置都匹配的个数，\n");
    printf("  y表示数字匹配但位置不匹配的个数。\n");
	printf("4.猜数中按下H键能得到详细信息，如：第1位数字正确，第2位数字位置不对等，\n");
	printf("  第三位数字位置不对等。\n");
	printf("5.猜数中按下K键后，输入设置的6位密码（默认为000000），可以直接查看4位数。\n");
	printf("6.计分规则\n");
	printf("  初始分值1000分，每猜一次扣100分，若猜对一个数，奖励20分，\n");
	printf("  若有一个数对但位置不对等，奖励10分，分值小于等于0时，游戏失败。\n");
	printf("\n按任意键后返回\n");
	getch();
}

void Password()//密码重置函数
{
	system("cls");
	printf("请输入新的六位密码:");
	scanf("%s",PASSWORD);
	getchar();
	printf("\n按任意键后返回\n");
	getch();
}

void WriteFile()//写文件函数
{
	int i;
	FILE *p;
	DescendingSort();
	p=fopen("F:\\GuessNumberScore.txt","w");

	for(i=0;i<3;i++)
	{
		fprintf(p,"%10s%5d",stu[i].name,stu[i].score);
	}
	fclose(p);
}

void DescendingSort()//倒序排列成绩函数
{
  int i,j,k,temp1;
  char temp2[10];
  for(i=0;i<4;i++)
  {
	  k=i;
	  for(j=i+1;j<5;j++)
	  {
		  if(stu[j].score>stu[k].score)
		  {
			  k=j;
		  }
	  }
	  if(k!=i)
	  {
		  temp1=stu[k].score;
		  stu[k].score=stu[i].score;
		  stu[i].score=temp1;
		  strcpy(temp2,stu[k].name);
		  strcpy(stu[k].name,stu[i].name);
		  strcpy(stu[i].name,temp2);
	  }
  }
}

void ReadFile()//读文件函数
{

	int i;
	FILE *p;
	if((p=fopen("F:\\GuessNumberScore.txt","r"))==NULL)
	{
		printf("Cannot open file.");
		return;
	}
	for(i=0;i<3;i++)
	{
		fscanf(p,"%10s%5d",&stu[i].name,&stu[i].score);
	}
	fclose(p);

}

void Game()//游戏函数
{
	int number;//定义整形变量number
	int cont;//定义整形变量cont
	system("cls");//清屏
	srand(time(NULL));//生成时间种子
	do{//执行一次以下程序,判断是否可进入循环
		number=MakeNumber();//执行生成随机数函数
		GuessNumber(number);//执行猜数函数
		printf("请输入玩家名:");//交互提示
		gets(stu[3].name);//向结构体中输入姓名
		WriteFile();//写入文件
		printf("Continue?(Y/N)");//交互提示
		cont=getchar();//让getch()=一变量
		while(getchar()!='\n')//键入后停顿
		{
			;
		}
	}
	while(cont!='N'&&cont!='n');//不输入N或n时进入下一轮游戏
}

int MakeNumber(void)//生成随机数函数
{
	int a,b,c,d;//定义整形变量a,b,c,d
	
	int number;//定义整形变量number
	
	srand((unsigned)time(NULL));//生成第随机数种子
	a=(rand()%9)+1;//生成第1个随机数并取其除以9的余数后加1以防得0
	
   
	srand((unsigned)time(NULL));//生成第随机数种子
	b=(rand()%10);//生成第2个随机数并取其除以10的余数
	while(b==a)//判断是否与第1个数重复,进入循环
		b=(rand()%10);//重新生成第2个随机数并取其除以10的余数
	
	
	srand((unsigned)time(NULL));//生成第随机数种子
	c=(rand()%10);//生成第3个随机数并取其除以10的余数
	while(c==a||c==b)//判断是否与第1,2个数重复,进入循环
		c=(rand()%10);//重新生成第3个随机数并取其除以10的余数
	

	srand((unsigned)time(NULL));//生成第随机数种子
	d=(rand()%10);//生成第4个随机数并取其除以10的余数
	while(d==a||d==b||d==c)//判断是否与第1,2,3个数重复,进入循环
		d=(rand()%10);//重新生成第4个随机数并取其除以10的余数


	number=1000*a+100*b+10*c+d;//将各位数乘以各位数量级赋值为数字
	return number;//将数字作为返回值
}

void GuessNumber(int number)//猜数函数
{
	int guess;//定义整形变量guess
	int times=0;//定义整形变量times
	
	int n[4];//定义整形数组n[4]
	int s1,s2,s3;//定义整形变量times
	int N[4];//定义整形数组N[4]
	int S1,S2,S3;//定义整形变量S1,S2,S3
	int i,j;//定义整形变量i,j
	int x=0,y=0;//定义整形变量x,y
	int X,Y;//定义整形变量X,Y
	char password[7];//定义数组密码
	int score=1000;//定义整形变量score
    int ch;	//定义整形变量ch
	do{//执行一次以下程序,判断是否可进入循环
		times++;//每次循环猜数次数自增1
		score=score-100;//每次循环猜数分数自减100
		printf("Round %d\n",times);//输出当前循环为第几回合
		scanf("%d",&guess);//输入猜测数串
		getchar();//键入后停顿

		n[0]=number/1000;//生成最高位数字
		s1=n[0]*1000;//最高位数字乘以最高位数量级
		n[1]=(number-s1)/100;//生成第2高位数字
		s2=n[1]*100;//第2高位数字乘以第2高位数量级
		n[2]=(number-s1-s2)/10;//生成第3高位数字
		s3=n[2]*10;//第3高位数字乘以第3高位数量级
		n[3]=number-s1-s2-s3;//生成第4高位数字

		N[0]=guess/1000;//生成最高位数字
		S1=N[0]*1000;//最高位数字乘以最高位数量级
		N[1]=(guess-S1)/100;//生成第2高位数字
		S2=N[1]*100;//第2高位数字乘以第2高位数量级
		N[2]=(guess-S1-S2)/10;//生成第3高位数字
		S3=N[2]*10;//第3高位数字乘以第3高位数量级
		N[3]=guess-S1-S2-S3;//生成第4高位数字
	
		for(j=0;j<=3;j++)//猜测数从第一个循环到最后一个
		{
			for(i=0;i<=3;i++)//随机数从第一个循环到最后一个
			{
				if(n[i]==N[j] && i==j)//如果两组数字大小与角标都相同
				{
					x++;//x自增1,为数字与位置都正确的数字的数量
				}
				else if(n[i]==N[j] && i!=j)//如果两组数字大小相同角标不同
				{
					y++;//y自增1,为数字正确但位置不正确数字的数量
				}
				else//其他情况
				{
					x=x;//x不变
					y=y;//y不变
				}
			}
		}
        X=x;//将x至赋给X
		Y=y;//将y至赋给Y
		printf("(%d,%d)\n",x,y);//输出x,y
		score=score+20*x+10*y;//x,y补偿加分
		printf("score=%d\n",score);//输出分数
		x=0;//x重制赋值为0
		y=0;//y重制赋值为0
		
		stu[3].score=score;//结构体赋值	
		if(X!=4 && score>0)//限制条件未全猜对且分数大于0时执行以下程序
		{
			printf("按任意键继续游戏.\n");//交互提示
			while(1)//利用死循环重复此循环
			{
				ch=getch();//不按回车直接键入,让getch()=一变量
				if(ch=='h'||ch=='H')//变量如果等于h执行以下程序
				{
					if(X!=0||Y!=0)//存在正确或位置正确的数字时执行以下程序
					{
						for(j=0;j<=3;j++)//猜测数从第一个循环到最后一个
						{
							for(i=0;i<=3;i++)//随机数从第一个循环到最后一个
							{
								if(n[i]==N[j] && i==j)//如果两组数字大小与角标都相同
									printf("第%d个数字正确\n",j+1);//输出此为第几个数字
								if(n[i]==N[j] && i!=j)//如果两组数字大小相同角标不同
									printf("第%d个数字位置不对等\n",j+1);//输出此为第几个数字
							}
						}
					}
					if(X==0 && Y==0)//所猜数字大小及位置均不正确
					{
						printf("对不起，所有数字均不正确\n");//交互提示
					}
					printf("按任意键继续游戏\n");//交互提示
				}
				else if(ch=='k'||ch=='K')//变量如果等于k执行以下程序
				{
					printf("请输入管理员密码:");//交互提示
					scanf("%s",&password);//输入密码获取答案
					getchar();//键入后停顿
					if(strcmp(PASSWORD,password)==0)//如果答案正确执行以下程序
					{
						printf("答案为：%d\n",number);//输出答案
						printf("按任意键继续游戏\n");//交互提示
					}
					else
					{
						printf("对不起，您的密码有误!\n");//交互提示
						printf("按任意键继续游戏\n");//交互提示
					}
				}
				else//按其他按键
				{	
					break;//结束本次循环,进入下次循环
				}
			}
			X=0;//X重制赋值为0
			Y=0;//Y重制赋值为0
		}
	}
	while(guess!=number&&score>0);//未猜对随机数且分数不等于零时执行以上程序
	if(guess==number)//猜对结果时执行以下程序
	{
		printf("Congratulations! You're so cool!\n");//交互提示
		Beep(523,130);//嗡鸣523hz,延时130ms
		Beep(587,130);//嗡鸣587hz,延时130ms
		Beep(659,130);//嗡鸣659hz,延时130ms
		Beep(784,300);//嗡鸣784hz,延时300ms
		Beep(659,150);//嗡鸣659hz,延时150ms
		Beep(784,900);//嗡鸣784hz,延时900ms
	}
   
	else//其他情况
	{
		printf("Mission failed after %d attempet.\n",times);//交互提示
        Beep(698,350);//嗡鸣698hz,延时350ms
		Beep(523,130);//嗡鸣523hz,延时130ms
		Beep(523,130);//嗡鸣523hz,延时130ms
		Beep(587,200);//嗡鸣587hz,延时200ms
		Beep(523,250);//嗡鸣523hz,延时250ms
		Sleep(550);//停顿550ms
		Beep(659,300);//嗡鸣659hz,延时300ms
        Beep(698,400);//嗡鸣698hz,延时400ms
	}
}

void Grade()//成绩输出函数
{
	int i;
	system("cls");
	for(i=0;i<3;i++)
	{
		printf("%10s%5d\n",stu[i].name,stu[i].score);
	}
	printf("\n按任意键后返回");
	getch();
}
