#include "./main_menu.c"
#include "./trick_or_treat.c"
#include "constants.h"
#include "networking/client.c"

Music startMenuMusic = LoadMusicStream("../resources/audio/start_menu.wav");
Music greenLightMusic = LoadMusicStream("../resources/audio/green_light.wav");
Music redLightMusic = LoadMusicStream("../resources/audio/red_light.wav");

int main() {

  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Initialize Window
  InitWindow(1920, 1080, "Overtale");
  SearchAndSetResourceDir("resources");
  Texture wabbit = LoadTexture("wabbit_alpha.png");
  Texture textures[6] = {
      LoadTexture("background.png"), LoadTexture("Green.PNG"),
      LoadTexture("Blue.PNG"),       LoadTexture("Yellow.PNG"),
      LoadTexture("Red.PNG"),        LoadTexture("Reaper.png")};
  if (IsWindowReady()) {
    StopMusicStream(greenLightMusic);
    StopMusicStream(redLightMusic);
    PlayMusicStream(startMenuMusic);
  }
  int SocketDescriptor = connect_to_server("10.2.132.132");
  char buffer[1024];
  read(SocketDescriptor, buffer, sizeof(buffer));
  int PlayerId = buffer[0] - '0';

  int current_screen = MAIN_MENU;
  volatile int positions[4] = {-1, -1, -1, -1};
  volatile char state[4] = {'\0', '\0', '\0', '\0'};
  positions[PlayerId] = 5;
  pthread_t tid;
  pthread_t tid2;

  struct thread_args args = {positions, SocketDescriptor, state, PlayerId};

  pthread_create(&tid, NULL, receive_packets, (void *)&args);
  pthread_create(&tid2, NULL, send_packet, (void *)&args);
  int flag = 1;

  while (!WindowShouldClose() && flag) {
    BeginDrawing();

    switch (current_screen) {

    case MAIN_MENU:
      main_menu(&current_screen);
      break;

    case HOST:
      // TODO
      break;

    case CONNECT:
      // TODO
      break;

    case GAME1:
      trick_or_treat(PlayerId, &current_screen, textures, positions, state,
                     SocketDescriptor);
      break;

    case EXIT:
      flag = 0;
      break;
    }
    EndDrawing();
  }

  UnloadTexture(wabbit);
  CloseWindow();
  return 0;
}