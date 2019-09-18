//
//  main.cpp
//  CS_2413_project
//
//  Created by Saransh Kalra on 11/26/18.
//  Copyright © 2018 Saransh Kalra. All rights reserved.
//

//
//  main.cpp
//  project
//
//  Created by Saransh Kalra on 12/3/18.
//  Copyright © 2018 Saransh Kalra. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "project.hpp"
#include <string>

using namespace std;
//global variable fro bst
BST bst;

//function for taking input from the user for the software information to be added
Node* User_insert_input() {
    cin.ignore();
    string name,version;
    int quantity, price;
    cout<<"Enter the name of the software: "<<endl;
    getline(cin,name);
    cout<<"Enter the version of the software: "<<endl;
    getline(cin,version);
    cout<<"Enter the quantity of the software: "<<endl;
    cin>>quantity;
    cout<<"Enter the price of the software: "<<endl;
    cin>>price;
    
    //create a pointer to a node with the information entered by the user and return it
    Node* node = new Node(name, version, quantity, price);
    return node;
}

//function for taking input from the user for the software information to be added when already taken the name from the user
Node* User_insert_input(string name) {
    cin.ignore();
    string version;
    int quantity, price;
    cout<<"Enter the version of the software: "<<endl;
    getline(cin,version);
    cout<<"Enter the quantity of the software: "<<endl;
    cin>>quantity;
    cout<<"Enter the price of the software: "<<endl;
    cin>>price;
    
    //create a pointer to a node with the information entered by the user and return it
    Node* node = new Node(name, version, quantity, price);
    return node;
}

//function to check if the file exists
bool is_file_exist(string file_name)
{
    ifstream infile(file_name.c_str());
    return infile.good();
}

//fuction for reading the file and storing as a bst
void store_as_BST(string file_name) {
    //opening the file in binary input output mode
    fstream f;
    f.open(file_name.c_str(),ios::in|ios::out|ios::binary);
    
    Node node;
    Node* node1;
    
    //while there are more records to read
    while(f.read((char*)&node, sizeof(node)))
    {
        //read the record and create a pointer pointing to that node of information
        node1 = new Node (node.entry_num, node.name, node.version, node.quantity, node.price);
        //add that pointer to the bst
        bst.insert(node1,0);
    }
    //printing the bst according to the file taht was read
    cout<<"BST According to the file: "<<endl;
    bst.print();
    
    //closing the file
    f.close();
}

//function to insert the a new node into the file
void file_insert(Node *node, string file_name) {
    //opening the file in output append mode
    ofstream outFile;
    outFile.open(file_name.c_str(), ios::out | ios::binary | ios::app);
    //creating a node with teh information teh pointer passed as an argument possesses
    Node node1 (node->entry_num, node->name, node->version, node->quantity, node->price);
    //write that node to the file
    outFile.write((char*)&node1, sizeof(node1));
    //close the file
    outFile.close();
}

//function for writing a file if it doesn't exist
void write_in_file(string file_name) {
    int num;
    cout<<"The file is empty you will need to add some software entries! "<<endl;
    cout<<"So, how many entries do you want to add? "<<endl;
    //taking the number of softwares the user wantes to amke entries for
    cin>>num;
    
    Node* node;
    
    //for loop to ask the user input as much number of times as he wanted to enter
    for (int i = 0; i < num; i++) {
        //taking the input from teh suer and storing it in a pointer
        node = User_insert_input();
        cout<<" ENTRY ADDED: "<<endl;
        //dislplaying what entry was added to the file
        node->display();
        //calling the insewrt to file function to add the record to the file
        file_insert(node, file_name);
    }
}

//function for updating the quantity of a particular software in the file
void file_sold_or_more_copies(string name, string file_name) {
    //opening the file file in binary input output ate mode
    fstream f;
    f.open(file_name.c_str(),ios::in|ios::out|ios::binary|ios::ate);
    //bringing the pointer to the start of the file
    f.seekg(0);
    Node node;
    
    Node* node1;
    Node node2;
    
    //while there are records left to read
    while(f.read((char*)&node,sizeof(node)))
    {
        //if we find the node which matches the node's name we want to change the quantity for
        if((node.name).compare(name)==0)
        {
            //get a pointer to point to that particular node in teh bst as it as the updated record for that node
            node1 = bst.search_helper(bst.root, name);
            //create a node which has the same information as the pointer to overwrite that record in the file with the updated one
            node2.entry_num = node1->entry_num;
            node2.name = node1->name;
            node2.version = node1->version;
            node2.quantity = node1->quantity;
            node2.price = node1->price;
            //move the pointer the size of the node back from the current position
            f.seekp(-sizeof(node2),ios::cur);
            //overwrite the updated record on top of the old record
            f.write((char*)&node2,sizeof(node2));
            //break out of the loop since the updation is done
            break;
        }
    }
    //close the file
    f.close();
    //make the two pointers the same as they are basically teh same so the destructor will be called twice for the same memory which is not possible as the space has already been freed
    node = node2;
}

