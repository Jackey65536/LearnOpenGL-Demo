#define MAIN_SPACE(name) namespace name { int main(int argc, char* argv[]); }

namespace Ch01 {
    MAIN_SPACE(HelloTriangleIndexed)
    MAIN_SPACE(ShadersInterpolation)
    MAIN_SPACE(ShadersUniform)
    MAIN_SPACE(ShadersClass)
    MAIN_SPACE(Textures)
    MAIN_SPACE(TexturesCombined)
}

int main(int argc, char* argv[])
{
    return Ch01::TexturesCombined::main(argc, argv);
}
