#include <camera/scene.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <input/events/window.hpp>
#include <debug/assertions.hpp>
#include <renderer/blender.hpp>
#include <renderer/buffers.hpp>
#include <renderer/framebuffer.hpp>
#include <renderer/render_command.hpp>
#include <renderer/renderer.hpp>
#include <renderer/shader.hpp>
#include <renderer/texture.hpp>
#include <utility>

namespace Light {

Renderer *Renderer::s_context = nullptr;

Renderer::Renderer(
    GLFWwindow *window_handle,
    Ref<SharedContext> shared_context,
    CreateInfo create_info
)
    : m_quad_renderer(
          LT_MAX_QUAD_RENDERER_VERTICES,
          shared_context,
          std::move(create_info.quad_renderer_shader)
      )
    , m_texture_renderer(
          LT_MAX_TEXTURE_RENDERER_VERTICES,
          shared_context,
          std::move(create_info.texture_renderer_shader)
      )
    , m_tinted_texture_renderer(
          LT_MAX_TINTED_TEXTURE_RENDERER_VERTICES,
          shared_context,
          std::move(create_info.tinted_texture_renderer_shader)
      )
    , m_view_projection_buffer(nullptr)
    , m_render_command(nullptr)
    , m_blender(nullptr)
    , m_target_framebuffer(nullptr)

{
	lt_assert(!s_context, "An instance of 'renderer' already exists, do not construct this class!");
	s_context = this;

	m_view_projection_buffer = ConstantBuffer::create(
	    ConstantBufferIndex::ViewProjection,
	    sizeof(glm::mat4),
	    shared_context
	);

	m_render_command = RenderCommand::create(window_handle, shared_context);
	m_blender = Blender::create(shared_context);
	m_blender->enable(BlendFactor::SRC_ALPHA, BlendFactor::INVERSE_SRC_ALPHA);
}

auto Renderer::create(
    GLFWwindow *windowHandle,
    Ref<SharedContext> sharedContext,
    CreateInfo create_info
) -> Scope<Renderer>
{
	return make_scope<Renderer>(
	    new Renderer(windowHandle, std::move(sharedContext), std::move(create_info))
	);
}

void Renderer::on_window_resize(const WindowResizedEvent &event)
{
	m_render_command->set_viewport(0u, 0u, event.get_size().x, event.get_size().y);
}

//======================================== DRAW_QUAD ========================================//
/* tinted textures */
void Renderer::draw_quad_impl(
    const glm::vec3 &position,
    const glm::vec2 &size,
    const glm::vec4 &tint,
    Ref<Texture> texture
)
{
	draw_quad(
	    glm::translate(glm::mat4(1.0f), position)
	        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f }),
	    tint,
	    std::move(texture)
	);
}

/* tint */
void Renderer::draw_quad_impl(
    const glm::vec3 &position,
    const glm::vec2 &size,
    const glm::vec4 &tint
)
{
	draw_quad(
	    glm::translate(glm::mat4(1.0f), position)
	        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f }),
	    tint
	);
}

/* texture */
void Renderer::draw_quad_impl(
    const glm::vec3 &position,
    const glm::vec2 &size,
    Ref<Texture> texture
)
{
	draw_quad(
	    glm::translate(glm::mat4(1.0f), position)
	        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f }),
	    std::move(texture)
	);
}
//======================================== DRAW_QUAD ========================================//

//==================== DRAW_QUAD_TINT ====================//
void Renderer::draw_quad_impl(const glm::mat4 &transform, const glm::vec4 &tint)
{
	auto map = std::span<QuadRendererProgram::QuadVertexData> { m_quad_renderer.get_map_current(),
		                                                        4 };

	// top left
	map[0].position = transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	map[0].tint = tint;

	// top right
	map[1].position = transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
	map[1].tint = tint;

	// bottom right
	map[2].position = transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
	map[2].tint = tint;

	// bottom left
	map[3].position = transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	map[3].tint = tint;

	// advance
	if (!m_quad_renderer.advance())
	{
		log_wrn("Exceeded LT_MAX_QUAD_RENDERER_VERTICES: {}", LT_MAX_QUAD_RENDERER_VERTICES);
		flush_scene();
	}
}

void Renderer::draw_quad_impl(const glm::mat4 &transform, const Ref<Texture> &texture)
{
	lt_assert(texture, "Texture passed to renderer::draw_quad_impl");

	texture->bind();
	auto map = std::span<TextureRendererProgram::TextureVertexData> {
		m_texture_renderer.get_map_current(),
		4
	};

	// top left
	map[0].position = transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	map[0].texcoord = { 0.0f, 0.0f };

	// top right
	map[1].position = transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
	map[1].texcoord = { 1.0f, 0.0f };

	// bottom right
	map[2].position = transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
	map[2].texcoord = { 1.0f, 1.0f };

	// bottom left
	map[3].position = transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	map[3].texcoord = { 0.0f, 1.0f };

	// advance
	if (!m_texture_renderer.advance())
	{
		log_wrn("Exceeded LT_MAX_TEXTURE_RENDERER_VERTICES: {}", LT_MAX_TEXTURE_RENDERER_VERTICES);
		flush_scene();
	}
}

