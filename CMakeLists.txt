cmake_minimum_required(VERSION 3.5.0)
project(thun VERSION 0.1.0 LANGUAGES C CXX)


# include(CTest)
# enable_testing()


INCLUDE_DIRECTORIES(include)


AUX_SOURCE_DIRECTORY(src DIR_SRCS)
SET(CMAKE_CXX_STANDARD 11)

SET(SOURCE_FILES ${DIR_SRCS})

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})




set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_package(Boost 1.82.0 REQUIRED COMPONENTS  program_options   )
target_link_libraries (${PROJECT_NAME} PRIVATE
    pthread 
    Boost::boost 
    Boost::program_options
    # Boost::asio
) 

find_package(libuv CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:libuv::uv_a>,libuv::uv_a,libuv::uv>)

find_package(kcp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE kcp::kcp)

# target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost Boost::asio)
