#ifndef _BSPLINE_H_
#define _BSPLINE_H_

/*
 * This comes from the matrix form of a B-Spline of degree 3:
 *
 *                          | 1  4  1 0| |S0|
 * P(t) = [1 t t^2 t^3] 1/6 |-3  0  3 0| |S1|
 *                          | 3 -6  3 0| |S2|
 *                          |-1  3 -3 1| |S3|
 *
 * https://observablehq.com/@danburzo/the-matrix-form-of-some-common-cubic-splines
 *
 * t = 0 -> p1
 * t = 1 -> p2
 */
glm::vec3 calculateBSpline(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float t);

#endif /* _BSPLINE_H_ */
