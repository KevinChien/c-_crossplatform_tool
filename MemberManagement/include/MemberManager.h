#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include <string>
#include <vector>

struct Member {
    std::string name;
    int age;
    std::string jobTitle;
};

class MemberManager {
public:
    void addMember(const std::string& name, int age, const std::string& jobTitle);
    void deleteMember(const std::string& name);
    std::vector<Member> searchMemberByName(const std::string& name) const;
    std::vector<Member> searchMemberByAge(int age) const;
    std::vector<Member> searchMemberByJobTitle(const std::string& jobTitle) const;
    void displayAllMembers() const;
    void importFromExcel(const std::string& filename);
    void exportToExcel(const std::string& filename) const;

private:
    std::vector<Member> members;
};

#endif // MEMBERMANAGER_H
