project(oxf)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Release")

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(system linux)
    set(THIRDPARTY "/home/vmns/3rdparty")
    set(BOOST_DATE_TIME_LIB libboost_date_time.a)
    set(BOOST_THREAD_LIB libboost_thread.a)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(system win)    
    set(THIRDPARTY "D:/work/projects/3rdparty")
    set(BOOST_DATE_TIME_LIB libboost_date_time-vc141-mt-x64-1_75.lib)
    set(BOOST_THREAD_LIB libboost_thread-vc141-mt-x64-1_75.lib)
endif ()

#加载自定义模块
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#设置库文件路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#设置可执行程序路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#设置子目录

set(platform x64)

#安装目录
set(INSTALL_PATH_LIB ${THIRDPARTY}/${CMAKE_PROJECT_NAME}/lib/${platform})
set(INSTALL_PATH_INCLUDE ${THIRDPARTY}/${CMAKE_PROJECT_NAME}/include)

if(WIN32)
    set(LINK_LIB_LIST WS2_32 Iphlpapi shlwapi)
else()
    set(LINK_LIB_LIST)
endif()



aux_source_directory(src SRC_LIST)
#安装头文件至系统目录
install(DIRECTORY src DESTINATION ${INSTALL_PATH_INCLUDE} FILES_MATCHING PATTERN "*.h")


#boost
set(BOOST_ROOT_PATH ${THIRDPARTY}/boost)
set(BOOST_INCLUDE_PATH ${BOOST_ROOT_PATH}/include)
set(BOOST_LIB_PATH ${BOOST_ROOT_PATH}/lib/${system}/${platform})
INCLUDE_DIRECTORIES(${BOOST_INCLUDE_PATH})
link_directories(${BOOST_LIB_PATH})
list(APPEND LINK_LIB_LIST ${BOOST_DATE_TIME_LIB} ${BOOST_THREAD_LIB})

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  /Zc:sizedDealloc- /MP /wd4430")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} /MDd /Od /ZI /DEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} /MD /O2")
else (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fpermissive -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")
endif (WIN32)

if (WIN32)
    #防止Windows.h包含Winsock.h
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

#打印库文件
message(STATUS "将链接依赖库:${LINK_LIB_LIST}")
#引用头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (NOT WIN32)
    add_compile_options(-Wno-deprecated-declarations)
    add_compile_options(-Wno-predefined-identifier-outside-function)
endif ()

#编译动态库
#if(NOT IOS AND NOT ANDROID)
#    add_library(${CMAKE_PROJECT_NAME}_shared SHARED ${SRC_LIST})
#    target_link_libraries(${CMAKE_PROJECT_NAME}_shared ${LINK_LIB_LIST})
#    set_target_properties(${CMAKE_PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}")
#    install(TARGETS ${CMAKE_PROJECT_NAME}_shared  ARCHIVE DESTINATION ${INSTALL_PATH_LIB} LIBRARY DESTINATION ${INSTALL_PATH_LIB})
#endif()

#编译静态库
add_library(${CMAKE_PROJECT_NAME}_static STATIC ${SRC_LIST})

set_target_properties(${CMAKE_PROJECT_NAME}_static PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}")
#安装静态库至系统目录
install(TARGETS ${CMAKE_PROJECT_NAME}_static ARCHIVE DESTINATION ${INSTALL_PATH_LIB})

add_subdirectory(test)

