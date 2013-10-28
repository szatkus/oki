include ../Makefile.global

FILES=_.js config.js game.js game_object.js launcher.js main.js maps.js menu.js renderer.js sound.js

all: $(FILES)
	cat $(FILES) | $(UGLIFY) > ../oki.js

%.js : %.coffee
	$(COFFEE) -cm $<

clean:
	rm -f *.js *.map ../oki.js

install: all
