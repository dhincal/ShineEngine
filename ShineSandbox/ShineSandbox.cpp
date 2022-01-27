#include <iostream>
#include "EngineContext.h"

EngineContext engineContext;

void OnRender()
{
	

	std::cout << "Renderin'" << "\n";
	

}


int main()
{
	

	engineContext.Init_GLFW();

	engineContext.SetRenderEvent(OnRender);
	engineContext.StartWindow(640,480,"Hello Engine");

	//engineContext.Renderer.Setup_Triangle();

	engineContext.StartRender();
	


}


