#include "Core/ObjectHelpers.h"
#include "Objects/Sphere.h"

namespace Helpers
{
    std::unique_ptr<Object> CreateGlassSphere()
    {
        std::unique_ptr<Object> sphere = std::make_unique<Sphere>();
        sphere->GetMaterial().SetTransparency(1.f);
        sphere->GetMaterial().SetRefractiveIndex(1.5f);

        return sphere;
    }
}
