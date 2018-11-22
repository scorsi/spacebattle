# Protocol

The protocol of the SpaceBattle game.

## Serialization

### Packet

A packet is formatted as follow: `<length:int><message:message>`.

- `length` : The length in bytes of the following message.

- `message` : The message sent.

### **Message**

A message is formatted as follow: `<op:int><id:int><status:int><payload:any>?`.

- `op` : The operation id.

- `id` : The communication response id.

- `status` : The status of the message, should **OK** `1` or **ERROR** `0`.

- `payload` : The payload of the message, can be null / empty depending of the `op` and the `id` of the message.

### Array

A array is formatted as follow: `<length:int>[<elem:T>]` where `T` is the type of the array.

- `length` : The number of element `T`.

- `elem` : An element of type `T`. 

### String

A string is formatted like an `Array` of type `char`, so formatted as: `<length:int>[<elem:char>]`.

### Player

A player is formatted as follow: `<id:int><name:string>`.

- `id` : The id of the player.

- `name` : The name of the player.

### Room

A room is formatted as follow: `<id:int><name:string><status:int><game-type:int>[<players:player>]`.

- `id` : The id of the room.

- `name` : The name of the room.

- `status` : The status of the room, should be:

  - **WAITING_FOR_PLAYER** `0`

  - **READY** `1`

  - **STARTING** `2`

  - **STARTED** `3`

  - **FINISHED** `4`

- `game-type` : The id type of the game, should be:

  - **CLASSIC** `1`

- `players` : The connected players.

## Operations

### `100` **USERNAME** : _Allow the server to ask and the client to set its username_.

#### Errors

##### Server errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

- `10` **USERNAME__ALREADY_TAKEN** : The given username by the client was already been taken

- `11` **USERNAME_INVALID** : The given username by the client is invalid

##### Client errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

#### Operation communication steps

1. Server : asks username to client

   `USERNAME``0``OK`

2. Client : answers to server with username

   `USERNAME``1``OK``"username"`

3. Server : answers

   - Server accepts the client username

     `USERNAME``2``OK`

   - Server don't accepts the client username

     `USERNAME``2``ERROR``error_message`

4. Client : back to number 2. until server accepts

### `200` **ROOM_FETCH** : _Allow the client to fetch available rooms_.

#### Errors

##### Server errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

##### Client errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

#### Operation communication steps

1. 

2. 

### `201` **ROOM_CONNECT** : _Allow the client to connect to a room_.

#### Errors

##### Server errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

##### Client errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

#### Operation communication steps

1. 

### `202` **ROOM_DISCONNECT** : _Allow the client to disconnect from its actual room_.

#### Errors

##### Server errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

##### Client errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

#### Operation communication steps

### `203` **ROOM_READY** : _Allow the server to inform the connected clients of a room that the room is ready to be launched_.

#### Errors

##### Server errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

##### Client errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

#### Operation communication steps

### `300` **CLIENT_FETCH** : _Allow the client to fetch information of another client_.

#### Errors

##### Server errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

##### Client errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

#### Operation communication steps

### `301` **CLIENT_CONNECTED** : _Allow the server to inform connected client of a room that a new client has been connected_.

#### Errors

##### Server errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

##### Client errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

#### Operation communication steps

### `302` **CLIENT_DISCONNECTED** : _Allow the server to inform connected client of a room that a client has been disconnected_.

#### Errors

##### Server errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

##### Client errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

#### Operation communication steps

### `303` **CLIENT_READY** : _Allow the server to inform connected clients of a room that a cient is now ready or no longer ready_.

#### Errors

##### Server errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

##### Client errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

#### Operation communication steps

### `400` **GAME_LAUNCHING** : _Allow the server to inform connected clients of a room that the game will launch_.

#### Errors

##### Server errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

##### Client errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

#### Operation communication steps

### `401` **GAME_STARTED** : _Allow the server to inform connected clients of a game that the game is started_.

#### Errors

##### Server errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

##### Client errors

- `00` **UNKNOWN_ANSWER** : The given answer from the server is unknown by the client

- `01` **UNEXPECTED_ANSWER** : The given answer from the server is unexpected by the client

#### Operation communication steps
