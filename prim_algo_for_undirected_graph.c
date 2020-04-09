#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct
{
	int visit,parent;
	double dist;
}vertex;
struct key
{
	int v;
	struct key *next;
};
typedef struct key node;

vertex *V;
node **g,**t;
int **adj,*H,H_size=0;
double **W;

void relax(int i,int j);
void prim_algo(int s,int n);
void minheap();
int extractmin(void);
void initialize(int n);
void build_graph(int n);
int check(int n);
void insert(int ,int);
void put_edge(int,int);

int main()
{
	int n,i,j,s;
	printf("Enter the number of vertices:\n");
	scanf("%d",&n);

	V = (vertex*)malloc(n*sizeof(vertex));
	H = (int*)malloc(n*sizeof(int));
	g = (node**)malloc(n*sizeof(node*));
	t = (node**)malloc(n*sizeof(node*));
	adj = (int **)malloc(n*sizeof(int));
	W = (double**)malloc(n*sizeof(double*));
	
	for(i=0;i<n;i++)
	{
		adj[i] = (int*)malloc(n*sizeof(int)); 
		W[i] = (double*)calloc(n,sizeof(double));
	}
	printf("Enter the adjacent matrix:\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			scanf("%d",&adj[i][j]);
			if(i == j)
				adj[i][j] = 0;
		}
	
	if(check(n) == 0)
	{
		printf("\nGraph is not an undirected graph\n");
		exit(1);
	}
	printf("\n\n");
	for(i=0;i<n;i++)
		for(j=0;j<i;j++)
		{
			if(adj[i][j] == 1)
			{
				printf("weight of edge (%2d,%2d) : ",i+1,j+1);
				scanf("%lf",&W[i][j]);
				W[j][i] = W[i][j];
				if(W[i][j] == 0)
				{
					printf("\n\n*****Enter positive weight*****\n\n");
					j--;
				}
			}
		}
	
	initialize(n);
	build_graph(n);
	printf("\n\nEnter source [1 to %d]:\n",n);
	scanf("%d",&s);
	V[s-1].dist =0;
	prim_algo(s-1,n);
	printf("\n\nvertex\t\t|  Neighbourhood\n");
	printf("--------------------------------\n");
	for(i=0;i<n;i++)
	{
		node *p = t[i];
		printf("vertex [%2d]\t",i+1);
		while(p != NULL)
		{
			printf("%4d",p->v+1);
			p=p->next;
		}
		printf("\n");
	}
	

}
void minheap()
{
	int k,j,p,n;
	n = H_size;
	for(p=1;p<n;p++)
	{	
		int k=p;
		do
		{	
			j=(k-1)/2;
			if(V[H[k]].dist < V[H[j]].dist)
				H[k]^=H[j]^=H[k]^=H[j];
			k=j;
		}while(j!=0);
	}
}
int extractmin(void)
{
	minheap();
	int k= H[0];
	H[0]=H[H_size-1];
	H_size--;
	minheap();
	return k;
}
void relax(int i,int j)
{
	if(V[j].dist > W[i][j])
	{
		V[j].dist = W[i][j];
		V[j].parent = i;
	}
}
void put_edge(int i,int j)
{
	node 	*p = (node *)malloc(sizeof(node)),
		*q = (node *)malloc(sizeof(node));
	
	p->v = i;
	p->next = t[j];
	t[j] = p;

	q->v = j;
	q->next = t[i];
	t[i] = q;
}
void prim_algo(int s,int n)
{
	int k;	
	H[H_size++] = s;
	V[s].visit = 1;
	
	while(H_size != 0)
	{
		k = extractmin();
		if(V[k].parent != -1)
			put_edge(V[k].parent,k);
		node *p = g[k];
		while(p != NULL)
		{
			
			if(V[p->v].visit != 2)
			{
				relax(k,p->v);
				if(V[p->v].visit == 0)
				{
					H[H_size++] = p->v;
					V[p->v].visit = 1;
				}
			}
			p = p->next;
		}
		V[k].visit = 2;	;
	}
}
int check(int n)
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<i;j++)	
			if(adj[i][j] != adj[j][i])
				return 0;
	return 1;
}
void initialize(int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		V[i].visit = 0;
		V[i].parent = -1;
		V[i].dist = INFINITY;
	}
}
void insert(int i,int j)
{
	node 	*p = (node *)malloc(sizeof(node)),
		*q = (node *)malloc(sizeof(node));
	
	p->v = i;
	p->next = g[j];
	g[j] = p;

	q->v = j;
	q->next = g[i];
	g[i] = q;
}
void build_graph(int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{	
		g[i] = NULL;
		for(j=0;j<n;j++)
		{
			if(adj[i][j]==1)
				insert(i,j);
		}
	}
}

