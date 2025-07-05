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

Renderer *Renderer::s_Context = nullptr;

Renderer::Renderer(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
    : m_QuadRenderer(LT_MAX_QUAD_RENDERER_VERTICES, sharedContext)
    , m_TextureRenderer(LT_MAX_TEXTURE_RENDERER_VERTICES, sharedContext)
    , m_TintedTextureRenderer(LT_MAX_TINTED_TEXTURE_RENDERER_VERTICES, sharedContext)
    , m_ViewProjectionBuffer(nullptr)
    , m_RenderCommand(nullptr)
    , m_Blender(nullptr)
    , m_DefaultFramebufferCamera(nullptr)
    , m_TargetFramebuffer(nullptr)
    , m_ShouldClearBackbuffer(false)
{
	ASSERT(!s_Context, "An instance of 'Renderer' already exists, do not construct this class!");
	s_Context = this;

	m_ViewProjectionBuffer = ConstantBuffer::Create(
	    ConstantBufferIndex::ViewProjection,
	    sizeof(glm::mat4),
	    sharedContext
	);

	m_RenderCommand = RenderCommand::Create(windowHandle, sharedContext);
	m_Blender = Blender::Create(sharedContext);
	m_Blender->Enable(BlendFactor::SRC_ALPHA, BlendFactor::INVERSE_SRC_ALPHA);
}

Scope<Renderer> Renderer::Create(GLFWwindow *windowHandle, Ref<SharedContext> sharedContext)
{
	return MakeScope<Renderer>(new Renderer(windowHandle, sharedContext));
}

void Renderer::OnWindowResize(const WindowResizedEvent &event)
{
	m_RenderCommand->SetViewport(0u, 0u, event.GetSize().x, event.GetSize().y);
}

//======================================== DRAW_QUAD ========================================//
/* tinted textures */
void Renderer::DrawQuadImpl(
    const glm::vec3 &position,
    const glm::vec2 &size,
    const glm::vec4 &tint,
    Ref<Texture> texture
)
{
	DrawQuad(
	    glm::translate(glm::mat4(1.0f), position)
	        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f }),
	    tint,
	    texture
	);
}

/* tint */
void Renderer::DrawQuadImpl(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &tint)
{
	DrawQuad(
	    glm::translate(glm::mat4(1.0f), position)
	        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f }),
	    tint
	);
}

/* texture */
void Renderer::DrawQuadImpl(const glm::vec3 &position, const glm::vec2 &size, Ref<Texture> texture)
{
	DrawQuad(
	    glm::translate(glm::mat4(1.0f), position)
	        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f }),
	    texture
	);
}
//======================================== DRAW_QUAD ========================================//

//==================== DRAW_QUAD_TINT ====================//
void Renderer::DrawQuadImpl(const glm::mat4 &transform, const glm::vec4 &tint)
{
	// locals
	QuadRendererProgram::QuadVertexData *bufferMap = m_QuadRenderer.GetMapCurrent();

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
	if (!m_QuadRenderer.Advance())
	{
		LOG(warn, "Exceeded LT_MAX_QUAD_RENDERER_VERTICES: {}", LT_MAX_QUAD_RENDERER_VERTICES);
		FlushScene();
	}
}
//==================== DRAW_QUAD_TINT ====================//

//==================== DRAW_QUAD_TEXTURE ====================//
void Renderer::DrawQuadImpl(const glm::mat4 &transform, Ref<Texture> texture)
{
	// #todo: implement a proper binding
	ASSERT(texture, "Texture passed to Renderer::DrawQuadImpl");
	texture->Bind();

	// locals
	TextureRendererProgram::TextureVertexData *bufferMap = m_TextureRenderer.GetMapCurrent();

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
	if (!m_TextureRenderer.Advance())
	{
		LOG(warn, "Exceeded LT_MAX_TEXTURE_RENDERER_VERTICES: {}", LT_MAX_TEXTURE_RENDERER_VERTICES
		);
		FlushScene();
	}
}

