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
  load: (callback) ->
    request = new XMLHttpRequest
    request.open('get', "maps/#name/index");
    request.responseType = 'arraybuffer'
    request.onreadystatechange = =>
      data = new Uint8Array(request.response)
      objects = []
      pos = 3
      @width = data[pos++] - 1
      @height = data[pos++] - 1
      @gameBuffer = document.createElement('canvas')
      @gameBuffer.width = (@width + 1) * app.BLOCK_WIDTH
      @gameBuffer.height = (@width + 1) * app.BLOCK_HEIGHT
      @staticsBuffer = document.createElement('canvas')
      @staticsBuffer.width = (@width + 1) * app.BLOCK_WIDTH
      @staticsBuffer.height = (@width + 1) * app.BLOCK_HEIGHT
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
            if block.tile >= 192
                block.tile -= 192;
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
                    width: BLOCK_WIDTH
                    height: BLOCK_HEIGHT
                switch (block.tile)
                    when 0
                        newObject.speed = 1;
                        newObject.AI = 1;
                        newObject.mass = 5;
                        newObject.img = monster[0];
                    when 1
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_COIN;
                        totalcoins++;
                    when 2
                        newObject.dir = DIR_ZERO;   
                        newObject.type = OBJ_LIFE;
                        newObject.anim.x = BLOCK_WIDTH;
                        totallifes++;
                    when 3
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_STRENGTH;
                        newObject.anim.x = 3*BLOCK_WIDTH;
                    when 4
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_DEATH;
                        newObject.anim.y = BLOCK_HEIGHT;
                    when 5
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_JUMP;
                        newObject.anim.x = BLOCK_WIDTH;
                        newObject.anim.y = BLOCK_HEIGHT;
                    when 6
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_SPEED;
                        newObject.anim.x = 2*BLOCK_WIDTH;
                        newObject.anim.y = BLOCK_HEIGHT;
                    when 7
                        newObject.speed = 2;
                        newObject.AI = 1;
                        newObject.type = OBJ_ENEMY;
                        newObject.mass = 7;
                        newObject.img = monster[1];
                    when 8
                      ###
                        newObject.dir = DIR_ZERO;
                        newObject.speed = 1;
                        newObject.type = OBJ_WATER;
                        newObject.img = 
                        SDL_CreateRGBSurface(SDL_HWSURFACE, game.w, game.h,
                                             24, 0, 0, 0, 0);
                        for (i=0;i<=level.width;i++)
                        
                            cut_image(tileset, newObject.img, 5, 8, 
                                      i*BLOCK_WIDTH, 0, BLOCK_WIDTH, 
                                      BLOCK_HEIGHT);
                            for (t=1;t<=level.height;t++)
                            
                            cut_image(tileset, newObject.img, 6, 8, 
                                      i*BLOCK_WIDTH, t*BLOCK_HEIGHT, BLOCK_WIDTH, 
                                      BLOCK_HEIGHT);
                            
                        
                        newObject.anim.w = game.w;
                        newObject.anim.h = BLOCK_HEIGHT;
                        newObject.pos.x = 0;
                        newObject.pos.w = game.w;
                      ###
                    when 9
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_WATER_STOP;
                        newObject.img = NULL;
                    when 10
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_WATER_UP;
                        newObject.img = NULL;
                    when 11
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_RUN;
                        newObject.anim.x = 3*BLOCK_WIDTH;
                        newObject.anim.y = BLOCK_HEIGHT;
                    when 12
                        newObject.dir = DIR_ZERO;
                        newObject.speed = 2*BLOCK_HEIGHT;
                        newObject.type = OBJ_UP;
                        newObject.anim.y = 2*BLOCK_HEIGHT;
                    when 13
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_DEATH;
                        newObject.anim.x = BLOCK_HEIGHT;
                        newObject.anim.y = 2*BLOCK_HEIGHT;
                    when 14
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_DEATH;
                        newObject.anim.x = 2*BLOCK_HEIGHT;
                        newObject.anim.y = 2*BLOCK_HEIGHT;
                    when 15
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_DEATH;
                        newObject.anim.x = 3*BLOCK_HEIGHT;
                        newObject.anim.y = 2*BLOCK_HEIGHT;
                    when 16
                        newObject.speed = 3;
                        newObject.AI = 2;
                        newObject.mass = 9;
                        newObject.strength = 1;
                        newObject.img = monster[2];
                        newObject.anim.w = 2*BLOCK_WIDTH;
                        newObject.anim.h = 2*BLOCK_HEIGHT;
                        newObject.pos.w = 2*BLOCK_WIDTH;
                        newObject.pos.h = 2*BLOCK_HEIGHT;
                    when 17
                        newObject.speed = 0;
                        newObject.strength = last_text;
                        newObject.type = OBJ_TEXT;
                        newObject.img = NULL;
                        fgets(text[last_text], fgetc(file), file);
                        last_text++;
                    when 18
                        newObject.speed = 6;
                        newObject.AI = 2;
                        newObject.mass = 3;
                        newObject.strength = 2;
                        newObject.jump.power = 5;
                        newObject.jump.time = 6;
                        newObject.img = monster[3];
                    when 19
                        newObject.speed = 11;
                        newObject.AI = 2;
                        newObject.mass = 5;
                        newObject.strength = 3;
                        newObject.jump.power = 7;
                        newObject.jump.time = 8;
                        newObject.img = monster[4];
                    when 21
                        newObject.dir = DIR_ZERO;
                        newObject.AI = last_key;
                        newObject.type = OBJ_KEY;
                        newObject.img = events;
                        newObject.anim.x = 6*BLOCK_HEIGHT;
                        newObject.anim.y = 2*BLOCK_HEIGHT;
                        last_key++;
                    when 22
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_JUMP_TIME;
                        newObject.anim.x = 7*BLOCK_WIDTH;
                        newObject.anim.y = 2*BLOCK_HEIGHT;
                    when 23
                        newObject.speed = 3;
                        newObject.AI = 2;
                        newObject.mass = 3;
                        newObject.strength = 1;
                        newObject.HP = 1;
                        newObject.img = monster[5];
                        newObject.run = 1;
                    when 24
                        newObject.dir = DIR_ZERO;
                        newObject.speed = 5*BLOCK_HEIGHT;
                        newObject.type = OBJ_UP;
                        newObject.anim.x = BLOCK_WIDTH;
                        newObject.anim.y = 3*BLOCK_HEIGHT;
                    when 25
                        newObject.speed = 2;
                        newObject.AI = 1;
                        newObject.mass = 5;
                        newObject.strength = last_text;
                        newObject.type = OBJ_TEXT;
                        newObject.img = man;
                        fgets(text[last_text], fgetc(file), file);
                        last_text++;
                    when 26
                        oke = newObject;
                        oke.mass = 6;
                        oke.AI = 2;
                        oke.type = 0;
                        oke.img = oke_img;
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
                        newObject.img = monster[6];
                    when 28
                        newObject.dir = DIR_ZERO;
                        newObject.speed = 100*BLOCK_HEIGHT;
                        newObject.type = OBJ_UP;
                        newObject.anim.x = 2*BLOCK_WIDTH;
                        newObject.anim.y = 3*BLOCK_HEIGHT;
                    when 29
                        newObject.type = OBJ_DEATH;
                        newObject.speed = 2;
                        newObject.AI = 1;
                        newObject.mass = 9;
                        newObject.img = monster[7];
                    when 30
                        newObject.type = OBJ_DARKER;
                        newObject.img = NULL;
                    when 31
                        newObject.type = OBJ_LIGHTER;
                        newObject.img = NULL;
                    when 32
                        newObject.speed = 3;
                        newObject.AI = 2;
                        newObject.mass = 5;
                        newObject.strength = 3;
                        newObject.img = monster[8];
                    when 33
                        newObject.speed = 2;
                        newObject.AI = 2;
                        newObject.mass = 1;
                        newObject.strength = 5;
                        newObject.img = monster[9];
                        newObject.anim.w = 4*BLOCK_WIDTH;
                        newObject.anim.h = 4*BLOCK_HEIGHT;
                        newObject.pos.w = 4*BLOCK_WIDTH;
                        newObject.pos.h = 4*BLOCK_HEIGHT;
                    when 34
                        newObject.dir = DIR_ZERO;
                        newObject.type = 0;
                        newObject.img = NULL;
                        anim[last_anim].vis = 1;
                        anim[last_anim].frames = 3;
                        anim[last_anim].loop = 0;
                        anim[last_anim].delay = 2;
                        anim[last_anim].img = torch;
                        anim[last_anim].pos = newObject.pos;
                        anim[last_anim].anim.x = 0;
                        anim[last_anim].anim.y = 0;
                        anim[last_anim].anim.w = BLOCK_WIDTH;
                        anim[last_anim].anim.h = BLOCK_HEIGHT;
                        last_anim++;
                    when 35
                        newObject.speed = 2;
                        newObject.AI = 2;
                        newObject.mass = 5;
                        newObject.type = OBJ_CLONE;
                        newObject.img = man;
                    when 36
                        newObject.speed = 3;
                        newObject.jump.time = 5;
                        newObject.jump.power = 5;
                        newObject.AI = 2;
                        newObject.mass = 5;
                        newObject.type = OBJ_CLONE;
                        newObject.img = monster[10];
                    when 37
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_HP;
                        newObject.anim.x = 5*BLOCK_WIDTH;
                        newObject.anim.y = 3*BLOCK_HEIGHT;
                    when 38
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_HEALTH;
                        newObject.anim.x = 6*BLOCK_WIDTH;
                        newObject.anim.y = 3*BLOCK_HEIGHT;
                    when 39
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_DEATH;
                        newObject.img = rock;
                        newObject.mass = 15;
                        newObject.anim.w = 3*BLOCK_WIDTH;
                        newObject.anim.h = 3*BLOCK_HEIGHT;
                        newObject.pos.w = 3*BLOCK_WIDTH;
                        newObject.pos.h = 3*BLOCK_HEIGHT;
                    when 40
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_BOMB;
                        newObject.strength = 3;
                        newObject.anim.x = 7*BLOCK_WIDTH;
                        newObject.anim.y = 3*BLOCK_HEIGHT;
                    when 41
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_TRAP;
                        newObject.anim.x = 0;
                        newObject.anim.y = 4*BLOCK_HEIGHT;
                        newObject.anim.h = 2*BLOCK_HEIGHT;
                        newObject.pos.y -= BLOCK_HEIGHT;
                        newObject.pos.h = 2*BLOCK_HEIGHT;
                    when 42
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_SHOOT;
                        newObject.anim.x = BLOCK_WIDTH;
                        newObject.anim.y = 4*BLOCK_HEIGHT;
                    when 43
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_FALL;
                        newObject.strength = 5;
                        newObject.anim.x = 2*BLOCK_WIDTH;
                        newObject.anim.y = 4*BLOCK_HEIGHT;
                    when 44
                        newObject.speed = 1;
                        newObject.AI = 1;
                        newObject.mass = 0;
                        newObject.img = monster[12];
                        newObject.strength = 99;
                    when 45
                        newObject.mass = 0;
                        newObject.dir = DIR_RIGHT;
                        newObject.img = monster[12];
                        newObject.strength = 99;
                        newObject.ghost = 1;
                    when 46
                        newObject.mass = 0;
                        newObject.speed = 1;
                        newObject.AI = 1;
                        newObject.img = monster[12];
                        newObject.strength = 99;
                        newObject.ghost = 1;
                    when 47
                        newObject.speed = 1;
                        newObject.AI = 2;
                        newObject.mass = 0;
                        newObject.img = monster[12];
                        newObject.strength = 99;
                    when 48
                        newObject.speed = 3;
                        newObject.AI = 1;
                        newObject.mass = 3;
                        newObject.strength = 1;
                        newObject.HP = 1;
                        newObject.img = monster[5];
                    when 49
                        newObject.dir = DIR_ZERO;
                        newObject.type = 0;
                        newObject.img = NULL;
                        anim[last_anim].vis = 1;
                        anim[last_anim].frames = 5;
                        anim[last_anim].loop = 0;
                        anim[last_anim].delay = 2;
                        anim[last_anim].img = glass;
                        anim[last_anim].pos = newObject.pos;
                        anim[last_anim].anim.x = 0;
                        anim[last_anim].anim.y = 0;
                        anim[last_anim].anim.w = BLOCK_WIDTH*2;
                        anim[last_anim].anim.h = BLOCK_HEIGHT*4;
                        last_anim++;
                    when 50
                        newObject.dir = DIR_ZERO;
                        newObject.type = 0;
                        newObject.img = NULL;
                        anim[last_anim].vis = 1;
                        anim[last_anim].frames = 5;
                        anim[last_anim].loop = 0;
                        anim[last_anim].delay = 2;
                        anim[last_anim].img = computer;
                        anim[last_anim].pos = newObject.pos;
                        anim[last_anim].anim.x = 0;
                        anim[last_anim].anim.y = 0;
                        anim[last_anim].anim.w = BLOCK_WIDTH;
                        anim[last_anim].anim.h = BLOCK_HEIGHT;
                        last_anim++;
                    when 51
                        newObject.speed = 2;
                        newObject.AI = 1;
                        newObject.mass = 1;
                        newObject.strength = 1;
                        newObject.jump.power = 5;
                        newObject.jump.time = 3;
                        newObject.img = monster[13];
                    when 52
                        newObject.speed = 2;
                        newObject.AI = 2;
                        newObject.mass = 1;
                        newObject.strength = 1;
                        newObject.jump.power = 5;
                        newObject.jump.time = 3;
                        newObject.img = monster[13];
                    when 53
                        newObject.speed = 2;
                        newObject.AI = 1;
                        newObject.mass = 9;
                        newObject.img = monster[14];
                        newObject.anim.w = 2*BLOCK_WIDTH;
                        newObject.anim.h = 2*BLOCK_HEIGHT;
                        newObject.pos.w = 2*BLOCK_WIDTH;
                        newObject.pos.h = 2*BLOCK_HEIGHT;
                        newObject.type = OBJ_BOMB;
                        newObject.strength = 6;
                    when 54
                        newObject.speed = 2;
                        newObject.AI = 2;
                        newObject.mass = 9;
                        newObject.img = monster[14];
                        newObject.anim.w = 2*BLOCK_WIDTH;
                        newObject.anim.h = 2*BLOCK_HEIGHT;
                        newObject.pos.w = 2*BLOCK_WIDTH;
                        newObject.pos.h = 2*BLOCK_HEIGHT;
                        newObject.type = OBJ_BOMB;
                        newObject.strength = 6;
                    when 55
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_BOMB;
                        newObject.strength = 9;
                        newObject.anim.x = 7*BLOCK_WIDTH;
                        newObject.anim.y = 3*BLOCK_HEIGHT;
                    when 56
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_BOMB;
                        newObject.strength = 27;
                        newObject.anim.x = 7*BLOCK_WIDTH;
                        newObject.anim.y = 3*BLOCK_HEIGHT;
                    when 57
                        newObject.dir = DIR_ZERO;
                        newObject.speed = -2*BLOCK_HEIGHT;
                        newObject.type = OBJ_UP;
                        newObject.anim.y = 4*BLOCK_HEIGHT;
                        newObject.anim.x = 3*BLOCK_WIDTH;
                    when 58
                        newObject.dir = DIR_ZERO;
                        newObject.speed = -2*BLOCK_WIDTH;
                        newObject.type = OBJ_GO;
                        newObject.anim.y = 4*BLOCK_HEIGHT;
                        newObject.anim.x = 4*BLOCK_WIDTH;
                    when 59
                        newObject.dir = DIR_ZERO;
                        newObject.speed = 2*BLOCK_WIDTH;
                        newObject.type = OBJ_GO;
                        newObject.anim.y = 4*BLOCK_HEIGHT;
                        newObject.anim.x = 5*BLOCK_WIDTH;
                    when 60
                        newObject.speed = 3;
                        newObject.AI = 2;
                        newObject.mass = 3;
                        newObject.strength = 0;
                        newObject.HP = 1;
                        newObject.img = monster[11];
                        newObject.run = 1;
                        newObject.anim.h = BLOCK_HEIGHT+5;
                    when 61
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_CHECKPOINT;
                        newObject.img = events;
                        newObject.anim.y = 3*BLOCK_HEIGHT;
                    when 62
                        newObject.dir = DIR_ZERO;
                        newObject.type = OBJ_EXIT;
                        newObject.img = NULL;
                        anim[last_anim].vis = 1;
                        anim[last_anim].frames = 4;
                        anim[last_anim].loop = 0;
                        anim[last_anim].delay = 0;
                        anim[last_anim].img = IMG_Load(getdata("gfx/exit.png"));
                        anim[last_anim].pos = newObject.pos;
                        anim[last_anim].anim.x = 0;
                        anim[last_anim].anim.y = 0;
                        anim[last_anim].anim.w = BLOCK_WIDTH;
                        anim[last_anim].anim.h = BLOCK_HEIGHT;
                        last_anim++;
                    when 63
                        newObject.vis = 0;
                        last_obj--;
                        oki.pos.x = x*BLOCK_WIDTH;
                        oki.pos.y = y*BLOCK_HEIGHT;
                        start_pos = oki.pos;
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
                last_obj++;
            
            while (block.tile >= 64)
            
                block.type++;
                block.tile-=64;
            
      if (oki.shoot) 
        last_obj++;
        oki.shoot = last_obj;
      callback()
    


  draw: ->
    for y in [0..@height]
      for x in [0..@width]
        app.renderer.drawTile(tileset, @staticsBuffer, @block[x][y].tile, 8, x * app.BLOCK_WIDTH, 
                      y * app.BLOCK_HEIGHT, app.BLOCK_WIDTH, app.BLOCK_HEIGHT);
  
  start: ->
    @load =>
      isPlaying = true
      while isPlaying
        window.onkeydown = (event) => 
                    if (event.key.keysym.sym == left) 
                        oki.dir = DIR_LEFT;
                        start = 1;
                    if (event.key.keysym.sym == right)
                        oki.dir = DIR_RIGHT;
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
                break;
        window.onkeyup = (event) => 
                    if (oki.dir == DIR_LEFT && event.key.keysym.sym == left) 
                        oki.dir = DIR_ZERO;
                    if (oki.dir == DIR_RIGHT && event.key.keysym.sym == right) 
                        oki.dir = DIR_ZERO;
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
                            obj[oki.shoot].dir = DIR_ZERO;
                            obj[oki.shoot].pos = oki.pos;
                            obj[oki.shoot].anim = oki.anim;
                            obj[oki.shoot].anim.x = 7*BLOCK_WIDTH;
                            obj[oki.shoot].anim.y = 3*BLOCK_HEIGHT;
                            obj[oki.shoot].type = OBJ_ONE_DEATH;
                            obj[oki.shoot].img = events;
                    if (event.key.keysym.sym == SDLK_p) 
                      pause_game = !pause_game;
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


