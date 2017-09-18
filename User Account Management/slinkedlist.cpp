#ifdef _SLINKEDLIST_H_
// helper function for deep copy
// Used by copy constructor and operator=
template <class T>
void SLinkedList<T>::CopyList(const SLinkedList& ll)
{
	front = NULL;
	if (ll.front != NULL)
	{
		Node<T>* ll_current = ll.front;
		Node<T>* temp = new Node<T>(ll_current->data);
		front = temp;
		back = front;
		ll_current = ll_current->next;
		while (ll_current != NULL)
		{
			temp->next = new Node<T>(ll_current->data);
			temp = temp->next;
			back = ll_current;
			ll_current = ll_current->next;
		}

	}
}

// helper function for deep delete
// Used by destructor and copy/assignment
template <class T>
void SLinkedList<T>::DeleteList()
{
	while (front != NULL)
	{
		Node<T>* temp = front;
		front = front->next;
		delete temp;
	}
	front = NULL;
	back = NULL;
}

// default constructor
template <class T>
SLinkedList<T>::SLinkedList()
{
	front = NULL;
	back = NULL;
	size = 0;
}

// copy constructor, performs deep copy of list elements
template <class T>
SLinkedList<T>::SLinkedList(const SLinkedList& ll)
{
	CopyList(ll);
	size = ll.size;
}

// destructor
template <class T>
SLinkedList<T>::~SLinkedList()
{
	DeleteList();
	size = 0;
}

// MUTATORS

// Inserts an item at the front of the list
// POST:  List contains item at front
// PARAM: item = item to be inserted
template <class T>
void SLinkedList<T>::InsertFront(T item)
{
	Node<T>* newNode = new Node<T>(item);
	newNode->next = front;
	front = newNode;
	if (!back)
		back = newNode;
	size++;
}

// Inserts an item at the back of the list
// POST:  List contains item at back
// PARAM: item = item to be inserted
template<class T>
void SLinkedList<T>::InsertBack(T item)
{
	Node<T>* newNode = new Node<T>(item);
	if (front){
		back->next = newNode;
		back = newNode;
	}
	else{
		front = newNode;
		back = newNode;
	}
	size++;
}

// Removes the first occurrence of the supplied parameter
// Removes and returns true if found, otherwise returns false if parameter is not found or list is empty
template <class T>
bool SLinkedList<T>::Remove(T item)
{
	bool found = false;
	if (front){
		Node<T>* current = front;
		Node<T>* prev = front;
		while (current){
			if (current->data == item){
				found = true;
				break;
			}
			prev = current;
			current = current->next;
		}
		if (found){
			if (current == front){
				front = front->next;
				delete current;
			}
			else if(current == back){
				back = prev;
				prev->next = NULL;
				delete current;
			}
			else{
				prev->next = current->next;
				delete current;
			}
			size--;
		}
	}
	return found;

}

// Removes all items in the list
template <class T>
void SLinkedList<T>::RemoveAll()
{
	DeleteList();
	size = 0;
}

// ACCESSORS

// Returns size of list
template <class T>
int SLinkedList<T>::Size() const{ return size; }

// Returns whether the list is empty
template <class T>
bool SLinkedList<T>::IsEmpty() const{ return (front == NULL); }

// Returns existence of item
template <class T>
bool SLinkedList<T>::Contains(T item) const
{
	bool found = false;
	if (front){
		Node<T>* current = front;
		while (current){
			if (current->data == item){
				found = true;
				break;
			}
			current = current->next;
		}
	}
	return found;
}

// Returns a pointer to the in-place list item or NULL if item not found
template <class T>
T* SLinkedList<T>::Retrieve(T item){
	Node<T>* list_item = front;
	while (list_item){
		if (list_item->data != item)
			list_item = list_item->next;
		else
			break;
	}
	return &(list_item->data);
}

// Returns a vector containing the list contents using push_back
template <class T>
vector<T> SLinkedList<T>::Dump() const{
	vector<T> my_vector;
	Node<T>* current = front;
	while (current)
	{
		my_vector.push_back(current->data);
		current = current->next;
	}
	return my_vector;
}

// OVERLOADED OPERATORS

// must work in the following cases:
// list2 = list1 -> general case
// list2 = list2 -> should do nothing
template <class T>
SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList& ll)
{
	if (this != &ll)
	{
		RemoveAll();
		CopyList(ll);
		size = ll.size;
	}
	return *this;
}

#endif