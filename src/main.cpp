#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>



Color green = {173,204,96,255};
Color darkGreen = {43,51,24,255};


int cellSize = 30; 
int cellCount = 25;

double lastUpdateTime = 0;

bool ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
	for(unsigned int i = 0; i < deque.size(); i++)
	{
		if(Vector2Equals(deque[i],element))
		{
			return true;
		}
	}
	return false;

}

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
		bool addSegment = false;
		

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
			body.push_front(Vector2Add(body[0],direction));
			if(addSegment)
			{
				addSegment = false;
			}else
			{
			body.pop_back();
			}
		}


		void Reset()
		{
			body = {Vector2{6,9},Vector2{5,9},Vector2{4,9}};
			direction = Vector2{1,0};
		}
};

class Food 
{

public:
	Vector2 position;
	Texture2D texture;

	Food(std::deque<Vector2> body)
	{
		Image image = LoadImage("graphics/food.png");
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
		position = GenerateRandomPosition(body);
	}

	~Food()
	{
		UnloadTexture(texture);
	}

	void Draw() 
	{
		DrawTexture(texture,position.x*cellSize,position.y*cellSize,WHITE);
	}

	Vector2 GenerateRandomCell()
	{
		float x = GetRandomValue(0,cellCount -1);
		float y = GetRandomValue(0,cellCount -1);
		return Vector2{x,y};
	}
	
	Vector2 GenerateRandomPosition(std::deque<Vector2> body)
	{
		Vector2 position = GenerateRandomCell();
		while(ElementInDeque(position,body))
		{
			position = GenerateRandomCell();
		}
		return position;
	}

};

class Game 
{
	public: 
		Snake snake = Snake();
		Food food = Food(snake.body);
		bool running = true;

		void Draw()
		{
			food.Draw();
			snake.Draw();
		}

		void Update()
		{
			if(running)
			{
			snake.Update();
			CheckCollisionWithFood();
			CheckCollisionWithWall();
			CheckCollisionWithSnake();
			}	
		}

		void CheckCollisionWithFood()
		{
			if(Vector2Equals(snake.body[0],food.position))
			{
				food.position = food.GenerateRandomPosition(snake.body);
				snake.addSegment = true;
			}
		}

		void CheckCollisionWithWall()
		{
			if(snake.body[0].x < 0 || snake.body[0].x == cellCount || snake.body[0].y < 0 || snake.body[0].y == cellCount)
			{
				GameOver();
			} 
		}

		void CheckCollisionWithSnake()
		{	
			std::deque<Vector2> headlessBody = snake.body;
			headlessBody.pop_front();
			if(ElementInDeque(snake.body[0],headlessBody))
			{
				GameOver();
			}
		}

		void GameOver()
		{
			snake.Reset();
			food.position = food.GenerateRandomPosition(snake.body);
			running = false;
		}
};

int main() 
{
	SetTargetFPS(60);
	InitWindow(cellSize*cellCount,cellSize*cellCount, "Retro Snake");
	Game game = Game();
		
	while(WindowShouldClose() == false)
	{
	BeginDrawing();

	if (eventTriggered(0.2))
	{
		game.Update();
	}

	//Snake Movement
	if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
	{
		game.snake.direction = Vector2{0,-1};
		game.running = true;
	}
	if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
	{
		game.snake.direction = Vector2{0,1};
		game.running = true;
	}
	if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
	{
		game.snake.direction = Vector2{-1,0};
		game.running = true;
	}
	if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
	{
		game.snake.direction = Vector2{1,0};
		game.running = true;
	}
	ClearBackground(green);
	game.Draw();
	EndDrawing();
	}

	CloseWindow();
	return 0; 
}