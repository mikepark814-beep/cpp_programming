file(GLOB LAB_SUBDIRS CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "q*" "c*" "lab*")

foreach(lab_dir IN LISTS LAB_SUBDIRS)
    set(lab_cmake "${CMAKE_CURRENT_SOURCE_DIR}/${lab_dir}/CMakeLists.txt")
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${lab_dir}" AND EXISTS "${lab_cmake}")
        add_subdirectory("${lab_dir}")
    endif()
endforeach()