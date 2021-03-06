#include <time.h>

#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\maths\maths.h"

#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\indexbuffer.h"
#include "src\graphics\buffers\vertexarray.h"

#include "src\graphics\renderer2d.h"
#include "src\graphics\simple2drenderer.h"
#include "src\graphics\batchrenderer2d.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src\utils\timer.h"

#define BATCH_RENDERER 1

int main()
{
	using namespace GameEngine;
	using namespace graphics;
	using namespace maths;

	Window window("NGen3", 960, 540);
	//glClearColor(1, 1, 1, 1);

	mat4 ortho = mat4::orthographic(0.0f, 24.0f, 0.0f, 16.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	std::vector<Renderable2D*> sprites;

	srand(time(NULL));

	for (float y = 0; y < 16.0f; y+= 0.05)
	{
		for (float x = 0; x < 24.0f; x+= 0.05)
		{
			sprites.push_back(new 
#if BATCH_RENDERER
			Sprite
#else
			StaticSprite
#endif
			(x, y, 0.04f, 0.04f, maths::vec4(0, rand() % 1000 / 1000.0f, 1, 1)
#if !BATCH_RENDERER
				, shader
#endif
				));
		}
	}

#if BATCH_RENDERER
	Sprite sprite(0,0,8,9, vec4(0.8,0.2,0.2,1.0));
	Sprite sprite2(8,0,8,9, vec4(0.2, 0.2, 0.8,1.0));
	BatchRenderer2D renderer;

#else
	StaticSprite sprite(0, 0, 8, 9, vec4(0.8, 0.2, 0.2, 1.0), shader);
	StaticSprite sprite2(8, 0, 8, 9, vec4(0.2, 0.2, 0.8, 1.0), shader);
	Simple2DRenderer renderer;
#endif

	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader.setUniform4f("col", vec4(0.1f, 0.3f, 0.7f, 1.0f));

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	double x, y;
	int width, height;
	while (!window.closed())
	{
		window.clear();
		window.getMousePosition(x, y);
		window.getWindowSize(width, height);
		shader.setUniform2f("light_pos", vec2( (float)(x * 24.0f / width), (float)(16.0f - y * 16.0f / height)));
		shader.setUniform1f("intensity_multiplier", rand() % 2);
#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
#if BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();
		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	return 0;
}