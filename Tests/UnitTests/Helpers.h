#pragma once

#include "Core/Material.h"
#include "CppUnitTestAssert.h"

namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template<>
            static std::wstring ToString<Material>(const Material& material)
            {
                std::wstringstream ss;

                ss << "Material(";
                ss << "Ambient: ";
                ss << material.GetAmbient();
                ss << ", Diffuse: ";
                ss << material.GetDiffuse();
                ss << ", Specular: ";
                ss << material.GetSpecular();
                ss << ", Shininess: ";
                ss << material.GetShininess();
                ss << ")";

                return ss.str();
            }
        }
    }
}