#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <memory>
#include <cstdio>
class Node {
		// IMPORTANT := All the data has to be present in the leaf node
   public:
    bool isLeaf;
    std::vector<int> keys;
    Node* ptr2next;              //Pointer to connect next node for leaf nodes
    union ptr {                  //to make memory efficient Node
        std::vector<Node*> ptr2Tree;  //Array of pointers to Children sub-trees for intermediate Nodes
        std::vector<FILE*> dataPtr;   // Data-Pointer for the leaf node
        ptr();   
        ~ptr(); 
    } ptr2TreeOrData; // mean either leaf node or  internal node
    friend class bp_tree;  // to access private members of the Node and hold the encapsulation concept
   public:
    Node();
    ~Node();  // RAII 
};

class bp_tree {
    /*
		::For Root Node :=
			The root node has, at least two tree pointers
		::For Internal Nodes:=
			1. ceil(maxIntChildLimit/2)     <=  #of children <= maxIntChildLimit
			2. ceil(maxIntChildLimit/2)-1  <=  #of keys     <= maxIntChildLimit -1
		::For Leaf Nodes :=
			1. ceil(maxLeafNodeLimit/2)   <=  #of keys     <= maxLeafNodeLimit -1
	*/
   private:
    int maxIntChildLimit;                                   //Limiting  #of children for internal Nodes!
    int maxLeafNodeLimit;                                   // Limiting #of nodes for leaf Nodes!!!
    Node* root;                                             //Pointer to the B+ Tree root
    void insertInternal(int x, Node** cursor, Node** child);  //Insert x from child in cursor(parent)
    Node** findParent(Node* cursor, Node* child);
    Node* firstLeftNode(Node* cursor);
    void destroyTree(Node* node);                          //to clean memory

   public:
    bp_tree();
    bp_tree(int degreeInternal, int degreeLeaf);
    ~bp_tree();  // Destructor for proper cleanup
    Node* getRoot();
    int getMaxIntChildLimit();
    int getMaxLeafNodeLimit();
    void setRoot(Node *);
    void display(Node* cursor);
    void seqDisplay(Node* cursor);
    void search(int key);
    void insert(int key, FILE* filePtr);
    void removeKey(int key);
    void removeInternal(int x, Node* cursor, Node* child);
};