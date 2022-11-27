//
// Created by User on 25/11/2022.
//

#ifndef DATA_STRUCTRS_WET1_LISTNODE_H
#define DATA_STRUCTRS_WET1_LISTNODE_H
#include "Node.h"

template<class T>
class ListNode : public Node<T>
{
private:
    ListNode<T> *m_prev;
    ListNode<T> *m_next;

public:
    ListNode() = default;
    ListNode(const T& value);
    ~ListNode() = default;
    ListNode<T>* getPrev();
    ListNode<T>* getNext();
    void setPrev(ListNode<T>* prevNode);
    void setNext(ListNode<T>* nextNode);
};

template<class T>
ListNode<T>::ListNode(const T& value): Node<T>(value), m_prev(nullptr), m_next(nullptr){}

template<class T>
ListNode<T> *ListNode<T>::getPrev()
{
    return this->m_prev;
}

template<class T>
ListNode<T> *ListNode<T>::getNext()
{
    return this->m_next;
}

template<class T>
void ListNode<T>::setPrev(ListNode<T> *prevNode)
{
    this->m_prev = prevNode;
}

template<class T>
void ListNode<T>::setNext(ListNode<T> *nextNode)
{
    this->m_next = nextNode;
}

#endif //DATA_STRUCTRS_WET1_LISTNODE_H
