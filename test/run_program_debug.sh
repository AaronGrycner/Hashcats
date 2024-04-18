#!/bin/bash

# The MPI hostfile path
HOSTFILE="../Hostfile/hostfile"

# The local path to the compiled MPI program
MPI_PROGRAM="../cmake-build-debug/Hashcats"

# The destination path on the remote machines where the MPI program should be copied
REMOTE_PATH="/home/aaron/CLionProjects/Hashcats/cmake-build-debug/Hashcats"

# Username for the SSH/SCP commands
USERNAME="aaron"

echo "Starting the distribution of the MPI program..."

# Read lines from the hostfile. The addition of a delimiter check ensures the last line is processed.
while IFS= read -r line || [[ -n "$line" ]]; do
    # Extract the hostname, ignoring lines that might include slots and comments
    HOST=$(echo $line | grep -v '^#' | awk '{print $1}')

    if [[ -z "$HOST" ]]; then
        echo "Invalid or commented line detected, skipping: $line"
        continue
    fi

    echo "Attempting to copy MPI program to $HOST..."
    # Use SCP to copy the MPI program to each host
    if scp "$MPI_PROGRAM" "${USERNAME}@${HOST}:${REMOTE_PATH}"; then
        echo "Successfully copied to ${HOST}."
    else
        echo "Failed to copy to ${HOST}, continuing to next..."
        # Optionally check directory existence and permissions
        ssh "${USERNAME}@${HOST}" "ls -ld ${REMOTE_PATH%/*} && ls -l ${REMOTE_PATH}"
    fi
done < "$HOSTFILE"

echo "Starting the MPI program execution with GDB..."
# Run the MPI program with each process under GDB
mpirun --hostfile "$HOSTFILE" -np 2 xterm -e gdb --args "$REMOTE_PATH"

echo "Script completed."
