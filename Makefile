CXX = g++
CXXFLAGS = -std=c++17 -Isrc

SRCS = main.cpp src/Quiz.cpp src/utils.cpp src/ConsoleUI.cpp src/ScoreBoard.cpp src/QuestionLoader.cpp src/LanguageLoader.cpp
TARGET = output/main

TEST_SRCS = tests/tests.cpp src/utils.cpp src/ConsoleUI.cpp src/ScoreBoard.cpp src/QuestionLoader.cpp src/LanguageLoader.cpp
TEST_TARGET = output/tests

# Определение операционной системы
ifeq ($(OS),Windows_NT)
    MKDIR = @powershell -Command "if (!(Test-Path output)) { New-Item -ItemType Directory -Path output | Out-Null }"
    RM = @powershell -Command "if (Test-Path $(TARGET)) { Remove-Item $(TARGET) }; if (Test-Path $(TEST_TARGET)) { Remove-Item $(TEST_TARGET) }"
    RUN_CMD = @powershell -Command "chcp 65001 > $$null; & ./output/main.exe"
    TEST_CMD = @powershell -Command "& ./output/tests"
    EXE_EXT = .exe
else
    MKDIR = mkdir -p output
    RM = rm -f $(TARGET) $(TEST_TARGET)
    RUN_CMD = ./$(TARGET)
    TEST_CMD = ./$(TEST_TARGET)
    EXE_EXT =
endif

REAL_TARGET = $(TARGET)$(EXE_EXT)
REAL_TEST_TARGET = $(TEST_TARGET)$(EXE_EXT)

all: $(REAL_TARGET)

$(REAL_TARGET): $(SRCS)
	$(MKDIR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(REAL_TARGET)

run: $(REAL_TARGET)
	$(RUN_CMD)

test: $(REAL_TEST_TARGET)
	$(TEST_CMD)

$(REAL_TEST_TARGET): $(TEST_SRCS)
	$(MKDIR)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $(REAL_TEST_TARGET)

clean:
	$(RM)
