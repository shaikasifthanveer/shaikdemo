#include<stdio.h>
void quicksort(int [],int,int);
int partition(int [],int,int);
int main()
{
	int a[50];
	int n,i;
	printf("enter the number of elements:");
	scanf("%d",&n);
	if(n<=0)
	{
		printf("\nInvalid Data");
		return 0;
	}
	printf("\nEnter the %d elements to be sorted:\n",n);
	for(i=0;i<n;i++)
	{
		printf("a[%d]=\t",i);
		scanf("%d",&a[i]);
	}
	quicksort(a,0,n-1);
	printf("After applying quick sort\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t",a[i]);
	}
	printf("\n");
	return 0;
}
int partition(int a[],int low,int high)
{
	int pwt,i,j,temp;
	if(low < high)
	{
		pwt = low;
		i = low;
		j = high;
		while(i<j)
		{
			while(a[i]<=a[pwt] && i<=high)
			{
				i++;
			}
			while(a[j]>a[pwt] && j>=low)
			{
				j--;
			}
			if(i<j)
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
		temp=a[j];
		a[j]=a[pwt];
		a[pwt]=temp;
		return j;
	}
}
void quicksort(int a[],int low,int high)
{
	if(low<high)
	{
		int j=partition(a,low,high);
		quicksort(a,low,j-1);
		quicksort(a,j+1,high);
	}
}
