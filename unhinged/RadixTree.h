//
//  RadixTree.hpp
//  unhinged
//
//  Created by Jacky Dai on 3/7/22.
//

#ifndef RadixTree_hpp
#define RadixTree_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

template <typename ValueType>
class RadixTree {
public:
RadixTree()
:head(&root)
{}
~RadixTree()
{
    Node* cur = head;
    for(int i = 0; i < 128; i ++) //delete all the subtrees from the root node so i do not call delete on the root node. Root node is not dynamically allocated
    {
        freeTree(cur->children[i]);
    }

}

void insert(std::string key, const ValueType& value)
{
    //std::cout << "----------- insert begin -------------" << std::endl;

    Node* n = head;
    std::string tempData;
    std::string toBeAdded = key;
    bool turn = false;
    while(n->children[toBeAdded[0]] != nullptr) //while loop thats goes through Radex tree to get to get node pointer to point at Targer Node
    {                                           //Target Pointer points at the node that will become a new parent node, node whose value will be replaced                                         and/or node that will be split in to its 2 chunks of word.
        n = n->children[toBeAdded[0]];          //makes p go down the letter path of the key(ToBeAddeded)
        tempData= n-> data;                     //temporary string that is set the current node's data
        for(int i = 0; i < n->data.size(); i++) //loops through  size of the current node's data
        {
            if(tempData[0] == toBeAdded[0])     //keep checking if every word in the current node matches with the node we want
            {
                tempData = tempData.substr(1);
                toBeAdded = toBeAdded.substr(1);
             //   std::cout <<"thing i want to add  " <<toBeAdded << std::endl;
             //   std::cout <<"thing already there  " << tempData << std::endl;
            }
            else                                //if it is not the same it will break out of evey loop becuase we have reached our Target Node.
            {
                turn = true;
                break;
            }
        }
        if(turn)
        {
            break;
        }
    }

    if(tempData.size() > 0) // if the tempData(a subscripted verison of a Node's data) is not 0, then we need to split a word to accommodate the key we are trying to add in the node already in the tree.
    {
        Node* suffix = new Node(); // create a new node that holds the last letters of the target node
        suffix->data = tempData; // takes all the information(ie. the Target node's data, value, valid status) and put it in the suffix node
        suffix->value = n->value;
        suffix->valid = true;

        for(int i = 0; i < 128; i++) // moves all the children node from the Target node to Suffix
        {
            suffix->children[i] = n->children[i];
            n->children[i] = nullptr;
        }

        n->data = n->data.substr(0, n->data.size() - tempData.size()); // set target node's data to the first letters of its original data.
        //std::cout <<"parent node data is now: " << p->data << std::endl;
        //p->value = nullptr;
        n->valid = false; // Target node's valid status is no longer valid because
        n->children[suffix->data[0]] = suffix;// reconnect suffix with target node
    }

    if((tempData.size() == 0 && toBeAdded.size()==0)||n->data == key) // if tempData and toBeadded is both empty strings or if target node's data is equal to the key, the node with the desired data is alread created and we simply replace the value of the target node and return.
    {
        //std::cout << "This node is already in the tree, replacing...  "<< std::endl;
        n->value = value;
        n->valid = true;
        //std::cout << "----------- insert end -------------" << std::endl;
        return;
    }
    n->children[toBeAdded[0]] = new Node(); //if we have not returned at this point we need to make a new leaf Node to the Radix tree
    n->children[toBeAdded[0]]->data = toBeAdded; // assign the data of the new node to toBeadded which is the Key substringed or the key itself
    n->children[toBeAdded[0]]->value = value; // value of this new leaf node is value
    n->children[toBeAdded[0]]->valid = true;// it is set as a valid node
}

ValueType* search(std::string key) const
{
    Node* n = head;
    std::string tempData;
    std::string toBeAdded = key;
    while(n->children[toBeAdded[0]] != nullptr) // code is similar to the code in insert to find the traget node
    {
        n = n->children[toBeAdded[0]]; // move to the next child based on the letter path of the key
        //std::cout << "letter path: " << p->data << std::endl;
        tempData= n-> data;
        for(int i = 0; i < n->data.size(); i++)
        {
            if(tempData[0] == toBeAdded[0])
            {
                tempData = tempData.substr(1);
                toBeAdded = toBeAdded.substr(1);
        //        std::cout << " durring sub tobeadded: "<<toBeAdded << std::endl;
            }
            else //if there is a difference in between the key and the node's letters, the key is not in the Radix tree and we return nullptr
            {
                //std::cout << tempData[0] << toBeAdded[0] << std::endl;
                return nullptr;
//                turn = true;
//                break;
            }
        }
    }

    if(!n->valid || toBeAdded.size() > 0)
    {
        return nullptr;
    }
    
    return &(n->value);


}




private:
    struct Node
    {
        Node():children(), data(""), valid(false)
        {}
        Node* children[128]; // each node contains an array, each spot in the array points to a different letter to represent the letterring path to ge to a desired key
        std::string data; //data stores the letters in each word which can be mapped together using the letter path of the array
        ValueType value; //value is the valuetype varaible that is being stored in each node.
        bool valid; //checks if each node is the end of a valid word
    };
    Node* head; // pointer to the root of the tree
    Node root;
    void freeTree(Node* cur)// recursively deletes the tree starting at a root node
    {
        if(cur == nullptr)
        {
            return;
        }
        for(int i = 0; i < 128; i++)
        {
            freeTree(cur->children[i]);
        }
        //std::cout << "\n Deleting node: " << cur->data << std::endl;
        delete cur;
    }
};



#endif /* RadixTree_hpp */


