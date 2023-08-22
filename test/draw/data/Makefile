#
# build binary file:
#   riscv64-linux-gnu-gcc -c ${fname}.c -o ${fname}.o -march=rv64imafd -mcmodel=medany
#   riscv64-linux-gnu-ld ${fname}.o -o ${fname} -egpumain
#

COMPILER=riscv64-linux-gnu-gcc
LINKER=riscv64-linux-gnu-ld
CFLAGS=-march=rv64imafd -mcmodel=medany

SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
TARGETS=$(patsubst %.c,%,$(SOURCES))

ALL:${TARGETS}

${TARGETS}:%:%.o
	${LINKER} $^ -o $@ -egpumain

%.o:%.c
	${COMPILER} -c $^ -o $@ ${CFLAGS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${TARGETS}
