cmake_minimum_required(VERSION 3.21)
project(MemberManagement)

set(CMAKE_CXX_STANDARD 17)

# 添加包含目錄
include_directories(include)
include_directories($ENV{XLS_WRITER_INCLUDE})
include_directories($ENV{ZLIB_ROOT_INCLUDE})
include_directories($ENV{ZLIB_ROOT})

# 添加源文件
set(SOURCES
    src/main.cpp
    src/MemberManager.cpp
)

# 添加測試文件
set(TEST_SOURCES
    test/test_cases.cpp
)

# 添加庫目錄
link_directories(${CMAKE_SOURCE_DIR}/build) # 添加xlsxwriter.lib所在的目錄

# 添加靜態庫
link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories($ENV{ZLIB_ROOT})

# 尋找 ZLIB
find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

# 添加主程序的可执行文件
add_executable(MemberManagement_main ${SOURCES})

# 編譯主程序
target_link_libraries(MemberManagement_main xlsxwriter ${ZLIB_LIBRARIES})

# 編譯測試程序
add_library(MemberManagement_test ${TEST_SOURCES} ${SOURCES})

# 添加測試可执行文件
add_executable(runTests ${TEST_SOURCES})

# 編譯測試程序
target_link_libraries(runTests MemberManagement_test xlsxwriter ${ZLIB_LIBRARIES})

# 在 Windows 平台下定义宏
if(WIN32)
    target_compile_definitions(MemberManagement_main PRIVATE _WIN32)
    target_compile_definitions(runTests PRIVATE _WIN32)
endif()