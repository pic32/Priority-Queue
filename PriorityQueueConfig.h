/*
	Date: April 19, 2011
	File Name: PriorityQueueConfig.h
	Version: 1.02
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file allows the user to enable/disable the 
	configurable options built within the Priority Queue
	Library.
*/

#ifndef PRIORITY_QUEUE_CONFIG_H
	#define PRIORITY_QUEUE_CONFIG_H

#define USING_PRIORITY_QUEUE_PEEK_METHOD					1
#define USING_PRIORITY_QUEUE_CLEAR_METHOD					1
#define USING_PRIORITY_QUEUE_GET_SIZE_METHOD				1
#define USING_PRIORITY_QUEUE_GET_SIZE_IN_BYTES_METHOD		1

#define PRIORITY_QUEUE_SAFE_MODE							1

#define USING_PRIORITY_QUEUE_DEPENDENT_FREE_METHOD			1

/**
	*Set USING_PRIORITY_QUEUE_GET_LIBRARY_VERSION to 1 to enable
	the PriorityQueueGetLibraryVersion() method.
*/
#define	USING_PRIORITY_QUEUE_GET_LIBRARY_VERSION			1

/**
	*This defines what method the PriorityQueue library will use to 
	allocate memory and deallocated.  This allows the LinkedList 
	library to be integrated into an OS.
*/
#define PQueueMemAlloc(Mem)										malloc(Mem)

/**
	*The method used for freeing up memory.
*/
#define PQueueMemDealloc(Mem)										free(Mem)

/**
	*Define USE_MALLOC as 1 to enable the stdlib.h file included
	with PriorityQueue.c.
*/
#define USE_MALLOC											1

/**
	*If the user isn't using malloc then include the file that will
	be needed for accessing whatever method PQueueMemAlloc() and PQueueMemDealloc()
	implement, below.
*/
//#include "Your memory file here.h"

#endif // end of PRIORITY_QUEUE_CONFIG_H
