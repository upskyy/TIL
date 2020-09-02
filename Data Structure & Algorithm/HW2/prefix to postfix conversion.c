#include<stdio.h>
#include<string.h>

#define OPERATORS "+-*/"

void preToPostFix(char* preFixIn, char* postFix);
int findExprLen(char* exprIn);

int main() {
	char preFixExpr[256] = "-+*ABC/EF";
	char postFixExpr[256] = "";

	printf("Begin prefix to postfix conversion\n\n");
	preToPostFix(preFixExpr, postFixExpr);
	printf("Prefix expr : %-s\n", preFixExpr);
	printf("Postfix expr : %-s\n", postFixExpr);
	printf("\nEnd prefix to postfix conversion\n");

	return 0;
}
void preToPostFix(char* preFixIn, char* postFix) {
	char operate[2];
	char postFix1[256];
	char postFix2[256];
	char temp[256];
	int lenPreFix;

	if (strlen(preFixIn) == 1) {   //이전 것이 하나 남았을 때 postFix에 옮겨버리고 널문자 붙혀서 리턴
		*postFix = *preFixIn;
		*(postFix + 1) = '\0';
		return;
	} // if only operand

	*operate = *preFixIn;
	*(operate + 1) = '\0';

	lenPreFix = findExprLen(preFixIn + 1);
	strncpy(temp, preFixIn + 1, lenPreFix);
	*(temp + lenPreFix) = '\0';
	preToPostFix(temp, postFix1);

	strcpy(temp, preFixIn + 1 + lenPreFix);
	preToPostFix(temp, postFix2);

	strcpy(postFix, postFix1);
	strcat(postFix, postFix2);
	strcat(postFix, operate);
	return;
}

int findExprLen(char* exprIn) {

	int len1;
	int len2;
	if (strcspn(exprIn, OPERATORS) == 0) {
		len1 = findExprLen(exprIn + 1);
		len2 = findExprLen(exprIn + 1 + len1);

	}
	else
		len1 = len2 = 0;
	return len1 + len2 + 1;

}