#include "stdio.h"
#include "stdlib.h"
int MidValue(int a[], int n);
void quick(int a[], int low, int high);
int main()
{
	int ans, * a, n, i;
	scanf("%d", &n);
	a = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		scanf("%d", &a[i]);
	printf("%d", MidValue(a, n));
	free(a);
	return 1;
}
int MidValue(int a[], int n)
//求a的中位数
{
	int low, high,mid;
	low = 0, high = n - 1;
	quick(a, low, high);
	if (n % 2)
		return a[n / 2];
	else
		return(a[n / 2] + a[n / 2 - 1]) / 2;
}
void quick(int a[], int low, int high)//快速排序，平均复杂度为O(nlogn)
{
	int i, j, x;
	if (low < high) {
		i = low;
		j = high;
		x = a[i];//选出的枢纽
		do {
			while (i < j && a[j] >= x)//j指针前移
				j--;
			if (i < j) {
				a[i] = a[j];
				i++;
				while (i < j && a[i] <= x)
					i++;
				if (i < j){
					a[j] = a[i];
					j--;
				}
			}
		} while (i != j);//i,j不相遇
		a[i] = x;
		quick(a, low, i - 1);//对左子文件排序
		quick(a, i + 1, high);//对右子文件排序
	}
}