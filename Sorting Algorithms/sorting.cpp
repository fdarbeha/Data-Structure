// File:        sorting.cpp
// Author:      Negin Bolkhanian , Fatemeh Darbehani
				
// Date:        2016-02-22
// Description: Skeleton file for sorting functions and helpers
//              


#include <stdlib.h> 
#include <time.h> 

// Selection sort function
// Goes through all the elements and find the smaller elements in ascending order
// Returns the number of barometer operation
template <class T>
int SelectionSort(T arr[], int n)
{
  int count = 0; // counter for barometer operations
  T temp;
  // Find the index of the smallest element
  for(int i = 0; i < n-1; i++)
  {
	  int smallest = i;
	  for(int j = i+1; j < n; j++)
	  {
		  count++;
		  if(arr[j] < arr[smallest])
			  smallest = j;		
	  }
      
	  if(i != smallest)
	    // Swap the smallest with the current item
		Swap( &arr[i], &arr[smallest]);
	} 
  return count;
}


template <class T>
void Swap(T* i, T* j)
{
	T temp;
	temp = *i;
	*i = *j;
	*j = temp;
}
// Quick sort function
// Uses recursive functions and pivots to sort the list in ascending order
// Calls the Quick sort helper
// Returns the number of barometer operation
template <class T>
int Quicksort(T arr[], int n)
{
  int count = 0;
  QuicksortHelper(arr, 0, n - 1, count);
  return count;
}

// Helper function for the Quick sort
// Uses QS partition function for finding the pivot and in fact sorting the data
// Calls itselt recursively with different ranges (smaller) to sort all the partitions
template <class T>
void QuicksortHelper(T arr[], int low, int high, int& counter)
{
  if(low < high){
	  int pivot = QSPartition(arr, low, high, counter);
	  QuicksortHelper(arr, low, pivot - 1, counter);
	  QuicksortHelper(arr, pivot + 1, high, counter);
  }
  else
	  return;
}

// QS partition function
// uses the last data as the assumed pivot in each partitioning
// Then sort the data according to the pivot and then return the index of the next pivot
template <class T>
int QSPartition(T arr[], int low, int high, int& counter)
{
	int pivotindex = high;
	high--;
	if(low >= 0){
	  T pivot = arr[pivotindex];
	  while(low != high){

		while (arr[low] < pivot && low < high)
          {
			counter += 2; // two comparisons
            low++;
          }

		  if(arr[low] < pivot)
			counter += 2;
		  else
			  counter++;

		  while (arr[high] > pivot && high > low)
          {
			counter += 2;
            high--;
		  }
		 if(arr[high] > pivot)
			counter += 2;
		 else
			counter++;

		  if(arr[low] > pivot && arr[high] < pivot)
			  Swap(&arr[low], &arr[high]);
		 
	  }
	  if(arr[low] > pivot){
		Swap(&arr[low], &arr[pivotindex]);
		pivotindex = low;
	  }
	  else if(arr[low] == pivot){
		Swap(&arr[low + 1], &arr[pivotindex]);
		pivotindex = low + 1;
	  }
	}
  return pivotindex;
}

// Randomized Quicksort
//RQuicksort sorts its array parameter using the quicksort
// returns an integer represents the number of times its barometer comparison is made during its execution.
template <class T>
int RQuicksort(T arr[], int n)
{
  int count = 0;
  RQuicksortHelper(arr, 0, n - 1, count);
  return count;
}
//Helper function for Randomized Quicksort
// Uses RQS partition function for finding the pivot and in fact sorting the data
// Calls itselt recursively with different ranges (smaller) to sort all the partitions
template <class T>
void RQuicksortHelper(T arr[], int low, int high, int& counter)
{
  if(low < high){
	  int pivot = RQSPartition(arr, low, high, counter);
	  RQuicksortHelper(arr, low, pivot - 1, counter);
	  RQuicksortHelper(arr, pivot + 1, high, counter);
  }
  else
	  return;
}



