#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


int  **I,*P;
double **W,*D;


char *strrev(char*);
void initialize(int,int);
void relax(int,int);
int bellman_ford(int,int);
char* path(int,int);

int main()
{

	int i,j,n,s;
	printf("Enter the number of nodes:\n");
	scanf("%d",&n);
	W = (double**)malloc(n*sizeof(double*));
	for(i=0;i<n;i++)
		W[i] = (double*)malloc(n*sizeof(double));
	I = (int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
		I[i] = (int*)malloc(n*sizeof(int));
	P = (int*)malloc(n*sizeof(int));
	D = (double*)malloc(n*sizeof(double));

	printf("Enter the incidence Matrix :\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&I[i][j]);

	printf("Enter weights to corresponding edges:\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(I[i][j] == 1)
			{
				printf("Edge (%2d, %2d) weight: ",i+1,j+1);
				scanf("%lf",&W[i][j]);
			}
			else
				W[i][j] = INFINITY;
	printf("Enter Source [ 1 --> %d ]\n",n);
	scanf("%d",&s);
	if(bellman_ford(s-1,n) == 0)
	{
		printf("There exist a negetive cycle:\n");
		return 0;
	}
	printf("\n\nThe distance vector is:\n");
	for(i=0;i<n;i++)
	{
		printf("%.3lf ",D[i]);
	}			
	printf("\n");
	printf("\n\nThe paths are :\n");
	for(i=0;i<n;i++)
	{
		printf("path to %d : %s\n",i+1,path(i,n));
	}
	printf("\n");
	
}


void initialize(int i,int n)
{
	int j;
	for(j=0;j<n;j++)
	{
		D[j] = INFINITY;
		P[j] = -1;
	}
	D[i] = 0;
}


void relax(int i,int j)
{
	double k = D[i] + W[i][j];
	if(D[j] > k)
	{
		D[j] = k;
		P[j] = i;
	}
}


int bellman_ford(int s,int n)
{
	int i,j,r;
	initialize(s,n);
	for(r=0;r<n-1;r++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(I[i][j] == 1)
					relax(i,j);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(I[i][j] == 1 && D[j] > D[i] + W[i][j])
				return 0;
	return 1;
}


char* path(int i,int n)
{
	char *p = (char*)malloc(10*n*sizeof(char));
	int k=i;
	while(P[i] != -1)
	{
		sprintf(p,"%s>-- %d ",p,P[i]+1);
		i=P[i];
	}
	strrev(p);
	sprintf(p,"%s%2d",p,k+1);
	return p;
}


char *strrev(char* str)
{
	if(strlen(str)<=1)
		return str;
	int p=0,q=strlen(str)-1;
	while(p<q)
	{
		*(str+p)^=*(str+q)^=*(str+p)^=*(str+q);
		p++;
		q--;
	}
	return str;
}













