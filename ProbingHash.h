#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>
#include <math.h>
#include <omp.h>
#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> { // derived from Hash
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion
    int tablesize;
    vector<pair<EntryState, pair<K,V>>> probVector;

public:
    ProbingHash(int n = 101)
    {
        probVector.resize(n);
        this -> tablesize = 0;
        for (int i = 0; i < n; i++)
        {
            this->probVector[i].first = EMPTY;
        }
    }

    ~ProbingHash() 
    {
        this->probVector.clear();
        // vector destructor will delete all elements
    }

    bool empty() 
    {
        return tablesize == 0;
    }

    int size() 
    {
        return this->tablesize;
    }

    V& at(const K& key) {
        throw std::out_of_range("Key not in hash");
    }

    V& operator[](const K& key) //returns value at key
    {   //vector<pair<EntryState, Hash<K,V>>>

        int keyPos = hash(key);
        int currentPos = keyPos;

        #pragma omp parallel for shared(probVector)
        for (int i = 0; i < probVector.size(); i++)
        {
            if (probVector[currentPos].second.second != key)
            {
                currentPos++;
                if(currentPos >= probVector.size()){
                    currentPos = 0;
                }
            }
            
            if (probVector[currentPos].second.second == key)
                keyPos = currentPos;
        }

        if(probVector[keyPos].second.second != key)
        {
            cout << "key not in hash" << endl;
            //throw std::out_of_range("Key not in hash");
        } 
        else
            return probVector[keyPos].second.second; //returns value of pair in second part of vector
    }

    int count(const K& key) 
    {
        if( probVector[ hash(key) ].first == VALID )
            return 1;
        else
            return 0;
    }

    void emplace(K key, V value)
    {
        bool success = false; //success variable for probing
        pair<K, V> newHash = {key, value}; //turn passed in variabls into pair
        int currentPos = hash( key ); //hash key to find position
      
        #pragma omp critical
        {
            while (probVector[currentPos].first != EMPTY)
            {
                currentPos++;
                if(currentPos >= probVector.size()){
                    currentPos = 0;
                }
            }
        
            probVector[ currentPos ].second.first = key;  // copy info into array
            probVector[ currentPos ].second.second = value;
            probVector[ currentPos ].first = VALID;  // Mark as active

            tablesize++;
            // rehash
            if( load_factor() >= 0.75 )  // Rehash when the table is 75% full
            {
                rehash( );
            }
        }
    }

    void erase(const K& key) 
    {
        int currentPos = hash(key); //find index by hashing
        if(( probVector[currentPos].first == VALID ))  //if index is active then mark deleted
        {    
            probVector[ currentPos ].first = DELETED;
        }
    }

    void insert(const std::pair<K, V>& input) 
    {

        int currentPos = hash( input.first ); //hash key to find position

        #pragma omp parallel
        {
        while (probVector[currentPos].first != EMPTY)
        {
            currentPos++;
            if(currentPos >= probVector.size()){
                currentPos = 0;
            }
        }
        }

        probVector[ currentPos ].second.first = input.first;  // copy info into array
        probVector[ currentPos ].second.second = input.second;
        probVector[ currentPos ].first = VALID;  // Mark as active

        tablesize++;

        if( load_factor() >= 0.75 )  // Rehash when the table is 75% full
        {
            rehash( );
        }
    }

    void clear() 
    {
        probVector.clear();
    }

    int bucket_count() 
    {
        if( probVector.size() == 0 )
            return 0;
        else    
            return probVector.size();
    }

    int bucket_size(int n) 
    {
        if( probVector[n].first == VALID )
            return 1;
        else
            return 0;
    }

    int bucket(const K& key) 
    {
        if( probVector[ hash(key) ].first == VALID ) //if index is active then return index
            return hash(key);
        else
            throw std::out_of_range("Key not in hash");  //else throw error
    }

    float load_factor() 
    {
        return (float)(this -> tablesize) / this -> bucket_count();
    }

    void rehash() 
    {
    vector<pair<EntryState, pair<K,V>>> oldProbVector = probVector;
    probVector.clear();

    // Now we want to create a vector that is the next prime after doubling the current vector size.
    probVector.resize(findNextPrime(2 * oldProbVector.size()));
    
    #pragma omp parallel for shared(oldProbVector)
    for (auto & entry : oldProbVector)  // Go through all of the old entries and place them in a good spot
    {  
        if( entry.first == DELETED )    // If there was an entry that was deleted then we need to bring down the tablesize
        {
            this->tablesize--;
        }

        if( entry.first == VALID )  // Insert everyactive entry from the old array
        {
            int currentPos = entry.second.second;
            currentPos = hash(currentPos);

            // Find first open bucket after inital hash
            while (probVector[currentPos].first != EMPTY)
            {
                currentPos++;
                if(currentPos >= probVector.size()){
                    currentPos = 0;
                }
            }
            
            // insert values
            probVector[currentPos].first = VALID;
            probVector[currentPos].second.first = entry.second.first;
            probVector[currentPos].second.second = entry.second.second;
        }    
    }
    }

    void rehash(int n) 
    {
        vector<pair<EntryState, pair<K,V>>> oldProbVector = probVector;

        // Now we want to create a vector that is the next prime after doubling the current vector size.
        probVector.resize(n);
        
        #pragma omp parallel for shared(oldProbVector)
        for (auto & entry : oldProbVector)  // Go through all of the old entries and place them in a good spot
        {  
            if( entry.first == DELETED )    // If there was an entry that was deleted then we need to bring down the tablesize
            {
                this->tablesize--;
            }

            if( entry.first == VALID )  // Insert everyactive entry from the old array
            {
                int currentPos = entry.second.second;
                currentPos = currentPos % probVector.size();

                // Find first open bucket linearly
                while (probVector[currentPos].first != EMPTY)
                {
                    currentPos++;
                    if(currentPos >= probVector.size()){
                        currentPos = 0;
                    }
                }
                
                // insert at first open bucket
                probVector[currentPos].first = VALID;
                probVector[currentPos].second.first = entry.second.first;
                probVector[currentPos].second.second = entry.second.second;
            }    
        }
    }

private:

    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {

    std::hash<K> hashFunction;
    size_t hashValue = hashFunction(key);
    return static_cast<int>(hashValue % probVector.size());

    }
};

#endif //__PROBING_HASH_H
