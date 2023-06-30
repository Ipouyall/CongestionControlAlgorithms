CXX = g++
CXXFLAGS = -Wall -std=c++11
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = test
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
TARGET = $(BINDIR)/CongestionControlAlgorithms
LIBS = -lgnuplot_i

# ANSI color codes
RED = \033[0;31m
GREEN = \033[0;32m
NC = \033[0m

# Determine OS
UNAME_S := $(shell uname -s)

# Gnuplot installation commands
ifeq ($(UNAME_S),Darwin)  # macOS
	INSTALL_CMD := brew install gnuplot
else ifeq ($(UNAME_S),Linux)  # Linux
	ifeq ($(shell which apt-get 2> /dev/null),)
		ifeq ($(shell which yum 2> /dev/null),)
			INSTALL_CMD := echo "Could not detect package manager. Please install Gnuplot manually."
		else
			INSTALL_CMD := sudo yum install -y gnuplot
		endif
	else
		INSTALL_CMD := sudo apt-get install -y gnuplot
	endif
else
	INSTALL_CMD := echo "Unsupported operating system. Please install Gnuplot manually."
endif

# Build rules
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories
$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Phony targets
.PHONY: all build clean install_gnuplot deps

all: build

build: $(TARGET)

clean:
	@echo "$(RED)Removing object files and executables...$(NC)"
	@rm -rf $(OBJDIR) $(BINDIR)
	@echo "$(RED)Removing generated files...$(NC)"
	@rm -rf tcp_reno.csv tcp_new_reno.csv tcp_bbr.csv
	@echo "$(GREEN)Done!$(NC)"

install_gnuplot:
	$(INSTALL_CMD)

deps: install_gnuplot