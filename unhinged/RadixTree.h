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
    ~RadixTree(){}
void insert(std::string key, const ValueType& value)
{
    Node* p = head;
    std::string toBeAdded = key;

    
    
    while(p->children[toBeAdded[0]] != nullptr)
    {
        
        p = p->children[toBeAdded[0]];
        key = toBeAdded;
        toBeAdded = toBeAdded.substr(1);
        if(toBeAdded == "")
        {
            ValueType* val = new ValueType(value);
            p->value = val;
            return;
        }
        //std::cout << toBeAdded << std::endl;
    }
    
    std::cout << "previous last node:" << p->data << std::endl;
    
    //std::string tempData = p->data;
//    if(p->data != "")
//    {
//        tempData = p->data.substr(1);
        std::cout << key << std::endl;
        std::cout << p->data << std::endl;
//    }
    bool turn = false;
    //bool end = false;
    Node* parent = p;
    while(p->data.size() > 1 && p->data[0] == key[0])
    {
       
        Node* suffix = new Node();
        suffix->data =p->data.substr(1);
        suffix->value = p->value;
        p->data = p->data[0];
        p->value = nullptr;
        parent = p;
        p->children[suffix->data[0]] = suffix;
        p = suffix;
        //tempData = suffix->data;
        if(turn)
        {
            toBeAdded = toBeAdded.substr(1);
        }
        key = toBeAdded;
        
        if(p->data.size() == 1)
        {
            parent = p;
            toBeAdded = toBeAdded.substr(1);
            break;
        }
        
        
//        std::cout << key << std::endl;
//        std::cout << p->data << std::endl;
//        std::cout << "suffix:" << suffix->data << std::endl;
//        std::cout << "suffix value:" << *suffix->value << std::endl;
        turn = true;
    }

    //std::cout << "last node data:" << parent->data << std::endl;
    
    if(toBeAdded == "")
    {
        ValueType* val = new ValueType(value);
        parent -> value = val;
        return;
    }
    
    parent->children[toBeAdded[0]] = new Node();
    //std::cout<< "at this path " << toBeAdded[0] << std::endl;
    
    std::cout << "letter path: " <<toBeAdded[0] << std::endl;
    //std::string added = toBeAdded.substr(1);
    
    std::cout << "inserting :" << toBeAdded << std::endl;
    
    parent->children[toBeAdded[0]]->data = toBeAdded;
    //std::cout << p->children[toBeAdded[0]]->data << std::endl;
    ValueType* val = new ValueType(value);
    //std::cout << val << std::endl;
    parent->children[toBeAdded[0]]->value = val;
//    std::cout << parent->children[toBeAdded[0]]->data << std::endl;
//    std::cout << *parent->children[toBeAdded[0]]->value << std::endl;
    
}

ValueType* search(std::string key) const
{
    Node* p = head;
    
    while(p->data != key && p->children[key[0]] != nullptr)
    {
        
        p = p->children[key[0]];
        std::cout << "letter path: " << p->data << std::endl;
        key = key.substr(1);
        std::cout << "key: " << key << std::endl;
        if(p->value != nullptr && key == "")
        {
            //std::cout <<"chunk 1:" <<  p->data << std::endl;
            return p->value;
        }
        //std::cout << p->children[key[0]]->data << std::endl; ;
        //std::cout << key << std::endl;
    }
    std::cout <<"chunk:" <<  p->data << std::endl;
//    std::cout << *(p->value) << std::endl;
//    int c = *(p->value);
//    std::cout << c << std::endl;
    return p->value;

}

private:
    struct Node
    {
        Node(): value(nullptr), children(), data("")
        {}
        Node* children[128];
        std::string data;
        ValueType* value;
    };
    Node* head;
    Node root;
};

#endif /* RadixTree_hpp */

