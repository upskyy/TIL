#include<stdio.h>
int main()
{
	int x, y, num;
	int p,q,k;
	  for(y=0;y<3;y++)
    {
	printf("가장 긴 변의 길이 : "); //짝수는 안됨. 
    scanf("%d",&num);
    printf("출력 형태(1~3) : ");
    scanf("%d",&x);
    
    switch(x)
    {
    	case 1:
    		for(p=0;p<num;p++)
    		{
    			for(q=0;q<=p;q++)
    			{
    				printf("*");
				}
			printf("\n");
			}
			break;
		case 2:
			for(p=0;p<num;p++)
			{
				for(q=num;q>p;q--)
				{
					printf("*");
				}
				printf("\n");
			}
			break;
		case 3:
			for(p=0;p<num;p++)
			{
				for(q=num-1;q>p;q--)
				printf(" ");
				for(k=1;k<=2*p+1;k++)
				{printf("*");
			}
			printf("\n");
			}
			break;
	}
}
return 0;
}
