app.mainLoop = ->
    context = app.renderer.context
    gameContext = @gameBuffer.getContext('2d')
    resolution = app.renderer.resolution
    gameWidth = @width * app.BLOCK_WIDTH
    gameHeight = @height * app.BLOCK_HEIGHT
    app.renderer.fillScreen('#000')
    gameContext.clearRect(0, 0, gameWidth, gameHeight);
    ###
    for (i=0;i<=255;i++)
    {
        if (obj.vis)
        {
            if (obj.img != events)
            {
              if (obj.dir == DIR_LEFT) obj.anim.y = obj.h;
              if (obj.dir == DIR_RIGHT) obj.anim.y = 0;
            }
            if (obj.ghost > 0) obj.ghost++;
            if (obj.ghost > 80) obj.ghost = 1;
            switch (obj.type)
            {
                case OBJ_WATER: 
                    obj.y-=obj.speed;
                    obj.h+=obj.speed;
                    obj.anim.h+=obj.speed;
                break;
                case OBJ_TRAP: 
                    obj.strength++;
                    if (obj.strength >= 11 && obj.strength <= 15) 
                        obj.y += 2;
                    if (obj.strength >= 16 && obj.strength <= 20) 
                        obj.y -= 2;
                    if (obj.strength == 20) obj.strength = 0;
                break;
            }
            move(i);
        }
    }
    ###
    @cameraX = @oki.x - resolution.x / 2;
    if (@cameraX < 0)
      @cameraX = 0;
    if (@cameraX > gameWidth - resolution.x)
      @cameraX = gameWidth - resolution.x
    @cameraY = @oki.y - resolution.y / 2;
    #@cameray+=camera_modifier;
    if (@cameraY < 0)
      @cameraY = 0;
    if (@cameraY > gameHeight - resolution.y)
      @cameraY = gameHeight - resolution.y
    
    context.drawImage(@staticsBuffer, @cameraX, @cameraY, resolution.x, resolution.y, 0, 0, resolution.x, resolution.y)
    for anim in @animations
        if (anim.isVisible)
            if (anim.wait == anim.delay)
                anim.frameX += anim.frameWidth
                if (anim.frameX == anim.frames * anim.frameWidth) 
                    anim.frameX = 0;
                if (anim.loops) 
                  anim.isVisible = false
                if (anim.loops > 0) 
                  anim.loops--;
                anim.wait = 0;
            else
              anim.wait++;
            gameContext.drawImage(anim.image, anim.frameX, anim.frameY, anim.frameWidth, anim.frameHeight, anim.x, anim.y, anim.frameWidth, anim.frameHeight)

    for obj in @objects
        if obj.isVisible && obj.ghost < 40
            #touch_oki(i);
            obj.blink-- if obj.blink > 0
              
            if obj.blink - ((obj.blink/2)*2)
              obj.animation.x += 100;
            else 
                obj.animation.x-=100 if obj.animation.x >= 100
            #if (obj.speed >= 10) SDL_BlitSurface(obj.img, &obj.old_anim, 
            #                                        game, &obj.old_pos);
            #if (die && i == 255) oki->anim.x = 40;
            obj.width = obj.animation.width
            obj.height = obj.animation.height
            if (obj.x > @cameraX-obj.width &&
                obj.x < @cameraX+resolution.x+obj.width &&
                obj.y > @cameraY-obj.height &&
                obj.y < @cameraY+resolution.y+obj.height &&
                obj.image?)
              gameContext.drawImage(obj.image, obj.animation.x, obj.animation.y, obj.width, obj.height, obj.x, obj.y, obj.width, obj.height)

    context.drawImage(@gameBuffer, @cameraX, @cameraY, resolution.x, resolution.y, 0, 0, resolution.x, resolution.y)
    ###
    if (mask) 
    {
        SDL_FillRect(screen, NULL, WHITE);
        mask--;
    }
    rect2.y = 0;
    if (show_time > 0)
    {
        rect.x = 0;
        if (oki->pos.y-@cameray >= RES_Y/2) 
        {
            rect.y = 0;
            rect2.y = RES_Y-BLOCK_HEIGHT;
        } else rect.y = RES_Y-text_bg->h;
        SDL_BlitSurface(text_bg, NULL, screen, &rect);
        draw_text_br(text[show_text], 5, rect.y+5);
        show_time--;
    }
    rect.x = 0;
    rect.y = 0;
    rect.w = BLOCK_WIDTH;
    rect.h = BLOCK_HEIGHT;
    rect2.x = 0;
    rect2.w = rect.w;
    rect2.h = rect.h;
    SDL_BlitSurface(events, &rect, screen, &rect2);
    sprintf(temp, "%d", coins);
    draw_text(temp, 11, rect2.y+2);
    rect.x = 10;
    rect.y = 0;
    rect.w = BLOCK_WIDTH;
    rect.h = BLOCK_HEIGHT;
    rect2.x = RES_X-22;
    rect2.w = rect.w;
    rect2.h = rect.h;
    SDL_BlitSurface(events, &rect, screen, &rect2);
    sprintf(temp, "%d", lifes);
    draw_text(temp, RES_X-11, rect2.y+2);
    if (enable_fps)
    {
        sprintf(temp, "%d", fps);
        draw_text(temp, RES_X-11, RES_Y-11);
        temp_fps++;
    }
    show_screen();
    SDL_Delay(limit);
    if (die) 
    {
        die = 0;
        lifes--;
        SDL_Delay(1000);
        oki->pos = start_pos;
        oki->anim.x = 0;
        oki->anim.y = 0;
        for (i=0;i<=255;i++)
        {
            switch (obj.type)
            {
                case OBJ_WATER:
                    obj.y = game->h-BLOCK_HEIGHT;
                    obj.h = BLOCK_HEIGHT;
                    obj.anim.h = BLOCK_HEIGHT;
                    obj.vis = 1;
                    obj.speed = 1;
                break;
                case OBJ_WATER_STOP:
                case OBJ_WATER_UP:
                    obj.vis = 1;
                break;
            }
        }
        oki->blink = 30;
        oki->damage = 0;
        if (lifes < 0) 
        {
            select_level = 0;
            play = 0;
            rect.x = 0;
            rect.y = 0;
            rect.w = RES_X;
            rect.h = RES_Y;
            SDL_FillRect(screen, &rect, WHITE);
            center_text("game over", RES_Y/2);
            sprintf(temp, "score: %d", coins+progress*100);
            center_text(temp, RES_Y/2+LETTER_HEIGHT);
            show_screen();
            event.type = 0;
            while (event.type != SDL_KEYDOWN)
              SDL_PollEvent(&event);
    ###
