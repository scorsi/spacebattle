extends Node

func _ready():
	$server_info/connected_as_value.text = global.username + " (" + global.player_id + ")"
	$server_info/connected_to_value.text = global.server_ip + ":" + str(global.server_port)
