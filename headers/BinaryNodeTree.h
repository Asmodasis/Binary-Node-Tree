#ifndef _BINARY_NODE_TREE
#define _BINARY_NODE_TREE

/*===============================================================================

FILE:              BinaryNodeTree.h

DESCRIPTION:       The header file for the class BinaryNodeTree

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
#include "../headers/PrecondViolatedExcept.h"
#include "../headers/NotFoundException.h"

template<class dataType>
class BinaryNodeTree : public BinaryTreeInterface<dataType>
{
private:
   std::shared_ptr<BinaryNode<dataType>> rootPtr;

protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------

   int getHeightHelper(std::shared_ptr<BinaryNode<dataType>> subTreePtr) const;
   int getNumberOfNodesHelper(std::shared_ptr<BinaryNode<dataType>> subTreePtr) const;

   // Recursively deletes all nodes from the tree.
   void destroyTree(std::shared_ptr<BinaryNode<dataType>> subTreePtr);

   // Recursively adds a new node to the tree in a left/right fashion to
   // keep the tree balanced.
   std::shared_ptr<BinaryNode<dataType>> balancedAdd(std::shared_ptr<BinaryNode<dataType>> subTreePtr,
                                     std::shared_ptr<BinaryNode<dataType>> newNodePtr);

   // Removes the target value from the tree by calling moveValuesUpTree
   // to overwrite value with value from child.
   std::shared_ptr<BinaryNode<dataType>> removeValue(std::shared_ptr<BinaryNode<dataType>> subTreePtr,
                                     const dataType target, bool& success);

   // Copies values up the tree to overwrite value in current node until
   // a leaf is reached; the leaf is then removed, since its value is
   // stored in the parent.
   std::shared_ptr<BinaryNode<dataType>> moveValuesUpTree(std::shared_ptr<BinaryNode<dataType>> subTreePtr);

   // Recursively searches for target value in the tree by using a
   // preorder traversal.
   std::shared_ptr<BinaryNode<dataType>> findNode(std::shared_ptr<BinaryNode<dataType>> treePtr,
                                  const dataType& target,
                                  bool& success) const;

   // Copies the tree rooted at treePtr and returns a pointer to
   // the copy.
   std::shared_ptr<BinaryNode<dataType>> copyTree(const std::shared_ptr<BinaryNode<dataType>> treePtr) const;

   // Recursive traversal helper methods:
   void preorder(void visit(dataType&), std::shared_ptr<BinaryNode<dataType>> treePtr) const;
   void inorder(void visit(dataType&), std::shared_ptr<BinaryNode<dataType>> treePtr) const;
   void postorder(void visit(dataType&), std::shared_ptr<BinaryNode<dataType>> treePtr) const;

public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   BinaryNodeTree();
   BinaryNodeTree(const dataType& rootItem);
   BinaryNodeTree(const dataType& rootItem,
                  const BinaryNodeTree<dataType>* leftTreePtr,
                  const BinaryNodeTree<dataType>* rightTreePtr);
   BinaryNodeTree(const BinaryNodeTree<dataType>& tree);
   ~BinaryNodeTree();

   //------------------------------------------------------------
   // Public BinaryTreeInterface Methods Section.
   //------------------------------------------------------------
   bool isEmpty() const;
   int getHeight() const;
   int getNumberOfNodes() const;
   dataType getRootData() const;//throw(PrecondViolatedExcept);
   void setRootData(const dataType& newData);
   bool add(const dataType& newData); // Adds a node
   bool remove(const dataType& data); // Removes a node
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
   BinaryNodeTree& operator=(const BinaryNodeTree& rightHandSide);
}; // end BinaryNodeTree
//#include "BinaryNodeTree.cpp"
#endif
