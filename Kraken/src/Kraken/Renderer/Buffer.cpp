#include "kepch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Kraken/Platform/OpenGL/OpenGLBuffer.h"

#ifdef KE_PLATFORM_WINDOWS
// Include DirectX (or other windows specfic binaries)
#endif

namespace Kraken {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RenderAPI::API::None: KE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		
		KE_CORE_ASSERT(false, "Unknown RedererAPI");
		return nullptr;
	}
	
	IndexBuffer* IndexBuffer::Create(uint32_t* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RenderAPI::API::None: KE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return new OpenGLIndexBuffer(vertices, size);
		}

		KE_CORE_ASSERT(false, "Unknown RedererAPI");
		return nullptr;
	}
}