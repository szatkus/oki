app.start = (canvas) ->
    #mapset = 0;
    @config.load()
    @renderer.wrapCanvas(canvas)
    #ifdef SOUND
    #Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    #endif
    #ifndef OPENGL
    #screen2 = SDL_SetVideoMode(RES_X*SCALE, RES_Y*SCALE, 8, SDL_SWSURFACE | 
    #SDL_FULLSCREEN*fs);
    #else
    ###
    strcpy(text[0], "game saved!");
    oki = &obj[255];
    oki->img = IMG_Load(getdata("gfx/oki.png"));
    oki->pos.w = BLOCK_WIDTH;
    oki->pos.h = BLOCK_HEIGHT;
    oki->anim.x = 0;
    oki->anim.y = 0;
    oki->anim.w = oki->pos.w;
    oki->anim.h = oki->pos.h;
    jump = Mix_LoadWAV(getdata("snd/jump.wav"));
    bonus = Mix_LoadWAV(getdata("snd/bonus.wav"));
    death = Mix_LoadWAV(getdata("snd/death.wav"));
    cursor = Mix_LoadWAV(getdata("snd/cursor.wav"));
    click = Mix_LoadWAV(getdata("snd/click.wav"));
    slap = Mix_LoadWAV(getdata("snd/hit.wav"));
    boom = Mix_LoadWAV(getdata("snd/boom.wav"));
    ###
    @renderer.loadImages =>
      @maps.loadMaplist =>
        #@game.camera.x = 0
        #@game.camera.y = 0
        #@game.camera.width = @renderer.resolution.x
        #@game.camera.height = @renderer.resolution.y
        #if (enable_fps) SDL_CreateThread(&count_fps, NULL);
        @game.start('default')