//performs a swap of the last element of a subarray with a random element of the subarray
template <class T>
int RQSPartition(T arr[], int low, int high, int& counter)
{
	srand (time(NULL));
	int pivotindex = rand() % (high - low) + low;
	Swap(&arr[pivotindex], &arr[high]);
	pivotindex = high;
	high--;
	if(low >= 0){
	  T pivot = arr[pivotindex];
	  while(low != high){
		  while (arr[low] < pivot && low < high)
          {
			counter+=2;
            low++;
          }
		  if(arr[low] < pivot)
			counter += 2;
		  else
			  counter++;

		  while (arr[high] > pivot && high > low)
          {
			counter+=2;
            high--;
		  }
		  if(arr[high] > pivot)
			counter += 2;
		  else
			  counter++;

		  if(arr[low] > pivot && arr[high] < pivot)
			  Swap(&arr[low], &arr[high]);
	  }
	  if(arr[low] > pivot){
		Swap(&arr[low], &arr[pivotindex]);
		pivotindex = low;
	  }
	  else if(arr[low] == pivot){
		Swap(&arr[low + 1], &arr[pivotindex]);
		pivotindex = low + 1;
	  }
	}
  return pivotindex;
}

// Merge sort function
// Uses merge sort helper function to recursively divide the data into the half until it reaches one data
// Then sorts the data from single element to the whole list in ascending order
// Returns the number of barometer operation
template <class T>
int Mergesort(T arr[], int n)
{
  int count = 0;
  int low = 0, high = n - 1;
  MergesortHelper(arr, low, high, n, count);
  return count;
}

// Megre sort helper function
// Divides the list into the half and recursively calls itself
// When reached to one element calls merge function to start sorting the data 
// Then again calls the merge function for sorting other halves
template <class T>
void MergesortHelper(T arr[], int low, int high, int n, int& counter)
{
	if(low < high)
	{
	  int mid = (high + low) / 2;
	
	  MergesortHelper(arr, low, mid, n, counter);
	  MergesortHelper(arr, mid + 1, high, n, counter);

	  Merge(arr, low, mid, high, n, counter);
	}
}

// Merge function
// Sorts the list in ascending order
// Creats a dynamic array to store the sorted data and then copy this array to the original one
template <class T>
void Merge(T arr[], int low, int mid, int high, int n, int& counter)
{
  int arr1 = low, arr2 = mid + 1, arrTemp = 0;
  T* tempArr = new T[high - low + 1];
  while((arr1 <= mid) && (arr2 <= high)){
          counter+=2;
          if(arr[arr1] < arr[arr2]){
                  tempArr[arrTemp] = arr[arr1];
                  arr1++;
          }
          else{
                  tempArr[arrTemp] = arr[arr2];
                  arr2++; 
          }
		  counter++;
          arrTemp++;
		  
  }
  counter++;

  while(arr1 <= mid){
		  counter++;
          tempArr[arrTemp] = arr[arr1];
          arr1++;
          arrTemp++;
  }
  counter++;
  while(arr2 <= high){
		  counter++;
          tempArr[arrTemp] = arr[arr2];
          arr2++;
          arrTemp++;
  }
   counter++;
  for(int i = low; i < high + 1; i++){
          arr[i] = tempArr[i - low];
 }

  delete[] tempArr;
}

// Shell sort functon
/* https://www.youtube.com/watch?v=M9YCh-ZeC7Y */
template <class T>
int ShellSort(T arr[], int n)
{
  int count = 0;
  int step = n / 2;
  while(step > 0){
	
	  for(int i = 0; i < n - step; i = i + step){
		  count++;
		  int index = i;
		  while(index >= 0 && arr[index]> arr[index + step]){
			  count+=2;
			  Swap(&arr[index], &arr[index + step]);
			  index = index - step;
		  }
		  if(index >= 0 )
			count += 2;
		  else
		    count++;
		  }
	  count++;
	  
	  step = step / 2;
  }

  return count;
}