#########################################################################
# File Name: makefile
# Author: ShiShupeng
# mail: shishupeng@mail.nsccwx.cn
# Created Time: 2017年10月19日 星期四 09时16分19秒
#########################################################################

TARGET = test
CC = icc
CFLAGS = -I/$(MYLIB)/include/

OBJ = pi.o

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

run:
	bsub -I -q q_x86_expr -N 1 -J $(TARGET) ./$(TARGET)
.PHONY : clean
clean:
	-rm -rf $(TARGET) $(OBJ) *.swp

