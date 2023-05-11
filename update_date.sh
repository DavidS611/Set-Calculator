#!/bin/bash

# Set the path to the file that will be updated
FILE=/home/david/Documents/Degree/Projects/Set-Calculator/date.txt

# Check if the file exists; if not, create it
if [ ! -f "$FILE" ]; then
    touch "$FILE"     # Create the file if it doesn't exist
fi

# Overwrite the file with the current date and time
echo "$(date)" > "$FILE"    # Overwrite the file with the current date and time

