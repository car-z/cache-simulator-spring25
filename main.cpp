/*
 * Main function which builds and runs the cache simulator based on provided memory trace
 * CSF Assignment 3
 * Caroline Zhao
 * czhao67@jhu.edu
 * Miranda Qing
 * mqing2@jhu.edu
 */

#include <iostream>
#include <string>
#include "cache.h"
#include <sstream>
#include <cmath>
#include <vector>
#include <array>

/*
 * Determines if n is a positive power of 2.
 *
 * Parameters:
 *   n - integer to evaluate
 *
 * Returns:
 *   true if n is a positive power of 2, false otherwise
 */
bool positivePowerOfTwo( int n ) {
  // in number which is power of 2 --> in binary representation only the MSB is set to 1
  // 0b10 & 0b01 = 0b00
  return n > 0 && (n & (n-1)) == 0;
}

/*
 * Determines if input arguments 1-3 are valid, and if number of inputs is valid
 * If not, the appropriate error is written to std:cerr
 *
 * Parameters:
 *   argc - integer identifying how many arguments were passed in on command line
 *   argv - array of C strings where each argument is an individiual string
 *
 * Returns:
 *   true if there are 7 arguments and input arguments 1-3 are valid, false otherwise
 */
bool checkValidInputNumbers( int argc, char ** argv ) {
  if ( argc != 7 ) {
    std::cerr << "Missing input arguments" << std::endl;
    return false;
  }
  if ( !positivePowerOfTwo(std::stoi(argv[1])) ) {
    std::cerr << "Number of sets in a cache must be positive power of 2" << std::endl;
    return false;
  }
  if ( !positivePowerOfTwo(std::stoi(argv[2])) ) {
    std::cerr << "Number of blocks in a set must be positive power of 2" << std::endl;
    return false;
  }
  if ( !positivePowerOfTwo(std::stoi(argv[3])) || std::stoi(argv[3]) < 4 ) {
    std::cerr << "Number of bytes in a block must be positive power of 2 and greater than 4" << std::endl;
    return false;
  }
  return true;
}

/*
 * Determines if input arguments 4-6 are valid, and if so sets the appropriate boolean variable.
 * If not, the appropriate error is written to std:cerr
 *
 * Parameters:
 *   argv - array of C strings where each argument is an individiual string
 *   writeAllocate - boolean reference to variable which denotes whether cache is write-allocate (true) or no-write-allocate (false)
 *   writeBack - boolean reference to variable which denotes whether cache is write-back (true) or write-through (false)
 *   lru - boolean reference to variable which denotes whether cache follows LRU (true) or FIFO (false) as its eviction strategy 
 *
 * Returns:
 *   true if inputs 4-6 are valid, false otherwise
 */
bool checkValidInputString( char **argv, bool& writeAllocate, bool& writeBack, bool& lru ) {
  if ( std::string(argv[4]) == "write-allocate" ) {
    writeAllocate = true; // IF TRUE -> WRITE-ALLOCATE
  } else if ( std::string(argv[4]) != "no-write-allocate") {
    std::cerr << "Invalid input for method to write to memory" << std::endl;
    return false;
  }
  if ( std::string(argv[5]) == "write-back") {
    writeBack = true; //IF TRUE -> WRITE-BACK
  } else if ( std::string(argv[5]) != "write-through") {
    std::cerr << "Invalid input for method to load from memory" << std::endl;
    return false;
  }
  if ( writeBack && !(writeAllocate) ) {
    std::cerr << "write-back and no-write-allocate is not valid" << std::endl;
    return false;
  }
  if ( std::string(argv[6]) == "lru") {
    lru = true; //IF TRUE -> LRU
  } else if ( std::string(argv[6]) != "fifo") {
    std::cerr << "Invalid input for eviction method" << std::endl;
    return false;
  }
  return true;
}

