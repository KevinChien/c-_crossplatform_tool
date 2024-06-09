#include "MemberManager.h"
#include <iostream>
#include <algorithm>
#include "xlsxwriter.h"
#include <xlsxio_read.h>

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

void MemberManager::importFromExcel(const std::string& filename) {
    std::cout << "Importing data from Excel file: " << filename << std::endl;

    // 打开 Excel 文件
    xlsxioreader xls_file = xlsxioread_open(filename.c_str());
    if (!xls_file) {
        std::cerr << "Error: Unable to open Excel file: " << filename << std::endl;
        return;
    }

    // 打开 Excel 文件成功
    std::cout << "Successfully opened Excel file." << std::endl;

    // 打开 Excel 文件中的第一个工作表
    xlsxioreadersheet sheet = xlsxioread_sheet_open(xls_file, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
    if (!sheet) {
        std::cerr << "Error: Unable to read worksheet from Excel file." << std::endl;
        xlsxioread_close(xls_file);
        return;
    }

    // 打开工作表成功
    std::cout << "Successfully opened worksheet." << std::endl;

    // 跳过标题行
    xlsxioread_sheet_next_row(sheet);

    // 读取数据并导入到成员列表中
    while (xlsxioread_sheet_next_row(sheet)) {
        const XLSXIOCHAR* name = xlsxioread_sheet_next_cell(sheet);
        const XLSXIOCHAR* age = xlsxioread_sheet_next_cell(sheet);
        const XLSXIOCHAR* job_title = xlsxioread_sheet_next_cell(sheet);

        if (!name || !age || !job_title) {
            // 在 Excel 文件中发现无效的数据格式
            std::cerr << "Error: Invalid data format in Excel file." << std::endl;
            break;
        }

        // 输出每个单元格的内容
        std::cout << "Name: " << name << ", Age: " << age << ", Job Title: " << job_title << std::endl;

        // 尝试将年龄从字符串转换为整数
        try {
            int age_value = std::stoi(reinterpret_cast<const char*>(age));
            // 将成员添加到列表中
            addMember(reinterpret_cast<const char*>(name), age_value, reinterpret_cast<const char*>(job_title));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid age format: " << e.what() << std::endl;
            break;
        }
    }

    // 关闭工作表和 Excel 文件
    xlsxioread_sheet_close(sheet);
    xlsxioread_close(xls_file);

    std::cout << "Data imported successfully." << std::endl;
}




// 導出成員資料
void MemberManager::exportToExcel(const std::string& filename) const {
    lxw_workbook *workbook = workbook_new(filename.c_str());
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
    std::cout << "Data exported to Excel file: " << filename << std::endl;
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