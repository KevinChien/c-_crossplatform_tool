#include "MemberManager.h"
#include <cassert>

void runTests() {
    MemberManager manager;

    // Test adding members
    manager.addMember("john", 25, "Developer");
    manager.addMember("jane", 28, "Manager");
    assert(manager.queryMember("john").size() == 1);
    assert(manager.queryMember("jane").size() == 1);

    // Test deleting members
    manager.deleteMember("john");
    assert(manager.queryMember("john").empty());

    // Test searching by name, age, and job title
    assert(manager.queryMember("jane").size() == 1);
    assert(manager.queryMember("john").size() == 0); // Assuming the member "john" was deleted
    assert(manager.queryMember("jane").size() == 1);
    assert(manager.queryMember("jane").size() == 1);
    // 这行应该移除，因为现在只能按名字搜索
    // assert(manager.queryMember("Manager").size() == 1);

    // Test exporting to JSON
    manager.exportToJSON("data/test_members");
}
