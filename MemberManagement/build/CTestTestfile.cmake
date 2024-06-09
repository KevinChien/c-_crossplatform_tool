# CMake generated Testfile for 
# Source directory: E:/c_workspace/MemberManagement
# Build directory: E:/c_workspace/MemberManagement/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[MemberManagementTest]=] "E:/c_workspace/MemberManagement/build/Debug/MemberManagement_test.exe")
  set_tests_properties([=[MemberManagementTest]=] PROPERTIES  _BACKTRACE_TRIPLES "E:/c_workspace/MemberManagement/CMakeLists.txt;46;add_test;E:/c_workspace/MemberManagement/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[MemberManagementTest]=] "E:/c_workspace/MemberManagement/build/Release/MemberManagement_test.exe")
  set_tests_properties([=[MemberManagementTest]=] PROPERTIES  _BACKTRACE_TRIPLES "E:/c_workspace/MemberManagement/CMakeLists.txt;46;add_test;E:/c_workspace/MemberManagement/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[MemberManagementTest]=] "E:/c_workspace/MemberManagement/build/MinSizeRel/MemberManagement_test.exe")
  set_tests_properties([=[MemberManagementTest]=] PROPERTIES  _BACKTRACE_TRIPLES "E:/c_workspace/MemberManagement/CMakeLists.txt;46;add_test;E:/c_workspace/MemberManagement/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[MemberManagementTest]=] "E:/c_workspace/MemberManagement/build/RelWithDebInfo/MemberManagement_test.exe")
  set_tests_properties([=[MemberManagementTest]=] PROPERTIES  _BACKTRACE_TRIPLES "E:/c_workspace/MemberManagement/CMakeLists.txt;46;add_test;E:/c_workspace/MemberManagement/CMakeLists.txt;0;")
else()
  add_test([=[MemberManagementTest]=] NOT_AVAILABLE)
endif()
