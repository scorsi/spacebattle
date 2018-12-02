extends Node


onready var server_info = $server_info


func _ready():
	$server_info/connected_as_value.text = global.username + " (" + global.player_id + ")"
	$server_info/connected_to_value.text = global.server_ip + ":" + str(global.server_port)


func _on_disconnect_pressed():
	global.disconnect_server()


func _on_toggle_server_info_pressed():
	server_info.hide() if server_info.visible else server_info.show()
