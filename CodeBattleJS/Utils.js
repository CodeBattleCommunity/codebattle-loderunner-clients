var pt = function (x, y) {
  return new Point(x, y);
};

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

