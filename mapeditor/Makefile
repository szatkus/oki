include ../Makefile.global

FILES=MEargc.o MEevent.o MEmain.o MEmap.o MEmove.o MErefresh.o MEtext.o \
../src/conf.o ../src/data.o ../src/font.o ../src/image.o ../src/okiGL.o

all: $(FILES)
	$(CC) $(CLIBS) $(FILES) -o ../oki_me

.c.o:
	$(CC) $(CFLAGS) -I../src -c -o $@ $<

clean:
	rm -f *.o

install: all
