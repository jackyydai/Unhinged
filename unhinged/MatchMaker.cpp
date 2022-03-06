//
//  MatchMaker.cpp
//  unhinged
//
//  Created by Jacky Dai on 3/4/22.
//

#include "MatchMaker.h"


MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
:m_mdb(&mdb),m_at(&at)
{}


//std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
//{
//    
//}

