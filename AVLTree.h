//
// Created by User on 22/11/2022.
//

#ifndef EX1_AVLTREE_H
#define EX1_AVLTREE_H

#include <iostream>
#include "BinNode.h"

template<class T, class Comparison>
class AVLTree {
private:
    // Tree fields
//    struct Node {
//        Node *m_right;
//        Node *m_left;
//        Node *m_father;
//        int m_height;
//        T *m_value;
//    };
    BinNode<T> *m_root;
    BinNode<T> *m_minValueNode; // in order to find the minimum value in tree in O(1)
    BinNode<T> *m_maxValueNode; // in order to find the maximum value in tree in O(1)
    int m_size;
    Comparison comparisonFunction;

    // Node Functions
    BinNode<T> *initNode(const T &data);

    BinNode<T> *balanceTree(BinNode<T> *node);

    BinNode<T> *insertNode(BinNode<T> *newNode, BinNode<T> *currentNode, BinNode<T> *father);

    BinNode<T> *findNode(BinNode<T> *node, const T &data);

    BinNode<T> *findNode(BinNode<T> *node, int id);

    BinNode<T> *removeNode(BinNode<T> *currentNode, BinNode<T> *nodeToDelete);

    int getBalanceFactor(BinNode<T> *node) const;

    int height(const BinNode<T> *node) const;

    int findNewHeight(const BinNode<T> *node) const;

    // Rotation Functions
    BinNode<T> *leftLeftRotation(BinNode<T> *node);

    BinNode<T> *leftRightRotation(BinNode<T> *node);

    BinNode<T> *rightLeftRotation(BinNode<T> *node);

    BinNode<T> *rightRightRotation(BinNode<T> *node);

    // Constructor, Destructor helper functions
    // TODO:: replace it becuse now node is class
    BinNode<T>* copyNode(BinNode<T> *node);

    void empty_aux(BinNode<T> *node);

    BinNode<T>* findMin(BinNode<T>* node) const;

    BinNode<T>* findMax(BinNode<T>* node) const;

    T* getMinValueInTree() const;

    T* getMaxValueInTree() const;


public:
    // Constructors, Destructor, Assignment
    AVLTree();

    AVLTree(const AVLTree<T, Comparison> &tree);

    AVLTree &operator=(const AVLTree<T, Comparison> &tree);

    ~AVLTree();

    // Interface Functions
    void insert(const T &data);

    bool find(const T &data);

    BinNode<T> * find(int id);

    void remove(const T &data);

    void remove(int idOfNodeToDelete);

    int getHeight() const;

    int getSize() const;

    BinNode<T>* getRoot() const;

    void emptyTree();

    bool isEmpty() const;

    void printH(BinNode<T> *node, int space);

    void printD(BinNode<T> *node, int space);
};

template<class T, class Comparison>
AVLTree<T, Comparison>::AVLTree() : m_root(nullptr), m_minValueNode(nullptr), m_maxValueNode(nullptr), m_size(0) {
}

template<class T, class Comparison>
AVLTree<T, Comparison>::~AVLTree(){
    emptyTree();
}

template<class T, class Comparison>
AVLTree<T, Comparison>& AVLTree<T, Comparison>::operator=(const AVLTree<T, Comparison> &tree){
    // TODO: ADD CHECK IF SUCCEED BEFORE EMPTY
    if(&tree == this){
        return *this;
    }
    emptyTree();
    m_root = copyNode(tree.getRoot());
    m_minValueNode = findMin(m_root);
    m_maxValueNode = findMax(m_root);
    m_size = tree.getSize();
    return *this;
}

template<class T, class Comparison>
AVLTree<T, Comparison>::AVLTree(const AVLTree<T, Comparison>& tree):m_root(nullptr), m_minValueNode(nullptr), m_maxValueNode(nullptr),
                                                                    m_size(tree.getSize()){
    // todo: check if can be added to the comprehension list
    m_root = copyNode(tree.getRoot());
    m_minValueNode = findMin(m_root);
    m_maxValueNode = findMax(m_root);
}


