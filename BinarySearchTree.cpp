//============================================================================
// Name        : BinarySearchTree.cpp
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
/* Author:     : Jaden Knutson
Description: 
    The program: "BinarySearchTree.cpp", is a C++ implementation of a binary search tree data structure. 
    The main function provides a menu-driven interface to interact with the binary search tree including options 
    to load bids from a CSV file, display all bids, find a specific bid, and remove a bid from the tree. Example:
        •	Option 1 - load bids,
        •	Option 2 - display all bids,
        •	Option 3 - find a bid,
        •	Option 4 - remove a bid,
        •	Option 9 - and exit the program.
    I have added in menu options 5, 6, 7, and 8 so user can switch between the two files and swith the ordering method
        •	Option 5 - Switches the order to: Pre-order
        •	Option 6 - Switches the order to: Post-order
        •	Option 7 - Switches the load directory to: eBid_Monthly_Sales.csv
        •	Option 8 - Switches the load directory to: eBid_Monthly_Sales_Dec_2016.csv
        •	Once the new directory is switched, the user can reload by entering "1" and can now sort/display the new file.
    //---------------------------------------------------------
    Most of my work went into:
        	BinarySearchTree::BinarySearchTree()
        	BinarySearchTree::~BinarySearchTree()

            Bid BinarySearchTree::Search(string bidId)
        	void BinarySearchTree::Insert(Bid bid)
        	void BinarySearchTree::addNode(Node* node, Bid bid)

        	void BinarySearchTree::Remove(string bidId)
        	Node* BinarySearchTree::removeNode(Node* node, string bidId)
            void deleteAll(Node* node);

        	void BinarySearchTree::InOrder()
        	void BinarySearchTree::inOrder(Node* root)
     
            void postOrder(Node* node);
            void BinarySearchTree::PostOrder()

            void BinarySearchTree::PreOrder()
            void preOrder(Node* node);
        //---------------------------------------------------------
        // FixMe (1): initialize housekeeping variables
        // FixMe (2): In order root
        // FixMe (3): Post order root
        // FixMe (4): Pre order root
        // FIXME (5)  Implement inserting a bid into the tree
        // FIXME (6)  Implement removing a bid from the tree
        // FIXME (7)  Implement searching the tree for a bid
        // FIXME (8)  Implement inserting a bid into the tree
        // FixMe (9): In-order traversal
        // FixMe (10): Post-order traversal
        // FixMe (11): Pre-order traversal

/*================================================================================================================================*/
#include <iostream>
#include <time.h>
#include "CSVparser.hpp"
using namespace std;
#include <ctime> //added <--------------------------------------------------------------------
#include <stack> //added <--------------------------------------------------------------------

/*================================================================================================================================*/
// Global definitions visible to all methods and classes
/*================================================================================================================================*/
// forward declarations
int numBidsLoaded = 0;//ADDED THIS <--------
double strToDouble(string str, char ch);

//---------------------------------------------------------
// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};
//---------------------------------------------------------
// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }
//---------------------------------------------------------
    // initialize with a bid
    Node(Bid aBid) :Node() {
        bid = aBid;
    }
};
/*================================================================================================================================*/
// Binary Search Tree class definition
/*================================================================================================================================*/
//Define a class containing data members and methods implement a binary search tree
class BinarySearchTree {

private:
    Node* root;
    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);

    Node* removeNode(Node* node, string bidId);
    void deleteAll(Node* node); //ADDED THIS <--------
//---------------------------------------------------------
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();

    void PostOrder();
    void PreOrder();
    void InOrder();

    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};
/*================================================================================================================================*/
/*================================================================================================================================*/










/*================================================================================================================================*/
/*================================================================================================================================*/
//Default constructor - FixMe (1): initialize housekeeping variables                                                                        // FixMe (1): initialize housekeeping variables
//---------------------------------------------------------
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    root = nullptr; //root is equal to nullptr
}
//============================================================================
//Destructor - recurse from root deleting every node
//---------------------------------------------------------
BinarySearchTree::~BinarySearchTree() {
    //helper function to delete all nodes
    deleteAll(root);
}
//============================================================================
void BinarySearchTree::deleteAll(Node* node) {
    if (node != nullptr) {
        // Recursively delete all nodes in left and right subtrees
        deleteAll(node->left);
        deleteAll(node->right);

        // Delete current node
        delete node;
    }
}

