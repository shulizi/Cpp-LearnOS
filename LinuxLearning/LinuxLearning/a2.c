#include<stdio.h>

int main()
{
    extern int etext,edata,end; /*对应文本的第一有效地址、初始化的数据*/
    printf("etext:%6x \t edata:%6x \t end:%6x \n",&etext,&edata,&end);
    return 0;
}
int etext,edata,end; /*对应文本的第一有效地址、初始化的数据*/
