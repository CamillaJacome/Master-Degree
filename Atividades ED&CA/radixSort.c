#include <stdio.h>
#define max 10

void radixsort(int *V, int n) 
{

	int i,exp=1,maior=0,bucket[n],temp[n];

	for(i=0;i<n;i++) 
	{
		if(V[i]>maior) 
			maior = V[i];		
	}

	while((maior/exp) > 0) 
	{
		for (i=0;i<n;i++) 
			bucket[i] = 0;

		for(i=0;i<n;i++) 
			bucket[(V[i] / exp) % 10]++;
		
		for(i=1;i<n;i++) 
			bucket[i] += bucket[i-1];
		
		for(i=(n - 1);i>=0;i--) 
			temp[--bucket[(V[i] / exp) % 10]] = V[i];
		
		for(i=0;i<n;i++) 
			V[i] = temp[i];
		
		exp *= 10;
	}
}

int main() {
	int v[7] = {329,457,657,839,436,720,355};
	int v2[10] = {5,2,7,8,10,6,1,4,9,3};
	radixsort(v2,10);
	for (int i=0;i<10;i++) {
		printf("%d ", v2[i]);
	}
	return(0);
}
