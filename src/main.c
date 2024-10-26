#include "raylib.h"
#include <stdio.h>
#include "resource_dir.h"

int main()
{
    // Button Coordinates Definitions
    Rectangle play_button = {
        612,
        354,
        200,
        60
    };
    Rectangle exit_button = {
        612,
        424,
        200,
        60
    };
    
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);


    // Initialize Window
    InitWindow(1920, 1080, "Overtale"); 
    SearchAndSetResourceDir("resources");
    Texture wabbit = LoadTexture("wabbit_alpha.png");
    while (!WindowShouldClose())
    {
        // Draw Buttons
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRec(play_button, DARKGRAY);
        DrawRectangleRec(exit_button, DARKGRAY);

        // Draw Start Game Button
        char* play_text = "Start Game";
        Vector2 play_pos = {
            play_button.x + play_button.width/2 - MeasureText(play_text, 30)/2,
            play_button.y + play_button.height/2 - 15
        };
        DrawText(play_text, play_pos.x, play_pos.y, 30, WHITE);

        // Handle Start Game Click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, play_button)) {
                printf("");
            }
        }

        // Draw Exit Game Button
        char* exit_text = "Exit Game";
        Vector2 exit_pos = {
            exit_button.x + exit_button.width/2 - MeasureText(exit_text, 30)/2,
            exit_button.y + exit_button.height/2 - 15
        };
        DrawText(exit_text, exit_pos.x, exit_pos.y, 30, WHITE);
        
        // Handle Exit Game Click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse_pos = GetMousePosition();
            if (CheckCollisionPointRec(mouse_pos, exit_button)) {
                printf("");
            }
        }
        DrawTexture(wabbit, 400, 200, WHITE);
        EndDrawing();
    }
    
    UnloadTexture(wabbit);
    CloseWindow();
    return 0;
}