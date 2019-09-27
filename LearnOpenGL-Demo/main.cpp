#define MAIN_SPACE(name) namespace name { int main(int argc, char* argv[]); }

namespace Ch01 {
    MAIN_SPACE(HelloTriangleIndexed)
    MAIN_SPACE(ShadersInterpolation)
}

int main(int argc, char* argv[])
{
    return Ch01::HelloTriangleIndexed::main(argc, argv);
}
