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
	rm -f ${OBJECTS}
