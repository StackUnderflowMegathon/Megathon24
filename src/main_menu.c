#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "resource_dir.h"

void main_menu(int* current_screen, Texture logo) {

    ClearBackground(BLACK);

    DrawTexture(logo, 500, 100, WHITE);
    // Button Coordinates Definitions
    Rectangle play_button = { 500, 900, 200, 60 };
    Rectangle exit_button = { 1200, 900, 200, 60 };

    DrawRectangleRec(play_button, DARKGRAY);
    DrawRectangleRec(exit_button, DARKGRAY);

    /*
    * DRAWING BUTTONS *
    */

    // Draw Start Game Button
    char* play_text = "Start Game";
    Vector2 play_pos = {
        play_button.x + play_button.width/2 - MeasureText(play_text, 30)/2,
        play_button.y + play_button.height/2 - 15
    };
    DrawText(play_text, play_pos.x, play_pos.y, 30, WHITE);

    // Draw Exit Game Button
    char* exit_text = "Exit Game";
    Vector2 exit_pos = {
        exit_button.x + exit_button.width/2 - MeasureText(exit_text, 30)/2,
        exit_button.y + exit_button.height/2 - 15
    };
    DrawText(exit_text, exit_pos.x, exit_pos.y, 30, WHITE);


    // Handle Start Game Click
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse_pos = GetMousePosition();
        printf("%d %d", mouse_pos.x, mouse_pos.y);
        if (CheckCollisionPointRec(mouse_pos, play_button)) {
            *current_screen = GAME1;
        }
    }

    // Handle Exit Game Click
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse_pos = GetMousePosition();
        if (CheckCollisionPointRec(mouse_pos, exit_button)) {
            *current_screen = EXIT;
        }
    }
        
    // DrawTexture(wabbit, 400, 200, WHITE);
}