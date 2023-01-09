# The executable to write
TARGET ?= example_provider.so

# Some helper constants
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
Q := @
CXX := clang++
ECHO := $(Q)echo
ECXX := $(ECHO) "    CXX "
ELEXER := $(ECHO) "  LEXER "
EPARSER := $(ECHO) " PARSER"
EBIN := $(ECHO) "    BIN "

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CXXFLAGS += -std=c++20
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -g -std=c++20 -fPIC -Wall
LDFLAGS ?= -rdynamic -shared -ldl -lbinn -pthread

MKDIR_P ?= mkdir -p

$(TARGET): $(OBJS)
	$(EBIN) $@
	$(Q)$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(Q)$(MKDIR_P) $(dir $@)
	$(ECXX) $<
	$(Q)$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(Q)$(RM) -r $(BUILD_DIR) $(TARGET) vgcore.*
