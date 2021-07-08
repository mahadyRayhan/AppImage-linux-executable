add_executable(hello-world-appimage main.cpp)
target_link_libraries(hello-world-appimage)

install(TARGETS hello-world-appimage DESTINATION bin COMPONENT binaries)