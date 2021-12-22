#include "kepch.h"
#include "RenderCommand.h"
#include "Kraken/Platform/OpenGL/OpenGLRenderAPI.h"

namespace Kraken {
	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI;
}