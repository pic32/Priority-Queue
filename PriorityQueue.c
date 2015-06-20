/*
	Date: April 19, 2011
	File Name: PriorityQueue.c
	Version: 1.02
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file contains the code for the Priority Queue Library.
	For all method definitions see PriorityQueue.h.
*/

#include "PriorityQueue.h"
#include "PriorityQueueConfig.h"

#if (USE_MALLOC == 1)
	#include "stdlib.h"
#endif // end of USE_MALLOC

PRIORITY_QUEUE *CreatePriorityQueue(PRIORITY_QUEUE *PriorityQueue, INT32 (*CompareTo)(const void *Data1, const void *Data2), void (*CustomFreeMethod)(void *Data))
{
	PRIORITY_QUEUE *TempPriorityQueue;

	#if (PRIORITY_QUEUE_SAFE_MODE == 1)
		if(CompareTo == (INT32(*)(const void *, const void *))NULL)
			return (PRIORITY_QUEUE*)NULL;
	#endif // end of PRIORITY_QUEUE_SAFE_MODE

	if(PriorityQueue)
	{
		TempPriorityQueue = (PRIORITY_QUEUE*)PriorityQueue;
	}
	else
	{
		if((TempPriorityQueue = (PRIORITY_QUEUE*)PQueueMemAlloc(sizeof(PRIORITY_QUEUE))) == (PRIORITY_QUEUE*)NULL)
		{
			return (PRIORITY_QUEUE*)NULL;
		}
	}

	TempPriorityQueue->CompareTo = (INT32(*)(const void *, const void *))CompareTo;
	TempPriorityQueue->Head = TempPriorityQueue->Tail = (PRIORITY_QUEUE_NODE*)NULL;
	TempPriorityQueue->Size = (UINT32)0;

	#if(USING_PRIORITY_QUEUE_DEPENDENT_FREE_METHOD == 1)
		TempPriorityQueue->PriorityQueueFreeMethod = (void(*)(void *))CustomFreeMethod;
	#endif // USING_PRIORITY_QUEUE_DEPENDENT_FREE_METHOD

	return (PRIORITY_QUEUE*)TempPriorityQueue;
}

BOOL PriorityQueueAdd(PRIORITY_QUEUE *PriorityQueue, const void *Data)
{
	PRIORITY_QUEUE_NODE *TempNode, *Node;

	#if (PRIORITY_QUEUE_SAFE_MODE == 1)
		if(PriorityQueueIsNull(PriorityQueue))
			return (BOOL)FALSE;
	#endif // end of PRIORITY_QUEUE_SAFE_MODE

	if((Node = (PRIORITY_QUEUE_NODE*)PQueueMemAlloc(sizeof(PRIORITY_QUEUE_NODE))) == (PRIORITY_QUEUE_NODE*)NULL)
		return (BOOL)FALSE;

	Node->Data = (void*)Data;
	Node->Next = Node->Previous = (PRIORITY_QUEUE_NODE*)NULL;

	PriorityQueue->Size++;

	if(PriorityQueue->Size == (UINT32)1)
	{
		PriorityQueue->Head = PriorityQueue->Tail = (PRIORITY_QUEUE_NODE*)Node;
		return (BOOL)TRUE;
	}

	TempNode = (PRIORITY_QUEUE_NODE*)(PriorityQueue->Head);

	do
	{
		if(PriorityQueue->CompareTo((void*)(TempNode->Data), (void*)(Node->Data)) > 0)
		{
			// we found a winner, we go before TempNode
			if(TempNode->Previous)
			{
				// we know we're not the first node in the list.
				Node->Previous = (PRIORITY_QUEUE_NODE*)(TempNode->Previous);
				Node->Next = (PRIORITY_QUEUE_NODE*)TempNode;
				Node->Previous->Next = (PRIORITY_QUEUE_NODE*)Node;
				TempNode->Previous = (PRIORITY_QUEUE_NODE*)Node;
			}
			else
			{
				// We're the beginning.
				Node->Next = (PRIORITY_QUEUE_NODE*)TempNode;
				TempNode->Previous = (PRIORITY_QUEUE_NODE*)Node;
				PriorityQueue->Head = (PRIORITY_QUEUE_NODE*)Node;
			}

			return (BOOL)TRUE;
		}

		TempNode = (PRIORITY_QUEUE_NODE*)(TempNode->Next);
	}
	while(TempNode != (PRIORITY_QUEUE_NODE*)NULL);

	// now were at the end of the LINKED_LIST
	PriorityQueue->Tail->Next = (PRIORITY_QUEUE_NODE*)Node;
	Node->Previous = (PRIORITY_QUEUE_NODE*)(PriorityQueue->Tail);
	PriorityQueue->Tail = (PRIORITY_QUEUE_NODE*)Node;

	return (BOOL)TRUE;
}

void *PriorityQueueRemove(PRIORITY_QUEUE *PriorityQueue)
{
	void *Data;
	PRIORITY_QUEUE_NODE *Node;

	#if (PRIORITY_QUEUE_SAFE_MODE == 1)
		if(PriorityQueueIsNull(PriorityQueue))
			return (void*)NULL;

		if(PriorityQueueIsEmpty(PriorityQueue))
			return (void*)NULL;
	#endif // end of PRIORITY_QUEUE_SAFE_MODE

	PriorityQueue->Size--;

	Data = (void*)(PriorityQueue->Head->Data);
	Node = (PRIORITY_QUEUE_NODE*)(PriorityQueue->Head);
	PriorityQueue->Head = (PRIORITY_QUEUE_NODE*)(PriorityQueue->Head->Next);

	if(PriorityQueue->Size == (UINT32)0)
	{
		PriorityQueue->Tail = (PRIORITY_QUEUE_NODE*)NULL;
	}
	else
	{
		PriorityQueue->Head->Previous = (PRIORITY_QUEUE_NODE*)NULL;
	}

	PQueueMemDealloc((void*)Node);

	return (void*)Data;
}

