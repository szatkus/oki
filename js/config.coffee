app.config =
  load: ->
    getConfig = (name) -> localStorage.getItem("oki/#{name}")
    @isFullscreen = getConfig('fullscreen') || false
    @left = getConfig('left') || 39
    @up = getConfig('up') || 38
    @right = getConfig('right') || 37
    @down = getConfig('down') || 40
    @buttonA = getConfig('A') || 90
    @buttonB = getConfig('B') || 88
    @mapset = getConfig('mapset') || 'default'
  
  save: ->
    setConfig = (name, value) -> localStorage.setItem("oki/#{name}", value)
    setConfig('fullscreen', @isFullscreen)
    getConfig('left', @left)
    getConfig('up', @up)
    getConfig('right', @right)
    getConfig('down', @down)
    getConfig('A', @buttonA)
    getConfig('B', @buttonB)
    getConfig('mapset', @mapset)
