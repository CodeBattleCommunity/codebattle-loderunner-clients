var Elements = {
  /// a void
  NONE: ' ',

  /// walls
  BRICK: '#',
  PIT_FILL_1: '1',
  PIT_FILL_2: '2',
  PIT_FILL_3: '3',
  PIT_FILL_4: '4',
  UNDESTROYABLE_WALL: '☼',

  DRILL_PIT: '*',

  // this is enemy
  ENEMY_LADDER: 'Q',
  ENEMY_LEFT: '«',
  ENEMY_RIGHT: '»',
  ENEMY_PIPE_LEFT: '<',
  ENEMY_PIPE_RIGHT: '>',
  ENEMY_PIT: 'X',

  /// gold ;)
  YELLOW_GOLD: '$',
  GREEN_GOLD: '&',
  RED_GOLD: '@',

  /// this is you
  HERO_DIE: 'Ѡ',
  HERO_DRILL_LEFT: 'Я',
  HERO_DRILL_RIGHT: 'R',
  HERO_LADDER: 'Y',
  HERO_LEFT: '◄',
  HERO_RIGHT: '►',
  HERO_FALL_LEFT: ']',
  HERO_FALL_RIGHT: '[',
  HERO_PIPE_LEFT: '{',
  HERO_PIPE_RIGHT: '}',

  HERO_SHADOW_DRILL_LEFT: '⊰',
  HERO_SHADOW_DRILL_RIGHT: '⊱',
  HERO_SHADOW_LADDER: '⍬',
  HERO_SHADOW_LEFT: '⊲',
  HERO_SHADOW_RIGHT: '⊳',
  HERO_SHADOW_FALL_LEFT: '⊅',
  HERO_SHADOW_FALL_RIGHT: '⊄',
  HERO_SHADOW_PIPE_LEFT: '⋜',
  HERO_SHADOW_PIPE_RIGHT: '⋝',

  /// this is other players
  OTHER_HERO_DIE: 'Z',
  OTHER_HERO_LEFT: ')',
  OTHER_HERO_RIGHT: ' : ',
  OTHER_HERO_LADDER: 'U',
  OTHER_HERO_PIPE_LEFT: 'Э',
  OTHER_HERO_PIPE_RIGHT: 'Є',

  OTHER_HERO_SHADOW_DIE: '⋈',
  OTHER_HERO_SHADOW_LEFT: '⋊',
  OTHER_HERO_SHADOW_RIGHT: '⋉',
  OTHER_HERO_SHADOW_LADDER: '⋕',
  OTHER_HERO_SHADOW_PIPE_LEFT: '⊣',
  OTHER_HERO_SHADOW_PIPE_RIGHT: '⊢',

  /// ladder and pipe - you can walk
  LADDER: 'H',
  PIPE: '~',
  PORTAL: '⊛',
  THE_SHADOW_PILL: 'S'
};

class GameClient {
  constructor(server, user, code) {
    this.path = "ws://" + server + "/codenjoy-contest/ws?user=" + user
        + "&code=" + code
  }

  run(callback) {
    var self = this;
    this.socket = new WebSocket(this.path);
    this.socket.onopen = this.onOpen;
    this.socket.onerror = this.onError;
    this.socket.onclose = this.onClose;
    this.socket.onmessage = function (event) {
      var board = new Board(event.data);
      var action = callback(board);
      self.send(action)
    }
  }

  get size() {
    return this.socket.size;
  }

  get map() {
    return this.socket.map;
  }

  get playerX() {
    return this.socket.playerX;
  }

  get playerY() {
    return this.socket.playerY;
  }

  set textArea(text) {
    this.text = text
  }

  onOpen() {
    text.value += "Connection established\n";
  }

  onClose(event) {
    if (event.wasClean) {
      text.value += "### disconnected ###\n"
    } else {
      text.value += "### accidentally disconnected ###\n";
      text.value += " - Err code: " + event.code + ", Reason: " + event.reason
          + "\n";
    }
  }