template<class T, class Comparison>
void AVLTree<T, Comparison>::insert(const T& data) {
    if (&data == nullptr) {
        return;
    }
    if (findNode(m_root, data) != nullptr) {
        std::cout << "throw NodeExists()";
    }

    auto *node = new BinNode<T>(data);

    m_root = insertNode(node, m_root, nullptr);
    // update minimum and maximum tree nodes
    m_minValueNode = findMin(m_root);
    m_maxValueNode = findMax(m_root);
    m_size++;
}

template<class T, class Comparison>
bool AVLTree<T, Comparison>::find(const T& data){
    BinNode<T>* node = findNode(m_root, data);
    if(node == nullptr){
        return false;
    }
    return true;
}


template<class T, class Comparison>
BinNode<T> * AVLTree<T, Comparison>::find(int id){
    BinNode<T>* node = findNode(m_root, id);
    if(node == nullptr){
        return nullptr;
    }
    return node;
}

template<class T, class Comparison>
void AVLTree<T, Comparison>::remove(const T& data) {
    if (isEmpty() || &data == nullptr) {
        return;
    }
    BinNode<T>* node_to_remove = findNode(m_root, data);

    if (node_to_remove == nullptr) {
        std::cout << "throw NodeDoesntExist()";
    }

    m_root = removeNode(node_to_remove, m_root);
    // m_root = removeNode(m_root, node_to_remove);
    // update minimum and maximum tree nodes
    m_minValueNode = findMin(m_root);
    m_maxValueNode = findMax(m_root);
    m_size--;
}

template<class T, class Comparison>
void AVLTree<T, Comparison>::remove(int idOfNodeToDelete) {
    if (isEmpty()) {
        return;
    }
    BinNode<T>* nodeToRemove = findNode(m_root, idOfNodeToDelete);

    if (nodeToRemove == nullptr) {
        std::cout << "throw NodeDoesntExist()";
    }

    m_root = removeNode(nodeToRemove, m_root);
    // update minimum and maximum tree nodes
    m_minValueNode = findMin(m_root);
    m_maxValueNode = findMax(m_root);
    m_size--;
}

template<class T, class Comparison>
void AVLTree<T, Comparison>::empty_aux(BinNode<T>* node) {
    if(node == nullptr){
        return;
    }

    if(node->getLeft()){
        empty_aux(node->getLeft());
    }
    if(node->getRight()){
        empty_aux(node->getRight());
    }
    delete node;
}

