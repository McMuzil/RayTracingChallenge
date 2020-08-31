#include "pch.h"
#include "CppUnitTest.h"

#include "RayTracer/Core/CollisionInfo.h"
#include "RayTracer/Core/Lighting.h"
#include "RayTracer/Core/Material.h"
#include "RayTracer/Core/Objects/Object.h"
#include "RayTracer/Core/Objects/Plane.h"
#include "RayTracer/Core/Objects/Sphere.h"
#include "RayTracer/Core/Pattern/StripePattern.h"
#include "RayTracer/Core/PointLight.h"
#include "RayTracer/Core/Ray.h"
#include "RayTracer/Core/Transform.h"
#include "RayTracer/Core/Vector.h"
#include "RayTracer/Core/World.h"
#include "RayTracer/Core/Helpers.h"
#include "RayTracer/Core/ObjectHelpers.h"
#include "Tests/UnitTests/Core/PatternMockup.h"

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

        TEST_METHOD(BiasedAbove)
        {
            Ray ray(Vec3D(0, 0, -5), Vec3D(0, 0, 1));
            Sphere sphere;
            sphere.SetTransform(Transform::Translation(0, 0, 1));

            CollisionInfo info = sphere.Intersect(ray);
            const Hit* hit = info.GetFirstHit();

            Assert::IsNotNull(hit);
            Assert::AreEqual(5.f, hit->distance);
            Assert::IsTrue(hit->biasedAbove.z < -Constants::BiasAbove / 2.f);
            Assert::IsTrue(hit->biasedAbove.z < hit->point.z);
        }

        TEST_METHOD(BiasedBelow)
        {
            Ray ray(Vec3D(0, 0, -5), Vec3D(0, 0, 1));
            std::unique_ptr<Object> sphere = Helpers::CreateGlassSphere();
            sphere->SetTransform(Transform::Translation(0, 0, 1));

            CollisionInfo info = sphere->Intersect(ray);
            const Hit* hit = info.GetFirstHit();

            Assert::IsNotNull(hit);
            Assert::AreEqual(5.f, hit->distance);
            Assert::IsTrue(hit->biasedBelow.z > Constants::BiasBelow / 2.f);
            Assert::IsTrue(hit->biasedBelow.z > hit->point.z);
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

            Assert::IsTrue(color.IsEqualWithEpsilon(Vec3D(0.19033f, 0.23791f, 0.14275f)));
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

            Assert::IsTrue(color.IsEqualWithEpsilon(Vec3D(0.87676f, 0.92434f, 0.82917f)));
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

        TEST_METHOD(RefractionsAtVariousIntersections)
        {
            std::unique_ptr<Object> a = Helpers::CreateGlassSphere();
            a->SetTransform(Transform::Scaling(2.f));
            a->GetMaterial().SetRefractiveIndex(1.5f);

            std::unique_ptr<Object> b = Helpers::CreateGlassSphere();
            b->SetTransform(Transform::Translation(0.f, 0.f, -0.25f));
            b->GetMaterial().SetRefractiveIndex(2.f);

            std::unique_ptr<Object> c = Helpers::CreateGlassSphere();
            c->SetTransform(Transform::Translation(0.f, 0.f, 0.25f));
            c->GetMaterial().SetRefractiveIndex(2.5f);

            const Ray r(Vec3D(0, 0, -4), Vec3D(0, 0, 1));
            CollisionInfo info;
            info.hits = {
                Hit(2.f, a.get()),
                Hit(2.75f, b.get()),
                Hit(3.25f, c.get()),
                Hit(4.75f, b.get()),
                Hit(5.25f, c.get()),
                Hit(6.f, a.get()),
            };

            const std::vector<float> inResults = { 1.0f, 1.5f, 2.0f, 2.5f, 2.5f, 1.5f };
            const std::vector<float> outResults = { 1.5f, 2.0f, 2.5f, 2.5f, 1.5f, 1.0f };

            for (size_t i = 0; i < 6; i++)
            {
                info.hits[i].object->FillRefractionIndices(info.hits[i], info);
                Assert::IsTrue(Helpers::IsEqualWithEpsilon(info.hits[i].refractiveIndexFrom, inResults[i]), std::to_wstring(i).c_str());
                Assert::IsTrue(Helpers::IsEqualWithEpsilon(info.hits[i].refractiveIndexTo, outResults[i]), std::to_wstring(i).c_str());
            }
        }

        TEST_METHOD(RefractedColorOpaqueSurface)
        {
            World world = World::CreateDefault();
            Ray ray(Vec3D(0, 0, -5), Vec3D(0, 0, 1));
            const Object* sphere = world.GetObjects()[0].get();

            CollisionInfo info;
            info.hits = {
                Hit(4.f, sphere),
                Hit(6.f, sphere),
            };

            sphere->FillIntersectionInfo(info.hits[0], ray, info);

            Vec3D refractedColor = Lighting::CalculateRefractedColor(world, &info.hits[0]);

            Assert::IsTrue(refractedColor.IsEqualWithEpsilon(Vec3D(0.f)));
        }

        TEST_METHOD(RefractedColorMaximumDepth)
        {
            World world = World::CreateDefault();
            Ray ray(Vec3D(0, 0, -5), Vec3D(0, 0, 1));
            Object* sphere = world.GetObjects()[0].get();
            Material& material = sphere->GetMaterial();
            material.SetTransparency(1.f);
            material.SetRefractiveIndex(1.5f);

            CollisionInfo info;
            info.hits = {
                Hit(4.f, sphere),
                Hit(6.f, sphere),
            };

            sphere->FillIntersectionInfo(info.hits[0], ray, info);

            Vec3D refractedColor = Lighting::CalculateRefractedColor(world, &info.hits[0], 0);

            Assert::IsTrue(refractedColor.IsEqualWithEpsilon(Vec3D(0.f)));
        }

        TEST_METHOD(RefractedColorUnderTotalInternalReflection)
        {
            World world = World::CreateDefault();
            float f = sqrt(2.f) / 2.f;
            Ray ray(Vec3D(0, 0, f), Vec3D(0, 1, 0));
            Object* sphere = world.GetObjects()[0].get();
            Material& material = sphere->GetMaterial();
            material.SetTransparency(1.f);
            material.SetRefractiveIndex(1.5f);

            CollisionInfo info;
            info.hits = {
                Hit(-f, sphere),
                Hit( f, sphere),
            };

            sphere->FillIntersectionInfo(info.hits[1], ray, info);

            Vec3D refractedColor = Lighting::CalculateRefractedColor(world, &info.hits[1], 5);

            Assert::IsTrue(refractedColor.IsEqualWithEpsilon(Vec3D(0.f)));
        }

        TEST_METHOD(RefractedColorWithRefractedRay)
        {
            World world = World::CreateDefault();

            Object* first = world.GetObjects()[0].get();
            Material& firstMat = first->GetMaterial();
            firstMat.SetAmbient(1.f);
            firstMat.SetPattern(std::make_unique<PatternMockup>(Vec3D(0.f), Vec3D(0.f)));

            Object* second = world.GetObjects()[1].get();
            Material& secondMat = second->GetMaterial();
            secondMat.SetTransparency(1.f);
            secondMat.SetRefractiveIndex(1.5f);

            Ray ray(Vec3D(0, 0, 0.1f), Vec3D(0, 1, 0));

            CollisionInfo info;
            info.hits = {
                Hit(-0.9899f, first),
                Hit(-0.4899f, second),
                Hit(0.4899f, second),
                Hit(0.9899f, first),
            };

            second->FillIntersectionInfo(info.hits[2], ray, info);

            Vec3D refractedColor = Lighting::CalculateRefractedColor(world, &info.hits[2], 5);

            Assert::IsTrue(refractedColor.IsEqualWithEpsilon(Vec3D(0.f, 0.99888f, 0.04722f)));
        }

        TEST_METHOD(CalculateColorForRefractiveMaterial)
        {
            World world = World::CreateDefault();
            World::ObjectsVector& objects = world.GetObjects();

            std::unique_ptr<Plane> plane = std::make_unique<Plane>();
            const Plane* planePointer = plane.get();
            plane->GetMaterial().SetTransparency(0.5f);
            plane->GetMaterial().SetRefractiveIndex(1.5f);
            plane->SetTransform(Transform::Translation(0, -1, 0));
            objects.emplace_back(std::move(plane));

            std::unique_ptr<Sphere> ball = std::make_unique<Sphere>();
            ball->GetMaterial().SetColor(Vec3D(1.f, 0, 0));
            ball->GetMaterial().SetAmbient(0.5f);
            ball->SetTransform(Transform::Translation(0, -3.5f, -0.5f));
            objects.emplace_back(std::move(ball));

            float f = sqrt(2.f) / 2.f;
            Ray ray(Vec3D(0, 0, -3), Vec3D(0, -f, f));

            Hit hit(sqrt(2.f));
            planePointer->FillIntersectionInfo(hit, ray);
            
            Vec3D color = Lighting::Calculate(world, &hit, Constants::BouncesCount);

            Assert::IsTrue(color.IsEqualWithEpsilon(Vec3D(0.93642f, 0.68642f, 0.68642f)));
        }

        TEST_METHOD(CalculateColorForRefractiveAndReflectiveMaterial)
        {
            World world = World::CreateDefault();
            World::ObjectsVector& objects = world.GetObjects();

            std::unique_ptr<Plane> plane = std::make_unique<Plane>();
            const Plane* planePointer = plane.get();
            plane->GetMaterial().SetTransparency(0.5f);
            plane->GetMaterial().SetReflectivity(0.5f);
            plane->GetMaterial().SetRefractiveIndex(1.5f);
            plane->SetTransform(Transform::Translation(0, -1, 0));
            objects.emplace_back(std::move(plane));

            std::unique_ptr<Sphere> ball = std::make_unique<Sphere>();
            ball->GetMaterial().SetColor(Vec3D(1.f, 0, 0));
            ball->GetMaterial().SetAmbient(0.5f);
            ball->SetTransform(Transform::Translation(0, -3.5f, -0.5f));
            objects.emplace_back(std::move(ball));

            float f = sqrt(2.f) / 2.f;
            Ray ray(Vec3D(0, 0, -3), Vec3D(0, -f, f));

            Hit hit(sqrt(2.f));
            planePointer->FillIntersectionInfo(hit, ray);

            Vec3D color = Lighting::Calculate(world, &hit, Constants::BouncesCount);

            Assert::IsTrue(color.IsEqualWithEpsilon(Vec3D(0.93391f, 0.69643f, 0.69243f)));
        }

        TEST_METHOD(ShlickApproximationTotalInternalReflection)
        {
            std::unique_ptr<Object> shape = Helpers::CreateGlassSphere();
            float f = sqrt(2.f) / 2.f;
            Ray ray(Vec3D(0, 0, f), Vec3D(0, 1, 0));

            CollisionInfo info;
            info.hits = {
                Hit(-f, shape.get()),
                Hit( f, shape.get()),
            };
            shape->FillIntersectionInfo(info.hits[1], ray, info);

            const float reflectance = Lighting::Shlick(info.hits[1]);
            Assert::AreEqual(1.f, reflectance);
        }

        TEST_METHOD(ShlickApproximationPerpendicularViewingAngle)
        {
            std::unique_ptr<Object> shape = Helpers::CreateGlassSphere();
            Ray ray(Vec3D(0, 0, 0), Vec3D(0, 1, 0));

            CollisionInfo info;
            info.hits = {
                Hit(-1, shape.get()),
                Hit( 1, shape.get()),
            };
            shape->FillIntersectionInfo(info.hits[1], ray, info);

            const float reflectance = Lighting::Shlick(info.hits[1]);
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(0.04f, reflectance));
        }

        TEST_METHOD(ShlickApproximationSmallAngle)
        {
            std::unique_ptr<Object> shape = Helpers::CreateGlassSphere();
            Ray ray(Vec3D(0, 0.99f, -2.f), Vec3D(0, 0, 1));

            CollisionInfo info;
            info.hits = {
                Hit(1.8589f, shape.get()),
            };
            shape->FillIntersectionInfo(info.hits[0], ray, info);

            const float reflectance = Lighting::Shlick(info.hits[0]);
            Assert::IsTrue(Helpers::IsEqualWithEpsilon(0.48873f, reflectance));
        }
    };
}
