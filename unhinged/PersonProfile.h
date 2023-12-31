//
//  PersonProfile.h
//  unhinged
//
//  Created by Jacky Dai on 3/4/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include "provided.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <map>// get rid of this pls
#include "RadixTree.h"

class AttValPair;
class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email);
    
    //This constructs a PersonProfile object, specifying the member’s name and email address.
    ~PersonProfile(){};
    
    
    //You may define a destructor for PersonProfile if you need one.
    std::string GetName() const
    {
        return m_name;
    }
    
    
    //The GetName method returns the member’s name.
    std::string GetEmail() const
    {
        return m_email;
    }
    
    
    //The GetEmail method returns the member’s email address.
    void AddAttValPair(const AttValPair& attval);
//    The AddAttValPair method is used to add a new attribute-value pair to the member’s profile. If
//    the person’s profile already has an attribute-value pair with the same attribute and value as the
//    attval parameter, then this method should do nothing. More than one attribute-value pair in the
//    map can have the same attribute, as long as their corresponding values are different. We place
//    no requirements on the order that you must store your attribute-value pairs.
    
    
    
    int GetNumAttValPairs() const
    {
        return int(attVec.size());
    }
//    This method returns the total number of distinct attribute-value pairs associated with this
//    member.
    
    bool GetAttVal(int attribute_num, AttValPair& attval) const;

private:
    std::string m_name;
    std::string m_email;
    //int m_attribute_num;
    //std::map<std::string, std::string> attMap;
    RadixTree<std::unordered_set<std::string>> attRTset; // radix tree that maps attributes to values
     
    std::vector<AttValPair> attVec; // vector that stores attValPairs so that we can retrieve AttVal using a index(attribute_num)
    //std::set<AttValPair> attSet;
    
};


#endif /* PersonProfile_h */

