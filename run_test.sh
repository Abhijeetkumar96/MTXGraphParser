#!/bin/bash

# Define the directory containing .mtx files
DIRECTORY="/home/graphwork/cs22s501/datasets/"

# Loop through all .mtx files in the specified directory
for file in "$DIRECTORY"*.mtx; do
    echo "Processing $file..."
    ./mtxToEdgelist "$file"
done
