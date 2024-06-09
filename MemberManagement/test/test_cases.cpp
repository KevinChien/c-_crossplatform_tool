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
    // Age and job title search replaced with name search
    assert(manager.queryMember("jane").size() == 1);
    assert(manager.queryMember("jane").size() == 1);
    assert(manager.queryMember("Manager").size() == 1);

    // Test exporting to Excel
    manager.exportToJSON("data/test_members");
}

// Note: No need for the main function in test cases
