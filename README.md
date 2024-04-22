Hashcats

Hashcats is an IN PROGRESS personal project that aims to allow the user to run any Hashcat cracking operation over a distributed node cluster simply by substituting "Hashcat [hashcat args]" for "Hashcats [hashcat args]". Hashcats handles distribution of wordlists, pcap files, and any other assets needed for the operation. Currently as a work in progress it is only working on the 22000 (WPA2) hashcat module and needs extensive testing, logging and exception handling added to it, however it can be used to crack WPA2 hashes with a wordlist and a .22000 capture file.

Motivation

I used MPI in the execution of this program. As it currently stands this was a a much more difficult way to accomplish distributing the Hashcat work over a local network. Using ssh to run Hashcat on each node and scp to distribute files would have been easier, however I used MPI in order to learn the system and allow greater expansion of the project as I come up with new ideas for it.

Usage

As it stands now, the program is mildly difficult to run, requiring potential modification of the run_program.sh script to match the users environment, creation of an MPI hostfile, and setup of MPI compatible nodes, with Hashcat also installed on all of them. The provided run_program.sh script handles distribution of the executable. If you are familiar with MPI this shouldn't be difficult. However eventually I will incorporate near complete setup of the environment into the program itself, allowing minimal configuration on the users part.
