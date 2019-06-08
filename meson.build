# Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

project('light_garbage_collector', 'cpp', default_options : ['cpp_std=c++17'])

dep_list = []

include_path = 'include'
src_path = 'src'
files_script_path = 'files.py'

include_dir = include_directories(include_path, src_path)
install_subdir(include_path,
	install_dir : join_paths(get_option('includedir'), meson.project_name()),
	strip_directory : true)

src_list = run_command(files(files_script_path), src_path, '.cc')\
	.stdout().strip().split('\n')

library(meson.project_name(),
	sources : src_list,
	include_directories : include_dir,
	dependencies : dep_list,
	install : true)
