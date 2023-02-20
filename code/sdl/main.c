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
    SDL_Window *window2 = NULL;
    SDL_Renderer *renderer2 = NULL;

    //Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Inistialisation SDL");

    //Création fenêtre et rendu.
    if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Création fenêtre échoué+rendu");
    
    /*------------------------------------------------------------------------*/

    //Charger l'image pour le FondMenu
    SDL_Surface *imageFondMenu = NULL;
    imageFondMenu = SDL_LoadBMP("photouno1.bmp");
    if(imageFondMenu == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible de charger l'image du menu");
    }

    //Créer la texture pour le FondMenu
    SDL_Texture *textureFondMenu = NULL;
    textureFondMenu = SDL_CreateTextureFromSurface(renderer, imageFondMenu);
    SDL_FreeSurface(imageFondMenu);
    if(textureFondMenu == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible de crée la texture du menu");
    }

    // Positionner le rectangle pour le FondMenu
    SDL_Rect rectangle;

    // Afficher le FondMenu
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

    //Charger l'image pour le bouton PlayMenu
    SDL_Surface *buttonPlayMenu = NULL;
    buttonPlayMenu = SDL_LoadBMP("buttonPlayMenu.bmp");
    if(buttonPlayMenu == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);   
        SDL_ExitWithError("Impossible de charger l'image du bouton");
    }


    // Créer la texture pour le bouton PlayMenu
    SDL_Texture *buttonTexture = NULL;
    buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonPlayMenu);
    SDL_FreeSurface(buttonPlayMenu);
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
                    printf("Le bouton a été cliqué sur Play !\n");

                    if(SDL_CreateWindowAndRenderer2(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window2, &renderer2) != 0)
                    SDL_ExitWithError("Création fenêtre échoué+rendu");

                    SDL_Window *newWindow = SDL_CreateWindow("Nouvelle fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240, SDL_WINDOW_SHOWN);
                    if (newWindow == NULL) {
                    SDL_Log("Erreur de création de la nouvelle fenêtre : %s", SDL_GetError());
                    return 1;
                    }

                    // Créer un rendu pour la nouvelle fenêtre
                    SDL_Renderer *newRenderer = SDL_CreateRenderer(newWindow, -1, 0);
                    if (newRenderer == NULL) {
                        SDL_Log("Erreur de création du rendu pour la nouvelle fenêtre : %s", SDL_GetError());
                        return 1;
                    }
                        
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




                    