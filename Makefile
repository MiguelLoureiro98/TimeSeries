GPP = g++
CPPFLAGS = -Wall -g
LIB_NAME = TimeSeries
SRC_DIR = src
TEST_DIR = tests
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_BIN = $(TEST_DIR)/bin
TEST_EXEC = $(TEST_BIN)/tests.out
INC = $(SRC_DIR)/$(LIB_NAME).h

.PHONY:
all: test

$(TEST_EXEC): $(TEST_SOURCES)
	$(GPP) $(CPPFLAGS) $^ -I $(SRC_DIR)/ -lCppUTest -o $@

.PHONY:
test: $(TEST_EXEC)
	@echo "Running tests..."
	$(TEST_EXEC)
	@echo "Tests run."

.PHONY:
clean:
	rm -r $(TEST_EXEC)
	@echo "All files have been successfully deleted."