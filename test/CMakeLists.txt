aux_source_directory(. oxfTest_src_list)

add_executable(oxfTest ${oxfTest_src_list})

if(ANDROID)
    target_link_libraries(oxfTest ${CMAKE_PROJECT_NAME}_static ${LINK_LIB_LIST})
elseif(WIN32)
    target_link_libraries(oxfTest ${CMAKE_PROJECT_NAME}_static ${LINK_LIB_LIST})
else()
    target_link_libraries(oxfTest ${CMAKE_PROJECT_NAME}_static ${LINK_LIB_LIST} pthread)
endif()
