
/*===============================================================================

FILE:              BinarySearchTree.cpp

DESCRIPTION:       the Implementation file for the class BinarySearchTree

COMPILER:          Linux g++ compiler


ACCREDITATION:     Credit given to Frank M. Carrano and Timothy Henry with their work
                    on the book Data Abstraction & Problem Solving with c++, code was 
                    presented in the book as either working functions or psuedocode, where I
                    built the functions based off the psuedocode.

                  Also Credit to Dr. Kostas Alexis as the Professor of the course CS302 (Data Structures)
                  at the University of Nevada Reno, who presented this material to his students.

MODIFICATION HISTORY:

Author                  Date               Version
================================================================================
Shawn Ray               2018-11-29         Version 1.0

================================================================================*/

#include <memory>

#include "../headers/BinarySearchTree.h"
#include "../headers/BinaryNodeTree.h"
#include "../headers/BinaryNode.h"

template<typename dataType>
std::shared_ptr<BinaryNode<dataType>> BinarySearchTree<dataType>::insertInorder(std::shared_ptr<BinaryNode<dataType>> subTreePtr,
                                                                std::shared_ptr<BinaryNode<dataType>> newNode){
    std::shared_ptr<BinaryNode<dataType>> tempPtr = nullptr;

    if(subTreePtr == nullptr)
        return newNode;
    else if (subTreePtr->getItem() > newNode->getItem()){  
            // if the item from subTreePtr is bigger, then it goes left                         

        tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNode);
        subTreePtr->setLeftChildPtr(tempPtr);
    }else{
            // else it is smaller and indeed goes right
        tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNode);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template<typename dataType>
std::shared_ptr<BinaryNode<dataType>> BinarySearchTree<dataType>::removeValue(std::shared_ptr<BinaryNode<dataType>> subTreePtr,
                                                                const dataType target,
                                                                bool& success){

        if(subTreePtr == nullptr){

            success = false;
            return nullptr;

        }else if(subTreePtr->getItem() == target){
            // Item is in the root of some subtree

            subTreePtr = removeNode(subTreePtr);                                    // remove the item
            success = true;                                                         // it has been found
                return subTreePtr;

        }else if(subTreePtr->getItem() > target){
            // search the left subtree
            
            // temp Binary Node for containing the subtree
            std::shared_ptr<BinaryNode<dataType>> tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
            subTreePtr->setLeftChildPtr(tempPtr);
                

                return subTreePtr;

        }else{
            // search the right subtree

            // temp Binary Node for containing the subtree
            std::shared_ptr<BinaryNode<dataType>> tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
            subTreePtr->setRightChildPtr(tempPtr);
                

                return subTreePtr;

        }
} // end removeValue

template<typename dataType>
std::shared_ptr<BinaryNode<dataType>> BinarySearchTree<dataType>::removeNode(std::shared_ptr<BinaryNode<dataType>> nodePtr){

    std::shared_ptr<BinaryNode<dataType>> nodeToConnectPtr = nullptr;
    dataType newNodeValue = (dataType) 0;                                            // create a temp location for
                                                                                     // for the swapping in cases of 2 childs

    if(nodePtr->isLeaf()){                                                           // node is a leaf

        nodePtr = nullptr;
            return nodePtr;                                                          // return  the nullptr

    }else if(nodePtr->getLeftChildPtr() == nullptr || nodePtr->getRightChildPtr() == nullptr){
                       // if nodePtr has only one child
                       // if either left or right is nullptr
                       // then there is only one child
        
        //std::shared_ptr<BinaryNode<dataType>> parentPtr = 

        if(nodePtr->getLeftChildPtr() != nullptr)                                   // then a left exists
            nodeToConnectPtr = nodePtr->getLeftChildPtr();
        else                                                                       // else a right exists
            nodeToConnectPtr = nodePtr->getRightChildPtr();

        nodePtr = nullptr;
        return nodeToConnectPtr;

    }else{              // Then the node has two children
                        // find the Inorder successor of the entry in nodePtr
                        // it is in the left subtree rooted at nodePtr's right child
            std::shared_ptr<BinaryNode<dataType>> tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue);
            nodePtr->setRightChildPtr(tempPtr);
            nodePtr->setItem(newNodeValue);                                         // put replacement value in nodePtr
            return nodePtr;
    }

} // end removeNode

//Removes the leftmost node in the left subtree of the node pointed to by nodePtr
//Sets inorderSuccessor to the value in this node.
//Returns a pointer to the revised subtree

template<typename dataType>
std::shared_ptr<BinaryNode<dataType>> BinarySearchTree<dataType>::removeLeftmostNode(std::shared_ptr<BinaryNode<dataType>> subTreePtr,
                                                                        dataType& inorderSuccessor){
    if(subTreePtr->getLeftChildPtr() == nullptr){

        // This is the node you want, it has no left child but it might have a right subtree
        inorderSuccessor = subTreePtr->getItem();
        return this->removeNode(subTreePtr);
    }else
        return this->removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);

} // end removeLeftmostNode


template<typename dataType>
std::shared_ptr<BinaryNode<dataType>> BinarySearchTree<dataType>::findNode(std::shared_ptr<BinaryNode<dataType>> treePtr,
                                    const dataType& target) const{
    if(treePtr == nullptr){
        return nullptr;
    }else if(treePtr->getItem() == target){                                         // found it
        return treePtr;
    }else if(treePtr->getItem() > target){                                          // search the left subtree
        return findNode(treePtr->getLeftChildPtr(), target);
    }else {
        return findNode(treePtr->getRightChildPtr(), target);                       // search the right subtree
    }

} // end findNode


