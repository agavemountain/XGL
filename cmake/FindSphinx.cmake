# FindSphinx.cmake
#
# This is part of the XGL software project.
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

include(FindPackageHandleStandardArgs)

# We are likely to find Sphinx near the Python interpreter
find_package(PythonInterp)
if(PYTHONINTERP_FOUND)
    get_filename_component(_PYTHON_DIR "${PYTHON_EXECUTABLE}" DIRECTORY)
    set(
        _PYTHON_PATHS
        "${_PYTHON_DIR}"
        "${_PYTHON_DIR}/bin"
        "${_PYTHON_DIR}/Scripts")
endif()

find_program(
    SPHINX_EXECUTABLE
    NAMES sphinx-build sphinx-build.exe
    HINTS ${_PYTHON_PATHS})
mark_as_advanced(SPHINX_EXECUTABLE)

find_package_handle_standard_args(Sphinx DEFAULT_MSG SPHINX_EXECUTABLE)


# If finding Sphinx fails, there is no use in defining
# add_sphinx_document, so return early
if(NOT Sphinx_FOUND)
    return()
endif()