/*================================================================================================================================*/
//Traverse the tree in order - FixMe (2): In order root                                                                                      // FixMe (2): In order root
//---------------------------------------------------------
void BinarySearchTree::InOrder() {
    this->inOrder(root); //call inOrder fuction and pass root 
}
//============================================================================
//FixMe (9): In-order traversal        if node is not equal to nullptr                                                                      // FixMe (9): In-order traversal
void BinarySearchTree::inOrder(Node* root) {
    // If tree/sub-tree is empty, return
    if (root == nullptr)
        return;

    // Create empty stack
    std::stack<Node*> nodeStack;

    // Set current node as root
    Node* current = root;

    // Traverse tree in in-order fashion
    while (current != nullptr || !nodeStack.empty()) {
        // Reach left most Node of current Node
        while (current != nullptr) {
            // place pointer to tree node on stack before traversing node's left subtree
            nodeStack.push(current);
            current = current->left;
        }

        // Current must be NULL, pop top item from stack
        current = nodeStack.top();
        nodeStack.pop();

        // Visit node at top of stack
        cout << current->bid.bidId << ": " << current->bid.title
            << " | " << current->bid.amount << " | " << current->bid.fund << endl;

        // Visit right subtree
        current = current->right;
    }
}

/*================================================================================================================================*/
//Traverse the tree in pre-order                                                                                                            // FixMe (4): Pre order root
//---------------------------------------------------------
void BinarySearchTree::PreOrder() {
    try {
        this->preOrder(root); //call preOrder function and pass root
    }
    catch (...) {
        // Handle the exception
        throw; // Rethrow exception 
    }
}
//============================================================================
void BinarySearchTree::preOrder(Node* root) {                                                                                               // FixMe (11): Pre-order traversal       
    // If tree/sub-tree is empty, return
    if (root == nullptr)
        return;

    std::stack<Node*> nodeStack; // Create stack to hold nodes during traversal
    nodeStack.push(root); // Start traversal at root node

    while (!nodeStack.empty()) { // traversal as long while more nodes in stack
        Node* node = nodeStack.top(); // Get node at top of stack
        nodeStack.pop(); // Remove node from stack

        // Process urrent node
        cout << node->bid.bidId << ": " << node->bid.title
            << " | " << node->bid.amount << " | " << node->bid.fund << endl;

        // Push right child first (to be processed next)
        if (node->right)
            nodeStack.push(node->right);

        // Push left child (to be processed after right child)
        if (node->left)
            nodeStack.push(node->left);
    }
}

/*================================================================================================================================*/
//Traverse the tree in post-order
//---------------------------------------------------------
void BinarySearchTree::PostOrder() {                                                                                                        // FixMe (3): Post order root
    try {
        this->postOrder(root); //call postOrder function and pass root
    }
    catch (...) {
        // Handle the exception
        throw; // Rethrow exception
    }
}
//============================================================================
void BinarySearchTree::postOrder(Node* root) { // Function to perform post-order traversal of a binary search tree
    // If tree/sub-tree is empty, return
    if (root == nullptr) // If null, there's nothing to traverse
        return;

    std::stack<Node*> nodeStack; // Create stack to hold nodes during traversal
    Node* current = root; // Start traversal at root node
    Node* lastVisited = nullptr; // Keep track of Last visited node

    while (current || !nodeStack.empty()) { // traversal as long while more nodes in stack or current node
        if (current) { // If current node
            nodeStack.push(current); // Push current node onto stack
            current = current->left; // Move to left child
        }
        else { // If no current node
            Node* temp = nodeStack.top(); // Look at top node of stack

            // If right child exists and not the last visited node
            if (temp->right && temp->right != lastVisited) {
                current = temp->right; // Move to the right child
            }
            else {
                // Process current node
                cout << temp->bid.bidId << ": " << temp->bid.title
                    << " | " << temp->bid.amount << " | " << temp->bid.fund << endl;
                nodeStack.pop(); // Remove node from stack
                lastVisited = temp; // Update last visited node
            }
        }
    }
}


/*================================================================================================================================*/
//Insert a bid
//---------------------------------------------------------
void BinarySearchTree::Insert(Bid bid) {                                                                                                    // FIXME (5) Implement inserting a bid into the tree
    
    // Create a new node with bid
    Node* newNode = new Node(bid);

    // If tree is empty, new node becomes the root
    if (root == nullptr) {
        root = newNode;// If tree is empty, root becomes the new node
    }
    else {
        // Start from the root and find the correct spot in the tree for the new node
        Node* current = root;
        Node* parent = nullptr;

        while (true) {
            parent = current;

            // If bidId of bid to be inserted is less than current node's bidId, go to left subtree
            if (bid.bidId.compare(current->bid.bidId) < 0) {
                current = current->left;

                if (current == nullptr) {
                    parent->left = newNode;// If current is null, insert new node to the left of parent
                    break;
                }
            }
            else {
                current = current->right; // Else, go to right subtree

                // If right child of current node is null, insert to right of parent
                if (current == nullptr) {
                    parent->right = newNode; //insert new node to the right of parent
                    break;
                }
            }
        }
    }
}

