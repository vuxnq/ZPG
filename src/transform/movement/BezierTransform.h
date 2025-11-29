#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <vector>
#include "transform/movement/MovementTransformComponent.h"

// TODO: remove
#include "iostream"
#include <glm/gtc/matrix_transform.hpp>


struct CubicCurve {
    glm::vec3 pointStart;
    glm::vec3 adjustPointStart;
    glm::vec3 adjustPointEnd;
    glm::vec3 pointEnd;
};

class BezierTransform : public MovementTransformComponent {
public:
    BezierTransform(const std::vector<CubicCurve>& curves, const float duration) : MovementTransformComponent(duration), spline(curves) {}
    ~BezierTransform() {}

    void Update(const float delta) override {
        elapsed = std::min(elapsed + delta, duration); // TODO: maybe this can be moved to MovementTransformComponent
    }
    glm::mat4 GetMatrix() override {
        // TODO:
        if (spline.empty()) return glm::mat4(1.0f);

        float time = elapsed / duration;

        int curvesCount = spline.size();
        float scaled = time * curvesCount;

        float index = std::floor(scaled);
        if (index >= curvesCount) index = curvesCount - 1;

        float localTime = scaled - index;

        glm::vec4 parameters = glm::vec4(localTime * localTime * localTime, localTime * localTime, localTime, 1.0f);

        auto B = glm::mat4x3(
            spline[index].pointStart,
            spline[index].adjustPointStart,
            spline[index].adjustPointEnd,
            spline[index].pointEnd
        );

        glm::vec3 pos = parameters * A * glm::transpose(B);

        std::cout << "t = " << time << " P=[ " << pos[0] << ", " << pos[1] << ", " << pos[2] << "]" << std::endl;
        return glm::translate(glm::mat4(1.f), pos);
    }

private:
    std::vector<CubicCurve> spline;

    glm::mat4 A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
    glm::vec4(3.0, -6.0, 3.0, 0),
    glm::vec4(-3.0, 3.0, 0, 0),
    glm::vec4(1, 0, 0, 0));
};
