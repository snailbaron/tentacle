import os

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))


def Settings(**kwargs):
    flags = [
        "-Wall",
        "-Wextra",
        "-x", "c++",
        "-std=c++17",

        "-isystem", "/usr/include/c++/8.2.1",
        "-isystem", "/usr/include/c++/8.2.1/x86_64-pc-linux-gnu",
        "-isystem", "/usr/include/c++/8.2.1/backward",
        "-isystem", "/usr/local/include",
        "-isystem", "/usr/include",

        "-I", SCRIPT_DIR + "/deps/argo/include",

        # TODO: better solution: find closest CMakeLists.txt
        "-I", os.path.dirname(kwargs["filename"]) + "/include",
    ]

    return {"flags": flags}
