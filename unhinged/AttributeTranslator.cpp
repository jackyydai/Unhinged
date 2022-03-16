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
    if(!infile) //if file was not successfully loaded return false
    {
        return false;
    }
    while(getline(infile, line, '\n')) //each line of the translator txt, this loop is called
    {
        string sAtt = "";
        string sVal = "";
        string cAtt = "";
        string cVal = "";
        int count = 0;
        for(; line[count] != ',' ; count ++)
        {
            sAtt += line[count];//sets source attribute from each line. (eveything before the first ",")
        }
        count++;
        for(; line[count] != ',' ; count ++)
        {
            sVal += line[count];//sets source value from each line. (eveything from the first ",", to the second ",")
        }
        count++;
        for(; line[count] != ',' ; count ++)
        {
            cAtt += line[count];//sets source attribute from each line. (eveything from the second ",", to the third ",")
        }
        count++;
        for(; count < line.size() ; count ++)
        {
            cVal += line[count];//sets source attribute from each line. (eveything from the third ",", to the end of the line)
        }

        string sourceKey = sAtt + "," + sVal;//creates a string of the source attribute and the value

        //map<string, vector<AttValPair>>::iterator p = attMap.find(sourceKey);

        std::vector<AttValPair>* q = attTransRT.search(sourceKey); //finds if the there is a vector of compatible attvalpairs in the tree that map to the source key yet
        if(q == nullptr) // if not create new vector and add this compatible attval to it and insert it to thr Radix tree
        {
            vector<AttValPair> toBeAdded;
            toBeAdded.push_back(AttValPair(cAtt, cVal));
            attTransRT.insert(sourceKey, toBeAdded);
        }
        else
        {
            bool end = false;
            for(int i = 0; i < (*q).size(); i++) // if their is a vector check the vector if it contains this compatiable attval yet. If not add it to the vector
            {
                if(AttValPair(cAtt, cVal) == (*q)[i])
                {
                    end = true;
                    break;
                }
            }
            if(!end)
            {

                (*q).push_back(AttValPair(cAtt, cVal));
            }
        }
    }
    infile.close();
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
    string search = source.attribute + "," + source.value;
    //map<string, vector<AttValPair>>::const_iterator p = attMap.find(search);
    std::vector<AttValPair>* q = attTransRT.search(search); //seatches through radix tree to see if the vector of compadible att that is maped to the sourceAttVal vals already exist in the tree

    if(q == nullptr) //if not return empty vector
    {
        vector<AttValPair> nothing;
        return nothing;
    }
    else // if so return that vector
    {
        return (*q);
    }
}




