#define MAIN_SPACE(name) namespace name { int main(int argc, char* argv[]); }

namespace Ch00 {
    MAIN_SPACE(Test)
}

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
    MAIN_SPACE(Materials)
    MAIN_SPACE(LightingMapsDiffuse)
    MAIN_SPACE(LightingMapsSpecular)
    MAIN_SPACE(LightingMapsEmission)
    MAIN_SPACE(LightCastersDirectional)
    MAIN_SPACE(LightCastersPoint)
    MAIN_SPACE(LightCastersSpot)
    MAIN_SPACE(LightCastersSoft)
    MAIN_SPACE(MultipleLight)
}

namespace Ch03 {
    MAIN_SPACE(ModelLoading)
}

namespace Ch04 {
    MAIN_SPACE(DepthTesting)
    MAIN_SPACE(StencilTesting)
    MAIN_SPACE(BlendingDiscard)
    MAIN_SPACE(BlendingSorted)
    MAIN_SPACE(Framebuffers)
}

int main(int argc, char* argv[])
{
    return Ch04::Framebuffers::main(argc, argv);
}
