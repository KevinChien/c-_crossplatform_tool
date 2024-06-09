#include "MemberManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "xlsxwriter.h"

void MemberManager::addMember(const std::string& name, int age, const std::string& jobTitle) {
    members.push_back({name, age, jobTitle});
}

void MemberManager::deleteMember(const std::string& name) {
    members.erase(std::remove_if(members.begin(), members.end(),
                                 [&name](const Member& member) { return member.name == name; }),
                  members.end());
}

std::vector<Member> MemberManager::searchMemberByName(const std::string& name) const {
    std::vector<Member> results;
    for (const auto& member : members) {
        if (member.name == name) {
            results.push_back(member);
        }
    }
    return results;
}

std::vector<Member> MemberManager::searchMemberByAge(int age) const {
    std::vector<Member> results;
    for (const auto& member : members) {
        if (member.age == age) {
            results.push_back(member);
        }
    }
    return results;
}

std::vector<Member> MemberManager::searchMemberByJobTitle(const std::string& jobTitle) const {
    std::vector<Member> results;
    for (const auto& member : members) {
        if (member.jobTitle == jobTitle) {
            results.push_back(member);
        }
    }
    return results;
}

void MemberManager::displayAllMembers() const {
    if (members.empty()) {
        std::cout << "No members found." << std::endl;
        return;
    }

    size_t nameWidth = 4, ageWidth = 3, jobTitleWidth = 9;
    for (const auto& member : members) {
        if (member.name.size() > nameWidth) nameWidth = member.name.size();
        if (member.jobTitle.size() > jobTitleWidth) jobTitleWidth = member.jobTitle.size();
    }

    std::cout << std::left << std::setw(nameWidth) << "Name" << " | "
              << std::setw(ageWidth) << "Age" << " | "
              << std::setw(jobTitleWidth) << "Job Title" << std::endl;
    std::cout << std::string(nameWidth + ageWidth + jobTitleWidth + 6, '-') << std::endl;

    for (const auto& member : members) {
        std::cout << std::left << std::setw(nameWidth) << member.name << " | "
                  << std::setw(ageWidth) << member.age << " | "
                  << std::setw(jobTitleWidth) << member.jobTitle << std::endl;
    }
}

void MemberManager::importFromExcel(const std::string& filename) {
    // Implementation for importing from Excel (omitted for brevity)
}

void MemberManager::exportToExcel(const std::string& filename) const {
    lxw_workbook  *workbook  = workbook_new(filename.c_str());
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    worksheet_write_string(worksheet, 0, 0, "Name", NULL);
    worksheet_write_string(worksheet, 0, 1, "Age", NULL);
    worksheet_write_string(worksheet, 0, 2, "Job Title", NULL);

    int row = 1;
    for (const auto& member : members) {
        worksheet_write_string(worksheet, row, 0, member.name.c_str(), NULL);
        worksheet_write_number(worksheet, row, 1, member.age, NULL);
        worksheet_write_string(worksheet, row, 2, member.jobTitle.c_str(), NULL);
        row++;
    }

    workbook_close(workbook);
}
