#include "pch.h"
#include "CppUnitTest.h"

#include "Core/Helpers.h"
#include "Core/Vector.h"
#include "Core/Canvas.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Core
{
    TEST_CLASS(CanvasTest)
    {
    public:

        TEST_METHOD(CreateCanvas)
        {
            Canvas canvas(10, 20);

            Assert::IsTrue(canvas.GetWidth() == 10u);
            Assert::IsTrue(canvas.GetHeight() == 20u);

            const Vec4D expectedPixelColor(0.f, 0.f, 0.f, 1.f);

            for (const Canvas::PixelRow& row : canvas.GetPixels())
            {
                for (const Vec4D& pixelColor : row)
                {
                    Assert::IsTrue(Vec4D::IsEqualWithEpsilon(pixelColor, expectedPixelColor));
                }
            }
        }

        TEST_METHOD(SetPixel)
        {
            Canvas canvas(10, 20);
            const Vec4D redColor = Vec4D(1.f, 0.f, 0.f, 1.f);
            canvas.SetPixel(redColor, 2, 3);

            Assert::IsTrue(Vec4D::IsEqualWithEpsilon(redColor, canvas.GetPixel(2, 3)));
        }

        TEST_METHOD(CanvasToPPM)
        {
            Canvas canvas(5, 3);

            canvas.SetPixel(Vec4D(1.5f, 0.f, 0.f), Vec2Du(0u, 0u));
            canvas.SetPixel(Vec4D(0.f, 0.5f, 0.f), Vec2Du(2u, 1u));
            canvas.SetPixel(Vec4D(-0.5f, 0.f, 1.f), Vec2Du(4u, 2u));

            const std::vector<std::string> expectedResult = {
                "P3",
                "5 3",
                "255",
                "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0",
                "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0",
                "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255",
            };

            std::stringstream ss(canvas.ToPPM());
            std::vector<std::string> outputVector;
            for (std::string line; std::getline(ss, line, '\n');)
            {
                outputVector.push_back(line);
            }

            Assert::AreEqual(expectedResult.size(), outputVector.size());

            for (size_t i = 0; i < expectedResult.size(); i++)
            {
                Assert::AreEqual(expectedResult[i], outputVector[i]);
            }
        }
    };
}
