#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
//gcc main.c $(sdl2-config --cflags --libs) -o output
//gcc main.c -o output -lSDL2 -lSDL2_ttf

void SDL_ExitWithError(const char *message);

int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    //Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Inistialisation SDL");

    //Création fenêtre et rendu.
    if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Création fenêtre échoué+rendu");
    
    /*------------------------------------------------------------------------*/
    
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;
 
    image = SDL_LoadBMP("photouno1.bmp");

    if(image == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible de charger l'image");
    }

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if(texture == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible de crée la texture");
    }

    SDL_Rect rectangle;

    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible de charger la texture");
    }

    rectangle.x = (WINDOW_WIDTH - rectangle.w) /2;
    rectangle.y = (WINDOW_HEIGHT - rectangle.h) /2;

    if(SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible d'afficher la texture'");
    }

    SDL_RenderPresent(renderer);

    /////////
    SDL_bool program_launched = SDL_TRUE;

    while(program_launched)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                program_launched = SDL_FALSE;
                break;
            
            default:
                break;
            }
        }
    }   
    /*------------------------------------------------------------------------*/

    //Quitter (pour aucune fuite de mémoir)
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;


}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}




                    