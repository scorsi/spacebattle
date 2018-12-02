extends ScrollContainer


export(PackedScene) var lobby_scene
onready var container = $container


func _ready():
	client.send_fetch_rooms()
	client.connect("result_fetch_rooms", self, "_on_result_fetch_rooms")


func _on_result_fetch_rooms(rooms):
	for c in container.get_children():
		c.queue_free()
	
	for r in rooms:
		var new_lobby = lobby_scene.instance()
		new_lobby.lobby_name = r["name"]
		new_lobby.lobby_id = r["id"]
		container.add_child(new_lobby)
