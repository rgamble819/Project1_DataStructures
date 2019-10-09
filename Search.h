// Signature must be retained. Implementation must be added.

#ifndef SEARCH_H
#define SEARCH_H

#include "Exceptions.h"
#include "ResizableArray.h"
#include "Comparator.h"
#include "DrillingRecordComparator.h"

// returns FIRST array location matching the given item (based on the comparator)
// if not found, returns -(location to insert + 1)
// Also returns lowest index of duplicate values.
template <typename T>
long long binarySearch(const T& item, const ResizableArray<T>& array, const Comparator<T>& comparator)
{
	long high = array.getSize() - 1L;
	long low = 0L;
	long mid = 0L;
	
	while (high >= low) 
	{
		mid = (low + high) / 2L;
		if (comparator.compare(item, array.get(mid)) > 0) 
		{

			low = mid + 1L;
		}
		else if (comparator.compare(item, array.get(mid)) < 0)
		{
			high = mid - 1L;
		}
		else 
		{
			// Binary search modification

			// Save index where item was found.
			long indexDown = mid;
			if (indexDown > 0) 
			{
				// Loop through index below to get the lowest index of duplicate value.
				while (indexDown > 0)
				{
					indexDown--;
					if (comparator.compare(array.get(mid), array.get(indexDown)) == 0) {
						mid = indexDown;
					}
					else 
					{
						break;
					}
				}
			}
			/////// End of modification. //////////

			return mid;
		}
	}
	return -1;
}

// Linear search through a resizable array.
template <typename T>
long long* linearSearch(const T& item, const ResizableArray<T>& array, const Comparator<T>& comparator) 
{
	long long* recordIndexFound = new long long[array.getSize()];

	int initialize = (int)array.getSize() - 1;
	while (initialize >= 0) 
	{
		recordIndexFound[initialize] = -1;
		initialize--;
	}

	unsigned long indexToLook = 0;
	long indexFoundTracker = 0;
	while (indexToLook < array.getSize())
	{
		if (comparator.compare(item, array.get(indexToLook)) == 0)
		{
			recordIndexFound[indexFoundTracker] = indexToLook;
			indexFoundTracker++;
		}
		indexToLook++;
	}
	return recordIndexFound;
}

// Hepler method that finds records that and duplicate to the record found with a previous binary search. The same comparator must be used as the binary search executed.
template <typename T>
// Count above and below an index where a record is found. This means it will count the total number of records that are identical to the search key.
ResizableArray<T>* findNear(const ResizableArray<T>& drillArray, long index, const DrillingRecord& toFind, const Comparator<T>& comparator)
{
	// Create array to return for output.
	ResizableArray<T>* recordsFound = new ResizableArray<T>();
	if (recordsFound == NULL) throw new ExceptionMemoryNotAvailable;

	// If index found from binary search isnt found return empty array.
	if (index < 0) 
	{
		return recordsFound;
	}

	// Add initial record to array.
	recordsFound->add(drillArray.get(index));

	// Create index to search from linearly.
	long indexUp = index + 1;
	long indexDown = index  -1;

	// Try catch will catch if index goes over or below array.
	try 
	{
		// Count Forwards and check forwards from index found
		while (comparator.compare(drillArray.get(indexUp), toFind) == 0)
		{
			// Add record to the array
			recordsFound->addAt(drillArray.get(indexUp), 0);

			// Increment loop
			indexUp++;
		}
	}		
	catch (ExceptionIndexOutOfRange* excep)
	{
		// Delete Exception
		delete excep;
		excep = NULL;
	}



	// Try catch will catch if index goes over or below array.
	try
	{
		// Count Backwards and check backwards from index found.
		while (comparator.compare(drillArray.get(indexDown), toFind) == 0)
		{
			//Add record to the array
			recordsFound->addAt(drillArray.get(indexDown), 0);

			// Decrement loop
			indexDown--;
		}
	}
	catch (ExceptionIndexOutOfRange* excep) 
	{
		// Delete Exception
		delete excep;
		excep = NULL;
	}

	// Return array.
	return recordsFound;
}

#endif