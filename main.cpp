// Fernando Medina
// Testing pushing and committing to Adam's repo


//Disclaimer: Code referenced from texbook for designs of certain functions in the hash tables
//Project developed in collaberation with Fernando Medina and Adam Caudle

#include <fstream>
#include "ChainingHash.h"
#include "ProbingHash.h"
//#include "ParallelProbingHash.h" 
#include <omp.h>

#define NUM_THREADS 4  // update this value with the number of cores in your system. 

int main()
{
	/*Task I (a)- ChainingHash table*/

		//  create an object of type ChainingHash 
		ChainingHash<int, int> chainingHashTable(101);

		// In order, insert values with keys 1 – 1,000,000. For simplicity, the key and value stored are the same. 

		double start_time = omp_get_wtime(); // record start time

		for (int i = 1; i <= 1000000; i++)   //go in a loop through 1 mil
		{
			chainingHashTable.insert(pair<int, int>(i, i));  // insert the pair (i, i) into the hash table.
		}

		double end_time = omp_get_wtime(); // record end time
		double total_time = end_time - start_time; // calculate total time

		// Report the total amount of time, in seconds, required to insert the values to ChainingHash table. Write the results to a file called “HashAnalysis.txt”. 

		std::ofstream outfile; // create an output file stream object
		outfile.open("HashAnalysis.txt"); // open the file for appending
		outfile << "Chaining insertion time: " << total_time << std::endl; // write the total time to the file

		// Search for the value with key 177 in ChainingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 

		start_time = omp_get_wtime(); // record start time
		chainingHashTable[177]; // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time
		outfile << "Chaining search time: " << total_time << std::endl; // write the total time to the file

		// Search for the value with key 2,000,000 in ChainingHash table. Report the time required to find the value in each table by writing it to the file.  

		start_time = omp_get_wtime(); // record start time
		chainingHashTable[2000000]; // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time
		outfile << "Chaining search time: " << total_time << std::endl; // write the total time to the file

		// Remove the value with key 177 from ChainingHash table. Report the time required to remove the value with in each table by writing it to the file.  

		start_time = omp_get_wtime(); // record start time
		chainingHashTable.erase(177); // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time
		outfile << "Chaining delete time: " << total_time << std::endl; // write the total time to the file

		//write to the file the final size, bucket count, and load factor of the hash for ChainingHash table. 

		outfile << "Table size: " << chainingHashTable.size() << std::endl; // write the size to the file
		outfile << "Bucket count: " << chainingHashTable.bucket_count() << std::endl; // write the bucket count to the file
		outfile << "Load factor: " << chainingHashTable.load_factor() << std::endl; // write the load factor to the file

	/*Task I (b) - ProbingHash table (using Linear Probing) */

		//  create an object of type ProbingHash 
		ProbingHash<int, int> ProbingObject;

		// In order, insert values with keys 1 – 1,000,000. For simplicity, the key and value stored are the same.
		start_time = omp_get_wtime(); // record start time

		for (int i = 1; i <= 1000000; i++)   //go in a loop through 1 mil
		{
			ProbingObject.insert(pair<int, int>(i, i));  // insert the pair (i, i) into the hash table.
		}

		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time

		// Report the total amount of time, in seconds, required to insert the values to ProbingHash table. Write the results to a file called “HashAnalysis.txt”. 

		outfile << "Probing insertion time: " << total_time << std::endl; // write the total time to the file

		// Search for the value with key 177 in ProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 
		
		start_time = omp_get_wtime(); // record start time
		ProbingObject[177]; // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time
		outfile << "Probing search time: " << total_time << std::endl; // write the total time to the file

		// Search for the value with key 2,000,000 in ProbingHash table. Report the time required to find the value in each table by writing it to the file.  

		start_time = omp_get_wtime(); // record start time
		ProbingObject[2000000]; // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time
		outfile << "Probing search time: " << total_time << std::endl; // write the total time to the file

		// Remove the value with key 177 from ProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

		start_time = omp_get_wtime(); // record start time
		ProbingObject.erase(177); // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time
		outfile << "Probing delete time: " << total_time << std::endl; // write the total time to the file

		// Also, write to the file the final size, bucket count, and load factor of the hash for ProbingHash table. 


		outfile << "Table size: " << ProbingObject.size() << std::endl; // write the size to the file
		outfile << "Bucket count: " << ProbingObject.bucket_count() << std::endl; // write the bucket count to the file
		outfile << "Load factor: " << ProbingObject.load_factor() << std::endl; // write the load factor to the file

	
	/*Task II -  ParallelProbingHash table (using Linear Probing) */
      
	  // (a) Using a single thread:  
		//  create an object of type ParallelProbingHash 
		ProbingHash<int, int> ParallelProbingObject;

		// Set the number of threads (omp_set_num_threads()) to 1 

		omp_set_num_threads(1);

		/* In an OpenMP parallel region (#pragma omp parallel), in order, insert values with keys 1 – 1,000,000. 
		Inside the parallel region make sure that the value for the iteration number of the loop is shared among all threads. 
		For simplicity, the key and value stored are the same.
        */
		// Report the total amount of time, in seconds, required to insert the values to ParallelProbingHash table. Write the results to a file called “HashAnalysis.txt”. 

		// Search for the value with key 177 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 
		
		// Search for the value with key 2,000,000 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the file.  

		// Remove the value with key 177 from ParallelProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

		// Also, write to the file the final size, bucket count, and load factor of the hash for ParallelProbingHash table. 



	// (b) Using multiple threads:  
		//  create an object of type ParallelProbingHash 

		ProbingHash<int, int> ParallelProbingObject2;
		// i.	Change the number of threads to match the number of cores on your system 

		omp_set_num_threads(NUM_THREADS);

		/* In an OpenMP parallel region (#pragma omp parallel), in order, insert values with keys 1 – 1,000,000. 
		Inside the parallel region make sure that the value for the iteration number of the loop is shared among all threads. 
		For simplicity, the key and value stored are the same.
        */
		// Report the total amount of time, in seconds, required to insert the values to ParallelProbingHash table. Write the results to a file called “HashAnalysis.txt”. 

		// Search for the value with key 177 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 
		
		// Search for the value with key 2,000,000 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the file.  

		// Remove the value with key 177 from ParallelProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

		// Also, write to the file the final size, bucket count, and load factor of the hash for ParallelProbingHash table. 

		/* Example output template:
			Parallel Probing insertion time: 
			Parallel Probing search time: 
			Parallel Probing failed search time: 
			Parallel Probing deletion time: 
			Table size: 
			Bucket count: 
			Load factor: 
		*/
	outfile.close(); // close the file
	return 0;
}