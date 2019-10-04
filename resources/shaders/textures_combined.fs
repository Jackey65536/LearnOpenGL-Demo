#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;
uniform int roateValue;

void main()
{
    // 返回80%的第一个输入颜色和20%的第二个输入颜色
//    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    //    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue) * vec4(ourColor, 1);
    if (roateValue%3 == 0) {
        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue) * vec4(ourColor.r, ourColor.g, ourColor.b, 1);
    } else if (roateValue%3 == 1) {
        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue) * vec4(ourColor.b, ourColor.r, ourColor.g, 1);
    } else if (roateValue%3 == 2) {
        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue) * vec4(ourColor.g, ourColor.b, ourColor.r, 1);
    }
}
