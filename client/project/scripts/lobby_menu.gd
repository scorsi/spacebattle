extends Node


onready var server_info = $server_info
onready var lobby_list = $lobby_list
onready var lobby_name = $lobby_name


func _ready():
	$server_info/connected_as_value.text = global.username + " (" + global.player_id + ")"
	$server_info/connected_to_value.text = global.server_ip + ":" + str(global.server_port)
	client.connect("result_create_room", self, "_on_result_create_room")
	client.connect("result_join_room", self, "_on_result_join_room")


func _on_disconnect_pressed():
	global.disconnect_server()


func _on_toggle_server_info_pressed():
	server_info.visible = !server_info.visible
	#server_info.hide() if server_info.visible else server_info.show()


func _on_result_create_room(id):
	print("_on_result_create_room", id)


func _on_result_join_room():
	print("_on_result_join_room")


func _on_create_lobby_pressed():
	client.send_create_room(lobby_name.text)


func _on_fetch_lobbies_pressed():
	$lobby_list.refresh_lobbies()
