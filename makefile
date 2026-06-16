# ================================
# Project directories
# ================================
SRCDIR  := src
OBJDIR  := build/obj
BINDIR  := build

TARGET  := $(BINDIR)/mmsl_enc

# ================================
# Compiler
# ================================
CXX       := g++
STANDARD  := -std=c++23

# ================================
# Compiler flags
# ================================
IGNORE_ASSERTVARS := \
	-Wno-unused-but-set-variable \
	-Wno-sign-compare \
	-Wno-maybe-uninitialized
CXXFLAGS := -Wall -Wextra -Werror -O3 $(STANDARD)

# ================================
# CaDiCaL
# ================================
CADICAL_FOLDER	?= cadical-2.2.1
CADICAL_INC     := ./$(CADICAL_FOLDER)
CADICAL_LIB_DIR := ./$(CADICAL_FOLDER)
CADICAL_LIB     := -lcadical

INCLUDES := -I$(CADICAL_INC)

# ================================
# Source files
# ================================
SOURCES := \
	encoders/general/clause_container.cpp \
	encoders/general/sat_solver_cadical.cpp \
	encoders/general/var_handler.cpp \
	encoders/iteration/ite_encoder.cpp \
	encoders/iteration/ite_instance_data.cpp \
	encoders/iteration/ite_instance.cpp \
	encoders/iteration/ite_ladder.cpp \
	graph/graph.cpp \
	searchers/ite_bfs.cpp \
	searchers/ite_from_ub.cpp \
	searchers/iteration.cpp \
	searchers/searcher.cpp \
	utils/args_parser.cpp \
	utils/pid_manager.cpp \
	utils/signal_handler.cpp \
	utils/usage.cpp \
	utils/version.cpp \
	encoder.cpp \
	global_data.cpp \
	main.cpp 

# ================================
# Object files
# ================================
OBJECTS := $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# ================================
# Default target
# ================================
.PHONY: all
all: $(TARGET)

# ================================
# Link
# ================================
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -L$(CADICAL_LIB_DIR) $(CADICAL_LIB) -o $@

# ================================
# Compile rules
# ================================
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Special flags for specific files
$(OBJDIR)/bdd.o: CXXFLAGS += $(IGNORE_ASSERTVARS)
$(OBJDIR)/duplex_encoder.o: CXXFLAGS += $(IGNORE_ASSERTVARS)

# ================================
# Clean
# ================================
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET) *.a *~ *.out

# ================================
# Archive
# ================================
.PHONY: tar
tar:
	tar cfv mmsl_enc.tar \
		makefile \
		$(SRCDIR) \
		$(CADICAL_LIB_DIR)/*.a \
		$(CADICAL_LIB_DIR)/*.hpp