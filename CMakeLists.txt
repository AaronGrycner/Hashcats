cmake_minimum_required(VERSION 3.5)
project(Hashcats)

set(CMAKE_CXX_STANDARD 23)

# Find MPI
find_package(MPI REQUIRED)

add_executable(Hashcats src/main.cpp src/Nodes/Master.cpp src/Nodes/Apprentice.cpp src/Nodes/Node.cpp
        include/FileData/FileData.h
        src/FileData/FileData.cpp

        include/Logger/Logger.h
        src/Log/Logger.cpp

        src/Messages/MessageFactory.cpp
        include/Messages/MessageFactory.h

        include/Messages/Messages.h

        src/Messages/Messenger.cpp
        include/Messages/Messenger.h

        include/Nodes/Apprentice.h
        src/Nodes/Apprentice.cpp

        include/Nodes/Master.h
        src/Nodes/Master.cpp

        include/Nodes/Node.h
        src/Nodes/Node.cpp

        test/test.h

        include/utils.h
)

# Include directories for the target
target_include_directories(Hashcats PRIVATE
        include
        include/FileData
        include/Messages
        include/Nodes
        include/Logger
        ${MPI_CXX_INCLUDE_PATH}
)

# Link with MPI libraries
target_link_libraries(Hashcats ${MPI_CXX_LIBRARIES})
