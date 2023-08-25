#
# build binary file:
#   riscv64-linux-gnu-gcc ${fname}.c -o ${fname} -march=rv64imafd -mcmodel=medany -lm -e gpumain -nostartfiles -static
#

CC=riscv64-linux-gnu-gcc
CPP=riscv64-linux-gnu-g++
CFLAGS=-march=rv64imafd -mcmodel=medany -lm -e gpumain -nostartfiles -static -fno-PIC

CSOURCES=$(wildcard *.c)
CTARGETS=$(patsubst %.c,%,$(CSOURCES))

CPPSOURCES=$(wildcard *.cpp)
CPPTARGETS=$(patsubst %.cpp,%,$(CPPSOURCES))

ALL:${CTARGETS} ${CPPTARGETS}

${CTARGETS}:%:%.c
	echo "C" $^
	${CC} $^ -o $@ ${CFLAGS}


${CPPTARGETS}:%:%.cpp
	echo "CPP" $^
	${CPP} $^ -o $@ ${CFLAGS}

.PHONY: clean

clean:
	rm -f ${CTARGETS}
	rm -f ${CPPTARGETS}
