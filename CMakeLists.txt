cmake_minimum_required(VERSION 3.5)
project(Hashcats)

set(CMAKE_CXX_STANDARD 23)

# Find MPI
find_package(MPI REQUIRED)

# Include MPI headers
include_directories(${MPI_CXX_INCLUDE_PATH} ./include include/Hashcats/nodes include/Hashcats/messaging ./test ./include/Hashcats ./include/Hashcats/Log)

add_executable(Hashcats src/main.cpp src/nodes/Master.cpp src/nodes/Apprentice.cpp src/nodes/Node.cpp
        test/test.h
        include/messaging/Messages.h
        include/utils.h
        include/Log/Logger.h
        src/Log/Logger.cpp
        include/Log/Logger.h
        include/File/File.h
        src/messaging/MessageFactory.cpp
        include/messaging/MessageFactory.h
        src/messaging/Messages.cpp
        src/messaging/Messenger.cpp
        include/messaging/Messenger.h
)

target_include_directories(Hashcats PRIVATE
                            include
                            include/messaging
                            include/nodes
                            include/Log)

# Link with MPI
target_link_libraries(Hashcats ${MPI_CXX_LIBRARIES})