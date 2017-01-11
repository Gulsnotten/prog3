#include "stdafx.h"
#include "TextLoader.h"

#include <iostream>
#include <fstream>

std::vector<std::string> TextFileManipulator::LoadFile(std::string p_file)
{
	// help from cpp tutorial
	// http://www.cplusplus.com/doc/tutorial/files/

	std::vector<std::string> loadedText;
	loadedText.clear();

	std::ifstream file(p_file);

	assert(file.is_open());

	std::string line;
	while (std::getline(file, line))
	{
		loadedText.push_back(line);
	}
	file.close();

	return loadedText;
}

void TextFileManipulator::WriteFile(std::string p_file, const std::vector<std::string> &p_data)
{
	std::ofstream file;
	file.open(p_file);

	assert(file.is_open());

	//file.clear();

	int i = 0;
	for (auto s : p_data) {
		file << s;
		i++;
		if (i < p_data.size()) {
			file << '\n';
		}
	}

	file.close();
}

bool TextFileManipulator::FileExists(std::string p_file)
{
	std::ifstream file(p_file);
	return file.good();
}
