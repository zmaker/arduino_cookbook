// SPDX-FileCopyrightText: Copyright (C) Arduino s.r.l. and/or its affiliated companies
//
// SPDX-License-Identifier: MPL-2.0

class WebUI {
  #socket;

  constructor(options = {}) {
    this.#socket = io(`http://${window.location.host}`, options);
  }

  /**
   * Called when the websocket connects to the server.
   * @param {() => void} callback - Called once when the connection is established.
   */
  on_connect(callback) {
    this.#socket.on('connect', callback);
  }

  /**
   * Called when the websocket disconnects from the server.
   * @param {() => void} callback - Called once when the connection is lost.
   */
  on_disconnect(callback) {
    this.#socket.on('disconnect', callback);
  }

  /**
   * Registers a callback for a specific event message from the board.
   * @param {string} eventName - The name of the event to listen for (e.g., 'led_status_update').
   * @param {(data: any) => void} callback - Callback invoked when the event is received.
   */
  on_message(eventName, callback) {
    this.#socket.on(eventName, callback);
  }

  /**
   * Sends a message to the board for a specific event.
   * @param {string} eventName - The name of the event to send (e.g., 'toggle_led').
   * @param {*} [data] - The data to send with the event. If omitted, an empty object is sent.
   */
  send_message(eventName, data) {
    this.#socket.emit(eventName, data ?? {});
  }
}
