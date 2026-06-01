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
	encoders/clause_container.cpp \
	encoders/instance_data.cpp \
	encoders/instance_encoder.cpp \
	encoders/ladder_encoder.cpp \
	encoders/mmsl_instance.cpp \
	encoders/sat_solver_cadical.cpp \
	encoders/var_handler.cpp \
	graph/graph.cpp \
	searchers/mmsl_iterate_from_ub.cpp \
	searchers/mmsl_iterate.cpp \
	utils/args_parser.cpp \
	utils/pid_manager.cpp \
	utils/signal_handler.cpp \
	utils/usage.cpp \
	utils/version.cpp \
	global_data.cpp \
	main.cpp \
	mmsl_encoder.cpp

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