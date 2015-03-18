#pragma once

#include "core.h"
#include "Broadcast.h"

#include <functional>
#include <map>

#include <GLFW/glfw3.h>

namespace Core
{
    template<typename T>
    class Scheduler;
}

using Scheduler = Core::Scheduler<time_base>;

enum Mouse
{
    LeftButton  = 1,
    RightButton = 2
};

class Window
{
    template<typename ... T>
    friend class Broadcast;

public:
    Window(uint32_t width, uint32_t height, const char* title);

    void mainloop(Scheduler* scheduler);

    inline void update()
    {
        _update = true;
    }

signals:
    signal(initializeGL);
    signal(draw);
    signal(resize, int, int);
    signal(mousemove, double, double, uint8_t);

private:
    static void _resizeHandler(GLFWwindow* w, int width, int height);
    static void _refreshHandler(GLFWwindow* w);
    static void _cursorPosHandler(GLFWwindow* w, double x, double y);

private:
    GLFWwindow* _window;
    Scheduler* _scheduler;
    std::atomic<bool> _update;

    static std::map<uintptr_t, Window*> _windowToThis;
};