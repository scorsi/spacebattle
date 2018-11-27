extends Node

const SERVER_PORT = 42500
const MAX_PLAYERS = 4
const SERVER_IP = "127.0.0.1"

# Player info, associate ID to data
var player_info = {}
# Info we send to other players
var my_info = { name = "Johnson Magenta", favorite_color = Color8(255, 0, 255) }

func _ready():
	get_node("host_button").connect("pressed", self, "_create_server")
	get_node("client_button").connect("pressed", self, "_create_client")
	
	get_tree().connect("network_peer_connected", self, "_player_connected")
	get_tree().connect("network_peer_disconnected", self, "_player_disconnected")
	get_tree().connect("connected_to_server", self, "_connected_success")
	get_tree().connect("connection_failed", self, "_connected_failure")
	get_tree().connect("server_disconnected", self, "_server_disconnected")

func _create_server():
	var peer = NetworkedMultiplayerENet.new()
	peer.create_server(SERVER_PORT, MAX_PLAYERS)
	get_tree().set_network_peer(peer)
	
	get_node("host_button").hide()
	get_node("client_button").hide()

func _create_client():
	var peer = NetworkedMultiplayerENet.new()
	peer.create_client(SERVER_IP, SERVER_PORT)
	get_tree().set_network_peer(peer)
	
	my_info.name = str(get_tree().get_network_unique_id())
	
	get_node("host_button").hide()
	get_node("client_button").hide()

func _player_connected(id):
	print("_player_connected")

func _player_disconnected(id):
	print("_player_disconnected")
	player_info.erase(id)
	update_players_display()

func _connected_success():
	print("_connected_success")
	rpc("register_player", get_tree().get_network_unique_id(), my_info)

func _connected_failure():
	print("_connected_failure")

func _server_disconnected():
	print("_server_disconnected")

func update_players_display():
	var players_text = ""
	for peer_id in player_info:
		players_text += player_info[peer_id].name + "\n"
	get_node("players").text = players_text

remote func register_player(id, info):
	print("register_player")
	update_players_display()
	# If I'm the server, let the new guy know about existing players
	if get_tree().is_network_server():
		# Send my info to new player
		rpc_id(id, "register_player", 1, my_info)
		# Send the info of existing players
		for peer_id in player_info:
			rpc_id(id, "register_player", peer_id, player_info[peer_id])
	# Store the info
	player_info[id] = info