void Renderer::DrawQuadImpl(const glm::mat4 &transform, const glm::vec4 &tint, Ref<Texture> texture)
{
	// #todo: implement a proper binding
	ASSERT(texture, "Texture passed to Renderer::DrawQuadImpl");
	texture->Bind();

	// locals
	TintedTextureRendererProgram::TintedTextureVertexData *bufferMap = m_TintedTextureRenderer
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
	if (!m_TintedTextureRenderer.Advance())
	{
		LOG(warn, "Exceeded LT_MAX_TEXTURE_RENDERER_VERTICES: {}", LT_MAX_TEXTURE_RENDERER_VERTICES
		);
		FlushScene();
	}
}

//==================== DRAW_QUAD_TEXTURE ====================//

void Renderer::BeginFrame()
{
}

void Renderer::EndFrame()
{
	m_RenderCommand->SwapBuffers();
	m_RenderCommand->ClearBackBuffer(
	    m_DefaultFramebufferCamera ? m_DefaultFramebufferCamera->GetBackgroundColor() :
	                                 glm::vec4(0.0f)
	);

	m_DefaultFramebufferCamera = nullptr;
}

void Renderer::BeginSceneImpl(
    Camera *camera,
    const glm::mat4 &cameraTransform,
    const Ref<Framebuffer> &targetFrameBuffer /* = nullptr */
)
{
	// determine the target frame buffer
	m_TargetFramebuffer = targetFrameBuffer;

	if (targetFrameBuffer)
		targetFrameBuffer->BindAsTarget(camera->GetBackgroundColor());
	else
	{
		m_DefaultFramebufferCamera = camera;
		m_RenderCommand->DefaultTargetFramebuffer();
	}

	// update view projection buffer
	glm::mat4 *map = (glm::mat4 *)m_ViewProjectionBuffer->Map();
	map[0] = camera->GetProjection() * glm::inverse(cameraTransform);
	m_ViewProjectionBuffer->UnMap();

	// map renderers
	m_QuadRenderer.Map();
	m_TextureRenderer.Map();
	m_TintedTextureRenderer.Map();
}

void Renderer::FlushScene()
{
	/* tinted texture renderer */
	m_TintedTextureRenderer.UnMap();
	if (m_TintedTextureRenderer.GetQuadCount())
	{
		m_TintedTextureRenderer.Bind();
		m_RenderCommand->DrawIndexed(m_TintedTextureRenderer.GetQuadCount() * 6u);
	}

	/* quad renderer */
	m_QuadRenderer.UnMap();
	if (m_QuadRenderer.GetQuadCount())
	{
		m_QuadRenderer.Bind();
		m_RenderCommand->DrawIndexed(m_QuadRenderer.GetQuadCount() * 6u);
	}

	/* texture renderer */
	m_TextureRenderer.UnMap();
	if (m_TextureRenderer.GetQuadCount())
	{
		m_TextureRenderer.Bind();
		m_RenderCommand->DrawIndexed(m_TextureRenderer.GetQuadCount() * 6u);
	}

	m_QuadRenderer.Map();
	m_TextureRenderer.Map();
	m_TintedTextureRenderer.Map();
}

void Renderer::EndSceneImpl()
{
	/* tinted texture renderer */
	m_TintedTextureRenderer.UnMap();
	if (m_TintedTextureRenderer.GetQuadCount())
	{
		m_TintedTextureRenderer.Bind();
		m_RenderCommand->DrawIndexed(m_TintedTextureRenderer.GetQuadCount() * 6u);
	}

	/* quad renderer */
	m_QuadRenderer.UnMap();
	if (m_QuadRenderer.GetQuadCount())
	{
		m_QuadRenderer.Bind();
		m_RenderCommand->DrawIndexed(m_QuadRenderer.GetQuadCount() * 6u);
	}

	/* texture renderer */
	m_TextureRenderer.UnMap();
	if (m_TextureRenderer.GetQuadCount())
	{
		m_TextureRenderer.Bind();
		m_RenderCommand->DrawIndexed(m_TextureRenderer.GetQuadCount() * 6u);
	}

	// reset frame buffer
	if (m_TargetFramebuffer)
	{
		m_TargetFramebuffer = nullptr;
		m_RenderCommand->DefaultTargetFramebuffer();
	}
}

} // namespace Light
