#include "sorting.h"


namespace sorting {

	//************
	// QuickSort *
	//************      
	void QuickSort(vector<int> &arr, int left, int right) {
		
		//***************************
		// implement quicksort here *
		//************ **************
		if (left<right)
		{
			int q = partition(arr, left, right);
			QuickSort(arr, left, q - 1);
			QuickSort(arr, q + 1, right);
		}
	}

	int partition(vector<int>& A, int p, int r)
	{
		int x = A[r];
		int i = p - 1;
		
		for (int j = p; j <= r-1; j++)
		{
			if(A[j] <= x)
			{
				i = i + 1;
				swap(A[i], A[j]);

			}
			

		}
		swap(A[i + 1], A[r]);

		return i + 1;
	}

	//************
	// MergeSort *
	//************

	//***************************
	// implement mergesort here *
	//***************************


	void Merge(vector<int> &a, vector<int> &b, int low, int pivot, int high) 
	{
		int i = low, j = pivot + 1, k = low;

		//copy numbers in right order into tmp array
		while (i <= pivot && j <= high)
		{
			if (a[i] < a[j])
				b[k++] = a[i++];
			else
				b[k++] = a[j++];
		}
		//copy rest if one side is empty
		//right side is empty
		while (i <= pivot)
		{
			b[k++] = a[i++];
		}
		//left side is empty
		while (j <= high)
		{
			b[k++] = a[j++];
		}


		//copy tmp into original
		for (int f = low; f <= high; f++)
		{
			a[f] = b[f];
		}

		return;
		/*int n1 = pivot-low+1;
		int n2 = high - pivot;
		vector <int> L, R;
		L.resize(n1+1);
		R.resize(n2+1);
		for (int i = 1; i < n1; i++)
		{
			L[i] = a[low + i - 1];
		}
		for (int j = 1; j < n2; j++)
		{
			R[j] = a[pivot + j];

		}

		L[n1 + 1] = INFINITY;
		R[n2 + 1] = INFINITY;

		int i = 1;
		int j = 1;

		for (int k = low; k < high; k++)
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
		}*/
	}

	void MergeSort(vector<int> &a, vector<int> &b, int low, int high) 
	{
		int q;
		if (low < high)
		{
			q = (low + high) / 2;
			MergeSort(a, b, low, q);
			MergeSort(a, b, q + 1, high);
			Merge(a, b, low, q, high);
		}
		return;
	}



	//************
	// Heapsort  *
	//************

	void HeapSort(vector<int> &a, int n) {


		//***************************
		// implement heapsort here *
		//***************************
		for (int i = n/2; i >= 0; i--)
		{
			percdown(a, n, i);
		}

		int j = n - 1;
		for (int j= n-1;j >= 0;j--)
		{
			swap(a[0], a[j]);
			percdown(a, j,0);
			
		}
		
	}

	void percdown(vector<int>& a, int size, int index)
	{
		int largest = index;
		int leftChildIndex = 2 * index + 1;
		int rightChildIndex = 2 * index + 2;

		//check if child is available and if it is bigger then index(startpoint)
		if (leftChildIndex < size && a[leftChildIndex] > a[largest])
			largest = leftChildIndex;
		if (rightChildIndex < size && a[rightChildIndex] > a[largest])
			largest = rightChildIndex;

		//if there is a new largest swap it and percdown again to keep the max heap
		if (largest != index)
		{
			swap(a[index], a[largest]);
			percdown(a,size, largest);
		}

		////pos of the "Tree" elements
		//
		//int j = start;
		//int child = start;
		//int tmp = a[start];

		//while (leftChild(j) < high)
		//{
		//	child = leftChild(j);

		//	if ((child != high - 1) && (a[child] > a[child + 1]))
		//		child++;

		//	if (tmp > a[child])
		//	{
		//		swap(a[j], a[child]);
		//		j = child;
		//	}
		//}
	}

	/*int leftChild(int i)
	{
		return 2 * i + 1;
	}*/

	//************
	// Shellsort *
	//************
	void ShellSort(vector<int> &a, int n)
	{

		//***************************
		// implement shellsort here *
		//***************************

		//größtmögliche hibbardzahl < N
		int gap = hibbard(n);

		//wenn gap 0 dann ist alles sortiert(best case)
		while (gap > 0)
		{

			int i = gap;

			//bis zur letzten stelle
			while (i < n)
			{

				int tmp = a[i];
				int j = i;
				//swap
				while (j>= gap && tmp < a[j-gap])
				{
					a[j] = a[j - gap];
					j = j - gap;
				}

				a[j] = tmp;
				i = i + 1;

			}
			//vorherige hibbard zahl
			gap = (gap - 1) / 2;
		}
	}

	int hibbard(int n)
	{

		
		int hib = 0;
		while (hib * 2 + 1 <= n)
			hib = hib * 2 + 1;

		return hib;
	}


  void randomizeVector(vector<int> &array, int n) {
    array.resize(n);

    for(unsigned int i=0;i<array.size();i++)
      array[i]=rand() % 1000000;
  }


}





