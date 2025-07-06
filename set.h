/*
 * Header file for Set class defining a Set Object 
 * CSF Assignment 3
 * Caroline Zhao
 * czhao67@jhu.edu
 * Miranda Qing
 * mqing2@jhu.edu
 */

#include <vector>
#include "slot.h"

class Set {
private:
    int index;
	std::vector<Slot> slots;

public:
    /*
     * Constructor which creates a new Set object and initializes the vector of slots
     *
     * Parameters:
     *   slotsPerSet - integer denoting number of slots in each set
     *      
     */
    Set(int slotsPerSet);

    /*
     * getter function returning the index (private field) of the set 
     *
     * Returns:
     *   the integer index which uniquely identifies each set in the cache
     * 
     */
    int getIndex();

    /*
     * function to find a specific index position in slots 
     * 
     * Parameters:
     *   tag - integer memory address with tag included of memory address to find index position of in slots
     *
     * Returns:
     *   the integer index position of tag in slots
     * 
     */
    int getSlotIndex( int tag );

    /*
     * function to find index in slots of memory address with least recent access time
     * 
     * Returns:
     *   the integer index position of the LRU memory address in slots
     * 
     */
    int getLRUSlotIndex();

    /*
     * function to find index in slots of memory address with oldest load time
     * 
     * Returns:
     *   the integer index position of the lecent recently loaded memory address in slots
     * 
     */
    int getOldestSlotIndex();

    /*
     * getter function to return slots (private field)
     * 
     * Returns:
     *   vector of Slot objects
     * 
     */
    std::vector<Slot> getSlots();

    /*
     * setter function to update the unique identifying index of this set
     * 
     * Parameters:
     *   i - integer to set as index
     * 
     */
    void updateIndex( int i );

    /*
     * setter function to update slots (private field)
     * 
     * Parameters:
     *   newSlots - vector of Slot Objects to set as slots
     * 
     */
    void updateSlots( std::vector<Slot> newSlots );

    /*
     * helper function to update the access time of the specified slot
     * 
     * Parameters:
     *   slotIndex - integer index position of the desired slot in slots
     *   currentSimTime - integer time to update the access time to
     * 
     */
    void updateSlotAccessTS( int slotIndex, int currentSimTime );

    /*
     * helper function to set the dirty bit of the specified slot to true
     * 
     * Parameters:
     *   slotIndex - integer index position of the desired slot in slots
     * 
     */
    void isDirty( int slotIndex );


};