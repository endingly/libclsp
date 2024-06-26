# A C++17 library for language servers.
# Copyright © 2019-2020 otreblan
#
# libclsp is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libclsp is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with libclsp.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.13.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

project(libclsp
	VERSION 0.1.3
	DESCRIPTION "A language server protocol C++ library"
	HOMEPAGE_URL "https://github.com/otreblan/libclsp"
	LANGUAGES "CXX"
)

# Without this, paths are not relative in the sources list
cmake_policy(SET CMP0076 NEW)

include(GNUInstallDirs)
include(FindPkgConfig)

# The library itself
add_library(${PROJECT_NAME})

# Version for the library symlinks
set_target_properties(${PROJECT_NAME}
	PROPERTIES
		VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION_MAJOR}
		PREFIX ""
		CXX_STANDARD 17
)

# Headers
target_include_directories(
	${PROJECT_NAME}
	PUBLIC
	$<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

# Sources list
add_subdirectory(src)

# Header installation
add_subdirectory(include)

# pkg-config file
configure_file(libclsp.pc.in
	${CMAKE_BINARY_DIR}/libclsp.pc
	@ONLY
)
install(FILES
	${CMAKE_BINARY_DIR}/libclsp.pc
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)

# Libraries
pkg_check_modules(rapidjson REQUIRED IMPORTED_TARGET RapidJSON)
include(FindBoost)

# Linking
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		Boost::headers

	INTERFACE
		PkgConfig::rapidjson
)

# Other flags
target_compile_options(${PROJECT_NAME}
	PUBLIC
		-DRAPIDJSON_HAS_STDSTRING=1
)

# Default flags
if(NOT DEFINED ENV{CXXFLAGS})
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -g -Wl,-z,defs")
endif()

include(install)