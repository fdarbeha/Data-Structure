// File:        dlinkedlist.cpp
// Author:      Fatemeh Darbehani
// Date:        January 25, 2016
// Description: Definition of a template doubly-linked-list class
#ifdef _DLINKEDLIST_H_
#include <stdexcept>
template <class T>
void DLinkedList<T>::CopyList(const DLinkedList& ll)
{
    size = 0;
    if(ll.size != 0){
        front = new Node<T> (ll.front->data);
        back = front;
        size++;
        
        Node<T>* iterate_ll = ll.front;
        
        while(iterate_ll->next){
            InsertBack(iterate_ll->next->data);
            iterate_ll = iterate_ll->next;
        }
    }
}
template <class T>
void DLinkedList<T> :: DeleteList()
{
    if(size != 0)
    {
        Node<T>* iterate = back;
        while(back != front)
        {
            back = back->prev;
            delete iterate;
            iterate = back;
        }
        front = NULL;
        back = NULL;
        delete iterate;
    }
}
template <class T>
DLinkedList<T> :: DLinkedList()
{
    size = 0;
    front = NULL;
    back = NULL;
}
template <class T>
DLinkedList<T> :: DLinkedList(const DLinkedList& ll)
{
    CopyList(ll);
}
template <class T>
DLinkedList<T> :: ~DLinkedList()
{
    DeleteList();
}
template <class T>
void DLinkedList<T> :: InsertFront(T item)
{
    Node<T>* item_node = new Node<T>(item);
    if(front == NULL)
    {
        front = item_node;
        back = front;
        front->next = NULL;
    }
    else{
        Node<T>* temp = front;
        front = item_node;
        front->next = temp;
        temp->prev = front;
    }
    front->prev = NULL;
    size++;
}
template <class T>
void DLinkedList<T> :: InsertBack(T item)
{
    Node<T>* item_node = new Node<T>(item);
    if(back == NULL){
        back = item_node;
        front = back;
        back->prev = NULL;
    }
    else{
        Node<T>* temp = back;
        back = item_node;
        item_node->prev = temp;
        temp->next = item_node;
    }
    back->next = NULL;
    size++;
}
template <class T>
void DLinkedList<T> :: InsertAt(T item, int p)
{
    Node<T>* item_node = new Node<T>(item);
    if(p < 0 || p > size)
        throw std::exception("DLinkedList::InsertAt -- Index out of range");
    if(p == 0)
        InsertFront(item);
    else if(p == size)
        InsertBack(item);
    else
    {
        int count = 0;
        Node<T>* temp = front;
        while(count != p){
            temp = temp->next;
            count++;
        }
        Node<T>* current = temp->prev;
        current->next = item_node;
        item_node->prev = current;
        item_node->next = temp;
        temp->prev = item_node;
        size++;
    }
}
template <class T>
T DLinkedList<T> :: RemoveAt(int p)
{
    if (IsEmpty())
        throw std::exception("DLinkedList::RemoveAt -- List is empty! or maybe list is tired!");
    if(p < 0 || p >= size)
        throw std::exception("DLinkedList::RemoveAt -- Index out of range");
    
    Node<T>* temp = NULL;
    
    if(p == 0){
        temp = front;
        front = front->next;
        front->prev = NULL;
    }
    else if(p == size-1){
        temp = back;
        back = back->prev;
        back->next = NULL;
    }
    else{
        temp = front;
        int count = 0;
        while(count != p){
            temp = temp->next;
            count++;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
    size--;
    return temp->data;
}
template <class T>
void DLinkedList<T> :: RemoveDuplicates()
{
    for(int i = 0; i < size - 1; i++)
        for(int j = i + 1; j < size; j++)
            if(ElementAt(i) == ElementAt(j)){
                RemoveAt(j);
                j--;
            }
}
template <class T>
int DLinkedList<T> :: Size() const
{
    return size;
}
template <class T>
bool DLinkedList<T> :: IsEmpty() const
{
    return (size == 0);
}
template <class T>
bool DLinkedList<T> :: Contains(T item) const
{
    if (IsEmpty())
        return false;
    
    for(int i = 0; i < size; i++)
        if(ElementAt(i) == item)
            return true;
    
    return false;
}
template <class T>
T DLinkedList<T> :: ElementAt(int p) const
{
    if(p < 0 || p >= size)
        throw std::exception("DLinkedList::ElementAt -- Index out of range");
    Node<T>* temp = front;
    int count = 0;
    while(count != p){
        temp = temp->next;
        count++;
    }
    return temp->data;
}
template <class T>
DLinkedList<T>& DLinkedList<T> :: operator=(const DLinkedList& ll)
{
    if(*this != ll){
        DeleteList();
        CopyList(ll);
    }
    return *this;
}
#endif