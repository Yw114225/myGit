## TARGET : Dependcy
	## command
CC = gcc
#CFLAGS = -Wall
DEBUG = -g
CFLAGS := -Wall -I./inc
LDFLAGS := -L./exec -lsqlite3
CURR_PATH = $(shell pwd)

# 虚拟路径，make先在当前目录下找依赖文件，找不到再到VAPTH路径下一次寻找
#VPATH = ./inc : ./src : ./obj : ./user_db 

TARGET  := client server
SOURCES := $(addsuffix .c, $(TARGET)) # 添加后缀.c
OBJECTS := $(addsuffix .o, $(TARGET)) 

OBJ_DIR := ./obj
EXEC_DIR := ./exec


OBJECTS := $(SOURCES: %.c = $(OBJ_DIR)/%.o)) # 添加前缀
EXECUTABLES := $(addprefix $(EXEC_DIR)/, $(TARGET))

all:$(EXECUTABLES)
#client : $(OBJECTS)
	#$(CC) -o $@ $^  $(DEBUG) $(CFLAGS)
#$(EXER_DIR) : $(ONJ_DIR)/%.o
	#$(CC) -o $@ $^ $(DEBUG) $(CFLAGS) -lsqlite3
$(OBJ_DIR)/%.o:%.c
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@
$(EXEC_DIR)/%: $(OBJ_DIR)/%.o
	$(CC) -o $@ $< $(LDFLAGS)
#clean:
	#rm -f $(TARGET) $(OBJECTS)
#.PHONY: all
#.PHONY: clean
clean:
	find . -type f \( -name "client" -name "*.o" \)  -exec rm -vi {} +
.PHONY: clean

