
#          Copyright Ted Middleton 2022.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.0 )
project( toolbox )

set( version 0.1.0 )

add_library( toolbox INTERFACE
    toolbox.hpp )
 
target_include_directories( toolbox
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    )
    
install( TARGETS toolbox
         EXPORT toolbox-targets
    )

install(
    FILES 
        toolbox.hpp 
    DESTINATION include
    )

 install( EXPORT toolbox-targets
         DESTINATION lib/cmake/toolbox
    )

set_property( TARGET toolbox PROPERTY VERSION ${version} )
set_property( TARGET toolbox PROPERTY SOVERSION 0 )
set_property( TARGET toolbox PROPERTY 
    INTERFACE_toolbox_MAJOR_VERSION 0 )
set_property( TARGET toolbox PROPERTY 
    COMPATIBLE_INTERFACE_STRING toolbox_MAJOR_VERSION )   

export(EXPORT toolbox-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/toolbox-targets.cmake"
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/toolbox-config-version.cmake"
    VERSION "${version}"
    COMPATIBILITY AnyNewerVersion
    )

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/toolbox-config.cmake"
    INSTALL_DESTINATION lib/cmake/toolbox
    )

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/toolbox-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/toolbox-config-version.cmake"
    DESTINATION lib/cmake/toolbox
    )
