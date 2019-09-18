//
//  project.hpp
//  CS_2413_project
//
//  Created by Saransh Kalra on 11/26/18.
//  Copyright © 2018 Saransh Kalra. All rights reserved.
//

//
//  project.hpp
//  project
//
//  Created by Saransh Kalra on 12/3/18.
//  Copyright © 2018 Saransh Kalra. All rights reserved.
//

#ifndef project_hpp
#define project_hpp

#include <stdio.h>
#include <string>

using namespace std;

//node class for BST
class Node {
public:
    //variable info for storing name of the software
    string name;
    //variable for storing the version of the software
    string version;
    //variable for storing the quantity of software available
    int quantity;
    //variable for storing price of the software
    int price;
    //variable to store entry number in the system
    int entry_num;
    //constructor with no entry number
    Node(string, string, int, int);
    //constructor will all arguments
    Node(int, string, string, int, int);
    //default constructor
    Node();
    //default deconstructor
    ~Node();
    //left pointer to point to the left node in the BST
    Node *left;
    //right pointer to point to the right node in the BST
    Node *right;
    //function to display the information in the node
    void display();
};

class BST {
public:
    //root pointer to point to the root of the BST
    Node *root;
    //variable to store the number of entries in the the file even with quantity zero then at end cleanup gives the size of bst and the number of file entries
    int size;
    //constructor
    BST();
    //destructor
    ~BST();
    //destructor helper to make the destructor recursive
    void destr_helper(Node*);
    //insert function for inserting a new node into the BST i.e. a new software
    void insert(Node* node, int quantity);
    //search function for searching the node based on its name
    void search(string);
    //recursive search helper function to make search easier
    Node* search_helper(Node*, string);
    //recursive inorder traversal function to make the print easier
    void inorderTraversal(Node*);
    //recursive preorder traversal function to make the print easier
    void preorderTraversal(Node*);
    //recursive postorder traversal function to make the print easier
    void postorderTraversal(Node*);
    //print function to print the BST according to inorder, postorder, preorder traversal
    void print();
    //parent finder recursive helper for remove function
    Node* parent_helper(Node*, string);
    //remove function to remove the argument passed from the BST when quantity is zero
    void remove(string);
    //function to decrease the copies when sold
    void sell_copy(string, int quantity);
    //a function which searchs nodes based on entry number
    Node* search_by_ent_num (Node* node, int num);
    
};


#endif /* project_hpp */

