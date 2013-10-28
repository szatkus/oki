app.game =
  maps: []
  background: null
  redraw: ->
    app.renderer.fillScreen('white')
    app.renderer.context.drawImage(@background, 0, 0)
    app.renderer.context.drawImage(app.renderer.images.oki, 0, 0, 10, 10, @maps[@progress].x, @maps[@progress].y, 10, 10)
  
  loadGame: (mapsetName) ->
    getData = (name) -> parseInt(localStorage.getItem("oki/#{mapsetName}/#{name}"))
    @progress = getData('progress') || 0
    @coins = getData('coins') || 0
    @lifes = getData('lifes') || 2
    @oki.speed = getData('speed') || 3
    @oki.jumpPower = getData('jumpp') || 5
    @oki.strength = getData('strength') || 0
    @oki.run = getData('run') || 0
    @oki.jumpDuration = getData('jumpd') || 5
    @oki.life = getData('life') || 0
    @oki.shoot = getData('shoot') || 0
  
  loadMapset: (name, callback) ->
    request = new XMLHttpRequest
    request.open('get', "maps/#{name}/index");
    request.onreadystatechange = =>
      if request.readyState is 4 and request.status is 200
        for line, i in request.responseText.trim().split('\n')
          if i is 0
            backgroundPath = "maps/#{name}/#{line}"
          else
            if (i - 1) % 3 == 0
              data = {}
              data.name = line
            if (i - 1) % 3 == 1
              data.x = parseInt(line)
            if (i - 1) % 3 == 2
              data.y = parseInt(line)
              @maps.push(data)
        @background = app.renderer.loadImage(backgroundPath, callback)
    request.send()
  
  saveGame: (mapsetName) ->
    getData = (name, value) -> localStorage.setItem("oki/#{mapsetName}/#{name}", value)
    setData('progress', @progress)
    setData('coins', @coins)
    setData('lifes', @lifes)
    setData('speed', @oki.speed)
    setData('jumpp', @oki.jumpPower)
    setData('strength', @oki.strength)
    setData('run', @oki.run)
    setData('jumpd', @oki.jumpDuration)
    setData('life', @oki.life)
    setData('shoot', @oki.shoot)
  
  start: (mapsetName) ->
    @selectedMap = 1;
    #mask = 0;
    @oki = new app.GameObject
      image: app.renderer.images.oki
      animation:
        x: 0
        y: 0
        width: app.BLOCK_WIDTH
        height: app.BLOCK_HEIGHT
    #die = 0;
    #pause_game = 0;
    #darkness = 1;
    @loadMapset mapsetName, =>
      @loadGame();
      #@redraw();
      #window.onkeydown = (event) =>
       # if event.which == app.config.buttonA or event.which == 13
      app.sound.play('click')
      mapName = @maps[@progress].name
      map = new app.Map("maps/#{mapsetName}/#{mapName}", this)
      map.start()
      ###
          check_event();
          if (lifes < 0) 
          {
              play = 0;
              @selectedMap = 0;
          }
          if (progress == maps)
          {
              rect.x = 0;
              rect.y = 0;
              rect.w = RES_X;
              rect.h = RES_Y;
              SDL_FillRect(screen, &rect, WHITE);
              center_text("THE END", RES_Y/2);
              sprintf(temp, "score: %d", 
                      coins+lifes*100+progress*100);
              center_text(temp, RES_Y/2+LETTER_HEIGHT);
              lifes = 0;
              show_screen();
              event.type = 0;
              while (event.type != SDL_KEYDOWN)
                SDL_PollEvent(&event);
              @selectedMap = 0;
          
        if event.which == 27 or event.which == 81
          check_quit()
          #oki->pos.x = map[pos].x;
          #oki->pos.y = map[pos].y;
          #if (lifes > 0) show_select();
###
