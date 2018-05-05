/*
以二元式形式输出单词<单词种类，单词属性>
其中单词种类用整数表示：
0：标识符
1：十进制整数
2：八进制整数
3：十六进制整数
运算符和界符，关键字采用一字一符，不编码
其中单词属性表示如下：
标识符，整数由于采用一类一符，属性用单词表示
运算符和界符，关键字采用一字一符，属性为空
*/
/*
2018.5.5 by yidaLiu
*/

#include "stdio.h"
#include "conio.h"
#include "ctype.h"
#include "string"

char area[80] = { '\0' }, wordchar[8];//存放标识符字符串
char ch;
int kind,//存放单词种类
	num,//存放整数
	p,//wordchar指针
	q,//area指针
	n;//用于循环

char *keyword[5]{ "if","then","else","while","do" };
char operator_[10]{ '+','-','*','/','>','<','=','(',')',';' };

void scan() {
	p = 0;
	for (n = 0;n < 7;n++)
		wordchar[n] = '\0';
	ch = area[q];
	while (ch==' ')
	{
		ch = area[++q];//如果是空格则指向下一个字符
	}

	if (isalpha(ch)) {//ch是字母字符
		while (isalnum(ch)) {
			wordchar[p++] = ch;
			//p++;
			//q++;
			ch = area[++q];
		}//while
		wordchar[p++] = '\0';
		//ch = area[q--];
		kind = 0;
		for (n = 0;n < 5;n++) {
			if (strcmp(wordchar, keyword[n]) == 0) {
				kind = 4;
				break;
			}//if
		}//for
	}//if

	else{
		if (isdigit(ch))//ch是数字字符
		{
			num = 0;
			switch (ch) {
			case '0':ch = area[++q];
				if (ch == 'x') {//十六进制
					ch = area[++q];
					for (n = 0;n < 7;n++)
						wordchar[n] = '\0';
					while (isdigit(ch) || ('a' <= ch && ch <= 'f')) {
						wordchar[p++] = ch;
						ch = area[++q];
					}
					wordchar[p++] = '\0';
					kind = 3;
				}//if
				else if(isdigit(ch))
				{
					while (isdigit(ch)) {//八进制
						num = num * 10 + ch - '0';
						ch = area[++q];
					}
					kind = 2;
				}
				else {
					kind = 1;
				}
				break;
			default:while (isdigit(ch)) {//十进制
						num = num * 10 + ch - '0';
						ch = area[++q];
					}
					kind = 1;
			}//switch
		}
		else {
			for (n = 0;n < 10;n++) {
				char check = operator_[n];
				if (ch == check) {
					kind = 5;
					break;
				}
				else {
					if (ch == '\0') {
						kind = 6;
						break;
					}
					else if (ch == '\t' || '\n')
						kind = 7;
					else
						kind = -1;
				}
					
			}//for
			q++;
		}
	}
}//scan

int main() {

	q = 0;
	printf("编译原理--词法分析器\n");
	FILE *fpRead = fopen("program.txt", "r");
	if (fpRead == NULL) {
		printf("Can't open the file.\n");
	}
	else {
		do {
			ch = fgetc(fpRead);
			area[q++] = ch;
		} while (!feof(fpRead));
		printf("\n结果如下：\n");
		q = 0;
		do {
			scan();
			switch (kind) {
			case -1:printf("输入错误！\n");break;
			case 0:printf("<%d,%s>\n", kind, wordchar);break;//标识符
			case 1:printf("<%d,%d>\n", kind, num);break;//十进制数
			case 2:printf("<%d,%d>\n", kind, num);break;//八进制数
			case 3:printf("<%d,%s>\n", kind, wordchar);break;//十六进制数
			case 4:printf("<%s,->\n", wordchar);break;//关键字
			case 5:printf("<%c,->\n", ch);break;//运算符
			}//switch
		} while (kind != 6);
	}
	return 0;
}