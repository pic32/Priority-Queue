/*
	Date: April 19, 2011
	File Name: PriorityQueue.h
	Version: 1.02
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file allows the user to utilize the PRIORITY_QUEUE data
	structure.  It provides all necessary method headers for 
	accessing the Priority Queue library.  The library is configurable
	with the use of PriorityQueueConfig.h.  This file must be included
	in every file that references the Priority Queue library or
	PRIORITY_QUEUE data structure.

	All methods are callable to the user.
*/

/*! \mainpage Priority Queue Library
 *  \brief This is a Library written in C for manipulating a Priority Queue Data Structure.
 *  \author brodie
 *  \version 1.02
 *  \date   April 19, 2011
 */

#ifndef PRIORITY_QUEUE_H
	#define PRIORITY_QUEUE_H

#include "GenericTypes.h"
#include "PriorityQueueObject.h"
#include "PriorityQueueConfig.h"

/*
	Function: PRIORITY_QUEUE *CreatePriorityQueue(PRIORITY_QUEUE *PriorityQueue, INT32(*CompareTo)(const void *Data1, const void *Data2), void (*CustomFreeMethod)(void *Data))

	Parameters: 
		PRIORITY_QUEUE *PriorityQueue - The address at which the PRIORITY_QUEUE will be inititalized.
		If NULL is passed in then this method will create a PRIORITY_QUEUE out of a
		the heap with a call to PQueueMemAlloc()(User Supplied Define).

		INT32(*CompareTo)(const void *Data1, const void *Data2) - A pointer to the method that the
		PRIORITY_QUEUE will use to compare 2 sets of data.  Essentially the easiest way to implement the CompareTo
		is to perform something equal to the following, return Data1 - Data2.  If Data1 is larger than Data2 return
		a value > 0, if they're equal return 0, else return a value < 0.

		void(*CustomFreeMethod)(void *Data) - A pointer to a method that the
		user defines.  Each time a PRIORITY_QUEUE_NODE is deleted this method will
		be called to delete the data at the PRIORITY_QUEUE_NODE.

	Returns:
		PRIORITY_QUEUE* - The address at which the newly initialized PRIORITY_QUEUE resides
		in memory.  If a new PRIORITY_QUEUE could not be created then (PRIORITY_QUEUE*)NULL is returned.

	Description: Creates a new PRIORITY_QUEUE in memory.

	Notes: None
*/
/**
		* @brief Initializes a PRIORITY_QUEUE, and can create a PRIORITY_QUEUE.
		* @param *PriorityQueue - A pointer to an already allocate PRIORITY_QUEUE or a NULL referenced PRIORITY_QUEUE
		pointer to create a PRIORITY_QUEUE from PQueueMemAlloc().
		* @param *CustomFreeMethod - A method called by the PRIORITY_QUEUE Library to delete
		a piece of data that a PRIORITY_QUEUE_NODE points to.
		* @return *PRIORITY_QUEUE - The address of the PRIORITY_QUEUE in memory.  If a PRIORITY_QUEUE could
		not be allocated, returns a NULL PRIORITY_QUEUE pointer.
		* @note None
		* @sa PQueueMemAlloc()
		* @since v1.0
*/
PRIORITY_QUEUE *CreatePriorityQueue(PRIORITY_QUEUE *PriorityQueue, INT32(*CompareTo)(const void *Data1, const void *Data2), void (*CustomFreeMethod)(void *Data));

/*
	Function: BOOL PriorityQueueAdd(PRIORITY_QUEUE *PriorityQueue, const void *Data)

	Parameters: 
		PRIORITY_QUEUE *PriorityQueue - The address of the PRIORITY_QUEUE that will have the data added to it.

		const void *Data - A pointer to the data that will be added to the PRIORITY_QUEUE.

	Returns:
		BOOL - TRUE if the operation was successful, FALSE otherwise.

	Description: Adds a new reference of data to the PRIORITY_QUEUE based on the CompareTo method
	of the PRIORITY_QUEUE.

	Notes: A duplicate set of data will be added after the original set of data.
*/
/**
		* @brief Adds a new reference of data to the specified PRIORITY_QUEUE.
		* @param *PriorityQueue - A pointer to an already allocate PRIORITY_QUEUE or a NULL referenced PRIORITY_QUEUE
		pointer to create a PRIORITY_QUEUE from PQueueMemAlloc().
		* @param *Data - The address of the data that will be added to the PRIORITY_QUEUE.
		* @return BOOL - TRUE if the operation was successful, FALSE otherwise.
		* @note A duplicate set of data will be added after the original set of data.
		* @sa PQueueMemAlloc()
		* @since v1.0
*/
BOOL PriorityQueueAdd(PRIORITY_QUEUE *PriorityQueue, const void *Data);

