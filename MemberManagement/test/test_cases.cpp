#include "MemberManager.h"
#include <cassert>

void runTests() {
    MemberManager manager;

    // Test adding members
    manager.addMember("john", 25, "Developer");
    manager.addMember("jane", 28, "Manager");
    assert(manager.searchMemberByName("john").size() == 1);
    assert(manager.searchMemberByName("jane").size() == 1);

    // Test deleting members
    manager.deleteMember("john");
    assert(manager.searchMemberByName("john").empty());

    // Test searching by age and job title
    assert(manager.searchMemberByAge(28).size() == 1);
    assert(manager.searchMemberByJobTitle("Manager").size() == 1);

    // Test displaying all members
    manager.displayAllMembers();

    // Test export to Excel
    manager.exportToExcel("data/test_members.xlsx");
}

// 注意：不再需要 main 函数
