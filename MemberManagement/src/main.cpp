#include <iostream>
#include <string>
#include <vector> // 添加必要的頭文件
#include <sstream> // 添加必要的頭文件
#include <iterator> // 添加必要的頭文件
#include "MemberManager.h"

// 函數原型
void interactiveMode(MemberManager& manager);
void processCommand(const std::string& command, MemberManager& manager);
void printHelp();

// 添加一個新成員
void addMember(MemberManager& manager, const std::string& name, int age, const std::string& jobTitle) {
    manager.addMember(name, age, jobTitle); // 使用 MemberManager 的 addMember 函數
}

// 移除一個成員
void removeMember(MemberManager& manager, const std::string& name) {
    manager.deleteMember(name);
}

// 查詢成員信息
void queryMember(MemberManager& manager, const std::string& name) {
    auto results = manager.queryMember(name);
    for (const auto& member : results) {
        std::cout << member.name << ", " << member.age << ", " << member.jobTitle << std::endl;
    }
}

// 修改成員信息
void modifyMember(MemberManager& manager, const std::string& name, const std::string& field, const std::string& newValue) {
    if (field == "age") {
        manager.modifyMemberAge(name, std::stoi(newValue));
    } else if (field == "jobTitle") {
        manager.modifyMemberJobTitle(name, newValue);
    } else {
        std::cout << "Invalid field specified for modification." << std::endl;
    }
}

// 列出所有成員
void listAllMembers(MemberManager& manager) {
    manager.listAllMembers(); // 使用 MemberManager 的 listAllMembers 函數
}

int main(int argc, char* argv[]) {
    MemberManager manager; // 創建 MemberManager 對象

    // 檢查命令行參數
    if (argc == 1) {
        // 啟動互動式介面
        interactiveMode(manager);
    } else {
        // 解析命令行參數並執行相應的命令
        std::string command = argv[1];
        processCommand(command, manager);
    }

    return 0;
}

// 互動式介面
void interactiveMode(MemberManager& manager) {
    std::cout << "Welcome to MemberManagement v1.0" << std::endl;
    std::cout << "> ";

    std::string command;
    while (std::getline(std::cin, command)) {
        processCommand(command, manager);
        std::cout << "> ";
    }
}

// 處理命令
void processCommand(const std::string& command, MemberManager& manager) {
    // 根據命令執行相應的操作
    if (command == "help") {
        printHelp();
    } else if (command.substr(0, 3) == "add") {
        // 解析添加成員命令
        std::istringstream iss(command);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, 
                                        std::istream_iterator<std::string>{}};
        if (tokens.size() == 4) {
            addMember(manager, tokens[1], std::stoi(tokens[2]), tokens[3]);
        } else {
            std::cout << "Invalid command. Usage: add <name> <age> <jobTitle>" << std::endl;
        }
    } else if (command.substr(0, 6) == "remove") {
        // 解析移除成員命令
        std::istringstream iss(command);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, 
                                        std::istream_iterator<std::string>{}};
        if (tokens.size() == 2) {
            removeMember(manager, tokens[1]);
        } else {
            std::cout << "Invalid command. Usage: remove <name>" << std::endl;
        }
    } else if (command.substr(0, 5) == "query") {
        // 解析查詢成員
        std::string name = command.substr(6);
        auto result = manager.queryMember(name);
        if (result.empty()) {
            std::cout << "Member not found." << std::endl;
        } else {
            std::cout << "Query result:" << std::endl;
            std::cout << "Name  | Age | Job Title" << std::endl;
            std::cout << "-----------------------" << std::endl;
            for (const auto& member : result) {
                std::cout << member.name << " | " << member.age << " | " << member.jobTitle << std::endl;
            }
        }
    } else if (command.substr(0, 6) == "modify") {
        // 解析修改成員命令
        std::istringstream iss(command);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>{}};
        if (tokens.size() == 4) {
            modifyMember(manager, tokens[1], tokens[2], tokens[3]);
        } else {
            std::cout << "Invalid command. Usage: modify <name> <age/jobTitle> <newValue>" << std::endl;
        }
    } else if (command == "list") {
        // 列出所有成員
        listAllMembers(manager);
    } else if (command.substr(0, 6) == "import") {
        // 解析導入成員數據命令
        std::istringstream iss(command);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>{}};
        if (tokens.size() == 2) {
            manager.importFromJSON(tokens[1]);
        } else {
            std::cout << "Invalid command. Usage: import <filename>" << std::endl;
        }
    } else if (command.substr(0, 6) == "export") {
        // 解析導出成員數據命令
        std::istringstream iss(command);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>{}};
        if (tokens.size() == 2) {
            manager.exportToJSON(tokens[1]);
        } else {
            std::cout << "Invalid command. Usage: export <filename>" << std::endl;
        }
    } else if (command == "exit") {
        manager.exitProgram();
    } else {
        std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
    }
}

// 输出帮助信息
void printHelp() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "add <name> <age> <jobTitle> : Add a new member" << std::endl;
    std::cout << "remove <name> : Remove a member" << std::endl;
    std::cout << "query <name> : Query member information" << std::endl;
    std::cout << "modify <name> <age/jobTitle> <newValue> : Modify member information" << std::endl;
    std::cout << "list : List all members" << std::endl;
    std::cout << "import <filename> : Import member data from Excel file" << std::endl;
    std::cout << "export <filename> : Export member data to Excel file" << std::endl;
    std::cout << "help : Show available commands" << std::endl;
}
