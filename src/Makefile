include ../Makefile.global

FILES=argc.o collision.o conf.o data.o event.o font.o fps.o game.o image.o \
main.o map.o menu.o move.o objects.o okiGL.o quit.o save.o sound.o timer.o

all: $(FILES)
	$(CC) $(CLIBS) $(FILES) -o ../oki

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o

install: all
