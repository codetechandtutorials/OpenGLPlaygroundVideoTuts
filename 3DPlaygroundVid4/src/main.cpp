#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "openGLPixelLoader.h"
#include "camera.h"
#include "kbminput.h"
#include <shader.h>

static int gWindowWidth = 640;
static int gWindowHeight = 480;
GLFWwindow* gWindow;
MouseInput* gMouseInput;
KeyboardInput* gKeyboardInput;
Shader* gShader;
Camera* gCamera;

void reshapeWindowHandler(GLFWwindow* window, int width, int height);
void mouseHandler(GLFWwindow* window, float xpos, float ypos);

void mouseMovement(float xpos, float ypos);
void keyPress();

int main()
{

  gCamera = new Camera(glm::vec3(0), 270.f, 0.f, 55.f);
  gMouseInput = new MouseInput();
  gKeyboardInput = new KeyboardInput();

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, "Hello World", NULL, NULL);
  if (!gWindow)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(gWindow);

  // init glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "failed to init GLAD" << std::endl;
    char a;
    std::cin >> a;
    exit(-1);
  }

  gShader = new Shader(
    "../3DPlaygroundVid4/shaders/vertex.glsl",
    "../3DPlaygroundVid4/shaders/frag.glsl"
  );

  loadUpSquare();

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(gWindow))
  {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    render();

    /* Swap front and back buffers */
    glfwSwapBuffers(gWindow);

    /* Poll for and process events */
    glfwPollEvents();
  }

  unloadSquare();

  glfwTerminate();
  
  return 0;

}

void reshapeWindowHandler(GLFWwindow* window, int width, int height)
{
  gWindowWidth = width;
  gWindowHeight = height;
  glViewport(0, 0, gWindowWidth, gWindowHeight);
}

void mouseHandler(GLFWwindow* window, float xpos, float ypos)
{
  mouseMovement(xpos, ypos);
}

