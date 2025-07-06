/*
 * Header file for Slot class defining a Slot Object
 * CSF Assignment 3
 * Caroline Zhao
 * czhao67@jhu.edu
 * Miranda Qing
 * mqing2@jhu.edu
 */

class Slot {
private:
	int tag;
	bool valid, dirty;
	int load_ts, access_ts;

public:
	/*
	 * Default constructor for new Slot object   
	 */
    Slot();
	/*
	 * Non-Default constructor for new Slot object   
	 * Parameters:
	 *   t - integer specifying the unique tag for the slot
	 *   loadTime - integer specifying the simulation time when this Slot was loaded into the cache
	 *
	 */
	Slot( int t, int loadTime );

	/*
     * getter function returning the tag (private field) of the slot 
     *
     * Returns:
     *   the integer tag which uniquely identifies each slot in the set
     * 
     */
	int getTag();

	/*
     * getter function returning the the value of valid (private field)
     *
     * Returns:
     *   boolean value denoting whether or not a slot is filled
     * 
     */
	bool getValid();

	/*
     * getter function returning the the value of dirty (private field)
     *
     * Returns:
     *   boolean value denoting whether or not a slot has been updated without updating memory
     * 
     */
	bool getDirty();

	/*
     * getter function returning the the value of the load time (private field)
     *
     * Returns:
     *   integer value representing the time when the slot was loaded into the cache
     * 
     */
	int getLoadTS();

	/*
     * getter function returning the the value of the access time (private field)
     *
     * Returns:
     *   integer value representing the time when the slot was last accessed
     * 
     */
	int getAccessTS();

	/*
     * setter function to update the unique identifying tag of this slot
     * 
     * Parameters:
     *   t - integer to set as tag
     * 
     */
	void updateTag( int t );

	/*
     * setter function to flip the value of valid
     */
	void toggleValid();	

	/*
     * setter function to set the dirty bit of the slot
     * 
     * Parameters:
     *   d - bool to set as dirty
     * 
     */
	void setDirty( bool d );

	/*
     * setter function to update the load time of this slot
     * 
     * Parameters:
     *   currentSimTime - integer to set as time of loading
     * 
     */
	void setLoadTS( int currentSimTime );

	/*
     * setter function to update the access time of this slot
     * 
     * Parameters:
     *   currentSimTime - integer to set as time of accessing
     * 
     */
	void setAccessTS( int currentSimTime );


};