/*
	Function: void *PriorityQueueRemove(PRIORITY_QUEUE *PriorityQueue)

	Parameters: 
		PRIORITY_QUEUE *PriorityQueue - The address of the PRIORITY_QUEUE that will have the data removed from it.

	Returns:
		*void - The address of the data located at the head of the specified PRIORITY_QUEUE, (void*)NULL otherwise.

	Description: Removes the next piece of data from the PRIORITY_QUEUE.

	Notes: None
*/
/**
		* @brief Removes the next piece of data from a PRIORITY_QUEUE.
		* @param *PriorityQueue - The address of the PRIORITY_QUEUE that will have the data removed from it.
		* @return *void - The address of the data located at the head of the specified PRIORITY_QUEUE, (void*)NULL otherwise.
		* @note This method calls PQueueMemDealloc() to remove from memory the node in the PRIORITY_QUEUE pointing to the data.
		* @sa PQueueMemDealloc()
		* @since v1.0
*/
void *PriorityQueueRemove(PRIORITY_QUEUE *PriorityQueue);

/*
	Function: void *PriorityQueuePeek(PRIORITY_QUEUE *PriorityQueue)

	Parameters: 
		PRIORITY_QUEUE *PriorityQueue - The address of the PRIORITY_QUEUE that will have the data peeked at.

	Returns:
		*void - The address of the data located at the head of the specified PRIORITY_QUEUE, without removing the data.
		(void*)NULL otherwise.

	Description: Peeks at the next piece of data from the PRIORITY_QUEUE, but does not remove it.

	Notes: None
*/
/**
		* @brief Peeks at the next piece of data from a PRIORITY_QUEUE.
		* @param *PriorityQueue - The address of the PRIORITY_QUEUE that will have the data peeked at.
		* @return *void - The address of the data located at the head of the specified PRIORITY_QUEUE, (void*)NULL otherwise.
		* @note This method will not remove the data located at the head of the PRIORITY_QUEUE.
		* @sa None
		* @since v1.0
*/
#if (USING_PRIORITY_QUEUE_PEEK_METHOD == 1)
	void *PriorityQueuePeek(PRIORITY_QUEUE *PriorityQueue);
#endif // end of USING_PRIORITY_QUEUE_PEEK_METHOD

/*
	Function: BOOL PriorityQueueClear(PRIORITY_QUEUE *PriorityQueue)

	Parameters: 
		PRIORITY_QUEUE *PriorityQueue - The address of the PRIORITY_QUEUE that will be cleared of all data.

	Returns:
		BOOL - TRUE if the PRIORITY_QUEUE was either empty or empited successfully.  Returns (BOOL)FALSE otherwise.

	Description: Clears all data inside the PRIORITY_QUEUE, and sets the size back to 0.  Will free data with user
	supplied method when PRIORITY_QUEUE was created.

	Notes: None
*/
/**
		* @brief Clears all data from a PRIORITY_QUEUE.
		* @param *PriorityQueue - The address of the PRIORITY_QUEUE that will have the data cleared from it.
		* @param DefaultFree - Set this to (BOOL)TRUE if the data at each node can be deleted with the PQueueMemDealloc() method.  
		Otherwise put this variable to (BOOL)FALSE.
		* @return BOOL - Returns (BOOL)TRUE if the operation was successful, meaning the PRIORITY_QUEUE is empty.  (BOOL)FALSE
		otherwise.
		* @note Will free data with user supplied method when PRIORITY_QUEUE was created.
		* @sa PQueueMemDealloc()
		* @since v1.0
*/
#if (USING_PRIORITY_QUEUE_CLEAR_METHOD == 1)
	BOOL PriorityQueueClear(PRIORITY_QUEUE *PriorityQueue);
#endif // end of USING_PRIORITY_QUEUE_CLEAR_METHOD

/*
	Function: UINT32 PriorityQueueGetSize(PRIORITY_QUEUE *PriorityQueue)

	Parameters: 
		PRIORITY_QUEUE *PriorityQueue - The address of the PRIORITY_QUEUE that will have its size returned.

	Returns:
		UINT32 - The size of the specified PRIORITY_QUEUE.  The size is determined by how many nodes are inside of
		PRIORITY_QUEUE.  If there is an error with the PRIORITY_QUEUE then this method returns (UINT32)0.

	Description: Clears all data inside the PRIORITY_QUEUE, and sets the size back to 0.

	Notes: None
*/
/**
		* @brief Returns the size of a PRIORITY_QUEUE.
		* @param *PriorityQueue - The address of the PRIORITY_QUEUE that will have its size returned.
		* @return UINT32 - The number of nodes present inside the specified PRIORITY_QUEUE.  If there are any errors
		with the PRIORITY_QUEUE or it is empty, then (UINT32)0 is returned.
		* @note None
		* @sa None
		* @since v1.0
*/
#if (USING_PRIORITY_QUEUE_GET_SIZE_METHOD == 1)
	UINT32 PriorityQueueGetSize(PRIORITY_QUEUE *PriorityQueue);