template<class T, class Comparison>
void AVLTree<T, Comparison>::emptyTree() {
    if(m_size > 0){
        empty_aux(m_root);
        m_root = nullptr;
        m_minValueNode = nullptr;
        m_maxValueNode = nullptr;
        m_size = 0;
    }
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::getHeight()const{
    if (m_root == nullptr) {
        return 0;
    }
    return m_root->m_height;
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::getSize() const{
    return m_size;
}

template<class T, class Comparison>
bool AVLTree<T, Comparison>::isEmpty() const{
    return m_size == 0;
}

template <class T, class Comparison>
void AVLTree<T, Comparison>::printD(BinNode<T> *node, int space){
    if(node==nullptr)
        return;
    space += 10;
    printD(node->getRight(), space);
    std::cout << std::endl;
    for(int i= 10; i<space; i++){
        std::cout << " ";
    }
    std::cout << **node->getData() << "\n";
    printD(node->getLeft(), space);
}

template <class T, class Comparison>
void AVLTree<T, Comparison>::printH(BinNode<T> *node, int space){
    if(node==nullptr)
        return;
    space += 10;
    printH(node->getRight(), space);
    std::cout << std::endl;
    std::cout << **node->getData() << ": "<< node->getHeight() << "\n";
    printH(node->getLeft(), space);
}

template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::getRoot() const {
    return m_root;
}

template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::initNode(const T &data) {
    BinNode<T>* node = new BinNode<T>();
    node->setData(new T(data));
    node->setHeight(0);
    node->setLeft(nullptr);
    node->setRight(nullptr);
    node->setFather(nullptr);
    return node;
}

template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::balanceTree(BinNode<T> *node) {
    int balanceFactor = getBalanceFactor(node);
    int leftBalanceFactor = getBalanceFactor(node->getLeft());
    int rightBalanceFactor = getBalanceFactor(node->getRight());

    // Left-Left imbalance
    if(balanceFactor > 1 && leftBalanceFactor > -1){
        return leftLeftRotation(node);
    }

        // Right-Right imbalance
    else if(balanceFactor < -1 && rightBalanceFactor < 1){
        return rightRightRotation(node);
    }

        // Left-Right imbalance
    else if(balanceFactor > 1 && leftBalanceFactor == -1){
        return leftRightRotation(node);
    }

        // Right-Left imbalance
    else if(balanceFactor < -1 && rightBalanceFactor == 1){
        return rightLeftRotation(node);
    }

    node->setHeight(findNewHeight(node));
    return node;
}

template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::insertNode(BinNode<T>  *newNode, BinNode<T> *currentNode,
                                               BinNode<T> *father){
    if (currentNode == nullptr) {
        newNode->setFather(father);
        return newNode;
    }
    if(comparisonFunction.lessThan(*newNode->getData(), *currentNode->getData())){
        currentNode->setLeft(insertNode(newNode, currentNode->getLeft(), currentNode));
    } else {
        currentNode->setRight(insertNode(newNode, currentNode->getRight(), currentNode));
    }
    return balanceTree(currentNode);
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::findNewHeight(const BinNode<T> *node) const {
    if(height(node->getRight()) > height(node->getLeft())){
        return height(node->getRight())+1;
    }
    return height(node->getLeft())+1;
}

template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::findNode(BinNode<T> *node, const T &data) {
    if(node == nullptr)
        return nullptr;
    if (comparisonFunction.equalTo(data, *node->getData())) {
        return node;
    } else {
        if(comparisonFunction.lessThan(*node->getData(), data)){
            return findNode(node->getRight(), data);
        } else {
            return findNode(node->getLeft(), data);
        }
    }
}

template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::findNode(BinNode<T> *node, int id) {
    if(node == nullptr)
        return nullptr;
    if (comparisonFunction.equalTo(*(node->getData()), id)) {
        return node;
    } else {
        if(comparisonFunction.lessThan(*node->getData(), id)){
            return findNode(node->getRight(), id);
        } else {
            return findNode(node->getLeft(), id);
        }
    }
}


template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::removeNode(BinNode<T> *currentNode, BinNode<T> *nodeToDelete){
    if (currentNode == nullptr) {
        return nullptr;
    }
    // Delete the node
    if (*currentNode->getData() == *nodeToDelete->getData()) {
        if (!nodeToDelete->getRight() && !nodeToDelete->getLeft()) {
            // Leaf
            delete nodeToDelete;
            return nullptr;
        } else if (!nodeToDelete->getRight()) {
            // Only left son
            BinNode<T>* temp = nodeToDelete->getLeft();
            nodeToDelete->setData(new T(*temp->getData()));
            nodeToDelete->setLeft(removeNode(nodeToDelete, nodeToDelete->getLeft()));

        } else if (!nodeToDelete->getLeft()) {
            // Only right son
            BinNode<T>* temp = nodeToDelete->getRight();
            nodeToDelete->setData(new T(*temp->getData()));
            nodeToDelete->setRight(removeNode(nodeToDelete, nodeToDelete->getRight()));
        } else {
            // right and left son exist
            BinNode<T> *temp = findMin(nodeToDelete->getRight());
            nodeToDelete->setData(new T(*temp->getData()));
            nodeToDelete->setRight(removeNode(nodeToDelete, nodeToDelete->getRight()));
        }

    }
    else{
        T p1 = *currentNode->getData();
        T p2 = *nodeToDelete->getData();
        if (comparisonFunction.lessThan(p1,p2)) {
            nodeToDelete->setLeft(removeNode(currentNode, nodeToDelete->getLeft()));
        } else {
            nodeToDelete->setRight(removeNode(currentNode, nodeToDelete->getRight()));
        }
    }

    nodeToDelete->setHeight(findNewHeight(nodeToDelete));

    // Balancing the tree
    return balanceTree(nodeToDelete);
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::getBalanceFactor(BinNode<T> *node) const {
    return node == nullptr ? -1 : (height(node->getLeft()) - height(node->getRight()));
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::height(const BinNode<T>* node) const{
    return node == nullptr ? -1 : node->getHeight();
}

template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::leftLeftRotation(BinNode<T> *node) {
    BinNode<T> *leftSubtree = node->getLeft();
    leftSubtree->setFather(node->getFather());
    node->setFather(leftSubtree);
    if(leftSubtree->getRight()){
        (leftSubtree->getRight())->setFather(node);
    }
    node->setLeft(node->getFather()->getRight());
    (node->getFather())->setRight(node);
    node->setHeight(findNewHeight(node));
    if(node->getFather()) {
        (node->getFather())->setHeight(findNewHeight(node->getFather()));
    }
    return node->getFather();
}

template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::rightRightRotation(BinNode<T> *node) {
    BinNode<T> *subTreeRight = node->getRight();
    (node->getRight())->setFather(node->getFather());
    node->setFather(subTreeRight);
    node->setRight(node->getFather()->getLeft());
    if(node->getRight())
        (node->getRight())->setFather(node);
    (node->getFather())->setLeft(node);

    node->setHeight(findNewHeight(node));
    if(node->getFather()){
        (node->getFather())->setHeight(findNewHeight(node));
    }

    return node->getFather();
}

template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::rightLeftRotation(BinNode<T> *node) {
    node->setRight(leftLeftRotation(node->getRight()));
    return rightRightRotation(node);
}

template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::leftRightRotation(BinNode<T> *node) {
    node->setLeft(rightRightRotation(node->getLeft()));
    return leftLeftRotation(node);
}

template<class T, class Comparison>
BinNode<T> *AVLTree<T, Comparison>::copyNode(BinNode<T>* node) {
    if(node == nullptr){
        return nullptr;
    }
    BinNode<T>* left = copyNode(node->getLeft());
    BinNode<T>* right = copyNode(node->getRight());

    BinNode<T>* new_node = initNode(*node->getData());
//    new_node->father = node->father;
    new_node->setLeft(left);
    if(new_node->setLeft())
        (new_node->getLeft())->setFather(new_node);
    new_node->setRight(right);
    if(new_node->getRight())
        (new_node->getRight())->setFather(new_node);
    new_node->setHeight(findNewHeight(new_node));
    return new_node;
}

template<class T, class Comparison>
BinNode<T>* AVLTree<T, Comparison>::findMin(BinNode<T>* node) const{
    if (node == nullptr) {
        return nullptr;
    }
    if (!node->getLeft()) {
        return node;
    }

    return findMin(node->getLeft());
}

template<class T, class Comparison>
BinNode<T>* AVLTree<T, Comparison>::findMax(BinNode<T>* node) const{
    if (node == nullptr) {
        return nullptr;
    }
    if (node->getRight() == nullptr) {
        return node;
    }

    return findMax(node->getRight());
}

template<class T, class Comparison>
T *AVLTree<T, Comparison>::getMinValueInTree() const {
    return m_minValueNode->getData();
}

template<class T, class Comparison>
T *AVLTree<T, Comparison>::getMaxValueInTree() const {
    return m_maxValueNode->getData();
}


#endif //EX1_AVLTREE_H