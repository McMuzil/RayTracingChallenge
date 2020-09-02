#include "pch.h"
#include "CppUnitTest.h"

#include "RayTracer/Core/Objects/Sphere.h"
#include "RayTracer/Core/Transform.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(SphereTest)
    {
    public:

        std::unique_ptr<Object> TestObject() const
        {
            return std::make_unique<Sphere>();
        }

        TEST_METHOD(ObjectHasParentAttribute)
        {
            std::unique_ptr<Object> object = TestObject();

            Assert::IsNull(object->GetParent());
        }

        TEST_METHOD(DefaultTransformation)
        {
            std::unique_ptr<Object> object = TestObject();

            Assert::IsTrue(Matrix<4, 4>::Identity().IsEqualWithEpsilon(object->GetTransform()));
        }

        TEST_METHOD(SetTranform)
        {
            std::unique_ptr<Object> object = TestObject();

            Matrix<4, 4> t = Transform::Translation(2, 3, 4);
            object->SetTransform(t);

            Assert::IsTrue(t.IsEqualWithEpsilon(object->GetTransform()));
        }

        TEST_METHOD(NormalAtAxisX)
        {
            const std::unique_ptr<Object> object = TestObject();
            const Vec3D normal = object->NormalAt(1, 0, 0);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(1, 0, 0), normal));
        }

        TEST_METHOD(NormalAtAxisY)
        {
            const std::unique_ptr<Object> object = TestObject();
            const Vec3D normal = object->NormalAt(0, 1, 0);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(0, 1, 0), normal));
        }

        TEST_METHOD(NormalAtAxisZ)
        {
            const std::unique_ptr<Object> object = TestObject();
            const Vec3D normal = object->NormalAt(0, 0, 1);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(0, 0, 1), normal));
        }

        TEST_METHOD(NormalAtNonaxialPoint)
        {
            const std::unique_ptr<Object> object = TestObject();
            const float f = sqrt(3.f) / 3.f;
            const Vec3D normal = object->NormalAt(f, f, f);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(f, f, f), normal));
        }

        TEST_METHOD(NormalIsNormalized)
        {
            const std::unique_ptr<Object> object = TestObject();
            const float f = sqrt(3.f) / 3.f;
            const Vec3D normal = object->NormalAt(f, f, f);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(normal, normal.Normalize()));
        }

        TEST_METHOD(NormalOnTranslatedSphere)
        {
            std::unique_ptr<Object> object = TestObject();
            object->SetTransform(Transform::Translation(0, 1, 0));
            const Vec3D normal = object->NormalAt(0, 1.70711f, -0.70711f);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(0, 0.70711f, -0.70711f), normal));
        }

        TEST_METHOD(NormalOnTransformedSphere)
        {
            std::unique_ptr<Object> object = TestObject();
            Matrix<4, 4> transform = Transform::Scaling(1.f, 0.5f, 1.f) * Transform::RotationZ(Constants::Pi / 5.f);
            object->SetTransform(transform);
            const float f = sqrt(2.f) / 2.f;
            const Vec3D normal = object->NormalAt(0, f, -f);
            Assert::IsTrue(Vec3D::IsEqualWithEpsilon(Vec3D(0, 0.97014f, -0.24254f), normal));
        }

        TEST_METHOD(DefaultMaterial)
        {
            const std::unique_ptr<Object> object = TestObject();

            Assert::AreEqual(object->GetMaterial(), Material());
        }

        TEST_METHOD(SetMaterialTest)
        {
            std::unique_ptr<Object> object = TestObject();

            Material material = object->GetMaterial();
            material.SetAmbient(1.f);
            object->SetMaterial(material);

            Assert::AreEqual(object->GetMaterial(), material);
        }
    };
}
