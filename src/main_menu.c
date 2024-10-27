#include "raylib.h"
#include "resource_dir.h"
#include <stdio.h>
#include <stdlib.h>

Music startMenuMusic = LoadMusicStream("../resources/audio/start_menu.wav");
Music greenLightMusic = LoadMusicStream("../resources/audio/start_menu.wav");
Music redLightMusic = LoadMusicStream("../resources/audio/start_menu.wav");

void main_menu(int *current_screen) {

  ClearBackground(BLACK);
  // Button Coordinates Definitions
  Rectangle play_button = {GetScreenWidth() / 2 - 100,
                           GetScreenHeight() / 2 - 100, 200, 60};
  Rectangle exit_button = {GetScreenWidth() / 2 - 100,
                           GetScreenHeight() / 2 + 100, 200, 60};

  DrawRectangleRec(play_button, DARKGRAY);
  DrawRectangleRec(exit_button, DARKGRAY);

  /*
   * DRAWING BUTTONS *
   */
  //   if (IsWindowReady()) {
  //     StopMusicStream(redLightMusic);
  //     StopMusicStream(startMenuMusic);
  //     PlayMusicStream(greenLightMusic);
  //   }

  // Draw Start Game Button
  char *play_text = "Start Game";
  Vector2 play_pos = {play_button.x + play_button.width / 2 -
                          MeasureText(play_text, 30) / 2,
                      play_button.y + play_button.height / 2 - 15};
  DrawText(play_text, play_pos.x, play_pos.y, 30, WHITE);

  // Draw Exit Game Button
  char *exit_text = "Exit Game";
  Vector2 exit_pos = {exit_button.x + exit_button.width / 2 -
                          MeasureText(exit_text, 30) / 2,
                      exit_button.y + exit_button.height / 2 - 15};
  DrawText(exit_text, exit_pos.x, exit_pos.y, 30, WHITE);

  // Handle Start Game Click
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 mouse_pos = GetMousePosition();
    printf("%d %d", mouse_pos.x, mouse_pos.y);
    if (CheckCollisionPointRec(mouse_pos, play_button)) {
      StopMusicStream(redLightMusic);
      StopMusicStream(startMenuMusic);
      PlayMusicStream(greenLightMusic);
      *current_screen = GAME1;
    }
  }

  // Handle Exit Game Click
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 mouse_pos = GetMousePosition();
    if (CheckCollisionPointRec(mouse_pos, exit_button)) {
      StopMusicStream(redLightMusic);
      StopMusicStream(startMenuMusic);
      StopMusicStream(greenLightMusic);
      *current_screen = EXIT;
    }
  }

  // DrawTexture(wabbit, 400, 200, WHITE);
}