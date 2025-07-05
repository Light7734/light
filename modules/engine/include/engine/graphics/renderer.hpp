#pragma once

#include <engine/base/base.hpp>
#include <engine/graphics/renderer_programs/quad.hpp>
#include <engine/graphics/renderer_programs/texture.hpp>
#include <engine/graphics/renderer_programs/tinted_texture.hpp>

#define LT_MAX_QUAD_RENDERER_VERTICES           1028u * 4u
#define LT_MAX_TEXTURE_RENDERER_VERTICES        1028u * 4u
#define LT_MAX_TINTED_TEXTURE_RENDERER_VERTICES 1028u * 4u

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
private:
	static Renderer *s_Context;

	// renderer programs
	QuadRendererProgram m_quad_renderer;
	TextureRendererProgram m_texture_renderer;
	TintedTextureRendererProgram m_tinted_texture_renderer;

	// constant buffers
	Scope<ConstantBuffer> m_view_projection_buffer;

	Scope<RenderCommand> m_render_command;
	Scope<Blender> m_blender;

	Camera *m_default_framebuffer_camera;
	Ref<Framebuffer> m_target_framebuffer;

	bool m_should_clear_backbuffer;

public:
	static Scope<Renderer> Create(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext);

	static inline void DrawQuad(
	    const glm::vec3 &position,
	    const glm::vec2 &size,
	    const glm::vec4 &tint,
	    Ref<Texture> texture
	)
	{
		s_Context->DrawQuadImpl(position, size, tint, texture);
	}
	static inline void DrawQuad(
	    const glm::vec3 &position,
	    const glm::vec2 &size,
	    const glm::vec4 &tint
	)
	{
		s_Context->DrawQuadImpl(position, size, tint);
	}
	static inline void DrawQuad(
	    const glm::vec3 &position,
	    const glm::vec2 &size,
	    Ref<Texture> texture
	)
	{
		s_Context->DrawQuadImpl(position, size, texture);
	}

	static void DrawQuad(const glm::mat4 &transform, const glm::vec4 &tint, Ref<Texture> texture)
	{
		s_Context->DrawQuadImpl(transform, tint, texture);
	}
	static void DrawQuad(const glm::mat4 &transform, const glm::vec4 &tint)
	{
		s_Context->DrawQuadImpl(transform, tint);
	}
	static void DrawQuad(const glm::mat4 &transform, Ref<Texture> texture)
	{
		s_Context->DrawQuadImpl(transform, texture);
	}

	static inline void BeginScene(
	    Camera *camera,
	    const glm::mat4 &cameraTransform,
	    const Ref<Framebuffer> &targetFrameBuffer = nullptr
	)
	{
		s_Context->BeginSceneImpl(camera, cameraTransform, targetFrameBuffer);
	}
	static inline void EndScene()
	{
		s_Context->EndSceneImpl();
	}

	void OnWindowResize(const WindowResizedEvent &event);

	void BeginFrame();
	void EndFrame();

private:
	Renderer(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext);

	void DrawQuadImpl(
	    const glm::vec3 &position,
	    const glm::vec2 &size,
	    const glm::vec4 &tint,
	    Ref<Texture> texture
	);
	void DrawQuadImpl(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &tint);
	void DrawQuadImpl(const glm::vec3 &position, const glm::vec2 &size, Ref<Texture> texture);

	void DrawQuadImpl(const glm::mat4 &transform, const glm::vec4 &tint, Ref<Texture> texture);
	void DrawQuadImpl(const glm::mat4 &transform, const glm::vec4 &tint);
	void DrawQuadImpl(const glm::mat4 &transform, Ref<Texture> texture);

	void BeginSceneImpl(
	    Camera *camera,
	    const glm::mat4 &cameraTransform,
	    const Ref<Framebuffer> &targetFrameBuffer = nullptr
	);
	void FlushScene();
	void EndSceneImpl();
};

} // namespace Light
