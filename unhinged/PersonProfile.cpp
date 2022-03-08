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
    map<std::string,std::string>::iterator p = attMap.find(attval.attribute);
    if(p == attMap.end())
    {
        attVec.push_back(attval);
        attMap.insert(make_pair(attval.attribute,attval.value));
    }
    else
    {
        if((*p).second != attval.value)
        {
            attVec.push_back(attval);
            attMap.insert(make_pair(attval.attribute,attval.value));
        }
    }
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