  onError(error) {
    text.value += "### error ###\n" + error.message + "\n";
  }

  send(msg) {
    text.value += "Sending: " + msg + '\n'
    this.socket.send(msg)
  }
}

class Board {
  constructor(board) {
    this.board = board.match(/^board=(.*)$/)[1];
    this.size = this.boardSize();
    this.xyl = new LengthToXY(this.size);
  }

  contains(a, obj) {
    var i = a.length;
    while (i--) {
      if (a[i].equals(obj)) {
        return true;
      }
    }
    return false;
  };

  sort(all) {
    return all.sort(function (pt1, pt2) {
      return pt1.y * 1000 + pt1.x - pt2.y * 1000 + pt2.x;
    });
  }

  removeDuplicates(all) {
    var result = [];
    for (var index in all) {
      var point = all[index];
      if (!this.contains(result, point)) {
        result.push(point);
      }
    }
    return this.sort(result);
  };

  boardSize() {
    return Math.sqrt(this.board.length);
  };

  printArray(array) {
    var result = [];
    for (var index in array) {
      var element = array[index];
      result.push(element.toString());
    }
    return "[" + result + "]";
  };

  getMyPosition() {
    var result = [];
    result = result.concat(this.findAll(Elements.HERO_DIE));
    result = result.concat(this.findAll(Elements.HERO_DRILL_LEFT));
    result = result.concat(this.findAll(Elements.HERO_DRILL_RIGHT));
    result = result.concat(this.findAll(Elements.HERO_FALL_RIGHT));
    result = result.concat(this.findAll(Elements.HERO_FALL_LEFT));
    result = result.concat(this.findAll(Elements.HERO_LADDER));
    result = result.concat(this.findAll(Elements.HERO_LEFT));
    result = result.concat(this.findAll(Elements.HERO_RIGHT));
    result = result.concat(this.findAll(Elements.HERO_PIPE_LEFT));
    result = result.concat(this.findAll(Elements.HERO_PIPE_RIGHT));
    result = result.concat(this.findAll(Elements.HERO_SHADOW_DRILL_LEFT));
    result = result.concat(this.findAll(Elements.HERO_SHADOW_DRILL_RIGHT));
    result = result.concat(this.findAll(Elements.HERO_SHADOW_LADDER));
    result = result.concat(this.findAll(Elements.HERO_SHADOW_LEFT));
    result = result.concat(this.findAll(Elements.HERO_SHADOW_RIGHT));
    result = result.concat(this.findAll(Elements.HERO_SHADOW_FALL_LEFT));
    result = result.concat(this.findAll(Elements.HERO_SHADOW_FALL_RIGHT));
    result = result.concat(this.findAll(Elements.HERO_SHADOW_PIPE_LEFT));
    result = result.concat(this.findAll(Elements.HERO_SHADOW_PIPE_RIGHT));
    return result[0];
  };

  isGameOver() {
    return this.board.indexOf(Elements.HERO_DIE) !== -1;
  };

  hasElementAt(x, y, element) {
    if (pt(x, y).isOutOf(this.size)) {
      return false;
    }
    return this.getAt(x, y) === element;
  };

  getEnemyPositions() {
    var result = [];
    result = result.concat(this.findAll(Elements.ENEMY_LADDER));
    result = result.concat(this.findAll(Elements.ENEMY_LEFT));
    result = result.concat(this.findAll(Elements.ENEMY_PIPE_LEFT));
    result = result.concat(this.findAll(Elements.ENEMY_PIPE_RIGHT));
    result = result.concat(this.findAll(Elements.ENEMY_RIGHT));
    result = result.concat(this.findAll(Elements.ENEMY_PIT));
    return result;
  };

