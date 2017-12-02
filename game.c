#include "overload.h"
#include <time.h>

static Sprite *player;

void RandomPos(Sprite *sp)
{
  sp->rect.x = rand() % WINDOW_WIDTH;
  sp->rect.y = rand() % WINDOW_HEIGHT;
}

void InitGame(void)
{
  player = MakeSprite("player");
  srand(time(NULL));
}

void UpdateGame(void)
{
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);

  if (keystate[SDL_SCANCODE_A])
    player->rect.x = (player->rect.x - SPEED) % WINDOW_WIDTH;

  if (keystate[SDL_SCANCODE_D])
    player->rect.x = (player->rect.x + SPEED) % WINDOW_WIDTH;

  if (keystate[SDL_SCANCODE_W])
    player->rect.y = (player->rect.y - SPEED) % WINDOW_HEIGHT;

  if (keystate[SDL_SCANCODE_S])
    player->rect.y = (player->rect.y + SPEED) % WINDOW_HEIGHT;

  switch ((rand() % 60)) {
  case 3:
    RandomPos(MakeSprite("dog1"));
    break;
  case 11:
    RandomPos(MakeSprite("cat1"));
    break;
  }
}
