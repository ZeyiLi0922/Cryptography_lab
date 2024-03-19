#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char k[16][49];

int pc1[56] = 
{
    57, 49, 41, 33, 25, 17, 9, 1,
    58, 50, 42, 34, 26, 18, 10, 2,
    59, 51, 43, 35, 27, 19, 11, 3,
    60, 52, 44, 36, 63, 55, 47, 39,
    31, 23, 15, 7, 62, 54, 46, 38,
    30, 22, 14, 6, 61, 53, 45, 37,
    29, 21, 13, 5, 28, 20, 12, 4
};

int loop[16] = 
{
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

int pc2[48] =
{
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int ip[64] = 
{
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int extend[48] = 
{
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1    
};

int sBox[8][4][16] = 
{
    //S1
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
    //S2
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9, 
    //S3
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1, 
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
    //S4
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14, 
    //S5
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
    //S6
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
    //S7
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
    //S8
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
};

int pTable[32] =
{
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25
};

int ipReverse[64] = 
{
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25    
};

char* charToBinary(char c)
{
    int b = c, k = 0, flag = 0;
    char str[9] = {'\0'};

    if (b < 0) //负数表示中文字符
    {
        b = -b;
        flag = 1;
    }

    while (k < 8)
    {
        if (b)
        {
            str[k] = ((b % 2) + '0');
            b /= 2;
        }
        else str[k] = '0';
        k++;
    }
    if (flag) //汉字字符处理过程
    {
        for (int i = 0; i < 8; i ++) //此时因为是负数，源码、反码、补码不相等，需要置换
        {
            if (str[i] == '0') str[i] = '1'; // 反码：最高最不变，其它的 0->1, 1->0
            else str[i] = '0';
        }
        int k = 0;
        for (int i = 0; str[i] != '0'; i ++) //补码 ： 反码 + 1
        {
            str[i] = '0';
            k = i;
        }
        str[k + 1] = '1';
    }

    static char res[9] = {'\0'};
    for(int i = 7, k = 0; i >= 0; i --, k ++)
    {
        res[k] = str[i];
    }

    return res;
}


int binaryToInt(char str[])
{
    int res = 0, p = 1;
    for (int i = strlen(str); i >= 0; i --)
    {
        res += ((str[i] - '0') * p);
        p *= 2;
    }
    return res;
}

char* intToBinary(int i)
{
    int k = 0;
    char str[5] = {'\0'};
    while (k < 4) //此处，处理进入S盒后取出的数据转为2进制，此处最多用4bit
    {
        if (i)
        {
            str[k] = ((i % 2) + '0');
            i /= 2;
        }
        else str[k] = '0';
        k++;
    }
    
    static char res[5] = {'\0'};
    for(int i = 3, j = 0; i >= 0; i --, j ++)
    {
        res[j] = str[i];
    }

    return res;
}

char* xorAB(char a[], char b[])
{
    static char str[9] = {'\0'};
    for (int i = 0; i < 8; i ++)
    {
        str[i] = (((a[i] - '0') ^ (b[i] - '0')) + '0');
    }
    return str;
}


char* f(char right[], char k[])
{
    int temp;
    char extendBinary[49] = {'\0'};
    char* b0;
    char b[8][7], row[3], col[5];
    char b8[33];
    static char pb[33];

    for (int i = 0; i < 48; i ++)
    {
        extendBinary[i] = right[extend[i] - 1];
    }

    b0 = xorAB(extendBinary, k);
    for (int i = 0; i < 8; i ++)
    {
        for(int j = 0; j < 6; j ++)
        {
            b[i][j] = b0[i*6 + j];
        }
    }

    for (int i = 0; i < 8; i ++)
    {
        row[0] = b[i][0], row[1] = b[i][5];
        col[0] = b[i][1], col[1] = b[i][2], col[2] = b[i][3], col[3] = b[i][4];

        temp = sBox[i][binaryToInt(row)][binaryToInt(col)];

        char* ch = intToBinary(temp);
        for (int j = 0; j < 4; j ++)
        {
            b8[i*4 + j] = ch[j];
        }
    }

    for (int i = 0; i < 32; i ++)
    {
        pb[i] = b8[pTable[i] - 1];
    }

    return pb;
}


void des_key(char key[])
{
    FILE* fp_key;

    if (NULL == (fp_key = fopen(key, "rb")))  
    {  
        printf("文件打开失败！\n");
        system("pause");
        exit(0);
    }  

    fseek (fp_key, 0, SEEK_END);
    long lSize = ftell (fp_key);
    rewind (fp_key);

    int num = lSize/sizeof(char);
    char *str = (char*) malloc (sizeof(char)*num);

    if (str == NULL)
    {
        printf("开辟空间出错");
        exit(0);
    }
    fread(str, sizeof(char), num, fp_key);


    char keyBinary[65], pc1keyBinary[57];
    int i = 0;
    for (i = 0; i < strlen(str); i ++)
    {
        char* ch = charToBinary(str[i]);
        for (int j = 0; j < 8; j ++ )
        {
            keyBinary[i*8 + j] = ch[j];
        }
    }

    while (strlen(keyBinary) % 64 != 0)
    {
        keyBinary[i] = '0';
        i ++;
    }

    for (i = 0; i < 56; i ++)
    {
        pc1keyBinary[i] = keyBinary[pc1[i] - 1];
    }

    char c[17][29], d[17][29];
    char temp[57];
    for(int i = 0; i < 28; i ++)
    {
        c[0][i] = pc1keyBinary[i];
        d[0][i] = pc1keyBinary[i + 28];
    }

    for (i = 1; i <= 16; i ++)
    {
        for (int j = 0; j < loop[i - 1]; j ++)
        {
            c[i][j] = c[i - 1][j];
            d[i][j] = d[i - 1][j];
        }

        for (int j = 28 - loop[i - 1]; j < 28; j ++)
        {
            c[i][j] = c[i - 1][j];
            d[i][j] = c[i - 1][j];
        }

        for(int j = 0; j < 28; j ++)
        {
            temp[j] = c[i][j];
        }
        for (int j = 28; j < 56; j ++)
        {
            temp[j] = d[i][j];
        }

        char pc2Temp[49];
        for (int j = 0; j < 48; j ++)
        {
            pc2Temp[j] = temp[pc2[j] - 1];
            k[i - 1][j] = pc2Temp[j];
        }
    }

    free(str);
    str = NULL;
}


char* wen(char** wenBinary, int num, int flag)
{
    char ipWenBinary[100][65];
    char left[17][33], right[17][33], temp[65];
    static char result[65];
    for (int i = 0; i < num; i ++)
    {
        for(int j = 0; j < 64; j ++)
        {
            temp[j] = wenBinary[i][ip[j] - 1];
        }
        
        for(int j = 0; j < 64; j ++) ipWenBinary[i][j] = temp[j];
    }

    for (int i = 0; i < num; i ++)
    {
        for (int j = 0; j < 32; j ++)
        {
            left[0][j] = ipWenBinary[i][j];
            right[0][j] = ipWenBinary[i][j + 32];
        }

        for (int j = 0; j < 16; j ++)
        {
            char* ch1;
            char* ch2;
            for (int k = 0; k < 32; k ++)
            {
                left[j + 1][k] = right[j][k];
            }
            if (flag == 1) 
            {
                ch1 = xorAB(left[j], f(right[j], k[j]));
                for (int i = 0; i < 32; i ++ )
                {
                    right[j + 1][i] = ch1[i];
                }
            }
            else 
            {
                ch2 = xorAB(left[j], f(right[j], k[15 - j]));
                for (int i = 0; i < 32; i ++)
                {
                    right[j + 1][i] = ch2[i];
                }
            }
        }
        for(int i = 0; i < 32; i ++ )
        {
            temp[i] = right[16][i];
        }
        for (int i = 32; i < 64; i ++ )
        {
            temp[i] = left[16][i];
        }

        for (int j = 0; j < 64; j ++ )
        {
            result[i*64 + j] = temp[ipReverse[j] - 1];            
        }
    }

    if (flag == 2)
    {
        char ch[num*8];
        char ch1[9];
        for (int i = 0; i < num * 8; i ++)
        {
            for (int j = 0; j < 8; j ++)
            {
                ch1[j] = result[i * 8 + j];
            }
            ch[i] = binaryToInt(ch1);
        }

        for (int i = 0; i < 64; i ++)
        {
            result[i] = ch[i];
        }
    }

    return result;
}


void encryption(char input_file[], char output_file[], char key[])
{
    des_key(key);
    FILE* fp_input;

    if (NULL == (fp_input = fopen(input_file, "rb")))  
    {  
        printf("文件打开失败！\n");
        system("pause");
        exit(0);
    }  

    fseek (fp_input, 0, SEEK_END);
    long lSize = ftell (fp_input);
    rewind (fp_input);

    int num = lSize/sizeof(char);
    char *enstr = (char*) malloc (sizeof(char)*num);

    if (enstr == NULL)
    {
        printf("开辟空间出错");
        exit(0);
    }
    fread(enstr, sizeof(char), num, fp_input);

    char temp[num];
    char* strBinary[100];
    int k = 0;
    for (int i = 0; i < num; i ++)
    {
        char* ch = charToBinary(enstr[i]);
        for (int j = 0; j < 8; j ++)
        {
            temp[i*8 + j] = ch[j];
        }
        //temp[i] = charToBinary(enstr[i]);
        if(((i + 1) % 8 == 0) || (((i + 1) % 8 != 0) && (i == num - 1)))
        {
            int j = 0, s = 0;
            while (temp[j] != '\0') 
            {
                strBinary[k++][j] = temp[j];
                s++;
            }

            for (int t = 0; t < s; t ++)
            {
                temp[t] = '\0';
            }
        }
    }

    while (strlen(strBinary[k - 1]) % 64 != 0)
    {
        for (int i = strlen(strBinary[k - 1]); strBinary[k - 1][i] != '\0'; i --)
        {
            strBinary[k - 1][i] = '0';
        }
    }

    char* result = wen(strBinary, k, 1);

    FILE* fp_output;
    fp_output = fopen(output_file, "wb");
    if(fp_output == NULL)
    {
        printf("写出文件出错");
        exit(0);
    }

    fwrite(result, sizeof(char), k*64, fp_output);

    fclose(fp_output);
    free(enstr);
    enstr = NULL;
    fclose(fp_input);
    printf("%s加密成功,暗文在%s中\n", input_file, output_file);
}


void decryption(char input_file[], char output_file[], char key[])
{
    des_key(key);
    FILE* fp_input;

    if (NULL == (fp_input = fopen(input_file, "rb")))  
    {  
        printf("文件打开失败！\n");
        system("pause");
        exit(0);
    }  

    fseek (fp_input, 0, SEEK_END);
    long lSize = ftell (fp_input);
    rewind (fp_input);

    int num = lSize/sizeof(char);
    char *enstr = (char*) malloc (sizeof(char)*num);

    if (enstr == NULL)
    {
        printf("开辟空间出错");
        exit(0);
    }
    fread(enstr, sizeof(char), num, fp_input);

    char temp[num];
    char* strBinary[100];
    int k = 0;
    for (int i = 0; i < num; i ++)
    {
        char* ch = charToBinary(enstr[i]);
        for (int j = 0; j < 8; j ++)
        {
            temp[i*8 + j] = ch[j];
        }
        //temp[i] = charToBinary(enstr[i]);
        if(((i + 1) % 8 == 0) || (((i + 1) % 8 != 0) && (i == num - 1)))
        {
            int j = 0, s = 0;
            while (temp[j] != '\0') 
            {
                strBinary[k++][j] = temp[j];
                s++;
            }

            for (int t = 0; t < s; t ++)
            {
                temp[t] = '\0';
            }
        }
    }

    while (strlen(strBinary[k - 1]) % 64 != 0)
    {
        for (int i = strlen(strBinary[k - 1]); strBinary[k - 1][i] != '\0'; i --)
        {
            strBinary[k - 1][i] = '0';
        }
    }

    char* result = wen(strBinary, k, 2);

    FILE* fp_output;
    fp_output = fopen(output_file, "wb");
    if(fp_output == NULL)
    {
        printf("写出文件出错");
        exit(0);
    }

    fwrite(result, sizeof(char), k*64, fp_output);

    fclose(fp_output);
    free(enstr);
    enstr = NULL;
    fclose(fp_input);

    printf("%s解密成功,明文在%s中\n", input_file, output_file);
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        printf("参数输入不正确！");
        printf("提示: 文件名 命令 输入文件 key 输出文件");
        exit(0);
    }

    if(strcmp(argv[1], "-e") == 0)
    {
        encryption(argv[2], argv[4], argv[3]);   
    }

    else if (strcmp(argv[1], "-d") == 0)
    {
        decryption(argv[2], argv[4], argv[3]);
    }

    else printf("输入的参数不满足实验条件");

    system("pause");
    return 0;
}