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

message("BUILDING libxgllib.")
SET(XGL_LIB_SOURCE
    src/accounting/payroll/PayPeriods.cpp
    src/db/DBSession.cpp
    src/db/User.cpp
    )

ADD_LIBRARY(xgllib ${XGL_LIB_SOURCE})
TARGET_LINK_LIBRARIES(xgllib wt wtdbo wtdbosqlite3)

add_subdirectory(unittest)