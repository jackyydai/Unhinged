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
//        if(toBeAdded == "")
//        {
//            std::cout << "skfjhvrskuheukshisekhvbkshvks" << std::endl;
//            ValueType* val = new ValueType(value);
//            p->value = val;
//            return;
//        }
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
        
        
        std::cout << key << std::endl;
        std::cout << p->data << std::endl;
        std::cout << "suffix:" << suffix->data << std::endl;
        std::cout << "suffix value:" << *suffix->value << std::endl;
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
    std::cout<< "at this path " << toBeAdded[0] << std::endl;
    
    std::cout << "letter path: " <<toBeAdded[0] << std::endl;
    //std::string added = toBeAdded.substr(1);
    
    std::cout << "inserting :" << toBeAdded << std::endl;
    
    parent->children[toBeAdded[0]]->data = toBeAdded;
    //std::cout << p->children[toBeAdded[0]]->data << std::endl;
    ValueType* val = new ValueType(value);
    //std::cout << val << std::endl;
    parent->children[toBeAdded[0]]->value = val;
    std::cout << parent->children[toBeAdded[0]]->data << std::endl;
    std::cout << *parent->children[toBeAdded[0]]->value << std::endl;
    
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
ValueType* search2(std::string key) const
{
    Node* p = head;
    std::string toBeAdded = key;
    std::string tempData;
    while(p->children[toBeAdded[0]] != nullptr)
    {
        
        p = p->children[toBeAdded[0]];
        std::cout << "letter path: " << p->data << std::endl;
        tempData= p-> data;
        for(int i = 0; i < p->data.size(); i++)
        {
            if(tempData[0] == toBeAdded[0])
            {
                tempData = tempData.substr(1);
                toBeAdded = toBeAdded.substr(1);
                std::cout << " durring sub tobeadded: "<<toBeAdded << std::endl;
            }
            else
            {
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
//    if(toBeAdded.size() > 0)
//    {
//        return nullptr;
//    }
//    for(int i = 0; i < p->data.size(); i++)
//    {
//        std::cout << key[key.size()-p->data.size()+i]  <<   p->data[i] << std::endl;
//        if(key[key.size()-p->data.size()+i] != p->data[i])
//        {
//
//            return nullptr;
//        }
//    }
    std::cout << "tobeadded: "<<toBeAdded << std::endl;
    std::cout << "where the value should be " << p->data << std::endl;
    std::cout <<key<< "->>>";
    return p->value;
    
}
void insert2(std::string key, const ValueType& value)
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
    std::cout << *p->children[toBeAdded[0]]->value << std::endl;
//    Node* parent = p;
//    
//    parent->children[toBeAdded[0]] = new Node();
//    std::cout<< "at this path " << toBeAdded[0] << std::endl;
//    
//    std::cout << "letter path: " <<toBeAdded[0] << std::endl;
//    //std::string added = toBeAdded.substr(1);
//    
//    std::cout << "inserting :" << toBeAdded << std::endl;
//    
//    parent->children[toBeAdded[0]]->data = toBeAdded;
//    //std::cout << p->children[toBeAdded[0]]->data << std::endl;
//    ValueType* val = new ValueType(value);
//    //std::cout << val << std::endl;
//    parent->children[toBeAdded[0]]->value = val;
//    std::cout << parent->children[toBeAdded[0]]->data << std::endl;
//    std::cout << *parent->children[toBeAdded[0]]->value << std::endl;
    
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

