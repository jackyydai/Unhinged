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

class MemberDatabase
{
public:
    MemberDatabase();
    
    ~MemberDatabase();
    
    bool LoadDatabase(std::string filename);
    
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    
    const PersonProfile* GetMemberByEmail(std::string email) const;
    
};


#endif /* MemberDatabase_hpp */
