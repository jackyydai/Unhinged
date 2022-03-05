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
        attMap.insert(make_pair(attval.attribute, attval.value));
        m_attribute_num++; 
//    }

}


bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if(attribute_num < 0 || attribute_num > attMap.size() - 1)
    {
        return false;
    }
    auto p = attMap.begin();
    for(int i = 0; i < attribute_num; i++)
    {
        p++;
    }
    //attval = *p;
    attval.attribute = (*p).first;
    attval.value = (*p).second;

    //std::unordered_set<AttValPair>::iterator  p = std::attSet.begin()+attribute_num;


    return true;
}

