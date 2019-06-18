#include <stdio.h>
#define MAX 100

void countSort(int *A, int k, int n)
{
	int B[n];
	int C[k];
	int i,j;

	//inicializa com zero
	for (i=0;i<k;i++)
		B[i]=0;
	//inicializa com zero
	for (i=0;i<k;i++)
		C[i]=0;
	//complementos de casas de cada valor
	for(j=0;j<n;j++)
		C[A[j]]++;

	for(i=1;i<=k;i++)
		C[i]=C[i]+C[i-1];
	
	for(j=n-1;j>=0;j--)
	{
		B[C[A[j]]]=A[j];
		C[A[j]]= C[A[j]]-1;

	}

	for(i=0; i<=n; ++i)
 	{
 		printf("%d\n",B[i]);
 	}

}


int main()
{
 	
	int v[]={5,6,8,1,3,1,7};
	int v2[]={6,7,1,1,2,4,2,8};
 	countSort(v2,8,8);
 	

	return 0;
}
