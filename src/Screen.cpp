//
// Created by root on 1/3/18.
//

#include "../Headers/Screen.h"
#include <cmath>
#include <iostream>
#include <cstring>


using namespace std;

int turns = 0;

int game[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
};

Screen::Screen() : window(nullptr), renderer(nullptr), texture(nullptr), buffer(nullptr) {

}

bool Screen::init() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        //In this case the SDL_Init fails
        return false;
    }

    // Create an application window with the following settings
    window = SDL_CreateWindow(
            "TIC-TAC-TOE",                          // Window title
            SDL_WINDOWPOS_UNDEFINED,                  // Initial X position
            SDL_WINDOWPOS_UNDEFINED,                  // Initial Y position
            SCREEN_WIDTH,                                // Width in pixels
            SCREEN_HEIGHT,                               // Height in pixeld
            SDL_WINDOW_SHOWN                       // A SDL_Window Flag
    );

    // Check that the window was successfully created
    if (window == nullptr) {
        // In the case that the window could not be made...
        return false;

    }

    renderer = SDL_CreateRenderer(
            window,                                             // The window where rendering is to be done
            -1,                                           // The index of the rendering driver to initialize, or -1 to
            // initialize the first one supporting the requested flags
            SDL_RENDERER_PRESENTVSYNC                     // Present is synchronized with the refresh rate
    );

    if (renderer == nullptr) {
        // In the case that the renderer could not be created...
        return false;
    }

    texture = SDL_CreateTexture(
            renderer,                                              // The rendering context
            SDL_PIXELFORMAT_RGBA8888,                       // Format, In this case we have on 4 byte for each pixel
            /*
             * SDL_PIXELFORMAT_RGBA8888 : Consist of three bytes for colour information
             * Each byte have a shade of the colour red green blue respectively (0 to 255)
             * The fourth byte is for transparency
             */

            SDL_TEXTUREACCESS_STATIC,                 // *The Way to write the pixels
            SCREEN_WIDTH,                                    // Screen Width
            SCREEN_HEIGHT                                    // Screen Height
    );

    if (texture == nullptr) {
        return false;
    }

    // A Block of memory we will use to update the texture
    buffer = new Uint32[SCREEN_WIDTH *
                        SCREEN_HEIGHT];                       // An array for each pixel .. return NULL for error

    memset(
            buffer,                                              // buffer whose memory has to be set
            255,                                              // Set each memory to the passes argument
            SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)     // Total data (in bytes)
    );

    return true;

}

void Screen::update() {

    SDL_UpdateTexture(
            texture,                              // The texture to update
            nullptr,                         // A pointer to the rectangle of pixels to update, NULL to update all
            buffer,                               // The row of pixel data
            SCREEN_WIDTH * sizeof(Uint32)   // No of bytes between the pixel data
    );

    SDL_RenderClear(renderer);           // Clears the renderer

    // copy's the texture to the renderer
    SDL_RenderCopy(
            renderer,                               // The Renderer Which should copy the texture
            texture,                                // The texture which will be copied into the renderer
            nullptr,                         // Pointer to source rectangle of pixels, NULL for all
            nullptr                          // Pointer to destination rectangle of pixels, NULL for all
    );

    // Present the renderer to the window
    SDL_RenderPresent(renderer);

}

void Screen::setUp(Uint8 red, Uint8 green, Uint8 blue) const {


    Uint32 color = 0;                               // An unsigned int of 32 bytes

    color += red;
    color <<= 8;                                    // shift 8 bits to the left
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i) {
        buffer[i] = color;
    }


}

