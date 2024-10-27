#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "resource_dir.h"

void end_menu(int* current_screen, volatile int* positions){
    int maxind = 0;
    for (int i = 0; i < 4; i++) {
        if (positions[i] > positions[maxind]) maxind = i;
    }
    
    ClearBackground(BLACK);
    DrawText("GAME OVER", 1920/2 - 325, 1080/2-150, 100, WHITE);
    char text[20];
    sprintf(text, "Player %d WON!", maxind + 1);
    DrawText(text, 1920/2 - 350, 1080/2 - 50, 100, WHITE);

    // Rectangle main_menu_button = { 1920/2 - 100, 1080/2 - 100, 200, 60 };
    Rectangle exit_button = { 1920/2 - 100, 1080/2 + 100, 200, 60 };

    // DrawRectangleRec(main_menu_button, DARKGRAY);
    DrawRectangleRec(exit_button, DARKGRAY);

    /*
    * DRAWING BUTTONS *
    */

    // Draw Start Game Button
    // char* play_text = "Main Menu";
    // Vector2 play_pos = {
    //     main_menu_button.x + main_menu_button.width/2 - MeasureText(play_text, 30)/2,
    //     main_menu_button.y + main_menu_button.height/2 - 15
    // };
    // DrawText(play_text, play_pos.x, play_pos.y, 30, WHITE);

    // Draw Exit Game Button
    char* exit_text = "Exit Game";
    Vector2 exit_pos = {
        exit_button.x + exit_button.width/2 - MeasureText(exit_text, 30)/2,
        exit_button.y + exit_button.height/2 - 15
    };
    DrawText(exit_text, exit_pos.x, exit_pos.y, 30, WHITE);


    // Handle Start Game Click
    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    //     Vector2 mouse_pos = GetMousePosition();
    //     printf("%d %d", mouse_pos.x, mouse_pos.y);
    //     if (CheckCollisionPointRec(mouse_pos, main_menu_button)) {
    //         *current_screen = MAIN_MENU;
    //     }
    // }

    // Handle Exit Game Click
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse_pos = GetMousePosition();
        if (CheckCollisionPointRec(mouse_pos, exit_button)) {
            *current_screen = EXIT;
        }
    }
}