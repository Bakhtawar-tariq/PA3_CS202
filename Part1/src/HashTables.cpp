#include "HashTables.h"


// =======================
// Constructor
// =======================
template <typename T>
HashTable<T>::HashTable(CollisionHandle strategy)
{
    collision_strategy = strategy;
}

// =======================
// Destructor
// =======================
template <typename T>
HashTable<T>::~HashTable()
{
    if (probing_table != nullptr){
        delete[] probing_table;
        probing_table = nullptr;
    }
}

// =======================
// Load Factor Calculation
// =======================

template <typename T>
void HashTable<T>::resizeAndRehash(){

}


template <typename T>
void HashTable<T>::calculateLoadFactor()
{
    loadFactor = num_elements/table_size;
    resizeAndRehash();
}


// =======================
// Linear Probing Methods
// =======================
template <typename T>
void HashTable<T>::insertLinearProbing(int key, T value)
{
    int pos = hashFunction1(key);
    int start = pos;
    while(!probing_table[pos].isEmpty && probing_table[pos].key != key){
        pos = (pos + 1) % table_size;
        if (pos == start) { //meaning full table
            return; 
        }
    }

    probing_table[pos].value = value;
    probing_table[pos].key = key;
    probing_table[pos].isEmpty = false;

    num_elements++;
    calculateLoadFactor();
    if (loadFactor > loadFactorThreshold){
        resizeAndRehash()
    }
}

template <typename T>
T HashTable<T>::searchLinearProbing(int key)
{
    int pos = hashFunction1(key);
    int start = pos;

    while(!probing_table[pos].isEmpty || probing_table[pos].key != key){
        if(!probing_table[pos].isEmpty && probing_table[pos].key != key){
            return probing_table[pos].value;
        }
        pos = (pos + 1) % table_size;
        if (pos == start) { 
            break; 
        }
    }
    return T();
}

template <typename T>
void HashTable<T>::removeLinearProbing(int key)
{
    int pos = hashFunction1(key);
    int start = pos;

    while(!probing_table[pos].isEmpty || probing_table[pos].key != key){
        if(!probing_table[pos].isEmpty && probing_table[pos].key != key){
            probing_table[pos].isEmpty = true;
            num_elements--;
            calculateLoadFactor();
            return;
        }
        pos = (pos + 1) % table_size;
        if (pos == start) { 
            break; 
        }
    }
    
}

// =======================
// Quadratic Probing Methods
// =======================
template <typename T>
void HashTable<T>::insertQuadraticProbing(int key, T value)
{
    
}

template <typename T>
T HashTable<T>::searchQuadraticProbing(int key)
{
    return T();
}

template <typename T>
void HashTable<T>::removeQuadraticProbing(int key)
{
    
}

// =======================
// Separate Chaining Methods
// =======================
template <typename T>
void HashTable<T>::insertSeparateChaining(int key, T value)
{
    
}

template <typename T>
T HashTable<T>::searchSeparateChaining(int key)
{
    return T();
}

template <typename T>
void HashTable<T>::removeSeparateChaining(int key)
{

}

// =======================
// Insert
// =======================
template <typename T>
void HashTable<T>::insert(int key, T value)
{
    switch (collision_strategy)
    {
        case LINEAR_PROBING:
            insertLinearProbing(key, value);
            break;
        case QUADRATIC_PROBING:
            insertQuadraticProbing(key, value);
            break;
        case SEPARATE_CHAINING:
            insertSeparateChaining(key, value);
            break;
    }
    calculateLoadFactor();
}

// =======================
// Search
// =======================
template <typename T>
T HashTable<T>::search(int key)
{
    switch (collision_strategy)
    {
        case LINEAR_PROBING:
            return searchLinearProbing(key);
        case QUADRATIC_PROBING:
            return searchQuadraticProbing(key);
        case SEPARATE_CHAINING:
            return searchSeparateChaining(key);
    }
    return T(); // Default return
}

// =======================
// Remove
// =======================
template <typename T>
void HashTable<T>::remove(int key)
{
    switch (collision_strategy)
    {
        case LINEAR_PROBING:
            removeLinearProbing(key);
            break;
        case QUADRATIC_PROBING:
            removeQuadraticProbing(key);
            break;
        case SEPARATE_CHAINING:
            removeSeparateChaining(key);
            break;
    }
    calculateLoadFactor();
}

// Please use this for debugging help
template <typename T>
void HashTable<T>::displayProbingTable()
{
    cout << "Current Table (size: " << table_size << "):\n";
    for (int i = 0; i < table_size; i++)
    {
        if (!probing_table[i].isEmpty)
            cout << "[" << i << "] -> Key: " << probing_table[i].key << ", Value: " << probing_table[i].value << endl;
        else
            cout << "[" << i << "] -> EMPTY\n";
    }
}