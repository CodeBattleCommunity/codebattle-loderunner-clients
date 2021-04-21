var boardRegex = /board=/;
class GameClient {
  constructor(url) {

	this.path = url.replace("http", "ws").replace("board/player/", "ws?user=").replace("?code=", "&code=");
        this.board = new Board();
  }

  run(callback) {
    var self = this;
    this.socket = new WebSocket(this.path);
    this.socket.onopen = this.onOpen;
    this.socket.onerror = this.onError.bind(this, callback);
    this.socket.onclose = this.onClose;
    this.socket.onmessage = function (event) {
      var board = new Board(event.data.replace(boardRegex, ''));
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

  onError(callback, error) {
    text.value += "### error ###\n" + error.message + "\n" + "### Try to reconnect after 1s...\n";

    setTimeout(() => this.run(callback), 1000);
  }

  send(msg) {
    text.value += "Sending: " + msg + '\n'
    this.socket.send(msg)
  }
}

