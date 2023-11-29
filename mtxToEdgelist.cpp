#include <set>
#include <omp.h>
#include <queue>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

class timer {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
        std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
        bool running = false;
    public:
        timer() {
            start_time = std::chrono::high_resolution_clock::now();
            running = true;
        }

        void stop(const std::string& str) {
            end_time = std::chrono::high_resolution_clock::now();
            running = false;
            elapsedMilliseconds(str);
        }

        void elapsedMilliseconds(const std::string& str) {
            std::chrono::time_point<std::chrono::high_resolution_clock> end;
            if(running) {
                end = std::chrono::high_resolution_clock::now();
            } else {
                end = end_time;
            }
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start_time).count();
            std::cout << str <<" took " << duration << " ms." << std::endl;
        }
};

std::string get_file_extension(const std::string& filename) {
	size_t result;
    std::string fileExtension;
    result = filename.rfind('.', filename.size() - 1);
    if(result != std::string::npos)
        fileExtension = filename.substr(result + 1);
    return fileExtension;
}

void read_mtx(const std::string& filename, std::vector<std::vector<int>>& adjlist) {
	std::ifstream inputFile(filename);
	if(!inputFile) {
		std::cerr <<"Unable to open file for reading." << std::endl;
		return;
	}
	std::string line;
	std::getline(inputFile, line);
	std::istringstream iss(line);
	std::string word;
	std::vector<std::string> words;
	
	while(iss >> word)
		words.push_back(word);

	if(words.size() != 5) {
		std::cerr <<"ERROR: mtx header is missing" << std::endl;
		return;
	}
    else 
        std::cout <<"MTX header read correctly.\n";

    std::getline(inputFile, line);
    while(line.size() > 0 && line[0]=='%') 
    	std::getline(inputFile,line);

    // Clear any error state flags
    iss.clear();

    // Set the new string for the istringstream
    iss.str(line);

    int row, col, num_of_entries;
    iss >> row >> col >> num_of_entries;

    if(row != col) {
        std::cerr<<"* ERROR: This is not a square matrix."<< std::endl;
        return;
    }
    adjlist.resize(row);
    int entry_counter = 0;
    int ridx, cidx, value;

    while(!inputFile.eof() && entry_counter < num_of_entries) {
        getline(inputFile, line);
        entry_counter++;

        if (!line.empty()) {
            iss.clear();
            iss.str(line);
            iss >> ridx >> cidx >> value;
            ridx--;
            cidx--;

            if (ridx < 0 || ridx >= row)  
            	std::cout << "sym-mtx error: " << ridx << " row " << row << std::endl;

            if (cidx < 0 || cidx >= col)  
            	std::cout << "sym-mtx error: " << cidx << " col " << col << std::endl;

            if (ridx != cidx) {
                adjlist[cidx].push_back(ridx);
                adjlist[ridx].push_back(cidx);
            }
        }
    }
}

void read_graph(const std::string& filename, std::vector<std::vector<int>>& adjlist) {
	std::string ext = get_file_extension(filename);

	if (ext == "mtx") {
		read_mtx(filename, adjlist);
	}
	else
		std::cerr <<"Unsupported file format." << std::endl;
}

void mtxToEdgeStream(const std::vector<std::set<int> >& adjlist, const std::string& name, long numEdges) {
    std::string output_path = "/raid/graphwork/";
    std::string filename = output_path + name;
    std::cout << filename << std::endl;
    std::ofstream outFile(filename);
    
    if(!outFile) {
        std::cerr <<"Unable to create output file." << std::endl;
        return;
    }
    long numVert = adjlist.size();
    outFile << numVert <<" " << numEdges << std::endl;

    for (int i = 0; i < adjlist.size(); ++i) {
       for (int adjVertex : adjlist[i]) {
            outFile << i << " " << adjVertex << std::endl;
        }
    }
}

std::string get_filename(std::string path) {
    std::filesystem::path file_path(path);

    // Extracting filename with extension
    std::string filename = file_path.filename().string();
    std::cout << "Filename with extension: " << filename << std::endl;

    // Extracting filename without extension
    std::string filename_without_extension = file_path.stem().string();
    std::cout << "Filename without extension: " << filename_without_extension << std::endl;


    return filename_without_extension + ".txt";
}

int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(false);
	if(argc < 2) {
		std::cerr <<"Usage : " << argv[0] <<"<filename> " << std::endl;
		return EXIT_FAILURE;
	}
	std::string filename = argv[1];
	std::vector<std::vector<int>> adjlist;
	timer read;
	read_graph(filename, adjlist);
	read.stop("Reading the graph");

	long degree = 0;
	for(int i = 0; i < adjlist.size(); ++i) {
	    // Add the number of edges connected to vertex i
	    degree += adjlist[i].size();
	}

	std::vector<std::set<int>> newAdj(adjlist.size());
	timer conversion;
	#pragma omp parallel for
	for (int i = 0; i < adjlist.size(); ++i) {
	    // Use std::make_move_iterator if the original vector is no longer needed
	    newAdj[i] = std::set<int>(std::make_move_iterator(adjlist[i].begin()), 
	                              std::make_move_iterator(adjlist[i].end()));
	}
	conversion.stop("Graph conversion");

	long newDegree = 0;
	for(int i = 0; i < newAdj.size(); ++i) {
	    newDegree += newAdj[i].size();
	}

    std::string name = get_filename(filename);

    timer write_timer;
    mtxToEdgeStream(newAdj, name, newDegree);
    write_timer.stop("Writing output ");

	if(newDegree == degree)
		std::cout <<"degree : " << newDegree << std::endl;
	else {
		std::cout <<"Old degree : " << degree <<std::endl;
		std::cout <<"New degree : " << newDegree <<std::endl;
	}

	return EXIT_SUCCESS;
}