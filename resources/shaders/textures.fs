#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord; // 纹理坐标

// sampler2D：采样器
uniform sampler2D texture1;

void main()
{
    // 使用之前设置的纹理参数对相应的颜色值进行采样。这个片段着色器的输出就是纹理的（插值）纹理坐标上的（过滤后的）颜色
//    FragColor = texture(texture1, TexCoord);
    FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0); // 将纹理颜色与定点颜色混合
}
