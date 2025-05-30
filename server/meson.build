project('chatroom', 'cpp', version : '1.5.1')

incdir = include_directories('src/main')

class_files = [
      	'src/main/main.cpp',
	'./src/main/server.cpp',
	'./src/main/client.cpp',
	'./src/main/user_status.cpp',
	'./src/main/request_manager.cpp',
	'./src/main/room.cpp',
	'./src/main/request_response.cpp',
	'./src/main/json_controller.cpp',
	'./src/main/operation.cpp']

#Dependencies:
#Jsoncpp
jsoncpp_proj = subproject('jsoncpp')
jsoncpp_dep = jsoncpp_proj.get_variable('jsoncpp_dep')

executable('server',
	sources : class_files,
	include_directories : incdir,
	dependencies: jsoncpp_dep)