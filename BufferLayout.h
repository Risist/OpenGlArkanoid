#pragma once
#include "Material.h"

namespace Rendering
{
	class BufferLayout
	{
	public:
		
		void AddLayoutElemFloat(string_t name, GLuint size)
		{
			_elems.push_back({ name, GL_FLOAT, size, size*sizeof(float) });
			_currentStride += sizeof(float) * size;
		}
		void AddLayoutElemDouble(string_t name, GLuint size)
		{
			_elems.push_back({ name, GL_DOUBLE, size, size * sizeof(double) });
			_currentStride += sizeof(double) * size;
		}

		void ApplyLayout(const Material& material)
		{
			GLuint currentOffset = 0;
			for (auto it : _elems)
			{
				GLint attribId = material.GetAtribId(it.name);
				glVertexAttribPointer(attribId, it.size, it.type, false, _currentStride, (void*)(currentOffset));
				glEnableVertexAttribArray(attribId);

				currentOffset += it.offset;
			}
		}

	private:
		struct LayoutElem
		{
			string_t name;
			GLuint type;
			GLuint size;
			GLuint offset;
		};
		std::vector<LayoutElem> _elems;
		GLuint _currentStride = 0;
	};
}

