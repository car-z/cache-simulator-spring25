/*
 * Cache class: function implementations
 * CSF Assignment 3
 * Caroline Zhao
 * czhao67@jhu.edu
 * Miranda Qing
 * mqing2@jhu.edu
 */

#include <vector>
#include "cache.h"
#include <iostream>

Cache::Cache(int numSets, int slotsPerSet) {
    //create numSets sets
    for (int i = 0; i < numSets; i++) {
        //add set to this cache
        sets.push_back(Set(slotsPerSet));
    }
}

// if hit -- returns indices of where slot is located [indexInSets, indexInSlots]
std::vector<int> Cache::indexLoadHit( int index, int tag ) {
    for ( int i = 0; i < (int) sets.size(); i++ ) {
        if ( sets[i].getIndex() == index ) {
            int indexInSlots = sets[i].getSlotIndex(tag);
                // indexInSlots is number if HIT, -1 if MISS
                return {(int) i, indexInSlots};
        }
    }
    // COMPLETE MISS
    return {-1, -1};
}

void Cache::handleLoadHit( int setIndex, int slotIndex, int currentSimTime ) {
    // update the most recent access time for the slot hit with the current sim time
    sets[setIndex].updateSlotAccessTS(slotIndex, currentSimTime);
}

int Cache::checkSetIndex( int indexInSets ) {
    if ( indexInSets == -1 ) {
        indexInSets = 0;        
        for ( int i = 0; i < (int) sets.size(); i++ ) {
            if (sets[i].getIndex() == -1) {
                indexInSets = i;
                break;
            }
        }
    }
    return indexInSets;
}

void Cache::eviction( std::vector<Slot>& slots, bool lru, int indexInSets, int tag, int currentSimTime, int& totalCycles, int bytesPerBlock ) {
    int i = -1;
    if (lru) {
        // LRU - find the slotIndex which has the lowest access time
        i = sets[indexInSets].getLRUSlotIndex();
    } else {
        // FIFO - find the slotIndex which was first loaded 
        i = sets[indexInSets].getOldestSlotIndex();
    }
    slots[i].updateTag(tag);
    slots[i].setLoadTS(currentSimTime);
    slots[i].setAccessTS(currentSimTime);
    if (slots[i].getDirty()) {
        totalCycles += 100*(bytesPerBlock/4);
        slots[i].setDirty(false);
    }
}

int Cache::handleLoadMiss( int indexInSets, int addressIndex, int addressWithTag, bool lru, int currentSimTime, int& totalCycles, int bytesPerBlock) {
    indexInSets = checkSetIndex(indexInSets);
    std::vector<Slot> slots = sets[indexInSets].getSlots();
    bool placed = false;
    for ( int i = 0; i < (int) slots.size(); i++ ) {
        // there is an empty slot
        if ( !(slots[i].getValid()) ) {
            // fill the slot with the loaded tag and current timestamp
            slots[i] = Slot(addressWithTag, currentSimTime);
            slots[i].toggleValid();
            placed = true;
            break;
        }
    }
    // EVICTION STRATEGY
    if ( !placed ) {
        eviction( slots, lru, indexInSets, addressWithTag, currentSimTime, totalCycles, bytesPerBlock);
        placed = true;
    }
    sets[indexInSets].updateSlots(slots);
    sets[indexInSets].updateIndex(addressIndex);
    return totalCycles;
}

void Cache::handleWriteThrough( int setIndex, int slotIndex, int currentSimTime ) {
    // update the most recent access time for the slot hit with the current sim time
    sets[setIndex].updateSlotAccessTS(slotIndex, currentSimTime);
}

void Cache::handleWriteBack( int setIndex, int slotIndex, int currentSimTime ) {
    // update the most recent access time for the slot hit with the current sim time
    sets[setIndex].updateSlotAccessTS(slotIndex, currentSimTime);
    sets[setIndex].isDirty(slotIndex);
}

void Cache::handleStoreMissWriteBack( int setIndex, int slotIndex ) {
    // update dirty tag 
    sets[setIndex].isDirty(slotIndex);
}


void Cache::printCache() {
    std::cout << "[";
    for (int i = 0; i < (int) sets.size(); i++) {
        std::vector<Slot> slots = sets[i].getSlots();
        for ( int j = 0; j < (int) slots.size(); j++ ) {
            std::cout << slots[j].getTag() << " ";
        }
        // comma after each set
        if (i != (int) sets.size() - 1) std::cout << ", "; 
    }
    std::cout << "]" << std::endl;
}


