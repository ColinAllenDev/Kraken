#pragma once
// ShaderDataType:
// * An abstract data type to be used by any rendering API.
// * Must Include:
//		* Size
//		* Component Count
//		* API Conversion Logic (OpenGL->SDT, Vulkan->SDT, etc.)

namespace Kraken {	
	struct ShaderData {
		uint32_t Size;
		uint32_t ComponentCount;
		uint32_t GLType;

		ShaderData();
		~ShaderData();
		ShaderData(uint32_t size, uint32_t count) : Size(size), ComponentCount(count) {}
		ShaderData(uint32_t size, uint32_t count, uint32_t glType) : Size(size), ComponentCount(count), GLType(glType) {}
	};

	class ShaderDataType {
	public:
		static ShaderData Float;
		static ShaderData Float2;
		static ShaderData Float3;
		static ShaderData Float4;
		
		static ShaderData Int;
		static ShaderData Int2;
		static ShaderData Int3;
		static ShaderData Int4;

		static ShaderData Mat3;
		static ShaderData Mat4;

		static ShaderData Bool;
	};
}