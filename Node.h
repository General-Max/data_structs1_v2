
#ifndef EX1_NODE_H
#define EX1_NODE_H

template<class T>
class Node
{
protected:
    T *m_data;
public:  
    // Default constructor
    Node();
    // Parameterised Constructor
    explicit Node(const T& data);

    //should be virtual?
    ~Node();
    
    T* getData();

    void setData(T* data);
};

template<class T>
Node<T>::Node(): m_data(nullptr){ }
  
    // Parameterised Constructor
template<class T>
Node<T>::Node(const T& data): m_data(new T(data)) {};

template <class T>
Node<T>::~Node()
{
    delete this->m_data;
    this->m_data = nullptr;
}

template<class T>
T* Node<T>::getData()
{
    return this->m_data;
}

template<class T>
void Node<T>::setData(T *data)
{
    this->m_data=data;
}

#endif //EX1_NODE_H
