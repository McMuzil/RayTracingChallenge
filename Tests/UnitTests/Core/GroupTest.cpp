#include "pch.h"
#include "CppUnitTest.h"

#include "RayTracer/Core/Helpers.h"
#include "RayTracer/Core/Vector.h"
#include "RayTracer/Core/Objects/Object.h"
#include "RayTracer/Core/Matrix.h"
#include "RayTracer/Core/ObjectHelpers.h"
#include "RayTracer/Core/Objects/Group.h"
#include "RayTracer/Core/Objects/Sphere.h"
#include "RayTracer/Core/Ray.h"
#include "RayTracer/Core/Transform.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(GroupTest)
    {
    public:

        TEST_METHOD(CreatingNewGroup)
        {
            Group group;

            Assert::IsTrue(group.GetChildren().size() == 0);
            Assert::IsTrue(group.GetTransform().IsEqualWithEpsilon(Matrix<4, 4>::Identity()));
        }

        TEST_METHOD(AddingChildToGroup)
        {
            Group group;

            std::unique_ptr<Object> object = std::make_unique<Sphere>();

            group.AddChild(object.get());

            const std::vector<Object*>& children = group.GetChildren();

            Assert::IsTrue(children.size() != 0);
            Assert::IsTrue(children[0] == object.get());
            Assert::IsTrue(object->GetParent() == &group);
        }

        TEST_METHOD(IntersectingRayWithEmptyGroup)
        {
            Group group;
            Ray ray(Vec3D(0.f), Vec3D(0, 0, 1));

            CollisionInfo info = group.IntersectInternal(ray);

            Assert::IsTrue(info.hits.size() == 0);
        }

        TEST_METHOD(IntersectingRayWithNonEmptyGroup)
        {
            Group group;

            Sphere sphere1;
            Sphere sphere2;
            sphere2.SetTransform(Transform::Translation(0, 0, -3));
            Sphere sphere3;
            sphere3.SetTransform(Transform::Translation(5, 0, 0));
            group.AddChild(&sphere1);
            group.AddChild(&sphere2);
            group.AddChild(&sphere3);

            Ray ray(Vec3D(0.f, 0.f, -5.f), Vec3D(0, 0, 1));

            CollisionInfo info = group.IntersectInternal(ray);

            Assert::IsTrue(info.hits.size() == 4);
            Assert::IsTrue(info.hits[0].object == &sphere2);
            Assert::IsTrue(info.hits[1].object == &sphere2);
            Assert::IsTrue(info.hits[2].object == &sphere1);
            Assert::IsTrue(info.hits[3].object == &sphere1);
        }

        TEST_METHOD(IntersectingTransformedGroup)
        {
            Group group;
            group.SetTransform(Transform::Scaling(Vec3D(2.f)));

            Sphere sphere1;
            sphere1.SetTransform(Transform::Translation(Vec3D(5.f, 0.f, 0.f)));
            group.AddChild(&sphere1);

            Ray ray(Vec3D(10, 0, -10), Vec3D(0, 0, 1));

            CollisionInfo info = group.Intersect(ray);

            Assert::IsTrue(info.hits.size() == 2);
        }

        TEST_METHOD(ConvertPointFromWorldSpaceToObjectSpace)
        {
            Group group1;
            group1.SetTransform(Transform::RotationY(Helpers::ToRad(90.f)));

            Group group2;
            group2.SetTransform(Transform::Scaling(Vec3D(2.f)));

            group1.AddChild(&group2);

            Sphere sphere;
            sphere.SetTransform(Transform::Translation(5, 0, 0));

            group2.AddChild(&sphere);

            Vec3D point = sphere.ToObjectSpace(Vec3D(-2, 0, -10));

            Assert::IsTrue(point.IsEqualWithEpsilon(Vec3D(0, 0, -1)));
        }

        TEST_METHOD(ConvertNormalFromObjectSpaceToWorldSpace)
        {
            Group group1;
            group1.SetTransform(Transform::RotationY(Helpers::ToRad(90.f)));

            Group group2;
            group2.SetTransform(Transform::Scaling(Vec3D(1.f, 2.f, 3.f)));

            group1.AddChild(&group2);

            Sphere sphere;
            sphere.SetTransform(Transform::Translation(5, 0, 0));

            group2.AddChild(&sphere);

            float f = sqrt(3.f) / 3.f;
            Vec3D normal = sphere.ToWorldSpace(Vec3D(f, f, f));
            normal = normal.Normalize();

            Assert::IsTrue(normal.IsEqualWithEpsilon(Vec3D(0.28571f, 0.42857f, -0.85714f)));
        }

        TEST_METHOD(FindNormalOnChildObject)
        {
            Group group1;
            group1.SetTransform(Transform::RotationY(Helpers::ToRad(90.f)));

            Group group2;
            group2.SetTransform(Transform::Scaling(Vec3D(1.f, 2.f, 3.f)));

            group1.AddChild(&group2);

            Sphere sphere;
            sphere.SetTransform(Transform::Translation(5, 0, 0));

            group2.AddChild(&sphere);

            Vec3D normal = sphere.NormalAt(Vec3D(1.7321f, 1.1547f, -5.5774f));
            normal = normal.Normalize();

            Assert::IsTrue(normal.IsEqualWithEpsilon(Vec3D(0.28570f, 0.42854f, -0.85716f)));
        }
    };
}
