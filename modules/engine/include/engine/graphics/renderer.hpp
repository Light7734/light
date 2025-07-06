#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/renderer_programs/quad.hpp>
#include <engine/graphics/renderer_programs/texture.hpp>
#include <engine/graphics/renderer_programs/tinted_texture.hpp>
#include <utility>

#define LT_MAX_QUAD_RENDERER_VERTICES           (1028u * 4u)
#define LT_MAX_TEXTURE_RENDERER_VERTICES        (1028u * 4u)
#define LT_MAX_TINTED_TEXTURE_RENDERER_VERTICES (1028u * 4u)

struct GLFWwindow;

namespace Light {

class Blender;
class ConstantBuffer;
class Framebuffer;
class RenderCommand;
class Texture;
class SharedContext;
class Camera;
class WindowResizedEvent;

class Renderer
{
public:
	static auto create(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
	    -> Scope<Renderer>;

	static void draw_quad(
	    const glm::vec3 &position,
	    const glm::vec2 &size,
	    const glm::vec4 &tint,
	    Ref<Texture> texture
	)
	{
		s_context->draw_quad_impl(position, size, tint, std::move(texture));
	}

	static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &tint)
	{
		s_context->draw_quad_impl(position, size, tint);
	}

	static void draw_quad(const glm::vec3 &position, const glm::vec2 &size, Ref<Texture> texture)
	{
		s_context->draw_quad_impl(position, size, std::move(texture));
	}

	static void draw_quad(const glm::mat4 &transform, const glm::vec4 &tint, Ref<Texture> texture)
	{
		s_context->draw_quad_impl(transform, tint, std::move(texture));
	}

	static void draw_quad(const glm::mat4 &transform, const glm::vec4 &tint)
	{
		s_context->draw_quad_impl(transform, tint);
	}

	static void draw_quad(const glm::mat4 &transform, Ref<Texture> texture)
	{
		s_context->draw_quad_impl(transform, std::move(texture));
	}

	static void begin_scene(
	    Camera *camera,
	    const glm::mat4 &cameraTransform,
	    const Ref<Framebuffer> &targetFrameBuffer = nullptr
	)
	{
		s_context->begin_scene_impl(camera, cameraTransform, targetFrameBuffer);
	}

	static void end_scene()
	{
		s_context->end_scene_impl();
	}

	void on_window_resize(const WindowResizedEvent &event);

	void begin_frame();

	void end_frame();

private:
	static Renderer *s_context;

	QuadRendererProgram m_quad_renderer;

	TextureRendererProgram m_texture_renderer;

	TintedTextureRendererProgram m_tinted_texture_renderer;

	Scope<ConstantBuffer> m_view_projection_buffer;

	Scope<RenderCommand> m_render_command;

	Scope<Blender> m_blender;

	Camera *m_default_framebuffer_camera { nullptr };

	Ref<Framebuffer> m_target_framebuffer;

	bool m_should_clear_backbuffer { false };

	Renderer(GLFWwindow *windowHandle, const Ref<SharedContext> &sharedContext);

	void draw_quad_impl(
	    const glm::vec3 &position,
	    const glm::vec2 &size,
	    const glm::vec4 &tint,
	    Ref<Texture> texture
	);

	void draw_quad_impl(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &tint);

	void draw_quad_impl(const glm::vec3 &position, const glm::vec2 &size, Ref<Texture> texture);

	void draw_quad_impl(
	    const glm::mat4 &transform,
	    const glm::vec4 &tint,
	    const Ref<Texture> &texture
	);

	void draw_quad_impl(const glm::mat4 &transform, const glm::vec4 &tint);

	void draw_quad_impl(const glm::mat4 &transform, const Ref<Texture> &texture);

	void begin_scene_impl(
	    Camera *camera,
	    const glm::mat4 &cameraTransform,
	    const Ref<Framebuffer> &targetFrameBuffer = nullptr
	);

	void flush_scene();

	void end_scene_impl();
};

} // namespace Light
