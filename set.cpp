/*
 * Set class: function implementations
 * CSF Assignment 3
 * Caroline Zhao
 * czhao67@jhu.edu
 * Miranda Qing
 * mqing2@jhu.edu
 */

#include <vector>
#include "set.h"

Set::Set(int slotsPerSet) {
    //create slotsPerSet slots in each set
    for (int j = 0; j < slotsPerSet; j++) {
        slots.push_back(Slot());
    }
    index = -1;
}

int Set::getIndex() {
    return index;
}

// find index in slots of slot with matching tag
int Set::getSlotIndex( int tag ) {
    for ( int i = 0; i < (int) slots.size(); i++ ) {
        if ( slots[i].getTag() == tag ) {
            return i;
        }
    }
    return -1; // NO MATCHING SLOT
}

// find index in slots of slot with least recent access time (LRU)
int Set::getLRUSlotIndex() {
    int leastRecentIndex = 0;
    for ( int i = 0; i < (int) slots.size(); i++ ) {
        if ( slots[i].getAccessTS() < slots[leastRecentIndex].getAccessTS() ) {
            leastRecentIndex = i;
        }
    }
    return leastRecentIndex;
}

// find index in slots of slot that has been in cache the longest (FIFO)
int Set::getOldestSlotIndex() {
    int oldestSlotIndex = 0;
    for ( int i = 0; i < (int) slots.size(); i++ ) {
        if ( slots[i].getLoadTS() < slots[oldestSlotIndex].getLoadTS() ) {
            oldestSlotIndex = i;
        }
    }
    return oldestSlotIndex;
}

std::vector<Slot> Set::getSlots() {
    return slots;
}

void Set::updateIndex( int i ) {
    index = i;
}

void Set::updateSlots( std::vector<Slot> newSlots ) {
    slots = newSlots;
}

void Set::updateSlotAccessTS( int slotIndex, int currentSimTime ) {
    slots[slotIndex].setAccessTS(currentSimTime);
}

void Set::isDirty( int slotIndex ) {
    slots[slotIndex].setDirty( true );
}