#if (USING_PRIORITY_QUEUE_PEEK_METHOD == 1)
	void *PriorityQueuePeek(PRIORITY_QUEUE *PriorityQueue)
	{
		#if (PRIORITY_QUEUE_SAFE_MODE == 1)
			if(PriorityQueueIsNull(PriorityQueue))
				return (void*)NULL;

			if(PriorityQueueIsEmpty(PriorityQueue))
				return (void*)NULL;
		#endif // end of PRIORITY_QUEUE_SAFE_MODE

		return (void*)(PriorityQueue->Head->Data);
	}
#endif // end of USING_PRIORITY_QUEUE_PEEK_METHOD

#if (USING_PRIORITY_QUEUE_CLEAR_METHOD == 1)
	BOOL PriorityQueueClear(PRIORITY_QUEUE *PriorityQueue)
	{
		PRIORITY_QUEUE_NODE *Node;

		#if (PRIORITY_QUEUE_SAFE_MODE == 1)
			if(PriorityQueueIsNull(PriorityQueue))
				return (BOOL)FALSE;
		#endif // end of PRIORITY_QUEUE_SAFE_MODE

		if(PriorityQueueIsEmpty(PriorityQueue))
			return (BOOL)TRUE;

		Node = (PRIORITY_QUEUE_NODE*)(PriorityQueue->Head);

		while(Node != (PRIORITY_QUEUE_NODE*)NULL)
		{
			PriorityQueue->Head = (PRIORITY_QUEUE_NODE*)(PriorityQueue->Head->Next);

			/*
				If the user allocated memory for the void pointer, clear it if they supplied
				a method pointer for freeing.  Otherwise check the DefaultFree variable next, if 
				so then use the method they supplied as a generic free method.
			*/
			#if(USING_PRIORITY_QUEUE_DEPENDENT_FREE_METHOD == 1)
				if(PriorityQueue->PriorityQueueFreeMethod)
				{
					PriorityQueue->PriorityQueueFreeMethod((void*)(Node->Data));
				}
			#endif // end of USING_PRIORITY_QUEUE_DEPENDENT_FREE_METHOD
	
			PQueueMemDealloc((void*)(Node));

			Node = (PRIORITY_QUEUE_NODE*)(PriorityQueue->Head);
		}

		PriorityQueue->Size = (UINT32)0;
		PriorityQueue->Tail = (PRIORITY_QUEUE_NODE*)NULL;

		return (BOOL)TRUE;
	}
#endif // end of USING_PRIORITY_QUEUE_CLEAR_METHOD

#if (USING_PRIORITY_QUEUE_GET_SIZE_METHOD == 1)
	UINT32 PriorityQueueGetSize(PRIORITY_QUEUE *PriorityQueue)
	{
		#if (PRIORITY_QUEUE_SAFE_MODE == 1)
			if(PriorityQueueIsNull(PriorityQueue))
				return (UINT32)0;
		#endif // end of PRIORITY_QUEUE_SAFE_MODE

		return (UINT32)(PriorityQueue->Size);
	}
#endif // end of USING_PRIORITY_QUEUE_GET_SIZE_METHOD

#if (USING_PRIORITY_QUEUE_GET_SIZE_IN_BYTES_METHOD == 1)
	UINT32 PriorityQueueGetSizeInBytes(PRIORITY_QUEUE *PriorityQueue, UINT32 DataSizeInBytes)
	{
		UINT32 Size;

		#if (PRIORITY_QUEUE_SAFE_MODE == 1)
			if(PriorityQueueIsNull(PriorityQueue))
				return (UINT32)0;
		#endif // end of PRIORITY_QUEUE_SAFE_MODE

		Size = (UINT32)sizeof(PRIORITY_QUEUE);
	
		if(PriorityQueueIsEmpty(PriorityQueue))
			return (UINT32)Size;

		/*
			If the user provided us with the size of their data in bytes
			then we must use it to calculate the size of the PRIORITY_QUEUE in bytes.
			Otherwise we just don't include it in the calculation.
		*/
		if(DataSizeInBytes)
			Size += (UINT32)((UINT32)(PriorityQueue->Size) * (UINT32)((UINT32)DataSizeInBytes + (UINT32)sizeof(PRIORITY_QUEUE_NODE)));
		else
			Size += (UINT32)((UINT32)(PriorityQueue->Size) * (UINT32)sizeof(PRIORITY_QUEUE_NODE));

		return (UINT32)Size;
	}
#endif // end of USING_PRIORITY_QUEUE_GET_SIZE_IN_BYTES_METHOD

#if (USING_PRIORITY_QUEUE_GET_LIBRARY_VERSION == 1)

	const BYTE *PriorityQueueLibraryVersion[] = {"Priority Queue Lib v1.02\0"};

	const BYTE *PriorityQueueGetLibraryVersion(void)
	{
		return (const BYTE*)PriorityQueueLibraryVersion;
	}

#endif // end of USING_PRIORITY_QUEUE_GET_LIBRARY_VERSION