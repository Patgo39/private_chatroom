project('chatroom', 'cpp', version : '1.5.1',
		    default_options : ['cpp_std=c++23'])

incdir = include_directories('src/chatroom/main')

class_files = [
      	'src/chatroom/main/main.cpp']

#Dependencies:
#Jsoncpp
jsoncpp_proj = subproject('jsoncpp')
jsoncpp_dep = jsoncpp_proj.get_variable('jsoncpp_dep')

executable('server',
	sources : class_files,
	include_directories : incdir,
	dependencies: jsoncpp_dep)