# Protocol

The protocol of the SpaceBattle game.

## Serialization

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

- `100` **USERNAME** : Allow to ask/set the username.

- `200` **ROOM_FETCH** : Client fetch available rooms.

- `201` **ROOM_CONNECT** : Client tries to connect to server.

- `202` **ROOM_DISCTONNECT** : Client inform the server of the room disconnection.

- `203` **ROOM_READY** : Server informs clients that the room is ready. 

- `300` **CLIENT_FETCH** : Client fetch connected clients of the room.

- `301` **CLIENT_CONNECT** : Server inform client that a client has been connected to the room.

- `302` **CLIENT_DISCONNECT** : Server inform client that a client has been disconnected from the server.

- `303` **CLIENT_READY** : Server inform clients that a client is ready.

- `304` **GAME_LAUNCH** : Server inform clients that the game is starting.

- `305` **GAME_START** : Server inform clients that the game has started (all clients loads the game).
