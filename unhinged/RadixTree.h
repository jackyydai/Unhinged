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


template <typename ValueType>
class RadixTree {
public:
 RadixTree();
 ~RadixTree();
 void insert(std::string key, const ValueType& value);
 ValueType* search(std::string key) const;
    
private:
    struct Node
    {
        vector<*Node> children;
    }
};

#endif /* RadixTree_hpp */
