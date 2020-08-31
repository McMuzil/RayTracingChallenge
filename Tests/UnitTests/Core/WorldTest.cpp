#include "pch.h"
#include "CppUnitTest.h"

#include "RayTracer/Core/CollisionInfo.h"
#include "RayTracer/Core/Material.h"
#include "RayTracer/Core/Objects/Sphere.h"
#include "RayTracer/Core/PointLight.h"
#include "RayTracer/Core/Ray.h"
#include "RayTracer/Core/Transform.h"
#include "RayTracer/Core/World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(WorldTest)
    {
    public:

        TEST_METHOD(DefaultWorld)
        {
            PointLight pointLight(Vec3D(-10, 10, -10), Vec3D(1, 1, 1));

            Sphere sphere1;
            Material material1;
            material1.SetColor(Vec3D(0.8f, 1.f, 0.6f));
            material1.SetDiffuse(0.7f);
            material1.SetSpecular(0.2f);
            sphere1.SetMaterial(material1);

            Sphere sphere2;
            sphere2.SetTransform(Transform::Scaling(Vec3D(0.5f)));

            World w = World::CreateDefault();
            Assert::IsTrue(w.GetLight() == pointLight);
            Assert::IsTrue(w.Contains(sphere1));
            Assert::IsTrue(w.GetObjects().size() == 2);
            Assert::IsTrue(*w.GetObjects()[0] == sphere1);
            Assert::IsTrue(w.Contains(sphere2));
            Assert::IsTrue(*w.GetObjects()[1] == sphere2);
        }

        TEST_METHOD(IntersectWorld)
        {
            World w = World::CreateDefault();
            Ray r(Vec3D(0, 0, -5), Vec3D(0, 0, 1));

            CollisionInfo info = w.Intersect(r);

            Assert::AreEqual(int(info.hits.size()), 4);
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(info.hits[0].distance, 4.f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(info.hits[1].distance, 4.5f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(info.hits[2].distance, 5.5f));
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(info.hits[3].distance, 6.f));
        }
    };
}
