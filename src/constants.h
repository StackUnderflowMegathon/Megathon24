typedef enum {
    MAIN_MENU,
    GAME1,
    GAME2,
    HOST,
    CONNECT,
    EXIT,
} screens;

struct thread_args{
    volatile int *positions;
    int SocketDescriptor;
    volatile char *state;
    int PlayerId;
};