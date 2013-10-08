#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "png15_static" for configuration "Debug"
set_property(TARGET png15_static APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(png15_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/Users/user/Documents/Polycode/Release/Darwin/Framework/Core/Dependencies/lib/libz.a;/usr/lib/libm.dylib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libpng15d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS png15_static )
list(APPEND _IMPORT_CHECK_FILES_FOR_png15_static "${_IMPORT_PREFIX}/lib/libpng15d.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
