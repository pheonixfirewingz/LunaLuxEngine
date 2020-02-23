#ifndef LUNALUXENGINE_READER_H
#define LUNALUXENGINE_READER_H
#include <vector>
#include <fstream>
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
		inline std::vector<char> readFile(const std::string& filename)
		{
			std::ifstream file(filename, std::ios::ate | std::ios::binary);
			if (!file.is_open())  throw std::runtime_error("failed to open file!");
			size_t fileSize = (size_t)file.tellg();
			std::vector<char> buffer(fileSize);
			file.seekg(0);
			file.read(buffer.data(), fileSize);
			file.close();

			return buffer;
		}
	};
}
#endif