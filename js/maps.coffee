app.maps =
  maplist: []
  loadMaplist: (callback) ->
    request = new XMLHttpRequest
    request.open('get', 'maps/maps');
    request.onreadystatechange = =>
      if request.readyState is 4 and request.status is 200
        @maplist = request.responseText.trim().split('\n')
        callback(@maplist)
    request.send()

class app.Map
  constructor: (@filename, @game) ->
    @oki = game.oki
  load: (callback) ->
    request = new XMLHttpRequest
    request.open('get', @filename);
    request.responseType = 'arraybuffer'
    request.onreadystatechange = =>
     if request.readyState == 4 and request.status == 200
      data = new Uint8Array(request.response)
      @objects = []
      @animations = []
      pos = 3
      @width = data[pos++] - 1
      @height = data[pos++] - 1
      @totalCoins = 0
      @totalLifes = 0
      @gameBuffer = document.createElement('canvas')
      @gameBuffer.width = (@width + 1) * app.BLOCK_WIDTH
      @gameBuffer.height = (@height + 1) * app.BLOCK_HEIGHT
      @staticsBuffer = document.createElement('canvas')
      @staticsBuffer.width = (@width + 1) * app.BLOCK_WIDTH
      @staticsBuffer.height = (@height + 1) * app.BLOCK_HEIGHT
      pos += 11
      @blocks = []
      for x in [0..@width]
        @blocks[x] = []
        for y in [0..@height]
          @blocks[x][y] = {}
      for y in [0..@height]
        for x in [0..@width]
            block = 
              tile: data[pos++]
              type: 0
            newObject = null
            newAnimation = null
            if block.tile >= 192
                block.tile -= 192;
                console.log(block.tile)
                newObject = new app.GameObject
                  x: x * app.BLOCK_WIDTH
                  y: y * app.BLOCK_WIDTH
                  width: app.BLOCK_WIDTH
                  height: app.BLOCK_WIDTH
                  direction: 'left'
                  type: 'enemy'
                  image: app.renderer.images.events
                  animation:
                    x: 0
                    y: 0
                    width: app.BLOCK_WIDTH
                    height: app.BLOCK_HEIGHT
                switch (block.tile)
                    when 0
                        newObject.speed = 1;
                        newObject.AI = 1;
                        newObject.mass = 5;
                        newObject.image = app.renderer.images.monster1
                    when 1
                        newObject.direction = 0;
                        newObject.type = 'coin';
                        @totalCoins++;
                    when 2
                        newObject.direction = 0;   
                        newObject.type = 'life';
                        newObject.animation.x = app.BLOCK_WIDTH;
                        @totalLifes++;
                    when 3
                        newObject.direction = 0;
                        newObject.type = 'strength';
                        newObject.animation.x = 3 * app.BLOCK_WIDTH;
                    when 4
                        newObject.direction = 0;
                        newObject.type = 'death';
                        newObject.animation.y = app.BLOCK_HEIGHT;
                    when 5
                        newObject.direction = 0;
                        newObject.type = 'jump';
                        newObject.animation.x = app.BLOCK_WIDTH;
                        newObject.animation.y = app.BLOCK_HEIGHT;
                    when 6
                        newObject.direction = 0;
                        newObject.type = 'speed';
                        newObject.animation.x = 2 * app.BLOCK_WIDTH;
                        newObject.animation.y = app.BLOCK_HEIGHT;
                    when 7
                        newObject.speed = 2;
                        newObject.AI = 1;
                        newObject.type = 'enemy';
                        newObject.mass = 7;
                        newObject.image = app.renderer.images.monster2
                    when 8
                      ###
                        newObject.direction = 0;
                        newObject.speed = 1;
                        newObject.type = OBJ_WATER;
                        newObject.image = 
                        SDL_CreateRGBSurface(SDL_HWSURFACE, game.w, game.h,
                                             24, 0, 0, 0, 0);
                        for (i=0;i<=level.width;i++)
                        
                            cut_image(tileset, newObject.image, 5, 8, 
                                      i * app.BLOCK_WIDTH, 0, app.BLOCK_WIDTH, 
                                      app.BLOCK_HEIGHT);
                            for (t=1;t<=level.height;t++)
                            
                            cut_image(tileset, newObject.image, 6, 8, 
                                      i * app.BLOCK_WIDTH, t * app.BLOCK_HEIGHT, app.BLOCK_WIDTH, 
                                      app.BLOCK_HEIGHT);
                            
                        
                        newObject.animation.w = game.w;
                        newObject.animation.h = app.BLOCK_HEIGHT;
                        newObject.pos.x = 0;
                        newObject.pos.w = game.w;
                      ###
                    when 9
                        newObject.direction = 0;
                        newObject.type = OBJ_WATER_STOP;
                        newObject.image = null;
                    when 10
                        newObject.direction = 0;
                        newObject.type = OBJ_WATER_UP;
                        newObject.image = null;
                    when 11
                        newObject.direction = 0;
                        newObject.type = OBJ_RUN;
                        newObject.animation.x = 3 * app.BLOCK_WIDTH;
                        newObject.animation.y = app.BLOCK_HEIGHT;
                    when 12
                        newObject.direction = 0;
                        newObject.speed = 2 * app.BLOCK_HEIGHT;
                        newObject.type = OBJ_UP;
                        newObject.animation.y = 2 * app.BLOCK_HEIGHT;
                    when 13
                        newObject.direction = 0;
                        newObject.type = OBJ_DEATH;
                        newObject.animation.x = app.BLOCK_HEIGHT;
                        newObject.animation.y = 2 * app.BLOCK_HEIGHT;
                    when 14
                        newObject.direction = 0;
                        newObject.type = OBJ_DEATH;
                        newObject.animation.x = 2 * app.BLOCK_HEIGHT;
                        newObject.animation.y = 2 * app.BLOCK_HEIGHT;
                    when 15
                        newObject.direction = 0;
                        newObject.type = OBJ_DEATH;
                        newObject.animation.x = 3 * app.BLOCK_HEIGHT;
                        newObject.animation.y = 2 * app.BLOCK_HEIGHT;
                    when 16
                        newObject.speed = 3;
                        newObject.AI = 2;
                        newObject.mass = 9;
                        newObject.strength = 1;
                        newObject.image = app.renderer.images.monster2
                        newObject.animation.w = 2 * app.BLOCK_WIDTH;
                        newObject.animation.h = 2 * app.BLOCK_HEIGHT;
                        newObject.pos.w = 2 * app.BLOCK_WIDTH;
                        newObject.pos.h = 2 * app.BLOCK_HEIGHT;
                    when 17
                      text = ''
                      while data[pos] != 0
                        text += String.fromCharCode(data[pos])
                        pos++
                      newObject.speed = 0;
                      newObject.text = text;
                      newObject.type = 'text'
                      newObject.image = null;
                    when 18
                        newObject.speed = 6;
                        newObject.AI = 2;
                        newObject.mass = 3;
                        newObject.strength = 2;
                        newObject.jump.power = 5;
                        newObject.jump.time = 6;
                        newObject.image = app.renderer.images.monster3
                    when 19
                        newObject.speed = 11;
                        newObject.AI = 2;
                        newObject.mass = 5;
                        newObject.strength = 3;
                        newObject.jump.power = 7;
                        newObject.jump.time = 8;
                        newObject.image = app.renderer.images.monster4
                    when 21
                        newObject.direction = 0;
                        newObject.AI = last_key;
                        newObject.type = OBJ_KEY;
                        newObject.image = events;
                        newObject.animation.x = 6 * app.BLOCK_HEIGHT;
                        newObject.animation.y = 2 * app.BLOCK_HEIGHT;
                        last_key++;
                    when 22
                        newObject.direction = 0;
                        newObject.type = OBJ_JUMP_TIME;
                        newObject.animation.x = 7 * app.BLOCK_WIDTH;
                        newObject.animation.y = 2 * app.BLOCK_HEIGHT;
                    when 23
                        newObject.speed = 3;
                        newObject.AI = 2;
                        newObject.mass = 3;
                        newObject.strength = 1;
                        newObject.HP = 1;
                        newObject.image = app.renderer.images.monster5
                        newObject.run = 1;
                    when 24
                        newObject.direction = 0;
                        newObject.speed = 5 * app.BLOCK_HEIGHT;
                        newObject.type = OBJ_UP;
                        newObject.animation.x = app.BLOCK_WIDTH;
                        newObject.animation.y = 3 * app.BLOCK_HEIGHT;
                    when 25
                        newObject.speed = 2;
                        newObject.AI = 1;
                        newObject.mass = 5;
                        newObject.strength = last_text;
                        newObject.type = OBJ_TEXT;
                        newObject.image = man;
                        fgets(text[last_text], fgetc(file), file);
                        last_text++;
                    when 26
                        oke = newObject;
                        oke.mass = 6;
                        oke.AI = 2;
                        oke.type = 0;
                        oke.image = oke_img;
                        oke.speed = oki.speed-1;
                        oke.strength = oki.strength+1;
                        oke.run = oki.run;
                        oke.jump.power = oki.jump.power;
                        oke.jump.time = oki.jump.time;
                    when 27
                        newObject.speed = 7;
                        newObject.AI = 1;
                        newObject.mass = 8;
                        newObject.strength = 3;
                        newObject.HP = 3;
                        newObject.image = app.renderer.images.monster6
                    when 28
                        newObject.direction = 0;
                        newObject.speed = 100 * app.BLOCK_HEIGHT;
                        newObject.type = OBJ_UP;
                        newObject.animation.x = 2 * app.BLOCK_WIDTH;
                        newObject.animation.y = 3 * app.BLOCK_HEIGHT;
                    when 29
                        newObject.type = OBJ_DEATH;
                        newObject.speed = 2;
                        newObject.AI = 1;
                        newObject.mass = 9;
                        newObject.image = app.renderer.images.monster7
                    when 30
                        newObject.type = OBJ_DARKER;
                        newObject.image = null;
                    when 31
                        newObject.type = OBJ_LIGHTER;
                        newObject.image = null;
                    when 32
                        newObject.speed = 3;
                        newObject.AI = 2;
                        newObject.mass = 5;
                        newObject.strength = 3;
                        newObject.image = app.renderer.images.monster8
                    when 33
                        newObject.speed = 2;
                        newObject.AI = 2;
                        newObject.mass = 1;
                        newObject.strength = 5;
                        newObject.image = app.renderer.images.monster9
                        newObject.animation.w = 4 * app.BLOCK_WIDTH;
                        newObject.animation.h = 4 * app.BLOCK_HEIGHT;
                        newObject.pos.w = 4 * app.BLOCK_WIDTH;
                        newObject.pos.h = 4 * app.BLOCK_HEIGHT;
                    when 34
                        newObject.direction = 0;
                        newObject.type = 0;
                        newObject.image = null;
                        newAnimation = new app.Animation
                        newAnimation.frames = 3;
                        newAnimation.loops = 0;
                        newAnimation.delay = 2;
                        newAnimation.image = app.renderer.images.torch;
                        newAnimation.x = newObject.x
                        newAnimation.y = newObject.y
                        newAnimation.width = newObject.width
                        newAnimation.height = newObject.height
                        newAnimation.frameX = 0;
                        newAnimation.frameY = 0;
                        newAnimation.frameWidth = app.BLOCK_WIDTH;
                        newAnimation.frameHeight = app.BLOCK_HEIGHT;
                    when 35
                        newObject.speed = 2;
                        newObject.AI = 2;
                        newObject.mass = 5;
                        newObject.type = OBJ_CLONE;
                        newObject.image = man;
                    when 36
                        newObject.speed = 3;
                        newObject.jump.time = 5;
                        newObject.jump.power = 5;
                        newObject.AI = 2;
                        newObject.mass = 5;
                        newObject.type = OBJ_CLONE;
                        newObject.image = app.renderer.images.monster10
                    when 37
                        newObject.direction = 0;
                        newObject.type = OBJ_HP;
                        newObject.animation.x = 5 * app.BLOCK_WIDTH;
                        newObject.animation.y = 3 * app.BLOCK_HEIGHT;
                    when 38
                        newObject.direction = 0;
                        newObject.type = OBJ_HEALTH;
                        newObject.animation.x = 6 * app.BLOCK_WIDTH;
                        newObject.animation.y = 3 * app.BLOCK_HEIGHT;
                    when 39
                        newObject.direction = 0;
                        newObject.type = OBJ_DEATH;
                        newObject.image = rock;
                        newObject.mass = 15;
                        newObject.animation.w = 3 * app.BLOCK_WIDTH;
                        newObject.animation.h = 3 * app.BLOCK_HEIGHT;
                        newObject.pos.w = 3 * app.BLOCK_WIDTH;
                        newObject.pos.h = 3 * app.BLOCK_HEIGHT;
                    when 40
                        newObject.direction = 0;
                        newObject.type = OBJ_BOMB;
                        newObject.strength = 3;
                        newObject.animation.x = 7 * app.BLOCK_WIDTH;
                        newObject.animation.y = 3 * app.BLOCK_HEIGHT;
                    when 41
                        newObject.direction = 0;
                        newObject.type = OBJ_TRAP;
                        newObject.animation.x = 0;
                        newObject.animation.y = 4 * app.BLOCK_HEIGHT;
                        newObject.animation.h = 2 * app.BLOCK_HEIGHT;
                        newObject.pos.y -= app.BLOCK_HEIGHT;
                        newObject.pos.h = 2 * app.BLOCK_HEIGHT;
                    when 42
                        newObject.direction = 0;
                        newObject.type = OBJ_SHOOT;
                        newObject.animation.x = app.BLOCK_WIDTH;
                        newObject.animation.y = 4 * app.BLOCK_HEIGHT;
                    when 43
                        newObject.direction = 0;
                        newObject.type = OBJ_FALL;
                        newObject.strength = 5;
                        newObject.animation.x = 2 * app.BLOCK_WIDTH;
                        newObject.animation.y = 4 * app.BLOCK_HEIGHT;
                    when 44
                        newObject.speed = 1;
                        newObject.AI = 1;
                        newObject.mass = 0;
                        newObject.image = app.renderer.images.monster12
                        newObject.strength = 99;
                    when 45
                        newObject.mass = 0;
                        newObject.direction = DIR_RIGHT;
                        newObject.image = app.renderer.images.monster12
                        newObject.strength = 99;
                        newObject.ghost = 1;
                    when 46
                        newObject.mass = 0;
                        newObject.speed = 1;
                        newObject.AI = 1;
                        newObject.image = app.renderer.images.monster12
                        newObject.strength = 99;
                        newObject.ghost = 1;
                    when 47
                        newObject.speed = 1;
                        newObject.AI = 2;
                        newObject.mass = 0;
                        newObject.image = app.renderer.images.monster12
                        newObject.strength = 99;
                    when 48
                        newObject.speed = 3;
                        newObject.AI = 1;
                        newObject.mass = 3;
                        newObject.strength = 1;
                        newObject.HP = 1;
                        newObject.image = app.renderer.images.monster5
                    when 49
                        newObject.direction = 0;
                        newObject.type = 0;
                        newObject.image = null;
                        newAnimation = new app.Animation
                        newAnimation.frames = 5;
                        newAnimation.isLooped = 0;
                        newAnimation.delay = 2;
                        newAnimation.image = glass;
                        newAnimation.x = newObject.x
                        newAnimation.y = newObject.y
                        newAnimation.width = newObject.width
                        newAnimation.height = newObject.height
                        newAnimation.frameX = 0;
                        newAnimation.frameY = 0;
                        newAnimation.frameWidth = app.BLOCK_WIDTH*2;
                        newAnimation.frameHeight = app.BLOCK_HEIGHT*4;
                    when 50
                        newObject.direction = 0;
                        newObject.type = 0;
                        newObject.image = null;
                        newAnimation = new app.Animation
                        newAnimation.frames = 5;
                        newAnimation.isLooped = 0;
                        newAnimation.delay = 2;
                        newAnimation.image = app.renderer.images.computer;
                        newAnimation.x = newObject.x
                        newAnimation.y = newObject.y
                        newAnimation.width = newObject.width
                        newAnimation.height = newObject.height
                        newAnimation.frameX = 0;
                        newAnimation.frameY = 0;
                        newAnimation.frameWidth = app.BLOCK_WIDTH;
                        newAnimation.frameHeight = app.BLOCK_HEIGHT;
                    when 51
                        newObject.speed = 2;
                        newObject.AI = 1;
                        newObject.mass = 1;
                        newObject.strength = 1;
                        newObject.jump.power = 5;
                        newObject.jump.time = 3;
                        newObject.image = app.renderer.images.monster13
                    when 52
                        newObject.speed = 2;
                        newObject.AI = 2;
                        newObject.mass = 1;
                        newObject.strength = 1;
                        newObject.jump.power = 5;
                        newObject.jump.time = 3;
                        newObject.image = app.renderer.images.monster13
                    when 53
                        newObject.speed = 2;
                        newObject.AI = 1;
                        newObject.mass = 9;
                        newObject.image = app.renderer.images.monster14
                        newObject.animation.w = 2 * app.BLOCK_WIDTH;
                        newObject.animation.h = 2 * app.BLOCK_HEIGHT;
                        newObject.pos.w = 2 * app.BLOCK_WIDTH;
                        newObject.pos.h = 2 * app.BLOCK_HEIGHT;
                        newObject.type = OBJ_BOMB;
                        newObject.strength = 6;
                    when 54
                        newObject.speed = 2;
                        newObject.AI = 2;
                        newObject.mass = 9;
                        newObject.image = app.renderer.images.monster14
                        newObject.animation.w = 2 * app.BLOCK_WIDTH;
                        newObject.animation.h = 2 * app.BLOCK_HEIGHT;
                        newObject.pos.w = 2 * app.BLOCK_WIDTH;
                        newObject.pos.h = 2 * app.BLOCK_HEIGHT;
                        newObject.type = OBJ_BOMB;
                        newObject.strength = 6;
                    when 55
                        newObject.direction = 0;
                        newObject.type = OBJ_BOMB;
                        newObject.strength = 9;
                        newObject.animation.x = 7 * app.BLOCK_WIDTH;
                        newObject.animation.y = 3 * app.BLOCK_HEIGHT;
                    when 56
                        newObject.direction = 0;
                        newObject.type = OBJ_BOMB;
                        newObject.strength = 27;
                        newObject.animation.x = 7 * app.BLOCK_WIDTH;
                        newObject.animation.y = 3 * app.BLOCK_HEIGHT;
                    when 57
                        newObject.direction = 0;
                        newObject.speed = -2 * app.BLOCK_HEIGHT;
                        newObject.type = OBJ_UP;
                        newObject.animation.y = 4 * app.BLOCK_HEIGHT;
                        newObject.animation.x = 3 * app.BLOCK_WIDTH;
                    when 58
                        newObject.direction = 0;
                        newObject.speed = -2 * app.BLOCK_WIDTH;
                        newObject.type = OBJ_GO;
                        newObject.animation.y = 4 * app.BLOCK_HEIGHT;
                        newObject.animation.x = 4 * app.BLOCK_WIDTH;
                    when 59
                        newObject.direction = 0;
                        newObject.speed = 2 * app.BLOCK_WIDTH;
                        newObject.type = OBJ_GO;
                        newObject.animation.y = 4 * app.BLOCK_HEIGHT;
                        newObject.animation.x = 5 * app.BLOCK_WIDTH;
                    when 60
                        newObject.speed = 3;
                        newObject.AI = 2;
                        newObject.mass = 3;
                        newObject.strength = 0;
                        newObject.HP = 1;
                        newObject.image = app.renderer.images.monster11
                        newObject.run = 1;
                        newObject.animation.h = app.BLOCK_HEIGHT+5;
                    when 61
                        newObject.direction = 0;
                        newObject.type = 'exit';
                        newObject.image = events;
                        newObject.animation.y = 3 * app.BLOCK_HEIGHT;
                    when 62
                        newObject.direction = 0;
                        newObject.type = 'exit';
                        newObject.image = null;
                        newAnimation = new app.Animation
                        newAnimation.frames = 4;
                        newAnimation.loops = 0;
                        newAnimation.delay = 0;
                        newAnimation.image = app.renderer.images.exit
                        newAnimation.x = newObject.x
                        newAnimation.y = newObject.y
                        newAnimation.width = newObject.width
                        newAnimation.height = newObject.height
                        newAnimation.frameX = 0;
                        newAnimation.frameY = 0;
                        newAnimation.frameWidth = app.BLOCK_WIDTH;
                        newAnimation.frameHeight = app.BLOCK_HEIGHT;
                    when 63
                        newObject = null
                        @oki.x = x * app.BLOCK_WIDTH;
                        @oki.y = y * app.BLOCK_HEIGHT;
                        #start_pos = oki.pos;
                if block.tile == 20
                    block.tile = 20;
                    block.type = 'wall';
                    ###
                    if (!(newObject.pos.x > door[last_door-1].x &&
                          newObject.pos.x < 
                          door[last_door-1].x+door[last_door-1].w &&
                          newObject.pos.y > door[last_door-1].y &&
                          newObject.pos.y < 
                          door[last_door-1].y+door[last_door-1].h))
                    
                        if (door[last_door-1].x+door[last_door-1].w == 
                            newObject.pos.x && door[last_door-1].y == 
                            newObject.pos.y)
                            door[last_door-1].w+=BLOCK_WIDTH;
                        else
                        
                            if (door[last_door-1].y+door[last_door-1].h == 
                                newObject.pos.y && door[last_door-1].x == 
                                newObject.pos.x)
                                door[last_door-1].h+=BLOCK_HEIGHT;
                            else
                            
                                door[last_door] = newObject.pos;
                                last_door++;
                            
                        
                    
                    last_obj--;
                    ###
                 else block.tile = 0;
                @objects.push(newObject) if newObject?
                @animations.push(newAnimation) if newAnimation?
            
            while (block.tile >= 64)
            
                block.type++;
                block.tile-=64;
            @blocks[x][y] = block
      ###      
      if (oki.shoot) 
        last_obj++;
        oki.shoot = last_obj;
      ###
      @draw()
      @objects.push(@oki)
      callback()
    request.send()


  draw: ->
    for y in [0..@height]
      for x in [0..@width]
        app.renderer.drawTile('tileset', @staticsBuffer.getContext('2d'), @blocks[x][y].tile, 8, x * app.BLOCK_WIDTH, 
                      y * app.BLOCK_HEIGHT, app.BLOCK_WIDTH, app.BLOCK_HEIGHT);
    document.body.appendChild(@staticsBuffer)
    document.body.appendChild(@gameBuffer)
  
  start: ->
    @load =>
        @cameraX = 0
        @cameraY = 0
        window.onkeydown = (event) => 
                    if (event.key.keysym.sym == left) 
                        oki.direction = DIR_LEFT;
                        start = 1;
                    if (event.key.keysym.sym == right)
                        oki.direction = DIR_RIGHT;
                        start = 1;
                    if (event.key.keysym.sym == up) 
                      camera_modifier = -10;
                    if (event.key.keysym.sym == down) 
                      camera_modifier = 10;
                    if (event.key.keysym.sym == A && oki.state != STATE_FALL && !oki.jump.frame) 
                        oki.jump.frame = 1;
                    if (event.key.keysym.sym == B && oki.run)
                        oki.speed = oki.speed*2-1;
                        oki.run = 2;
                    if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)
                      check_quit();
        window.onkeyup = (event) => 
                    if (oki.direction == DIR_LEFT && event.key.keysym.sym == left) 
                        oki.direction = 0;
                    if (oki.direction == DIR_RIGHT && event.key.keysym.sym == right) 
                        oki.direction = 0;
                    if (event.key.keysym.sym == up || event.key.keysym.sym == down)
                        camera_modifier = 0;
                    if (event.key.keysym.sym == A)
                        oki.jump.frame = 0;
                        oki.state = STATE_STAY;
                    if (event.key.keysym.sym == B && oki.run == 2)
                        oki.speed = oki.speed/2+1;
                        oki.run = 1;
                        if (oki.shoot)
                            obj[oki.shoot].vis = 1;
                            obj[oki.shoot].direction = 0;
                            obj[oki.shoot].pos = oki.pos;
                            obj[oki.shoot].anim = oki.anim;
                            obj[oki.shoot].animation.x = 7 * app.BLOCK_WIDTH;
                            obj[oki.shoot].animation.y = 3 * app.BLOCK_HEIGHT;
                            obj[oki.shoot].type = OBJ_ONE_DEATH;
                            obj[oki.shoot].image = events;
                    if (event.key.keysym.sym == SDLK_p) 
                      pause_game = !pause_game;
        callLoop = =>
          app.mainLoop.apply(this, [])
        @timer = setInterval(callLoop, 50)
          
    ###
        if (!pause_game) 
          timer();
        else
            center_text("PAUSE", RES_Y/2);
            sprintf(temp, "score: %d", 
                    coins+lifes*100+progress*100);
            center_text(temp, RES_Y/2+LETTER_HEIGHT);
            show_screen();
    ###


