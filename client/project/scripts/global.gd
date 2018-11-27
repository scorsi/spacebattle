extends Node


var username = ""


func create_server(server_port):
	var peer = NetworkedMultiplayerENet.new()
	peer.create_server(server_port, 10)
	get_tree().set_network_peer(peer)
	init_signal()
	return true


func create_client(server_ip, server_port):
	var peer = NetworkedMultiplayerENet.new()
	peer.create_client(server_ip, server_port)
	get_tree().set_network_peer(peer)
	init_signal()
	return true


func init_signal():
	get_tree().disconnect("network_peer_connected", self, "_player_connected")
	get_tree().connect("network_peer_connected", self, "_player_connected")
	get_tree().disconnect("network_peer_disconnected", self, "_player_disconnected")
	get_tree().connect("network_peer_disconnected", self, "_player_disconnected")
	get_tree().disconnect("connected_to_server", self, "_connected_success")
	get_tree().connect("connected_to_server", self, "_connected_success")
	get_tree().disconnect("connection_failed", self, "_connected_failure")
	get_tree().connect("connection_failed", self, "_connected_failure")
	get_tree().disconnect("server_disconnected", self, "_server_disconnected")
	get_tree().connect("server_disconnected", self, "_server_disconnected")

func _player_connected(id):
	print("_player_connected")

func _player_disconnected(id):
	print("_player_disconnected")

func _connected_success():
	print("_connected_success")

func _connected_failure():
	print("_connected_failure")

func _server_disconnected():
	print("_server_disconnected")
