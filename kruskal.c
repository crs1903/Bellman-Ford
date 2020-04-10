#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct
{
	int visit,parent;
}vertex;
typedef struct
{
	int s,t;
	double w;
}edge;
struct key
{
	int v;
	struct key *next;
};
typedef struct key node;

edge *E; 
node **g,**t;
vertex *V;
int N,**adj,e = 0;
double **W,**Wt;

void add_edge(edge);
void kruskal();
int check_path(int,int);
edge extractmin();
void minheap();
void build_graph();
void insert(int ,int);

int main()
{
	int i,j;
	printf("Enter the number of vertices in graph:\n");
	scanf("%d",&N);
	
	V = (vertex*)malloc(N*sizeof(vertex));
	g = (node**)malloc(N*sizeof(node));
	t = (node**)malloc(N*sizeof(node));
	for(i=0;i<N;i++)
		g[i] = t[i] =NULL;
	adj = (int **)malloc(N*sizeof(int*));
	for(i=0;i<N;i++)
		adj[i] = (int *)malloc(N*sizeof(int));
	W = (double **)malloc(N*sizeof(double*));
	for(i=0;i<N;i++)
		W[i] = (double *)malloc(N*sizeof(double));
	printf("\nEnter the adjacent matrix:\n");
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{
			scanf("%d",&adj[i][j]);
			if(i==j)
				adj[i][j] = 0;
		}
	for(i=0;i<N;i++)
		for(j=0;j<i;j++)
			if(adj[i][j]!=adj[j][i])
			{
				printf("\n\nThe graph must be undirected\n");
				exit(1);
			}
	printf("\n\n");
	for(i=0;i<N;i++)
		for(j=0;j<i;j++)
		{
			if(adj[i][j] == 1)
			{
				printf("Enter the Weight of edge ( %2d,%2d) : ",i+1,j+1);
				scanf("%lf",&W[i][j]);
				W[j][i] = W[i][j];
				e++;	
			}
			else
				W[i][j] = W[j][i] = INFINITY;
		}
	build_graph();
	printf("\n\nThe Tree is:");
	kruskal();
	printf("\n\n");
	for(i=0;i<N;i++)
	{
		node *p = t[i];
		if(p!=NULL)
			printf("Vertex [%2d] : ",i+1);
		while(p != NULL)
		{
			printf("%d ",p->v+1);
			p = p->next;
		}
		printf("\n");
	}
	double cost = 0;
	for(i=0;i<N;i++)
		for(j=0;j<i;j++)
		{	
			if(Wt[i][j] != INFINITY)
			cost += Wt[i][j];		
		}
	printf("\n\nTotal cost :\t%lf\n",cost);
}
void build_graph()
{
	int i,j,k = 0;
	for(i=0;i<N;i++)
	{
		V[i].visit = 0;
		V[i].parent =-1;
	}
	E = (edge*)malloc(e*sizeof(edge));
	for(i=0;i<N;i++)
		for(j=0;j<i;j++)
			if(adj[i][j] == 1)
			{
				E[k].s = i;
				E[k].t = j;
				E[k].w = W[i][j];
				k++;
				insert(i,j);
			}
			
}
void insert(int i,int j)
{
	node 	*p = (node*)malloc(sizeof(node)),
		*q = (node*)malloc(sizeof(node));
	
	
	p->v = i;
	p->next = g[j];
	g[j] = p;
	
	q->v = j;
	q->next = g[i];
	g[i] = q;
}
void minheap()
{
	int k,j,p,n;
	n = e;
	for(p=1;p<n;p++)
	{	
		k=p;
		do
		{	
			j=(k-1)/2;
			if(E[k].w < E[j].w)
			{
				edge tmp = E[k];
				E[k] = E[j];
				E[j] = tmp;
			}
			k=j;
		}while(j!=0);
	}
}
edge extractmin()
{
	int i,k,l,r;
	edge tmp = E[0];
	E[0] = E[e-1];
	E[e-1] = tmp;
	e--;
	for(i = 0; i < e ;)
	{
		k = i;
		l = 2*i+1;
		if(l < e && E[l].w < E[i].w)
			i = l;
		if(l+1 < e && E[l+1].w < E[i].w)
			i = l+1;
		if(i != k)
		{
			tmp = E[i];
			E[i] = E[k];
			E[k] = tmp;
		}
		else
			break;
	}
	return E[e];	
}
int check_path(int s,int d)
{
	if(t[s] == NULL)
		return 1;
	int Q_start = 0,Q_end =0,*Q = (int *)malloc(N*sizeof(int)),i;
	int *visit = (int *)calloc(N,sizeof(int)),*P = (int *)calloc(N,sizeof(int)),k;
	for(i=0;i<N;i++)
		P[i] = -1;
	Q[Q_end++]=s;
	visit[s] = 1;
	while(Q_end != Q_start)
	{
		k = Q[Q_start++];
		node *p = t[k];
		while(p != NULL)
		{
			if(p->v == d)
				return 0;
			if(visit[p->v] == 0)
			{
				Q[Q_end++] = p->v;
				P[p->v] = k;
				visit[p->v] = 1;
			}
			p = p->next;
		}	
		visit[k] = 2;		
	}
	return 1;
	
}
void kruskal()
{
	int i,j;
	Wt = (double**)malloc(N*sizeof(double*));
	for(i=0;i<N;i++)
	{
		Wt[i] = (double*)malloc(N*sizeof(double));
		for(j=0;j<N;j++)
			Wt[i][j] = INFINITY;
	}
	
	edge h;
	minheap();
	while(e != 0)
	{
		h = extractmin();
		if(check_path(h.s,h.t))
		{
			add_edge(h);
			Wt[h.s][h.t] = Wt[h.t][h.s] = h.w;
		}		
	}
}
void add_edge(edge h)
{
	node 	*p = (node*)malloc(sizeof(node)),
		*q = (node*)malloc(sizeof(node));
	
	p->v = h.s;
	p->next = t[h.t];
	t[h.t] = p;
	
	q->v = h.t;
	q->next = t[h.s];
	t[h.s] = q;
		
}
