#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;
char ch;
int iskey(char *word)
{

        if(!strcmp(word,"begin"))
            return 1;
        else if(!strcmp(word,"if"))
            return 2;
        else if(!strcmp(word,"then"))
            return 3;
        else if(!strcmp(word,"while"))
            return 4;
        else if(!strcmp(word,"do"))
            return 5;
        else if(!strcmp(word,"end"))
            return 6;

    return 0;
}
int sign_2(char *word)
{
    if(!strcmp(word,":="))
        return 18;
    else if(!strcmp(word,"<>"))
        return 21;
    else if(!strcmp(word,"<="))
        return 22;
    else if(!strcmp(word,">="))
        return 24;
    return 0;
}
int  isnum(char c)
{
    if(c>='0'&&c<='9')
        return 1;
    return 0;
}

int isalpha(char c)
{
    if(c>='a'&&c<'z')
        return 1;
    else  return 0;

}
void scanner(FILE *fp)
{
    char word[20]={'\0'};

    char ch;
    int i,c;

    ch  = fgetc(fp);

    if(isalpha(ch))
    {
        word[0] = ch;
        ch  = fgetc(fp);
        i = 1;
        while(isnum(ch)||isalpha(ch))
        {
            word[i]=ch;
            i++;
            ch = fgetc(fp);
        }
        word[i] = '\0';
        fseek(fp,-1,1);
        c = iskey(word);
        if(c)
        {
            switch(c)
            {
            case 1:cout<<"(1,"<<word<<")"<<endl;break;
            case 2:cout<<"(2,"<<word<<")"<<endl;break;
            case 3:cout<<"(3,"<<word<<")"<<endl;break;
            case 4:cout<<"(4,"<<word<<")"<<endl;break;
            case 5:cout<<"(5,"<<word<<")"<<endl;break;
            case 6:cout<<"(6,"<<word<<")"<<endl;break;

            }
        }
        else cout<<"(10,"<<word<<")"<<endl;

    }
    else
        if(isnum(ch))
        {
            word[0] = ch;
            ch = fgetc(fp);
            i = 1;
            while(isnum(ch))
            {
                word[i] = ch;
                i++;
                ch = fgetc(fp);
            }
            word[i] = '\0';
            fseek(fp,-1,1);
            cout<<"(11,"<<word<<")"<<endl;
        }
        else
        {
            word[0] = ch;

            switch(ch)
            {
                case '+':cout<<"(13,"<<word<<")"<<endl;break;
                case '-':cout<<"(14,"<<word<<")"<<endl;break;
                case '*':cout<<"(15,"<<word<<")"<<endl;break;
                case '/':cout<<"(16,"<<word<<")"<<endl;break;
                case ':':
                    ch = fgetc(fp);
                    if(ch=='='){
                    word[1]=ch;
                    cout<<"(18,"<<word<<")"<<endl;
                    }
                    else{
                        fseek(fp,-1,1);
                        cout<<"(17,"<<word<<")"<<endl;
                    }
                    break;
                case '<':
                    ch = fgetc(fp);
                    if(ch=='='){
                        word[1]=ch;
                        cout<<"(22,"<<word<<")"<<endl;
                    }
                    else if(ch=='>')
                    {
                        word[1]=ch;
                        cout<<"(21,"<<word<<")"<<endl;
                    }

                    else{
                        fseek(fp,-1,1);
                        cout<<"(20,"<<word<<")"<<endl;
                    }
                    break;
                case '>':
                    ch = fgetc(fp);
                    if(ch=='='){
                    word[1]=ch;
                    cout<<"(24,"<<word<<")"<<endl;
                    }
                    else{
                        fseek(fp,-1,1);
                        cout<<"(23,"<<word<<")"<<endl;
                    }
                    break;
                case '=':cout<<"(25,"<<word<<")"<<endl;break;
                case ';':cout<<"(26,"<<word<<")"<<endl;break;
                case '(':cout<<"(27,"<<word<<")"<<endl;break;
                case ')':cout<<"(28,"<<word<<")"<<endl;break;
                case '#':cout<<"(0,"<<word<<")"<<endl;break;



            }

        }

}

int main()
{
    FILE *fp;
    fp = fopen("E:\\1.txt","r");
    if(fp=='\0')
    {
        cout<<"读入文件错误"<<endl;
        exit(0);
    }
    cout<<"************词法分析结果如下****************\n";
    while(ch!='#')
    {
        ch = fgetc(fp);
        if(ch=='#') break;
        else if(ch==' '||ch=='\t'||ch=='\n'){}
        else {
            fseek(fp,-1,1);
            scanner(fp);
        }
    }
    return 0;
}
