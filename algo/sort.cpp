#include <iostream>
using namespace std;

//后边先有序
void bubbleSort(int arr[], int len)
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
void insertionSort(int arr[], int len)
{
    int i, j, temp;
    //前提，a[i] 之前是有序的，因为a[0]可以理解为一个元素组成的队伍，自然是有序的，不需要搞插入了
    for (i = 1; i < len; i++)
    {
        temp = arr[i]; //让arr[i]前的i个元素空出一个位置
        for (j = i; j > 0 && arr[j - 1] > temp; j--)
        {
            arr[j] = arr[j - 1]; //小于我的都后退
        }
        arr[j] = temp;
    }
}

void selectionSort(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int min = i;
        for (int j = i; j < len; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        if (i != min)
        {
            int tmp = arr[i];
            arr[i] = arr[min];
            arr[min] = tmp;
        }
    }
}

void mergeSort(int a[], int len)
{
    if (len <= 1)
    {
        return;
    }
    int nArr[len];
    int m = len / 2;
    mergeSort(a, m);
    mergeSort(&a[m], len - m);
    int i, j, k;
    for (i = 0, j = m, k = 0; i < m && j < len;)
    {
        if (a[i] < a[j])
        {
            nArr[k++] = a[i++];
        }
        else
        {
            nArr[k++] = a[j++];
        }
    }
    while (i < m)
    {
        nArr[k++] = a[i++];
    }
    while (j < len)
    {
        nArr[k++] = a[j++];
    }
    for (i = 0; i < len; i++)
    {
        a[i] = nArr[i];
    }
}


int partition(int arr[], int low, int high) {
    int pivot = arr[high];    // taking the last element as pivot
    int i = (low - 1);        // Index of smaller element

    for (int j = low; j < high; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot) {
            i++;   // increment index of smaller element
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

/** 
 *      The main function that implements QuickSort  
 *      arr[] --> Array to be sorted,  
 *      low --> Starting index,  
 *      high --> Ending index 
*/
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}



int arr[] = {1, 0, 3, 4, 5, 6, 7, 8, 9, 2};
int len = (int)sizeof(arr) / sizeof(arr[0]);
int main()
{

    quickSort(arr, 0,len-1);
    for (int i = 0; i < len; i++)
        cout << arr[i] << "\t";
    cout << endl;

    return 0;
}
