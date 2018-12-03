extends Node

var username = ""
var player_id = null
var current_scene = null
var main_menu_error = null
var server_ip = "127.0.0.1"
var server_port = 42500

func _ready():
	client.connect("connection_success", self, "_connection_success")
	client.connect("connection_failure", self, "_connection_failure")
	client.connect("connection_ready", self, "_connection_ready")
	client.connect("disconnected", self, "_disconnected")
	
	var root = get_tree().get_root()
	current_scene = root.get_child(root.get_child_count() -1)
	set_process(false)


func goto_scene(path):
	call_deferred("_deferred_goto_scene", path)


func _deferred_goto_scene(path):
	current_scene.free()
	current_scene = ResourceLoader.load(path).instance()
	
	get_tree().get_root().add_child(current_scene)
	get_tree().set_current_scene(current_scene)


func create_client(_server_ip, _server_port):
	client.server_ip = _server_ip
	client.server_port = _server_port
	client.username = username
	client.connect_to_host()


func disconnect_server():
	client.disconnect_from_host()
	main_menu_error = null
	goto_scene("res://scenes/main_menu.tscn")


func _connection_success():
	print("_connection_success")


func _connection_ready():
	print("_connection_ready")
	player_id = client.player_id
	goto_scene("res://scenes/lobby_menu.tscn")


func _connection_failure():
	print("_connection_failure")
	main_menu_error = "Cannot connect to the server"
	goto_scene("res://scenes/main_menu.tscn")


func _disconnected():
	print("_disconnected")
	main_menu_error = "Server disconnected"
	goto_scene("res://scenes/main_menu.tscn")
