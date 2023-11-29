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
    ./EdgeAdderForConnectivity filename.txt
```
This step ensures that the graph is connected by modifying the original graph if necessary when the number of components is greater than one.

##How to Cite
If you use MTXGraphParser in your research or project, please consider citing it. Below is the citation format:

Suggested Citation Format
In Text Reference
"... as implemented in the MTXGraphParser (Abhijeet et al., 2023)..."

Full Reference
Abhijeet kumar. 2023. "MTXGraphParser: A Tool for Converting MTX Graphs to Edge Lists and Ensuring Graph Connectivity." GitHub repository. https://github.com/Abhijeetkumar96/MTXGraphParser.

## Contributing
Contributions are welcome!