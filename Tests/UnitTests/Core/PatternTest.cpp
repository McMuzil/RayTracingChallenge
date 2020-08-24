#include "pch.h"
#include "CppUnitTest.h"

#include "Core/Material.h"
#include "Core/Objects/Sphere.h"
#include "Core/Pattern/Pattern.h"
#include "Core/Pattern/PatternFactory.h"
#include "Core/Pattern/SpecificPatternFactory.h"
#include "Core/Pattern/StripePattern.h"
#include "Core/Transform.h"
#include "Core/Vector.h"

class PatternMockup : public Pattern
{
public:
    using Pattern::Pattern;

    Vec3D GetColorAt(const Vec3D& position) const override
    {
        return position;
    }

    std::unique_ptr<ICloneable> Clone() const override
    {
        PatternMockup pattern(*this);
        return std::make_unique<PatternMockup>(pattern);
    }
};

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(PatternTest)
    {
    public:

        const Vec3D BlackColor = Vec3D(0.f);
        const Vec3D WhiteColor = Vec3D(1.f);
        const std::string StripePatternType = "Stripe";

        TEST_CLASS_INITIALIZE(SetUp)
        {
            PatternFactory::Set(std::make_unique<SpecificPatternFactory>());
        }

        TEST_CLASS_CLEANUP(TearDown)
        {
            PatternFactory::Set(nullptr);
        }

        TEST_METHOD(GeneralPatternTest)
        {
            std::unique_ptr<Pattern> pattern = PatternFactory::Get()->Create(StripePatternType, WhiteColor, BlackColor);

            Assert::IsNotNull(pattern.get());
            Assert::AreEqual((int) pattern->GetColorCount(), 2);
            Assert::IsTrue(WhiteColor.IsEqualWithEpsilon(pattern->GetColor(0)));
            Assert::IsTrue(BlackColor.IsEqualWithEpsilon(pattern->GetColor(1)));
            Assert::IsTrue(pattern->GetTransform().IsEqualWithEpsilon(Matrix<4, 4>::Identity()));
        }

        TEST_METHOD(ColorAtWithObjectTransformation)
        {
            Sphere sphere;
            Material material = sphere.GetMaterial();
            material.SetPattern(std::make_unique<PatternMockup>(WhiteColor, BlackColor));
            sphere.SetMaterial(material);

            sphere.SetTransform(Transform::Scaling(2, 2, 2));

            const Vec3D color = sphere.GetColorAt(Vec3D(2, 3, 4));

            Assert::IsTrue(Vec3D(1, 1.5f, 2.f).IsEqualWithEpsilon(color));
        }

        TEST_METHOD(ColorAtWithObjectAndPatternTransformation)
        {
            Sphere sphere;
            Material material = sphere.GetMaterial();
            material.SetPattern(std::make_unique<PatternMockup>(WhiteColor, BlackColor));
            sphere.SetMaterial(material);
            sphere.GetMaterial().GetPattern()->SetTransform(Transform::Scaling(0.5f, 0.5f, 0.5f));

            sphere.SetTransform(Transform::Scaling(2, 2, 2));

            const Vec3D color = sphere.GetColorAt(Vec3D(2, 3, 4));

            Assert::IsTrue(Vec3D(2, 3, 4).IsEqualWithEpsilon(color));
        }

        TEST_METHOD(StripePatternIsConstantInY)
        {
            std::unique_ptr<Pattern> pattern = PatternFactory::Get()->Create(StripePatternType, WhiteColor, BlackColor);
            
            Assert::IsTrue(WhiteColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(0, 0, 0))));
            Assert::IsTrue(WhiteColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(0, 1, 0))));
            Assert::IsTrue(WhiteColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(0, 2, 0))));
        }

        TEST_METHOD(StripePatternIsConstantInZ)
        {
            std::unique_ptr<Pattern> pattern = PatternFactory::Get()->Create(StripePatternType, WhiteColor, BlackColor);

            Assert::IsTrue(WhiteColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(0, 0, 0))));
            Assert::IsTrue(WhiteColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(0, 0, 1))));
            Assert::IsTrue(WhiteColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(0, 0, 2))));
        }

        TEST_METHOD(StripePatternIsAlternatesInX)
        {
            std::unique_ptr<Pattern> pattern = PatternFactory::Get()->Create(StripePatternType, WhiteColor, BlackColor);

            Assert::IsTrue(WhiteColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(0, 0, 0))));
            Assert::IsTrue(WhiteColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(0.9f, 0, 0))));
            Assert::IsTrue(BlackColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(1, 0, 0))));
            Assert::IsTrue(BlackColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(-0.1f, 0, 0))));
            Assert::IsTrue(BlackColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(-1, 0, 0))));
            Assert::IsTrue(WhiteColor.IsEqualWithEpsilon(pattern->GetColorAt(Vec3D(-1.1f, 0, 0))));
        }
    };
}
