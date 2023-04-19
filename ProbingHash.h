#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>
#include <math.h>

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
    }

    ~ProbingHash() 
    {
        this->probVector.clear();
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
        return probVector[hash(key)].second.second; //returns value of pair in second part of vector
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
        int hashPos = hash( key ); //hash key to find position

        // update values to emplace K and V
        probVector[ hashPos ].second = newHash;  // copy info into array
        probVector[ hashPos ].first = VALID;  // Mark as active

        tablesize++;

        // rehash
        if( load_factor() > 0.75 )  // Rehash when the table is 75% full
            rehash( );
    }

    void insert(const std::pair<K, V>& pair) 
    {
        int currentPos = hash( pair.second ); //hash key to find position
      
        probVector[ currentPos ].second.first = pair.first;  // copy info into array
        probVector[ currentPos ].second.second = pair.second;
        probVector[ currentPos ].first = VALID;  // Mark as active

        tablesize++;
        // rehash
        if( load_factor() > 0.75 )  // Rehash when the table is 75% full
            rehash( );
    }

    void erase(const K& key) 
    {
        int currentPos = hash(key); //find index by hashing
        if(( probVector[currentPos].first == VALID ))  //if index is active then mark deleted
        {    
            probVector[ currentPos ].first = DELETED;
        }
    }

    void clear() 
    {
        probVector.clear();
    }

    int bucket_count() 
    {
        return probVector.size();
    }

    int bucket_size(int n) 
    {
        if( probVector[n].first == 1 )
            return 1;
        else
            return 0;
    }

    int bucket(const K& key) 
    {
        if( probVector[ hash(key) ].first == 1 ) //if index is active then return index
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

        // Now we want to create a vector that is the next prime after doubling the current vector size.
        probVector.resize(findNextPrime(2 * oldProbVector.size()));
        
        for (auto & entry : oldProbVector)
        {
            entry.first = EMPTY;  // Make every entry EMPTY
        }

        for (auto & entry : oldProbVector)
        {
            if( entry.first == VALID )
            {
                insert(entry.second);  // Insert every entry from the old array
            }
        }
    }

    void rehash(int n) 
    {

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

        int emptyLocation =  0;
        emptyLocation = key % probVector.size();
        while (probVector[emptyLocation].first != EMPTY)
        {
            emptyLocation++;

            if(emptyLocation >= probVector.size())
                emptyLocation = 0;
        }

        return emptyLocation;
    }
    
};

#endif //__PROBING_HASH_H
