#include "hashtable.h"

// hash function, uses Horner's method
// Assume input string consists only of lower-case a to z
int HashTable::Hash(string input) const
{
	int result = 0, length = input.length();
	if (length > 1){
		result = findValue(input[0]) * 32;
		for (int i = 1; i < length - 1; i++)
		{
			result = ((result + findValue(input[i])) % maxsize) * 32;
		}
		result = (result + findValue(input[length - 1])) % maxsize;
	}
	else
		result = findValue(input[0]) % maxsize;
	return result;
}

// helper function to find smallest prime number greater than supplied parameter
int HashTable::SmallestPrime(int n) const
{
	bool prime = false;
	while (!prime)
	{
		prime = IsPrime(n + 1);
		n++;
	}
	return n;
}

// helper function to determine whether a number is prime
bool HashTable::IsPrime(int n) const
{
	for (int i = 2; i <= ceil(sqrt(n)); i++)
		if (n % i == 0)
			return false;
	return true;
}

// Resizes the hashtable into a larger array.
// Return false if n is smaller than current array size or if n is negative.
// Else, set array size to the smallest prime number larger than n
//   and re-hash all contents into the new array, delete the old array and return true.
bool HashTable::Resize(int n)
{
	if (n <= maxsize || n < 0)
		return false;
	
	vector<UserAccount> hashValues;
	vector<UserAccount> hashVector;

	for(int i = 0; i < maxsize; i++){
		hashValues = table[i].Dump();
		if (hashValues.size() != 0)
			hashVector.insert(hashVector.end(), hashValues.begin(), hashValues.end());
		table[i].RemoveAll();
	}
	delete[] table;
	maxsize = SmallestPrime(n);
	table = new SLinkedList<UserAccount>[maxsize];

	for (int i = 0; i < (int)hashVector.size(); i++)
		Insert(hashVector.at(i));

	return true;
}

// default constructor
// creates an array of size 101
HashTable::HashTable()
{
	size = 0;
	maxsize = 101;
	table = new SLinkedList<UserAccount>[maxsize];
}

// parameterized constructor
// creates an array of size = smallest prime number > 2n
HashTable::HashTable(int n)
{
	size = 0;
	maxsize = SmallestPrime(2*n);
	table = new SLinkedList<UserAccount>[maxsize];
}

// copy constructor
// Creates deep copy of sourceht
HashTable::HashTable(const HashTable& sourceht)
{
	maxsize = sourceht.MaxSize();
	table = new SLinkedList<UserAccount>[maxsize];
	for (int i = 0; i < maxsize; i++)
		table[i] = sourceht.table[i];
	size = sourceht.Size();
}

// destructor
HashTable::~HashTable()
{
	for (int i = 0; i < maxsize; i++)
		table[i].RemoveAll();
	size = 0;
	maxsize = 0;
	table = NULL;
	delete[] table;
}

// overloaded assignment operator
HashTable& HashTable::operator = (const HashTable& sourceht)
{
	if (&sourceht != this){
		for (int i = 0; i<maxsize; i++)
			table[i].RemoveAll();
		delete[] table;
		maxsize = sourceht.maxsize;
		table = new SLinkedList<UserAccount>[maxsize];
		for (int i = 0; i < maxsize; i++)
			table[i] = sourceht.table[i];
		size = sourceht.Size();
	}
	return *this; 
}

// Insertion
// If item does not already exist, inserts at back of hashed list and returns true
//   otherwise returns false
// If load factor (before insertion) is above 2/3, expand into a new
//   table of smallest prime number size at least double the present table size
//   and then insert the item.
bool HashTable::Insert(UserAccount acct)
{
	if (LoadFactor() > (2 / 3))
		Resize(maxsize*2);
	if (!Search(acct)){
		int index = Hash(acct.GetUsername());
		table[index].InsertBack(acct);
		size++;
		return true;
	}
	return false;
}

// Removal
// If item exists, removes and returns true
//   otherwise returns false
bool HashTable::Remove(UserAccount acct)
{
	if (!Search(acct))
		return false;
	int index = Hash(acct.GetUsername());
	table[index].Remove(acct);
	size--;
	return true;
}

// Search
// Returns true if item exists, false otherwise
bool HashTable::Search(UserAccount acct) const
{
	int index = Hash(acct.GetUsername());
	if (table[index].Contains(acct))
		return true;
	return false;
}

// Retrieval
// Returns a pointer to a UserAccount object inside the hash table (linked list)
//   if a matching parameter is found, otherwise return NULL
UserAccount* HashTable::Retrieve(UserAccount acct)
{
	if (!Search(acct))
		return NULL;
	int index = Hash(acct.GetUsername());
	return table[index].Retrieve(acct);
}

// Returns the number of items stored in the hash table
int HashTable::Size() const{ return size; }

// Returns the size of the underlying array
int HashTable::MaxSize() const{ return maxsize; }

// Returns the load factor as size / maxsize.
// Note that due to separate chaining, load factor can be > 1.
double HashTable::LoadFactor() const{ return size / maxsize; }
