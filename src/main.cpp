#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>



Color green = {173,204,96,255};
Color darkGreen = {43,51,24,255};


int cellSize = 30; 
int cellCount = 25;

double lastUpdateTime = 0;

bool eventTriggered(double interval)
{
	double currentTime = GetTime();
	if(currentTime - lastUpdateTime > interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

class Snake
{
	public:
		std::deque<Vector2> body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
		Vector2 direction = Vector2{1,0};
		

		void Draw()
		{
			for(unsigned int i = 0; i < body.size(); i++)
			{
				float x = body[i].x;
				float y = body[i].y;
				Rectangle rect = {x*cellSize,y*cellSize,cellSize,cellSize};
				DrawRectangleRounded(rect,0.5,6,darkGreen);	
			}

		}

		void Update()
		{
			body.pop_back();
			body.push_front(Vector2Add(body[0],direction));
		}
};

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
	Snake snake = Snake();
		
	while(WindowShouldClose() == false)
	{
	BeginDrawing();

	if (eventTriggered(0.2))
	{
		snake.Update();
	}

	//Snake Movement
	if(IsKeyPressed(KEY_UP) && snake.direction.y != 1)
	{
		snake.direction = Vector2{0,-1};
	}
	if(IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
	{
		snake.direction = Vector2{0,1};
	}
	if(IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
	{
		snake.direction = Vector2{-1,0};
	}
	if(IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
	{
		snake.direction = Vector2{1,0};
	}
	//Drawing
	ClearBackground(green);
	food.Draw();
	snake.Draw();
	
	EndDrawing();
	}

	CloseWindow();
	return 0; 
}