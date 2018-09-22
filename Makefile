CC := @g++
RM := @rm -rf
DEBUG := 1

ALL_CFLAGS = -g -O2 -std=c++11 -pg

INCS_DIR := ./
LIBS_DIR := ./
SRCS_DIR := ./
INSTALL_DIR := ./
OUT_EXE_NAME := gen
OUT_EXE := $(INSTALL_DIR)$(OUT_EXE_NAME)

INC_PATH := $(addprefix -I, $(INCS_DIR), $(SRCS_DIR))
LIB_PATH := $(addprefix -L, $(LIBS_DIR))

CFLAGS := -O2 -std=c++11
ifeq ($(DEBUG), 1)
CFLAGS += -g
endif

LIBS_FLAGS := 

MAIN := $(MAIN)

all: 
	$(CC) $(MAIN) lamia_timer.cc -o $(OUT_EXE) $(CFLAGS) $(INC_PATH) $(LIB_PATH) $(LIBS_FLAGS)
  
clean:
	$(RM) $(OUT_EXE) core

