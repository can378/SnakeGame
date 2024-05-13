#include "func.h"

#include "SDL_image.h"
#include <windows.h>
#include <string>
#include <vector>
#include <atlstr.h>

#include <iostream>
#include <iomanip>
#include <sstream>


int g_input_shoot;
int nowInput;
int keyUpNum;
int keyDownNum;
std::vector<int> g_input_stack;



double g_elapsed_time_ms;

int g_X;
int g_Y;

int sizeH;
int sizeW;

//image
SDL_Rect g_airplane_pos;
SDL_Texture* g_star_texture;
SDL_Texture* g_spaceship_texture;
SDL_Rect g_spaceship_rect;
SDL_Rect g_star_rect;

SDL_Rect g_bg_source_rect;
SDL_Rect g_bg_destination_rect;
SDL_Texture* g_bg_texture;


//sound
Mix_Chunk* wave1_;
Mix_Music* music1_;

//text
TTF_Font* game_font_;
SDL_Texture* text_score;
SDL_Rect text_score_rect;

SDL_Texture* text_kr;
SDL_Rect text_kr_rect;

int score;






//////////////////////////////////////////////////////////////////////////
// 숫자를 문자 Texture로 만드는 함수.
void UpdateScore(int num)
{
	//destroy from memory
	if (text_score != 0)
	{
		SDL_DestroyTexture(text_score);		// !!!중요!!!  이미 생성되어있는 texture 가 있으면 반드시 메모리에서 지워야한다. !!!
		text_score = 0;
	}

	//change to 00000
	std::ostringstream oss;
	oss << std::setw(5) << std::setfill('0') << num;
	std::string scoreResult = oss.str();



	SDL_Color black = { 255, 255, 255, 0 };
	//SDL_Surface* tmp_surface = TTF_RenderText_Blended(game_font_, std::to_string((long long)num).c_str(), black);
	SDL_Surface* tmp_surface = TTF_RenderText_Blended(game_font_, scoreResult.c_str(), black);

	text_score_rect.x = 0;
	text_score_rect.y = 0;
	text_score_rect.w = tmp_surface->w;
	text_score_rect.h = tmp_surface->h;

	text_score = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	SDL_FreeSurface(tmp_surface);
}




class Bullet 
{

public:
	Bullet(int x, int y, bool isFly)
	{
		g_bullet_pos.x = x;
		g_bullet_pos.y = y;
		g_bullet_pos.w = 40;
		g_bullet_pos.h = 40;
		isFlying = isFly;
	};

	void DrawBullet()
	{
		if (isFlying)
		{
			SDL_RenderCopy(g_renderer, g_star_texture,&g_star_rect,	&g_bullet_pos);
			
			Flight();
		}
	}
	void Flight()
	{
		g_bullet_pos.y -= 25;

		if (g_bullet_pos.y < -g_bullet_pos.h/2) 
		{ 
			isFlying = false;  
		}
	}
	
	SDL_Rect g_bullet_pos;
	bool isFlying;

};


std::vector<Bullet> bullets(5, Bullet(0, 0, false));
/////////////////////////////////////////////////////////////
void InitGame() 
{
	/*
	g_input_shoot = 0;
	g_input_stack.push_back(0);

	keyUpNum = 10;
	keyDownNum = 10;
	g_flag_running = true;

	g_X = 0;
	g_Y = 10;

	sizeH = 20;
	sizeW = 30;

	g_elapsed_time_ms = 0;


	//Drawing////////////////////////////////////////////////////////////////
	
	// BG
	SDL_Surface* bg_surface = IMG_Load("../Resources/nightSky.png");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	g_bg_source_rect.x = 0;
	g_bg_source_rect.y = 0;
	g_bg_source_rect.w = 838;
	g_bg_source_rect.h = 648;

	g_bg_destination_rect.x = 0;
	g_bg_destination_rect.y = 0;
	g_bg_destination_rect.w = 838;
	g_bg_destination_rect.h = 648;

	//star
	SDL_Surface* g_surface_star = IMG_Load("../Resources/star.png");
	g_star_texture= SDL_CreateTextureFromSurface(g_renderer, g_surface_star);
	SDL_FreeSurface(g_surface_star);
	
	g_star_rect = { 0  , 0, 582, 558 };

	//spaceship
	SDL_Surface* g_surface_spaceship= IMG_Load("../Resources/spaceship2.png");
	g_spaceship_texture = SDL_CreateTextureFromSurface(g_renderer, g_surface_spaceship);
	SDL_FreeSurface(g_surface_spaceship);

	g_spaceship_rect = { 0 , 0, 228,440};


	//drawing airplane
	int win_w, win_h;
	SDL_GetWindowSize(g_window, &win_w, &win_h);
	g_airplane_pos.w = 70;
	g_airplane_pos.h = 130;
	g_airplane_pos.x = win_w / 2 - g_airplane_pos.w / 2;
	g_airplane_pos.y = win_h / 2 - g_airplane_pos.h / 2;



	//Text////////////////////////////////////////////////////////////////
	game_font_ = TTF_OpenFont("../Resources/IBMPlexSansKR-Bold.ttf", 20);
	
	TTF_Font* font2 = TTF_OpenFont("../Resources/IBMPlexSansKR-SemiBold.ttf", 20);
	SDL_Color textColor = { 255,255, 255, 255 };
	SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(font2, CW2A(L"점수", CP_UTF8), textColor);

	text_kr_rect.x = 0;
	text_kr_rect.y = 0;
	text_kr_rect.w = tmp_surface->w;
	text_kr_rect.h = tmp_surface->h;

	text_kr = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	TTF_CloseFont(font2);



	//Sound//////////////////////////////////////////////////////////////
	// Set the music volume 
	Mix_VolumeMusic(128);

	// Load the wave and mp3 files 
	wave1_ = Mix_LoadWAV("../Resources/blaster.mp3");
	if (wave1_ == NULL)
	{	printf("Couldn't load the wav: %s\n", Mix_GetError());	}

	music1_ = Mix_LoadMUS("../Resources/crazy_chase.mp3");
	if (!music1_)
	{	printf("Couldn't load the mp3 file: %s\n", Mix_GetError());	}
	
	
	//play bgm
	Mix_PlayMusic(music1_, -1);

	//score
	score = 0;
	UpdateScore(score);






	*/

	//Organize///////////////////////////////////////////////////////////////
	// std::cout 출력에 버퍼를 사용하여, 출력 속도가 느려지는 현상을 피한다.
	setvbuf(stdout, NULL, _IOLBF, 4096);

	// Clear the console screen.
	system("cls");
}



