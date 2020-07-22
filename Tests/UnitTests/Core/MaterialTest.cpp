#include "pch.h"
#include "CppUnitTest.h"
#include "Core/Material.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(MaterialTest)
    {
    public:

        TEST_METHOD(DefaultMaterial)
        {
            const Material material;

            Assert::IsTrue(Vec3D(1, 1, 1).IsEqualWithEpsilon(material.GetColor()));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(material.GetAmbient(), 0.1f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(material.GetDiffuse(), 0.9f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(material.GetSpecular(), 0.9f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(material.GetShininess(), 200.f));
        }
    };
}
