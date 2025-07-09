#include <asset_parser/parser.hpp>
#include <format>
#include <fstream>
#include <utility>

namespace Assets {

// void Asset::unpack(std::byte *destination)
// {
// 	if (!m_stream.is_open())
// 	{
// 		throw std::logic_error {
// 			"Failed to unpack asset: "
// 			"ifstream is closed",
// 		};
// 	}
//
// 	switch (m_metadata.blob_compression_type)
// 	{
// 	case CompressionType::None:
// 		if (m_metadata.packed_size != m_metadata.unpacked_size)
// 		{
// 			throw std::logic_error {
// 				"Failed to unpack asset: "
// 				"compression type set to none but packed/unpacked sizes differ",
// 			};
// 		}
//
// 		m_stream.read(
// 		    std::bit_cast<char *>(destination),
// 		    static_cast<long>(m_metadata.packed_size)
// 		);
// 		m_stream.close();
//
// 	case CompressionType::LZ4:
// 		m_stream.close();
// 		throw std::logic_error {
// 			"Failed to unpack asset: "
// 			"LZ4 compression is not implemented yet",
// 		};
//
//
// 	case CompressionType::LZ4HC:
// 		m_stream.close();
// 		throw std::logic_error {
// 			"Failed to unpack asset: "
// 			"LZ4HC compression is not implemented yet",
// 		};
//
// 	default:
// 		m_stream.close();
// 		throw std::logic_error {
// 			std::format(
// 			    "Failed to unpack asset: "
// 			    "Compression type was not recognized: {}",
// 			    std::to_underlying(m_metadata.blob_compression_type)
// 			),
// 		};
// 	}
// }

} // namespace Assets
