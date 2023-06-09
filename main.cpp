
//Disclaimer: Code referenced from texbook for designs of certain functions in the hash tables
//Project developed in collaberation with Fernando Medina and Adam Caudle

/*
(6 pts) How did the serial implementations for the ChainingHash and ProbingHash
compare to each other? Did you expect the time results obtained? Explain.
	The serial implementations for the ChainingHash and ProbingHash were very similar with slightly
	different accessing speeds. The ChainingHash was slightly faster than the ProbingHash in this respect. 
	 The ProbingHash has to check the state of each pair to see if it is valid or not, 
	 while the ChainingHash doestn. This means the insertion as well as acccessing are slightly slower on the 
	 probing hash when brought to this scale.

2. (6 pts) Compare the parallel and serial implementations for the ProbingHash. Did the
parallel implementations provide you with the expected speedup? Explain.
	The parallel implementation of the ProbingHash were much faster than the serial implementation. 
	We expected this because the parallel implementation was able to split the work between the 
	threads and complete the work much faster than the serial implementation. 

3. (6 pts) What could you change in your parallel implementations to improve performance and
speedup? Explain. 
	I could improve my parrallel implementations to improve better performance and speedup by
	making my funciton threadsafe so I would not have to take extra measures such as locks or critical 
	sections. This could improve times in the parralel sections of my code.
*/

//Disclaimer: Code referenced from texbook for designs of certain functions in the hash tables
//Project developed in collaberation with Fernando Medina and Adam Caudle

