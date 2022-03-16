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

MemberDatabase::~MemberDatabase()
{}

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
    while(getline(infile, line, '\n'))//this loop goes through every chunk of member's information at a time
    {
        string name;
        string email;
        string strOfAtt;
        
        name = line; // sets the first line to string varible name
        //cout << name << endl;
        
        getline(infile, line, '\n');
        email = line;//sets second line to the string varible email
        //cout << email <<  endl;

        getline(infile, line, '\n');
        strOfAtt = line;
        //cout << strOfAtt << endl ;
        int numOfAtt = stoi(strOfAtt); //cast to a int using stoi
        //cout << numOfAtt << endl;
        
        
        
//        if(emailPerson.find(email) != emailPerson.end())
        if(emailPersonRT.search(email) != nullptr) // If two members in the data file have the same email address, this method returns false.
        {
            return false;
        }
        
        PersonProfile* person = new PersonProfile(name,email); //create new person
        for(int i = 0; i < numOfAtt; i++) // loops through the number of attributeval in each each memeber discription
        {
            string sPair;
            getline(infile, line, '\n');
            sPair = line;
            AttValPair aPair = createAttPair(sPair);
            
            person->AddAttValPair(aPair);// add each attvalpair the person just created
            vector<string>* p = pairEmailsRT.search(sPair);//creates a vetor pointer to see if their exist vector of emails that map to a sourse pair
            if(p == nullptr)
            {
                vector<string> toBeAdded; //create a vector of string to hold emails
                toBeAdded.push_back(email);
                pairEmailsRT.insert(sPair, toBeAdded); //add to the radix tree
            }
            else
            {
                bool end = false;
                for(int i = 0; i < (*p).size(); i++) // if the vector of emails already exist check if this email is in the vector, is not add it in
                {
                    if(email == (*p)[i])
                    {
                        end = true;
                        break;
                    }
                }
                if(!end)
                {
//                    if(find((*p).second.begin(),(*p).second.end(),email) == (*p).second.end())
//                    {
                        (*p).push_back(email);
                    //}
                }
            }
        }
        emailPersonRT.insert(email, person); // insert the email map to person in the Radix tree
        //emailPerson.insert(make_pair(email, person));
        getline(infile, line, '\n'); // skips the extra new line
    }
    infile.close();
    return true;
    
    
    
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    string search = input.attribute + "," + input.value;
    
    vector<string>* p = pairEmailsRT.search(search);// searches the attribute value pair email tree
    
    if(p == nullptr)//if null return empty string, return vector itself otherwise
    {
        vector<string> nothing;
        return nothing;
    }
    else
    {
        return (*p);
    }
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    PersonProfile** p = emailPersonRT.search(email); //searches the email person radix tree
    if(p == nullptr)//if does not exist return null pointer, return person otherwise
    {
        return nullptr;
    }
    else
    {
        return (*p);
    }
}
