#ifndef _QUAD_h_
#define _QUAD_h_


#include <glad/glad.h>
#include "shader.h"


class Quad
{
public:
	GLuint m_vao, m_v, m_colorLoc;
	CShader m_colorShader;

	Quad()
	{
		m_vao = 0;
	}

	void init(float x0, float y0, float x1, float y1)
	{
		GLfloat data[] =
		{
			x0, y0,
			x1, y0,
			x1, y1,

			x0, y0,
			x1, y1,
			x0, y1,
		};

		// create vao
		glGenVertexArrays(1, &m_vao);
		// setting vao as current
		glBindVertexArray(m_vao);

		// uploading vertexes
		glGenBuffers(1, &m_v);
		glBindBuffer(GL_ARRAY_BUFFER, m_v);
		glEnableVertexAttribArray(0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		// unbinding
		glBindVertexArray(NULL);

		if (m_colorShader.loadShader("color_shader.vs", "color_shader.fs") == false)
		{
			printf("Error in shaders. Press enter to finish-->\n");
			getchar();
			exit(1);
		}
		m_colorShader.setCurrent();
		m_colorLoc = glGetUniformLocation(m_colorShader.getProgram(), "color");
		glUniform3f(m_colorLoc, 1, 1, 1);
		m_colorShader.unbind();
	}

	void render(float r, float g, float b)
	{
		glDisable(GL_DEPTH_TEST);
		m_colorShader.setCurrent();
		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_v);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);

		glUniform3f(m_colorLoc, r, g, b);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);
		m_colorShader.unbind();
		glEnable(GL_DEPTH_TEST);
		printf("Quad render called!\n");
	}
};

#endif