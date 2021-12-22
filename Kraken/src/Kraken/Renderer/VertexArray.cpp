#include "kepch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Kraken/Platform/OpenGL/OpenGLVertexArray.h"

namespace Kraken {

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RenderAPI::API::None: KE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		KE_CORE_ASSERT(false, "Unknown RedererAPI");
		return nullptr;
	}
}