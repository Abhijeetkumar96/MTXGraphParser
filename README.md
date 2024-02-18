# MTXGraphParser
## Description
[MTXGraphParser] is a specialized tool designed for converting MTX (Matrix Market format) graphs into plain edge-list graphs. 
This project aims to simplify the process of handling MTX graph data, making it more accessible and usable in various applications that require edge-list formats.

## Features
MTX Graph Reading: Efficiently reads MTX graph files.
Edge-List Conversion: Converts MTX graphs to a plain edge-list format.
Graph Connectivity: Offers the feature to make the graph connected if the number of components is greater than one, ensuring a unified graph structure for further analysis or processing.

## Getting Started
### Installation
```shell
    git clone https://github.com/Abhijeetkumar96/MTXGraphParser.git
    # Navigate to the project directory
    cd MTXGraphParser-master
    # Compile the project using the make command:
    make
```
## Usage
### Convert MTX to Edge List
To convert a .mtx file to an edge list, use the following command, replacing filename.mtx with the path to your MTX file:
```shell
    ./mtxToEdgeList filename.mtx
```
This will create an edge list from the specified .mtx file.
### Checking and Restoring Number of Components
If the graph needs to be connected and the number of components is not one, use the following command to check and potentially modify the graph for connectivity. Replace filename.txt with the path to your edge list file:

```shell
    ./EdgeAdderForConnectivity filename.txt output_path/
```
### Example
Assuming you have a graph file named **myGraph.txt** and you want to save the output into a directory located at 
**home/output/**, you would run:
```shell
    ./EdgeAdderForConnectivity myGraph.txt home/output/ 
```

This command processes **myGraph.txt**, adding edges to ensure connectivity, and saves the modified graph file in the **home/output/** directory.

Make sure that the **output_path/** directory exists before running the command, or the tool may fail to save the output file. 
You can create the directory using **`mkdir -p output_path/`** if necessary.

# Future Features

## In-Place File Update

In a future release, we plan to introduce the capability to update graph files in place. This enhancement will allow users to apply modifications directly to the original file, eliminating the need for outputting to a separate file when not necessary.

### Reminder:

- This feature is under development and not yet available in the current version.
- It aims to simplify workflows by reducing the steps required to apply changes.
- Keep an eye on our release notes for updates on this and other new features.

We appreciate your patience and are excited to bring more functionalities to improve your experience with our tools.


## How to Cite
If you use MTXGraphParser in your research or project, please consider citing it. Below is the citation format:

Suggested Citation Format
In Text Reference
"... as implemented in the MTXGraphParser (Abhijeet et al., 2023)..."

Full Reference
Abhijeet kumar. 2023. "MTXGraphParser: A Tool for Converting MTX Graphs to Edge Lists and Ensuring Graph Connectivity." GitHub repository. https://github.com/Abhijeetkumar96/MTXGraphParser.

## Contributing
Contributions are welcome! Here are some ways you can contribute:

* Reporting bugs: If you find a bug, please open an issue describing the problem.
* Suggesting enhancements: Have ideas on how to make this tool better? Share them by opening an issue.
* Submitting Pull Requests: We welcome pull requests. If you've made an improvement or fixed a bug, please fork the repository, make your changes, and submit a pull request.

## Pull Request Process

1. Fork the repository and create your branch from master.
2. If you've added code, write clear, commented code and ensure it adheres to the existing style.
3. Update the README.md with details of changes, including new environment variables, exposed ports, or useful file locations.
4. Increase the version numbers in any examples files and the README.md to the new version that this Pull Request would represent. The versioning scheme we use is [SemVer](https://semver.org/) .
5. Ensure your code does not introduce any new warnings or errors.
6. Submit your pull request.

**Thank you for considering contributing to this project.**
