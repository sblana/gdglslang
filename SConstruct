#!/usr/bin/env python
import os
import sys

from methods import print_error


libname = "gdglslang"
projectdir = "project"

localEnv = Environment(tools=["default"], PLATFORM="")

# Build profiles can be used to decrease compile times.
# You can either specify "disabled_classes", OR
# explicitly specify "enabled_classes" which disables all other classes.
# Modify the example file as needed and uncomment the line below or
# manually specify the build_profile parameter when running SCons.

# localEnv["build_profile"] = "build_profile.json"

customs = ["custom.py"]
customs = [os.path.abspath(path) for path in customs]

opts = Variables(customs, ARGUMENTS)
opts.Update(localEnv)

Help(opts.GenerateHelpText(localEnv))

env = localEnv.Clone()

if not (os.path.isdir("godot-cpp") and os.listdir("godot-cpp")):
    print_error("""godot-cpp is not available within this folder, as Git submodules haven't been initialized.
Run the following command to download godot-cpp:

    git submodule update --init --recursive""")
    sys.exit(1)

env = SConscript("godot-cpp/SConstruct", {"env": env, "customs": customs, "api_version": "4.7"})

env.Append(CCFLAGS=["-Wall", "-Wextra", "-Werror"])
env.Append(CCFLAGS=["-Wno-unused-parameter", "-Wno-sign-compare"])

env.Append(CPPPATH=["src/"])
env.Append(CPPPATH=["./"])
env.Append(CPPPATH=["glslang/"])
sources =      Glob("src/*.cpp")
sources.append(Glob("src/*/*.cpp"))
sources.append(Glob("src/*/*/*.cpp"))

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

# cmake -B ../glslang_building/build_dir/ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$(pwd)/../glslang_building/install" -DENABLE_GLSLANG_BINARIES=OFF -DENABLE_PCH=OFF -DGLSLANG_TESTS=OFF
env.Append(LIBPATH=["./glslang_building/install/lib/"])
env.Append(LIBS=["glslang-default-resource-limits"])
env.Append(LIBS=["glslang"])
env.Append(LIBS=["SPIRV-Tools-diff"])
env.Append(LIBS=["SPIRV-Tools-link"])
env.Append(LIBS=["SPIRV-Tools-lint"])
env.Append(LIBS=["SPIRV-Tools-opt"])
env.Append(LIBS=["SPIRV-Tools-reduce"])
env.Append(LIBS=["SPIRV-Tools"])


# .dev doesn't inhibit compatibility, so we don't need to key it.
# .universal just means "compatible with all relevant arches" so we don't need to key it.
suffix = env['suffix'].replace(".dev", "").replace(".universal", "")

lib_filename = "{}{}{}{}".format(env.subst('$SHLIBPREFIX'), libname, suffix, env.subst('$SHLIBSUFFIX'))

library = env.SharedLibrary(
    "bin/{}/{}".format(env['platform'], lib_filename),
    source=sources
)

copy = env.Install("{}/addons/{}/bin/{}/".format(projectdir, libname, env["platform"]), library)

default_args = [library, copy]
Default(*default_args)