//
//  MemberDatabase.hpp
//  unhinged
//
//  Created by Jacky Dai on 3/4/22.
//

#ifndef MemberDatabase_hpp
#define MemberDatabase_hpp

#include "provided.h"
#include "PersonProfile.h"
#include <vector>
#include <map>


class MemberDatabase
{
public:
    MemberDatabase(){}

    ~MemberDatabase();

    bool LoadDatabase(std::string filename);

    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;

    const PersonProfile* GetMemberByEmail(std::string email) const;
private:

    AttValPair createAttPair(std::string input); //function that turns a string version of attVal pair to the struct attvalpair
    RadixTree<std::vector<std::string>> pairEmailsRT; //RadixTree class that maps attribute-value pairs to email addresses


    RadixTree<PersonProfile*> emailPersonRT;// RadixTree class that maps email addresses to member profiles

};


#endif /* MemberDatabase_hpp */


