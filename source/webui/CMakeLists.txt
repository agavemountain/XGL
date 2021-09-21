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

SET(WT_PROJECT_SOURCE
    src/main.cpp
    src/XGLApplication.cpp
)

SET(WT_PROJECT_TARGET XGL.wt)

ADD_EXECUTABLE(${WT_PROJECT_TARGET} ${WT_PROJECT_SOURCE})
TARGET_INCLUDE_DIRECTORIES(${WT_PROJECT_TARGET} PRIVATE include)
TARGET_LINK_LIBRARIES(${WT_PROJECT_TARGET} ${WT_CONNECTOR} wt)

INCLUDE_DIRECTORIES(/usr/local/include/Wt)