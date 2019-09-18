//
//  project.cpp
//  project
//
//  Created by Saransh Kalra on 12/3/18.
//  Copyright © 2018 Saransh Kalra. All rights reserved.
//

#include <iostream>
#include "project.hpp"
#include "string.h"

using namespace std;

//constructor with no entry number
Node::Node(string name, string version, int quantity, int price) {
    this->name = name;
    this->version = version;
    this->quantity = quantity;
    this->price = price;
    this->left = this->right = NULL;
    this->entry_num = 0;
}

//constructor will all arguments
Node::Node(int entry_num, string name, string version, int quantity, int price) {
    this->name = name;
    this->version = version;
    this->quantity = quantity;
    this->price = price;
    this->left = this->right = NULL;
    this->entry_num = entry_num;
}

//default constructor
Node::Node() {
    this->name = " ";
    this->version = " ";
    this->quantity = 0;
    this->price = 0;
    this->left = this->right = NULL;
    this->entry_num = 0;
}

//desconstructor placeholder
Node::~Node() {
    
}

//function to display the information stored in the node
void Node::display() {
    cout<<" { Sno: "<<this->entry_num<<" Name: "<<this->name<<" Version: "<<this->version<<" Quantity: "<<this->quantity<<" Price: "<<this->price<<" } "<<endl;
}

//constructor for the BST class
BST::BST() {
    //initialises the root to 0
    this->root = NULL;
    //intializes size to zero
    this->size = 0;
}

//destructor for the BST class
BST::~BST(){
    //caling the destructor helper with root as the argument
    this->destr_helper(this->root);
}

//recursive destructor helper function for making destructor easier
void BST::destr_helper(Node* node){
    //if node exists
    if(node){
        //do postorder traversal for the whole BST and delete all the nodes
        this->destr_helper(node->left);
        this->destr_helper(node->right);
        delete node;
    }
}
//insert function for inserting a new node to the BST with quantity, if a new entry added no matter what quantity is but if it is already in the BST quantiy is used to update its Quantity if more copies came in
void BST::insert(Node* node, int quantity) {
    //if root doesn't exist
    if(!this->root) {
        //assign the current size + 1 as the new node is added
        node->entry_num = ++this->size;
        //assign that node to the root
        this->root = node;
    }
    //else add according to its name if its bigger ,smaller or equal to
    else {
        //variable flag to exit out of the loop
        int flag = 0;
        //make a traversal node initialized to root
        Node *p1 = this->root;
        //while flag is 0, be in the loop i.e. we can exit the loop whenever we want to making flag 1
        while(flag==0) {
            //if the value to be added is greater that the traversal node it will be stored in the right side
            if(node->name.compare(p1->name) > 0) {
                //if a right exists then update the traversal node to be its right
                if(p1->right) {
                    p1 = p1->right;
                }
                //if a right doesnt exist then add the new node at the right and make flag 1 to exit out of the loop
                else {
                    node->entry_num = ++this->size;
                    p1->right = node;
                    flag = 1;
                }
            }
            //if the value to be added is less than the current traversal node then it would be stored in the left side
            else if (node->name.compare(p1->name) < 0) {
                //if a left exists then update the traversal node to be its left
                if(p1->left) {
                    p1 = p1->left;
                }
                //if a left doesnt exist then add the new node at the left and make flag 1 to exit out of the loop
                else {
                    node->entry_num = ++this->size;
                    p1->left = node;
                    flag = 1;
                }
            }
            //else it means its equal to the node info already in ther tree which means we should update its quantity and exit the loop by making flag 1
            else {
                p1->quantity = p1->quantity + quantity;
                flag = 1;
            }
        }
    }
}

//search function for searching the software by name in the BST
void BST::search(string name) {
    //if there is no root give error that the BST is empty
    if(!this->root) {
        cout<<"Nothing to search for! The Binary Search Tree is empty"<<endl;
    }
    //else search for the node
    else {
        //if the search hepler function returns true then display that this value exists in the  BST
        if(this->search_helper(this->root, name)) {
            cout<<"Yes, "<<name<<" exists in the Binary Search Tree."<<endl;
        }
        //else display that it doesn't exist in the BST
        else {
            cout<<"The software "<<name<<" was not found in the Binary Search Tree."<<endl;
        }
    }
}

