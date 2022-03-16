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
    static bool greater(const EmailCount& lhs, const EmailCount& rhs); // comparison function to order the vector using sort
    AttValPair createAttPair(const std::string& line) const; // function to turn string to AttValPair
    std::string createString(AttValPair line) const; // function to turn AttvalPair into string
};

#endif /* MatchMaker_hpp */


