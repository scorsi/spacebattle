extends Node


export var lobby_name = ""
export var lobby_id = ""
export var lobby_players = 0
export var lobby_max_players = 2


func _ready():
	$lobby_name.text = lobby_name
	$lobby_id.text = lobby_id
	$lobby_players.text = str(lobby_players) + "/" + str(lobby_max_players)


func _connect():
	client.send_join_room(lobby_id)
