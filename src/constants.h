typedef enum {
    MAIN_MENU,
    GAME1,
    GAME2,
    HOST,
    CONNECT,
    EXIT,
} screens;

struct thread_args{
    int *positions;
    int SocketDescriptor;
    char *state;
};