//
//  PersonProfile.c
//  unhinged
//
//  Created by Jacky Dai on 3/4/22.
//

#include "PersonProfile.h"
PersonProfile::PersonProfile(std::string name, std::string email)
: m_name(name), m_email(email), m_attribute_num(0)
{
}

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
//    if(attSet.find(attval) == attSet.end())
//    {
        //attMap.insert(make_pair(attval.attribute, attval.value));
    if(attSet.find(attval) == attSet.end())
    {
        attVec.push_back(attval);
        attSet.insert(attval);
        m_attribute_num++;
    }
        
//    }

}


bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if(attribute_num < 0 || attribute_num > attVec.size() - 1)
    {
        return false;
    }
    
    attval.attribute = attVec[attribute_num].attribute;
    attval.value = attVec[attribute_num].value;


    return true;
}