#include <fstream>
#include "ChainingHash.h"
#include "ProbingHash.h"
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

		int insertval = 2000000;
		
		start_time = omp_get_wtime(); // record start time

		chainingHashTable[2000000]; // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time

		if(insertval > chainingHashTable.size())
		{
			outfile << "chaining search item not in hash" << std::endl; // write the total time to the file
		}
		else
		{
			outfile << "chaining search time: " << total_time << std::endl; // write the total time to the file
		}
		// Remov

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

			    // rehash
            if( ProbingObject.load_factor() >= 0.75 )  // Rehash when the table is 75% full
            {
                ProbingObject.rehash( );
            }
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

		insertval = 2000000;
		
		start_time = omp_get_wtime(); // record start time

		ProbingObject[2000000]; // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time

		if(insertval > ProbingObject.size())
		{
			outfile << "Probing thread search item not in hash" << std::endl; // write the total time to the file
		}
		else
		{
			outfile << "Probing thread search time: " << total_time << std::endl; // write the total time to the file
		}
		// Remov

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

	   	start_time = omp_get_wtime(); // record start time

	   	//#pragma omp parallel for shared(ParallelProbingObject)
			for (int i = 1; i <= 1000000; i++)   //go in a loop through 1 mil
			{
				ParallelProbingObject.insert(pair<int, int>(i, i));  // insert the pair (i, i) into the hash table.
			}

		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time

		// Report the total amount of time, in seconds, required to insert the values to ParallelProbingHash table. Write the results to a file called “HashAnalysis.txt”. 

		outfile << "Parallel Probing 1 thread insertion time: " << total_time << std::endl; // write the total time to the file

		// Search for the value with key 177 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 
		
		start_time = omp_get_wtime(); // record start time
		#pragma omp parallel
		ParallelProbingObject[177]; // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time

		outfile << "Parallel Probing 1 thread search time: " << total_time << std::endl; // write the total time to the file

		// Search for the value with key 2,000,000 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the file.  

		insertval = 2000000;
		
		start_time = omp_get_wtime(); // record start time

		ParallelProbingObject[2000000]; // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time

		if(insertval > ParallelProbingObject.size())
		{
			outfile << "Parallel Probing thread search item not in hash" << std::endl; // write the total time to the file
		}
		// else
		// {
		// 	outfile << "Parallel Probing thread search time: " << total_time << std::endl; // write the total time to the file
		// }
		// Remov

		//outfile << "Parallel Probing 1 thread search time: " << total_time << std::endl; // write the total time to the file
		// Remove the value with key 177 from ParallelProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

		start_time = omp_get_wtime(); // record start time
		#pragma omp parallel
		ParallelProbingObject.erase(177); // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time

		outfile << "Parallel Probing 1 thread delete time: " << total_time << std::endl; // write the total time to the file

		// Also, write to the file the final size, bucket count, and load factor of the hash for ParallelProbingHash table. 

		outfile << "Table size: " << ParallelProbingObject.size() << std::endl; // write the size to the file
		outfile << "Bucket count: " << ParallelProbingObject.bucket_count() << std::endl; // write the bucket count to the file
		outfile << "Load factor: " << ParallelProbingObject.load_factor() << std::endl;

	// (b) Using multiple threads:  
		//  create an object of type ParallelProbingHash 

		ProbingHash<int, int> ParallelProbingObject2;
		//300,000
		//ParallelProbingObject2.rehash(500000);

		// i.	Change the number of threads togit match the number of cores on your system 

		omp_set_num_threads(NUM_THREADS);

		/* In an OpenMP parallel region (#pragma omp parallel), in order, insert values with keys 1 – 1,000,000. 
		Inside the parallel region make sure that the value for the iteration number of the loop is shared among all threads. 
		For simplicity, the key and value stored are the same.
        */
		
		//std::cout << "First Size: " << ParallelProbingObject2.bucket_count() << std::endl;
		
		start_time = omp_get_wtime(); // record start time

		//#pragma omp parallel
		// Fuctions in ProbingHash.h are parrallized individually. This is because our insert function
		// does not like like being accessed by more than one core at a time. This is because multiple cores
		// try to rehash at the same time. This causes seg fault errors and does not work. We did parrallelize
		// Rehash(), Search(), and deleted, also some sections of insert.
		for (int i = 1; i <= 1000000; i++) 
		{
			ParallelProbingObject2.insert(pair<int, int>(i, i));
		}

		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time

		// Report the total amount of time, in seconds, required to insert the values to ParallelProbingHash table. Write the results to a file called “HashAnalysis.txt”. 

		outfile << "Parallel Probing 4 thread insertion time: " << total_time << std::endl; // write the total time to the file

		// Search for the value with key 177 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the “HashAnalysis.txt” file. 
		
		start_time = omp_get_wtime(); // record start time
		#pragma omp parallel
		ParallelProbingObject2[177]; // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time

		outfile << "Parallel Probing 4 thread search time: " << total_time << std::endl; // write the total time to the file

		// Search for the value with key 2,000,000 in ParallelProbingHash table. Report the time required to find the value in each table by writing it to the file.  

		insertval = 2000000;
		
		start_time = omp_get_wtime(); // record start time
		#pragma omp parallel
		ParallelProbingObject2[2000000]; // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time

		if(insertval > ParallelProbingObject2.size())
		{
			outfile << "Parallel Probing 4 thread search item not in hash" << std::endl; // write the total time to the file
		}
		else
		{
			outfile << "Parallel Probing 4 thread search time: " << total_time << std::endl; // write the total time to the file
		}
		// Remove the value with key 177 from ParallelProbingHash table. Report the time required to remove the value with in each table by writing it to the file.  

		start_time = omp_get_wtime(); // record start time
		ParallelProbingObject2.erase(177); // search for the value with key 177
		end_time = omp_get_wtime(); // record end time
		total_time = end_time - start_time; // calculate total time

		outfile << "Parallel Probing 4 thread delete time: " << total_time << std::endl; // write the total time to the file

		// Also, write to the file the final size, bucket count, and load factor of the hash for ParallelProbingHash table. 

		outfile << "Table size: " << ParallelProbingObject2.size() << std::endl; // write the size to the file
		outfile << "Bucket count: " << ParallelProbingObject2.bucket_count() << std::endl; // write the bucket count to the file
		outfile << "Load factor: " << ParallelProbingObject2.load_factor() << std::endl; // write the load factor to the file
		
	outfile.close(); // close the file
	return 0;
}