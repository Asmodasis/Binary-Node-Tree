
/*===============================================================================

FILE:              BinaryNodeTree.cpp

DESCRIPTION:       the Implementation file for the class BinaryNodeTree

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

#include "../headers/BinaryNodeTree.h"

/*=============================================================================
FUNCTION:          getHeightHelper()
DESCRIPTION:       Assistance function to help getting height of the tree
PRECONDITION:      the Pointer for the subtree
POSTCONDITION:     integer return value for the height
===============================================================================*/

template<typename dataType> 
int BinaryNodeTree<dataType>::getHeightHelper(std::shared_ptr<BinaryNode<dataType>> subTreePtr) const{ 

   if(subTreePtr == nullptr) 
      return 0; 
   else
      return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), 
                     getHeightHelper(subTreePtr->getRightChildPtr()));
}// end getHeightHelper 

/*=============================================================================
FUNCTION:          getNumberOfNodesHelper()
DESCRIPTION:       Assistance function to help getting the amount of Nodes in the tree
PRECONDITION:      the Pointer for the subtree
POSTCONDITION:     integer return value for the amount of nodes 
===============================================================================*/

template<typename dataType> 
int BinaryNodeTree<dataType>::getNumberOfNodesHelper(std::shared_ptr<BinaryNode<dataType>> subTreePtr) const{

   if (subTreePtr == nullptr)
      return 0;
   else
      return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + 
                 getNumberOfNodesHelper(subTreePtr->getRightChildPtr());

} // end getNumberOfNodesHelper

/*=============================================================================
FUNCTION:          destroyTree
DESCRIPTION:       destroys the tree from the specified node
PRECONDITION:      a pointer to the sub tree
POSTCONDITION:     None
===============================================================================*/

template<typename dataType> 
void BinaryNodeTree<dataType>::destroyTree(std::shared_ptr<BinaryNode<dataType>> subTreePtr){ 

   if(subTreePtr != nullptr){ 
       destroyTree(subTreePtr->getLeftChildPtr()); 
       destroyTree(subTreePtr->getRightChildPtr());

   }// end if
}// end destroyTree 

/*=============================================================================
FUNCTION:          balancedAdd()
DESCRIPTION:       add to the tree in a balanced fashion
PRECONDITION:      a pointer to sub tree, and new node
POSTCONDITION:     returned pointer to the sub ree
===============================================================================*/

template<typename dataType> 
std::shared_ptr<BinaryNode<dataType>> BinaryNodeTree<dataType>::balancedAdd(
                                                  std::shared_ptr<BinaryNode<dataType>> subTreePtr, 
                                                  std::shared_ptr<BinaryNode<dataType>> newNodePtr){ 
   
   if(subTreePtr == nullptr) 
      return newNodePtr; 
   else{ 
       std::shared_ptr<BinaryNode<dataType>> leftPtr = subTreePtr->getLeftChildPtr(); 
       std::shared_ptr<BinaryNode<dataType>> rightPtr = subTreePtr->getRightChildPtr(); 
      
      if(getHeightHelper(leftPtr) > getHeightHelper(rightPtr)){ 
            rightPtr = balancedAdd(rightPtr, newNodePtr); 
            subTreePtr->setRightChildPtr(rightPtr); 
      }else{ 
           leftPtr = balancedAdd(leftPtr, newNodePtr); 
           subTreePtr->setLeftChildPtr(leftPtr); 
      }// end if 
      return subTreePtr; 
   }  // end if 
}// end balancedAdd 

/*=============================================================================
FUNCTION:          removeValue()
DESCRIPTION:       removes the value from the tree
PRECONDITION:      a pointer to the sub tree and the target value
POSTCONDITION:     a returned pointer to the subtree
===============================================================================*/

template<typename dataType>
std::shared_ptr<BinaryNode<dataType>> BinaryNodeTree<dataType>::removeValue(std::shared_ptr<BinaryNode<dataType>> subTreePtr, const dataType target, bool& success){

       if (subTreePtr == nullptr) // not found here
          return nullptr;

       if (subTreePtr->getItem() == target){  // found it

              subTreePtr = moveValuesUpTree(subTreePtr);
              success = true;

              return subTreePtr;
        }else{

              std::shared_ptr<BinaryNode<dataType>> targetNodePtr = removeValue(
                                    subTreePtr->getLeftChildPtr(), target, success);

              subTreePtr->setLeftChildPtr(targetNodePtr);

              if (!success){ // no need to search right subTree

                     targetNodePtr = removeValue(subTreePtr->getRightChildPtr(),
                                                 target, success);

                     subTreePtr->setRightChildPtr(targetNodePtr);

              } // end if

              return subTreePtr;

       } // end if

} // end removeValue

