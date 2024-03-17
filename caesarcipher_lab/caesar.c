/***********************************************************************
Copyright Buu Information Security Major
File Name: caesar.c  
Author：Li Zeyi 
ID: 2021240381019    
Version: v6.0        
Date: 2023.3.10    
Description: 对一串字符进行简单的凯撒加密和解密          
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>//头文件引入string.h，后面会用到判断两个字符串是否相等的函数strcmp();

//const int N = 1e5 + 10;
//char g_str[N];//定义一个全局变量str，用来存放和转移文档中的内容

/***********************************************************************
Function Name: encryption  
Parameters: 两个字符型数组，输入文件为input_file，输出文件为output_file
Return: void类型函数，不需要返回值
Description: 通过简单的凯撒加密算法，将一个文件中的字符串进行加密    
************************************************************************/
void encryption(char input_file[], char output_file[])
{
    FILE *fp1;  //定义一个FILE类型的指针，指向要打开的文件。
    if (NULL == (fp1 = fopen(input_file, "r")))  
    {  
        printf("文件打开失败！\n");
        system("pause");
        exit(0);
    }  

    char *str;
 
    int n = 0;
    while (EOF != fgetc(fp1)) //此处的循环是将fp1所指向的文件长度进行统计
    {  
        n++;
    }  

    str = (char *)malloc((n + 1)* sizeof(char)); //申请动态数组，长度为n;
    memset(str, '\0', (n + 1)*sizeof(char)); //对数组进行初始化，将数组str中的元素内容均赋值为'0'

    n = 0;    
    char ch; 

    fp1 = fopen(input_file, "r"); //重新让fp1指向所指文件，原因是之前的fgetc()函数将指针指向了文件的最后一个字符;
    while (EOF != (ch = fgetc(fp1)))
    {
        str[n] = ch;
        n++;
    }

    fclose(fp1);  //对于一个文件来说，打开和关闭操作必须同时包含

    int t = 3;

    for (int i = 0; i < n + 1; i++) //这里的for循环是凯撒加密的关键点，凯撒加密的主要思想是字符的偏移
    {
        if (str[i] >= 'a' && str[i] <= 'z') 
        {
            if (t >= 0) str[i] = ((str[i] - 'a') + t) % 26 + 'a';
            else
            {
                str[i] = ((str[i] - 'a') + t + 26) % 26 + 'a';
            }
        }
        else if (str[i] >= 'A' && str[i] <= 'Z') 
        {
            str[i] += 32;
            str[i] = ((str[i] - 'a') + t) % 26 + 'a';
        }

    }

    FILE *f;
    f = fopen(output_file,"w");
    fputs(str, f);//fputs()是将一整行的字符(即字符串)都写入到指针f所指向的文件之中
    fclose(f);
    printf("%s加密成功,暗文在%s中\n", input_file, output_file);
    free(str);//释放指针str中的内容
    str = NULL;//将指针指向NULL
}

/***********************************************************************
Function Name: decryption              
Parameters: 两个字符型数组，输入文件为input_file，输出文件为output_file
Return: void类型函数，不需要返回值
Description: 解密函数，可以将上一次加密的字符串进行解密 
************************************************************************/
void decryption(char input_file[], char output_file[])
{
    FILE *fp;
    if (NULL == (fp = fopen(input_file, "r")))  
    {  
        printf("文件打开失败\n");  
        exit(0);
    }  
    
    char *str;
    char ch;  //    
    int n = 0;
    //memset(g_str, 0, sizeof(g_str));//这里用memset()进行一个初始化的处理，原因是之前的加密过程中已经在str数组中存入了内容
    while (EOF !=  fgetc(fp)) //此处的循环是将fp所指向的文件长度进行统计
    {  
        n++;
    }  
    //printf("密文长度为: %d\n", n);
    str = (char* )malloc((n + 1)* sizeof(char)); //申请动态数组，长度为n;
    memset(str, '\0', n + 1);
    //printf("str 的长度为: %d\n", strlen(str));
    n = 0;
    fp = fopen(input_file, "r");//重新让fp指向所指文件，原因是之前的fgetc()函数将指针指向了文件的最后一个字符
    while (EOF != (ch = fgetc(fp)))
    {
        str[n] = ch;
        n++;
    }

    fclose(fp);  

    int t = 3;
    //printf("上一次加密过程中的位移量为：");
    //scanf("%d", &t);

    for (int i = 0; i < n ; i++) //解密过程是减去对应的加密过程中的偏移量，和加密过程相反
    {
        if (str[i] >= 'a' && str[i] <= 'z') 
        {
            if (t >= 0) str[i] = ((str[i] - 'a') - t + 26) % 26 + 'a';
            else
            {
                str[i] = ((str[i] - 'a') - t) % 26 + 'a';
            }
        }
        //if (str[i] == '\0') break;
    }
    
    FILE *f;
    f = fopen(output_file, "w");
    fputs(str, f);
    fclose(f);
    printf("%s解密成功,明文在%s中\n",input_file, output_file);
    free(str); //释放指针str中的内容
    str = NULL; //将指针指向NULL
}

int main(int argc, char* argv[])  //char* argv[] == char argv[][];
{  
    if (argc != 4) 
    {
        printf("参数输入不正确！");
        printf("提示：文件名 命令 .txt文件1 .txt文件2");
        exit(0);
    }
    
    if (strcmp(argv[1], "-e") == 0)//此处不能用 == 来进行比较，必须使用strcmp()函数，== 符号只是比较两个字符串的地址。
    {
        encryption(argv[2], argv[3]);// caesar -e message.txt ciphers.txt
    }


    else if (strcmp(argv[1], "-d") == 0)//需要注意的是，strcmp()函数，如果两个字符串相等，则返回值为0
    {
        decryption(argv[2], argv[3]);
    }

    else printf("输入参数不满足实验条件\n");

    system("pause");
    return 0;  
}