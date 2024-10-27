    #include "raylib.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include "resource_dir.h"
    #include <pthread.h>

    // #include "./networking/client.c"

    void trick_or_treat(int pid, int* current_screen, Texture textures[6], volatile int positions[4], volatile char states[4], int socketid) {

        SearchAndSetResourceDir("resources");
        ClearBackground(BLACK);

        DrawTexture(textures[0], 0, 0, WHITE);
        Rectangle EndLine = {GetScreenWidth()*0.8, 0, 1, GetScreenHeight()};
        DrawRectangleRec(EndLine, WHITE);
        
        Rectangle Player = {positions[pid], 100, 80, 140};
        float scale = 0.08f;
        // printf("positions array for pid %d is: ", pid);
        for (int i = 0; i < 4; i++) {
            // printf("%d ", positions[i]);
            if (positions[i] > 0) {
                DrawTextureEx(textures[i+1], (Vector2){positions[i], 80+240*i}, 0.0f, scale, WHITE);
            }
        }
        // printf("\n");

        // drawstuff(2, *x, 100, 80, 140, textures);
        if(CheckCollisionRecs(Player, EndLine)){
            *current_screen = MAIN_MENU;
        }

        if(IsKeyDown(KEY_RIGHT)){
            pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
            pthread_mutex_lock(&mtx);
            positions[pid] += 2;
            pthread_mutex_unlock(&mtx);
            // char buffer[8];
            // sprintf(buffer, "%d%c%d", pid, 'M', positions[pid]);
            
            // send_packet(buffer, socketid);
        }

    }