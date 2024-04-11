cmake_minimum_required(VERSION 3.5)
project(Hashcats)

set(CMAKE_CXX_STANDARD 23)

# Find MPI
find_package(MPI REQUIRED)

# Include MPI headers
include_directories(${MPI_CXX_INCLUDE_PATH} ./include include/Hashcats/nodes include/Hashcats/messaging ./test ./include/Hashcats ./include/Hashcats/Log)

add_executable(Hashcats src/main.cpp src/nodes/Master.cpp src/nodes/Apprentice.cpp src/nodes/Node.cpp
        test/test.h
        include/Hashcats/messaging/Message.h
        src/messaging/Message.cpp
        include/Hashcats/utils.h
        include/Hashcats/Log/Logger.h
        include/Hashcats/Log/Logger.h
        include/Hashcats/Exceptions.h
        include/Hashcats/init/init.h
        include/Hashcats/init/network_check.h
        include/Hashcats/init/ssh_check.h
)

# Link with MPI
target_link_libraries(Hashcats ${MPI_CXX_LIBRARIES})

# Include directories for libtins
target_include_directories(Hashcats PRIVATE ${TINS_INCLUDE_DIRS})

# Link libtins to the executable
target_link_libraries(Hashcats ${TINS_LIBRARIES})
