#include "pch.h"
#include "CppUnitTest.h"

#include "Core/CollisionInfo.h"
#include "Core/Lighting.h"
#include "Core/Material.h"
#include "Core/Object.h"
#include "Core/PointLight.h"
#include "Core/Ray.h"
#include "Core/Vector.h"
#include "Core/World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(LightingTest)
    {
    public:

        const Material DefaultMaterial;
        const Vec3D Position;

        TEST_METHOD(EyeBetweenLightAndSurface)
        {
            Vec3D toEye(0, 0, -1);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 0, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultMaterial, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(1.9f, 1.9f, 1.9f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(EyeBetweenLightAndSurfaceAndEyeOffset45)
        {
            float f = sqrt(2.f) / 2.f;
            Vec3D toEye(0, f, -f);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 0, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultMaterial, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(1.f, 1.f, 1.f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(EyeOppositeSurfaceAndLightOffset45)
        {
            Vec3D toEye(0, 0, -1);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 10, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultMaterial, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(0.7364f, 0.7364f, 0.7364f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(EyeInPathOfReflectionVector)
        {
            float f = sqrt(2.f) / 2.f;
            Vec3D toEye(0, -f, -f);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 10, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultMaterial, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(1.63638f, 1.63638f, 1.63638f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(LightBehindSurface)
        {
            Vec3D toEye(0, 0, -1);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 0, 10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultMaterial, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(0.1f, 0.1f, 0.1f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(ShadingAnIntersectionOutside)
        {
            World w = World::CreateDefault();
            Ray r(Vec3D(0, 0, -5), Vec3D(0, 0, 1));
            const Object& sphere = *(w.GetObjects()[0]);
            CollisionInfo info = sphere.Intersect(r);

            const Hit* hit = info.GetFirstHit();
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(hit->distance, 4.f), L"Wrong hit.");

            Vec3D color = Lighting::Calculate(w, hit);
            Assert::IsTrue(color.IsEqualWithEpsilon(Vec3D(0.38066f, 0.47583f, 0.2855f)));
        }

        TEST_METHOD(ShadingAnIntersectionInside)
        {
            World w = World::CreateDefault();
            w.SetLight(PointLight(Vec3D(0.f, 0.25f, 0.f), Vec3D(1, 1, 1)));
            Ray r(Vec3D(0, 0, 0), Vec3D(0, 0, 1));
            const Object& sphere = *(w.GetObjects()[1]);
            CollisionInfo info = sphere.Intersect(r);

            Assert::IsTrue(info.hits.size() == 2, L"We should have to hits between the sphere and the ray.");
            const Hit* hit = &info.hits[1]; // Get the inner to out hit
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(hit->distance, 0.5f), L"Wrong hit.");

            Vec3D color = Lighting::Calculate(w, hit);
            Assert::IsTrue(color.IsEqualWithEpsilon(Vec3D(0.90498f, 0.90498f, 0.90498f)));
        }

        TEST_METHOD(ColorWhenRayMissesTheWorld)
        {
            World w = World::CreateDefault();
            Ray r(Vec3D(0, 0, -5), Vec3D(0, 1, 0));
            Vec3D color = Lighting::Calculate(w, r);

            Assert::IsTrue(Vec3D(0.f).IsEqualWithEpsilon(color));
        }

        TEST_METHOD(ColorWhenRayHitsTheWorld)
        {
            World w = World::CreateDefault();
            Ray r(Vec3D(0, 0, -5), Vec3D(0, 0, 1));
            Vec3D color = Lighting::Calculate(w, r);

            Assert::IsTrue(Vec3D(0.38066f, 0.47583f, 0.2855f).IsEqualWithEpsilon(color));
        }

        TEST_METHOD(ColorWithIntersectionBehindRay)
        {
            World w = World::CreateDefault();

            std::unique_ptr<Object>& outer = w.GetObjects()[0];
            Material material = outer->GetMaterial();
            material.SetAmbient(1.f);
            outer->SetMaterial(material);

            std::unique_ptr<Object>& inner = w.GetObjects()[1];
            material = inner->GetMaterial();
            material.SetAmbient(1.f);
            inner->SetMaterial(material);

            Ray r(Vec3D(0, 0, 0.75f), Vec3D(0, 0, -1));
            Vec3D color = Lighting::Calculate(w, r);

            Assert::IsTrue(inner->GetMaterial().GetColor().IsEqualWithEpsilon(color), L"The color should be equal to inners sphere.");
        }
    };
}
