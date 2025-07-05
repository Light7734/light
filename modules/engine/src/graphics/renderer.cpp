#include <engine/camera/scene.hpp>
#include <engine/events/window.hpp>
#include <engine/graphics/blender.hpp>
#include <engine/graphics/buffers.hpp>
#include <engine/graphics/framebuffer.hpp>
#include <engine/graphics/render_command.hpp>
#include <engine/graphics/renderer.hpp>
#include <engine/graphics/texture.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>

namespace Light {

renderer *renderer::s_context = nullptr;

renderer::renderer(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
    : m_quad_renderer(LT_MAX_QUAD_RENDERER_VERTICES, sharedContext)
    , m_texture_renderer(LT_MAX_TEXTURE_RENDERER_VERTICES, sharedContext)
    , m_tinted_texture_renderer(LT_MAX_TINTED_TEXTURE_RENDERER_VERTICES, sharedContext)
    , m_view_projection_buffer(nullptr)
    , m_render_command(nullptr)
    , m_blender(nullptr)
    , m_default_framebuffer_camera(nullptr)
    , m_target_framebuffer(nullptr)
    , m_should_clear_backbuffer(false)
{
	lt_assert(!s_context, "An instance of 'renderer' already exists, do not construct this class!");
	s_context = this;

	m_view_projection_buffer = ConstantBuffer::create(
	    ConstantBufferIndex::ViewProjection,
	    sizeof(glm::mat4),
	    sharedContext
	);

	m_render_command = RenderCommand::create(windowHandle, sharedContext);
	m_blender = Blender::create(sharedContext);
	m_blender->enable(BlendFactor::SRC_ALPHA, BlendFactor::INVERSE_SRC_ALPHA);
}

Scope<renderer> renderer::create(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
{
	return make_scope<renderer>(new renderer(windowHandle, sharedContext));
}

void renderer::on_window_resize(const WindowResizedEvent &event)
{
	m_render_command->set_viewport(0u, 0u, event.get_size().x, event.get_size().y);
}

//======================================== DRAW_QUAD ========================================//
/* tinted textures */
void renderer::draw_quad_impl(
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
	    texture
	);
}

/* tint */
void renderer::draw_quad_impl(
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
void renderer::draw_quad_impl(
    const glm::vec3 &position,
    const glm::vec2 &size,
    Ref<Texture> texture
)
{
	draw_quad(
	    glm::translate(glm::mat4(1.0f), position)
	        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f }),
	    texture
	);
}
//======================================== DRAW_QUAD ========================================//

//==================== DRAW_QUAD_TINT ====================//
void renderer::draw_quad_impl(const glm::mat4 &transform, const glm::vec4 &tint)
{
	// locals
	QuadRendererProgram::QuadVertexData *bufferMap = m_quad_renderer.GetMapCurrent();

	// top left
	bufferMap[0].position = transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	bufferMap[0].tint = tint;

	// top right
	bufferMap[1].position = transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
	bufferMap[1].tint = tint;

	// bottom right
	bufferMap[2].position = transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
	bufferMap[2].tint = tint;

	// bottom left
	bufferMap[3].position = transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	bufferMap[3].tint = tint;

	// advance
	if (!m_quad_renderer.advance())
	{
		lt_log(warn, "Exceeded LT_MAX_QUAD_RENDERER_VERTICES: {}", LT_MAX_QUAD_RENDERER_VERTICES);
		flush_scene();
	}
}
//==================== DRAW_QUAD_TINT ====================//

//==================== DRAW_QUAD_TEXTURE ====================//
void renderer::draw_quad_impl(const glm::mat4 &transform, Ref<Texture> texture)
{
	// #todo: implement a proper binding
	lt_assert(texture, "Texture passed to renderer::draw_quad_impl");
	texture->bind();

	// locals
	TextureRendererProgram::TextureVertexData *bufferMap = m_texture_renderer.GetMapCurrent();

	// top left
	bufferMap[0].position = transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	bufferMap[0].texcoord = { 0.0f, 0.0f };

	// top right
	bufferMap[1].position = transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
	bufferMap[1].texcoord = { 1.0f, 0.0f };

	// bottom right
	bufferMap[2].position = transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
	bufferMap[2].texcoord = { 1.0f, 1.0f };

	// bottom left
	bufferMap[3].position = transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	bufferMap[3].texcoord = { 0.0f, 1.0f };

	// advance
	if (!m_texture_renderer.advance())
	{
		lt_log(
		    warn,
		    "Exceeded LT_MAX_TEXTURE_RENDERER_VERTICES: {}",
		    LT_MAX_TEXTURE_RENDERER_VERTICES
		);
		flush_scene();
	}
}

void renderer::draw_quad_impl(
    const glm::mat4 &transform,
    const glm::vec4 &tint,
    Ref<Texture> texture
)
{
	// #todo: implement a proper binding
	lt_assert(texture, "Texture passed to renderer::draw_quad_impl");
	texture->bind();

	// locals
	TintedTextureRendererProgram::TintedTextureVertexData *bufferMap = m_tinted_texture_renderer
	                                                                       .GetMapCurrent();

	// top left
	bufferMap[0].position = transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	bufferMap[0].tint = tint;
	bufferMap[0].texcoord = { 0.0f, 0.0f };

	// top right
	bufferMap[1].position = transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
	bufferMap[1].tint = tint;
	bufferMap[1].texcoord = { 1.0f, 0.0f };

	// bottom right
	bufferMap[2].position = transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
	bufferMap[2].tint = tint;
	bufferMap[2].texcoord = { 1.0f, 1.0f };

	// bottom left
	bufferMap[3].position = transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
	bufferMap[3].tint = tint;
	bufferMap[3].texcoord = { 0.0f, 1.0f };

	// advance
	if (!m_tinted_texture_renderer.advance())
	{
		lt_log(
		    warn,
		    "Exceeded LT_MAX_TEXTURE_RENDERER_VERTICES: {}",
		    LT_MAX_TEXTURE_RENDERER_VERTICES
		);
		flush_scene();
	}
}

//==================== DRAW_QUAD_TEXTURE ====================//

void renderer::begin_frame()
{
}

void renderer::end_frame()
{
	m_render_command->swap_buffers();
	m_render_command->clear_back_buffer(
	    m_default_framebuffer_camera ? m_default_framebuffer_camera->GetBackgroundColor() :
	                                   glm::vec4(0.0f)
	);

	m_default_framebuffer_camera = nullptr;
}

void renderer::begin_scene_impl(
    Camera *camera,
    const glm::mat4 &cameraTransform,
    const Ref<Framebuffer> &targetFrameBuffer /* = nullptr */
)
{
	// determine the target frame buffer
	m_target_framebuffer = targetFrameBuffer;

	if (targetFrameBuffer)
		targetFrameBuffer->bind_as_target(camera->GetBackgroundColor());
	else
	{
		m_default_framebuffer_camera = camera;
		m_render_command->default_target_framebuffer();
	}

	// update view projection buffer
	glm::mat4 *map = (glm::mat4 *)m_view_projection_buffer->map();
	map[0] = camera->GetProjection() * glm::inverse(cameraTransform);
	m_view_projection_buffer->un_map();

	// map renderers
	m_quad_renderer.map();
	m_texture_renderer.map();
	m_tinted_texture_renderer.map();
}

void renderer::flush_scene()
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

void renderer::end_scene_impl()
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
