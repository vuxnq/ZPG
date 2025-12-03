#include "transform/static/TranslateTransform.h"
#include <glm/gtc/matrix_transform.hpp>

TranslateTransform::TranslateTransform(const glm::vec3& offset)
: offset(offset)
{
    SetMatrix(glm::translate(glm::mat4(1.0f), offset));
}
