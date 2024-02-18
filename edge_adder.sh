#!/bin/bash

# Update to the directory containing your .txt files
DIRECTORY="/home/graphs/"
# Update the output directory to store the processed files
OUTPUT_DIR="/home/graphs/datasets/"

# Loop through all .txt files in the specified directory
for file in "$DIRECTORY"*.txt; do
    echo "Processing $file..."
    ./EdgeAdderForConnectivity "$file" "$OUTPUT_DIR"
done
