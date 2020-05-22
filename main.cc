/*
 * File: main.cc
 * Description: This is a main entry point for application
 *
 * sdl200521
 * Copyright 2020 (c) Philosoph228 <philosoph228@gmail.com>
 *
 */

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
  // Init SDL
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window =
      SDL_CreateWindow("sdl200521", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

  SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

  // Init rect
  SDL_Rect rect(0, 0, 4, 4);
  float x_speed = 0;
  float y_speed = 0;
  float pos_x = 0;
  float pos_y = 0;

  // Main loop reusable objects
  SDL_Event event{};
  bool bRunning = true;
  uint32_t then = SDL_GetTicks();

  // Main loop itself
  while (bRunning) {
    // Uncomment to simulate CPU lags:
    // SDL_Delay(10);

    SDL_PollEvent(&event);

    uint32_t now = SDL_GetTicks();
    float delta = now - then;
    then = now;

    if (event.type == SDL_QUIT) {
      bRunning = false;
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_LEFT) {
        x_speed = -1.f;
      } else if (event.key.keysym.sym == SDLK_RIGHT) {
        x_speed = 1.f;
      } else if (event.key.keysym.sym == SDLK_UP) {
        y_speed = -1.f;
      } else if (event.key.keysym.sym == SDLK_DOWN) {
        y_speed = 1.f;
      }
    } else if (event.type == SDL_KEYUP) {
      if (event.key.keysym.sym == SDLK_LEFT ||
          event.key.keysym.sym == SDLK_RIGHT) {
        // Set horizontal movement speed to 0 if key has been unpressed
        x_speed = 0.f;
      } else if (event.key.keysym.sym == SDLK_UP ||
                 event.key.keysym.sym == SDLK_DOWN) {
        y_speed = 0.f;
      }
    }

    /*
    // Switch statement approach
    switch (event.type) {
      case SDL_QUIT:
        bRunning = false;
        break;
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
            x_speed = -1.f;
            break;
          case SDLK_RIGHT:
            x_speed = 1.f;
            break;
          case SDLK_UP:
            y_speed = -1.f;
            break;
          case SDLK_DOWN:
            y_speed = 1.f;
            break;
        }
      } break;
      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
          case SDLK_DOWN:
            x_speed = 0.f;
            break;
          case SDLK_UP:
          case SDLK_RIGHT:
            y_speed = 0.f;
            break;
        }
        break;
    }
    */

    // As your time-based delta is a REAL number, to avoid precision stripping
    // you need to store your coordinates as real number too
    pos_x += delta * x_speed;
    pos_y += delta * y_speed;

    // Then apply real value coordinates to natural one
    rect.x = pos_x;
    rect.y = pos_y;

    SDL_FillRect(screenSurface, &rect,
                 SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));
    SDL_UpdateWindowSurface(window);
  }

  SDL_Quit();
  return 0;
}
