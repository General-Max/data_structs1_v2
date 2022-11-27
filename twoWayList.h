//
// Created by User on 25/11/2022.
//

#ifndef DATA_STRUCTRS_WET1_TWOWAYLIST_H
#define DATA_STRUCTRS_WET1_TWOWAYLIST_H
#include "ListNode.h"
#include <iostream>
#include "SortByScore.h"

template<class T>
class twoWayList{
private:
    ListNode<T>* m_head;
    SortByScore m_comparisonFunction;
    //   ListNode<T>* tail;
public:
    twoWayList();
    ~twoWayList();
//
    ListNode<T>* getHead();
//    ListNode<T>* getnext();
//
    void setHead(ListNode<T>* newHeadNode);
//    void setTail(ListNode<T>* newTailNode);

    void insertAfter(ListNode<T>* newNode, ListNode<T>* prevNode);
    void insertBefore(ListNode<T>* newNode, ListNode<T>* nextNode);
    void deleteNode(ListNode<T>* nodeToDelete);

    void printList();
};

template <class T>
twoWayList<T>::twoWayList(): m_head(nullptr) {}

template <class T>
twoWayList<T>::~twoWayList()
{
    ListNode<T>* toDelete = this->m_head;
    ListNode<T>* temp;
    while(toDelete!= nullptr){
        temp = toDelete->getNext();
        delete toDelete;
        toDelete = temp;
    }
}

template <class T>
void twoWayList<T>::insertAfter(ListNode<T>* newNode, ListNode<T>* prevNode)
{
    ListNode<T>* nextNode = prevNode->getNext();
    newNode->setNext(nextNode);
    prevNode->setNext(newNode);
    if(nextNode!=nullptr){
        nextNode->setPrev(newNode);
    }
    newNode->setPrev(prevNode);
}

template <class T>
void twoWayList<T>::insertBefore(ListNode<T>* newNode, ListNode<T> *nextNode)
{
    ListNode<T>* prevNode = nextNode->getPrev();
    if(prevNode){
        newNode->setNext(nextNode);
        prevNode->setNext(newNode);
        newNode->setPrev(prevNode);
        nextNode->setPrev(newNode);
    }
    else{
        this->m_head = newNode;
        newNode->setNext(nextNode);
        nextNode->setPrev(newNode);
    }
}

template <class T>
void twoWayList<T>::deleteNode(ListNode<T>* nodeToDelete)
{
    if(nodeToDelete == nullptr){
        std::cout<< "error in deleting node from a list" << std::endl;
    }
    ListNode<T>* prevNode = nodeToDelete->getPrev();
    ListNode<T>* nextNode = nodeToDelete->getNext();

    if(prevNode == nullptr){
        this->m_head = nextNode;
        nextNode->setPrev(nullptr);
    }
    else if(nextNode == nullptr){
        prevNode->setNext(nullptr);
    }
    else{
        prevNode->setNext(nextNode);
        nextNode->setPrev(prevNode);
    }

    delete nodeToDelete;
}

template<class T>
void twoWayList<T>::printList()
{
    std::cout << **this->m_head->getData() <<  "-> ";
    ListNode<T>* temp = this->m_head->getNext();
    while(temp != nullptr){
        std::cout << **temp->getData() <<  "-> ";
        temp = temp->getNext();
    }
    std::cout << std::endl;
}

template<class T>
void twoWayList<T>::setHead(ListNode<T> *newHeadNode) {
    this->m_head = newHeadNode;
}

template<class T>
ListNode<T> *twoWayList<T>::getHead() {
    return m_head;
}

#endif //DATA_STRUCTRS_WET1_TWOWAYLIST_H
