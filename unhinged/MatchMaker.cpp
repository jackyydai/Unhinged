//
//  MatchMaker.cpp
//  unhinged
//
//  Created by Jacky Dai on 3/4/22.
//

#include "MatchMaker.h"
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


bool MatchMaker::greater(const EmailCount& lhs, const EmailCount& rhs)
{
    if(lhs.count > rhs.count)
    {
        return true;
    }
    if(lhs.count < rhs.count)
    {
        return false;
    }
    return lhs.email < rhs.email;
}

AttValPair MatchMaker::createAttPair(const string& line) const
{
    int cIndex = int(line.find(","));
    string att = line.substr(0, cIndex);
    string val = line.substr(cIndex + 1);
    AttValPair newPair(att, val);
    return newPair;
}

string MatchMaker::createString(AttValPair line) const
{
    return line.attribute + "," + line.value;
}



MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
:m_mdb(&mdb),m_at(&at)
{}


std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
    const PersonProfile* subject = m_mdb->GetMemberByEmail(email); // get person profile using email

    vector<EmailCount> ecVec; //create empty vector of emailcounts

    unordered_set<string> compadSet;

    //cout << "----------------------------compadable-------------------------------" << endl;
    for(int i = 0; i< subject->GetNumAttValPairs(); i++) //for loops through the attribute values of personprofile of the email that is mapped together
    {
        AttValPair temp;
        subject->GetAttVal(i, temp);
        vector<AttValPair> compadVec = m_at->FindCompatibleAttValPairs(temp); //gets a vector of compatable attvalpairs of each attval pair of PersonProfile
        for(int j = 0; j < compadVec.size(); j++)
        {
            compadSet.insert(createString(compadVec[j]));// inserts each attvalpair into a unordered set as a string to remove duplicates
        }
    }
    //cout << "---------------------------------------------------------------------------------" << endl;

    unordered_set<string> compadEmailSet;//

    for(unordered_set<string>::iterator p = compadSet.begin(); p != compadSet.end(); p++) //loops through entire compatable attvalpair set
    {
        AttValPair cAttVal = createAttPair(*p);
        vector<string> compadEmails = m_mdb->FindMatchingMembers(cAttVal); //gets a vector of emails from compatable attvalpairs
        for(int m = 0; m < compadEmails.size(); m++)
        {
            compadEmailSet.insert(compadEmails[m]);// inserts each email into a unodered set to remove duplicate emails
            
        }
    }

    for(unordered_set<string>::iterator q = compadEmailSet.begin(); q != compadEmailSet.end(); q++) // loops through compatableEmail set
    {
        const PersonProfile* cSubject = m_mdb->GetMemberByEmail(*q);// get each PersonProfile from the emails in the set
        int count = 0;
        //cout << "name: " << cSubject->GetName() << endl;
        for(int l = 0; l< cSubject->GetNumAttValPairs(); l++)//get each attvalpair of the personProfile
        {
            AttValPair potentialAttPair;
            cSubject->GetAttVal(l, potentialAttPair);
            
            if(compadSet.find(createString(potentialAttPair)) != compadSet.end()) //counts the number of compatable attval pairs that equal the person's attval pairs
            {
                count ++;
            }
        }
        if(count >= threshold) //if it meets the threshold create EmailCount and add it to the emailcount vector
        {
            EmailCount toBeAdded(*q,count);
            ecVec.push_back(toBeAdded);
        }
            
    }

    sort(ecVec.begin(),ecVec.end(),greater);//sort vector in descending order of the number of compatible attribute-value pairs, with ties broken by a secondary ordering in ascending alphabetical order by email address


    return ecVec;
}
