#include "pch.h"
#include "CppUnitTest.h"

#include "Core/CollisionInfo.h"
#include "Core/Lighting.h"
#include "Core/Material.h"
#include "Core/Objects/Object.h"
#include "Core/Objects/Plane.h"
#include "Core/Objects/Sphere.h"
#include "Core/Pattern/StripePattern.h"
#include "Core/PointLight.h"
#include "Core/Ray.h"
#include "Core/Transform.h"
#include "Core/Vector.h"
#include "Core/World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(LightingTest)
    {
    public:

        Sphere DefaultObject;
        const Vec3D Position;

        TEST_METHOD(EyeBetweenLightAndSurface)
        {
            Vec3D toEye(0, 0, -1);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 0, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultObject, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(1.9f, 1.9f, 1.9f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(EyeBetweenLightAndSurfaceInShadow)
        {
            Vec3D toEye(0, 0, -1);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 0, -10), Vec3D(1, 1, 1));
            bool inShadow = true;

            Vec3D result = Lighting::Calculate(DefaultObject, pointLight, Position, toEye, normal, inShadow);

            Assert::IsTrue(Vec3D(0.1f, 0.1f, 0.1f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(EyeBetweenLightAndSurfaceAndEyeOffset45)
        {
            float f = sqrt(2.f) / 2.f;
            Vec3D toEye(0, f, -f);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 0, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultObject, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(1.f, 1.f, 1.f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(EyeOppositeSurfaceAndLightOffset45)
        {
            Vec3D toEye(0, 0, -1);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 10, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultObject, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(0.7364f, 0.7364f, 0.7364f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(EyeInPathOfReflectionVector)
        {
            float f = sqrt(2.f) / 2.f;
            Vec3D toEye(0, -f, -f);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 10, -10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultObject, pointLight, Position, toEye, normal);

            Assert::IsTrue(Vec3D(1.63638f, 1.63638f, 1.63638f).IsEqualWithEpsilon(result));
        }

        TEST_METHOD(LightBehindSurface)
        {
            Vec3D toEye(0, 0, -1);
            Vec3D normal(0, 0, -1);
            PointLight pointLight(Vec3D(0, 0, 10), Vec3D(1, 1, 1));

            Vec3D result = Lighting::Calculate(DefaultObject, pointLight, Position, toEye, normal);

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

        TEST_METHOD(ColorWithShadow)
        {
            World world;
            auto& objects = world.GetObjects();

            world.SetLight(PointLight(Vec3D(0, 0, -10), Vec3D(1, 1, 1)));

            objects.emplace_back(std::make_unique<Sphere>());

            auto sphere = std::make_unique<Sphere>();
            sphere->SetTransform(Transform::Translation(0, 0, 10));
            objects.emplace_back(std::move(sphere));

            Ray ray(Vec3D(0, 0, 5), Vec3D(0, 0, 1));

            Vec3D color = Lighting::Calculate(world, ray);

            Assert::IsTrue(Vec3D(0.1f, 0.1f, 0.1f).IsEqualWithEpsilon(color));
        }

        TEST_METHOD(ColorWithPattern)
        {
            Material material = DefaultObject.GetMaterial();
            material.SetPattern(std::make_unique<StripePattern>(Vec3D(1.f), Vec3D(0.f)));
            material.SetAmbient(1.f);
            material.SetDiffuse(0.f);
            material.SetSpecular(0.f);
            DefaultObject.SetMaterial(material);
            const Vec3D toEye(0, 0, -1);
            const Vec3D normal(0, 0, -1);
            const PointLight light(Vec3D(0, 0, -10), Vec3D(1, 1, 1));

            const Vec3D color1 = Lighting::Calculate(DefaultObject, light, Vec3D(0.9f, 0, 0), toEye, normal);
            Assert::IsTrue(color1.IsEqualWithEpsilon(Vec3D(1, 1, 1)));
            const Vec3D color2 = Lighting::Calculate(DefaultObject, light, Vec3D(1.1f, 0, 0), toEye, normal);
            Assert::IsTrue(color2.IsEqualWithEpsilon(Vec3D(0, 0, 0)));
        }

        TEST_METHOD(ColorWithPatternAppliedAndObjectTransformation)
        {
            DefaultObject.SetTransform(Transform::Scaling(2.f, 1.f, 1.f));

            Material material = DefaultObject.GetMaterial();
            material.SetPattern(std::make_unique<StripePattern>(Vec3D(1.f), Vec3D(0.f)));
            material.SetAmbient(1.f);
            material.SetDiffuse(0.f);
            material.SetSpecular(0.f);
            DefaultObject.SetMaterial(material);
            const Vec3D toEye(0, 0, -1);
            const Vec3D normal(0, 0, -1);
            const PointLight light(Vec3D(0, 0, -10), Vec3D(1, 1, 1));

            const Vec3D color1 = Lighting::Calculate(DefaultObject, light, Vec3D(1.5f, 0, 0), toEye, normal);
            Assert::IsTrue(color1.IsEqualWithEpsilon(Vec3D(1, 1, 1)));
        }

        TEST_METHOD(ColorWithPatternTransformation)
        {
            auto pattern = std::make_unique<StripePattern>(Vec3D(1.f), Vec3D(0.f));
            pattern->SetTransform(Transform::Scaling(2.f, 1.f, 1.f));

            Material material = DefaultObject.GetMaterial();
            material.SetPattern(std::move(pattern));
            material.SetAmbient(1.f);
            material.SetDiffuse(0.f);
            material.SetSpecular(0.f);
            DefaultObject.SetMaterial(material);
            const Vec3D toEye(0, 0, -1);
            const Vec3D normal(0, 0, -1);
            const PointLight light(Vec3D(0, 0, -10), Vec3D(1, 1, 1));

            const Vec3D color1 = Lighting::Calculate(DefaultObject, light, Vec3D(1.5f, 0, 0), toEye, normal);
            Assert::IsTrue(color1.IsEqualWithEpsilon(Vec3D(1, 1, 1)));
        }

        TEST_METHOD(ColorWithPatternAndObjectTransformations)
        {
            DefaultObject.SetTransform(Transform::Scaling(2.f, 2.f, 2.f));

            auto pattern = std::make_unique<StripePattern>(Vec3D(1.f), Vec3D(0.f));
            pattern->SetTransform(Transform::Translation(0.5f, 0.0f, 0.0f));

            Material material = DefaultObject.GetMaterial();
            material.SetPattern(std::move(pattern));
            material.SetAmbient(1.f);
            material.SetDiffuse(0.f);
            material.SetSpecular(0.f);
            DefaultObject.SetMaterial(material);
            const Vec3D toEye(0, 0, -1);
            const Vec3D normal(0, 0, -1);
            const PointLight light(Vec3D(0, 0, -10), Vec3D(1, 1, 1));

            const Vec3D color1 = Lighting::Calculate(DefaultObject, light, Vec3D(2.5f, 0, 0), toEye, normal);
            Assert::IsTrue(color1.IsEqualWithEpsilon(Vec3D(1, 1, 1)));
        }

        TEST_METHOD(ShadowBias)
        {
            Ray ray(Vec3D(0, 0, -5), Vec3D(0, 0, 1));
            Sphere sphere;
            sphere.SetTransform(Transform::Translation(0, 0, 1));
            
            CollisionInfo info = sphere.Intersect(ray);
            const Hit* hit = info.GetFirstHit();

            Assert::IsNotNull(hit);
            Assert::AreEqual(5.f, hit->distance);
            Assert::IsTrue(hit->biasedPoint.z < -Constants::ShadowBias / 2.f);
            Assert::IsTrue(hit->biasedPoint.z < hit->point.z);
        }

        TEST_METHOD(ShadowWhenPointNotCollinearWithObjectAndLight)
        {
            World world = World::CreateDefault();
            Vec3D point(0, 10, 0);

            Assert::IsFalse(Lighting::IsInShadow(world, point), L"The point must not be in shadow.");
        }

        TEST_METHOD(ShadowWhenObjectBetweenPointAndLight)
        {
            World world = World::CreateDefault();
            Vec3D point(10, -10, 10);

            Assert::IsTrue(Lighting::IsInShadow(world, point), L"The point must be in shadow.");
        }

        TEST_METHOD(ShadowWhenObjectBehindLight)
        {
            World world = World::CreateDefault();
            Vec3D point(-20, 20, -20);

            Assert::IsFalse(Lighting::IsInShadow(world, point), L"The point must not be in shadow.");
        }

        TEST_METHOD(ShadowWhenObjectBehindPoint)
        {
            World world = World::CreateDefault();
            Vec3D point(-2, 2, -2);

            Assert::IsFalse(Lighting::IsInShadow(world, point), L"The point must not be in shadow.");
        }

        TEST_METHOD(ReflectedColorForNonReflectiveMaterial)
        {
            World world = World::CreateDefault();
            Ray ray(Vec3D(0.f), Vec3D(0, 0, 1));
            Object* object = world.GetObjects()[1].get();
            object->GetMaterial().SetAmbient(1.f);

            Hit hit;
            hit.distance = 1.f;
            object->FillIntersectionInfo(hit, ray);

            Vec3D color = Lighting::CalculateReflectedColor(world, &hit);

            Assert::IsTrue(color.IsEqualWithEpsilon(Vec3D(0.f)));
        }

        TEST_METHOD(ReflectedColorForReflectiveMaterial)
        {
            World world = World::CreateDefault();
            float f = sqrt(2.f) / 2.f;
            Ray ray(Vec3D(0, 0, -3), Vec3D(0, -f, f));
            Plane plane;
            plane.GetMaterial().SetReflectivity(0.5f);
            plane.SetTransform(Transform::Translation(0, -1, 0));
            world.GetObjects().emplace_back(std::make_unique<Plane>(plane));

            Hit hit;
            hit.distance = sqrt(2.f);
            plane.FillIntersectionInfo(hit, ray);

            Vec3D color = Lighting::CalculateReflectedColor(world, &hit);

            Assert::IsTrue(color.IsEqualWithEpsilon(Vec3D(0.19206f, 0.24007f, 0.14404f)));
        }

        TEST_METHOD(CalculateColorForReflectiveMaterial)
        {
            World world = World::CreateDefault();
            float f = sqrt(2.f) / 2.f;
            Ray ray(Vec3D(0, 0, -3), Vec3D(0, -f, f));
            auto plane = std::make_unique<Plane>();
            plane->GetMaterial().SetReflectivity(0.5f);
            plane->SetTransform(Transform::Translation(0, -1, 0));
            Object* planePtr = plane.get();
            world.GetObjects().emplace_back(std::move(plane));

            Hit hit;
            hit.distance = sqrt(2.f);
            planePtr->FillIntersectionInfo(hit, ray);

            Vec3D color = Lighting::Calculate(world, &hit);

            Assert::IsTrue(color.IsEqualWithEpsilon(Vec3D(0.87848f, 0.92649f, 0.83047f)));
        }

        TEST_METHOD(CalculateColorTwoParallelMirrors)
        {
            World world;
            world.SetLight(PointLight(Vec3D(0), Vec3D(1, 1, 1)));

            World::ObjectsVector& objects = world.GetObjects();
            auto upperPlane = std::make_unique<Plane>();
            upperPlane->GetMaterial().SetReflectivity(1.f);
            upperPlane->SetTransform(Transform::Translation(0, -1, 0));
            objects.emplace_back(std::move(upperPlane));

            auto lowerPlane = std::make_unique<Plane>();
            lowerPlane->GetMaterial().SetReflectivity(1.f);
            lowerPlane->SetTransform(Transform::Translation(0, 1, 0));
            objects.emplace_back(std::move(lowerPlane));

            Ray ray(Vec3D(0, 0, -3), Vec3D(0, 1, 0));

            Vec3D color = Lighting::Calculate(world, ray);

            // To pass this test we should just reach this point
            Assert::IsTrue(true);
        }

        TEST_METHOD(ReflectedColorForReflectiveMaterialZeroBounces)
        {
            World world = World::CreateDefault();
            float f = sqrt(2.f) / 2.f;
            Ray ray(Vec3D(0, 0, -3), Vec3D(0, -f, f));
            Plane plane;
            plane.GetMaterial().SetReflectivity(0.5f);
            plane.SetTransform(Transform::Translation(0, -1, 0));
            world.GetObjects().emplace_back(std::make_unique<Plane>(plane));

            Hit hit;
            hit.distance = sqrt(2.f);
            plane.FillIntersectionInfo(hit, ray);

            Vec3D color = Lighting::CalculateReflectedColor(world, &hit, 0);

            Assert::IsTrue(color.IsEqualWithEpsilon(Vec3D(0.f)));
        }
    };
}