/*
 * Parses lines of input and determines whether or not a load or store is performed.
 * Also calculates the index and tag of the memory address.
 *
 * Parameters:
 *   line - input string to parse for memory trace instructions
 *   load - boolean reference to variable which denotes whether load (true) or store (false) needs to be performed
 *   bytesPerBlock - int specifying the number of bytes per block of memory
 *   numSets - int specifying the number of sets in the virtual cache
 *
 * Returns:
 *   { tag, index } of the memory location of the memory access
 *   {-1, -1} if the memory access is invalid
 */
std::vector<int> processMemoryTrace( std::string line, bool& load, int bytesPerBlock, int numSets ) {
  std::stringstream ss(line);
  char ls;
  std::string strAddress;
  ss >> ls >> strAddress;

  if ( ls == 's') {
      load = false; // LOAD FALSE -> IT IS A STORE
    } else if ( ls != 'l') {
      std::cerr << "Invalid memory access" << std::endl;
      return {-1,-1}; //INDICATING FAILURE
    }
  // reading string hex value into unsigned integer number
  std::stringstream ss2(strAddress);
  unsigned int addressIndex;
  ss2 >> std::hex >> addressIndex;
  // removing offset (leaves index with tag)
  int offset = std::log2(bytesPerBlock);
  addressIndex = addressIndex >> offset;
  int addressWithTag = addressIndex;
  // removing tag (just leaving index)
  int indexBits = std::log2(numSets);
  if (indexBits == 0) {
    addressIndex = 0;
  } else {
    addressIndex = addressIndex << (32 - indexBits);
    addressIndex = addressIndex >> (32 - indexBits);
  }
  return {addressWithTag, (int) addressIndex};
}

/*
 * Handles operations in cache when a load is performed
 *
 * Parameters:
 *   outputs - array of integers where the output counters are stored as elements
 *   cache - reference to Cache object
 *   index - integer representing the index in the cache of the current memory access
 *   tag - integer representing the tag of the current memory access
 *   bytesPerBlock - integer representing the number of bytes per block of memory
 *   lru - boolean specifying the eviction strategy to follow: true -> lru, false -> Fifo
 *   simTime - integer specifying the current simulation time
 *
 */
void handleLoad( std::array<int, 7>& outputs, Cache& cache, int index, int tag, int bytesPerBlock, bool lru, int simTime ) {
  outputs[0]++;

  std::vector<int> indicesHit = cache.indexLoadHit(index, tag);
  if ( indicesHit[1] != -1 ) {
    //LOAD HIT
    outputs[2]++;
    outputs[6]++;
    cache.handleLoadHit(indicesHit[0], indicesHit[1], simTime);
  } else {
    //LOAD MISS
    outputs[3]++;
    outputs[6] += 100*(bytesPerBlock/4);
    outputs[6] = cache.handleLoadMiss(indicesHit[0], index, tag, lru, simTime, outputs[6], bytesPerBlock);
  }
}

/*
 * Handles operations in cache when there is a store hit
 *
 * Parameters:
 *   outputs - array of integers where the output counters are stored as elements
 *   cache - reference to Cache object
 *   writeBack - boolean specifying if cache is write-back (true) or write-through (false)
 *   simTime - integer specifying the current simulation time
 *   indexInSets - integer representing the index of the set the current memory access is accessing
 *   indexInSlots - integer representing the index of the slot in the set that the current memory access is
 *
 */
void handleStoreHit( std::array<int, 7>& outputs, Cache& cache, bool writeBack, int simTime, int indexInSets, int indexInSlots) {
  outputs[4]++;
  outputs[6]++;
  if ( writeBack ) {
    // write-back
    cache.handleWriteBack(indexInSets, indexInSlots, simTime);
    } else {
    // write-through
    outputs[6] += 100;
    cache.handleWriteThrough(indexInSets, indexInSlots, simTime);
  }
}

/*
 * Handles operations in cache when there is a store
 *
 * Parameters:
 *   outputs - array of integers where the output counters are stored as elements
 *   cache - reference to Cache object
 *   index - integer representing the index in the cache of the current memory access
 *   tag - integer representing the tag of the current memory access
 *   bytesPerBlock - integer representing the number of bytes per block of memory
 *   lru - boolean specifying the eviction strategy to follow: true -> lru, false -> Fifo
 *   simTime - integer specifying the current simulation time
 *   writeBack - boolean specifying if cache is write-back (true) or write-through (false)
 *   writeAllocate - boolean specifying if cache is write-allocate (true) or no-write-allocate (false)
 *
 */
