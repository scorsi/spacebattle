extends Node

var username = ""
var current_scene = null

func _ready():
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
	client.connect("connection_success", self, "_connection_success")
	client.connect("connection_failure", self, "_connection_failure")
	client.connect("disconnected", self, "_disconnected")
	client.start_client(_server_ip, _server_port)


func _connection_success():
	print("_connected_success")


func _connection_failure():
	print("_connected_failure")


func _disconnected():
	print("_server_disconnected")
