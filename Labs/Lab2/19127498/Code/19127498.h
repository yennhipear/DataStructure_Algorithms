#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <algorithm>

using namespace std;

void HoanVi(int &a, int &b);

void GenerateRandomData(int a[], int n);

void GenerateSortedData(int a[], int n);

void GenerateReverseData(int a[], int n);

void GenerateNearlySortedData(int a[], int n);

void GenerateData(int a[], int n, int dataType);

/* ************************************************************* */

//SELECTION SORT
void SelectionSort(int a[], int n);

//INSERTION SORT
void InsertionSort(int a[], int n);

//BUBBLE SORT
void BubbleSort(int a[], int n);

//HEAP SORT
void heapify(int a[], int n, int i);
void HeapSort(int a[], int n);

//MERGE SORT
void merge(int a[], int left, int mid, int right);
void MergeSort(int a[], int left, int right);

//QUICK SORT
int partition(int a[], int left, int right);
void QuickSort (int a[], int left, int right);

//RADIX SORT
int getMax(int a[], int n);
void countSort(int a[], int n, int exp);
void RadixSort(int arr[], int n);
