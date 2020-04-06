#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int ver,d_time,f_time,p,visit,c;
	
}vertex;

struct key
{
	int v;
	struct key *next;
};
typedef struct key node;

vertex *V;
node **g;
int **adj,time = 0,com_num = 0;
node **component;

void push(int i,int j);
void build_graph(int n);
void insert(int i,int data);
void DFS(int);
void DFS_visit(int);

int main()
{
	int n,i,j,k,s;
	vertex tmp;
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
	
	
	time = 0;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(i>j)
				adj[i][j]^=adj[j][i]^=adj[i][j]^=adj[j][i];
	
	for(i=0;i<n-1;i++)
		for(j=i+1;j<n;j++)
			if(V[i].f_time < V[j].f_time)
			{
				tmp = V[i];
				V[i] = V[j];
				V[j] = tmp;
			}
	
	for(int i=0;i<n;i++)
	{
		g[i]=NULL;
		V[i].p = -1;
		V[i].visit = V[i].c = 0;
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			if(adj[i][j]==1)
			{
				insert(i,j);
			}
		}
	DFS(n);

	
	for(i=0;i<n;i++)
	{
		if(V[i].p == -1)
			com_num++;
	}

	printf("\n\nThe number of strongly connected components is : %d\n\n",com_num);
	
	component = (node**)malloc(com_num*sizeof(node*));
	for(i=0;i<com_num;i++)
		component[i] = NULL;

	k=0;
	for(i=0;i<n;i++)
	{
		if(V[i].p == -1)
		{	
			for(j=0;j<n;j++)
			{
				if(V[j].d_time>=V[i].d_time && V[j].f_time<=V[i].f_time)
					push(k,j);
			}
			k++;
		}
	}
	
	for(i=0;i<com_num;i++)
	{
		printf("component[%d] : { ",i+1);
		node *p = component[i];
		while(p != NULL)
		{
			printf("%d ",p->v+1);
			p = p->next;
		}
		printf("}\n");
	}
	
	
	
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
		V[i].d_time = V[i].f_time = V[i].visit = 0,V[i].c = 0;
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
void push(int i,int j)
{
	node *p=(node*)malloc(sizeof(node));
	p->v = j;
	p->next = component[i];
	component[i] = p;
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









