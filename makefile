ARCH := x86_64

CC = clang
AR = ar

p = .
SRC = $(p)/src

SRC_DIRS = $(SRC)/*
SRC_ARCH = $(wildcard $(addsuffix /$(ARCH)/*.[cs],$(SRC_DIRS)))
SRC_BASE = $(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
SRC_ALL = $(SRC_ARCH) $(SRC_BASE)
OBJ = $(addprefix obj/, $(SRC_ALL:$(p)/%=%.o))

CFLAGS = -std=c11 -ffreestanding -nostdlib -pipe -I src/inc -include src/inc/lib.h

CC_CMD = $(CC) $(CFLAGS) -o $< -o $@
AR_CMD = $(AR) rc $@ $<

all:
	@echo $(OBJ)

lib.a: $(OBJ)
	$(AR_CMD)

obj/%.o: $(p)/%.s
	$(CC_CMD)

obj/%.o: $(p)/%.c
	$(CC_CMD)
