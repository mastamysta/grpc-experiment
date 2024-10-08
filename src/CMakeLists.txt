add_executable(server serv.cpp)
target_link_libraries(server proto-objects)

add_executable(client client.cpp)
target_link_libraries(client proto-objects)
