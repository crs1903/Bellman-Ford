#include<stdio.h>
#include<stdlib.h>

struct link
{
	int val;
	struct link *next;
};
typedef struct link list;
struct key
{
	int n,p,v,w;
	list *nbd;
};
typedef struct key node;

node *ver;
int n,**adj,*A,*B,**E;

void buildGraph(int);
void insert(int,int);
void res(int);

int main()
{
	int i,j;
	printf("Enter the number of vertices: ");
	scanf("%d",&n);
	adj = (int**)malloc(n*sizeof(int*));
	E = (int**)malloc(n*sizeof(int*));
	ver = (node*)malloc(n*sizeof(node));
	A = (int*)malloc(n*sizeof(int));
	B = (int*)malloc(n*sizeof(int));
	printf("\nEnter the adjacent matrix:\n");
	for(i=0;i<n;i++)
	{
		adj[i] = (int*)malloc(n*sizeof(int));
		E[i] = (int*)malloc((n+1)*sizeof(int));
		for(j=0;j<n;j++)
			scanf("%d",&adj[i][j]);
		adj[i][i] = 0;
		E[i][0] = 0;
	}

	printf("\n\nEnter Weight : \n");
	for(i=0;i<n;i++)
	{
		printf("vertex[%2d]:\t",i+1);
		scanf("%d",&ver[i].w);
	}
	for(i=0;i<n;i++)
	{
		A[i] = B[i] = -1;
		ver[i].n = i;
		ver[i].p = -1;
		ver[i].v = 0;
		ver[i].nbd = NULL;
	}
	buildGraph(0);
	res(0);
	
	printf("\n\nIndependent Set\t:");	
	for(j=1;j<=E[0][0];j++)
		printf("%d ",E[0][j]+1);
	printf("\n\nWeight : %d\n\n",A[0]);
	printf("\n");
	
	
}
void buildGraph(int s)
{
	int *Q = (int*)malloc(n*sizeof(int)),Q_s=0,Q_f=0,k,i;
	Q[Q_f++] = s;
	ver[s].v = 1;
	while(Q_s != Q_f)
	{
		k = Q[Q_s++];
		for(i=0;i<n;i++)
		{
			if((adj[k][i]==1)&&(ver[i].v==0))
			{
				ver[i].p = k;
				ver[i].v = 1;
				insert(i,k);
				Q[Q_f++] = i;
			}
		}
	}
}
void insert(int i,int s)
{
	list *new = (list*)malloc(sizeof(list));
	new->next = ver[s].nbd;
	new->val = i;
	ver[s].nbd = new;
}
void res(int s)
{
	int t;
	if(ver[s].nbd == NULL)
	{
		A[s] = ver[s].w;
		B[s] = 0;
		t = E[s][0]++;
		E[s][t+1] = s;
		return;
	}
	int W = 0,K = ver[s].w;
	list *p = ver[s].nbd,*r;
	while(p != NULL)
	{
		res(p->val);
		W += A[p->val];
		K += B[p->val];
		p = p->next;
	}
	B[s] = W;
	if(W>K)
	{
		A[s] = W;
		p = ver[s].nbd;
		while(p != NULL)
		{
			int q = E[s][0];
			t = 1;
			while(t<=E[p->val][0])
			{
				E[s][q+1] = E[p->val][t++];
				q++;
			}
			E[s][0] = q;
			p = p->next;
		}
		
	}
	else
	{
		A[s] = K;
		t = E[s][0];
		E[s][t+1] = s;
		E[s][0]++;
		p = ver[s].nbd;
		while(p != NULL)
		{
			r = ver[p->val].nbd;
			while(r != NULL)
			{
				int q = E[s][0];
				t = 1;
				while(t<=E[r->val][0])
				{
					E[s][q+1] = E[r->val][t++];
					q++;
				}
				E[s][0] = q;
				r = r->next;
			}
			p = p->next;
		}
		
	}
}
