/* File 	: CompareTimes.cpp
 * Author 	: Emil Thomas  
 * Date		: 02/06/2019
 *	
 *	This file compares the running time of insertion sort algorithm and 
 *	std::sort algorithm for sorting integers in a vector.
 *
 *	TODO:
 *		1. Add the code (where ever there is //insert code here )
 *		to time the two functions, std_sort and insertion_sort
 *			
 *		2. Change the #defined N and run this three times each for the 
 *			values below
 *		3. Report the elapsed time for each function in milliseconds
 *
 *	N = 10,000 : std_sort :  1 ms, insertion_sort :   78 ms
 *	N = 20,000 : std_sort :  3 ms, insertion_sort :   316 ms
 *	N = 30,000 : std_sort :  6 ms, insertion_sort :   725 ms
 *
 * ******************************************************************************/


#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm>

#define N 30000 				//Size of the vector

using namespace std;
using namespace std::chrono;	//The stl timer implemntation

/*InsertionSort : SOurce: geekforgeeks*/
void insertion_sort(vector<int> &arr)
{
	long unsigned int i;
	int key, j; 
	for (i = 1; i < arr.size(); i++) 
	{ 
		key = arr[i]; 
		j = i-1; 
				  
		/* Move elements of arr[0..i-1], that are 
		*           greater than key, to one position ahead 
		*                     of their current position */
		while (j >= 0 && arr[j] > key) 
		{ 
			arr[j+1] = arr[j]; 
			j = j-1; 
		} 
	  arr[j+1] = key; 
	}

}

/*Wrapped in a function just to make fair comparison*/
void std_sort(vector<int> &arr)
{
	std::sort(arr.begin(), arr.end());

}

int main()
{
	//Generate a vector of N rand integers 
	auto f = []() {return rand() % RAND_MAX;};
	vector<int> v1(N);
	generate(v1.begin(), v1.end(), f);

	//make a copy
	vector<int> v2{v1};	

	// timing using std::sort
	
	//get the time using steady_clock 
	auto t1 = steady_clock::now();          //insert code here;
	std_sort(v1);
	auto t2 = steady_clock::now();			//insert code here;
	//get the time elapsed using duration_cast
	auto elap = duration_cast<milliseconds>(t2 - t1);		// insert code here;
	cout << "standard::sort :" << elap.count() << " ms" << endl;

	//timing insertionSort 
	t1 = steady_clock::now();				// insert code here;
	insertion_sort(v2);
	t2 = steady_clock::now();				// insert code here;
	elap = duration_cast<milliseconds>(t2 - t1);				// insert code here;
	cout << "insertion_sort :" <<  elap.count() << " ms" << endl;

}
