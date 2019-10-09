
//#include "ResizableArray.h"
#include "Comparator.h"
#include "DrillingRecordComparator.h"
#include"DrillingRecord.h"
#include"Search.h"
#include <string>
#include "Sorter.h"

using namespace std;

void testCompare();
void testBinarySearch();
//void testMerge();
void testMergeSort();
void testLinearSearch();
void testTimeStamps();

int main2() 
{
	testTimeStamps();
	//testCompare();
	//testMerge();
//	testBinarySearch();
	//testMergeSort();
	//testLinearSearch();
	return 5;
}

template<typename T>
bool assert(T item1, T item2) 
{
	if (item1 == item2) 
	{
		return true;
	}
	return false;
}

void testCompare() 
{
	// Testing all possibilities of comparator
	DrillingRecordComparator* compareDate = new DrillingRecordComparator(0);
	DrillingRecordComparator* compareTime = new DrillingRecordComparator(1);
	DrillingRecordComparator* compareValues = new DrillingRecordComparator(4);

	// Create records to compare and then assert they are accurate
	DrillingRecord* record1 = new DrillingRecord();
	DrillingRecord* record2 = new DrillingRecord();
	
	record1->setString("07/31/2019", 0);
	record2->setString("07/31/2019", 0);

	if (assert(0, compareDate->compare(*record1, *record2))) 
	{
		cout << "Date comparator was successful! 1 = 2\n";
	}
	else 
	{
		cout << "Date comparator failed! 1\n";
	}

	record1->setString("07/31/2018", 0);
	record2->setString("07/31/2019", 0);

	if (assert(-1, compareDate->compare(*record1, *record2)))
	{
		cout << "Date comparator was successful! 1 < 2\n";
	}
	else
	{
		cout << "Date comparator failed! 2\n";
	}

	record1->setString("07/31/2019", 0);
	record2->setString("07/31/2018", 0);

	if (assert(1, compareDate->compare(*record1, *record2)))
	{
		cout << "Date comparator was successful! 1 > 2\n";
	}
	else
	{
		cout << "Date comparator failed! 3\n";
	}

	record1->setString("00:00:01", 1);
	record2->setString("00:00:01", 1);

	if (assert(0, compareTime->compare(*record1, *record2)))
	{
		cout << "Time comparator was successful! 1 = 2\n";
	}
	else
	{
		cout << "Time comparator failed! 1\n";
	}

	record1->setString("00:00:01", 1);
	record2->setString("00:00:02", 1);

	if (assert(-1, compareTime->compare(*record1, *record2)))
	{
		cout << "Time comparator was successful! 1 < 2\n";
	}
	else
	{
		cout << "Time comparator failed! 2\n";
	}

	record1->setString("00:10:02", 1);
	record2->setString("00:00:01", 1);

	if (assert(1, compareTime->compare(*record1, *record2)))
	{
		cout << "Time comparator was successful! 1 < 2\n";
	}
	else
	{
		cout << "Time comparator failed! 3\n";
	}

	record1->setNum(5.0, 2);
	record2->setNum(5.0, 2);

	if (assert(0, compareValues->compare(*record1, *record2)))
	{
		cout << "Value comparator was successful! 1 = 2\n";
	}
	else
	{
		cout << "Value comparator failed! 1\n";
	}

	record1->setNum(2.0, 2);
	record2->setNum(5.0, 2);

	if (assert(-1, compareValues->compare(*record1, *record2)))
	{
		cout << "Value comparator was successful! 1 < 2\n";
	}
	else
	{
		cout << "Value comparator failed! 2\n";
	}

	record1->setNum(5.0, 2);
	record2->setNum(2.0, 2);

	if (assert(1, compareValues->compare(*record1, *record2)))
	{
		cout << "Value comparator was successful! 1 > 2\n";
	}
	else
	{
		cout << "Value comparator failed! 3\n";
	}
}

