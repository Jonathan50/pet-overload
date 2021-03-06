#include "overload.h"

#define HASHSIZE 101

static struct {
  const char *name;
  SDL_Texture *texture;
} cache[HASHSIZE] = {0};

/* Hash function is from here:
   http://stackoverflow.com/a/4384446 */

Uint8 hash(const char *s)
{
  Uint32 hashval;

  for (hashval = 0; *s; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

SDL_Texture *GetTexture(const char *name, SDL_Renderer *renderer)
{
  Uint8 hashval = hash(name);

#ifdef DEBUG
  if (cache[hashval].texture != NULL
      && strcmp(name, cache[hashval].name) != 0) {
    fprintf(stderr, "Debug: hash collision occured between %s and %s!\n",
	    name, cache[hashval].name);
  }
#endif

  if (cache[hashval].texture == NULL) {
    SDL_Surface *surface;
    char path[128];

    snprintf(path, 128, "%s/%s.bmp", assetspath, name);
#ifdef DEBUG
    fprintf(stderr, "Debug: loading file %s\n", path);
#endif
    surface = SDL_LoadBMP(path);
    cache[hashval].name = name;
    cache[hashval].texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (cache[hashval].texture == NULL) {
      fprintf(stderr, "Error: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
  }

  return cache[hashval].texture;
}