void Renderer::draw_quad_impl(
    const glm::mat4 &transform,
    const glm::vec4 &tint,
    const Ref<Texture> &texture
)
{
	lt_assert(texture, "Texture passed to renderer::draw_quad_impl");

	texture->bind();
	auto map = std::span<TintedTextureRendererProgram::TintedTextureVertexData> {
		m_tinted_texture_renderer.get_map_current(),
		4
	};

	// top left
	map[0].position = transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	map[0].tint = tint;
	map[0].texcoord = { 0.0f, 0.0f };

	// top right
	map[1].position = transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
	map[1].tint = tint;
	map[1].texcoord = { 1.0f, 0.0f };

	// bottom right
	map[2].position = transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
	map[2].tint = tint;
	map[2].texcoord = { 1.0f, 1.0f };

	// bottom left
	map[3].position = transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	map[3].tint = tint;
	map[3].texcoord = { 0.0f, 1.0f };

	if (!m_tinted_texture_renderer.advance())
	{
		log_wrn("Exceeded LT_MAX_TEXTURE_RENDERER_VERTICES: {}", LT_MAX_TEXTURE_RENDERER_VERTICES);
		flush_scene();
	}
}

void Renderer::begin_frame()
{
}

void Renderer::end_frame()
{
	m_render_command->swap_buffers();
	m_render_command->clear_back_buffer(
	    m_default_framebuffer_camera ? m_default_framebuffer_camera->get_background_color() :
	                                   glm::vec4(0.0f)
	);

	m_default_framebuffer_camera = nullptr;
}

void Renderer::begin_scene_impl(
    Camera *camera,
    const glm::mat4 &cameraTransform,
    const Ref<Framebuffer> &targetFrameBuffer /* = nullptr */
)
{
	// determine the target frame buffer
	m_target_framebuffer = targetFrameBuffer;

	if (targetFrameBuffer)
	{
		targetFrameBuffer->bind_as_target(camera->get_background_color());
	}
	else
	{
		m_default_framebuffer_camera = camera;
		m_render_command->default_target_framebuffer();
	}

	// update view projection buffer
	auto *map = (glm::mat4 *)m_view_projection_buffer->map();
	map[0] = camera->get_projection() * glm::inverse(cameraTransform);
	m_view_projection_buffer->un_map();

	// map renderers
	m_quad_renderer.map();
	m_texture_renderer.map();
	m_tinted_texture_renderer.map();
}

void Renderer::flush_scene()
{
	/* tinted texture renderer */
	m_tinted_texture_renderer.un_map();
	if (m_tinted_texture_renderer.get_quad_count())
	{
		m_tinted_texture_renderer.bind();
		m_render_command->draw_indexed(m_tinted_texture_renderer.get_quad_count() * 6u);
	}

	/* quad renderer */
	m_quad_renderer.un_map();
	if (m_quad_renderer.get_quad_count())
	{
		m_quad_renderer.bind();
		m_render_command->draw_indexed(m_quad_renderer.get_quad_count() * 6u);
	}

	/* texture renderer */
	m_texture_renderer.un_map();
	if (m_texture_renderer.get_quad_count())
	{
		m_texture_renderer.bind();
		m_render_command->draw_indexed(m_texture_renderer.get_quad_count() * 6u);
	}

	m_quad_renderer.map();
	m_texture_renderer.map();
	m_tinted_texture_renderer.map();
}

void Renderer::end_scene_impl()
{
	/* tinted texture renderer */
	m_tinted_texture_renderer.un_map();
	if (m_tinted_texture_renderer.get_quad_count())
	{
		m_tinted_texture_renderer.bind();
		m_render_command->draw_indexed(m_tinted_texture_renderer.get_quad_count() * 6u);
	}

	/* quad renderer */
	m_quad_renderer.un_map();
	if (m_quad_renderer.get_quad_count())
	{
		m_quad_renderer.bind();
		m_render_command->draw_indexed(m_quad_renderer.get_quad_count() * 6u);
	}

	/* texture renderer */
	m_texture_renderer.un_map();
	if (m_texture_renderer.get_quad_count())
	{
		m_texture_renderer.bind();
		m_render_command->draw_indexed(m_texture_renderer.get_quad_count() * 6u);
	}

	// reset frame buffer
	if (m_target_framebuffer)
	{
		m_target_framebuffer = nullptr;
		m_render_command->default_target_framebuffer();
	}
}

} // namespace Light
