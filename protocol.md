# Protocol

The protocol of the SpaceBattle game.

## Serialization

### Packet

A packet is formatted as follow: `<length:int64><message:message>`.

- `length` : The length in bytes of the following message.

- `message` : The message sent.

### **Message**

A message is formatted as follow: `<op:int32><status:bool><payload:any>?`.

- `op` : The operation id.

- `status` : The status of the message, should **OK** `true` or **ERROR** `false`.

- `payload` : The payload of the message, can be null / empty depending of the `op` and the `id` of the message.

The `payload` is either the `op` payload if the `status` is **OK** or a _error_ payload if the status is **ERROR**. 

### Array

A array is formatted as follow: `<length:int64>[<elem:T>]` where `T` is the type of the array.

- `length` : The number of element `T`.

- `elem` : An element of type `T`. 

### **Error**

An error is formatted like an `Array` of type `int16`, so fomatted as: `<length:int64>[<error-type:int16>]`.

- `length` : The number of errors.

- `error-type` : The _error id_ depending of the _message op id_.

### String

A string is formatted like an `Array` of type `char`, so formatted as: `<length:int64>[<elem:char>]`.

### Player

A player is formatted as follow: `<id:int64><name:string>`.

- `id` : The id of the player.

- `name` : The username of the player.

### Room

A room is formatted as follow: `<id:int64><name:string><status:int16><game-type:int16>`.

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

## Operations

### `0001` **set_client_id** (server → client → server)

Sent by the server to the client, it allow the client to know its id. The server must respond without payload and with `status` to true to passe to the `authentication` state. 

#### Payload

##### Server

`<id:string>`

- `id` : The client id.

#### Errors

##### Server

- `01` **unexpected_message** : The server doesn't expect this message from the client

##### Client

No available error

### `0101` **ask_username** (server → client)

Only sent by the server to the client during the `authentication` state, it allow the server to ask the client username.

#### Payload

##### Server

No payload.

#### Errors

##### Server

- `01` **unexpected_message** : The server doesn't expect this message from the client

##### Client

No available error

### `0102` **set_username** (client → server → client)

Sent by the client after the `ask_username` command sent by the server, it allow the client to set its username.

The server should respond with the status `OK` if everything is good and the client should passe to the `in_menu` state.

If the status code is `ERROR`, the client must send another valid username until the status is `OK`.

#### Payload

##### Client

`<username:string>`

- `username` : The username to set.

##### Server

No payload.

#### Errors

##### Server

- `01` **unexpected_message** : The server doesn't expect this message from the client

- `02` **poorly_formatted_payload** : The client's answer does not respect the payload format

- `02` **username_already_taken** : The given username by the client was already been taken

- `03` **invalid_username_** : The given username by the client is invalid

##### Client

No available error

### `0201` **fetch_rooms** (client → server → client)

Sent by the client, it allow the client to get all available rooms.

#### Payload

##### Client

No payload.

_Note: may change in the future._

##### Server

`<rooms:array<room>>`

- `rooms` : The list of actual rooms, refer to the `room` data strucure.

_Note: may change in the future._

#### Errors

##### Server

- `01` **unexpected_message** : The server doesn't expect this message from the client

##### Client

No available error

### `0202` **fetch_room_info** (client → server → client)

Sent by the client, it allow to fetch all info in a room as the players.

#### Payloads

##### Client

`<id:int64>`

- `id` : The id of the room to fetch info from.

##### Server

`<status:int16><players:array<player>>`

- `status` : The actual status of the room, refer to the `room` data strucutre.

- `players` : The connected players to the room.

_Note: may change in the future._

#### Errors

##### Server

- `01` **unexpected_message** : The server doesn't expect this message from the client

- `02` **poorly_formatted_payload** : The client's answer does not respect the payload format

##### Client

No available error

### `0203` **create_room** (client → server → client)

Sent by the client, it allow the client to create a new room.

#### Payloads

##### Client

`<name:string><game-type:int16>`

- `name` : The name of the room to create.

- `game-type` : The game type of the room.

##### Server

`<id:int64>`

- `id` : The id of the created room.

#### Errors

##### Server

- `01` **unexpected_message** : The server doesn't expect this message from the client

- `02` **poorly_formatted_payload** : The client's answer does not respect the payload format

- `03` **room_name_already_taken** : A room with the same name already exists

- `04` **game_type_do_not_exists** : The given game type does not exists

##### Client

No available error

### `0204` **join_room** (client → server → client)

Sent by the client, it allow the client to join a room thanks to its id.

#### Payload

##### Client

`<id:int64>`

- `id` : The id of the room to join.

##### Server

No payload.

#### Errors

##### Server

- `01` **unexpected_message** : The server doesn't expect this message from the client

- `02` **poorly_formatted_payload** : The client's answer does not respect the payload format

- `03` **room_is_full** : The given room is already full

- `04` **room_do_not_exists** : The given romm does not exists

##### Client

No available error

### `0301` **leave_room** (client → server → client)

Sent by the client, it allow the client to leave the actual connected room.

#### Payload

##### Client

No payload.

##### Server

No payload.

#### Errors

##### Server

- `01` **unexpected_message** : The server doesn't expect this message from the client

- `02` **not_connected_to_room** : The client is not connected to any room

##### Client

No available error

### `0302` **player_joined** (server → client)

Sent by the server to each client of a room to inform them a new connected client

#### Payload

##### Server

`<player:player>`

- `player` : The new connected player, see `player` data structure for more information.

#### Errors

##### Server

- `01` **unexpected_message** : The server doesn't expect this message from the client

##### Client

No available error

### `0303` **player_leaved** (server → client)

Sent by the server to each client of a room to inform them a client has leave

#### Payload

##### Server

`<id:int64>`

- `id` : The id of the client who leaved.

#### Errors

##### Server

- `01` **unexpected_message** : The server doesn't expect this message from the client

##### Client

No available error
