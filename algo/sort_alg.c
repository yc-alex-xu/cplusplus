#include <stdio.h>

//后边先有序
void bubble_sort(int arr[], int len)
{
    for (int i = len - 1; i > 0; i--)
    {
        int changed = 0;
        for (int j = 0; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                changed = 1;
            }
        }
        if (!changed)
            break;
    }
}
//前边先有序,但不能保证前面的就是最小的
void insertion_sort(int arr[], int len)
{
    int i, j, temp;
    for (i = 1; i < len; i++)
    { //前提，a[i] 之前是有序的，因为a[0]可以理解为一个元素组成的队伍，自然是有序的，不需要搞插入了
        temp = arr[i];//让arr[i]前的i个元素空出一个位置
        for (j = i; j > 0 &&arr[j - 1] > temp ; j--) //j代表的是被插的队伍
                arr[j] = arr[j - 1]; //小于我的都后退
        arr[j] = temp;//如果实际没有回退过，
    }
}

int fab(int n)
{
    if (n<=2) {
        return 1;
    }
    else
    {
        return fab(n-1)+fab(n-2);
    }
    
}

int main()
{
    int arr[] = {22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70};
    int len = (int)sizeof(arr) / sizeof(arr[0]);
    insertion_sort(arr, len);
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);

    for (int i = 0; i < 10; i++)
    {
        printf("fab[%d]=%d\n",i,fab(i));
    }

    return 0;
}