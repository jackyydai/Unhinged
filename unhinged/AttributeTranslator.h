//
//  AttributeTranslator.hpp
//  unhinged
//
//  Created by Jacky Dai on 3/4/22.
//

#ifndef AttributeTranslator_hpp
#define AttributeTranslator_hpp

#include <stdio.h>

#include "provided.h"
#include <vector>
#include <map>
#include "RadixTree.h"


class AttributeTranslator
{
public:
    AttributeTranslator();
//    This is the AttributeTranslator constructor. It must take no arguments.
//    7
    ~AttributeTranslator(){}
//    You may define a destructor for AttributeTranslator if you need one to free any dynamically
//    allocated memory used by your object.
    bool Load(std::string filename);
//    This method loads the attribute-value translation data from the data file specified by the
//    filename parameter. The method must load the data into a data structure that enables efficient
//    translation of attribute-value pairs (meeting the big-O requirements at the top of this section).
//    The method must return true if the file was successfully loaded and false otherwise.
//    As described above, the text file consists of one or more lines (likely thousands of lines) with the
//    following format:
//    source_attribute,source_value,compatible_attribute,compatible_value
//    You must ignore all empty lines. You may assume that there are no extraneous spaces before
//    or after any comma or at the beginning or end of any line, and that neither attributes nor values
//    will have any commas in them. You may assume that the file is all lower-case and you do not
//    need to do case-insensitive checks.
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
//    This method must identify all compatible attribute-value pairs for the specified source attributevalue pair in an efficient manner (meeting the requirements at the top of this section) and return
//    a vector containing them. If there are no compatible pairs, the vector returned must be empty.
//    There is no particular order required for the AttValPairs in the vector returned. The vector
//    returned must not contain two attribute-value pairs with the same attributes and values (i.e., no
//    duplicates).
//    Given a line from the sample translation file above, e.g.,:
//    favorite_food,del taco,favorite_food,mexican
//    The first two terms represent the source attribute and sourc
private:
    RadixTree<std::vector<AttValPair>> attTransRT;//maps source attribute-value information to compatible attribute-values(vector)

};



#endif /* AttributeTranslator_hpp */
