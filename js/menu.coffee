MENU_START = 70
MENU_MAIN = 0
MENU_OPTIONS = 1
MENU_KEYS = 2

app.menu = 
  pointer: {}
  
  mode: MENU_MAIN
  
  show: ->
    
    app.renderer.fillScreen('white')
    app.renderer.context.drawImage(app.renderer.images.logo, 30, 0)
    app.renderer.context.drawImage(app.renderer.images.oki, 0, 0, 10, 10, @pointer.x, @pointer.y, 10, 10)
    app.renderer.drawCenteredText("szatkus 2006", 50);
    switch (@mode)
      when MENU_MAIN
        app.renderer.drawCenteredText("start game", MENU_START)
        app.renderer.drawCenteredText("options", MENU_START + 10)
      when MENU_OPTIONS
        app.renderer.drawCenteredText("back", MENU_START)
        if @pointer.y is MENU_START + 10
            app.renderer.drawCenteredText("restart game to apply", MENU_START - 10)
        #if (fs) strcpy(temp, "yes");
        #else strcpy(temp, "no");
        #sprintf(temp2, "fullscreen %s", temp);
        #app.renderer.drawCenteredText(temp2, MENU_START+10);
        app.renderer.drawCenteredText("redefine keys", MENU_START + 20)
        #app.renderer.drawCenteredText(maplist[mapset], MENU_START+30);
        app.renderer.drawCenteredText("clear save (!)", MENU_START + 40)
      when MENU_KEYS
        switch (key)
          when 0
           app.renderer.drawText("left", 60, MENU_START)
          when 1
           app.renderer.drawText("up", 60, MENU_START)
          when 2
           app.renderer.drawText("right", 60, MENU_START)
          when 3
           app.renderer.drawText("down", 60, MENU_START)
          when 4
           app.renderer.drawText("jump", 60, MENU_START)
          when 5
           app.renderer.drawText("run", 60, MENU_START)



  start: ->    
    @pointer.x = 30;
    @pointer.y = MENU_START;
    #FIXME
    @pointer.width = 10;
    @pointer.height = 10;
    @end = 10;
    @show()
    window.onkeydown = (event) =>
      if (@mode != MENU_KEYS)
        switch event.which
            when 38
                app.sound.play('cursor')
                @pointer.y -= 10;
                if (@pointer.y < MENU_START) 
                    @pointer.y = MENU_START + @end
            when 40
                app.sound.play('cursor')
                @pointer.y += 10;
                if (@pointer.y > MENU_START + @end) 
                    @pointer.y = MENU_START
            when 13
              app.sound.play('click')
              if @mode is MENU_MAIN
                if @pointer.y is MENU_START
                  app.game.start(app.config.mapset)
                else
                  @mode = MENU_OPTIONS;
                  @pointer.y = MENU_START
                  @end = 40
              else
                switch @pointer.y
                  when MENU_START
                    @mode = MENU_MAIN
                    @pointer.y = MENU_START;
                    @end = 20;
                  when MENU_START+10
                       fs = !fs;
                  when MENU_START+20
                     @mode = MENU_KEYS;
                     key = 0;
                  when MENU_START+30
                    mapset++;
                    if (mapset == mapsets)
                       mapset = 0;
                  when MENU_START+40
                   progress = 0;
                   coins = 0;
                   lifes = 2;
                   ###
                   oki->speed = 3;
                   oki->jump.power = 5;
                   oki->jump.time = 5;
                   oki->strength = 0;
                   oki->run = 0;
                   oki->HP = 0;
                   oki->shoot = 0;
                   sprintf(temp, "maps/%s/save", maplist[mapset]);
                   save_game(temp);
                   ###
        @show();
      else
      ###
          switch (key)
          {
              case 0: left = event.key.keysym.sym; break;
              case 1: up = event.key.keysym.sym; break;
              case 2: right = event.key.keysym.sym; break;
              case 3: down = event.key.keysym.sym; break;
              case 4: A = event.key.keysym.sym; break;
              case 5: 
                  B = event.key.keysym.sym;
                  @mode = MENU_OPTIONS;
              break;
          }
          key++;
          @show();
      ###
