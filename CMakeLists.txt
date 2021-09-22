# XGL CMake file
#
# Copyright (C) 2021  IO Industrial Holdings, LLC
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
cmake_minimum_required(VERSION 3.4)
project (XGL VERSION "0.0.0")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Generate version file based on project version
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/templates/version.h.in 
    ${CMAKE_CURRENT_SOURCE_DIR}/source/xgllib/include/XGLVersion.h
    )

# Documentation generation
include(documentation)

set (WT_CONNECTOR "wthttp" CACHE STRING "Connector used (wthttp or wtfcgi)")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/source/xgllib/include)
add_subdirectory(source)