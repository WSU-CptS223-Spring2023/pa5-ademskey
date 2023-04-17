#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

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
    vector<pair<EntryState, Hash<K,V>>> probVector;

public:
    ProbingHash(int n = 11) 
    {
        probVector.resize(n);
    }

    ~ProbingHash() 
    {
        this->clear();
    }

    bool empty() 
    {
        return tablesize == 0;
    }

    int size() 
    {
        return this -> tablesize;
    }

    V& at(const K& key) {
        throw std::out_of_range("Key not in hash");
    }

    V& operator[](const K& key) //returns value at key key
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
        std::pair<K, V> pair(key, value); //turn passed in variabls into pair

        while(success == false) //while a insertion has not been made
        { 
            int currentPos = hash( pair.first ); //hash key to find position

            if(probVector[currentPos].first == 0))  // if empty index found
                success == true;
                ++currentSize; //incrament the recorded size of vector

            if( probVector[ currentPos ].second != 2 )  // if deleted index found
                ++currentSize; //incrament the recorded size of vector
                success == true;

            if( success == true) //if empty found move into spot
            {            
                probVector[ currentPos ].second = pair;  // copye info into array
                probVector[ currentPos ].first = 1;  // Mark as active
            }
            curentPos++;  //move to next spot (linear hash)
        }
        // rehash
        if( currentSize > probVector.size( ) / 2 )
            rehash( );

        return true;
    }

    void insert(const std::pair<K, V>& pair) 
    {
        bool success = false; //success variable for probing

        while(success == false) //while a insertion has not been made
        { 
            int currentPos = hash( pair.first ); //hash key to find position

            if(probVector[currentPos].first == 0)  // if empty index found
                success == true;
                ++currentSize; //incrament the recorded size of vector

            else if( probVector[ currentPos ].first != 2 )  // if deleted index found
                ++currentSize; //incrament the recorded size of vector
                success == true;

            if( success == true) //if empty found move into spot
            {            
                probVector[ currentPos ].second = pair;  // copye info into array
                probVector[ currentPos ].first = 1;  // Mark as active
            }
            curentPos++;  //move to next spot (linear hash)
        }
        // rehash
        if( currentSize > probVector.size( ) / 2 )
            rehash( );

        return true;
    }

    void erase(const K& key) 
    {
        int currentPos = hash(key); //find index by hashing
        if(( probVector[currentPos].info == 1 ))  //if index is active then mark deleted
            probVector[ currentPos ].first = DELETED;
    }

    void clear() 
    {
        delete probVector;
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
        return 0;       
    }
    
};

#endif //__PROBING_HASH_H
