LETTER_WIDTH = 5
LETTER_HEIGHT = 7
MONSTERS_COUNT = 14

app.renderer =  
  
  canvas: null
  
  context: null
  
  resolution:
    x: 160
    y: 120
  
  images: {}
  
  wrapCanvas: (@canvas) ->
    @context = canvas.getContext('2d')
    canvas.width = @resolution.x
    canvas.height = @resolution.y
  
  drawTile: (image, context, tile, size, x, y, width, height) ->
    image = @images[image] unless image instanceof Image
    context ?= @context
    sx = ((tile - (Math.floor(tile / size)) * size)) * width
    sy = Math.floor(tile / size) * height
    context.drawImage(image, sx, sy, width, height, x, y, width, height)
  
  fillScreen: (color) ->
    @context.fillStyle = color
    @context.fillRect(0, 0, @canvas.width, @canvas.height)

  loadImage: (filename, callback) ->
    image = new Image
    image.src = filename
    image.onload = ->
      callback(image)
    return image
  
  loadImages: (callback) ->
    imagesNames = [
      'font'
      'events'
      'tileset'
      'killed'
      'text'
      'man'
      'oki'
      'oke'
      'torch'
      'rock'
      'glass'
      'comp'
      'logo'
      'exit'
    ]
    for i in [1..MONSTERS_COUNT]
      imagesNames.push("monster#{i}")
    remains = 0
    @images = {}
    for i of imagesNames
      name = imagesNames[i]
      remains++
      do (name) =>
        @loadImage "gfx/#{name}.png", (image) => 
          @images[name] = image
          remains--
          callback() if remains is 0



  drawText: (text, x, y) ->
      for i of text
          @drawTile('font', @context, text.charCodeAt(i), 16, x + i * LETTER_WIDTH, y, LETTER_WIDTH, LETTER_HEIGHT);

  drawParagraph: (text, x, y) ->
    pos = 0;
    length = 0;
    line = 0;
    for i of text
        if x + length * LETTER_WIDTH + 10 > RES_X
            length = 0;
            line++;
        @drawTile(font, screen, text.charCodeAt(i), 16, x + length * LETTER_WIDTH, y + line * LETTER_HEIGHT,
          LETTER_WIDTH, LETTER_HEIGHT);
        length++;

  drawCenteredText: (text, y) ->
    x = (@resolution.x - (text.length * LETTER_WIDTH)) / 2;
    @drawText(text, x, y);