void mouseMovement(float xpos, float ypos)
{
  //first person
  static bool firstMouse = true;
  static float lastX(0.f), lastY(0.f), xOffset(0.f), yOffset(0.f);
  if (firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  xOffset = xpos - lastX;
  yOffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  static const float mouseSensitivity = 0.1f;
  xOffset *= mouseSensitivity;
  yOffset *= mouseSensitivity;

  gMouseInput->xOffset = xOffset;
  gMouseInput->yOffset = yOffset;
}

void keyPress()
{
  // esc
  if (glfwGetKey(gWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    gKeyboardInput->esc = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
  {
    gKeyboardInput->esc = false;
  }
  // function keys
  if (glfwGetKey(gWindow, GLFW_KEY_F1) == GLFW_PRESS)
  {
    gKeyboardInput->f1 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F1) == GLFW_RELEASE)
  {
    gKeyboardInput->f1 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F2) == GLFW_PRESS)
  {
    gKeyboardInput->f2 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F2) == GLFW_RELEASE)
  {
    gKeyboardInput->f2 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F3) == GLFW_PRESS)
  {
    gKeyboardInput->f3 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F3) == GLFW_RELEASE)
  {
    gKeyboardInput->f3 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F4) == GLFW_PRESS)
  {
    gKeyboardInput->f4 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F4) == GLFW_RELEASE)
  {
    gKeyboardInput->f4 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F5) == GLFW_PRESS)
  {
    gKeyboardInput->f5 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F5) == GLFW_RELEASE)
  {
    gKeyboardInput->f5 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F6) == GLFW_PRESS)
  {
    gKeyboardInput->f6 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F6) == GLFW_RELEASE)
  {
    gKeyboardInput->f6 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F7) == GLFW_PRESS)
  {
    gKeyboardInput->f7 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F7) == GLFW_RELEASE)
  {
    gKeyboardInput->f7 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F8) == GLFW_PRESS)
  {
    gKeyboardInput->f8 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F8) == GLFW_RELEASE)
  {
    gKeyboardInput->f8 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F9) == GLFW_PRESS)
  {
    gKeyboardInput->f9 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F9) == GLFW_RELEASE)
  {
    gKeyboardInput->f9 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F10) == GLFW_PRESS)
  {
    gKeyboardInput->f10 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F10) == GLFW_RELEASE)
  {
    gKeyboardInput->f10 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F11) == GLFW_PRESS)
  {
    gKeyboardInput->f11 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F11) == GLFW_RELEASE)
  {
    gKeyboardInput->f11 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F12) == GLFW_PRESS)
  {
    gKeyboardInput->f12 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F12) == GLFW_RELEASE)
  {
    gKeyboardInput->f12 = false;
  }
  // number key row
  if (glfwGetKey(gWindow, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
  {
    gKeyboardInput->graveAccent = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE)
  {
    gKeyboardInput->graveAccent = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_1) == GLFW_PRESS)
  {
    gKeyboardInput->n1 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_1) == GLFW_RELEASE)
  {
    gKeyboardInput->n1 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_2) == GLFW_PRESS)
  {
    gKeyboardInput->n2 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_2) == GLFW_RELEASE)
  {
    gKeyboardInput->n2 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_3) == GLFW_PRESS)
  {
    gKeyboardInput->n3 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_3) == GLFW_RELEASE)
  {
    gKeyboardInput->n3 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_4) == GLFW_PRESS)
  {
    gKeyboardInput->n4 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_4) == GLFW_RELEASE)
  {
    gKeyboardInput->n4 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_5) == GLFW_PRESS)
  {
    gKeyboardInput->n5 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_5) == GLFW_RELEASE)
  {
    gKeyboardInput->n5 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_6) == GLFW_PRESS)
  {
    gKeyboardInput->n6 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_6) == GLFW_RELEASE)
  {
    gKeyboardInput->n6 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_7) == GLFW_PRESS)
  {
    gKeyboardInput->n7 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_7) == GLFW_RELEASE)
  {
    gKeyboardInput->n7 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_8) == GLFW_PRESS)
  {
    gKeyboardInput->n8 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_8) == GLFW_RELEASE)
  {
    gKeyboardInput->n8 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_9) == GLFW_PRESS)
  {
    gKeyboardInput->n9 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_9) == GLFW_RELEASE)
  {
    gKeyboardInput->n9 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_0) == GLFW_PRESS)
  {
    gKeyboardInput->n0 = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_0) == GLFW_RELEASE)
  {
    gKeyboardInput->n0 = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_MINUS) == GLFW_PRESS)
  {
    gKeyboardInput->minus = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_MINUS) == GLFW_RELEASE)
  {
    gKeyboardInput->minus = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_EQUAL) == GLFW_PRESS)
  {
    gKeyboardInput->equal = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_EQUAL) == GLFW_RELEASE)
  {
    gKeyboardInput->equal = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
  {
    gKeyboardInput->backspace = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_BACKSPACE) == GLFW_RELEASE)
  {
    gKeyboardInput->backspace = false;
  }
  // alphabet keys
  if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS)
  {
    gKeyboardInput->a = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_RELEASE)
  {
    gKeyboardInput->a = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_B) == GLFW_PRESS)
  {
    gKeyboardInput->b = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_B) == GLFW_RELEASE)
  {
    gKeyboardInput->b = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_C) == GLFW_PRESS)
  {
    gKeyboardInput->c = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_C) == GLFW_RELEASE)
  {
    gKeyboardInput->c = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS)
  {
    gKeyboardInput->d = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_RELEASE)
  {
    gKeyboardInput->d = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_E) == GLFW_PRESS)
  {
    gKeyboardInput->e = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_E) == GLFW_RELEASE)
  {
    gKeyboardInput->e = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_F) == GLFW_PRESS)
  {
    gKeyboardInput->f = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_F) == GLFW_RELEASE)
  {
    gKeyboardInput->f = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_G) == GLFW_PRESS)
  {
    gKeyboardInput->g = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_G) == GLFW_RELEASE)
  {
    gKeyboardInput->g = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_H) == GLFW_PRESS)
  {
    gKeyboardInput->h = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_H) == GLFW_RELEASE)
  {
    gKeyboardInput->h = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_I) == GLFW_PRESS)
  {
    gKeyboardInput->i = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_I) == GLFW_RELEASE)
  {
    gKeyboardInput->i = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_J) == GLFW_PRESS)
  {
    gKeyboardInput->j = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_J) == GLFW_RELEASE)
  {
    gKeyboardInput->j = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_K) == GLFW_PRESS)
  {
    gKeyboardInput->k = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_K) == GLFW_RELEASE)
  {
    gKeyboardInput->k = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_L) == GLFW_PRESS)
  {
    gKeyboardInput->l = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_L) == GLFW_RELEASE)
  {
    gKeyboardInput->l = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_M) == GLFW_PRESS)
  {
    gKeyboardInput->m = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_M) == GLFW_RELEASE)
  {
    gKeyboardInput->m = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_N) == GLFW_PRESS)
  {
    gKeyboardInput->n = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_N) == GLFW_RELEASE)
  {
    gKeyboardInput->n = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_O) == GLFW_PRESS)
  {
    gKeyboardInput->o = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_O) == GLFW_RELEASE)
  {
    gKeyboardInput->o = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_P) == GLFW_PRESS)
  {
    gKeyboardInput->p = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_P) == GLFW_RELEASE)
  {
    gKeyboardInput->p = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_Q) == GLFW_PRESS)
  {
    gKeyboardInput->q = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_Q) == GLFW_RELEASE)
  {
    gKeyboardInput->q = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_R) == GLFW_PRESS)
  {
    gKeyboardInput->r = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_R) == GLFW_RELEASE)
  {
    gKeyboardInput->r = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS)
  {
    gKeyboardInput->s = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_RELEASE)
  {
    gKeyboardInput->s = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_T) == GLFW_PRESS)
  {
    gKeyboardInput->t = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_T) == GLFW_RELEASE)
  {
    gKeyboardInput->t = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_U) == GLFW_PRESS)
  {
    gKeyboardInput->u = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_U) == GLFW_RELEASE)
  {
    gKeyboardInput->u = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_V) == GLFW_PRESS)
  {
    gKeyboardInput->v = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_V) == GLFW_RELEASE)
  {
    gKeyboardInput->v = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS)
  {
    gKeyboardInput->w = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_RELEASE)
  {
    gKeyboardInput->w = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_X) == GLFW_PRESS)
  {
    gKeyboardInput->x = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_X) == GLFW_RELEASE)
  {
    gKeyboardInput->x = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_Y) == GLFW_PRESS)
  {
    gKeyboardInput->y = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_Y) == GLFW_RELEASE)
  {
    gKeyboardInput->y = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_Z) == GLFW_PRESS)
  {
    gKeyboardInput->z = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_Z) == GLFW_RELEASE)
  {
    gKeyboardInput->z = false;
  }
  // tab-shift-control-alt
  if (glfwGetKey(gWindow, GLFW_KEY_TAB) == GLFW_PRESS)
  {
    gKeyboardInput->tab = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_TAB) == GLFW_RELEASE)
  {
    gKeyboardInput->tab = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
  {
    gKeyboardInput->leftShift = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
  {
    gKeyboardInput->leftShift = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
  {
    gKeyboardInput->rightShift = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_RIGHT_SHIFT) == GLFW_RELEASE)
  {
    gKeyboardInput->rightShift = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
  {
    gKeyboardInput->leftControl = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
  {
    gKeyboardInput->leftControl = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
  {
    gKeyboardInput->rightControl = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_RIGHT_CONTROL) == GLFW_RELEASE)
  {
    gKeyboardInput->rightControl = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
  {
    gKeyboardInput->leftAlt = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE)
  {
    gKeyboardInput->leftAlt = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
  {
    gKeyboardInput->rightAlt = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_RIGHT_ALT) == GLFW_RELEASE)
  {
    gKeyboardInput->rightAlt = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    gKeyboardInput->spacebar = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_SPACE) == GLFW_RELEASE)
  {
    gKeyboardInput->spacebar = false;
  }
  // brackets
  if (glfwGetKey(gWindow, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
  {
    gKeyboardInput->leftSquareBracket = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_LEFT_BRACKET) == GLFW_RELEASE)
  {
    gKeyboardInput->leftSquareBracket = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
  {
    gKeyboardInput->rightSquareBracket = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_RIGHT_BRACKET) == GLFW_RELEASE)
  {
    gKeyboardInput->rightSquareBracket = false;
  }
  // slash-quote-semicolon-enter
  if (glfwGetKey(gWindow, GLFW_KEY_BACKSLASH) == GLFW_PRESS)
  {
    gKeyboardInput->backslash = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_BACKSLASH) == GLFW_RELEASE)
  {
    gKeyboardInput->backslash = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_SEMICOLON) == GLFW_PRESS)
  {
    gKeyboardInput->semiColon = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_SEMICOLON) == GLFW_RELEASE)
  {
    gKeyboardInput->semiColon = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_APOSTROPHE) == GLFW_PRESS)
  {
    gKeyboardInput->apostrophe = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_APOSTROPHE) == GLFW_RELEASE)
  {
    gKeyboardInput->apostrophe = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_ENTER) == GLFW_PRESS)
  {
    gKeyboardInput->enter = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_ENTER) == GLFW_RELEASE)
  {
    gKeyboardInput->enter = false;
  }
  // comma-period-forwardslash
  if (glfwGetKey(gWindow, GLFW_KEY_COMMA) == GLFW_PRESS)
  {
    gKeyboardInput->comma = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_COMMA) == GLFW_RELEASE)
  {
    gKeyboardInput->comma = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_PERIOD) == GLFW_PRESS)
  {
    gKeyboardInput->period = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_PERIOD) == GLFW_RELEASE)
  {
    gKeyboardInput->period = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_SLASH) == GLFW_PRESS)
  {
    gKeyboardInput->forwardSlash = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_SLASH) == GLFW_RELEASE)
  {
    gKeyboardInput->forwardSlash = false;
  }
  // printscreen-etc
  if (glfwGetKey(gWindow, GLFW_KEY_PRINT_SCREEN) == GLFW_PRESS)
  {
    gKeyboardInput->printScreen = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_PRINT_SCREEN) == GLFW_RELEASE)
  {
    gKeyboardInput->printScreen = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_SCROLL_LOCK) == GLFW_PRESS)
  {
    gKeyboardInput->scrollLock = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_SCROLL_LOCK) == GLFW_RELEASE)
  {
    gKeyboardInput->scrollLock = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_PAUSE) == GLFW_PRESS)
  {
    gKeyboardInput->pauseBreak = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_PAUSE) == GLFW_RELEASE)
  {
    gKeyboardInput->pauseBreak = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_INSERT) == GLFW_PRESS)
  {
    gKeyboardInput->insert = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_INSERT) == GLFW_RELEASE)
  {
    gKeyboardInput->insert = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_DELETE) == GLFW_PRESS)
  {
    gKeyboardInput->del = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_DELETE) == GLFW_RELEASE)
  {
    gKeyboardInput->del = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_HOME) == GLFW_PRESS)
  {
    gKeyboardInput->home = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_HOME) == GLFW_RELEASE)
  {
    gKeyboardInput->home = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_END) == GLFW_PRESS)
  {
    gKeyboardInput->end = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_END) == GLFW_RELEASE)
  {
    gKeyboardInput->end = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_PAGE_UP) == GLFW_PRESS) {
    gKeyboardInput->pageUp = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_PAGE_UP) == GLFW_RELEASE) {
    gKeyboardInput->pageUp = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) {
    gKeyboardInput->pageDown = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_PAGE_DOWN) == GLFW_RELEASE) {
    gKeyboardInput->pageDown = false;
  }
  // arrows
  if (glfwGetKey(gWindow, GLFW_KEY_UP) == GLFW_PRESS) {
    gKeyboardInput->upArrow = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_UP) == GLFW_RELEASE) {
    gKeyboardInput->upArrow = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
    gKeyboardInput->downArrow = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_DOWN) == GLFW_RELEASE) {
    gKeyboardInput->downArrow = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
    gKeyboardInput->leftArrow = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_LEFT) == GLFW_RELEASE) {
    gKeyboardInput->leftArrow = false;
  }
  if (glfwGetKey(gWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    gKeyboardInput->rightArrow = true;
  }
  else if (glfwGetKey(gWindow, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
    gKeyboardInput->rightArrow = false;
  }

  // mouse clicks
  if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    gKeyboardInput->mouseButton1 = true;
  }
  else if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
    gKeyboardInput->mouseButton1 = false;
  }
  if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
    gKeyboardInput->mouseButton2 = true;
  }
  else if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
    gKeyboardInput->mouseButton2 = false;
  }
  if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
    gKeyboardInput->mouseButton3 = true;
  }
  else if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE) {
    gKeyboardInput->mouseButton3 = false;
  }
  if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_4) == GLFW_PRESS) {
    gKeyboardInput->mouseButton4 = true;
  }
  else if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_4) == GLFW_RELEASE) {
    gKeyboardInput->mouseButton4 = false;
  }
  if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_5) == GLFW_PRESS) {
    gKeyboardInput->mousebutton5 = true;
  }
  else if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_5) == GLFW_RELEASE) {
    gKeyboardInput->mousebutton5 = false;
  }
  if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_6) == GLFW_PRESS) {
    gKeyboardInput->mouseButton6 = true;
  }
  else if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_6) == GLFW_RELEASE) {
    gKeyboardInput->mouseButton6 = false;
  }
  if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_7) == GLFW_PRESS) {
    gKeyboardInput->mousebutton7 = true;
  }
  else if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_7) == GLFW_RELEASE) {
    gKeyboardInput->mousebutton7 = false;
  }
  if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_8) == GLFW_PRESS) {
    gKeyboardInput->mouseButton8 = true;
  }
  else if (glfwGetMouseButton(gWindow, GLFW_MOUSE_BUTTON_8) == GLFW_RELEASE) {
    gKeyboardInput->mouseButton8 = false;
  }
}