#include "Camera.h"

Camera* CameraConstructor(float width, float height, vec2 position)
{
	Camera* this = (Camera*)malloc(sizeof(Camera));
    if (!this) {
        //free(this); if this == NULL you got free(NULL), you can do it, but it's useless;
        DEBUG_LOG("malloc failed in CameraConstructor");
        return NULL;
    }

    this->ViewportHeight = height;
    this->ViewportWidth = width;
    glm_vec2_copy(position, this->Position);

    return this;
}

void CameraMatrix(Camera* this, Shader* shader)
{
    //Set up projection;
    glm_ortho(0.0f, this->ViewportWidth, this->ViewportHeight, 0.0f, -1.0f, 1.0f, this->Projection);

    //Set up view;
    glm_mat4_identity(this->View);
    glm_translate(this->View, (vec3) { this->Position[0], this->Position[1], 0.0f });

    //Send to the shader;
    int viewLocation = glGetUniformLocation(shader->ID, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, this->View);

    int projectionLocation = glGetUniformLocation(shader->ID, "projection");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, this->Projection);
}

void SetLock(bool lockHorizontal, bool lockVertical)
{
    // TODO: implement lock logic
}

CallbackParameter CameraUp(Camera* this)
{
    glm_vec2_copy((vec2) { this->Position[0], this->Position[1] + 1.0f }, this->Position);
}

CallbackParameter CameraDown(Camera* this)
{
    glm_vec2_copy((vec2) { this->Position[0], this->Position[1] - 1.0f }, this->Position);
}

CallbackParameter CameraLeft(Camera* this)
{
    glm_vec2_copy((vec2) { this->Position[0] + 1.0f, this->Position[1] }, this->Position);
}

CallbackParameter CameraRight(Camera* this)
{
    glm_vec2_copy((vec2) { this->Position[0] - 1.0f, this->Position[1] }, this->Position);
}