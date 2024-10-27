typedef enum {
    MAIN_MENU,
    GAME1,
    GAME2,
    HOST,
    CONNECT,
    EXIT,
    END_MENU,
} screens;

struct thread_args{
    volatile int *positions;
    int SocketDescriptor;
    volatile char *state;
    int PlayerId;
    int* Flipped;
};