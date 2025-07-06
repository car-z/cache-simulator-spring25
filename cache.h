/*
 * Header File defining a Cache class defining a Cache object
 * CSF Assignment 3
 * Caroline Zhao
 * czhao67@jhu.edu
 * Miranda Qing
 * mqing2@jhu.edu
 */

#include <vector>
#include "set.h"

class Cache {
private:
	std::vector<Set> sets;

public:
    
    /*
     * Constructor which creates a new Cache object and initializes the vector of Sets
     *
     * Parameters:
     *   numSets - integer for number of sets in the Cache
     *   slotsPerSet - integer for number of slots in each set
     *      
     */
    Cache(int numSets, int slotsPerSet);

    /*
     * function which returns the indices of where the memory access is located in the cache
     *
     * Parameters:
     *   index - integer representing the index in the cache of the current memory access
     *   tag - integer representing the tag of the current memory access
     *      
     * Returns:
     *   a vector where the first value is the index in sets of the corresponding set, 
     *   and the second value is the index of the slot in the corresponding set
     * 
     *   {-1, -1} returned if neither index is found
     */
    std::vector<int> indexLoadHit( int index, int tag);

    /*
     * handles a load hit in cache
     *
     * Parameters:
     *   setIndex - integer representing the index in sets of the current memory access
     *   slotIndex - integer representing the index within the set at sets[setIndex] where the current memory access points to
     *   currentSimTime - integer specifying the current simulation time
     *      
     */
    void handleLoadHit( int setIndex, int slotIndex, int currentSimTime ); 

    /*
     * handles a load miss in cache
     *
     * Parameters:
     *   indexInSets - integer representing the index in sets of the current memory access
     *   addressIndex - integer representing the address index in the cache of the current memory access
     *   addresswithTag - integer representing the tag of the current memory access
     *   lru - boolean specifying the eviction strategy to follow: true -> lru, false -> Fifo
     *   currentSimTime - integer specifying the current simulation time
     *   totalCycles - integer reference specifying the total cycle count of the cache
     *   bytesPerBlock - integer representing the number of bytes per block of memory
     *      
     * Returns:
     *   the total cycle count of the cache
     * 
     */
    int handleLoadMiss( int indexInSets, int addressIndex, int addressWithTag, bool lru, int currentSimTime, int& totalCycles, int bytesPerBlock);

    /*
     * handles writing-through for the cache
     *
     * Parameters:
     *   setIndex - integer representing the index in sets of the current memory access
     *   slotIndex - integer representing the index within the set at sets[setIndex] where the current memory access points to
     *   currentSimTime - integer specifying the current simulation time
     *      
     */
    void handleWriteThrough( int setIndex, int slotIndex, int currentSimTime );

    /*
     * handles writing-back for the cache when it is a store hit
     *
     * Parameters:
     *   setIndex - integer representing the index in sets of the current memory access
     *   slotIndex - integer representing the index within the set at sets[setIndex] where the current memory access points to
     *   currentSimTime - integer specifying the current simulation time
     *      
     */
    void handleWriteBack( int setIndex, int slotIndex, int currentSimTime );

    /*
     * handles a a write-back for the cache when it is a store miss
     *
     * Parameters:
     *   setIndex - integer representing the index in sets of the current memory access
     *   slotIndex - integer representing the index within the set at sets[setIndex] where the current memory access points to
     *      
     */
    void handleStoreMissWriteBack( int setIndex, int slotIndex );

    /*
     * helper function to print the current state of the cache to the console
     */    
    void printCache();

    /*
     * helper function for finding an empty index in sets if indexInSets is not currently valid (never been set before)
     *
     * Parameters:
     *   indexInSets - integer representing the index in sets of the current memory access
     *                 will be -1 if this index has never been set before for this cache
     * 
     * Returns:
     *   an integer pointing to the correct index in sets for which the current memory access maps to
     *      
     */
    int checkSetIndex( int indexInSets );

    /*
     * helper function to handle evicting a block from cache when cache is full based on either LRU or FIFO 
     *
     * Parameters:
     *   slots - reference to a vector of slots from which a block will be evicted 
     *   lru - boolean specifying the eviction strategy to follow: true -> lru, false -> Fifo
     *   indexInSets - integer representing the index of set that the the memory access is trying to access
     *   tag - integer representing the address including the tag of the current memory access
     *   currentSimTime - integer specifying the current simulation time
     *   totalCycles - integer reference specifying the total cycle count of the cache
     *   bytesPerBlock - integer representing the number of bytes per block of memory
     *      
     */
    void eviction( std::vector<Slot>& slots, bool lru, int indexInSets, int tag, int currentSimTime, int& totalCycles, int bytesPerBlock );
};