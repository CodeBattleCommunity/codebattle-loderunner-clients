class Board {

    constructor(board = ''){
        this._boardString = board;
        this._len = this._boardString.length;
        this._size = Math.sqrt(this._len);

        this._board2d = this._boardString.match(new RegExp(`.{${this._size}}`,"g"))?.join('\n');
    }

    get size() {
        return this._size;
    }

    
    findAll(element) {
        let result = [];
        for (let i = 0; i < this._len; i++) {
            var item = this._boardString[i];
            if (item === element) {
                result = result.concat(this._strpos2point(i));
            }
        }
        return result;
    }

    getAt(x, y) {
        // Return an Element object at coordinates x,y
        return this._boardString[this._xy2strpos(x, y)];
    }

    hasElementAt(x, y, element) {
        // Return True if Element is at x,y coordinates
        return element === this.getAt(x, y);
    }

    isBarrierAt(x, y) {
        // Return true if barrier is at x,y
        return Point(x, y) in this.barriers;
    }

   get myPosition() {
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
    }

    get isGameOver() {
        return this._boardString.includes(Elements.HERO_DIE);
    }

    get enemyPositions() {
        // Return the list of points for other heroes
        var result = [];
        
        result = result.concat(this.findAll(Elements.ENEMY_LADDER));
        result = result.concat(this.findAll(Elements.ENEMY_LEFT));
        result = result.concat(this.findAll(Elements.ENEMY_PIPE_LEFT));
        result = result.concat(this.findAll(Elements.ENEMY_PIPE_RIGHT));
        result = result.concat(this.findAll(Elements.ENEMY_RIGHT));
        result = result.concat(this.findAll(Elements.ENEMY_PIT));

        return result;
    }

    get otherHeroPositions() {
        // Return the list of points for other heroes
        var result = [];

        result = result.concat(this.findAll(Elements.OTHER_HERO_LADDER));
        result = result.concat(this.findAll(Elements.OTHER_HERO_LEFT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_RIGHT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_PIPE_LEFT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_PIPE_RIGHT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_LEFT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_RIGHT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_LADDER));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_PIPE_LEFT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_PIPE_RIGHT));

        return result;
    }

    get shadowPills() {
        var result = [];
        result = result.concat(this.findAll(Elements.THE_SHADOW_PILL));
        return result;
    }

    get portals() {
        var result = [];
        result = result.concat(this.findAll(Elements.PORTAL));
        return result;
    }

    get shadows() {
        var result = [];

        result = result.concat(this.findAll(Elements.HERO_SHADOW_DRILL_LEFT));
        result = result.concat(this.findAll(Elements.HERO_SHADOW_DRILL_RIGHT));
        result = result.concat(this.findAll(Elements.HERO_SHADOW_LADDER));
        result = result.concat(this.findAll(Elements.HERO_SHADOW_LEFT));
        result = result.concat(this.findAll(Elements.HERO_SHADOW_RIGHT));
        result = result.concat(this.findAll(Elements.HERO_SHADOW_FALL_LEFT));
        result = result.concat(this.findAll(Elements.HERO_SHADOW_FALL_RIGHT));
        result = result.concat(this.findAll(Elements.HERO_SHADOW_PIPE_LEFT));
        result = result.concat(this.findAll(Elements.HERO_SHADOW_PIPE_RIGHT));

        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_LEFT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_RIGHT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_LADDER));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_PIPE_LEFT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_PIPE_RIGHT));

        return result;
    }

    get wallPositions() {
        // Returns the list of walls Element Points
        var result = [];

        result = result.concat(this.findAll(Elements.BRICK));
        result = result.concat(this.findAll(Elements.UNDESTROYABLE_WALL));

        return result;
    }

    get ladderPositions() {
        // Returns the set of ladder Points
        var result = [];

        result = result.concat(this.findAll(Elements.LADDER));
        result = result.concat(this.findAll(Elements.HERO_LADDER));
        result = result.concat(this.findAll(Elements.OTHER_HERO_LADDER));
        result = result.concat(this.findAll(Elements.ENEMY_LADDER));
        result = result.concat(this.findAll(Elements.HERO_SHADOW_LADDER));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_LADDER));

        return result;
    }

    get goldPositions() {
        var result = [];

        result = result.concat(this.findAll(Elements.YELLOW_GOLD));
        result = result.concat(this.findAll(Elements.GREEN_GOLD));
        result = result.concat(this.findAll(Elements.RED_GOLD));

        return result;
    }

    get pipePositions() {
        // Returns the set of pipe Points
        var result = [];

        result = result.concat(this.findAll(Elements.PIPE));
        result = result.concat(this.findAll(Elements.HERO_PIPE_LEFT));
        result = result.concat(this.findAll(Elements.HERO_PIPE_RIGHT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_PIPE_LEFT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_PIPE_RIGHT));
        result = result.concat(this.findAll(Elements.ENEMY_PIPE_LEFT));
        result = result.concat(this.findAll(Elements.ENEMY_PIPE_RIGHT));
        result = result.concat(this.findAll(Elements.HERO_SHADOW_PIPE_LEFT));
        result = result.concat(this.findAll(Elements.HERO_SHADOW_PIPE_RIGHT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_PIPE_LEFT));
        result = result.concat(this.findAll(Elements.OTHER_HERO_SHADOW_PIPE_RIGHT));

        return result;
    }

    get barriers() {    
        // Return the list of barriers Points
        var result = [];
        result = result.concat(this.wallPositions);
        return result;
    }

    isNearToElement(x, y, elem) {
        var nearXY = [
            { x: x + 1, y: y }, 
            { x: x - 1, y: y },
            { x: x, y: y + 1 }, 
            { x: x, y: y - 1 }
        ];
        if (!new Point(x, y).isOutOf(this._size)) {
            return nearXY.some(item => this.hasElementAt(item.x, item.y, elem));
        }

        return false;
    }

    hasEnemyAt(x, y) {
        return this._hasElementAtPoint(this.enemyPositions, x, y);
    }

    hasOtherHeroAt(x, y) {
        return this._hasElementAtPoint(this.otherHeroPositions, x, y);
    }

    hasWallAt(x, y) {
        return this._hasElementAtPoint(this.wallPositions, x, y);
    }

    hasLadderAt(x, y) {
        return this._hasElementAtPoint(this.ladderPositions, x, y);
    }

    hasGoldAt(x, y) {
        return this._hasElementAtPoint(this.goldPositions, x, y);
    }

    hasPipeAt(x, y) {
        return this._hasElementAtPoint(this.pipePositions, x, y);
    }

    hasShadowAt(x, y) {
        return this._hasElementAtPoint(this.shadows, x, y);
    }

    getCountElementsNearToPoint(x, y, elem) {
        // Counts the number of occurencies of elem nearby
        if (!new Point(x, y).isOutOf(this._size)) {
            var nearXY = [
                { x: x + 1, y: y }, 
                { x: x - 1, y: y },
                { x: x, y: y + 1 }, 
                { x: x, y: y - 1 }
            ];
            return  nearXY.reduce((acc, item) => {
                if (this.hasElementAt(item.x, item.y, elem)) {
                    return acc + 1;
                }
                return acc;
            }, 0);
        }
        return 0;
    }

    _hasElementAtPoint(pointsArray, x, y) {
        var point = new Point(x, y);
        return pointsArray.some(item => point.equals(item));
    }

    _strpos2point(strpos) {
        return new Point(...this._strpos2xy(strpos));
    }

    _strpos2xy(strpos) {
        var x = strpos % this._size;
        var y = Math.trunc(strpos / this._size);
        return [x, y];
    }

    _xy2strpos(x, y) {
        return this._size * y + x;
    }
}
