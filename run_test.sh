#!/bin/bash

# Update to the directory containing .mtx files
DIRECTORY="/home/datasets/mtx/"

# Loop through all .mtx files in the specified directory
for file in "$DIRECTORY"*.mtx; do
    echo "Processing $file..."
    ./mtxToEdgelist "$file"
done
