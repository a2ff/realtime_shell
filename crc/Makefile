OPTIONS=CRC16
OPTIONS_CRC16=PRECALC RUNTIME DEBUG
OBJS=crc16.o

EXE=testcase
OPTDEFS=$(foreach i,$(OPTIONS),$(patsubst %,_$i_%,$(OPTIONS_$i)))
DEFS+=$(OPTDEFS)
CFLAGS=$(patsubst %,-D%, $(DEFS))

all: $(EXE)

test: all
	./testcase

$(EXE): $(EXE:=.o) $(OBJS)

testcase.o crc16.o: crc16.h portability.h

clean:
	rm -f *.o $(EXE)

.PHONY: all clean
