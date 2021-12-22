#include "kepch.h"
#include "ShaderData.h"

#include <glad/glad.h>

namespace Kraken {
	ShaderData ShaderDataType::Float = ShaderData(4, 1, GL_FLOAT);
	ShaderData ShaderDataType::Float2 = ShaderData(4 * 2, 2, GL_FLOAT);
	ShaderData ShaderDataType::Float3 = ShaderData(4 * 3, 3, GL_FLOAT);
	ShaderData ShaderDataType::Float4 = ShaderData(4 * 4, 4, GL_FLOAT);
	
	ShaderData ShaderDataType::Int = ShaderData(4, 1, GL_INT);
	ShaderData ShaderDataType::Int2 = ShaderData(4 * 2, 2, GL_INT);
	ShaderData ShaderDataType::Int3 = ShaderData(4 * 3, 3, GL_INT);
	ShaderData ShaderDataType::Int4 = ShaderData(4 * 4, 4, GL_INT);

	ShaderData ShaderDataType::Mat3 = ShaderData(4 * 3 * 3, 3 * 3, GL_FLOAT);
	ShaderData ShaderDataType::Mat4 = ShaderData(4 * 4 * 4, 4 * 4, GL_FLOAT);

	ShaderData ShaderDataType::Bool = ShaderData(1, 1, GL_BOOL);


	ShaderData::ShaderData() {}
	ShaderData::~ShaderData() {}
}