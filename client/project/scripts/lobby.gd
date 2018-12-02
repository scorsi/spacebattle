extends Node


export var lobby_name = ""
export var lobby_id = ""


func _ready():
	$name.text = lobby_name
	$id.text = lobby_id


func _connect():
	pass
