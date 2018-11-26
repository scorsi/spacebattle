extends Node

var ip_address_node

var form_container
var loading_container
var port_node
var connect_button_node
var error_msg_node

func _ready():
	form_container = get_node("background/form_container")
	loading_container = get_node("background/loading_container")
	
	ip_address_node = get_node("background/form_container/ip_address_text_edit")
	port_node = get_node("background/form_container/port_text_edit")
	connect_button_node = get_node("background/form_container/connect_button")
	error_msg_node = get_node("background/form_container/connect_error")
	
	connect_button_node.connect("pressed", self, "_connect_to_server")

func _display_error(msg):
	error_msg_node.text = msg
	error_msg_node.show()

func _connect_to_server():
	error_msg_node.hide()
	var ip_address = ip_address_node.text
	var port = port_node.text
	if ip_address.length() == 0:
		_display_error("Ip address is blank.")
	else:
		var regex = RegEx.new()
		regex.compile("^\\d{1,3}\\.\\d{1,3}.\\d{1,3}.\\d{1,3}$")
		if regex.search(ip_address):
			regex.compile("^\\d{1,5}$")
			if regex.search(port) and int(port) > 0 and int(port) <= 65535:
				form_container.hide()
				loading_container.show()
				
			else:
				_display_error("Port must be a valid number between 0 and 65535")
		else:
			_display_error("Ip address is not a valid ip address.")
