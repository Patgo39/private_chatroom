project('chatroom', 'cpp', version : '1.5.1')

incdir = include_directories('src/main', 'src/main/view')

class_files = [
      	'src/main/main.cpp',
	'./src/main/view/screen.cpp',
	'./src/main/client.cpp',
	'./src/main/client_connection_exception.cpp']

executable('client', sources : class_files, include_directories : incdir)