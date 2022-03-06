//
//  AttributeTranslator.cpp
//  unhinged
//
//  Created by Jacky Dai on 3/4/22.
//
#include <vector>
#include "AttributeTranslator.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

AttributeTranslator::AttributeTranslator()
{
    
}

bool AttributeTranslator::Load(std::string filename)
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
        string sAtt = "";
        string sVal = "";
        string cAtt = "";
        string cVal = "";
        int count = 0;
        for(; line[count] != ',' ; count ++)
        {
            sAtt += line[count];
        }
        count++;
        for(; line[count] != ',' ; count ++)
        {
            sVal += line[count];
        }
        count++;
        for(; line[count] != ',' ; count ++)
        {
            cAtt += line[count];
        }
        count++;
        for(; count < line.size() ; count ++)
        {
            cVal += line[count];
        }

        string sourceKey = sAtt + "," + sVal;

        map<string, vector<AttValPair>>::iterator p = attMap.find(sourceKey);
        //string compatibleKey = cAtt + "," + cVal;
        if(p == attMap.end())
        {
            vector<AttValPair> toBeAdded;

            toBeAdded.push_back(AttValPair(cAtt, cVal));
            attMap.insert(make_pair(sourceKey, toBeAdded));
        }
        else
        {
            bool end = false;
            for(int i = 0; i < (*p).second.size(); i++)
            {
                if(AttValPair(cAtt, cVal) == ((*p).second)[i])
                {
                    end = true;
                    break;
                }
            }
            if(!end)
            {

                (*p).second.push_back(AttValPair(cAtt, cVal));
            }
//            cout << "source :  " <<(*p).first << endl;
//            for(int i = 0; i < (*p).second.size(); i++)
//            {
//
//                cout << (*p).second[i].attribute << "," << (*p).second[i].value << endl;
//
//            }
//            cout << endl;
//            cout << endl;
//            cout << endl;
        }


    }
    infile.close();
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
    string search = source.attribute + "," + source.value;
    map<string, vector<AttValPair>>::const_iterator p = attMap.find(search);
    if(p == attMap.end())
    {
        vector<AttValPair> nothing;
        return nothing;
    }
    else
    {
        return (*p).second;
    }
}