//recursive search helper function to make search easier
Node* BST::search_helper(Node *node, string name) {
    //if a node doesn't exist return the node i.e. NULL
    if(!node) {
        //return false
        return node;
    }
    //if the value is found at this node return the node
    else if (node->name.compare(name) == 0) {
        //return true
        return node;
    }
    //if its less than the node passed as argument then pass the left of the node as an argument and call the search helper again because if it is in BST will be found to the left
    else if (name.compare(node->name) < 0) {
        return this->search_helper(node->left, name);
    }
    //if its more than the node passed as argument then pass the right of the node as an argument and call the search helper again because if it is in BST will be found to the right
    else {
        return this->search_helper(node->right, name);
    }
}

//recursive inorder traversal function to make the print easier
void BST::inorderTraversal(Node *temp) {
    //if temp exists follow LVR that means go to left then print that node and then go to right
    if(temp) {
        inorderTraversal(temp->left);
        temp->display();
        inorderTraversal(temp->right);
    }
}

//recursive preorder traversal function to make the print easier
void BST::preorderTraversal(Node *temp) {
    //if temp exists follow VLR that means print that node then go to left and then go to right
    if(temp) {
        temp->display();
        preorderTraversal(temp->left);
        preorderTraversal(temp->right);
    }
}

//recursive postorder traversal function to make the print easier
void BST::postorderTraversal(Node *temp) {
    //if temp exists follow LRV that means go to left then go to right and then print that node
    if(temp) {
        postorderTraversal(temp->left);
        postorderTraversal(temp->right);
        temp->display();
    }
}

//print function to print the BST according to inorder, preorder and postorder traversal
void BST::print() {
    //if the root doesn't exist, give an error that the BST is empty
    if(!this->root) {
        cout<<"Nothing to display! The Binary Search Tree is empty"<<endl;
    }
    // else just call the inorder, preorder and postorder traversal helper with root as the argument and print the BST with that in that particular order
    else {
        cout<<" Inorder Traversal: "<<endl;
        cout<<"{ ";
        inorderTraversal(this->root);
        cout<<"}"<<endl;
        
        cout<<" Preorder Traversal: "<<endl;
        cout<<"{ ";
        preorderTraversal(this->root);
        cout<<"}"<<endl;
        
        cout<<" Postorder Traversal: "<<endl;
        cout<<"{ ";
        postorderTraversal(this->root);
        cout<<"}"<<endl;
    }
}


//parent finder recursive helper for remove function
Node* BST::parent_helper(Node *node, string name) {
    //if the node doesn't exist
    if (node == NULL) {
        //return NULL
        return NULL;
    }
    //else if the root is the node to be deleted then return null as it has no parent
    else if (node->name.compare(name)==0) {
        return NULL;
    }
    //else if it has two children
    else if (node->right && node->left) {
        //return the node as parent of any of its children have the value to be deleted
        if ((node->left->name.compare(name)==0) || (node->right->name.compare(name)==0)) {
            //return true
            return node;
        }
        //else if the current node has value bigger than whats required go to the left of it
        else if (name.compare(node->name) < 0) {
            return this->parent_helper(node->left, name);
        }
        //else go the right of it
        else {
            return this->parent_helper(node->right, name);
        }
    }
    //else if the node has just a right child just check the right child
    else if (node->right && !node->left) {
        //if the right child has the node to be deleted return the node as parent
        if (node->right->name.compare(name)==0) {
            //return true
            return node;
        }
        //else if the current node has value bigger than whats required go to the left of it
        else if (node->name.compare(node->name) < 0) {
            return this->parent_helper(node->left, name);
        }
        //else go the right of it
        else {
            return this->parent_helper(node->right, name);
        }
    }
    //else if the node has just a left child just check the right child
    else if (!node->right && node->left) {
        //if the left child has the node to be deleted return the node as parent
        if (node->left->name.compare(name)==0) {
            //return true
            return node;
        }
        //else if the current node has value bigger than whats required go to the left of it
        else if (name.compare(node->name) < 0) {
            return this->parent_helper(node->left, name);
        }
        //else go the right of it
        else {
            return this->parent_helper(node->right, name);
        }
    }
    //else
    else {
        //if the current node has value bigger than whats required go to the left of it
        if (name.compare(node->name) < 0) {
            return this->parent_helper(node->left, name);
        }
        //else go the right of it
        else {
            return this->parent_helper(node->right, name);
        }
    }
}

