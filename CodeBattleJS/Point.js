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