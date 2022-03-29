#include "19127498.h"

//SELECTION SORT
void SelectionSort(int a[], int n)
{
    int i, j, min_index;
  
    for (i = 0; i < n - 1; i++)
    {
        min_index = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[min_index])
                min_index = j;
        }
  
        swap(a[min_index], a[i]);
    }
}


//INSERTION SORT
void InsertionSort(int a[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;
  
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}


//BUBBLE SORT
void BubbleSort(int a[], int n)
{
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}


//HEAP SORT
void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
    if (left < n && a[left] > a[largest])
        largest = left;
 
    if (right < n && a[right] > a[largest])
        largest = right;
 
    if (largest != i)
    {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void HeapSort(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
 
    for (int i = n - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}


//MERGE SORT
void merge(int a[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
 
    int L[n1], R[n2];
 
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];
 
    int i = 0, j = 0;
    int k = left;
 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int a[], int left, int right)
{
    if(left >= right)
    {
        return;
    }
    int mid = (left + right - 1) / 2;
    MergeSort(a, left, mid);
    MergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
}


//QUICK SORT
int partition(int a[], int left, int right)
{
    int pivot = a[(left + right) / 2];
    int i = left, j = right;

    while (i <= j)
    {
        while (a[i] < pivot)
        {
            i++;
        }
        while (a[j] > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            swap (a[i], a[j]);
            i++;
            j--;
        }
    }
    return i;
}

void QuickSort (int a[], int left, int right)
{
    if (left < right)
    {
        int pi = partition(a, left, right);
        QuickSort(a, left, pi - 1);
        QuickSort(a, pi, right);
    }
}


//RADIX SORT
int getMax(int a[], int n)
{
    int max = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

void countSort(int a[], int n, int exp)
{
    int output[n];
    int i, count[10] = { 0 };
  
    for (i = 0; i < n; i++)
        count[(a[i] / exp) % 10]++;
  
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
  
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }
  
    for (i = 0; i < n; i++)
        a[i] = output[i];
}
  
void RadixSort(int arr[], int n)
{
    int m = getMax(arr, n);
  
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}


int main()
{
    cout << "\t\t\t *** LAP 2 - SORTING *** " << endl;
    
    int size;
    cout << "- Enter size: ";     cin >> size;
    int *a = new int [size];
  
    cout << "- Data Types "            << endl;
    cout << "\t 0. Random Data"        << endl;
    cout << "\t 1. Sorted Data"        << endl;
    cout << "\t 2. Reverse Data"       << endl;
    cout << "\t 3. Nearly Sorted Data" << endl;
    
    int dataType;
    cout << "--> Your data type: ";    cin >> dataType;
    GenerateData(a, size, dataType);

    clock_t start, end;
    
    start = clock();
    
//    SelectionSort(a, size);
    InsertionSort(a, size);
//    BubbleSort(a, size);
//    HeapSort(a, size);
//    MergeSort(a, 0, size - 1);
//    QuickSort(a, 0, size - 1);
//    RadixSort(a, size);
    
    end = clock();
    
    double time_use = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    cout << "\n- It takes " << time_use << " ms to complete. " << endl << endl;
    
    delete []a;
    
    return 0;
}

