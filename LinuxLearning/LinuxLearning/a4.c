/*Open the file and put the line into screen*/ /*Command format: ./command filename */ #include<sys/types.h>
#include<stdio.h>
int main(int argc,char *argv[])
{
    char s[1024];
    FILE *fp3;
    if((fp3=fopen(argv[3],"w"))!=(FILE*)0) /*打开参数 1 指定的文件*/ {
        FILE *fp;
        if((fp=fopen(argv[1],"r"))!=(FILE*)0) /*打开参数 1 指定的文件*/ {
            while((fgets(s,1024,fp))!=(char *)0){
                fputs(s,fp3); /*写入缓冲区*/
                puts(s); /*显示缓冲区*/
            }
            
        }else
        {
            fprintf(stderr,"file1 open error.\n");
            exit(1);
        }
        
        fputs("\n",fp3); /*写入缓冲区*/
        FILE *fp2;
        if((fp2=fopen(argv[2],"r"))!=(FILE*)0) /*打开参数 1 指定的文件*/ {
            while((fgets(s,1024,fp2))!=(char *)0){
                fputs(s,fp3); /*写入缓冲区*/
                puts(s); /*显示缓冲区*/
            }
        }else
        {
            fprintf(stderr,"file2 open error.\n");
            exit(1);
        }
        
        
    }else
    {
        fprintf(stderr,"file3 open error.\n");
        exit(1);
    }
    
    
    exit(0);
}
