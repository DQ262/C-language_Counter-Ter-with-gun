#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include <time.h>

long long int speed=0;              //控制敌人的速度
int position_x, position_y;         //警察的所在位置
int upbullet_x, upbullet_y;         //向前打（i）的子弹的位置
int leftbullet_x, leftbullet_y;     //向前左（j）的子弹的位置
int rightbullet_x, rightbullet_y;   //向前右（L）的子弹的位置
int downbullet_x, downbullet_y;     //向前下（k）的子弹的位置
int enemy_x, enemy_y,flag,flag2=0;  //小偷的位置
char c[4]={"ZYX"};
char d[4];
int map[190][190]={
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,1},
    {0,1,1,1,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0},
    {0,1,0,1,0,1,0,1,0,0,1,1,0,1,1,0,0,1,0},
    {0,1,0,1,0,0,0,1,0,1,1,0,0,0,0,0,1,1,0},
    {0,1,0,0,1,0,0,1,0,0,1,1,0,1,1,0,0,1,0},
    {0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0},
    {0,1,1,1,0,0,0,0,0,0,1,0,1,1,0,0,1,1,0},
    {0,1,0,0,0,1,1,1,0,0,1,0,1,0,0,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,1,0},
    {0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0},
    {0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,1,0},
    {0,1,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,1,0},
    {0,1,0,1,0,0,0,0,1,0,1,0,1,1,1,0,0,1,0},
    {1,1,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
};
// 地图，17行17列，其中 0 代表着空地；
// 1 代表着墙；0处输出"    ",1处输出"■"，警察和醉犯可分别用"★""♀"表示。

void startup(){//警察位置初始化，小偷位置初始化，子弹位置初始化（如果打算做子弹）
int x,i;                //
time_t t=time(NULL);    //    以系统时间作为标签，生成随机数
srand(t);               //
position_x=16;          //警察位置初始化
position_y=9;
upbullet_x=19;          //子弹位置初始化
upbullet_y=19;
leftbullet_x=0;
leftbullet_y=0;
rightbullet_x=0;
rightbullet_x=19;
downbullet_x=0;
downbullet_y=1;
enemy_x=2;              //小偷位置初始化
enemy_y=7;
flag=0;
flag2=0;
do{enemy_y=rand()%18;}
while ((enemy_y==0)||(enemy_y==1)||(enemy_y==7)||(enemy_y==9)||(enemy_y==16)||(enemy_y==17)||(enemy_y==18));
}

void StartMap(){        //对各个单位进行赋值，警察2，小偷3，子弹4567
    map[position_x][position_y]=2;
    map[enemy_x][enemy_y]=3;
    map[upbullet_x][upbullet_y]=4;
    map[leftbullet_x][leftbullet_y]=5;
    map[rightbullet_x][rightbullet_y]=6;
    map[downbullet_x][downbullet_y]=7;
}

