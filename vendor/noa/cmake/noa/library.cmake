function(noa_library)
  cmake_parse_arguments(NOA_LIBRARY ""
    "NAMESPACE;PROJECT;NAME;FOLDER" "PRIVATE_HEADERS;SOURCES" ${ARGN})

  if(NOT NOA_LIBRARY_NAMESPACE)
    message(FATAL_ERROR "You must pass the namespace name using the NAMESPACE option")
  endif()
  if(NOT NOA_LIBRARY_PROJECT)
    message(FATAL_ERROR "You must pass the project name using the PROJECT option")
  endif()
  if(NOT NOA_LIBRARY_NAME)
    message(FATAL_ERROR "You must pass the library name using the NAME option")
  endif()
  if(NOT NOA_LIBRARY_FOLDER)
    message(FATAL_ERROR "You must pass the folder name using the FOLDER option")
  endif()

  set(INCLUDE_PREFIX "include/${NOA_LIBRARY_NAMESPACE}/${NOA_LIBRARY_PROJECT}")
  set(PUBLIC_HEADER "${INCLUDE_PREFIX}/${NOA_LIBRARY_NAME}.h")

  if(NOA_LIBRARY_SOURCES)
    set(ABSOLUTE_PRIVATE_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/${NOA_LIBRARY_NAME}_export.h")
    foreach(private_header IN LISTS NOA_LIBRARY_PRIVATE_HEADERS)
      list(APPEND ABSOLUTE_PRIVATE_HEADERS "${INCLUDE_PREFIX}/${NOA_LIBRARY_NAME}_${private_header}")
    endforeach()
  else()
    set(ABSOLUTE_PRIVATE_HEADERS)
  endif()

  if(NOA_LIBRARY_SOURCES)
    add_library(${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
      ${PUBLIC_HEADER} ${ABSOLUTE_PRIVATE_HEADERS} ${NOA_LIBRARY_SOURCES})
  else()
    add_library(${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME} INTERFACE
      ${PUBLIC_HEADER} ${ABSOLUTE_PRIVATE_HEADERS})
  endif()

  add_library(${NOA_LIBRARY_NAMESPACE}::${NOA_LIBRARY_PROJECT}::${NOA_LIBRARY_NAME}
    ALIAS ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME})

  if(NOA_LIBRARY_SOURCES)
    target_include_directories(${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
      PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
  else()
    target_include_directories(${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
      INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
  endif()

  if(NOA_LIBRARY_SOURCES)
    set_target_properties(${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
      PROPERTIES
        OUTPUT_NAME ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
        PUBLIC_HEADER "${PUBLIC_HEADER}"
        PRIVATE_HEADER "${ABSOLUTE_PRIVATE_HEADERS}"
        EXPORT_NAME "${NOA_LIBRARY_PROJECT}::${NOA_LIBRARY_NAME}"
        FOLDER "${NOA_LIBRARY_FOLDER}")
  else()
    set_target_properties(${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
      PROPERTIES
        OUTPUT_NAME ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
        PUBLIC_HEADER "${PUBLIC_HEADER}"
        PRIVATE_HEADER "${ABSOLUTE_PRIVATE_HEADERS}"
        FOLDER "${NOA_LIBRARY_FOLDER}")
  endif()

  if(NOA_LIBRARY_SOURCES)
    include(GenerateExportHeader)
    generate_export_header(${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
      EXPORT_FILE_NAME ${NOA_LIBRARY_NAME}_export.h)
    set_target_properties(${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
      PROPERTIES
        SOVERSION "${PROJECT_VERSION_MAJOR}"
        VERSION "${PROJECT_VERSION}")

    # To find the generated files
    target_include_directories(${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
      PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")
  endif()
endfunction()

function(noa_library_install)
  cmake_parse_arguments(NOA_LIBRARY "" "NAMESPACE;PROJECT;NAME" "" ${ARGN})

  if(NOT NOA_LIBRARY_NAMESPACE)
    message(FATAL_ERROR "You must pass the namespace name using the NAMESPACE option")
  endif()
  if(NOT NOA_LIBRARY_PROJECT)
    message(FATAL_ERROR "You must pass the project name using the PROJECT option")
  endif()
  if(NOT NOA_LIBRARY_NAME)
    message(FATAL_ERROR "You must pass the library name using the NAME option")
  endif()

  include(GNUInstallDirs)
  install(TARGETS ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
    EXPORT ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${NOA_LIBRARY_NAMESPACE}/${NOA_LIBRARY_PROJECT}"
      COMPONENT ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_dev
      PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${NOA_LIBRARY_NAMESPACE}/${NOA_LIBRARY_PROJECT}"
      COMPONENT ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_dev
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
      COMPONENT ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      COMPONENT ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}
      NAMELINK_COMPONENT ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_dev
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      COMPONENT ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_dev)
  install(EXPORT ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_${NOA_LIBRARY_NAME}
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${NOA_LIBRARY_PROJECT}"
    NAMESPACE ${NOA_LIBRARY_NAMESPACE}::
    COMPONENT ${NOA_LIBRARY_NAMESPACE}_${NOA_LIBRARY_PROJECT}_dev)
endfunction()
