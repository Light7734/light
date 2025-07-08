Asset Management
===================================================================================================
Layout
---------------------------------------------------------------------------------------------------
{version}              | 4 bytes, ie. uint32_t
{general metadata}     | sizeof(AssetMetadata)
{specialized metadata} | sizeof(XXXAssetMetadata), eg. TextureAssetMetadata
{blob_0...n metadata}  | n * sizeof(BlobMetadata)
{blob_0...n data}      | variable size based on actual data
{end marker}           | 8 byte, ie size_t for marking the END

Sections
---------------------------------------------------------------------------------------------------
version              -> The version of the asset for forward compatibility
general metadata     -> Common asset metadata such as file-path, asset-type, creator, etc.
specialized metadata -> Metadata specific to the asset, eg. texture dimensions for Textures
blob_0...n metadata  -> Metadata specifying how the actual data is packed, required for unpacking.
blob_0...n data      -> The actual data, packed and compressed to be reacdy for direct engine consumption.

Loading
---------------------------------------------------------------------------------------------------
Each `Loader` has ONE OR MORE supported input file types (detected via the file extension): eg. StbLoader -> Can read in .jpg, .png, .bmp, etc.... files

Each `Loader` has ONLY ONE supported output asset type:
eg. StbLoader -> outputs TextureAsset

Multiple `Loader`s MAY have as output the same asset type:
eg. StbLoader -> outputs TextureAsset
eg. SomeOtherImgLoader -> outputs TextureAsset

Multiple `Loader`s SHOULD NOT have as input same extension types
eg. .jpg, .png -> if supported, should only be supported by 1 `Loader` class

Each `Loader` SHOULD read and turn the data from a file (eg. .png for textures) into something
understandable by a `Packer` (not the engine itself).

A `Loader` SHOULD NOT be responsible for packing the parsed file data into asset data,
as that implies direct understanding of the layout required by the engine. 

And if that layout changes, ALL `Loader`s should change accordingly; 
which makes a class that's responsible for reading files dependant on the engine's (potentially frequent) internal changes.
The logic is to reduce many-to-one dependency into a one-to-one dependency by redirecting the packing process to `Packer` classes

Packing
---------------------------------------------------------------------------------------------------
Each `Packer` is responsible for packing ONLY ONE asset type:
eg. TexturePacker for packing texture assets from parsed image files.
eg. ModelPacker for packing model assets from parsed model files.

Each `Packer` will output ONE OR MORE blobs of data, 
and for EACH blob of data, it'll write a BlobMetadata, AFTER the specialized metadata (eg. TextureAssetMetadata)

A `Packer` will make use of the `Compressor` classes to compress the data,
and lay it out in a way that is suitable for the engine's consumption.

Unpacking
---------------------------------------------------------------------------------------------------
A `Parser` is responsible for parsing ONLY ONE asset type:
eg. TextureParser for parsing texture assets for direct engine consumption.
eg. ModelParser  for parsing model assets for direct engine consumption.
