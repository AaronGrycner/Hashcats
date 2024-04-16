scp ../cmake-build-debug/Hashcats aaron@192.168.4.63:/home/aaron/CLionProjects/Hashcats/cmake-build-debug
ssh aaron@192.168.4.63 "chmod 755 /home/aaron/CLionProjects/Hashcats/cmake-build-debug"
mpirun --hostfile /home/aaron/CLionProjects/Hashcats/Hostfile/hostfile -np 2 /home/aaron/CLionProjects/Hashcats/cmake-build-debug/Hashcats