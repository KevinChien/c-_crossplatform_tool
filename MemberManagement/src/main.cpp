#include <iostream>
#include "MemberManager.h"

int main() {
    MemberManager manager;

    // Sample interaction with the manager
    manager.addMember("kevin", 42, "Engineer");
    manager.addMember("alice", 30, "Designer");

    std::cout << "All members:" << std::endl;
    manager.displayAllMembers();

    std::cout << "Searching for members named 'kevin':" << std::endl;
    auto results = manager.searchMemberByName("kevin");
    for (const auto& member : results) {
        std::cout << member.name << ", " << member.age << ", " << member.jobTitle << std::endl;
    }

    manager.exportToExcel("data/members.xlsx");
    return 0;
}
