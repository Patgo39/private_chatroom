project('Proyecto1', 'cpp', version : '1.3.2',
default_options : ['warning_level=2', 'cpp_std=c++14'])

src_files = files('src/main/myp/files/Cliente.cpp')
inc_dir = include_directories('src/main/myp/files')

executable('Cliente',
	'./src/main/myp/files/main.cpp',
	src_files,
	include_directories: inc_dir)