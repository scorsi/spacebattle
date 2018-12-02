extends ScrollContainer


export(PackedScene) var lobby_scene
onready var container = $container


func _ready():
	for i in range(5):
		var new_lobby_elem = lobby_scene.instance()
		container.add_child(new_lobby_elem)
		container.add_spacer(false)
