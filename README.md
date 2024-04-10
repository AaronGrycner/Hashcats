Hashcats

Hashcats is a robust software project focusing on networked hash computation. It combines efficient logging mechanisms with advanced hashing functionalities to offer a comprehensive solution for distributed hash computation tasks.
Features

    Logging: Integrated logging system for detailed event tracking and debugging.
    Distributed Processing: Utilizes network nodes for distributed hash computation.
    Modular Design: The project is structured to allow easy expansion and customization.

Structure

The project is organized into several key directories:

    include/: Contains all header files necessary for the project.
    src/: Houses the main application source files including implementation details for messaging and node management.
    test/: Includes scripts and resources for testing the functionalities of the application.

Key Components

    Logger: Implemented in src/Logger.cpp for detailed runtime information.
    Messaging and Nodes: Modules found in src/messaging and src/nodes that handle inter-node communication and node behavior respectively.

Getting Started
Prerequisites

Ensure you have CMake installed to build the project:

bash

sudo apt-get install cmake

Building the Project

To build Hashcats, run the following commands in the root directory:

bash

mkdir build && cd build
cmake ..
make

This will compile the project and generate the executable.
Running Tests

To run tests, navigate to the test/ directory and execute the scripts:

bash

./test.sh

Contributing

Contributions are welcome! Please feel free to fork the repository, make changes, and submit pull requests. For major changes, please open an issue first to discuss what you would like to change.
License

This project is licensed under the MIT License - see the LICENSE file for details.
