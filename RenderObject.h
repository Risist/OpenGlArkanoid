#pragma once
#include "BufferLayout.h"

namespace Rendering
{
	
	/// primitive type drawn by RenderObject
	enum class EPrimitiveType : GLenum
	{
		ELines = GL_LINES,
		ETriangles = GL_TRIANGLES,
	};

	/// Rendering hint for speeding up ogl operations
	enum class EDrawMode
	{
		EStaticDraw = GL_STATIC_DRAW,
		EDynamicDraw = GL_DYNAMIC_DRAW,
		EStreamDraw = GL_STREAM_DRAW,
	};

	template<
		EDrawMode drawMode = EDrawMode::EStaticDraw,
		EPrimitiveType primitiveType = EPrimitiveType::ETriangles
		>
	class RenderObject
	{
	public:
		~RenderObject()
		{
			if(vaoId != -1)
				glDeleteVertexArrays(1, &vaoId);
			ReleaseVertexBuffer();
		}

		void Display(int startVertex = 0)
		{
			BindVao();
			material.Bind();
			glDrawArrays((GLenum)primitiveType, startVertex, vertexCount);
		}
		void Display(int startVertex, int displayCount)
		{
			BindVao();
			material.Bind();
			glDrawArrays((GLenum)primitiveType, startVertex, displayCount);
		}
		
	public:
		void Init()
		{
			glGenVertexArrays(1, &vaoId);
			BindVao();
		}

		template<typename VertexTy>
		void GenerateVertexBuffer(VertexTy* data, GLuint vertexCount)
		{
			ReleaseVertexBuffer();
			this->vertexCount = vertexCount;
			bufferData = data;

			BindVao();
			glGenBuffers(1, &bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(VertexTy) * vertexCount, data, (GLenum)drawMode);
		}
		void ReleaseVertexBuffer()
		{
			if (bufferId != -1)
				glDeleteBuffers(1, &bufferId);
		}

		BufferLayout layout;
		void ApplyLayout()
		{
			BindVao();
			layout.ApplyLayout(material);
		}

		Material material;
	private:
		void* bufferData = nullptr;
		GLuint vertexCount = 0;
		GLuint bufferId = -1;

		GLuint vaoId = -1;
		inline void BindVao() { glBindVertexArray(vaoId); }
	};


	/*
	/////  ////  Usage example:
	////////////////////////////
	{
		Rendering::RenderObject<Rendering::EDrawMode::EStaticDraw, Rendering::EPrimitiveType::ELines> obj;
		obj.Init();

		obj.material.InitProgramFromFile("BasicShader.vert", "BasicShader.frag");
	
		Vertex v[] = {
			{  0.f, 0.5f,   0.9f, 0.5f, 0.f},
			{-0.5f, 0.5f,   0.0f, 1.f, 0.f}
		};
		obj.GenerateVertexBuffer(v, 2);

		obj.material.Bind();
		obj.layout.AddLayoutElem<Rendering::BufferLayout::EFloat>("position", 2);
		obj.layout.AddLayoutElem<Rendering::BufferLayout::EFloat>("color", 3);
		obj.ApplyLayout();


		...
		obj.Display();
	}
	*/
}