/*================================================================================================================================*/
//Remove a bid - FIXME (6) Implement removing a bid from the tree                                                                            // FIXME (6) Implement removing a bid from the tree
//---------------------------------------------------------
void BinarySearchTree::Remove(string bidId) {       
    // Implement removing a bid from tree
    this->removeNode(root, bidId); //remove node root bidID
}
//============================================================================
//Remove bid from a node (recursive)
//@param node Current node in tree
//@param string BidId that we are removing
//---------------------------------------------------------
Node* BinarySearchTree::removeNode(Node* node, string bidId) {

    // If tree/sub-tree is empty, return node
    if (node == nullptr) {
        return node;
    }

    // If bidId to be deleted is smaller than node's bidId, then it lies in left subtree
    if (bidId.compare(node->bid.bidId) < 0) {
        node->left = removeNode(node->left, bidId);
    }
    // If bidId to be deleted is greater than node's bidId, then it lies in right subtree
    else if (bidId.compare(node->bid.bidId) > 0) {
        node->right = removeNode(node->right, bidId);
    }
    // If bidId is same as node's bidId, then delete node
    else {

        // Node with only one child or no child
        if (node->left == nullptr && node->right == nullptr) {
            delete node; // Delete node
            node = nullptr; // Set node to nullptr to maintain tree structure
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        // Node with only left child
        else if (node->left != nullptr && node->right == nullptr) {
            Node* temp = node; // Temporary node for deletion
            node = node->left; // Replace node with its left child
            delete temp; // Delete temporary node
        }

        // Node with only right child
        else if (node->right != nullptr && node->left == nullptr) {
            Node* temp = node; // Temporary node for deletion
            node = node->right; // Replace node with its right child
            delete temp; // Delete temporary node
        }

        // Node with two children
        else {
            Node* temp = node->right; // Start with right child of node
            // Find leftmost node in right subtree 
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            // Replace bid of node to be deleted with bid of the inorder successor
            node->bid = temp->bid;
            // Delete inorder successor
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }
    // Return the possibly new root node of the tree/sub-tree
    return node;
}

/*================================================================================================================================*/
//Search for a bid - FIXME (7) Implement searching the tree for a bid                                                                       // FIXME (7) Implement searching the tree for a bid
//---------------------------------------------------------
Bid BinarySearchTree::Search(string bidId) {
    Node* current = root;  // Start search at root of tree

    // Keep traversing down the tree until bottom of tree is reached or bid is found
    while (current != nullptr) {
        // current node matches, return it
        if (current->bid.bidId.compare(bidId) == 0) {
            return current->bid;
        }
        // If bid is smaller than current, then traverse left
        else if (bidId.compare(current->bid.bidId) < 0) {
            current = current->left;
        }
        // If bid is larger than current, traverse right
        else {
            current = current->right;
        }
    }

    Bid bid;
    return bid; // No match found
}

/*================================================================================================================================*/
//Add a bid to some node (recursive)    FIXME (8) Implement inserting a bid into the tree                                                   // FIXME (8) Implement inserting a bid into the tree
//---------------------------------------------------------
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (8) Implement inserting a bid into tree
    // if node is larger, then add to left
    if (node->bid.bidId.compare(bid.bidId) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(bid);
        }
        else {
            // else recurse down left node
            this->addNode(node->left, bid);
        }
    }
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(bid);
        }
        else {
            // else recurse down right node
            this->addNode(node->right, bid);
        }
    }
}
/*================================================================================================================================*/













/*================================================================================================================================*/
// Static methods used for testing
/*================================================================================================================================*/
//Display the bid information to the console (std::out)
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}
/*================================================================================================================================*/
 //Load a CSV file containing bids into a container
 //@param csvPath the path to the CSV file to load
 //@return a container holding all the bids read
//---------------------------------------------------------
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);
//---------------------------------------------------------
    // read and display header row - optional
    vector<string> header = file.getHeader();
    //for (auto const& c : header) { 
        //cout << c << " | "; //<----------------------------------OPTIONAL TURN ON/OFF CURRENTLY: off
    //}
    //cout << "" << endl; //<--------------------------------------OPTIONAL TURN ON/OFF CURRENTLY: off
//---------------------------------------------------------
    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');
            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;
            // push this bid to the end
            bst->Insert(bid);
            //------------------------------------------------------------------
            numBidsLoaded++;//ADDED THIS <-------- counts bids loaded
            //------------------------------------------------------------------
        }
