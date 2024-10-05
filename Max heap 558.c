#include<stdio.h>
void swap(int *a, int *b)
{
int temp = *b;
	*b = *a;
    *a= temp;
}
void printarray(char message[],int arr[],int n)
{
	printf("%s",message);
	int i;
	for(i=0;i<n;++i)
	{
		printf("%d\t",arr[i]);
	}
	printf("\n");
}
void heapify(int arr[],int n,int i)
{
	int largest = i;
	int leftchild = 2*i + 1;
	int rightchild = 2*i + 2;
	if(leftchild < n && arr[leftchild] > arr[largest])
	largest = leftchild;
	if(rightchild < n && arr[rightchild] > arr[largest])
	largest = rightchild;
	if(largest != i)
	{
		swap(&arr[i], &arr[largest]);
		heapify(arr,n,largest);
	}
}
void buildheap(int arr[],int n)
{
	int lastnonleafnode = (n/2)-1,i;
	for(i = lastnonleafnode;i>=0;i--)
	{
		heapify(arr,n,i);
	}
}
void main()
{
	int arr[]={4,18,17,10,19,20,14,8,3,12};
	int n = sizeof(arr) / sizeof(arr[0]);
	printarray("Array is :",arr,n);
	buildheap(arr,n);
	printarray("Array representation of Heap is : ",arr,n);
}
