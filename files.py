#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import os, sys

__author__ = 'Xianguang Zhou <xianguang.zhou@outlook.com>'
__copyright__ = 'Copyright (C) 2019 Xianguang Zhou <xianguang.zhou@outlook.com>'
__license__ = 'AGPL-3.0'


def main():
    directory_arg = sys.argv[1]
    extension_name_arg = sys.argv[2]

    for root, _dirs, files in os.walk(
            os.path.join(os.path.dirname(__file__), directory_arg)):
        for file_name in files:
            _, extension_name = os.path.splitext(file_name)
            if extension_name == extension_name_arg:
                print(os.path.join(root, file_name))


if __name__ == '__main__':
    main()
