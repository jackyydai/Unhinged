//
//  MemberDatabase.cpp
//  unhinged
//
//  Created by Jacky Dai on 3/4/22.
//

#include "MemberDatabase.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

AttValPair MemberDatabase::createAttPair(string line)
{
    int cIndex = int(line.find(","));
    string att = line.substr(0, cIndex);
    string val = line.substr(cIndex + 1);
    AttValPair newPair(att, val);
    return newPair;
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
    
    string line;
    ifstream infile;
    infile.open(filename);
    if(!infile)
    {
        return false;
    }
    while(getline(infile, line, '\n'))
    {
        string name;
        string email;
        string strOfAtt;
        
        //getline(infile, line, '\n');
        name = line;
        //cout << name << endl;
        
        getline(infile, line, '\n');
        email = line;
        //cout << email <<  endl;

        getline(infile, line, '\n');
        strOfAtt = line;
        //cout << strOfAtt << endl ;
        int numOfAtt = stoi(strOfAtt);
        //cout << numOfAtt << endl;
        
        
        
        if(emailPerson.find(email) != emailPerson.end())
        {
            //cout << "hi" ;
            return false;
        }
        PersonProfile* person = new PersonProfile(name,email);
        for(int i = 0; i < numOfAtt; i++)
        {
            string sPair;
            getline(infile, line, '\n');
            sPair = line;
            AttValPair aPair = createAttPair(sPair);
            person->AddAttValPair(aPair);
            map<string, vector<string>>::iterator p = pairEmails.find(sPair);
            //string compatibleKey = cAtt + "," + cVal;
            if(p == pairEmails.end())
            {
                vector<string> toBeAdded;
                toBeAdded.push_back(email);
                pairEmails.insert(make_pair(sPair, toBeAdded));
            }
            else
            {
                bool end = false;
                for(int i = 0; i < (*p).second.size(); i++)
                {
                    if(email == ((*p).second)[i])
                    {
                        end = true;
                        break;
                    }
                }
                if(!end)
                {
//                    if(find((*p).second.begin(),(*p).second.end(),email) == (*p).second.end())
//                    {
                        (*p).second.push_back(email);
                    //}
                }
            }
        }
        emailPerson.insert(make_pair(email, person));
        getline(infile, line, '\n');
    }
    infile.close();
    return true;
    
    
    
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    string search = input.attribute + "," + input.value;
    map<string, vector<string>>::const_iterator p = pairEmails.find(search);
    if(p == pairEmails.end())
    {
        vector<string> nothing;
        return nothing;
    }
    else
    {
        return (*p).second;
    }
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    map<string, PersonProfile*>::const_iterator p = emailPerson.find(email);
    if(p == emailPerson.end())
    {
        return nullptr;
    }
    else
    {
        return (*p).second;
    }
}
