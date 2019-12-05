#pragma once
#include <shader.h>
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\gtx\transform.hpp>

extern int gWindowWidth;
extern int gWindowHeight;

class Camera
{
private:
  glm::vec3 mPos;
  glm::vec3 mFront, mUp, mRight;
  float mYaw;
  float mPitch;
  float mFov;
  float mNearRenderDistance = .01f;
  float mFarRenderDistance = 2000.f;
public:
  const glm::vec3 WORLD_UP = glm::vec3(0, 1, 0);

  Camera(const glm::vec3 startingPos, const float lookDir, const float pitch, const float fov)
  {
    mPos = startingPos;
    mYaw = lookDir;
    mPitch = pitch;

    _updateCameraVectors();  // set Front, Up, & Right

    mFov = fov;

  }

  void updateViewMatrix(Shader* shader)
  {
    shader->use();
    shader->setMat4("view", getViewMatrix());
  }

  // needs called to update the FoV and/or window_width window_height, and draw distances
  void updateProjectionMatrix(Shader* shader)
  {
    glm::mat4 projection = glm::perspective(glm::radians(mFov), (float)gWindowWidth / (float)gWindowHeight, mNearRenderDistance, mFarRenderDistance);
    shader->use();
    shader->setMat4("projection", projection);
  }

  glm::mat4 getProjectionMatrix()
  {
    glm::mat4 projection = glm::perspective(glm::radians(mFov), (float)gWindowWidth / (float)gWindowHeight, mNearRenderDistance, mFarRenderDistance);

    return projection;
  }

  void setPosition(glm::vec3 pos)
  {
    mPos = pos;
    _updateCameraVectors();  //update front, up, right   --- todo: should we do this here?
  }

  void increaseYawAndPitch(float yawOff, float pitchOff)
  {
    _increaseYaw(yawOff);
    _increasePitch(pitchOff);
    _updateCameraVectors();
  }

  void increasePosition(glm::vec3 amount)
  {
    mPos += amount;
    _updateCameraVectors();  //update front, up, right   --- todo: should we do this here?
  }

  void _increaseYaw(float offset)
  {
    mYaw += offset;
  }

  void _increasePitch(float offset)
  {
    mPitch += offset;

    if (this->mPitch > 89.0f)
    {
      this->mPitch = 89.0f;
    }
    else if (this->mPitch < -89.0f)
    {
      this->mPitch = -89.0f;
    }
  }

  void setToOrtho(Shader* shader)
  {
    //ortho(T const& left, T const& right, T const& bottom, T const& top, T const& zNear, T const& zFar)

    glm::mat4 projection = glm::ortho(-gWindowWidth / 2.f, gWindowWidth / 2.f, -gWindowHeight / 2.f, gWindowHeight / 2.f, -1.f, 1.f);
    shader->use();
    shader->setMat4("projection", projection);
  }

  void setToPerspective(Shader* shader, float fov)
  {
    glm::mat4 projection = glm::perspective(glm::radians(mFov), (float)gWindowWidth / (float)gWindowHeight, mNearRenderDistance, mFarRenderDistance);
    shader->use();
    shader->setMat4("projection", projection);
  }

  glm::mat4 getViewMatrix()
  {
    return glm::lookAt(mPos, mPos + mFront, mUp);
  }

  glm::vec3* getPosition()
  {
    return &mPos;
  }

  glm::vec3* getFront()
  {
    return &mFront;
  }

  glm::vec3* getRight()
  {
    return &mRight;
  }

  float getYaw()
  {
    return mYaw;
  }

  float getPitch()
  {
    return mPitch;
  }

  void _updateCameraVectors()
  {
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

    mFront = glm::normalize(front);
    mRight = glm::normalize(glm::cross(mFront, WORLD_UP));
    mUp = glm::normalize(glm::cross(mRight, mFront));
  }
};
