/*
	Date: April 19, 2011
	File Name: PriorityQueueObject.h
	Version: 1.02
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file is the definition of the PRIORITY_QUEUE object
	itself.
*/

#ifndef PRIORITY_QUEUE_OBJECT_H
	#define PRIORITY_QUEUE_OBJECT_H

#include "GenericTypes.h"
#include "PriorityQueueConfig.h"

struct _PriorityQueueNode
{
	void *Data;
	struct _PriorityQueueNode *Next;
	struct _PriorityQueueNode *Previous;
};

typedef struct _PriorityQueueNode PRIORITY_QUEUE_NODE;

struct _PriorityQueue
{
	// Attributes
	UINT32 Size;					// The current Size of the PRIORITY_QUEUE.
	PRIORITY_QUEUE_NODE *Head;		// A pointer to the beginning of the PRIORITY_QUEUE.
	PRIORITY_QUEUE_NODE *Tail;		// A pointer to the end of the PRIORITY_QUEUE.

	// Methods

	/*
		If Data2 is smaller than Data1 then this method should return < 0.
		If they are equal it should return 0.
		If Data2 is larger than Data1 then this method should return > 0.
	*/
	INT32 (*CompareTo)(const void *Data1, const void *Data2);

	#if(USING_PRIORITY_QUEUE_DEPENDENT_FREE_METHOD == 1)
		void (*PriorityQueueFreeMethod)(void *Data);
	#endif // USING_PRIORITY_QUEUE_DEPENDENT_FREE_METHOD
};

typedef struct _PriorityQueue PRIORITY_QUEUE;

#endif // end of PRIORITY_QUEUE_OBJECT_H
