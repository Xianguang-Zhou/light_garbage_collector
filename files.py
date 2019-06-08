#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

import os, sys

__author__ = 'Xianguang Zhou <xianguang.zhou@outlook.com>'
__copyright__ = 'Copyright (C) 2019 Xianguang Zhou <xianguang.zhou@outlook.com>'
__license__ = 'MPL-2.0'


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
