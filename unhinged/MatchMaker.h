//
//  MatchMaker.hpp
//  unhinged
//
//  Created by Jacky Dai on 3/4/22.
//

#ifndef MatchMaker_hpp
#define MatchMaker_hpp

#include <stdio.h>
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include <unordered_set>


class MatchMaker
{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);

    ~MatchMaker(){}

    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;

private:
    const MemberDatabase* m_mdb;
    const AttributeTranslator* m_at;
    static bool greater(const EmailCount& lhs, const EmailCount& rhs);
    AttValPair createAttPair(const std::string& line) const;
    std::string createString(AttValPair line) const;
};

#endif /* MatchMaker_hpp */

//
//#ifndef MATCH
//#define MATCH
//#include <vector>
//#include "MemberDatabase.h"
//#include "AttributeTranslator.h"
//#include "PersonProfile.h"
//#include "provided.h"
//#include <unordered_set>
//#include <string>
//
//class MatchMaker
//{
//public:
//MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
//~MatchMaker() {}
/////* You may define a destructor for MemberDatabase if you need one to free any dynamically
//// allocated memory used by your object.*/
//std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
//private:
//const MemberDatabase* mDatabase;
//const AttributeTranslator* mAttTranslator;
////AttValPair stringtoAttValPair(std::string line);
//AttValPair stringtoAttValPair(std::string line) const ;
//};
//#endif // !MATCH
