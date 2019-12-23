#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

/*===============================================================================

FILE:              BinarySearchTree.h

DESCRIPTION:       the Header file for the class BinarySearchTree

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

#include "../headers/BinaryTreeInterface.h"
#include "../headers/BinaryNode.h"
#include "../headers/BinaryNodeTree.h"
#include "../headers/NotFoundException.h"
#include "../headers/PrecondViolatedExcept.h"

template<class dataType>
class BinarySearchTree : public BinaryNodeTree<dataType>
 {
  private:
     std::shared_ptr<BinaryNode<dataType>> rootPtr;

  protected:
     //------------------------------------------------------------
     // Protected Utility Methods Section:
     // Recursive helper methods for the public methods.
     //------------------------------------------------------------

     std::shared_ptr<BinaryNode<dataType>> insertInorder(std::shared_ptr<BinaryNode<dataType>> subTreePtr,
                                         std::shared_ptr<BinaryNode<dataType>> newNode);

     // Removes the given target value from the tree while maintaining a
     // binary search tree.
     std::shared_ptr<BinaryNode<dataType>> removeValue(std::shared_ptr<BinaryNode<dataType>> subTreePtr,
                                       const dataType target,
                                       bool& success);
         // Removes a given node from a tree while maintaining a
    // binary search tree.
     std::shared_ptr<BinaryNode<dataType>> removeNode(std::shared_ptr<BinaryNode<dataType>> nodePtr);
         // Removes the leftmost node in the left subtree of the node
     // pointed to by nodePtr.
     // Sets inorderSuccessor to the value in this node.
     // Returns a pointer to the revised subtree.
     std::shared_ptr<BinaryNode<dataType>> removeLeftmostNode(std::shared_ptr<BinaryNode<dataType>> subTreePtr,
                                              dataType& inorderSuccessor);

     // Returns a pointer to the node containing the given value,
     // or nullptr if not found.
     std::shared_ptr<BinaryNode<dataType>> findNode(std::shared_ptr<BinaryNode<dataType>> treePtr,
                                    const dataType& target) const;

 public:

     //------------------------------------------------------------
     // Constructor and Destructor Section.
     //------------------------------------------------------------
     BinarySearchTree();
     BinarySearchTree(const dataType& rootItem);
     BinarySearchTree(const BinarySearchTree<dataType>& tree);
     ~BinarySearchTree();

     //------------------------------------------------------------
     // Public Methods Section.
     //------------------------------------------------------------
     bool isEmpty() const;
     int getHeight() const;
     int getNumberOfNodes() const;
     dataType getRootData() const; //throw(PrecondViolatedExcept);
     void setRootData(const dataType& newData) const; //throw(PrecondViolatedExcept);
     
     bool add(const dataType& newEntry);
     bool remove(const dataType& anEntry);

     void clear();
     dataType getEntry(const dataType& anEntry) const; //throw(NotFoundException);
     bool contains(const dataType& anEntry) const;

     //------------------------------------------------------------
     // Public Traversals Section.
     //------------------------------------------------------------
     void preorderTraverse(void visit(dataType&)) const;
     void inorderTraverse(void visit(dataType&)) const;
     void postorderTraverse(void visit(dataType&)) const;

     //------------------------------------------------------------
    // Overloaded Operator Section.
     //------------------------------------------------------------
     BinarySearchTree<dataType>& operator=(const BinarySearchTree<dataType>& rightHandSide);
 }; // end BinarySearchTree

 //#include "BinarySearchTree.cpp"

 #endif
