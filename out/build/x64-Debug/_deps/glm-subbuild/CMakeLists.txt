# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.30.5-msvc23)

# Reject any attempt to use a toolchain file. We must not use one because
# we could be downloading it here. If the CMAKE_TOOLCHAIN_FILE environment
# variable is set, the cache variable will have been initialized from it.
unset(CMAKE_TOOLCHAIN_FILE CACHE)
unset(ENV{CMAKE_TOOLCHAIN_FILE})

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(glm-populate NONE)


# Pass through things we've already detected in the main project to avoid
# paying the cost of redetecting them again in ExternalProject_Add()
set(GIT_EXECUTABLE [==[C:/Users/s404510/AppData/Local/Programs/Git/cmd/git.exe]==])
set(GIT_VERSION_STRING [==[2.50.1.windows.1]==])
set_property(GLOBAL PROPERTY _CMAKE_FindGit_GIT_EXECUTABLE_VERSION
  [==[C:/Users/s404510/AppData/Local/Programs/Git/cmd/git.exe;2.50.1.windows.1]==]
)


include(ExternalProject)
ExternalProject_Add(glm-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/g-truc/glm" "EXTERNALPROJECT_INTERNAL_ARGUMENT_SEPARATOR"
                    SOURCE_DIR          "C:/Users/s404510/Documents/GitHub/wuehansGameJam/out/build/x64-Debug/_deps/glm-src"
                    BINARY_DIR          "C:/Users/s404510/Documents/GitHub/wuehansGameJam/out/build/x64-Debug/_deps/glm-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


