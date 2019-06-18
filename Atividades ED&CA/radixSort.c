#include <stdio.h>
#define MAX 10

void countSort(int *A, int k, int n)
{
	int B[n];
	int C[MAX];
	int i,j;
	
	//inicializa com zero
	for (i=0;i<n;i++)
		B[i]=0;
	//inicializa com zero
	for (i=0;i<k;i++)
		C[i]=0;
	//complementos de casas de cada valor
	
	for(j=0;j<n;j++)
		C[(A[j]/k) %10]++;

	for(i=1;i<=MAX;i++)
		C[i]=C[i]+C[i-1];
	
	for(j=n-1;j>=0;j--)
	{
		B[(C[(A[j]/k) %10] )-1]=A[j];
		C[(A[j]/k)%10]= C[(A[j]/k)%10]-1;

	}
}
void radixsort(int *A, int k, int n) 
{
    int exp;
    for (exp = 1; k/exp > 0; exp *= 10)
        //k=k/exp;
        countSort(A,exp,n);
 
}

int main()
{
 	
	int v[]={5,6,8,1,3,1,7};
	int v7[7] = {329,457,657,839,436,720,355};
	int v3[10] = {5,2,7,8,10,6,1,4,9,3};
	int v2[]={6,7,1,1,2,4,2,8};
 	//countSort(v7,839,7);
 	radixsort(v,8,7);

	for(int i=0;i<7;i++)
 	{
 		printf("%d\n",v[i]);
 	}

	return 0;
}