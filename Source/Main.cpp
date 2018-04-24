// Newspaper Dissector
// M. H. Beals (2018) v.0.1.8 [Software]

// MIT License
// Copyright(c) 2018 M. H. Beals
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// // to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>


// Permanent variables
std::string workingDirectory = "";
std::string typeInput="";
std::string edgesOutput;
std::string nodesOutput;
std::string inputFile;
std::string filterFile;
int weight;

// Data Structs for Various Data Vectors
struct unit {
	std::vector <int> connections;
};
unit emptyUnit;

// Data Vectors 
std::vector <std::string> buffer; // Input Buffer
std::vector <std::string> names; // Unique Names
std::vector <std::string> publications; // Unique Publications
std::vector <std::string> filterList; // List of Desired Publications
std::vector <struct unit> personPublicationConnections; // MultiArray for Persons & their Publications
std::vector <struct unit> publicationPersonConnections; // MultiArray for Publications & their Persons
std::vector <struct unit> networks; // MultiArray for Persons & other Persons

									// Utility (temporary) Variables
int publicationHolder;
int nameHolder;


void loadFile()
{
	// Load files
	std::ifstream input(inputFile);
	std::ifstream inputFilter(filterFile);

	// Create Filer List
	while (inputFilter)
	{
		std::string line;
		for (std::string line; std::getline(inputFilter, line, '\n');)
		{
			filterList.push_back(line);
		}
	}

	// Create Filtered Input List
	while (input)
	{

		// Separate by line
		std::string line;
		for (std::string line; std::getline(input, line, '\n');)
		{

			// Separate by field
			std::istringstream iline(line);
			while (iline)
			{
				std::string field;
				std::getline(iline, field, '\t');
				buffer.push_back(field);
			}

			// If it is in the filter list
			if (std::find(filterList.begin(), filterList.end(), buffer[0]) != filterList.end())
			{
				// If it is an exisiting publicaiton
				if (std::find(publications.begin(), publications.end(), buffer[0]) != publications.end())
				{
					// Select relevant publication ID
					publicationHolder = std::distance(publications.begin(), find(publications.begin(), publications.end(), buffer[0]));
				}
				// If it is a new publication
				else
				{
					// Create new publicaiton ID 
					publications.push_back(buffer[0]);
					publicationHolder = publications.size() - 1;
					publicationPersonConnections.push_back(emptyUnit);
				}

				// If it is an exisiting name
				if (std::find(names.begin(), names.end(), buffer[1]) != names.end())
				{
					// Find name ID
					nameHolder = std::distance(names.begin(), find(names.begin(), names.end(), buffer[1]));
				}
				// If it is a new name
				else
				{
					// Create name ID
					names.push_back(buffer[1]);
					nameHolder = names.size() - 1;
					personPublicationConnections.push_back(emptyUnit);
				}

				// Add publication to name in publicationPersonConnections vector and vice versa
				personPublicationConnections[nameHolder].connections.push_back(publicationHolder);
				publicationPersonConnections[publicationHolder].connections.push_back(nameHolder);

			}
			// Reset buffer for next line 
			buffer.clear();
		}
	}
}

void createNetworks()
{
	// For every unique name
	for (int i = 0; i < names.size(); i++)
	{
		// Create a network entry
		networks.push_back(emptyUnit);

		// For every publicaiton listed in that unique name
		for (int j = 0; j < personPublicationConnections[i].connections.size(); j++)
		{

			// Go through that publication's person connections
			int currentPublication = personPublicationConnections[i].connections[j];
			for (int k = 0; k < publicationPersonConnections[currentPublication].connections.size(); k++)
			{
				int currentConnection = publicationPersonConnections[currentPublication].connections[k];

				// If the person isn't a self-connection, add it to the network. 
				// It's okay to have duplicates, they'll just add weight to the connection
				if (currentConnection != i)
				{
					networks[i].connections.push_back(currentConnection);
				}
			}
		}
	}
}

void createEdgeAndNodeLists()
{
	// Go through all the unique names
	std::string edgeLine = "Source;Target;Weight\n";
	for (int i = 0; i < names.size(); i++)
	{
		// Go through all the other names
		for (int j = i + 1; j < names.size(); j++)
		{
			weight = 0;

			// And add 1 to the weight for each match / connection
			for (int k = 0; k < networks[i].connections.size(); k++)
			{
				if (networks[i].connections[k] == j)
				{
					weight++;
				}
			}

			// If it has at least one coonnection, add it to the edge list
			if (weight != 0)
			{
				edgeLine = edgeLine + std::to_string(i + 1) + ";" + std::to_string(j + 1) + ";" + std::to_string(weight) + "\n";
			}
		}
	}

	std::ofstream edgeFile(edgesOutput);
	edgeFile << edgeLine; // save edge data to file
	edgeFile.close();

	// Go through each unique name and add it to the node list
	std::string nodeLine = "Label;ID\n";
	for (int i = 0; i < names.size(); i++)
	{
		nodeLine = nodeLine + names[i] + ";" + std::to_string(i + 1) + "\n";
	}

	std::ofstream nodeFile(nodesOutput);
	nodeFile << nodeLine; // save node data to file
	nodeFile.close();

}

int main()
{

	// Ask relevant questions for input and out files
	std::cout << "What is the full path of your working directory (where your input and filer files are)? \n";
	std::cout << "For example: c:\\users\\me\\files\\ \n";
	std::cin >> workingDirectory;

	std::cout << "Are you using the (F)ull list or the (C)reator/Contributor list? \n";
	std::cin >> typeInput;
	if (typeInput == "F" || typeInput == "f" || typeInput == "C" || typeInput == "c"){}
	else
	{
		std::cout << "I didn't understand that. Please use F or C \n";
		std::cin >> typeInput;
	}

	// Update file locations
	edgesOutput = workingDirectory + "ATLEdges.csv";
	nodesOutput = workingDirectory + "ATLNodes.csv";
	if (typeInput == "F" || typeInput == "f")
	{
		inputFile = workingDirectory + "ATLNamesList.txt";
	}
	else
	{
		inputFile = workingDirectory + "ATLNamesListCreator.txt";
	}
	filterFile = workingDirectory + "ATLFilterList.txt";

	std::cout << "\nThank you! Please wait for me to process your edges & nodes!\n";

	// Run programme
	loadFile();
	createNetworks();
	createEdgeAndNodeLists();

	return 0;
}