//clean up file function which replaces the node with quantity zero with the node at last in the file
void cleanup(string file_name) {
    //opening the file in binary out mode
    ofstream outFile;
    outFile.open("temp.dat", ios::out | ios::binary);
    
    Node* node9;
    Node node8;
    
    //loop for putting the whole bst into the file running till the bst ends
    for(int i = 1; i <= bst.size; i++) {
        //node pointing to the node having teh corresponding entry number
        node9 = bst.search_by_ent_num (bst.root, i);
        //if it exists then write it in the new file
        if(node9) {
            node8.entry_num = node9->entry_num;
            node8.name = node9->name;
            node8.version = node9->version;
            node8.quantity = node9->quantity;
            node8.price = node9->price;
            outFile.write((char*)&node8,sizeof(node8));
        }
        //if not means we deleted it from the bst
        else {
            //if thats the case take the last record
            node9 = bst.search_by_ent_num (bst.root, bst.size);
            //checking if the deleted record was the last one
            if(node9) {
                //if not then change the entry number to the number missing
                node8.entry_num = i;
                node8.name = node9->name;
                node8.version = node9->version;
                node8.quantity = node9->quantity;
                node8.price = node9->price;
                //write the last node in place of the deleted node
                outFile.write((char*)&node8,sizeof(node8));
            }
            //make the bst less by 1 since the last record is already written in place of teh deleted one ad we dont need to keep a record of how many there are in the file now as we are creating a new one in its place
            bst.size--;
        }
        node9= NULL;
        
    }
    
    //close the file
    outFile.close();
    
    //remove the old file
    remove(file_name.c_str());
    //rename the temporary file into the file name we want
    rename("temp.dat",file_name.c_str());

    
}

int main() {
    int choice;
    int flag = 0;
    string file_name;
    file_name="s1.dat";
    
    //if the fiel already exists store it as bst
    if(is_file_exist(file_name.c_str())) {
        store_as_BST(file_name);
    }
    //if not create the file by writing to it and read from it again to create the bst ensuring taht data was written to it
    else {
        write_in_file(file_name);
        store_as_BST(file_name);
    }
    
    //displaying the menu
    cout<<endl;
    cout<<"SOFTWARE MANAGEMENT SYSTEM"<<endl;
    cout<<"--------------------------"<<endl;
    cout<<"1. Make an entry for a software that came in "<<endl;
    cout<<"2. Make an entry for the copies sold "<<endl;
    cout<<"3. Check the status of a software in the system "<<endl;
    cout<<"4. Exit "<<endl;
    cout<<"Enter your choice: "<<endl;
    cin>>choice;
    cout<<endl;
    
    Node* node;
    
    //don't exit the loop until the exit function is called
    while(flag == 0) {
        //if teh choice is 1 i.e. making an entry for software that came in
        if (choice == 1) {
            //take the name of the software that came in
            cin.ignore();
            string name;
            cout<<"Enter the name of the software which you want to make an entry for: "<<endl;
            getline(cin, name);
            //if its a new record display a warning message to enter two times after inputing the name as cin.ignore creates a problem
            if (!bst.search_helper (bst.root, name)) {
                cout<<"Press enter once more in order to continue..."<<endl;
            }
            //if the software is already in the system, increase its copies
            if (bst.search_helper (bst.root, name)) {
                int quantity;
                //take input for how many copies came in
                cout<<"Enter the number of copies that were added: "<<endl;
                cin>>quantity;
                //call teh bst insert function with the quantity as an argument to update the entry in the bst
                bst.insert (bst.search_helper (bst.root, name), quantity);
                //call the quantity update file function to update the record in the file
                file_sold_or_more_copies(name, file_name);
                //display the updated entry
                cout<<" UPDATED ENTRY: "<<endl;
                bst.search_helper (bst.root, name)->display();
            }
            //else insert the new software into the system
            else {
                //take everything else from teh user except name because he entered it already
                node = User_insert_input(name);
                //insert the node in the BST
                bst.insert(node,0);
                //insert the node in the file
                file_insert(node, file_name);
                //display the entry added
                cout<<" ENTRY ADDED: "<<endl;
                node->display();
            }
        }
        //else if choice is 2 i.e. making an entry for the copies sold for a software
        else if (choice == 2) {
            int quantity;
            //take the name of the software from the user whose copies were sold
            string name;
            cout<<"Enter the name of the software whose copies were sold: "<<endl;
            cin.ignore();
            getline(cin, name);
            //take the number of copies that were sold from the user
            cout<<"Enter the number of copies that were sold: "<<endl;
            cin>>quantity;
            //call the sell copy function in the bst to update that particular record in the bst
            bst.sell_copy(name, quantity);
            //call the update quantity function for the file to update that particular record in the file
            file_sold_or_more_copies(name, file_name);
            cout<<"Updated Entry: "<<endl;
            //display the updated entry if it exists
            if(bst.search_helper(bst.root, name)) {
                bst.search_helper(bst.root, name)->display();
            }
            //if the quantity becomes zero, dislpay message that stock was sold out and remove it from the bst
            if (bst.search_helper(bst.root, name)->quantity == 0) {
                bst.remove(name);
                cout<<"Entry deleted! Because stock ran out!"<<endl;
            }
        }
        //else if choice is 3 i.e. check the status of a software in the system
        else if (choice == 3) {
            //ask the user for what software he wants to check for the availability in the system
            string name;
            cout<<"Enter the name of the software whose status you want to check: "<<endl;
            cin.ignore();
            getline(cin, name);
            //search for the name in the bst
            bst.search(name);
            //if teh record exists display it
            if(bst.search_helper(bst.root, name)) {
                bst.search_helper(bst.root, name)->display();
            }
        }
        //else if choice is 4 i.e. exit
        else if (choice == 4) {
            //call the cleanup file function to update the zero quantity records
            cleanup(file_name);
            //print the file bst before exiting with the serial numbers unupdated as opposed to the file which has them correct and next time they will be as per the file
            cout<<"Final BST: "<<endl;
            bst.print();
            //put the flag as 1 to exit out of the loop
            flag = 1;
        }
        // else give an error of invalid choice to the user and ask for input again
        else {
            cout<<"Invalid Choice! Try Again!"<<endl;
            cout<<"Enter your choice: "<<endl;
            cin>>choice;
        }
        //if the choice was not 4 ask for the input again
        if(choice != 4) {
            cout<<"Enter your choice: "<<endl;
            cin>>choice;
        }
    }
    return 0;
}

