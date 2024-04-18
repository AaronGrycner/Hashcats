cmake_minimum_required(VERSION 3.5)
project(Hashcats)

set(CMAKE_CXX_STANDARD 23)

# Find MPI
find_package(MPI REQUIRED)

# Include MPI headers
include_directories(${MPI_CXX_INCLUDE_PATH} ./include include/Hashcats/nodes include/Hashcats/messaging ./test ./include/Hashcats ./include/Hashcats/Log)

add_executable(Hashcats src/main.cpp src/nodes/Master.cpp src/nodes/Apprentice.cpp src/nodes/Node.cpp
        include/FileData/FileData.h
        src/FileData/FileData.cpp

        include/Log/Logger.h
        src/Log/Logger.cpp

        src/Messages/MessageFactory.cpp
        include/Messages/MessageFactory.h

        include/Messages/Messages.h

        src/Messages/Messenger.cpp
        include/Messages/Messenger.h

        include/nodes/Apprentice.h
        src/nodes/Apprentice.cpp

        include/nodes/Master.h
        src/nodes/Master.cpp

        include/nodes/Node.h
        src/nodes/Node.cpp

        test/test.h

        include/utils.h
)

target_include_directories(Hashcats PRIVATE
                            include
                            include/FileData
                            include/Messages
                            include/nodes
                            include/Log)

# Link with MPI
target_link_libraries(Hashcats ${MPI_CXX_LIBRARIES})