#include <stdio.h>

int     ch;
char	count=0;

int main()
{
	ch=getchar();
	while (!feof(stdin)){
		if ((count--)==0) { printf("\n"); count=20; };
		printf("%d,",ch);
		ch=getchar();
	}
}                             