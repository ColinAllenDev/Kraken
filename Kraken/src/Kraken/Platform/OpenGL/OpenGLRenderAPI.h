#pragma once

#include "Kraken/Renderer/RenderAPI.h"

namespace Kraken {
	class OpenGLRenderAPI : public RenderAPI {
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}