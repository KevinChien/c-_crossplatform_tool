ifeq ($(OS),Windows_NT)
    # Windows 下的设置
    CXX = g++
    CXXFLAGS = -std=c++11 -Wall
    INCLUDE_DIR = include
    LIBS = -lxlsxwriter
else
    # Ubuntu 下的设置
    CXX = g++
    CXXFLAGS = -std=c++11 -Wall -Iinclude -I../libxlsxwriter-main/include -I../zlib-develop
    INCLUDE_DIR = include
    LIBS = -L/usr/local/lib -lxlsxwriter -lz
endif

SRC_DIR = src
TEST_DIR = test

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/MemberManager.cpp
OBJS = $(SRCS:.cpp=.o)

TEST_SRCS = $(TEST_DIR)/test_cases.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

TARGET = member_management
TEST_TARGET = test_member_management

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ $^ $(LIBS)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ $^ $(LIBS)

clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TARGET) $(TEST_TARGET)

.PHONY: all clean
