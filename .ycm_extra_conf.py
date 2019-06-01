import os
import sys

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))

MODULE_DEPS = {
    "mr-octopus": [
        "asset-locator",
        "gfx",
    ],
    "gfx": [
        "asset-locator",
    ],
}

EXTERNAL_DEPS = {
    "gfx": ["flat"],
    "mr-octopus": ["flat"],
}

def get_cxx_include_dir():
    base = "/usr/include/c++"
    max_version = max(os.listdir(base))
    return os.path.join(base, max_version)

CXX_INCLUDE_DIR = get_cxx_include_dir()

FLAGS = [
    "-Wall",
    "-Wextra",
    "-x", "c++",
    "-std=c++17",

    '-isystem', CXX_INCLUDE_DIR,
    '-isystem', CXX_INCLUDE_DIR + '/x86_64-pc-linux-gnu',
    '-isystem', CXX_INCLUDE_DIR + '/backward',
    '-isystem', '/usr/local/include/',
    '-isystem', '/usr/include/',
]

def cmake_directory(file_path):
    dir = os.path.dirname(file_path)
    while not os.path.exists(os.path.join(dir, "CMakeLists.txt")):
        dir = os.path.dirname(dir)
    return dir


class Module(object):
    def __init__(self, path):
        root_dir = cmake_directory(path)

        self.name = os.path.basename(root_dir)
        self.include_dir = os.path.join(root_dir, "include")


def module_include_dir(module_name):
    return os.path.join(SCRIPT_DIR, "src", module_name, "include")


def dep_include_dir(dep_name):
    return os.path.join(SCRIPT_DIR, "deps", dep_name, "include")


def flags_for_file(file_path):
    flags = FLAGS[:]
    def add_include_dir(include_dir):
        if os.path.exists(include_dir):
            flags.extend(["-I", include_dir])

    module = Module(file_path)

    add_include_dir(module.include_dir)
    for dependency in MODULE_DEPS[module.name]:
        add_include_dir(module_include_dir(dependency))
    for dependency in EXTERNAL_DEPS[module.name]:
        add_include_dir(dep_include_dir(dependency))

    return flags


def Settings(**kwargs):
    return {"flags": flags_for_file(kwargs["filename"])}


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: python .ycm_extra_conf_py PATH_TO_FILE")
    else:
        print(flags_for_file(sys.argv[1]))