bool Screen::processEvent() {

    int x = event.button.x, y = event.button.y;


    while (SDL_PollEvent(
            &event)) {                                // SDL_PollEvent(&event) : Return 1 if events are pending otherwise return 0

        if (event.type == SDL_QUIT) {
            // In this case the event is of quiting the window then jump out the loop
            return false;
        } else if (event.type == SDL_MOUSEBUTTONUP && turns % 2 == 1) {
            if (x > 200 && x < 333 && y > 100 && y < 233 && game[0][0] != 0 && game[0][0] != 10) {
                drawNots(267, 167);
                game[0][0] = 0;
                turns++;                                     //0 for nots
            } else if (x > 333 && x < 466 && y > 100 && y < 233 && game[0][1] != 0 && game[0][1] != 10) {
                drawNots(400, 167);
                game[0][1] = 0;
                turns++;
            } else if (x > 466 && x < 600 && y > 100 && y < 233 && game[0][2] != 0 && game[0][2] != 10) {
                drawNots(533, 167);
                game[0][2] = 0;
                turns++;
            } else if (x > 200 && x < 333 && y > 233 && y < 366 && game[1][0] != 0 && game[1][0] != 10) {
                drawNots(267, 300);
                game[1][0] = 0;
                turns++;
            } else if (x > 333 && x < 466 && y > 233 && y < 366 && game[1][1] != 0 && game[1][1] != 10) {
                drawNots(400, 300);
                game[1][1] = 0;
                turns++;
            } else if (x > 466 && x < 600 && y > 233 && y < 366 && game[1][2] != 0 && game[1][2] != 10) {
                drawNots(533, 300);
                game[1][2] = 0;
                turns++;
            } else if (x > 200 && x < 333 && y > 366 && y < 500 && game[2][0] != 0 && game[2][0] != 10) {
                drawNots(267, 433);
                game[2][0] = 0;
                turns++;
            } else if (x > 333 && x < 466 && y > 366 && y < 500 && game[2][1] != 0 && game[2][1] != 10) {
                drawNots(400, 433);
                game[2][1] = 0;
                turns++;
            } else if (x > 466 && x < 600 && y > 366 && y < 500 && game[2][2] != 0 && game[2][2] != 10) {
                drawNots(533, 433);
                game[2][2] = 0;
                turns++;
            }
            gameEnds();
        } else if (event.type == SDL_MOUSEBUTTONUP && turns % 2 == 0) {

            if (x > 200 && x < 333 && y > 100 && y < 233 && game[0][0] != 0 && game[0][0] != 10) {
                drawCross(267, 167);
                game[0][0] = 10;                              // 10 for crosses
                turns++;
            } else if (x > 333 && x < 466 && y > 100 && y < 233 && game[0][1] != 0 && game[0][1] != 10) {
                drawCross(400, 167);
                game[0][1] = 10;
                turns++;
            } else if (x > 466 && x < 600 && y > 100 && y < 233 && game[0][2] != 0 && game[0][2] != 10) {
                drawCross(533, 167);
                game[0][2] = 10;
                turns++;
            } else if (x > 200 && x < 333 && y > 233 && y < 366 && game[1][0] != 0 && game[1][0] != 10) {
                drawCross(267, 300);
                game[1][0] = 10;
                turns++;
            } else if (x > 333 && x < 466 && y > 233 && y < 366 && game[1][1] != 0 && game[1][1] != 10) {
                drawCross(400, 300);
                game[1][1] = 10;
                turns++;
            } else if (x > 466 && x < 600 && y > 233 && y < 366 && game[1][2] != 0 && game[1][2] != 10) {
                drawCross(533, 300);
                game[1][2] = 10;
                turns++;
            } else if (x > 200 && x < 333 && y > 366 && y < 500 && game[2][0] != 0 && game[2][0] != 10) {
                drawCross(267, 433);
                game[2][0] = 10;
                turns++;
            } else if (x > 333 && x < 466 && y > 366 && y < 500 && game[2][1] != 0 && game[2][1] != 10) {
                drawCross(400, 433);
                game[2][1] = 10;
                turns++;
            } else if (x > 466 && x < 600 && y > 366 && y < 500 && game[2][2] != 0 && game[2][2] != 10) {
                drawCross(533, 433);
                game[2][2] = 10;
                turns++;
            }
            gameEnds();
        }
    }
    return true;
}

void Screen::drawLines() const {

    for (int i = 101; i < 500; ++i) {
        for (int j = 330; j < 337; ++j) {
            buffer[i * SCREEN_WIDTH + j] = 0x006464FF;
        }
        for (int j = 464; j < 471; ++j) {
            buffer[i * SCREEN_WIDTH + j] = 0x006464FF;
        }
    }
    for (int i = 230; i < 371; ++i) {
        for (int j = 200; j < 600 && (i > 230 && i < 237); ++j) {
            buffer[i * SCREEN_WIDTH + j] = 0x006464FF;
        }

        for (int j = 200; j < 600 && (i > 364 && i < 371); ++j) {
            buffer[i * SCREEN_WIDTH + j] = 0x006464FF;
        }
    }

}

void Screen::drawNots(int x, int y) const {

    float distance;

    for (int i = 0; i < SCREEN_WIDTH; ++i) {
        for (int j = 0; j < SCREEN_HEIGHT; ++j) {
            distance = (float) sqrt(pow((x - j), 2) + pow((y - i), 2));
            if (distance < 47.5 && distance > 40) {
                buffer[i * SCREEN_WIDTH + j] = 0xFFFFFFFF;
            }

        }
    }
}

