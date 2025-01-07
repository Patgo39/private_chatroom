project('chatroom', 'cpp', version : '1.5.1')

incdir = include_directories('src/main', 'src/main/view')

class_files = [
      	'src/main/main.cpp',
	'./src/main/view/screen.cpp',
	'./src/main/client.cpp',
	'./src/main/client_connection_exception.cpp',
	'./src/main/command_exception.cpp',
	'./src/main/command_manager.cpp']

#Dependencies:
#Ncurses
ncurses = dependency('ncurses', required : true)

#Jsoncpp
jsoncpp_proj = subproject('jsoncpp')
jsoncpp_dep = jsoncpp_proj.get_variable('jsoncpp_dep')


executable('client',
	sources : class_files,
	include_directories : incdir,
	dependencies: [ncurses,
		      jsoncpp_dep])