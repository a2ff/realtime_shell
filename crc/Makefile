OPTIONS=CRC16
OPTIONS_CRC16=PRECALC RUNTIME DEBUG
DEFS=
OBJS=crc16.o
CFLAGS=-std=c11 -O3 -g
EXE=testcase.exe

OPTDEFS=$(foreach i,$(OPTIONS),$(patsubst %,_$i_%,$(OPTIONS_$i)))
DEFS+=$(OPTDEFS)
CFLAGS+=$(patsubst %,-D%, $(DEFS))

all: $(EXE:.exe=.lst)

test: all
	./testcase.exe

$(EXE): $(EXE:.exe=.o) $(OBJS)
	$(CC) $^ -o $@

$(EXE:.exe=.lst): $(EXE)
	objdump -S -M intel $< > $@

testcase.o crc16.o: crc16.h

clean:
	rm -f *.o *.lst $(EXE)

.PHONY: all clean