void handleStore( std::array<int, 7>& outputs, Cache& cache, int index, int tag, int bytesPerBlock, bool lru, int simTime, bool writeBack, bool writeAllocate ) {
  outputs[1]++;
  std::vector<int> indicesHit = cache.indexLoadHit(index, tag);
  if ( indicesHit[1] != -1 ) {
    handleStoreHit(outputs, cache, writeBack, simTime, indicesHit[0], indicesHit[1]);
  } else {
    //STORE MISS
    outputs[5]++;
    if ( writeAllocate ) {
      outputs[6] += 100*(bytesPerBlock/4);
      outputs[6]++;
      outputs[6] = cache.handleLoadMiss(indicesHit[0], index, tag, lru, simTime, outputs[6], bytesPerBlock);
      if (!writeBack) {
        outputs[6] += 100;
      } else {
        indicesHit = cache.indexLoadHit(index, tag);
        cache.handleStoreMissWriteBack(indicesHit[0], indicesHit[1]);
      }
    } else {
      outputs[6] += 100;
    }
  }
}

/*
 * Main Function which generates a cache simulator with parameters specified by user input
 * then parses a provided memory trace file to simulate memory accesses.
 * Counts of cache operations are printed to the console.
 *
 * Parameters:
 *   argc - integer identifying how many arguments were passed in on command line
 *   argv - array of C strings where each argument is an individiual string
 *
 * Returns:
 *   0 if the cache simulator runs succesfully
 *   1 if the cache simulator throws an error
 */
int main( int argc, char **argv ) {
  if ( !checkValidInputNumbers(argc, argv) ) {
    return 1;
  }
  bool writeAllocate = false; //IF FALSE -> NO-WRITE-ALLOCATE
  bool writeBack = false; //IF FALSE -> WRITE-THROUGH
  bool lru = false; //IF FALSE -> FIFO
  if ( !checkValidInputString(argv,writeAllocate,writeBack,lru) ) {
    return 1;
  }

  int simTime = 0;

  //CACHE PROPERTIES
  int numSets = std::stoi(argv[1]);
  int blocksPerSet = std::stoi(argv[2]);
  int bytesPerBlock = std::stoi(argv[3]);

  // OUTPUTS HELD IN ARRAY
  // outputs = [totalLoads, totalStores, loadHits, loadMisses, storeHits, storeMisses, totalCycles]
  std::array<int, 7> outputs = {0}; 

  Cache cache( numSets, blocksPerSet ); //initializing cache with specified number of sets and slots

  // READING MEMORY TRACE LINE BY LINE
  std::string line;
  while (std::getline(std::cin, line)) {
    bool load = true; //  if (load) --> load; if (!load) --> store

    std::vector<int> addresses = processMemoryTrace(line, load, bytesPerBlock, numSets); // addresses[0] = addressWithTag, addresses[1] = addressIndex
    if ( addresses[0] == -1 ) {
      return 1;
    }

    simTime++;
    if (load) {
      handleLoad(outputs, cache, addresses[1], addresses[0], bytesPerBlock, lru, simTime);
    } else {
      handleStore(outputs, cache, addresses[1], addresses[0], bytesPerBlock, lru, simTime, writeBack, writeAllocate);
    }
  }

  //OUTPUTS
  std::cout << "Total loads: " << outputs[0] << std::endl;
  std::cout << "Total stores: " << outputs[1] << std::endl;
  std::cout << "Load hits: " << outputs[2] << std::endl;
  std::cout << "Load misses: " << outputs[3] << std::endl;
  std::cout << "Store hits: " << outputs[4] << std::endl;
  std::cout << "Store misses: " << outputs[5] << std::endl;
  std::cout << "Total cycles: " << outputs[6] << std::endl;

  return 0;
}