#include "constants.h"
#include "networking/client.c"
#include "./main_menu.c"
#include "./trick_or_treat.c"
#include "end_menu.c"


int main()
{

    char ip_address[30];
    printf("Set host IP address: ");
    scanf("%s", ip_address);

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    // Initialize Window
    InitWindow(1920, 1080, "Overtale"); 
    SearchAndSetResourceDir("resources");
    Texture textures[8] = {LoadTexture("background.png"), LoadTexture("Green.PNG"), LoadTexture("Blue.PNG"), LoadTexture("Yellow.PNG"), LoadTexture("Red.PNG"), LoadTexture("Reaper1.png"), LoadTexture("Reaper2.png"), LoadTexture("Dead.png")};
    Texture logo = LoadTexture("Overtale.png");

    int SocketDescriptor = connect_to_server(ip_address);
    char buffer[1024];
    read(SocketDescriptor, buffer, sizeof(buffer));
    int PlayerId = buffer[0]-'0';
    
    int current_screen = MAIN_MENU;
    volatile int positions[4] = {-1,-1,-1,-1};
    volatile char state[4] = {'\0', '\0','\0','\0'};
    positions[PlayerId] = 5;
    int flipped = 0;
    pthread_t tid;
    pthread_t tid2;

    struct thread_args args = {positions, SocketDescriptor, state, PlayerId, &flipped};


    pthread_create(&tid, NULL, receive_packets, (void*) &args);
    pthread_create(&tid2, NULL, send_packet, (void*) &args);
    int flag = 1;



    while (!WindowShouldClose() && flag)
    {
        BeginDrawing();

        switch(current_screen){

            case MAIN_MENU:
                main_menu(&current_screen, logo);
                break;
            
            case HOST:
                //TODO
                break;

            case CONNECT:
                //TODO
                break;

            case GAME1:
                trick_or_treat(PlayerId, &current_screen, textures, positions, state, flipped);
                break;
                
            case EXIT:
                flag = 0;
                break;

            case END_MENU:
                end_menu(&current_screen, positions);
                break;
        }
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}