#endif // end of USING_PRIORITY_QUEUE_GET_SIZE_METHOD

/*
	Function: UINT32 PriorityQueueGetSize(PRIORITY_QUEUE *PriorityQueue)

	Parameters: 
		PRIORITY_QUEUE *PriorityQueue - The address of the PRIORITY_QUEUE that will have its size returned.

	Returns:
		UINT32 - The size of the specified PRIORITY_QUEUE.  The size is determined by how many nodes are inside of
		PRIORITY_QUEUE.  If there is an error with the PRIORITY_QUEUE then this method returns (UINT32)0.

	Description: Clears all data inside the PRIORITY_QUEUE, and sets the size back to 0.

	Notes: None
*/
/**
		* @brief Returns the size in bytes of a PRIORITY_QUEUE.
		* @param *PriorityQueue - The address of the PRIORITY_QUEUE that will have its size in bytes returned.
		* @return UINT32 - The number of bytes minus the size of the head of the PRIORITY_QUEUE.  An empty PRIORITY_QUEUE
		will return (UINT32)0.
		* @note This method calculates the size of the PRIORITY_QUEUE in bytes by knowing the size of the data stored in
		each node, and the size of a node multiplied by the number of nodes held within the PRIORITY_QUEUE.
		* @sa None
		* @since v1.0
*/
#if (USING_PRIORITY_QUEUE_GET_SIZE_IN_BYTES_METHOD == 1)
	UINT32 PriorityQueueGetSizeInBytes(PRIORITY_QUEUE *PriorityQueue, UINT32 DataSizeInBytes);
#endif // end of USING_PRIORITY_QUEUE_GET_SIZE_IN_BYTES_METHOD

/*
	Function: const BYTE *PriorityQueueGetLibraryVersion(void)

	Parameters: 
		None

	Returns:
		const BYTE* - The current Priority Queue Library version.

	Description: Returns the current version of the Priority Queue Library.  This string is 
	(BYTE)NULL terminated.

	Notes: None
*/
/**
		* @brief Returns the current version of the Priority Queue Library.
		* @param None
		* @return UINT32 - The current Priority Queue Library version.
		* @note The string is (BYTE)NULL terminated.
		* @since v1.01
*/
#if (USING_PRIORITY_QUEUE_GET_LIBRARY_VERSION == 1)
	const BYTE *PriorityQueueGetLibraryVersion(void);
#endif // end of USING_PRIORITY_QUEUE_GET_LIBRARY_VERSION

/*
	Macro: UINT32 PriorityQueueGetSizeOfNodeInBytes(UINT32 DataSizeInBytes)

	Parameters: 
		UINT32 DataSizeInBytes - The size in bytes of the data being stored in a PRIORITY_QUEUE.

	Returns:
		UINT32 - The size in bytes that the PRIORITY_QUEUE_NODE takes up with it's accompaning
		data.

	Description: Returns the size of a PRIORITY_QUEUE_NODE and it's data in bytes.

	Notes: This method does not take into account how much memory is used to allocate 
	memory through PQueueMemAlloc().
*/
#define PriorityQueueGetSizeOfNodeInBytes(Size)	(UINT32)(Size + sizeof(PRIORITY_QUEUE_NODE))

/*
	Macro: BOOL PriorityQueueIsNull(PRIORITY_QUEUE *PriorityQueue)

	Parameters: 
		PRIORITY_QUEUE *PriorityQueue - The PRIORITY_QUEUE to check if it's NULL or not.

	Returns:
		BOOL - TRUE if the PRIORITY_QUEUE is NULL, FALSE otherwise.

	Description: Checks to see if a PRIORITY_QUEUE is NULL or not.

	Notes: None
*/
#define PriorityQueueIsNull(PriorityQueue)		(PriorityQueue == (PRIORITY_QUEUE*)NULL)

/*
	Macro: BOOL PriorityQueueIsEmpty(PRIORITY_QUEUE *PriorityQueue)

	Parameters: 
		PRIORITY_QUEUE *PriorityQueue - The PRIORITY_QUEUE to check if it's empty or not.

	Returns:
		BOOL - TRUE if the PRIORITY_QUEUE is empty, FALSE otherwise.

	Description: Checks to see if the PRIORITY_QUEUE is empty.

	Notes: None
*/
#define PriorityQueueIsEmpty(PriorityQueue)		(PriorityQueue->Size == (UINT32)0)

#endif // end of PRIORITY_QUEUE_H
