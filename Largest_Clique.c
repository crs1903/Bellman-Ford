#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>


int n,**adj;
uint64_t Largest_Clique;

int  checkClique(uint64_t);
int  posbit(uint64_t);
void updateClique(uint64_t);
void printClique();

int main()
{
	int i,j,t = n-1;
	uint64_t k;
	printf("Enter the Number of vertices:\n");
	scanf("%d",&n);
	adj = (int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
		adj[i] = (int*)malloc(n*sizeof(int));
	printf("Enter the Adjacent matrix:\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&adj[i][j]);
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(adj[i][j] != adj[j][i])
			{
				printf("\n\nThe Matrix is not symmetric\n");
				exit(1);
			}
	k = (1<<n)-1;
	while(k != 0)
	{
		if(checkClique(k))
			if(posbit(k) > posbit(Largest_Clique))
				Largest_Clique = k;
		k--;
				
	}
	printClique();
}
int checkClique(uint64_t k)
{
	int p = posbit(k),t=0,i=0,j;
	//printf("%d\n",p);
	int *arr = (int*)malloc(p*sizeof(int));
	while(k != 0)
	{
		if((k&1)==1)
			arr[t++] = i;
		k>>=1;
		i++;
	}
	for(i=0;i<p;i++)
	{
		if(adj[i][i] == 1)
			return 0;
		for(j=0;j<i;j++)
			if(adj[arr[i]][arr[j]] != 1)
				return 0;
	}
	free(arr);
	return 1;
}
int  posbit(uint64_t k)
{
	int count = 0;
	while(k!=0)
	{
		k = (k&(k-1));
		count++;
	}
	return count;
}
void printClique()
{
	uint64_t k = Largest_Clique;
	int p = posbit(k),t=0,i=0,j;
	int *arr = (int*)malloc(p*sizeof(int));
	while(k != 0)
	{
		if((k&1)==1)
			arr[t++] = i;
		k>>=1;
		i++;
	}
	printf("\n\nThe largest Clique is :\t");
	for(i=0;i<p;i++)
	{
		printf("%2d ",arr[i]+1);
	}
	free(arr);
	printf("\n\n");
}

