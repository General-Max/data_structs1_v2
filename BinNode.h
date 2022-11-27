
#ifndef EX1_BINNODE_H
#define EX1_BINNODE_H

#include "Node.h"

template<class T>
class BinNode : public Node<T>
{
private:
    BinNode<T> *m_right;
    BinNode<T> *m_left;
    BinNode<T> *m_father;
    int m_height;

public:
    explicit BinNode<T>(const T& value);
    ~BinNode<T>() = default;
    BinNode<T>* getLeft() const;
    BinNode<T>* getRight() const;
    BinNode<T>* getFather() const;
    int getHeight() const;

    void setLeft(BinNode<T>* newLeft);
    void setRight(BinNode<T>* newRight);
    void setFather(BinNode<T>* newFather);
    void setHeight(int newHeight);

};

template<class T>
BinNode<T>::BinNode(const T& value): Node<T>(value), m_father(nullptr), m_left(nullptr), m_right(nullptr),
        m_height(0){ }

template <class T>
BinNode<T>* BinNode<T>::getLeft() const
{
    return this->m_left;
}

template <class T>
BinNode<T>* BinNode<T>::getRight() const
{
    return this->m_right;
}

template <class T>
BinNode<T>* BinNode<T>::getFather() const
{
    return this->m_father;
}

template <class T>
int BinNode<T>::getHeight() const
{
    return this->m_height;
}

template <class T>
void BinNode<T>::setLeft(BinNode<T>* newLeft)
{
    this->m_left = newLeft;
}

template <class T>
void BinNode<T>::setRight(BinNode<T>* newRight)
{
    this->m_right=newRight;
}

template <class T>
void BinNode<T>::setFather(BinNode<T>* newFather)
{
    this->m_father = newFather;
}

template <class T>
void BinNode<T>::setHeight(int newHeight)
{
    this->m_height = newHeight;
}

#endif //EX1_BINNODE_H

