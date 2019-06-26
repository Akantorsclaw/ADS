#ifndef _SORTING_H_
#define _SORTING_H_

#include <vector>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

namespace sorting {
  
  //************
  // QuickSort *
  //************
  void QuickSort(vector<int> &arr, int left, int right);
  int partition(vector<int> &A,int p,int r);

  //************
  // MergeSort *
  //************
  void Merge(vector<int> &a, vector<int> &b,int low, int pivot, int high);
  void MergeSort(vector<int> &a, vector<int> &b, int low, int high);

  //************
  // Heapsort  *
  //************
  void HeapSort(vector<int> &a, int n);
  void percdown(vector<int> &a, int start, int high);
  /*int leftChild(int i);*/
  //************
  // Shellsort *
  //************
  void ShellSort(vector<int> &a, int n);
  int hibbard(int n);
  //*******************
  // Helper functions *
  //*******************
  void randomizeVector(vector<int> &array, int n);
  
 }
#endif 