/*=============================================================================
FUNCTION:          moveValuesUpTree()
DESCRIPTION:       moves the values up the tree 
PRECONDITION:      a pointer to the sub tree
POSTCONDITION:     a returned sub tree pointer
===============================================================================*/

template<typename dataType>
std::shared_ptr<BinaryNode<dataType>> BinaryNodeTree<dataType>::moveValuesUpTree(std::shared_ptr<BinaryNode<dataType>> subTreePtr){

      std::shared_ptr<BinaryNode<dataType>> leftPtr = subTreePtr->getLeftChildPtr();

      std::shared_ptr<BinaryNode<dataType>> rightPtr = subTreePtr->getRightChildPtr();

      int leftHeight = getHeightHelper(leftPtr);
      int rightHeight = getHeightHelper(rightPtr);

      if (leftHeight > rightHeight){

          subTreePtr->setItem(leftPtr->getItem());

          leftPtr = moveValuesUpTree(leftPtr);

          subTreePtr->setLeftChildPtr(leftPtr);

            return subTreePtr;
      }else{

            if (rightPtr != nullptr){

                     subTreePtr->setItem(rightPtr->getItem());

                     rightPtr = moveValuesUpTree(rightPtr);

                     subTreePtr->setRightChildPtr(rightPtr);

                      return subTreePtr;

              }else{

                     //this was a leaf!

                     // value not important


                     return nullptr;

              } // end if

       } // end if  

} // end moveValuesUpTree

