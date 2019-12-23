
/*===============================================================================

FILE:              xxx.CPP or xxx.HPP

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

#include <cstddef>
#include <memory>

#include "../headers/BinaryNode.h"

/*=============================================================================
FUNCTION:          BinaryNode()
DESCRIPTION:       Default constructor
PRECONDITION:      None
POSTCONDITION:     None
===============================================================================*/

template<typename dataType>
BinaryNode<dataType>::BinaryNode() 
                       : item(nullptr), leftChildPtr(nullptr), rightChildPtr(nullptr){

} // end default constructor

/*=============================================================================
FUNCTION:          BinaryNode(const dataType& anItem)
DESCRIPTION:       Overloaded constructor
PRECONDITION:      pass an Item to enter into the node
POSTCONDITION:     None
===============================================================================*/

template<typename dataType>
BinaryNode<dataType>::BinaryNode(const dataType& anItem)
                       : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr){

} // end constructor

/*=============================================================================
FUNCTION:          BinaryNode(const dataType& anItem,
                                 std::shared_ptr<BinaryNode<dataType>> leftPtr,
                                 std::shared_ptr<BinaryNode<dataType>> rightPtr)
DESCRIPTION:       Overloaded contructor
PRECONDITION:      Passed an Item, Left and Right node pointer 
POSTCONDITION:     None
===============================================================================*/

template<typename dataType>
BinaryNode<dataType>::BinaryNode(const dataType& anItem,
                                 std::shared_ptr<BinaryNode<dataType>> leftPtr,
                                 std::shared_ptr<BinaryNode<dataType>> rightPtr)
                                 : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr){

} // end constructor

/*=============================================================================
FUNCTION:          setItem()
DESCRIPTION:       sets the item inside a Node
PRECONDITION:      passed an Item to enter into the node
POSTCONDITION:     None
===============================================================================*/

template<typename dataType>
void BinaryNode<dataType>::setItem(const dataType& anItem){
        
      item = anItem;

} // end setItem

/*=============================================================================
FUNCTION:          getItem()
DESCRIPTION:       gets the item within the node
PRECONDITION:      None
POSTCONDITION:     a returned dataType item for item inside
===============================================================================*/

template<typename dataType>
dataType BinaryNode<dataType>::getItem() const{

       return item;

} // end getItem

/*=============================================================================
FUNCTION:          isLeaf()
DESCRIPTION:       Tests if the node is a leaf
PRECONDITION:      None
POSTCONDITION:     Boolean return value based on the test
===============================================================================*/

template<typename dataType>
bool BinaryNode<dataType>::isLeaf() const{

       return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));

}

/*=============================================================================
FUNCTION:          getLeftChildPtr()
DESCRIPTION:       Get the left childs pointer
PRECONDITION:      None 
POSTCONDITION:     A pointer return value for the locations of the Node
===============================================================================*/

template<typename dataType>
std::shared_ptr<BinaryNode<dataType>> BinaryNode<dataType>::getLeftChildPtr() const{

       return leftChildPtr;

} // end getLeftChildPtr        

/*=============================================================================
FUNCTION:          getRightChildPtr()
DESCRIPTION:       Get the right childs pointer
PRECONDITION:      None 
POSTCONDITION:     A pointer return value for the locations of the Node
===============================================================================*/

template<typename dataType>
std::shared_ptr<BinaryNode<dataType>> BinaryNode<dataType>::getRightChildPtr() const{

       return rightChildPtr;

} // end getRightChildPtr   

/*=============================================================================
FUNCTION:          setLeftChildPtr()
DESCRIPTION:       Sets the left child pointer
PRECONDITION:      passed a pointer to set to the left child
POSTCONDITION:     None
===============================================================================*/

template<typename dataType>
void BinaryNode<dataType>::setLeftChildPtr(std::shared_ptr<BinaryNode<dataType>> leftPtr){

       leftChildPtr = leftPtr;

} // end setLeftChildPtr

/*=============================================================================
FUNCTION:          setRightChildPtr()
DESCRIPTION:       sets the right child pointer
PRECONDITION:      passed a pointer to set to the right Child
POSTCONDITION:     None
===============================================================================*/

template<typename dataType>
void BinaryNode<dataType>::setRightChildPtr(std::shared_ptr<BinaryNode<dataType>> rightPtr){

       rightChildPtr = rightPtr;

} // end setRightChildPtr