#!/bin/bash

# Define the directory containing .mtx files
DIRECTORY="/raid/graphwork/"

# Loop through all .mtx files in the specified directory
for file in "$DIRECTORY"*.txt; do
    echo "Processing $file..."
    ./EdgeAdderForConnectivity "$file"
done
