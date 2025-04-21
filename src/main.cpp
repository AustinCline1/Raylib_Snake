#include <raylib.h>



Color green = {173,204,96,255};
Color darkGreen = {43,51,24,255};

int main() 
{
	SetTargetFPS(60);

	InitWindow(750,750, "Retro Snake");
		
	while(WindowShouldClose() == false)
	{
	BeginDrawing();

	//Drawing
	ClearBackground(green);
	
	
	EndDrawing();
	}

	CloseWindow();
	return 0; 
}