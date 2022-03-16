////main.cpp
//
#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//
const std::string MEMBERS_FILE    = "members.txt";
const std::string TRANSLATOR_FILE = "translator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);


void listCompatiblePairs(const AttributeTranslator& translator)
{
     AttValPair att("hobby","painting");
     std::vector<AttValPair> result =
     translator.FindCompatibleAttValPairs(att);
    if (!result.empty())
    {
         std::cout << "Compatible attributes and values:" << std::endl;
         for (const auto& p: result)
         std::cout << p.attribute << " -> " << p.value << std::endl;
     }
}

void printEmails(const MemberDatabase& mdb)
{
     AttValPair att("job", "salesperson");
     std::vector<std::string> result = mdb.FindMatchingMembers(att);
    if (!result.empty())
    {
         std::cout << "Compatible emails:" << std::endl;
         for (const auto& p: result)
         std::cout << p << std::endl;
     }
}

void findMemberByEmail(const MemberDatabase& md, std::string member_email)
{
    const PersonProfile* ptr = md.GetMemberByEmail(member_email);
    if (ptr != nullptr)
    std::cout << "Found info for member: " << ptr->GetName() << std::endl;
    else
    std::cout << "No member has address " << member_email << std::endl;
}

void tester(AttValPair* pair)
{
    if (pair == nullptr)
    {
        std::cout << "No value found." << std::endl;
    }
    else
    {
        std::cout << "The value is: " << pair->value << std::endl;
    }
}

int main() {
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
        ;

    std::cout << "Happy dating!" << std::endl;
    
    
    
    //code ^^^^^^

//    RadixTree<int> rT;
//    rT.insert("shop", 5);
//    rT.insert("good", 2);
//    rT.insert("mad", 9);
//    rT.insert("cool", 10);
//    rT.insert("shell", 111);
//    rT.insert("sheep", 123);
//    rT.insert("she", 123333);
//    rT.insert("car", 2);
//    rT.insert("car", 1);
//    rT.insert("camp", 3);
//    rT.insert("cramp", 99);
//    rT.insert("carry", 960);
//
//    rT.insert("card", 3);
//    rT.insert("camp", 3);
//
//    rT.insert("car",90);
//    rT.insert("car",67);
//    rT.insert("cat",999);
//    rT.insert("car",9988);
//
//
//    rT.insert("she", 1);
//    rT.insert("sheep", 2);
//
//    std::cout << *(rT.search("car")) << std::endl;
//    std::cout << *(rT.search("card")) << std::endl;
//    std::cout << *(rT.search("cat")) << std::endl;
//    std::cout << *(rT.search("camp")) << std::endl;
//    std::cout << *(rT.search("cramp")) << std::endl;
//    std::cout << *(rT.search("carry")) << std::endl;
//    std::cout << *(rT.search("shop")) << std::endl;

//    AttributeTranslator tra = AttributeTranslator();
//    tra.Load(TRANSLATOR_FILE);
//    std::cout << "----------" << std::endl;
//    listCompatiblePairs(tra);


//    MemberDatabase mdb;
//    mdb.LoadDatabase(MEMBERS_FILE);
//    printEmails(mdb);
//    findMemberByEmail(mdb, "TitusQuin0@me.com");
//    findMemberByEmail(mdb, "RPa6425@cox.net");
//    findMemberByEmail(mdb, "ScHob4657@juno.com");
//    findMemberByEmail(mdb, "AzariahSala558@zoho.com");
//
//
    
    
    
//
//    PersonProfile person = PersonProfile("Jacky", "ykcaj@g.ucla.edu");
//    cout << person.GetName() << endl;
//    cout << person.GetEmail() << endl;
//    AttValPair a = AttValPair("job", "doctor");
//    AttValPair b = AttValPair("hobby", "hobby");
//    AttValPair c = AttValPair("hobby", "gaming");
//    AttValPair d = AttValPair("hobby", "poker");
//    AttValPair e = AttValPair("hobby", "improv");
//    AttValPair f = AttValPair("trait", "reactive");
//    AttValPair g = AttValPair("trait", "complacent");
//    AttValPair h = AttValPair("trait", "bewildered");
//    AttValPair i = AttValPair("hobby", "dancing");
//    AttValPair j = AttValPair("hobby", "dancing");
//
//    person.AddAttValPair(a);
//    person.AddAttValPair(b);
//    person.AddAttValPair(c);
//    person.AddAttValPair(d);
//    person.AddAttValPair(e);
//    person.AddAttValPair(f);
//    person.AddAttValPair(g);
//    person.AddAttValPair(h);
//    person.AddAttValPair(i);
//    person.AddAttValPair(j);
//    AttValPair print;
//
//    for(int i = 0; i < person.GetNumAttValPairs(); i++)
//    {
//        person.GetAttVal(i, print);
//        cout << print.attribute << ", " << print.value << endl;
//    }
}


bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    
    //   Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

    //   Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
    
        }
    }
    std::cout << std::endl;
    return true;
}
