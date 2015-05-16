#!/usr/bin/python3

import configparser
import re

VERSION_H = 'include/kernel/version.h'

"""
Replaces the matched contents of a file with the given string.
Arguments:
    filename: The file to open
    search: The search pattern
    pattern: The pattern to replace
    string: The string to replace with
"""
def update(filename, search, pattern, string):
    lines = []

    # Read in the contents
    with open(filename, 'r') as conf:
        lines = conf.readlines()

    # Find the line to edit
    for n, line in enumerate(open(filename)):
        result = re.search(search, line)

        # Replace the matched pattern
        if result != None:
            new = re.sub(pattern, string, line)
            lines[n] = new

    # Writeback
    with open(filename, 'w') as conf:
        conf.writelines(lines)

"""
The main function of this script.
"""
if __name__ == "__main__":
    config = configparser.ConfigParser()
    config.read('ritchie.conf')

    # Read in the options
    (name, version, codename) = [pair[1] for pair in config.items('Version')]
    (arch, image, device) = [pair[1] for pair in config.items('Build')]

    version_string = "\""+ name +" "+ version +" ("+codename+")\""

    # Update the GRUB configuration file
    print('Updating \'grub.cfg\'... ', end='')
    update('grub.cfg', 'menuentry', r'\".*\"', version_string)
    update('grub.cfg', 'multiboot', r'/boot/.*$', '/boot/'+image)
    print('DONE')

    # Update kernel version header file
    print('Updating \''+ VERSION_H +'\'... ', end='')
    update(VERSION_H, 'PROJECT', r'PROJECT \".*\"', 'PROJECT \"'+ name +'\"')
    update(VERSION_H, 'VERSION', r'VERSION \".*\"', 'VERSION \"'+ version +'\"')
    update(VERSION_H, 'CODENAME', r'CODENAME \".*\"', 'CODENAME \"'+ codename +'\"')
    print('DONE')

    # Update config.make file
    print('Updating \'config.make\'... ', end='')
    update('config.make', 'ARCH', r'ARCH = .*', 'ARCH = '+ arch)
    update('config.make', 'IMAGE', r'IMAGE = .*', 'IMAGE = '+ image)
    update('config.make', 'DEVICE', r'DEVICE = .*', 'DEVICE = '+ device)
    print('DONE')