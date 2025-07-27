project('chatroom', 'cpp', version : '1.5.1',
		    default_options: ['cpp_std_=c++23'])

incdir = include_directories('src/main', 'src/main/view')

class_files = [
      	'src/main/main.cpp',
	'./src/main/view/screen.cpp',
	'./src/main/client.cpp',
	'./src/main/client_connection_exception.cpp',
	'./src/main/command_exception.cpp',
	'./src/main/command_manager.cpp',
	'./src/main/view/user_interface.cpp',
	'./src/main/server_response_manager.cpp',
	',/src/main/message.cpp',
	'./src/main/server_response_exception.cpp']

#Dependencies:
ftxui_proj = subproject('ftxui')
screen_dep = ftxui_proj.get_variable('screen_dep')
dom_dep = ftxui_proj.get_variable('dom_dep')
component_dep = ftxui_proj.get_variable('component_dep')

#Jsoncpp
jsoncpp_proj = subproject('jsoncpp')
jsoncpp_dep = jsoncpp_proj.get_variable('jsoncpp_dep')


executable('client',
	sources : class_files,
	include_directories : incdir,
	dependencies: [jsoncpp_dep,
		      screen_dep,
		      dom_dep,
		      component_dep])