R""(#version 460 core

// This shader is hugely taken from https://www.shadertoy.com/view/slSXRW
// Which itself uses Sebastien Hillaire's code:
// https://github.com/sebh/UnrealEngineSkyAtmosphere

in vec2 outUVCoords;
out vec4 FragColor;

layout(binding = 0) uniform sampler2D u_TransmittanceLUT;
layout(binding = 1) uniform sampler2D u_SkyViewLUT;

uniform mat4 u_InvViewProj;
uniform float u_ViewHeight;
uniform vec3 u_SunDir;

const float PI = 3.14159265358;

// Units are in megameters.
const float groundRadius = 6.360;
const float atmosphereRadius = 6.460;

// Utils
float safeacos(const float x)
{
    return acos(clamp(x, -1.0, 1.0));
}

// From https://gamedev.stackexchange.com/questions/96459/fast-ray-sphere-collision-code.
float rayIntersectSphere(vec3 ro, vec3 rd, float rad)
{
    float b = dot(ro, rd);
    float c = dot(ro, ro) - rad*rad;
    if (c > 0.0f && b > 0.0)
    {
        return -1.0;
    }
    float discr = b*b - c;
    if (discr < 0.0)
    {
        return -1.0;
    }
    // Special case: inside sphere, use far discriminant
    if (discr > b*b)
    {
        return (-b + sqrt(discr));
    }
    return -b - sqrt(discr);
}

vec3 getValFromTLUT(vec3 pos, vec3 sunDir)
{
    vec3 up = pos / u_ViewHeight;
    float sunCosZenithAngle = dot(sunDir, up);
    vec2 uv = vec2(clamp(0.5 + 0.5*sunCosZenithAngle, 0.0, 1.0),
                   max(0.0, min(1.0, (u_ViewHeight - groundRadius)/(atmosphereRadius - groundRadius))));
    return texture(u_TransmittanceLUT, uv).rgb;
}

vec3 getValFromSkyLUT(vec3 rayDir, vec3 sunDir) {
    vec3 up = vec3(0.0, 1.0, 0.0);

    float horizonAngle = safeacos(sqrt(u_ViewHeight * u_ViewHeight - groundRadius * groundRadius) / u_ViewHeight);
    float altitudeAngle = horizonAngle - acos(dot(rayDir, up)); // Between -PI/2 and PI/2
    float azimuthAngle; // Between 0 and 2*PI
    if (abs(altitudeAngle) > (0.5*PI - .0001))
    {
        // Looking nearly straight up or down.
        azimuthAngle = 0.0;
    }
    else
    {
        vec3 right = cross(sunDir, up);
        vec3 forward = cross(up, right);

        vec3 projectedDir = normalize(rayDir - up*(dot(rayDir, up)));
        float sinTheta = dot(projectedDir, right);
        float cosTheta = dot(projectedDir, forward);
        azimuthAngle = atan(sinTheta, cosTheta) + PI;
    }

    // Non-linear mapping of altitude angle. See Section 5.3 of the paper.
    float v = 0.5 + 0.5*sign(altitudeAngle)*sqrt(abs(altitudeAngle)*2.0/PI);
    vec2 uv = vec2(azimuthAngle / (2.0 * PI), v);

    return texture(u_SkyViewLUT, uv).rgb;
}

vec3 jodieReinhardTonemap(vec3 c)
{
    // From: https://www.shadertoy.com/view/tdSXzD
    float l = dot(c, vec3(0.2126, 0.7152, 0.0722));
    vec3 tc = c / (c + 1.0);
    return mix(c / (l + 1.0), tc, tc);
}

vec3 sunWithBloom(vec3 rayDir, vec3 sunDir)
{
    const float sunSolidAngle = 2.53*PI/180.0;
    const float minSunCosTheta = cos(sunSolidAngle);

    float cosTheta = dot(rayDir, sunDir);
    if (cosTheta >= minSunCosTheta) return vec3(1.0);

    float offset = minSunCosTheta - cosTheta;
    float gaussianBloom = exp(-offset*50000.0)*0.5;
    float invBloom = 1.0/(0.02 + offset*300.0)*0.01;
    return vec3(gaussianBloom+invBloom);
}

void main()
{
    vec4 clipPos = vec4(outUVCoords * 2.0 - 1.0, 1.0, 1.0);
    vec4 viewSpacePos = u_InvViewProj * clipPos;
    vec3 rayDir = normalize(viewSpacePos.xyz / viewSpacePos.w);

    vec3 viewPos = vec3(0.0, u_ViewHeight, 0.0);

    vec3 lum = getValFromSkyLUT(rayDir, u_SunDir);
    vec3 sunLum = sunWithBloom(rayDir, u_SunDir);
    sunLum = smoothstep(0.002, 1.0, sunLum);
    if (length(sunLum) > 0.0) {
        if (rayIntersectSphere(viewPos, rayDir, groundRadius) >= 0.0) {
            sunLum *= 0.0;
        } else {
            // If the sun value is applied to this pixel,
            // we need to calculate the transmittance to obscure it.
            sunLum *= getValFromTLUT(viewPos, u_SunDir);
        }
    }
    lum += sunLum;

    lum *= 20.0;
    lum = pow(lum, vec3(1.3));
    lum /= (smoothstep(0.0, 0.2, clamp(u_SunDir.y, 0.0, 1.0)) * 2.0 + 0.15);

    lum = jodieReinhardTonemap(lum);
    lum = pow(lum, vec3(1.0 / 2.2)); // Gamma standard

    FragColor = vec4(lum, 1.0);
}
)""
