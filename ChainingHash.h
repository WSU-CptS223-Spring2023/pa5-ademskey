/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <math.h>
#include <algorithm>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

using std::begin;
using std::end;
using std::find;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:

public:
    ChainingHash(int n = 11) 
    {   
        this -> Lists.resize(n);
        this -> currentSize = 0;
    }

    ~ChainingHash() {
        this->clear();
    }

    bool empty() 
    {   
        return this -> currentSize == 0;
    }

    int size() 
    {   
        return this -> currentSize;
    }

    V& at(const K& key) {
        throw std::out_of_range("Key not in hash");
    }

    V& operator[](const K& key) 
    {
        return Lists[hash(key)].front();  
    }

    int count(const K& key) 
    {
        auto & whichList = Lists[hash(key)];  // Get the list
        if (auto itr = find(begin(whichList), end(whichList), key); itr != end(whichList))   // Find the item
            return whichList.size();  // Return the size of the list
        else
            return 0;

    }

    void emplace(K key, V value) 
    {
        auto & whichList = Lists[ key ];      
        if( find( begin( whichList ), end( whichList ), value ) != end( whichList ) )  // If the value is already in the list
            return;

        whichList.push_back( value);
        whichList.push_back( value); // Insert the key
        // Rehash
        if( ++currentSize > Lists.size() )
            rehash( );
    }

    void insert(const std::pair<K, V>& pair) 
    {
        auto & whichList = Lists[ hash( pair.second ) ];      
        if( find( begin( whichList ), end( whichList ), pair.second ) != end( whichList ) )  // If the value is already in the list
            return;

        whichList.push_back( pair.first);

            // Rehash
        if( ++currentSize > Lists.size( ) )
            rehash( );

    }

    void erase(const K& key) 
    {
        auto & whichList = Lists[hash(key)];  // Get the list
        auto itr = find(begin(whichList), end(whichList), key );     // Find the item (iter is an item in a list)

        if( itr != end( whichList )){  // If the item is in the list
            whichList.erase( itr );   // Remove the item
            --currentSize;          // Decrement the size
        }
    }

    void clear() 
    {
        for(auto & thisList : Lists)  // For each list in the table
            thisList.clear();  // Clear the list
        this -> currentSize = 0;
    }

    int bucket_count() //size of hash vector
    {
        int count = 0;
        for (const auto& bucket : Lists)
            count += bucket.size();
        return count;
    }

    int bucket_size(int n) 
    {
        return Lists[n].size();   // Return the size of the list at index n
    }

    int bucket(const K& key) 
    {
        if(!Lists[hash(key)].empty())  // If the list at the index of the key is not empty
            return hash(key);  // Return the index of the list that contains the key
        else
            throw std::out_of_range("Key not in hash");
        return -1;
    }

    float load_factor() 
    {
        return (float)currentSize / this -> bucket_count();
    }

    void rehash() 
    {
        vector<list<V>> oldLists = this -> Lists;  // Create a copy of old table
        std::pair<K, V> insertpair; //declare a pair for isnerting

        // Create new double-sized, empty table
        Lists.resize(findNextPrime(2 * Lists.size()));  // Resize the vector
        for( auto & thisList : this -> Lists)  // Initialize the vector of Lists
            thisList.clear();

        // Copy table over
        this -> currentSize = 0;  // Reset the size
        for(auto & thisList : oldLists)  // For each list in the old table
            for( auto & x : thisList)  // For each item in the list
                insertpair = std::make_pair(hash(x), x);
                insert(insertpair);  // Insert the item
    }
    void rehash(int n) 
    {
        vector<list<V>> oldLists = this -> Lists;  // Create a copy of old table
        std::pair<K, V> insertpair; //declare a pair for isnerting

        // Create new double-sized, empty table
        this -> Lists.resize(n);  // Resize the vector to size passed in
        for( auto & thisList : this -> Lists)  // Initialize the vector of Lists
            thisList.clear();

        // Copy table over
        this -> currentSize = 0;  // Reset the size
        for(auto & thisList : oldLists)  // For each list in the old table
            for( auto & x : thisList)  // For each item in the list
                insertpair = std::make_pair(hash(x), x);
                insert(insertpair);  // Insert the item
    }
    
private:

    vector<list<V>> Lists;   // The array of Lists
    int  currentSize;              // Number of items in the hash table

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

#endif //__CHAINING_HASH_H