/*=============================================================================
FUNCTION:          findNode()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>
std::shared_ptr<BinaryNode<dataType>> BinaryNodeTree<dataType>::findNode( std::shared_ptr<BinaryNode<dataType>> treePtr,
                                                          const dataType& target, bool& success) const{

       if(treePtr == nullptr) // not found here
            return nullptr;

       if(treePtr->getItem() == target){ // found it

              success = true;
                return treePtr;
        }else{

              std::shared_ptr<BinaryNode<dataType>> targetNodePtr = findNode(
                                                              treePtr->getLeftChildPtr() ,
                                                              target ,
                                                              success
                                                            );

              if(!success){ // no need to search right subTree

                     targetNodePtr = findNode(treePtr->getRightChildPtr(), target, success);

              } // end if

              return targetNodePtr;

       } // end if

} // end findNode

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType> 
std::shared_ptr<BinaryNode<dataType>> BinaryNodeTree<dataType>::copyTree(const std::shared_ptr<BinaryNode<dataType>> treePtr) const{ 
   
   std::shared_ptr<BinaryNode<dataType>> newTreePtr = nullptr; 

   // Copy tree nodes during a preorder traversal 
   if(treePtr != nullptr){ 
      // Copy node 
       newTreePtr = new BinaryNode<dataType>(treePtr->getItem(), nullptr,nullptr); 
       newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr())); 
       newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr())); 
   }// end if 

// Else tree is empty (newTreePtr is nullptr) 
   return newTreePtr;

} // end copyTree 

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>
void BinaryNodeTree<dataType>::preorder(void visit(dataType&),
                                        std::shared_ptr<BinaryNode<dataType>> treePtr) const{

       if (treePtr != nullptr){

              dataType theItem = treePtr->getItem();

              visit(theItem);

              preorder(visit, treePtr->getLeftChildPtr());

              preorder(visit, treePtr->getRightChildPtr());

       } // end if

} // end preorder

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>
void BinaryNodeTree<dataType>::inorder(void visit(dataType&),
                                       std::shared_ptr<BinaryNode<dataType>> treePtr) const{

       if (treePtr != nullptr){

              inorder(visit, treePtr->getLeftChildPtr());

              dataType theItem = treePtr->getItem();

              visit(theItem);

              inorder(visit, treePtr->getRightChildPtr());

       } // end if

} // end inorder

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>
void BinaryNodeTree<dataType>::postorder(void visit(dataType&),
                                         std::shared_ptr<BinaryNode<dataType>> treePtr) const{

       if (treePtr != nullptr){

              postorder(visit, treePtr->getLeftChildPtr());

              postorder(visit, treePtr->getRightChildPtr());

              dataType theItem = treePtr->getItem();

              visit(theItem);

       } // end if

} // end postorder

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType> 
BinaryNodeTree<dataType>::BinaryNodeTree() : rootPtr(nullptr) { 
} // end default constructor 

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/
  
template<typename dataType> 
BinaryNodeTree<dataType>::BinaryNodeTree(const dataType& rootItem){ 
   rootPtr =  std::make_shared<BinaryNode<dataType>>(rootItem, nullptr, nullptr); 
} // end constructor 

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType> 
BinaryNodeTree<dataType>::BinaryNodeTree(const dataType& rootItem, 
                                         const BinaryNodeTree<dataType>* leftTreePtr, 
                                         const BinaryNodeTree<dataType>* rightTreePtr){ 
   
   rootPtr = std::make_shared<BinaryNode<dataType>>(rootItem, 
                                      copyTree(leftTreePtr->rootPtr), 
                                      copyTree(rightTreePtr->rootPtr)); 
}// end constructor 

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType> 
BinaryNodeTree<dataType>::BinaryNodeTree(const BinaryNodeTree<dataType>& treePtr){ 
   rootPtr = copyTree(treePtr.rootPtr); 
}// end copy constructor 

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType> 
BinaryNodeTree<dataType>::~BinaryNodeTree(){
   destroyTree(rootPtr);                     // destroy the tree from the root
} // end destructor

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType> 
bool BinaryNodeTree<dataType>::isEmpty() const{

    return rootPtr == nullptr;

} // end isEmpty

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType> 
int BinaryNodeTree<dataType>::getHeight() const{
      return getHeightHelper(rootPtr); 
} // end getHeight

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType> 
int BinaryNodeTree<dataType>::getNumberOfNodes() const{
      return getNumberOfNodesHelper(rootPtr);
} // end getNumberOfNodes

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>
dataType BinaryNodeTree<dataType>::getRootData() const{ //throw(PrecondViolatedExcept){

    if(this->isEmpty()){                                       // if tree is empty                               
          throw PrecondViolatedExcept("getRootData() called on an empty tree.");
    }else{                                               // tree is not empty

      return rootPtr->getItem();                         // then  return the item on the root
    }
}

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>
void BinaryNodeTree<dataType>::setRootData(const dataType& newData){

  if(this->isEmpty()){                                   // if tree is empty
    rootPtr = std::make_shared<BinaryNode<dataType>>(newData, nullptr, nullptr); // create a new tree

  }else{                                                 // tree is not empty

    rootPtr->setItem(newData);                           // then assign it a value
  } 

} // end setRootData

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType> 
bool BinaryNodeTree<dataType>::add(const dataType& newData){ 
   
   std::shared_ptr<BinaryNode<dataType>> newNodePtr = std::make_shared<BinaryNode<dataType>>(newData); 
   
   rootPtr = balancedAdd(rootPtr, newNodePtr); 

   return true; 
}// end add 

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>
bool BinaryNodeTree<dataType>::remove(const dataType& target){

       bool isSuccessful = false;

       rootPtr = removeValue(rootPtr, target, isSuccessful);

       return isSuccessful;

} // end remove

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>
void BinaryNodeTree<dataType>::clear(){

       destroyTree(rootPtr);

       rootPtr = nullptr;

} // end clear

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>
dataType BinaryNodeTree<dataType>::getEntry(const dataType& anEntry) const { //throw(NotFoundException)


       bool isSuccessful = false;

       std::shared_ptr<BinaryNode<dataType>> binaryNodePtr = findNode(rootPtr,
                                                      anEntry, isSuccessful);

       if (isSuccessful)
              return binaryNodePtr->getItem();

       else
              throw NotFoundException("Entry not found in tree!");

} // end getEntry

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>  // TODO: REQUIRES TESTING 
bool BinaryNodeTree<dataType>::contains(const dataType& anEntry) const{

    bool isSuccessful = false;

      std::shared_ptr<BinaryNode<dataType>> binaryNodePtr = findNode(rootPtr,
                                                      anEntry, isSuccessful);
                                                        // find the node, from the root to the entry
                                                        // if not found, nullptr returned
      return (anEntry == binaryNodePtr->getItem());     // get the item and test it's value
 
   }

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>
void BinaryNodeTree<dataType>::preorderTraverse(void visit(dataType&)) const{
        
        preorder(visit, rootPtr);

} // end preorderTraverse

/*=============================================================================
FUNCTION:          name-of-function()
DESCRIPTION:       A brief description of this function ...
PRECONDITION:
POSTCONDITION:
===============================================================================*/

template<typename dataType>
void BinaryNodeTree<dataType>::inorderTraverse(void visit(dataType&)) const{

       inorder(visit, rootPtr);

} // end inorderTraverse

template<typename dataType>
void BinaryNodeTree<dataType>::postorderTraverse(void visit(dataType&)) const{

       postorder(visit, rootPtr);

} // end postorderTraverse

template<typename dataType>
BinaryNodeTree<dataType>& BinaryNodeTree<dataType>::operator=(
                                const BinaryNodeTree<dataType>& rightHandSide){

       if (!isEmpty())
            clear();

       this = copyTree(&rightHandSide);

        return *this;

} // end operator=