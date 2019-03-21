#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\maths\maths.h"

#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\indexbuffer.h"
#include "src\graphics\buffers\vertexarray.h"

#include "src\graphics\renderer2d.h"
#include "src\graphics\simple2drenderer.h"

int main()
{
	using namespace GameEngine;
	using namespace graphics;
	using namespace maths;

	Window window("NGen3", 960, 540);
	//glClearColor(1, 1, 1, 1);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));


	Renderable2D sprite(vec3(0,0,0), vec2(8,9), vec4(0.8,0.2,0.2,1.0), shader);
	Renderable2D sprite2(vec3(8, 0, 0), vec2(8, 9), vec4(0.2, 0.2, 0.8,1.0), shader);
	Simple2DRenderer renderer;

	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader.setUniform4f("col", vec4(0.1f, 0.3f, 0.7f, 1.0f));


	while (!window.closed())
	{
		window.clear();
		double x, y;
		int width, height;
		window.getMousePosition(x, y);
		window.getWindowSize(width, height);
		shader.setUniform2f("light_pos", vec2( (float)(x * 16.0f / width), (float)(9.0f - y * 9.0f / height)));
		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.flush();
		window.update();
	}

	return 0;
}