void testBinarySearch() 
{
	ResizableArray<DrillingRecord>* testArr = new ResizableArray<DrillingRecord>();

	DrillingRecordComparator* comparator = new DrillingRecordComparator(0);
	DrillingRecordComparator* numsComparator = new DrillingRecordComparator(11);

	for (int i = 0; i < 9; i++) 
	{
		DrillingRecord* record = new DrillingRecord();
		record->setString("test" + to_string(i), 0);

		if (i == 8) 
		{
			record->setNum(15,9);
		}

		testArr->add(*record);
	}

	DrillingRecord* toFind = new DrillingRecord();
	toFind->setString("test7", 0);

	int indexLoc = binarySearch(*toFind, *testArr, *comparator);
	
	if (assert(7, indexLoc)) 
	{
		cout << "Binary search was successful!\n";
	}
	else 
	{
		cout << "Binary search failed!\n";
	}

	toFind->setString("test4", 0);
	indexLoc = binarySearch(*toFind, *testArr, *comparator);

	if (assert(4, indexLoc))
	{
		cout << "Binary search was successful!\n";
	}
	else
	{
		cout << "Binary search failed!\n";
	}

	toFind->setNum(15, 9);

	int indexLoc2 = binarySearch(*toFind, *testArr, *numsComparator);

	if (assert(8, indexLoc2))
	{


		cout << "Binary search was successful!\n";
	}
	else
	{
		cout << "Binary search failed!\n";
	}
}

void testMerge()
{
	// Create record array to merge/sort
	ResizableArray<DrillingRecord>* recordsToSort = new ResizableArray<DrillingRecord>();

	// Create records and populate array
	DrillingRecord* first = new DrillingRecord();
	DrillingRecord* second = new DrillingRecord();
	first->addNum(2);
	second->addNum(1);
	recordsToSort->add(*first);
	recordsToSort->add(*second);

	// Create comparator to sort by
	DrillingRecordComparator* comparator = new DrillingRecordComparator(2);

	// Call the method to test
	//Sorter<DrillingRecord>::merge(*recordsToSort, 0, 0, 1, *comparator);

	if (assert(1.0, (recordsToSort->get(0).getNum(0))))
	{
		cout << "Merge function was successful!\n";
	}
	else 
	{
		cout << "Merge function failed!\n";
	}
}

void testMergeSort() 
{
	// Construct array
	ResizableArray<DrillingRecord>* arrayToSort = new ResizableArray<DrillingRecord>();

	// Construct comparator for row 0
	DrillingRecordComparator* comparator = new DrillingRecordComparator(0);

	//Populate arrayToSort
	for(int numRecords = 8; numRecords >= 0; numRecords--)
	{
		DrillingRecord* record = new DrillingRecord;
		record->addString("test:" + to_string(numRecords));
		arrayToSort->add(*record);
	}

	for (int index = 0; index < arrayToSort->getSize(); index++)
	{
		cout << arrayToSort->get(index) << '\n';
	}
	cout << '\n';

	// Call sort method
	Sorter<DrillingRecord>::sort(*arrayToSort, *comparator);

	for (int index = 0; index < arrayToSort->getSize(); index++) 
	{
		cout << arrayToSort->get(index) << '\n';
	}
}

void testLinearSearch() 
{
	/*ResizableArray<DrillingRecord>* drillarr = new ResizableArray<DrillingRecord>();

	DrillingRecordComparator* comparator = new DrillingRecordComparator(1);

	for (int i = 0; i < 9; i++) 
	{
		DrillingRecord* record = new DrillingRecord;
		if (i == 5) {
			record->setString(to_string(i), 1);
		}
		drillarr->add(*record);
	}

	DrillingRecord* toSearch = new DrillingRecord;

	toSearch->setString(to_string(5), 1);

	int index = linearSearch(*toSearch, *drillarr, *comparator);


	cout << "\n";
	for (int j = 0; j < 9; j++) 
	{
		cout << drillarr->get(j) << "\n";
	}

	cout << "\n" << *toSearch << "\n";



	if (assert(5, index)) 
	{		
		cout << "Linear search was successful.";
	}
	else 
	{
		cout << "Linear search was a failure! Index Found: " << index << " Index Expected: 5";
	}*/
}

void testTimeStamps() 
{
	ResizableArray<DrillingRecord>* arr = new ResizableArray<DrillingRecord>();
	int i = 9;
	while (i >= 0) 
	{
		DrillingRecord* record = new DrillingRecord();
		record->setString("12:" + to_string(rand() % 10) + ":" + to_string(rand() % 10), 1);
		arr->add(*record);
		i--;
	}

	int index = arr->getSize() - 1;
	while (index >= 0) 
	{
		cout << arr->get(index) << "\n";
		index--;
	}
	cout << "\n";

	DrillingRecordComparator* comparator = new DrillingRecordComparator(1);
	Sorter<DrillingRecord>::sort(*arr, *comparator);

	index = arr->getSize() - 1;
	while (index >= 0)
	{
		cout << arr->get(index) << "\n";
		index--;
	}
}