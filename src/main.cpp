#define MAIN_SPACE(name) namespace name { int main(int argc, char* argv[]); }

namespace Ch01 {
    MAIN_SPACE(HelloTriangleIndexed)
    MAIN_SPACE(ShadersInterpolation)
    MAIN_SPACE(ShadersUniform)
    MAIN_SPACE(ShadersClass)
    MAIN_SPACE(Textures)
    MAIN_SPACE(TexturesCombined)
    MAIN_SPACE(Transformations)
    MAIN_SPACE(CoordinateSystems)
    MAIN_SPACE(CoordinateSystemsDepth)
    MAIN_SPACE(CoordinateSystemsMultiple)
    MAIN_SPACE(CameraKeyboardDt)
    MAIN_SPACE(CameraMouseZoom)
}

namespace Ch02 {
    MAIN_SPACE(Colors)
    MAIN_SPACE(BasicLightingDiffuse)
    MAIN_SPACE(BasicLightingSpecular)
}

int main(int argc, char* argv[])
{
    return Ch02::BasicLightingSpecular::main(argc, argv);
}