//function to decrease the copies when sold
void BST::sell_copy(string name, int quantity) {
    //variable to store the node whose quantity is to be decreased, searched in the BST using search helper
    Node *remNode = this->search_helper(this->root, name);
    //if the node to be deleted doesn't exist then display error that the value deos not exist in the BST
    if (!remNode) {
        cout<<"Software copies you want to enter as sold is not in the system! "<<endl;
    }
    //else
    else {
        //if quantity entered is more than available display an error
        if(quantity > remNode->quantity) {
            cout<<"There is some problem as the number of items you want to sell are greater than there are in the system";
        }
        //else decrease the quantity as per the argument passed
        else {
            remNode->quantity = remNode->quantity - quantity;
        }
    }
}

//a function which searches nodes based on entry number
Node* BST::search_by_ent_num(Node* node, int num) {
    //if node exits
    if(node) {
        //return node if entry number of the node is equal to the argument
        if(node->entry_num == num) {
            return node;
        }
        //else keep finding
        else {
            //if node left has the number find it there and return the function itself so whenever it finds the record it keep returning to the parent recursive call so we have the node we need in the end
            if(search_by_ent_num(node->left,num)) {
                return search_by_ent_num(node->left,num);
            }
            //else if node right has the number find it there and return the function itself so whenever it finds the record it keeps returning to the parent recursive call so we have the node we need in the end
            else if(search_by_ent_num(node->right,num)) {
                return search_by_ent_num(node->right,num);
            }
            //else return nothing i.e. null
            else {
                return 0;
            }
        }
    }
    //else return nothing i.e. null
    else {
        return 0;
    }
}

//remove function to remove the argument passed from the BST when quantity is zero
void BST::remove(string name) {
    //variable to store the node to be deleted, searched in the BST using search helper
    Node *remNode = this->search_helper(this->root, name);
    //if the node to be deleted doesn't exist then display error that the value deos not exist in the BST
    if (!remNode) {
        cout<<"Software copies you want to enter as sold is not in the system! "<<endl;
    }
    //else
    else {
        //serach for the parent of the node to be deleted using parent helper and store in this variable
        Node *remNode_parent = parent_helper(this->root, name);
        
        //if the node to be deleted has no child
        if(!(remNode->right || remNode->left)) {
            //if the node to be deleted has a parent
            if(remNode_parent) {
                //if the node to be deleted is the left child then set the left child of the parent to be null
                if(remNode->name.compare(remNode_parent->name) < 0) {
                    remNode_parent->left = 0;
                }
                //else it is the right child then set the right child of the parent to be null
                else {
                    remNode_parent->right = 0;
                }
            }
            //else it means it doesnt have a parent, so its the root, set it to be null
            else {
                this->root = 0;
            }
            //delete the node
            delete remNode;
        }
        
        //else if the node to be deleted has two children
        else if(remNode->right && remNode->left) {
            //make a temporary pointer which will store the value that will take the place of the deleted node initialised to the right of the node to be deleted
            Node *temp = remNode->right;
            //while there is a left go to left means the leftmost node
            while(temp->left) {
                temp = temp->left;
            }
            //make the remnode parent store the parent of the node that will take place of the deleted node using parent helper
            remNode_parent = parent_helper(this->root, temp->name);
            //if the value that will replace is a right child
            if(temp->name.compare(remNode_parent->name) > 0) {
                //then set its parent's right to be its right
                remNode_parent->right = temp->right;
            }
            //else set its parent's left to be its right
            else {
                remNode_parent->left = temp->right;
            }
            //replace the value in place of node to be deleted
            remNode->name = temp->name;
            //finally delete the node
            delete temp;
        }
        
        //else means it has only one child
        else {
            //if it doesnt have a parent meaning its the root
            if(!remNode_parent) {
                //if it has a left child
                if(remNode->left) {
                    //set the left child to be the new root
                    this->root = remNode->left;
                }
                //else set the right child to be the new root
                else {
                    this->root = remNode->right;
                }
            }
            
            //else its not a root then
            else {
                //if it has a left child only
                if(remNode->left) {
                    //if the value to be deleted was the left child
                    if(remNode->name.compare(remNode_parent->name) < 0) {
                        //set the left child to be the deleted node's left
                        remNode_parent->left = remNode->left;
                    }
                    //else set the right child to be the deleted node's left
                    else {
                        remNode_parent->right = remNode->left;
                    }
                }
                //else it has a right child only
                else {
                    //if the value to be deleted was the left child
                    if(remNode->name.compare(remNode_parent->name) < 0) {
                        //set the left child to be the deleted node's right
                        remNode_parent->left = remNode->right;
                    }
                    //else set the right child to be the deleted node's right
                    else {
                        remNode_parent->right = remNode->right;
                    }
                }
                //finally delete the node
                delete remNode;
            }
        }
    }
}
