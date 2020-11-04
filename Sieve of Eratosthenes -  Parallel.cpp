// This code is a parallel implementation of the " Sieve of Eratosthenes " Algorithm using OpenMP

#include <bits/stdc++.h>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono; 


int main()
{
  // Set the Size of the Sieve
  long int N;
  
  cout<<"Enter the Size of The Sieve - ";
  cin>>N;
  
  long int* primes; 

  long int square_root = (long int) sqrt((long double)N);
  
  //assign memory for primes
  primes = (long int *)calloc(N, sizeof(long int));
  
  primes[0] = 0;
  primes[1] = 0;
  
  long int i, j;
 
  for (i = 2; i <= N; ++i)
  {	
    primes[i] = 1;
  }

 	//Start Timer
	auto start = high_resolution_clock::now(); 
  
  	//Region of Interest
  	for (i = 2; i < square_root; ++i) 
	{
    	//start parallel execution with default number of threads, use the primes array as a shared resource for all the threads
		#pragma omp parallel for shared(primes)
			for(j = i * i; j <= N; j = j + i) 
			{
      			primes[j] = 0;
    		}
  	
	}		

	//Stop Timer
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    
	
	cout << "Overall Execution Time in (ms) : "<< duration.count()/1000 << "ms" << endl; 	


  	free(primes);

  return 0;
}
