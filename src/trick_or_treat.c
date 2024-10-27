    #include "raylib.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include "resource_dir.h"
    #include <pthread.h>

    // #include "./networking/client.c", LoadTexture("Reaper2.png")

    void trick_or_treat(int pid, int* current_screen, Texture textures[8], volatile int positions[4], volatile char states[4], int treat) {
        ClearBackground(BLACK);
        pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
        DrawTexture(textures[0], 0, 0, WHITE);

        Rectangle EndLine = {GetScreenWidth()*0.8, 0, 1, GetScreenHeight()};
        DrawRectangleRec(EndLine, WHITE);
        
        Rectangle Player = {positions[pid], 100, 80, 140};
        float scale = 0.08f;

        int total = 0;
        int dead = 0;
        // printf("positions array for pid %d is: ", pid);
        for (int i = 0; i < 4; i++) {
            if (positions[i] > 0) {
                total++;
                if (states[i] != 'D')
                    DrawTextureEx(textures[i+1], (Vector2){positions[i], 80+240*i}, 0.0f, scale, WHITE);
                else if(states[i] == 'D') {
                    DrawTextureEx(textures[7], (Vector2){positions[i], 80+240*i}, 0.0f, scale, WHITE);
                    dead++;
                }
            }
        }
        if (total == dead) {
            *current_screen = END_MENU;
            // printf("total = dead\n");
            return;
        }

        if (treat == 1) {
            scale = 8.00f;
            DrawTextureEx(textures[5], (Vector2){GetScreenWidth()*0.7, 80+240*0.5}, 0.0f, scale, WHITE);
        }
        else {
            scale = 8.00f;
            DrawTextureEx(textures[6], (Vector2){GetScreenWidth()*0.7, 80+240*0.5}, 0.0f, scale, WHITE);
        }

        // printf("\n");

        // drawstuff(2, *x, 100, 80, 140, textures);
        if(positions[pid] >= 0.8*GetScreenWidth()){
            *current_screen = END_MENU; // maybe change
            // printf("collided bro\n");
            return;
        }
        if (states[pid] == 'D') return;
        if(IsKeyDown(KEY_RIGHT)){
            if (treat == 0) {
                states[pid] = 'D';
                return;
            }
            
            pthread_mutex_lock(&mtx);
            positions[pid] += 2;
            pthread_mutex_unlock(&mtx);
        }

    }