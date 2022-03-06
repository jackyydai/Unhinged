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
    
    ~MemberDatabase(){}
    
    bool LoadDatabase(std::string filename);
    
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    
    const PersonProfile* GetMemberByEmail(std::string email) const;
private:
    
    AttValPair createAttPair(std::string input);
    std::map<std::string, std::vector<std::string>> pairEmails;
    std::map<std::string, PersonProfile*> emailPerson;
    
};


#endif /* MemberDatabase_hpp */
