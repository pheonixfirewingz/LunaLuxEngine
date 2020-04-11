#ifndef LUNALUXENGINE_READER_H
#define LUNALUXENGINE_READER_H
#include<fstream>
#include<sstream>
#include<string>
#include "../common/EnginePanic.h"

#define READFILE(tempstring,charpointer,filename) \
LunaLuxEngine::FileSystem::FileReader::get()->readFile(filename, tempstring);\
charpointer = tempstring.data();

namespace LunaLuxEngine::FileSystem
{

	class FileReader
	{
	public:
		static FileReader* get()
		{
			static FileReader* reader = new FileReader();
			return reader;
		}
		inline void readFile(char* filename, std::string& buffer)
		{
			std::ifstream file(filename, std::ios::ate | std::ios::binary);

			if (!file.is_open() || !file) LunaLuxEngine::EnginePanic::get()->panic("could not open File");
			file.seekg(0);
			std::ostringstream ss;
			ss << file.rdbuf();
			buffer = ss.str();
			file.close();
		};
	};
}
#endif