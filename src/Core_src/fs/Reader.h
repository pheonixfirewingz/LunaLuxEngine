#ifndef LUNALUXENGINE_READER_H
#define LUNALUXENGINE_READER_H
#include<fstream>
#include<sstream>
#include<string>

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
			if (!file.is_open())  throw std::runtime_error("failed to open file!");
			size_t fileSize = (size_t)file.tellg();
			file.seekg(0);
			std::ostringstream ss;
			ss << file.rdbuf();
			buffer = ss.str();
			file.close();
		};
	};
}
#endif