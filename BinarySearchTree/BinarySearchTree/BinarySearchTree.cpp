#include <iostream>
#include <time.h>
#include "CSVparser.hpp"
using namespace std;
#include <ctime>
#include <stack>

struct Bid {
    string bidId;
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

struct Node {
    Bid bid;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Bid aBid) :Node() {
        bid = aBid;
    }
};

class BinarySearchTree {
private:
    Node* root;
    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
}

void BinarySearchTree::InOrder() {
    this->inOrder(root);
}

void BinarySearchTree::Insert(Bid bid) {
    Node* newNode = new Node(bid);

    if (root == nullptr) {
        root = newNode;
    }
    else {
        Node* current = root;
        Node* parent = nullptr;

        while (true) {
            parent = current;

            if (bid.bidId.compare(current->bid.bidId) < 0) {
                current = current->left;

                if (current == nullptr) {
                    parent->left = newNode;
                    break;
                }
            }
            else {
                current = current->right;

                if (current == nullptr) {
                    parent->right = newNode;
                    break;
                }
            }
        }
    }
}

void BinarySearchTree::Remove(string bidId) {
    this->removeNode(root, bidId);
}

Bid BinarySearchTree::Search(string bidId) {
    Node* current = root;

    while (current != nullptr) {
        if (current->bid.bidId.compare(bidId) == 0) {
            return current->bid;
        }
        else if (bidId.compare(current->bid.bidId) < 0) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    Bid bid;
    return bid;
}

void BinarySearchTree::addNode(Node* node, Bid bid) {
    if (node->bid.bidId.compare(bid.bidId) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(bid);
        }
        else {
            this->addNode(node->left, bid);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(bid);
        }
        else {
            this->addNode(node->right, bid);
        }
    }
}

void BinarySearchTree::inOrder(Node* root) {
    if (root == nullptr)
        return;

    std::stack<Node*> nodeStack;
    Node* current = root;

    while (current != nullptr || !nodeStack.empty()) {
        while (current != nullptr) {
            nodeStack.push(current);
            current = current->left;
        }

        current = nodeStack.top();
        nodeStack.pop();

        cout << current->bid.bidId << ": " << current->bid.title
            << " | " << current->bid.amount << " | " << current->bid.fund << endl;

        current = current->right;
    }
}

Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    if (node == nullptr) {
        return node;
    }

    if (bidId.compare(node->bid.bidId) < 0) {
        node->left = removeNode(node->left, bidId);
    }
    else if (bidId.compare(node->bid.bidId) > 0) {
        node->right = removeNode(node->right, bidId);
    }
    else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = node->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        node->bid = temp->bid;
        node->right = removeNode(node->right, temp->bid.bidId);
    }

    return node;
}

void LoadBids(string csvPath, BinarySearchTree* bst) {
    csv::Parser file = csv::Parser(csvPath);

    for (int i = 0; i < file.rowCount(); i++) {
        Bid bid;
        bid.bidId = file[i][1];
        bid.title = file[i][0];
        bid.fund = file[i][8];
        bid.amount = std::stod(file[i][4]);

        bst->Insert(bid);
    }
}

int main() {
    BinarySearchTree* bst = new BinarySearchTree();

    string csvPath = "eBid_Monthly_Sales.csv";
    LoadBids(csvPath, bst);

    bst->InOrder();

    delete bst;

    return 0;
}
