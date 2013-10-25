#define OBJ_ENEMY 1
#define OBJ_COIN 2
#define OBJ_LIFE 3
#define OBJ_STRENGTH 4
#define OBJ_DEATH 5
#define OBJ_EXIT 6
#define OBJ_JUMP 7
#define OBJ_SPEED 8
#define OBJ_WATER 9
#define OBJ_WATER_STOP 10
#define OBJ_WATER_UP 11
#define OBJ_RUN 12
#define OBJ_UP 13
#define OBJ_TEXT 14
#define OBJ_KEY 15
#define OBJ_JUMP_TIME 16
#define OBJ_CHECKPOINT 17
#define OBJ_DARKER 18
#define OBJ_LIGHTER 19
#define OBJ_CLONE 20
#define OBJ_HP 21
#define OBJ_HEALTH 22
#define OBJ_BOMB 23
#define OBJ_TRAP 24
#define OBJ_SHOOT 25
#define OBJ_ONE_DEATH 26
#define OBJ_FALL 27
#define OBJ_GO 28

#define STATE_STAY 0
#define STATE_WALK 1
#define STATE_FALL 2
#define STATE_JUMP 3

#define DIR_LEFT 0
#define DIR_ZERO 1
#define DIR_RIGHT 2

class app.GameObject
    isVisible: true
    state: 'stay'
    direction: 0
    ai: null
    type: null
    mass: 0
    strength: 0
    run: null
    fall: null
    blink: null
    damage: 0
    life: 0
    ghost: null
    shoot: 0
    speed: 0
    jumpPower: 0
    jumpFrame: 0
    jumpDuration: 0
    image: null
    position: {}
    animation: {}
    oldAnimation: {}
    constructor: (properties) ->
      if properties?
        for i in properties
          this[i] = properties[i]
