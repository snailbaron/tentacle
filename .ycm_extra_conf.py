import os

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))

MODULE_DEPS = {
    "mr-octopus": ["asset-locator"],
}

FLAGS = [
    "-Wall",
    "-Wextra",
    "-x", "c++",
    "-std=c++17",

    "-isystem", "/usr/include/c++/8.2.1",
    "-isystem", "/usr/include/c++/8.2.1/x86_64-pc-linux-gnu",
    "-isystem", "/usr/include/c++/8.2.1/backward",
    "-isystem", "/usr/local/include",
    "-isystem", "/usr/include",
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


def Settings(**kwargs):
    flags = FLAGS[:]

    def add_include_dir(include_dir):
        if os.path.exists(include_dir):
            flags.extend(["-I", include_dir])

    file_path = kwargs["filename"]
    module = Module(file_path)

    add_include_dir(module.include_dir)
    for dependency in MODULE_DEPS[module.name]:
        add_include_dir(module_include_dir(dependency))

    return {"flags": flags}
