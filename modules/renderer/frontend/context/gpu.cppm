export module renderer.frontend.gpu;

namespace lt::renderer {

export class IGpu
{
public:
	IGpu() = default;

	virtual ~IGpu() = default;

	IGpu(IGpu &&) = default;

	IGpu(const IGpu &) = delete;

	auto operator=(IGpu &&) -> IGpu & = default;

	auto operator=(const IGpu &) -> IGpu & = delete;
};

} // namespace lt::renderer
