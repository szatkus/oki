include Makefile.global

all:
	@make -C src
	@make -C mapeditor
	@make -C extra
	@make -C doc
	@make -C gfx
	@make -C maps
	@make -C snd

clean:
	rm -f oki
	rm -f oki_bash
	rm -f oki_me
	rm -f core.*
	@make -C src clean
	@make -C mapeditor clean
	@make -C extra clean
	@make -C doc clean
	@make -C gfx clean
	@make -C maps clean
	@make -C snd clean

install:
	mkdir -p $(WORKDIR)
	@make -C src install
	@make -C mapeditor install
	@make -C extra install
	@make -C doc install
	@make -C gfx install
	@make -C maps install
	@make -C snd install
	cp -f oki $(WORKDIR)
	cp -f oki_me $(WORKDIR)
	cp -f COPYING $(WORKDIR)
	cp -f README $(WORKDIR)
	mkdir -p $(PREFIX)/share/pixmaps
	cp -f gfx/oki40.png $(PREFIX)/share/pixmaps/oki.png

uninstall:
	rm -f $(PREFIX)/bin/oki
	rm -rf $(WORKDIR)

mrproper: clean
	rm -f Makefile.global
	rm -f extra/oki_bash
	mv Makefile Makefile.in
