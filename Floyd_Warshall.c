#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define inf INFINITY
void print_dmat(double**,int);
void print_pmat(int**,int);
int main(){
	double **A,**B;
	int **P,**Q;
	int i,j,k,n;
	printf("Enter number of vertice :\n");
	scanf("%d",&n);
	A = (double**)malloc(sizeof(double*)*n);
	B = (double**)malloc(sizeof(double*)*n);
	P = (int**)malloc(sizeof(int*)*n);
	Q = (int**)malloc(sizeof(int*)*n);
	printf("Enter The Incidence matrix :\n");	
	for(i=0;i<n;i++){	
    A[i] = (double*)malloc(sizeof(double)*n);
		B[i] = (double*)malloc(sizeof(double)*n);
		P[i] = (int*)malloc(sizeof(int)*n);
		Q[i] = (int*)malloc(sizeof(int)*n);
		for(j=0;j<n;j++)
			scanf("%lf",*(A+i)+j);
	}
	printf("Enter the weight of the edges :\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			if(i==j){
				A[i][j]=0;
				P[i][j]=-1;
				continue;
			}
			if(A[i][j]!=0){
				printf("Enter the weight of edge (%2d)--(%2d) : ",i+1,j+1);
				scanf("%lf",*(A+i)+j);
				P[i][j]=i;
			}
			else{
				A[i][j]=inf;
				P[i][j]=-1;
			}
		}	
	printf("D[0]=\n");
	print_dmat(A,n);
	printf("P[0]=\n");
	print_pmat(P,n);
	printf("\n\n\n");
	for(k=0;k<n;k++){
		for(i=0;i<n;i++)
			for(j=0;j<n;j++){
				if(k%2==0){
					if(A[i][j]<=A[i][k]+A[k][j]){
						B[i][j]=A[i][j];
						Q[i][j]=P[i][j];
					}
					else{
						B[i][j]=A[i][k]+A[k][j];
						Q[i][j]=P[k][j];
					}	
				}
				else{
					if(B[i][j]<=B[i][k]+B[k][j]){
						A[i][j]=B[i][j];
						P[i][j]=Q[i][j];
					}
					else{
						A[i][j]=B[i][k]+B[k][j];
						P[i][j]=Q[k][j];
					}	
				}
			}
		printf("D[%d]\n",k+1);
		if(k%2==0)
			print_dmat(B,n);
		else
			print_dmat(A,n);
		printf("P[%d]\n",k+1);
		if(k%2==0)
			print_pmat(Q,n);
		else
			print_pmat(P,n);
					
	}			
}
void print_dmat(double **arr,int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			if(arr[i][j]==inf)
				printf("--\t");
			else
				printf("%.2lf\t",arr[i][j]);
		printf("\n");
	}
	printf("\n");
}
void print_pmat(int **arr,int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			if(arr[i][j]==-1)
				printf("nil\t");
			else
				printf("%2d\t",(int)(arr[i][j]+1));
		printf("\n");
	}
	printf("\n");
}
