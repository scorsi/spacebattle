extends Node


var state = ""


var network_type_container
var join_form_container
var create_form_container
var loading_container
var error_container


func _ready():
	error_container = get_node("error_container")
	network_type__init()
	loading__init()
	join_form__init()
	create_form__init()
	
	if global.main_menu_error != null:
		display_error(global.main_menu_error, "network_type__display")
	else:
		network_type__display()


func hide_all_container():
	error_container.hide()
	network_type_container.hide()
	join_form_container.hide()
	create_form_container.hide()
	loading_container.hide()


func display_error(text, function):
	get_node("error_container/text").text = text
	get_node("error_container/button").disconnect("pressed", self, "display_join_form_container")
	get_node("error_container/button").connect("pressed", self, function)
	hide_all_container()
	error_container.show()


## NETWORK TYPE STATE

func network_type__init():
	network_type_container = get_node("network_type_container")
	get_node("network_type_container/join_button").connect("pressed", self, "network_type__join_button_pressed")
	get_node("network_type_container/host_button").connect("pressed", self, "network_type__host_button_pressed")


func network_type__join_button_pressed():
	join_form__display()


func network_type__host_button_pressed():
	create_form__display()


func network_type__display():
	hide_all_container()
	network_type_container.show()
	state = "network_type"


## LOADING STATE

func loading__init():
	loading_container = get_node("loading_container")


func loading__display():
	hide_all_container()
	loading_container.show()
	state = "loading"


## JOIN FORM STATE

func join_form__init():
	join_form_container = get_node("join_form_container")
	get_node("join_form_container/button").connect("pressed", self, "join_form__button_pressed")
	get_node("join_form_container/return").connect("pressed", self, "network_type__display")


func join_form__button_pressed():
	loading__display()
	
	var ip_address = get_node("join_form_container/ip_address/text_edit").text
	var port = get_node("join_form_container/port/text_edit").text
	var username = get_node("join_form_container/username/text_edit").text
	
	if ip_address.length() == 0:
		display_error("IP address must not be blank.", "join_form__display")
		return
	elif port.length() == 0:
		display_error("Port must not be blank.", "join_form__display")
		return
	elif username.length() == 0:
		display_error("Username must not be blank.", "join_form__display")
		return
	
	var regex = RegEx.new()
	regex.compile("^\\d{1,3}\\.\\d{1,3}.\\d{1,3}.\\d{1,3}$")
	if !regex.search(ip_address):
		display_error("The given IP address is not a valid ip address.", "join_form__display")
		return
	regex.compile("^\\d{1,5}$")
	if !regex.search(port) or !(int(port) > 0 and int(port) <= 65535):
		display_error("Port must be a valid number between 0 and 65535.", "join_form__display")
		return
	
	global.username = username
	global.create_client(ip_address, int(port))


func join_form__display():
	hide_all_container()
	get_node("join_form_container/ip_address/text_edit").text = global.server_ip
	get_node("join_form_container/port/text_edit").text = str(global.server_port)
	get_node("join_form_container/username/text_edit").text = global.username
	join_form_container.show()
	state = "join_form"


## CREATE FORM STATE

func create_form__init():
	create_form_container = get_node("create_form_container")
	get_node("create_form_container/button").connect("pressed", self, "create_form__button_pressed")
	get_node("create_form_container/return").connect("pressed", self, "network_type__display")


func create_form__button_pressed():
	loading__display()
	
	var port = get_node("create_form_container/port/text_edit").text
	var username = get_node("create_form_container/username/text_edit").text
	
	if port.length() == 0:
		display_error("Port must not be blank.", "create_form__display")	
		return
	elif username.length() == 0:
		display_error("Username must not be blank.", "create_form__display")	
		return
	
	var regex = RegEx.new()
	regex.compile("^\\d{1,5}$")
	if !regex.search(port) or !(int(port) > 0 and int(port) <= 65535):
		display_error("Port must be a valid number between 0 and 65535.", "create_form__display")
		return
	
	global.username = username
	global.create_server(int(port))
	global.goto_scene("res://scenes/lobby.tscn")


func create_form__display():
	hide_all_container()
	create_form_container.show()
	state = "create_form"