void Screen::drawCross(int x, int y) const {

    int diff = 93;

    for (int i = 0; i < 93; ++i, diff -= 2) {
        for (int j = 0; j < 93; ++j) {
            if (i == j || (i - 133) == j) {
                for (int k = -3; k < 3; ++k) {
                    buffer[(y - 47 + i + k) * SCREEN_WIDTH + x - 47 + j - k] = 0xFF1064FF;
                    buffer[(y - 47 + i + k) * SCREEN_WIDTH + x - 48 + j - k] = 0xFF1064FF;
                    buffer[(y - 47 + i + k) * SCREEN_WIDTH + x - 47 + diff + j + k] = 0xFF1064FF;
                    buffer[(y - 47 + i + k) * SCREEN_WIDTH + x - 48 + diff + j + k] = 0xFF1064FF;
                }
            }
        }
    }
}

void Screen::gameEnds() {

    int x;
    bool ended = false;

    if (game[0][0] == game[1][1] && game[1][1] == game[2][2]) {
        // draw a line with slope -1 passing throught origin
        for (int i = 200; i < 600; ++i) {
            for (int j = 100; j < 500; ++j) {
                if (i == (j + 100)) {
                    for (int k = -3; k < 3; ++k) {
                        buffer[(j + k) * SCREEN_WIDTH + i - k] = 0xFFFFFFFF;
                        buffer[(j + k) * SCREEN_WIDTH + i - k - 1] = 0xFFFFFFFF;      // to fill the gap between pixels
                    }
                    break;
                }
            }
        }
        x = game[0][0];
        ended = true;
    } else if (game[0][0] == game[0][1] && game[0][1] == game[0][2]) {
        for (int i = 200; i < 600; ++i) {
            for (int k = -3; k < 3; ++k) {
                buffer[(166 - k) * SCREEN_WIDTH + i] = 0xFFFFFFFF;                         // straight line first row
            }
        }
        x = game[0][0];
        ended = true;
    } else if (game[0][1] == game[1][1] && game[1][1] == game[2][1]) {
        for (int i = 100; i < 500; ++i) {
            for (int k = -3; k < 3; ++k) {
                buffer[(i) * SCREEN_WIDTH + 400 -
                       k] = 0xFFFFFFFF;                         // straight line second column
            }
        }
        x = game[0][1];
        ended = true;
    } else if (game[0][0] == game[1][0] && game[1][0] == game[2][0]) {
        for (int i = 100; i < 500; ++i) {
            for (int k = -3; k < 3; ++k) {
                buffer[(i) * SCREEN_WIDTH + 266 -
                       k] = 0xFFFFFFFF;                         // straight line second column
            }
        }
        x = game[0][0];
        ended = true;
    } else if (game[0][2] == game[1][2] && game[1][2] == game[2][2]) {
        for (int i = 100; i < 500; ++i) {
            for (int k = -3; k < 3; ++k) {
                buffer[(i) * SCREEN_WIDTH + 532 -
                       k] = 0xFFFFFFFF;                         // straight line third column
            }
        }
        x = game[0][2];
        ended = true;
    } else if (game[0][2] == game[1][1] && game[1][1] == game[2][0]) {
        for (int i = 600; i > 200; --i) {
            for (int j = 100; j < 500; ++j) {
                if ((i + j) == 700 || (i + j == 699)) {
                    for (int k = -3; k < 3; ++k) {
                        buffer[(j + k) * SCREEN_WIDTH + i + k] = 0xFFFFFFFF;
                        buffer[(j + k) * SCREEN_WIDTH + i + k - 1] = 0xFFFFFFFF;      // to fill the gap between pixels
                    }
                    break;
                }
            }
        }
        x = game[0][2];
        ended = true;
    } else if (game[1][0] == game[1][1] && game[1][1] == game[1][2]) {
        for (int i = 200; i < 600; ++i) {
            for (int k = -3; k < 3; ++k) {
                buffer[(299 - k) * SCREEN_WIDTH + i] = 0xFFFFFFFF;                         // straight line second row
            }
        }
        x = game[1][0];
        ended = true;
    } else if (game[2][0] == game[2][1] && game[2][1] == game[2][2]) {
        for (int i = 200; i < 600; ++i) {
            for (int k = -3; k < 3; ++k) {
                buffer[(432 - k) * SCREEN_WIDTH + i] = 0xFFFFFFFF;                         // straight line third row
            }
        }
        x = game[2][0];
        ended = true;
    }

    if (x == 0 && ended) {
        update();
        SDL_Delay(2000);
        setUp(0, 250, 250);
        drawNots(400, 300);

    } else if (x == 10 && ended) {
        update();
        SDL_Delay(2000);
        setUp(0, 250, 250);
        drawCross(400, 300);

    } else if (turns == 9) {
        update();
        SDL_Delay(2000);
        setUp(0, 250, 250);
        for (int i = 333; i < 466; ++i) {
            for (int j = 296; j < 304; ++j) {
                buffer[SCREEN_WIDTH * j + i] = 0xFFFFFFFF;
            }
        }
    }

}

void Screen::close() {

    //Deallocate all the resources assigned to all the *objects
    delete[] buffer;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
