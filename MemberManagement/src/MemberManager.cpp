#include "MemberManager.h"
#include <iostream>
#include <algorithm>
#include "xlsxwriter.h"
#include <iomanip> // 添加这个头文件

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// 添加成員
void MemberManager::addMember(const std::string& name, int age, const std::string& jobTitle) {
    members.push_back({name, age, jobTitle});
}

// 刪除成員
void MemberManager::deleteMember(const std::string& name) {
    members.erase(std::remove_if(members.begin(), members.end(),
                                 [&name](const Member& member) { return member.name == name; }),
                  members.end());
}

// 查询成员信息
std::vector<Member> MemberManager::queryMember(const std::string& name) const {
    std::vector<Member> results;
    for (const auto& member : members) {
        if (member.name == name) {
            results.push_back(member);
        }
    }

    // 计算每个字段的最大宽度
    size_t maxNameWidth = 4; // 默认最小宽度为4，至少能容纳 "Name" 这个单词
    size_t maxAgeWidth = 3;  // 默认最小宽度为3，至少能容纳 "Age" 这个单词
    size_t maxTitleWidth = 9; // 默认最小宽度为9，至少能容纳 "Job Title" 这个单词

    for (const auto& member : results) {
        maxNameWidth = std::max(maxNameWidth, member.name.size());
        maxAgeWidth = std::max(maxAgeWidth, std::to_string(member.age).size());
        maxTitleWidth = std::max(maxTitleWidth, member.jobTitle.size());
    }

    // 打印查询结果的表头
    std::cout << "Query results for member: " << name << std::endl;
    std::cout << std::left << std::setw(maxNameWidth + 2) << "Name" << " | "
              << std::setw(maxAgeWidth + 2) << "Age" << " | "
              << std::setw(maxTitleWidth + 2) << "Job Title" << std::endl;
    std::cout << std::string(maxNameWidth + maxAgeWidth + maxTitleWidth + 8, '-') << std::endl;

    // 打印查询结果
    for (const auto& member : results) {
        std::cout << std::left << std::setw(maxNameWidth + 2) << member.name << " | "
                  << std::setw(maxAgeWidth + 2) << member.age << " | "
                  << std::setw(maxTitleWidth + 2) << member.jobTitle << std::endl;
    }

    return results;
}

// 列出所有成員
void MemberManager::listAllMembers() const {
    if (members.empty()) {
        std::cout << "No members found." << std::endl;
        return;
    }

    // 计算每个字段的最大宽度
    size_t maxNameWidth = 4; // 默认最小宽度为4，至少能容纳 "Name" 这个单词
    size_t maxAgeWidth = 3;  // 默认最小宽度为3，至少能容纳 "Age" 这个单词
    size_t maxTitleWidth = 9; // 默认最小宽度为9，至少能容纳 "Job Title" 这个单词

    for (const auto& member : members) {
        maxNameWidth = std::max(maxNameWidth, member.name.size());
        maxAgeWidth = std::max(maxAgeWidth, std::to_string(member.age).size());
        maxTitleWidth = std::max(maxTitleWidth, member.jobTitle.size());
    }

    // 打印表头
    std::cout << "All members:" << std::endl;
    std::cout << std::left << std::setw(maxNameWidth + 2) << "Name" << " | "
              << std::setw(maxAgeWidth + 2) << "Age" << " | "
              << std::setw(maxTitleWidth + 2) << "Job Title" << std::endl;

    // 打印分隔线
    std::cout << std::setfill('-') << std::setw(maxNameWidth + maxAgeWidth + maxTitleWidth + 8) << "-" << std::endl;
    std::cout << std::setfill(' ');

    // 打印每个成员的信息
    for (const auto& member : members) {
        std::cout << std::left << std::setw(maxNameWidth + 2) << member.name << " | "
                  << std::setw(maxAgeWidth + 2) << member.age << " | "
                  << std::setw(maxTitleWidth + 2) << member.jobTitle << std::endl;
    }
}

void MemberManager::importFromJSON(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open JSON file: " << filename << std::endl;
        return;
    }

    json data;
    try {
        file >> data;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unable to parse JSON data: " << e.what() << std::endl;
        return;
    }

    for (const auto& member : data["members"]) {
        std::string name = member["name"];
        int age = member["age"];
        std::string job_title = member["job_title"];

        // Output the data
        std::cout << "Name: " << name << ", Age: " << age << ", Job Title: " << job_title << std::endl;

        // Add the member to the list
        addMember(name, age, job_title);
    }

    std::cout << "Data imported successfully from JSON file: " << filename << std::endl;
}

void MemberManager::exportToJSON(const std::string& filename) const {
    json data;

    for (const auto& member : members) {
        json member_data;
        member_data["name"] = member.name;
        member_data["age"] = member.age;
        member_data["job_title"] = member.jobTitle;
        data["members"].push_back(member_data);
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to create JSON file: " << filename << std::endl;
        return;
    }

    try {
        file << std::setw(4) << data << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: Unable to write JSON data: " << e.what() << std::endl;
        return;
    }

    std::cout << "Data exported to JSON file: " << filename << std::endl;
}

// 修改成员的年龄
void MemberManager::modifyMemberAge(const std::string& name, int newAge) {
    for (auto& member : members) {
        if (member.name == name) {
            member.age = newAge;
            return;
        }
    }
    std::cout << "Member not found." << std::endl;
}

// 修改成员的职位
void MemberManager::modifyMemberJobTitle(const std::string& name, const std::string& newJobTitle) {
    for (auto& member : members) {
        if (member.name == name) {
            member.jobTitle = newJobTitle;
            return;
        }
    }
    std::cout << "Member not found." << std::endl;
}

// 退出程序
void MemberManager::exitProgram() {
    std::cout << "Exiting MemberManagement program. Goodbye!" << std::endl;
    exit(0);
}