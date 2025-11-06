#version 450

out vec4 fragColor;
in vec3 fragmentLocalPosition;
uniform samplerCube UISky;

void main () {
    fragColor = vec4(0.1,0.1,0.1,0.1)+texture(UISky, fragmentLocalPosition);
}
