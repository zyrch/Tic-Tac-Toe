//
// Created by root on 1/3/18.
//

#include <SDL2/SDL.h>

#ifndef TIC_TAC_TOE_SCREEN_H
#define TIC_TAC_TOE_SCREEN_H


class Screen {

public:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    Uint32 *buffer;
public:

    Screen();
    bool init();
    void update();
    void setUp(Uint8 red, Uint8 green, Uint8 blue) const;
    bool processEvent();
    void drawLines() const;
    void drawCross(int x, int y) const;
    void drawNots(int x, int y) const;
    void gameEnds();
    void close();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Event event{};

};


#endif //TIC_TAC_TOE_SCREEN_H
