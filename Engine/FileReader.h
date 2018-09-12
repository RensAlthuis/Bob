#pragma once
#include <stdio.h>
#include <iostream>

namespace FileReader {
	static const char* readFile(const char* path) {
		FILE* fp;
		fopen_s(&fp, path, "rb");
		if (!fp) {
			std::cout << "ERROR: Failed to read file" << std::endl;
			return "";
		}

		fseek(fp, 0, SEEK_END);
		long length = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char* str = (char*)malloc((length + 1) * sizeof(char));
		fread(str, 1, length, fp);
		fclose(fp);
		str[length] = '\0';
		return str;
	}
};