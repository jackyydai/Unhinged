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
ValueType* search(std::string key) const
{
    Node* p = head;
    std::string toBeAdded = key;
    std::string tempData;
    //bool turn = false;
    while(p->children[toBeAdded[0]] != nullptr)
    {
        
        p = p->children[toBeAdded[0]];
        //std::cout << "letter path: " << p->data << std::endl;
        tempData= p-> data;
        for(int i = 0; i < p->data.size(); i++)
        {
            if(tempData[0] == toBeAdded[0])
            {
                tempData = tempData.substr(1);
                toBeAdded = toBeAdded.substr(1);
        //        std::cout << " durring sub tobeadded: "<<toBeAdded << std::endl;
            }
            else
            {
                std::cout << tempData[0] << toBeAdded[0] << std::endl; 
                return nullptr; 
//                turn = true;
//                break;
            }
        }
//        if(turn)
//        {
//            break;
//        }
    }
    
    if(toBeAdded.size() > 0)
    {
        
        return nullptr;
    }
//    for(int i = 0; i < p->data.size(); i++)
//    {
//        std::cout << key[key.size()-p->data.size()+i]  <<   p->data[i] << std::endl;
//        if(key[key.size()-p->data.size()+i] != p->data[i])
//        {
//
//            return nullptr;
//        }
//    }
    //std::cout << "tobeadded: "<<toBeAdded << std::endl;
    //std::cout << "where the value should be " << p->data << std::endl;
    std::cout <<key<< "->>>";
    return p->value;
    
}
void insert(std::string key, const ValueType& value)
{
    std::cout << "----------- insert begin -------------" << std::endl;
    
    Node* p = head;
    std::string toBeAdded = key;
    std::string tempData;
    bool turn = false;
    while(p->children[toBeAdded[0]] != nullptr)
    {
        p = p->children[toBeAdded[0]];
        tempData= p-> data;
        for(int i = 0; i < p->data.size(); i++)
        {
            if(tempData[0] == toBeAdded[0])
            {
                tempData = tempData.substr(1);
                toBeAdded = toBeAdded.substr(1);
                std::cout <<"thing i want to add  " <<toBeAdded << std::endl;
                std::cout <<"thing already there  " << tempData << std::endl;
            }
            else
            {
                turn = true;
                break;
            }
        }
        if(turn)
        {
            break;
        }
        //toBeAdded = toBeAdded.substr(1);
    }
    std::cout << "insert 2: "<<toBeAdded << std::endl;
    std::cout << "insert 2 before: "<<tempData << std::endl;
    //bool turn = false;
    if(tempData.size() > 0)
    {
        Node* suffix = new Node();
        suffix->data = tempData;
        suffix->value = p->value;
        
        for(int i = 0; i < 128; i++)
        {
            suffix->children[i] = p->children[i];
            p->children[i] = nullptr;
        }
        
        p->data = p->data.substr(0, p->data.size() - tempData.size());
        std::cout <<"parent node data is now: " << p->data << std::endl;
        p->value = nullptr;
        p->children[suffix->data[0]] = suffix;
        std::cout << "suffix:" << suffix->data << std::endl;
        //std::cout << "suffix value:" << *suffix->value << std::endl;
    }
    
    
    p->children[toBeAdded[0]] = new Node();
    std::cout<< "at this path " << toBeAdded[0] << std::endl;
    std::cout << "inserting :" << toBeAdded << std::endl;
    p->children[toBeAdded[0]]->data = toBeAdded;
    ValueType* val = new ValueType(value);
    p->children[toBeAdded[0]]->value = val;
    //std::cout << *p->children[toBeAdded[0]]->value << std::endl;
    std::cout << "----------- insert end -------------" << std::endl;
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