template<typename dataType>
BinarySearchTree<dataType>::BinarySearchTree() : rootPtr(nullptr) {  //: BinaryNodeTree<dataType>::BinaryNodeTree(){
}

template<typename dataType>
BinarySearchTree<dataType>::BinarySearchTree(const dataType& rootItem) //: BinaryNodeTree<dataType>::BinaryNodeTree(rootItem)
{
    this->rootPtr = std::make_shared<BinaryNode<dataType>>(rootItem, nullptr, nullptr);
}

template<typename dataType>
BinarySearchTree<dataType>::BinarySearchTree(const BinarySearchTree<dataType>& tree) //: BinaryNodeTree<dataType>::BinaryNodeTree(tree)
{
    this->rootPtr = this->copyTree(tree.rootptr);                                         // calls copyTree from BinaryNodeTree
}

template<typename dataType>
BinarySearchTree<dataType>::~BinarySearchTree(){

    this->destroyTree(this->rootPtr);                                              // calls destroyTree from BinaryNodeTree



}


template<typename dataType>
bool BinarySearchTree<dataType>::isEmpty() const{

    return rootPtr == nullptr;                                                      //  tests if it is nullptr
                                                                                    
} // end isEmpty


template<typename dataType>
int BinarySearchTree<dataType>::getHeight() const{

   return BinaryNodeTree<dataType>::getHeightHelper(rootPtr);                       // calls the inherited getHeightHelper
                                                                                    // from BinaryNodeTree
} // end getHeight


template<typename dataType>
int BinarySearchTree<dataType>::getNumberOfNodes() const{

   return BinaryNodeTree<dataType>::getNumberOfNodesHelper(this->rootPtr);                                                 // calls the inherited getNumberOfNodesHelper
                                                                                    // from BinaryNodeTree
} // end getNumberOfNodes

template<typename dataType>
dataType BinarySearchTree<dataType>::getRootData() const{ //throw(PrecondViolatedExcept){

    if(isEmpty()){                                       // if tree is empty                               
          throw PrecondViolatedExcept("Violation: no Root Node available.");
    }else{                                               // tree is not empty

      return rootPtr->getItem();                         // then  return the item on the root
    }
} // end getRootData


template<typename dataType>
void BinarySearchTree<dataType>::setRootData(const dataType& newData) const{ //throw(PrecondViolatedExcept){

  throw PrecondViolatedExcept("Violation: Root Data in a Binary Search Tree can not be modified.");                                                     
                                                                                   
} // end setRootData


template<typename dataType>
bool BinarySearchTree<dataType>::add(const dataType& newEntry){

    std::shared_ptr<BinaryNode<dataType>> newNode = std::make_shared<BinaryNode<dataType>>(newEntry);             // create a new node based off the entry
                                                                                    // passed as a parameter
    this->rootPtr = this->insertInorder(this->rootPtr, newNode);                    // insert in order, the new node, from the root

        return true;                                                                // adding a node to a linked list is always
                                                                                    // applicable, so it's always true                                                  

} // end add


template<typename dataType>
bool BinarySearchTree<dataType>::remove(const dataType& anEntry){

    bool isSuccessful = false;                                                      // can we remove a value?
    this->rootPtr = this->removeValue(this->rootPtr, anEntry, isSuccessful);        // remove it if it exists

    return isSuccessful;                                                            // return the result of the removal test

} // end remove

template<typename dataType>
void BinarySearchTree<dataType>::clear(){

    BinaryNodeTree<dataType>::destroyTree(this->rootPtr);                           // calls the inherited destroyTree
                                                                                    // from BinaryNodeTree
    rootPtr = nullptr;
} // end clear

template<typename dataType>
dataType BinarySearchTree<dataType>::getEntry(const dataType& anEntry) const{ //throw(NotFoundException){

   std::shared_ptr<BinaryNode<dataType>> foundNode = this->findNode(this->rootPtr, anEntry);        // look for the node

   if(!foundNode)                                                                   // if(node was not found)
        throw NotFoundException("The Entry was not Found within this Tree.");       // item was not found
   else
    return foundNode->getItem();                                                    // return the found item
} // end getEntry


template<typename dataType>
bool BinarySearchTree<dataType>::contains(const dataType& anEntry) const{

   if(this->findNode(this->rootPtr, anEntry)){
    return true;
   }
   else 
        return false;                                   
                                                                                    // then it's false
} // end contains


template<typename dataType>
void BinarySearchTree<dataType>::preorderTraverse(void visit(dataType&)) const{

   this->preorder(visit, rootPtr);                                                  // calls the inherited preorder
                                                                                    // from BinaryNodeTree
} // end preorderTraverse                                                            


template<typename dataType>
void BinarySearchTree<dataType>::inorderTraverse(void visit(dataType&)) const{

   this->inorder(visit, rootPtr);                                                   // calls the inherited inorder
                                                                                     // from BinaryNodeTree
} // end inorderTraverse                                                            

template<typename dataType>
void BinarySearchTree<dataType>::postorderTraverse(void visit(dataType&)) const{

   this->postorder(visit, rootPtr);                                                  // calls the inherited postorder
                                                                                     // from BinaryNodeTree
} // end postorderTraverse


template<typename dataType>
BinarySearchTree<dataType>& BinarySearchTree<dataType>::operator=(const BinarySearchTree<dataType>& rightHandSide){

    if(!this->isEmpty())                                                              // if not empty then clear
        this->clear();
    this = copyTree(&rightHandSide);                                                  // copyTree from BinaryNodeTree

        return *this;                                                                 // return the object inherent to the function
} // end operator = 