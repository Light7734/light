#include "AssetParser.hpp"

#include <fstream>
#include <istream>
#include <ostream>

namespace Assets {

bool save_binary_file(const char* path, const AssetFile& file)
{
	std::ofstream outstream(path, std::ios::binary | std::ios::out);

	outstream.write((const char*)&file.version, sizeof(uint32_t));
	outstream.write((const char*)&file.type, sizeof(AssetFile::Type));

	uint32_t json_size = file.json.size();
	uint32_t blob_size = file.blob.size();
	outstream.write((const char*)&json_size, sizeof(uint32_t));
	outstream.write((const char*)&blob_size, sizeof(uint32_t));

	outstream.write(file.json.c_str(), json_size);
	outstream.write((const char*)file.blob.data(), blob_size);

	outstream.close();

	outstream.close();

	return true;
}

bool load_binary_file(const char* path, AssetFile& out_file)
{
	std::ifstream instream(path, std::ios::binary);
	instream.seekg(0ull);

	if (!instream.is_open())
		return false;

	instream.read((char*)&out_file.version, sizeof(uint32_t));
	instream.read((char*)&out_file.type, sizeof(AssetFile::Type));

	uint32_t json_size;
	uint32_t blob_size;
	instream.read((char*)&json_size, sizeof(uint32_t));
	instream.read((char*)&blob_size, sizeof(uint32_t));

	out_file.json.resize(json_size);
	out_file.blob.resize(blob_size);
	instream.read((char*)out_file.json.data(), json_size);
	instream.read((char*)out_file.blob.data(), blob_size);

	instream.close();

	return true;
}

} // namespace Assets
