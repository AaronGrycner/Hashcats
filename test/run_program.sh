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

# Initialize a counter for valid hosts
valid_hosts=1

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
        ((valid_hosts++))  # Increment the count of valid hosts
    else
        echo "Failed to copy to ${HOST}, continuing to next..."
        # Optionally check directory existence and permissions
        ssh "${USERNAME}@${HOST}" "ls -ld ${REMOTE_PATH%/*} && ls -l ${REMOTE_PATH}"
    fi
done < "$HOSTFILE"

echo "Detected $valid_hosts valid hosts. Starting the MPI program execution..."
# Run the MPI program using the counted number of valid hosts
mpirun --hostfile "$HOSTFILE" -np "$valid_hosts" "$REMOTE_PATH"

echo "Script completed."