//---------------------------------------------------------
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}
/*================================================================================================================================*/
// Simple C function to convert a string to a doublE after stripping out unwanted characters
// credit: http://stackoverflow.com/a/24875936
//---------------------------------------------------------
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end()); // Remove the specified character from the string
    return atof(str.c_str()); // Convert the modified string to a double
}
/*================================================================================================================================*/
/*================================================================================================================================*/
//NO EDITS











/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/* ░██████╗████████╗░█████╗░██████╗░████████╗      ███╗░░░███╗░█████╗░██╗███╗░░██╗
   ██╔════╝╚══██╔══╝██╔══██╗██╔══██╗╚══██╔══╝      ████╗░████║██╔══██╗██║████╗░██║
   ╚█████╗░░░░██║░░░███████║██████╔╝░░░██║░░░      ██╔████╔██║███████║██║██╔██╗██║
   ░╚═══██╗░░░██║░░░██╔══██║██╔══██╗░░░██║░░░      ██║╚██╔╝██║██╔══██║██║██║╚████║
   ██████╔╝░░░██║░░░██║░░██║██║░░██║░░░██║░░░      ██║░╚═╝░██║██║░░██║██║██║░╚███║
   ╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░      ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝  - The one and only main() method*
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
int main(int argc, char* argv[]) {
//---------------------------------------------------------
    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98009";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        //csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98009";
    }
//---------------------------------------------------------
    // Define a timer variable
    clock_t ticks;
    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;
//============================================================================
    int choice = 0;
    while (choice != 9) {
        cout << "------------------------------------------" << endl;
        cout << "Main Menu Options:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids: In-Order" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << endl;
        cout << "Additional Menu Options:" << endl;
        //---------------------------------------------------------
        //ADDED OPTION 5 AND 6
        cout << "  5. Display All Bids: Pre-Order" << endl;
        cout << "  6. Display All Bids: Post-Order" << endl;
        //---------------------------------------------------------      
        //ADDED OPTION 6 AND 7        
        cout << "  7. Change bid file: 12,023 Total Bids" << endl;
        //cout << "  6. Switch load designation to: eBid_Monthly_Sales.csv" << endl;
        cout << "  8. Change bid file: 76 Total Bids" << endl;
        //cout << "  7. Switch load designation to: eBid_Monthly_Sales_Dec_2016.csv (default)" << endl;
        //--------------------------------------------------------- 
        cout << "------------------------------------------" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;
//============================================================================
        switch (choice) {
        case 1:         
            // Initialize a timer variable before loading bids
            ticks = clock();
            // Complete the method call to load the bids
            loadBids(csvPath, bst);
            //cout << bst->Size() << " bids read" << endl;
            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "Bids Loaded: " << numBidsLoaded << endl; //ADDED THIS <--------
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
        //---------------------------------------------------------
        case 2:
            bst->InOrder();
            break;
        //---------------------------------------------------------
        case 3:
            ticks = clock(); 
            bid = bst->Search(bidKey);
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
        //---------------------------------------------------------
        case 4:
            bst->Remove(bidKey); // Remove a bid
            break;
/*================================================================================================================================*/
        //NEW MENU OPTIONS: 5 & 6      
        case 5:
            bst->PreOrder();
            break;
        //---------------------------------------------------------
        case 6:
            bst->PostOrder();
            break;
        //---------------------------------------------------------  
        //NEW MENU OPTIONS: 7 & 8
        case 7:
            csvPath = "eBid_Monthly_Sales.csv";
            cout << "You've switched the load designation to: eBid_Monthly_Sales.csv" << endl;
            cout << "Please Re-Load the bids." << endl;
            cout << endl;
            break;
        //---------------------------------------------------------
        case 8:
            csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
            cout << "You've switched the load designation to: eBid_Monthly_Sales_Dec_2016.csv" << endl;
            cout << "Please Re-Load the bids." << endl;
            cout << endl;
            break;
        }//End Switch-Case
/*================================================================================================================================*/
//ADDED BLANK LINES
    cout << "---" << endl << endl;    
    }
    cout << "Good bye." << endl;
	return 0;
}
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/
  /*███████╗███╗░░██╗██████╗░      ███╗░░░███╗░█████╗░██╗███╗░░██╗
    ██╔════╝████╗░██║██╔══██╗      ████╗░████║██╔══██╗██║████╗░██║
    █████╗░░██╔██╗██║██║░░██║      ██╔████╔██║███████║██║██╔██╗██║
    ██╔══╝░░██║╚████║██║░░██║      ██║╚██╔╝██║██╔══██║██║██║╚████║
    ███████╗██║░╚███║██████╔╝      ██║░╚═╝░██║██║░░██║██║██║░╚███║
    ╚══════╝╚═╝░░╚══╝╚═════╝░      ╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝*/
/*================================================================================================================================*/
/*================================================================================================================================*/
/*================================================================================================================================*/



