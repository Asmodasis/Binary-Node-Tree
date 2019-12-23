#ifndef _BINARY_NODE
#define _BINARY_NODE

/*===============================================================================

FILE:              BinaryNode.h

DESCRIPTION:       A class based node implementation featuring two children nodes

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

template<class dataType>
class BinaryNode
{
private:
   dataType              item;           // Data portion
   std::shared_ptr<BinaryNode<dataType>> leftChildPtr;   // Pointer to left child
   std::shared_ptr<BinaryNode<dataType>> rightChildPtr;  // Pointer to right child

public:
   BinaryNode();
   BinaryNode(const dataType& anItem);
   BinaryNode(const dataType& anItem,
              std::shared_ptr<BinaryNode<dataType>> leftPtr,
              std::shared_ptr<BinaryNode<dataType>> rightPtr);

   void setItem(const dataType& anItem);
   dataType getItem() const;

   bool isLeaf() const;

   std::shared_ptr<BinaryNode<dataType>> getLeftChildPtr() const;
   std::shared_ptr<BinaryNode<dataType>> getRightChildPtr() const;

   void setLeftChildPtr(std::shared_ptr<BinaryNode<dataType>> leftPtr);
   void setRightChildPtr(std::shared_ptr<BinaryNode<dataType>> rightPtr);
}; // end BinaryNode

//#include "BinaryNode.cpp"

#endif
