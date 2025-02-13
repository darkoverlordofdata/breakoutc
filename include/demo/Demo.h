#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <corefw/corefw.h>
#include <dna.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

typedef struct Demo Demo;
extern const CFClass *DemoClass;
struct DemoVtbl;
typedef enum {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
} GameState;


struct Demo {
    CFObject obj;
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

    GameState State;
    CFArray* Levels;
    GLuint Level;
};


extern DNAResourceManager* ResourceManager;


extern void* New(Demo* this, char* title, int width, int height);
extern method void Initialize(Demo* this);
extern method void LoadContent(Demo* this);
extern method void Update(Demo* this);
extern method void Draw(Demo* this);
extern method void Run(Demo* this);
extern method void SetKey(Demo* this, int key, bool value);
extern method void SetState(Demo* this, GameState state);
extern method void Start(Demo* this);
extern method void ResetLevel(Demo* this);
extern method void ResetPlayer(Demo* this);
extern method void Dispose(Demo* this);
extern method void DoCollisions(Demo* this);

static inline Demo* NewDemo(char* title, int width, int height)
{
    return New((Demo*)cfw_create(DemoClass), title, width, height);
}

