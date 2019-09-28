#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;

void main()
{
    // 返回80%的第一个输入颜色和20%的第二个输入颜色
//    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
}
