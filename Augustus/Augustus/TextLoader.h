#pragma once

#include <string>
#include <vector>

class TextFileManipulator
{
public:
	static std::vector<std::string> LoadFile(std::string p_file);
	static void WriteFile(std::string p_file, const std::vector<std::string> &p_data);
	static bool FileExists(std::string p_file);
};