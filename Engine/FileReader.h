#pragma once
#include <stdio.h>
#include <iostream>

namespace Engine
{
namespace FileReader
{
static bool readFile(const char *path, char *&buf, long &len)
{
	FILE *fp;
	fp = fopen(path, "rb");
	if (!fp)
	{
		std::cout << "ERROR: Failed to open file" << std::endl;
		return false;
	}

	fseek(fp, 0, SEEK_END);
	long length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *str = new char[length + 1];
	size_t nRead = fread(str, 1, length, fp);
	if (nRead == 0)
	{
		std::cout << "ERROR: Failed to read file" << std::endl;
		return "";
	}
	fclose(fp);
	str[length] = '\0';
	buf = str;
	len = length;
	return true;
}
}; // namespace FileReader
}; // namespace Engine