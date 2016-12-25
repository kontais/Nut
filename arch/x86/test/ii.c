#include<stdio.h>
#define M 2
#define N 3

int main()
{
	int i,j,s,n;
	int c,d,e,f;
	int a[M][N]={0};
	int b[M][N]={0};
	printf("please input M*N numbers\n");
	for(i=0; i<M; i++)
	{
		for(j=0; j<N; j++)
		{
			scanf("%d",&n);
			a[i][j]=n;
		}
		
	}
	for(i=0; i<M; i++)
	{
		for(j=0; j<N; j++)
		{
			c=d=e=f=1;
			if(i-1>=0)
			{
				if(a[i][j]<a[i-1][j])
					c=0;
			}
			if(i+1<M)
			{
				if(a[i][j]<a[i+1][j])
					d=0;
			}
			if(j-1>=0)
			{
				if(a[i][j]<a[i][j-1])
					e=0;
			}
			if(j+1<N)
			{
				if(a[i][j]<a[i][j+1])
					f=0;
			}
			s=c*d*e*f;
			if(s==0)
				b[i][j]=0;
			else
				b[i][j]=1;
		}
	}
	for(i=0; i<M; i++)
	{
		for(j=0; j<N; j++)
		{
			printf("%d\t",b[i][j]);
		}
	}
	return 0;
}
