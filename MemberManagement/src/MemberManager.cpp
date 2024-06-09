#include "MemberManager.h"
#include <iostream>
#include <algorithm>
#include "xlsxwriter.h"

#ifndef _WIN32
#include <xlsxio_read.h>
#else
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#endif

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
    return results;
}

// 列出所有成員
void MemberManager::listAllMembers() const {
    if (members.empty()) {
        std::cout << "No members found." << std::endl;
        return;
    }

    std::cout << "All members:" << std::endl;
    std::cout << "Name  | Age | Job Title" << std::endl;
    std::cout << "-----------------------" << std::endl;

    for (const auto& member : members) {
        std::cout << member.name << " | " << member.age << " | " << member.jobTitle << std::endl;
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