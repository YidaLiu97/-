/*
�Զ�Ԫʽ��ʽ�������<�������࣬��������>
���е���������������ʾ��
0����ʶ��
1��ʮ��������
2���˽�������
3��ʮ����������
������ͽ�����ؼ��ֲ���һ��һ����������
���е������Ա�ʾ���£�
��ʶ�����������ڲ���һ��һ���������õ��ʱ�ʾ
������ͽ�����ؼ��ֲ���һ��һ��������Ϊ��
*/
/*
2018.5.5 by yidaLiu
*/

#include "stdio.h"
#include "conio.h"
#include "ctype.h"
#include "string"

char area[80] = { '\0' }, wordchar[8];//��ű�ʶ���ַ���
char ch;
int kind,//��ŵ�������
	num,//�������
	p,//wordcharָ��
	q,//areaָ��
	n;//����ѭ��

char *keyword[5]{ "if","then","else","while","do" };
char operator_[10]{ '+','-','*','/','>','<','=','(',')',';' };

void scan() {
	p = 0;
	for (n = 0;n < 7;n++)
		wordchar[n] = '\0';
	ch = area[q];
	while (ch==' ')
	{
		ch = area[++q];//����ǿո���ָ����һ���ַ�
	}

	if (isalpha(ch)) {//ch����ĸ�ַ�
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
		if (isdigit(ch))//ch�������ַ�
		{
			num = 0;
			switch (ch) {
			case '0':ch = area[++q];
				if (ch == 'x') {//ʮ������
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
					while (isdigit(ch)) {//�˽���
						num = num * 10 + ch - '0';
						ch = area[++q];
					}
					kind = 2;
				}
				else {
					kind = 1;
				}
				break;
			default:while (isdigit(ch)) {//ʮ����
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
	printf("����ԭ��--�ʷ�������\n");
	FILE *fpRead = fopen("program.txt", "r");
	if (fpRead == NULL) {
		printf("Can't open the file.\n");
	}
	else {
		do {
			ch = fgetc(fpRead);
			area[q++] = ch;
		} while (!feof(fpRead));
		printf("\n������£�\n");
		q = 0;
		do {
			scan();
			switch (kind) {
			case -1:printf("�������\n");break;
			case 0:printf("<%d,%s>\n", kind, wordchar);break;//��ʶ��
			case 1:printf("<%d,%d>\n", kind, num);break;//ʮ������
			case 2:printf("<%d,%d>\n", kind, num);break;//�˽�����
			case 3:printf("<%d,%s>\n", kind, wordchar);break;//ʮ��������
			case 4:printf("<%s,->\n", wordchar);break;//�ؼ���
			case 5:printf("<%c,->\n", ch);break;//�����
			}//switch
		} while (kind != 6);
	}
	return 0;
}