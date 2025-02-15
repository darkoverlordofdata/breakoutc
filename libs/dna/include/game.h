#pragma once
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <corefw.h>
#include <corefw.h>

typedef struct __DNAGame* DNAGameRef;
struct DNAGameVtbl;
extern const CFClassRef DNAGameClass;

extern DNAGameRef DNAGame_instance;

typedef void (*DNAGameProc)(void* self);
struct DNAGameVtbl {
    void (*Initialize)(void* self);
    void (*LoadContent)(void* self);
    void (*Update)(void* self);
    void (*Draw)(void* self);
};

struct __DNAGame {
    struct __CFObject obj;
    void* subclass;
    struct DNAGameVtbl const* override;
    GLFWwindow* window;
    char* title;
    int len;
    bool* keys;
    double delta;
    double factor;
    uint64_t targetElapsedTime;
    uint64_t accumulatedElapsedTime;
    uint64_t maxElapsedTime;
    uint64_t totalGameTime;
    uint64_t elapsedGameTime;
    uint64_t currentTime;
    long previousTicks;
    int x;
    int y;
    int width;
    int height;
    uint32_t flags;
    int mouseX;
    int mouseY;
    bool mouseDown;
    int sdlVersion;
    int frameSkip;
    int gl_major_version;
    int gl_minor_version;
    bool isRunning;
    int ticks;
    int fps;
    bool isFixedTimeStep;
    bool isRunningSlowly;
    int updateFrameLag;
    bool shouldExit;
    bool suppressDraw;
};


extern method void* New(DNAGameRef this, char* cstr, int width, int height, void* subclass, struct DNAGameVtbl* vptr);

extern method void HandleEvents(DNAGameRef const this);
extern method char* ToString(DNAGameRef this);
extern method void Start(DNAGameRef const this);
extern method void Tick(DNAGameRef const this);
extern method void RunLoop(DNAGameRef const this);
extern method void Run(DNAGameRef const this);
extern method void Initialize(DNAGameRef const this);
extern method void LoadContent(DNAGameRef const this);
extern method void Update(DNAGameRef const this);
extern method void Draw(DNAGameRef const this);

static inline DNAGameRef NewDNAGame(char* cstr, int width, int height, void* subclass, struct DNAGameVtbl* vptr)
{
    return New((DNAGameRef)CFCreate(DNAGameClass), cstr, width, height, subclass, vptr);
}
