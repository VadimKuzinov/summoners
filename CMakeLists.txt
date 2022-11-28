cmake_minimum_required (VERSION 3.8)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

project(summoners)

set(CMAKE_CXX_STANDARD 20)
set(SRC server.cpp server/Game.cpp server/Server.cpp server/Player.cpp)
add_subdirectory(src)

add_executable(server ${SRC})
target_link_libraries(server game wsock32 ws2_32)

set(PROJECT_DIR ${CMAKE_BINARY_DIR}/../../../)

set(SDL2_INCLUDE_DIR ${PROJECT_DIR}/include/SDL2/include)
set(SDL2_LIBRARY_DIR ${PROJECT_DIR}/include/SDL2/lib/x64)

set(SDL2main_INCLUDE_DIR ${PROJECT_DIR}/include/SDL2/include)
set(SDL2main_LIBRARY_DIR ${PROJECT_DIR}/include/SDL2/lib/x64)

set(SDL2ttf_INCLUDE_DIR ${PROJECT_DIR}/include/SDL2_ttf/include)
set(SDL2ttf_LIBRARY_DIR ${PROJECT_DIR}/include/SDL2_ttf/lib/x64)


add_library(SDL2 SHARED IMPORTED)
set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_LIBRARY_DIR}/SDL2.dll)
set_property(TARGET SDL2 PROPERTY IMPORTED_IMPLIB ${SDL2_LIBRARY_DIR}/SDL2.lib)

add_library(SDL2main SHARED IMPORTED)
set_property(TARGET SDL2main PROPERTY IMPORTED_IMPLIB ${SDL2_LIBRARY_DIR}/SDL2main.lib)

add_library(SDL2ttf SHARED IMPORTED)
set_property(TARGET SDL2ttf PROPERTY IMPORTED_LOCATION ${SDL2ttf_LIBRARY_DIR}/SDL2_ttf.dll)
set_property(TARGET SDL2ttf PROPERTY IMPORTED_IMPLIB ${SDL2ttf_LIBRARY_DIR}/SDL2_ttf.lib)


add_executable(client client.cpp client/Client.cpp client/Drawer.cpp client/MapWidget.cpp client/MenuWidget.cpp client/Point.cpp client/SerializeWidget.cpp)
target_include_directories(client PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(client PUBLIC ${SDL2ttf_INCLUDE_DIR})

target_link_libraries(client wsock32 ws2_32 SDL2main SDL2 SDL2ttf)

add_custom_command ( TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2> $<TARGET_FILE_DIR:client>
)

add_custom_command ( TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2ttf> $<TARGET_FILE_DIR:client>
)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(testing exampletest.cpp)
target_link_libraries(testing gtest_main game)
add_test(NAME nametest COMMAND testing)