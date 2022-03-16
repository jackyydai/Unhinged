//
//  PersonProfile.c
//  unhinged
//
//  Created by Jacky Dai on 3/4/22.
//

#include "PersonProfile.h"
using namespace std;
PersonProfile::PersonProfile(std::string name, std::string email)
: m_name(name), m_email(email)//, m_attribute_num(0)
{
}

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
    std::unordered_set<std::string>* q = attRTset.search(attval.attribute); //gets a set pointer based on the attribute
    
    if(q == nullptr) // if the set deos not exist in the tree we create a new set with the attval.value inside and add to the vector
    {
        attVec.push_back(attval);
        
        std::unordered_set<std::string> setTBA;
        setTBA.insert(attval.value);
        attRTset.insert(attval.attribute, setTBA);
    }
    else
    {
        if((*q).find(attval.value) == (*q).end()) //checks if the value already exist in the set, if not, add it to the vector and the set
        {
            attVec.push_back(attval);
            
            (*q).insert(attval.value);
            
        }// if it does exist, do nothing and do not create dup
    }
}


bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if(attribute_num < 0 || attribute_num > attVec.size() - 1) // checks if the attribute_num is contained in the range of the vector (0 to length of the vector)
    {
        return false;
    }
    
    attval.attribute = attVec[attribute_num].attribute; //sets the attval's attribute and value
    attval.value = attVec[attribute_num].value;
    return true;
}

