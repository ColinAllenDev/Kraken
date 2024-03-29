#pragma once
#include "RenderCommand.h"

namespace Kraken {

	class Renderer {
	public:
		static void BeginScene(); // TODO: add scene parameters
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray); 
		
		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	private:
	};
}