void HideCursor()
{//隐藏光标
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x, int y)
{//清理一部分屏幕
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void show(){            //展示的内容
    gotoxy(0,0);
    int i, j;
    for (i=1; i<=17; i++)
    {
        for (j=1; j<=17; j++)
        {
            if (map[i][j] == 0)
                printf("  ");   //空格是0 空地
            if (map[i][j] == 1)
                printf("■");    //■是1 墙
            if (map[i][j] == 2)
                printf("★");    //★是2 警察
            if (map[i][j] == 3)
                printf("♀");    //☆是3 小偷
            if (map[i][j] == 4)
                printf("↑");    //↑是4 子弹
            if (map[i][j] == 5)
                printf("←");    //←是5 子弹
            if (map[i][j] == 6)
                printf("→");    //→是6 子弹
            if (map[i][j] == 7)
                printf("↓");    //↓是7 子弹
        }
        printf("\n");
    }
    //printf("\n你的得分:%d\n\n", score);
    printf("\n你是一名光荣的人民警察(★)，现在一个小偷(♀)正在你负责的辖区内行凶作恶\n请操控你的角色(★)，击毙小偷(♀)，为民除害！\n\n");
    printf("**  操作说明: WASD分别操作 上左下右 四个方向的移动  **\n");
    printf("**            IJKL分别发射 上左下右 四个方向的子弹  **\n\n");
    printf("##  提示:请不要试图与小偷近身搏斗,必要时使用你的枪  ##\n\n");
    printf("%%%  制作:立华柒劫 DQ262  %%%% 友情支持:dsgwds Acid  %%%\n");
    printf("@@ 参考资料:① https://blog.csdn.net/zhaojin0718/article/details/81416546 @@\n");
    printf("@@ 参考资料:② https://blog.csdn.net/zhao5502169/article/details/61620774 @@\n");
}

void updateWithInput()//与输入有关的更新
{
    char input;
    if (kbhit())//在VC6.0++下，为_kbhit()
    {
        input = getch();//在VC6.0++下为_getch();

        //下面是警察移动
        if (input == 'a')                               //向左移动
            if(map[position_x][position_y-1]==0)
                {map[position_x][position_y]=0;position_y--;}
        if (input == 's')                               //向下移动
            if(map[position_x+1][position_y]==0)
                {map[position_x][position_y]=0;position_x++;}
        if (input == 'd')                               //向右移动
            if(map[position_x][position_y+1]==0)
                {map[position_x][position_y]=0;position_y++;}
        if (input == 'w')                               //向上移动
            if(map[position_x-1][position_y]==0)
                {map[position_x][position_y]=0;position_x--;}

        //下面是发射子弹
        if (input == 'i')                               //向上射击
            if(map[position_x-1][position_y]!=1)
                {upbullet_x = position_x - 1;upbullet_y = position_y;}
        if (input == 'j')                               //向左射击
            if(map[position_x][position_y-1]!=1)
                {leftbullet_x = position_x;leftbullet_y = position_y - 1;}
        if (input == 'k')                               //向下射击
            if(map[position_x+1][position_y]!=1)
                {downbullet_x = position_x + 1;downbullet_y = position_y;}
        if (input == 'l')                               //向右射击
            if(map[position_x][position_y+1]!=1)
                {rightbullet_x = position_x;rightbullet_y = position_y + 1;}

        if (input == 'Z'){ZYX();}
}
}
void updateWithoutInput()//与输入无关的更新
{
    if (upbullet_y < 18 && upbullet_x > 0)           //子弹up自动飞行
        {
            if(map[upbullet_x-1][upbullet_y]!=1)
                {map[upbullet_x][upbullet_y]=0;upbullet_x--;}
            else {map[upbullet_x][upbullet_y]=0;upbullet_x=19;upbullet_y=19;}
        }
    if (leftbullet_y < 18 && leftbullet_x > 0)       //子弹left自动飞行
        {
            if(map[leftbullet_x][leftbullet_y - 1]!=1)
                {map[leftbullet_x][leftbullet_y]=0;leftbullet_y--;}
            else {map[leftbullet_x][leftbullet_y]=0;leftbullet_x=0;leftbullet_y=0;}
        }
    if (rightbullet_y < 18 && rightbullet_x > 0)     //子弹right自动飞行
        {
            if(map[rightbullet_x][rightbullet_y + 1]!=1)
                {map[rightbullet_x][rightbullet_y]=0;rightbullet_y++;}
            else {map[rightbullet_x][rightbullet_y]=0;rightbullet_x=0;rightbullet_y=19;}
        }
    if (downbullet_y < 18 && downbullet_x > 0)       //子弹down自动飞行
        {
            if(map[downbullet_x + 1][downbullet_y]!=1)
                {map[downbullet_x][downbullet_y]=0;downbullet_x++;}
            else {map[downbullet_x][downbullet_y]=0;downbullet_x=0;downbullet_y=1;}
        }

    if (((upbullet_x == enemy_x) && (upbullet_y == enemy_y))||((leftbullet_x == enemy_x) && (leftbullet_y == enemy_y))||((rightbullet_x == enemy_x) && (rightbullet_y == enemy_y))||((downbullet_x == enemy_x) && (downbullet_y == enemy_y)))
        //当敌人的飞机被击中时
        {
            flag2=1;// printf("你成功击毙了小偷！\n");
        }
    speed = 0;
    if (speed == 0)
    {
        int x,i;                //
        time_t t=time(NULL);    //    以系统时间作为标签，生成随机数
        srand(t);               //
        int p;
        flag=0;
        Sleep(100);
        while(flag==0)
        {
            p=rand()%4;
            switch(p)
            {
                case 0:if(map[enemy_x-1][enemy_y]==0||map[enemy_x-1][enemy_y]==2){map[enemy_x][enemy_y]=0;enemy_x--;flag=1;}break;//小偷会随机向上下左右
                case 1:if(map[enemy_x][enemy_y-1]==0||map[enemy_x][enemy_y-1]==2){map[enemy_x][enemy_y]=0;enemy_y--;flag=1;}break;//的空地移动哦
                case 2:if(map[enemy_x+1][enemy_y]==0||map[enemy_x+1][enemy_y]==2){map[enemy_x][enemy_y]=0;enemy_x++;flag=1;}break;//
                case 3:if(map[enemy_x][enemy_y+1]==0||map[enemy_x][enemy_y+1]==2){map[enemy_x][enemy_y]=0;enemy_y++;flag=1;}break;//
            }
        }
        speed = 1;
    }
    if(enemy_x == position_x && enemy_y == position_y){flag2=2;}
}

void ZYX(){         //作弊码
//if(kbhit())
{int i;
gets(d);
i=strcmp(c,d);
if(i==0)
    flag2=3;}
}

int main()
{
    //int i;

        loop:startup();
        while (flag2==0)
        {
            HideCursor();
            StartMap();
            show();
            updateWithoutInput();
            updateWithInput();
            //Sleep(100);
        }
        switch(flag2)
        {
            case 1: {for(int i=1;i<100;i++)printf("!!!!!  你成功击毙了小偷，好样的  !!!!!\n\n");printf("按r键重新开始游戏...");}break;
            case 2: {for(int i=1;i<100;i++)printf("!!!!!  你被小偷干死了，真菜  !!!!!\n\n");printf("按r键重新开始游戏...");}break;
            case 3: {for(int i=1;i<100;i++)printf("!!!!!  ZYX I LOVE U  !!!!!\n\n");printf("按r键重新开始游戏...");}break;
        }
        Sleep(2000);
        char input;
        while(1)
            if (kbhit())//在VC6.0++下，为_kbhit()
            {
                input = getch();//在VC6.0++下为_getch();
                if (input == 'r') //按r重新开始游戏
                {
                    system("cls");
                    map[position_x][position_y]=0;
                    goto loop;
                }
            }
        system("pause");
    return 0;
}
