

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

#include "../src/BinarySearchTree.cpp"
#include "../src/BinaryNodeTree.cpp"
#include "../src/BinaryNode.cpp"


// function declarations
char menu (std::ostream&, std::istream&);
template<typename dataType>
bool binarySearchTreeOperations(BinarySearchTree<dataType>& , char, std::ostream&, std::istream&);
template<typename dataType>
void fileOut(dataType& item);

/*
template<typename dataType>
struct TreeVisitor{													// the struct to be used with std::visit
	public:

		std::ostream& treeOut;										// the stream for printing
		std::string&  mesFirst;										// message for first 
		std::string&  mesLast;										// message for last

		TreeVisitor(std::ostream & out, const std::string& first, const std::string& last ){
			treeOut = out;
			mesFirst = first;
			mesLast = last; 

		}

		void operator () (const dataType& visitorOutput){

			treeOut << mesFirst << visitorOutput << mesLast;

		}
	private:
};
*/


int main(int argc, char *argv[], char *envp[]){

	char choice;
	BinarySearchTree<int> tree;

	srand(time(0));													// seed the random nunber generator
    
    
	
	while( binarySearchTreeOperations( tree ,   					// the BST we will be working with
									  choice =  menu(std::cout, std::cin) ,   // menu selection, character return
									  std::cout, 					// output
									  std::cin 						// input
									 )
		 );															// keep looping until quit is selected										

  return 0;

}

char menu (std::ostream& out, std::istream& in){

	char choice;
	bool menuLoop = true; 

	while(menuLoop){
		out << "\n\t===========================================================";
		out << "\n\tWelcome to the BinarySearchTree Demo Menu -- BST for short";
		out << "\n\t===========================================================";
		out << "\n\ta) Test if the BST is empty :: isEmpty()";
		out << "\n\tb) Get the height of the BST :: getHeight()";
		out << "\n\tc) Get the number of Nodes in the BST :: getNumberOfNodes()";
		out << "\n\td) Get the Root data of the BST :: getRootData()";
		out << "\n\te) Set the Root data of the BST :: setRootData()";
		out << "\n\tf) Add a new entry to the BST :: add()";
		out << "\n\tg) Remove an entry from the BST :: remove()";
		out << "\n\th) Clear the BST :: clear()";
		out << "\n\ti) Get an entry from the BST :: getEntry()";
		out << "\n\tj) See if the BST Contains an entry :: contains()";
		out << "\n\tk) Preorder Traverse :: preorderTraverse()";
		out << "\n\tl) Inorder Traverse :: inorderTraverse()";
		out << "\n\tm) Postorder Traverse :: postorderTraverse()";
		out << "\n\tq) Quit the Program ";
		out << "\n\t===========================================================";
		out << "\n\tPlease choose from the selection ";

		in >> choice;

		if( in.fail() || ( (choice < 'a' || choice > 'm') && choice != 'q' ) ){		// clear the errors that occur
			in.clear();
			in.ignore(256, '\n');
			out << "\n\tPlease choose a valid selection!\n"; 
		}else{
			choice = std::tolower(choice);
			menuLoop = false;														// if failed, keep looping
		}
	}

	return choice;
}

template<typename dataType>
bool binarySearchTreeOperations(BinarySearchTree<dataType>& tree, char input, std::ostream& out, std::istream& in){

	bool returnTest = true;
	int addInput = 0;
	
	dataType anEntry;																					// an entry to add to tree

	

	try{
		switch(input){
			case 'a':
				// isEmpty()
					if(tree.isEmpty()){
						out << "\n\tThe BST is Empty\n";
					}else{
						out << "\n\tThe BST is Not empty\n";
					}
	 

				break;
			case 'b':
				// getHeight()
					out << "\n\tThe height of the BST is " << tree.getHeight() << "\n";
				break;
			case 'c':
				// getNumberOfNodes()
					out << "\n\tThe number of nodes the BST has is " << tree.getNumberOfNodes() << "\n";
				break;
			case 'd':
				// getRootData()
					out << "\n\tThe Value in the Root of the BST is " << tree.getRootData() << "\n";

				break;
			case 'e':
				// setRootData()
					tree.setRootData(2);

				break;
			case 'f':
				// add()
					out << "\n\tWould you like to add a number ( 1 ) or randomly generate 100 numbers ( 2 ) : ";
					in >> addInput;
						if(addInput == 1){
							out  << "\n\tPlease input a value you would like to add : ";
							in >> anEntry;
							if(!tree.add(anEntry))
								out << "\n\tUnable to add entry!\n";
						}else{

							for(int i = 0; i < 100; ++i)
								tree.add( (rand() % 200) );
						}


				break;
			case 'g':
				// remove()
				out  << "\n\tPlease input a value you would like to remove : ";
				in >> anEntry;

				out << "\n\tRemoving the value from the tree! \n";
					
					if(!tree.remove(anEntry))
						out << "\n\tUnable to remove entry! Object not found\n";

				break;
			case 'h':
				// clear()
				out << "\n\tClearing values from the tree! \n";
				tree.clear();

				break;
			case 'i':
				// getEntry()
				out  << "\n\tPlease input a value you would like to get from the Tree: ";
				in >> anEntry;

				out << "\n\tYes the value " << tree.getEntry(anEntry) << " was located in the Tree!\n";

				break;
			case 'j':
				// contains()
				out  << "\n\tPlease input a value you would like to see if the tree Contains it: ";
				in >> anEntry;

				if(tree.contains(anEntry))
					out << "\n\tYes the value is in the tree! \n";
				else
					out << "\n\tNo the value is not in the tree! \n";

				break;
			case 'k':
				// preorderTraverse()
				out << "\n\nDisplaying Preorder Traversing\n";
				tree.preorderTraverse([] (dataType& item) { std::cout << item; });
					
				//if(&std::cout != &out)														// test if it's a file
					tree.preorderTraverse( fileOut );										// not the best solution but it works

				break;
			case 'l':
				// inorderTraverse()
				out << "\n\nDisplaying Inorder Traversing\n";
				tree.inorderTraverse([] (dataType& item) { std::cout << item; });

				//if(&std::cout != &out)														// test if it's a file
					tree.inorderTraverse( fileOut );										// not the best solution but it works

				break;
			case 'm':
				// postorderTraverse()
				out << "\n\nDisplaying Postorder Traversing\n";
				tree.postorderTraverse([] (dataType& item) { std::cout << item; });

				//if(&std::cout != &out)														// test if it's a file
					tree.postorderTraverse( fileOut );										// not the best solution but it works

				break;
			case 'q':
				returnTest = false;
				out << "\n\n\tThank you for running the program\n\n";
			break;
		}

	}catch(logic_error err){																// error catching
		out << "\n\t" << err.what() << "\n";				

	}

	return returnTest;
}

template<typename dataType>
void fileOut(dataType& item){ 

	std::fstream file;

	file.open("../documentation/output.txt", std::ios::out | std::ios::app);

	file << item;

	file.close();

}