  getOtherHeroPositions() {
    var result = [];
    result = result.concat(this.findAll(Elements.OTHER_HERO_LEFT));
    result = result.concat(this.findAll(Elements.OTHER_HERO_RIGHT));
    result = result.concat(this.findAll(Elements.OTHER_HERO_LADDER));
    result = result.concat(this.findAll(Elements.OTHER_HERO_PIPE_LEFT));
    result = result.concat(this.findAll(Elements.OTHER_HERO_PIPE_RIGHT));    
    result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_LEFT));
    result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_RIGHT));
    result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_LADDER));
    result = result.concat(this.findAll(OTHER_HERO_SHADOW_PIPE_LEFT));
    result = result.concat(this.findAll( OTHER_HERO_SHADOW_PIPE_RIGHT));
    return result;
  };

  getWallPositions() {
    var result = [];
    result = result.concat(this.findAll(Elements.BRICK));
    result = result.concat(this.findAll(Elements.UNDESTROYABLE_WALL));
    return result;
  };

  getLadderPositions() {
    var result = [];
    result = result.concat(this.findAll(Elements.LADDER));
    result = result.concat(this.findAll(Elements.HERO_LADDER));
    result = result.concat(this.findAll(Elements.OTHER_HERO_LADDER));
    result = result.concat(this.findAll(Elements.ENEMY_LADDER));
    return result;
  };

  getGoldPositions() {
    var result = [];
    result = result.concat(this.findAll(Elements.YELLOW_GOLD));
    result = result.concat(this.findAll(Elements.GREEN_GOLD));
    result = result.concat(this.findAll(Elements.RED_GOLD));
    return result;
  };

  getPipePositions() {
    var result = [];
    result = result.concat(this.findAll(Elements.PIPE));
    result = result.concat(this.findAll(Elements.HERO_PIPE_LEFT));
    result = result.concat(this.findAll(Elements.HERO_PIPE_RIGHT));
    result = result.concat(this.findAll(Elements.OTHER_HERO_PIPE_LEFT));
    result = result.concat(this.findAll(Elements.OTHER_HERO_PIPE_RIGHT));
    result = result.concat(this.findAll(Elements.ENEMY_PIPE_LEFT));
    result = result.concat(this.findAll(Elements.ENEMY_PIPE_RIGHT));
    return result;
  };

  getShadowPillPositions() {
    return this.findAll(Elements.THE_SHADOW_PILL);    
  };

  getPortalPositions() {
    return this.findAll(Elements.PORTAL);
  }

  getAt(x, y) {
    if (pt(x, y).isOutOf(this.size)) {
      return Elements.UNDESTROYABLE_WALL;
    }
    return this.board.charAt(this.xyl.getLength(x, y));
  };

  boardAsString() {
    var result = "";
    for (var i = 0; i < size; i++) {
      result += this.board.substring(i * this.size, (i + 1) * this.size);
      result += "\n";
    }
    return result;
  };

  findAll(element) {
    var result = [];
    for (var i = 0; i < this.size * this.size; i++) {
      var point = this.xyl.getXY(i);
      if (this.hasElementAt(point.x, point.y, element)) {
        result.push(point);
      }
    }
    return this.sort(result);
  };

  isAnyOfAt(x, y, elements) {
    if (pt(x, y).isOutOf(this.size)) {
      return false;
    }
    for (var index in elements) {
      var element = elements[index];
      if (this.hasElementAt(x, y, element)) {
        return true;
      }
    }
    return false;
  };

  isNearToElement(x, y, element) {
    if (pt(x, y).isOutOf(this.size)) {
      return false;
    }
    return this.hasElementAt(x + 1, y, element) || // TODO to remove duplicate
        this.hasElementAt(x - 1, y, element) ||
        this.hasElementAt(x, y + 1, element) ||
        this.hasElementAt(x, y - 1, element);
  };

  hasEnemyAt(x, y) {
    return this.isAnyOfAt(x, y, [
      Elements.ENEMY_LADDER,
      Elements.ENEMY_LEFT,
      Elements.ENEMY_PIPE_LEFT,
      Elements.ENEMY_PIPE_RIGHT,
      Elements.ENEMY_PIT,
      Elements.ENEMY_RIGHT
    ]);
  };

  hasOtherHeroAt(x, y) {
    return this.isAnyOfAt(x, y,
        [
          Elements.OTHER_HERO_LEFT,
          Elements.OTHER_HERO_RIGHT,
          Elements.OTHER_HERO_LADDER,
          Elements.OTHER_HERO_PIPE_LEFT,
          Elements.OTHER_HERO_PIPE_RIGHT
        ]);
  };

  hasWallAt(x, y) {
    if (pt(x, y).isOutOf(this.size)) {
      return true;
    }
    return this.isAnyOfAt(x, y, [Elements.BRICK, Elements.UNDESTROYABLE_WALL]);
  };

  hasLadderAt(x, y) {
    return this.isAnyOfAt(x, y, [
      Elements.LADDER,
      Elements.HERO_LADDER,
      Elements.ENEMY_LADDER,
      Elements.OTHER_HERO_LADDER
    ]);
  };

  hasGoldAt(x, y) {
    return this.isAnyOfAt(x, y, [
      Elements.YELLOW_GOLD,
      Elements.GREEN_GOLD,
      Elements.RED_GOLD
    ]);
  };

  hasPipeAt(x, y) {
    return this.isAnyOfAt(x, y, [
      Elements.PIPE,
      Elements.HERO_PIPE_LEFT,
      Elements.HERO_PIPE_RIGHT,
      Elements.OTHER_HERO_PIPE_LEFT,
      Elements.OTHER_HERO_PIPE_RIGHT,
      Elements.ENEMY_PIPE_LEFT,
      Elements.ENEMY_PIPE_RIGHT,
    ]);
  };

  hasShadowAt(x, y) {
    return this.isAnyOfAt(x, y, [
      HERO_SHADOW_DRILL_LEFT,
      HERO_SHADOW_DRILL_RIGHT,
      HERO_SHADOW_LADDER,
      HERO_SHADOW_LEFT,
      HERO_SHADOW_RIGHT,
      HERO_SHADOW_FALL_LEFT,
      HERO_SHADOW_FALL_RIGHT,
      HERO_SHADOW_PIPE_LEFT,
      HERO_SHADOW_PIPE_RIGHT,
      OTHER_HERO_SHADOW_DIE,
      OTHER_HERO_SHADOW_LEFT,
      OTHER_HERO_SHADOW_RIGHT,
      OTHER_HERO_SHADOW_LADDER,
      OTHER_HERO_SHADOW_PIPE_LEFT,
      OTHER_HERO_SHADOW_PIPE_RIGHT,
    ])
  };

  hasPortalAt(x, y) {
    return this.hasElementAt(x, y, Elements.PORTAL);  

  };

  countNear(x, y, element) {
    if (pt(x, y).isOutOf(this.size)) {
      return 0;
    }
    var count = 0;
    if (this.hasElementAt(x - 1, y, element)) {
      count++;
    } // TODO to remove duplicate
    if (this.hasElementAt(x + 1, y, element)) {
      count++;
    }
    if (this.hasElementAt(x, y - 1, element)) {
      count++;
    }
    if (this.hasElementAt(x, y + 1, element)) {
      count++;
    }
    return count;
  };
}

class Point {
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }

  equals(o) {
    return o.x === this.x && o.y === this.y;
  }

  toString() {
    return '[' + this.x + ',' + this.y + ']';
  }

  isOutOf(boardSize) {
    return this.x >= boardSize || this.y >= boardSize || this.x < 0 || this.y < 0;
  }
}

class LengthToXY {
  constructor(boardSize) {
    this.boardSize = boardSize;
  }

  inversionY(y) {
    return y;
  }

  inversionX(x) {
    return x;
  }

  getXY(length) {
    if (length === -1) {
      return null;
    }
    var x = this.inversionX(length % this.boardSize);
    var y = this.inversionY(Math.trunc(length / this.boardSize));
    return new Point(x, y);
  }

  getLength(x, y) {
    var xx = this.inversionX(x);
    var yy = this.inversionY(y);
    return yy * this.boardSize + xx;
  }
}

var pt = function (x, y) {
  return new Point(x, y);
};

