#ifndef MEMBER_MANAGER_H
#define MEMBER_MANAGER_H

#include <string>
#include <vector>

struct Member {
    std::string name;
    int age;
    std::string jobTitle;
};

class MemberManager {
public:
    // 新功能：添加成員
    void addMember(const std::string& name, int age, const std::string& jobTitle);

    // 新功能：刪除成員
    void deleteMember(const std::string& name);

    // 查询成员信息
    std::vector<Member> queryMember(const std::string& name) const;

    // 新功能：列出所有成員
    void listAllMembers() const;

        // 新功能：導入成員資料
    void importFromExcel(const std::string& filename);

    // 新功能：導出成員資料
    void exportToExcel(const std::string& filename) const;

    // 修改成员的年龄
    void modifyMemberAge(const std::string& name, int newAge);

    // 修改成员的职位
    void modifyMemberJobTitle(const std::string& name, const std::string& newJobTitle);

    // 退出程序
    void exitProgram();

private:
    std::vector<Member> members;
};

#endif
