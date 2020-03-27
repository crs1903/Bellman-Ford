#include<stdio.h>
#include<stdlib.h>

struct key
{
	int vertex;
	struct key* next;
};
typedef struct key node;

node **g;
int **adj;
int *visit;
int *Q,*parent,q_start,q_end;

int pop(int);
void build_graph(int n);
void insert(int i,int data);
void BFS(int sor);


int main()
{
	int n,i,j,k,s;
	printf("Enter the number of vertices:\n");
	scanf("%d",&n);
	visit=(int*)calloc(n,sizeof(int));
	Q=(int*)calloc(n,sizeof(int));
	parent=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		parent[i] = -1;
	adj=(int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
		adj[i]=(int*)calloc(n,sizeof(int));	
	printf("Enter adjacent matrix:\n");
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",*(adj+i)+j);	
	build_graph(n);
	printf("Enter source vertex:[ 1 to %d ]\n",n);
	scanf("%d",&s);
	BFS(s-1);
	
	for(k=0;k<n;k++)
	{
		int path[n]; 
		printf("Path to vertex %2d : ",k+1);
		j=0;
		i=k;
		while(i != -1)
		{
			path[j++] = i+1;
			i = parent[i];
		}
		while(j-->0)
		{
			printf("%d ",path[j]);
		}
		printf("\n");
	}
	
}

void build_graph(int n)
{
	g=(node**)malloc(n*sizeof(node*));
	for(int i=0;i<n;i++)
	{
		g[i]=NULL;
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			if(adj[i][j]==1)
			{
				insert(i,j);
			}
		}
}
void insert(int i,int data)
{
	node *p=(node*)malloc(sizeof(node));
	p->vertex=data;
	p->next=g[i];
	g[i]=p;
}
int pop(int i)
{
	int k=g[i]->vertex;
	g[i]=g[i]->next;
	return k;
}
void BFS(int sor)
{
	visit[sor]=1;
	node *p=g[sor];
	while(p!=NULL)
	{
		int k=p->vertex;
		if(visit[k]==0)
		{
			visit[k]=1;
			Q[q_end++]=k;
			parent[k]=sor;
		}
		p=p->next;
	}
	while(q_start<q_end)
	{
		BFS(Q[q_start++]);
	}
	visit[sor]=2;	
}








