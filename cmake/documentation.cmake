# Build Documentation
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

# Build documentation option
# 
# This option will build the html documentation and doxygen
# documentation
#
# usage: cmake -DBUILD_DOCS=ON ..
#  
option(BUILD_DOCS "Build the documentation" OFF)

if(BUILD_DOCS)

    find_package(Doxygen)

	if (DOXYGEN_FOUND)
	    # set input and output files
	    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
	    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	    # request to configure the file
	    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
	    message("Doxygen build started")

	    # note the option ALL which allows to build the docs together with the application
	    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating documentation with Doxygen"
            VERBATIM )
	else (DOXYGEN_FOUND)
        message(WARNING "No Doxygen found. Documentation target not available.")
	endif (DOXYGEN_FOUND)

    find_package(Sphinx REQUIRED)
    if(Sphinx_FOUND)
        set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/_build")
        
        # Sphinx cache with pickled ReST documents
        set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_doctrees")
        
        # HTML output directory
        set(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/html")
        
        add_custom_target(xgl_docs_html ALL
            ${SPHINX_EXECUTABLE}
                -q -b html
                -c "${CMAKE_CURRENT_SOURCE_DIR}/doc/guide"
                -d "${SPHINX_CACHE_DIR}"
                "${CMAKE_CURRENT_SOURCE_DIR}/doc/guide"
                "${SPHINX_HTML_DIR}"
            COMMENT "Building HTML documentation with Sphinx")

    else()
        message(WARNING "No Sphinx found. Documentation target not available.")
    endif()

endif(BUILD_DOCS)