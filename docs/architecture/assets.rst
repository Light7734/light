Asset Management
===================================================================================================

On Disk Layout
---------------------------------------------------------------------------------------------------

.. code-block:: md

    {general metadata}     | `AssetMetadata`
    {specialized metadata} | eg. `TextureAssetMetadata`, `ShaderAssetMetadata`
    {blob count}           | `u32`
    {blob_0...n metadata}  | {blob count} number of `BlobMetadata`s
    {blob_0...n data}      | {blob count} number of binary data

Baking
---------------------------------------------------------------------------------------------------
Parsers are functions that are responsible for reading raw asset files (eg, :code:`.png`, :code:`.obj`, :code:`.gltf`, :code:`.ogg` files) from disk,
and constructing a common :code:`XXXAsset::PackData` (eg. :code:`ModelAsset::PackData`) structure out of them.

Example parser signature: 

.. code:: cpp

    auto parse_obj(const std::filesystem::path& path) -> lt::assets::ModelAsset::PackData;

It is then the responsibility of the :code:`XXXAsset` class to implement a :code:`pack` method to save this data into disk,
in a way that the :code:`XXXAsset` class can later :code:`unpack` the data from disk in an efficient way.

All raw asset files will be packed into a ready-to-use format. 
Which means, when baking a :code:`.jpg` or :code:`.png` or :code:`.bmp` file, 
regardless of their original format, they'll be baked into a common, ready-to-use by the engine format.


General Metadata
---------------------------------------------------------------------------------------------------
.. code-block:: md

    {vesrion} | `u8`
    {type}    | `std::array<const char, 16>`

:code:`version` is used to keep backward-compatibility in case there's a breaking change, so future versions
can have a special code for converting old baked asset files into new baked asset files.

However, :code:`version` is currently useless as we are in the *beta* phase of the engine. So breaking changes
are expected and backward-compatibility is a waste of effort (maybe once we have some users?).

:code:`type` is a *16 character long* identifier for the type of the asset (we do not rely on the filename extension).
It's pretty much the same concept as *magic bytes*.

An example of an asset type identifier:

.. code:: cpp


    class ShaderAsset
    {
    public:
        // using Type_T = std::array<const char, 16>;  (imported symbol)
        static constexpr auto asset_type_identifier = Type_T { "SHADER_________" };
    // ...
    };


Specialized Metadata
---------------------------------------------------------------------------------------------------
Metadata for the specific asset type, for example:

.. code:: cpp

    class ShaderAsset
    {
        //...
        enum class Type : u8
        {
            vertex,
            fragment,
            geometry,
            compute,
        };

        struct Metadata
        {
            Type type;
        };
        //...
    };

Very simple exmaple, expect much more complicated metadatas for more complicated assets like models which
require textures, vertices, indices, LoDs, etc; or textures which require dimensions, bits per pixel, etc.

Blob Metadata
---------------------------------------------------------------------------------------------------
The metadata of a blob of data, eg. the pixels of an image, or the normals of a model.

.. code-block:: md

    {tag}               | `u8`
    {offset}            | `size_t`
    {compression_type}  | `CompressionType`
    {compressed_size}   | `size_t`
    {uncompressed_size} | `size_t`

:code:`tag` is an enum identifier (of type u8) for programmers to quickly access (unpack) the desired binary data,
it's like indexing into a :code:`map` with :code:`tag`\ s as keys and the binary data as values.

For exmaple:

.. code:: cpp

    class ModelAsset
    {
    //...
        enum class BlobTag : Tag_T /* u8 */
        {
            vertices,
            indices,
        };

        auto unpack(BlobTag tag) const -> Blob /* std::vector<byte> */;

        void unpack_to(BlobTag tag, std::span<byte> destination) const;
    //...
    };

:code:`offset` is the byte offset, from the beginning of the file, to the first byte of the binary data.

:code:`compression_type` is the type of compression used on the raw binary data before being saved to disk, 
so the existing on-disk binary data should be decompressed according to this type. Current list of compression types include:

.. code:: cpp

    enum class CompressionType : u8
    {
        none,
        lz4,
        lz4_hc,
    };

:code:`compressed_size` is the size of the blob's binary data on disk,
basically how many bytes one should read from the file on disk.

:code:`uncompressed_size` is the expected size of the blob's binary data after decompression, 
in case of :code:`CompressionType::none`, it should be equals to :code:`compressed_size`.
