add_executable(01_asio_timeout main.cpp)

find_package(asio CONFIG REQUIRED)

target_link_libraries(01_asio_timeout PRIVATE asio::asio)