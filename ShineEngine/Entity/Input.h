#pragma once
#include "../stdafx.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

class Input
{
    GLFWwindow* m_window;

    static Input& getInstanceImpl(GLFWwindow** const s = nullptr)
    {
        static Input instance{ s };
        return instance;
    }

    Input(GLFWwindow** const s)
        : m_window{ s ? std::move(*s) : 0 } // employ move ctor
    {
        if (nullptr == s)
            throw std::runtime_error{ "Input not initialized" };
    }

public:
    static Input& getInstance()
    {
        return getInstanceImpl();
    }
    static void init(GLFWwindow* s) // enable moving in
    {
        getInstanceImpl(&s);
    }
    glm::vec2 GetMousePosition() {
        glm::dvec2 mousePos;
        glfwGetCursorPos(m_window, &mousePos.x, &mousePos.y);

        return (glm::vec2)mousePos;
    }

    bool GetMouseButton(int button) {
        return  glfwGetMouseButton(m_window,button);
    }


    Input(Input const&) = delete;
    void operator=(Input const&) = delete;
};