/////////////////////////////////////////////////////////////
void Update() 
{
	//std::cout << g_input_shoot << "\n";

	nowInput = g_input_stack[g_input_stack.size() - 1];

	//left
	if (nowInput == 1)
	{ 
		g_airplane_pos.x -= 10;
	}
	//right
	else if (nowInput == 2)
	{ 	
		g_airplane_pos.x += 10;
	}
	//up
	else if (nowInput == 3)
	{ 	
		g_airplane_pos.y -= 10;
	}
	//down
	else if (nowInput == 4)
	{ 
		g_airplane_pos.y += 10;
	}

	

	
	if (g_airplane_pos.x > 838 - g_airplane_pos.w)
	{
		g_airplane_pos.x = 0;
	}
	else if (g_airplane_pos.x < 0)
	{
		g_airplane_pos.x = 838 - g_airplane_pos.w;
	}

	if (g_airplane_pos.y > 648-g_airplane_pos.h)
	{
		g_airplane_pos.y = 0;
	}
	else if (g_airplane_pos.y < 0) 
	{
		g_airplane_pos.y = 648 - g_airplane_pos.h;
	}

	g_elapsed_time_ms += 33;


}



/////////////////////////////////////////////////////////////
void Render() 
{

	SDL_RenderClear(g_renderer);
	/*
	// Background drawing
	SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);
	
	// Airplane drawing
	SDL_RenderCopy(g_renderer, g_spaceship_texture, &g_spaceship_rect, &g_airplane_pos);

	// Bullet drawing
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isFlying == true)
		{	bullets[i].DrawBullet();	}
	}



	//text drawing
	int win_w, win_h;
	SDL_GetWindowSize(g_window, &win_w, &win_h);

	SDL_Rect tmp_r;
	tmp_r.x = 20;
	tmp_r.y = 20;
	tmp_r.w = text_kr_rect.w;
	tmp_r.h = text_kr_rect.h;
	SDL_RenderCopy(g_renderer, text_kr, &text_kr_rect, &tmp_r);


	// score drawing
	SDL_Rect r;
	//r.x = win_w / 2 - text_score_rect.w / 2;
	r.x = tmp_r.x+text_kr_rect.w+20;
	r.y = tmp_r.y;
	r.w = text_score_rect.w;
	r.h = text_score_rect.h;
	SDL_RenderCopy(g_renderer, text_score, 0, &r);

	*/
	

	//draw to screen
	SDL_RenderPresent(g_renderer);


}








/////////////////////////////////////////////////////////////
void HandleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) 
	{
		switch (event.type) 
		{

		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				g_input_shoot = 1;
			}

			if (event.key.keysym.sym == SDLK_LEFT) 
			{
				keyDownNum = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) 
			{
				keyDownNum = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP) 
			{
				keyDownNum = 3;
			}			
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				keyDownNum = 4;
			}

			
			if (keyDownNum != 10)
			{
				for (int i = g_input_stack.size() - 1; i >= 0; i--)
				{
					if (g_input_stack[i] != keyDownNum && keyDownNum != 10)
					{
						if (i == 0) { g_input_stack.push_back(keyDownNum);}
					}
					else { break; }
				}
				keyDownNum = 10;
			}
			
			
			
			
			break;

		case SDL_KEYUP:
			
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				g_input_shoot = 0;
			}


			if (event.key.keysym.sym == SDLK_LEFT) 
			{
				keyUpNum = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) 
			{
				keyUpNum = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP) 
			{
				keyUpNum = 3;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				keyUpNum = 4;
			}

			


			for (int i = g_input_stack.size() - 1; i >= 0; i--)
			{
				if (g_input_stack[i] == keyUpNum)
				{
					g_input_stack.erase(g_input_stack.begin()+i);
					keyUpNum = 10;
				}
			}

			
			
			break;

		case SDL_MOUSEBUTTONDOWN:
			// 마우스 왼쪽 버튼이 눌려 졌을 때.
			break;

		default:
			break;
		}
	}


	//std::cout << "g_input=" << g_input<<"\n";

}



/////////////////////////////////////////////////////////////
// 사용된 자원(이미지, 사운드 등)과 메모리 등을 해제
void ClearGame()
{
	SDL_DestroyTexture(g_spaceship_texture);
	SDL_DestroyTexture(g_star_texture);
	if (wave1_) Mix_FreeChunk(wave1_);
	if (music1_) Mix_FreeMusic(music1_);
	TTF_CloseFont(game_font_);
	SDL_DestroyTexture(text_kr);
}
