#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int ver,d_time,f_time,p,visit;
	
}vertex;

struct key
{
	int v;
	struct key *next;
};
typedef struct key node;

vertex *V;
node **g;
int **adj,time = 0;


void build_graph(int n);
void insert(int i,int data);
void DFS(int);
void DFS_visit(int);

int main()
{
	int n,i,j,k,s;
	printf("Enter the number of vertices:\n");
	scanf("%d",&n);
	
	adj=(int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
		adj[i]=(int*)calloc(n,sizeof(int));	

	printf("Enter adjacent matrix:\n");
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",*(adj+i)+j);	
	build_graph(n);
	DFS(n);
	printf("time are:\n");
	printf("\n\nvertex\t\td_time\t\tf_time\t\tparent\t\tvisit\n\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",V[i].ver+1,V[i].d_time,V[i].f_time,V[i].p,V[i].visit);
	}
	
	printf("\n");
	
	
}

void build_graph(int n)
{
	g=(node**)malloc(n*sizeof(node*));
	for(int i=0;i<n;i++)
	{
		g[i]=NULL;
	}
	V=(vertex*)malloc(n*sizeof(vertex));

	for(int i=0;i<n;i++)
	{
		V[i].ver = i;
		V[i].d_time = V[i].f_time = V[i].visit = 0;
		V[i].p = -1;
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
	p->v=data;
	p->next=g[i];
	g[i]=p;
}

void DFS(int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		if(V[i].visit == 0)
			DFS_visit(i);
	}
	
}
void DFS_visit(int sor)
{
	time++;
	V[sor].d_time = time;
	V[sor].visit = 1;
	node *p = g[sor];
	while(p!= NULL)
	{
		if(V[p->v].visit == 0)
		{
			V[p->v].p = sor;
			DFS_visit(p->v);
		}
		p=p->next;
	}
	V[sor].visit = 2;
	time++;
	V[sor].f_time = time;
}









