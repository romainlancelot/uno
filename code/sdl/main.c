#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define BUTTON_WIDTH 256
#define BUTTON_HEIGHT 100
//gcc main.c $(sdl2-config --cflags --libs) -o output


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
    
    SDL_Surface *imageFondMenu = NULL;
    SDL_Texture *textureFondMenu = NULL;
    SDL_Surface *buttonImage = NULL;
    SDL_Surface *buttonTextue = NULL;

    buttonImage = SDL_LoadBMP("button.bmp");
    imageFondMenu = SDL_LoadBMP("photouno1.bmp");

    //Charger l'image pour le bouton
    if(buttonImage == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible de charger l'image du bouton");
    }

    //Charger l'image pour le FondMenu
    if(imageFondMenu == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible de charger l'image du menu");
    }

    //Créer la texture pour le FondMenu
    textureFondMenu = SDL_CreateTextureFromSurface(renderer, imageFondMenu);
    SDL_FreeSurface(imageFondMenu);

    if(textureFondMenu == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible de crée la texture du menu");
    }

    SDL_Rect rectangle;

    if(SDL_QueryTexture(textureFondMenu, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible de charger la texture du menu");
    }

    rectangle.x = (WINDOW_WIDTH - rectangle.w) /2;
    rectangle.y = (WINDOW_HEIGHT - rectangle.h) /2;

    if(SDL_RenderCopy(renderer, textureFondMenu, NULL, &rectangle) != 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible d'afficher la texture du menu'");
    }

        ///

    // Créer la texture pour le bouton
    SDL_Texture *buttonTexture = NULL;
    buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonImage);
    SDL_FreeSurface(buttonImage);
    if(buttonTexture == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible de crée la texture du bouton");
    }

    // Positionner le rectangle pour le bouton
    SDL_Rect buttonRect;
    buttonRect.w = BUTTON_WIDTH;
    buttonRect.h = BUTTON_HEIGHT;
    buttonRect.x = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
    buttonRect.y = (WINDOW_HEIGHT - BUTTON_HEIGHT) / 2;

    // Afficher le bouton
    if(SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect) != 0)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible d'afficher le bouton");
    }

    ///

    //Afficher le rendu
    SDL_RenderPresent(renderer);

    /////////Boucle de lancement 
    SDL_bool program_launched = SDL_TRUE;

    while(program_launched)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT && 
                    event.button.x >= buttonRect.x && event.button.x < buttonRect.x + buttonRect.w && 
                    event.button.y >= buttonRect.y && event.button.y < buttonRect.y + buttonRect.h)
                {
                    printf("Le bouton a été cliqué !\n");
                }
                break;

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




                    