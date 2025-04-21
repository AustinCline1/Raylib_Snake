#include <raylib.h>



Color green = {173,204,96,255};
Color darkGreen = {43,51,24,255};


int cellSize = 30; 
int cellCount = 25;

class Food 
{

public:
	Vector2 position;
	Texture2D texture;

	Food()
	{
		Image image = LoadImage("graphics/food.png");
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
		position = GenerateRandomPosition();
	}

	~Food()
	{
		UnloadTexture(texture);
	}

	void Draw() 
	{
		DrawTexture(texture,position.x*cellSize,position.y*cellSize,WHITE);
	}
	
	Vector2 GenerateRandomPosition()
	{
		float x = GetRandomValue(0,cellCount -1);
		float y = GetRandomValue(0,cellCount -1);
		return Vector2{x,y};
	}

};


int main() 
{
	SetTargetFPS(60);
	InitWindow(cellSize*cellCount,cellSize*cellCount, "Retro Snake");
	Food food = Food();
		
	while(WindowShouldClose() == false)
	{
	BeginDrawing();

	//Drawing
	ClearBackground(green);
	food.Draw();
	
	EndDrawing();
	}

	CloseWindow();
	return 0; 
}