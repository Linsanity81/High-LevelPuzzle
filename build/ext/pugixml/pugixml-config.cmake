
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was pugixml-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

####################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/pugixml-targets.cmake")

# If the user is not requiring 1.11 (either by explicitly requesting an older
# version or not requesting one at all), provide the old imported target name
# for compatibility.
if (NOT DEFINED PACKAGE_FIND_VERSION OR PACKAGE_FIND_VERSION VERSION_LESS "1.11")
  add_library(pugixml INTERFACE IMPORTED)
  target_link_libraries(pugixml INTERFACE pugixml::pugixml)
endif ()
