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
//��a����λ��
{
	int low, high,mid;
	low = 0, high = n - 1;
	quick(a, low, high);
	if (n % 2)
		return a[n / 2];
	else
		return(a[n / 2] + a[n / 2 - 1]) / 2;
}
void quick(int a[], int low, int high)//��������ƽ�����Ӷ�ΪO(nlogn)
{
	int i, j, x;
	if (low < high) {
		i = low;
		j = high;
		x = a[i];//ѡ������Ŧ
		do {
			while (i < j && a[j] >= x)//jָ��ǰ��
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
		} while (i != j);//i,j������
		a[i] = x;
		quick(a, low, i - 1);//�������ļ�����
		quick(a, i + 1, high);//�������ļ�����
	}
}