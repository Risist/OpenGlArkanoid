#pragma once

/// Way of abstracting OpenGl drawing process

//#include "Material.h"
//#include "BufferLayout.h"
#include "RenderObject.h"

namespace Rendering
{
	struct Vertex
	{
		glm::vec2 position;
		glm::vec3 color;
	};
}
