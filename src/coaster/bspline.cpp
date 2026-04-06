#include "bspline.h"

/*
 * This comes from the matrix form of a B-Spline of degree 3:
 *
 *                          | 1  4  1 0| |S0|
 * P(t) = [1 t t^2 t^3] 1/6 |-3  0  3 0| |S1|
 *                          | 3 -6  3 0| |S2|
 *                          |-1  3 -3 1| |S3|
 *
 * https://observablehq.com/@danburzo/the-matrix-form-of-some-common-cubic-splines
 */
glm::vec3 calculateBSpline(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t) {
    const float t2 = t * t;
    const float t3 = t2 * t;

    /*
    float f1 = ((1.f * 1.f) + (t * -3.f) + (t2 * 3.f)  + (t3 * -1.f)) / 6.f;
    float f2 = ((1.f * 4.f) + (t * 0.f)  + (t2 * -6.f) + (t3 * 3.f))  / 6.f;
    float f3 = ((1.f * 1.f) + (t * 3.f)  + (t2 * 3.f)  + (t3 * -3.f)) / 6.f;
    float f4 = ((1.f * 0.f) + (t * 0.f)  + (t2 * 0.f)  + (t3 * 1.f))  / 6.f;

    Which simplifies to:
    */
    const float f1 = (1.f - 3.f*t + 3.f*t2 - t3) / 6.f;
    const float f2 = (4.f - 6.f*t2 + 3*t3) / 6.f;
    const float f3 = (1.f + 3.f*t + 3*t2 - 3*t3) / 6.f;
    const float f4 = t3 / 6.f;

    return (p0 * f1) + (p1 * f2) + (p2 * f3) + (p3 * f4);
}
