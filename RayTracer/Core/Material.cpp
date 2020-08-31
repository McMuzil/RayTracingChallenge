#include "Core/Material.h"

#include "Core/Pattern/Pattern.h"
#include "Helpers.h"

Material::Material()
{
}

Material::Material(const Material& other)
{
    *this = other;
}

Material::~Material()
{
}

void Material::SetPattern(std::unique_ptr<Pattern>&& val)
{
    m_pattern = std::move(val);
}

bool Material::operator==(const Material& other) const
{
    return Helpers::IsEqualWithEpsilon(m_ambient, other.m_ambient) &&
        Helpers::IsEqualWithEpsilon(m_diffuse, other.m_diffuse) &&
        Helpers::IsEqualWithEpsilon(m_specular, other.m_specular) &&
        Helpers::IsEqualWithEpsilon(m_shininess, other.m_shininess) &&
        Helpers::IsEqualWithEpsilon(m_reflectivity, other.m_reflectivity) &&
        Helpers::IsEqualWithEpsilon(m_transparency, other.m_transparency) &&
        Helpers::IsEqualWithEpsilon(m_refractiveIndex, other.m_refractiveIndex);
}

Material& Material::operator=(const Material& other)
{
    this->SetColor(other.GetColor());
    this->SetAmbient(other.GetAmbient());
    this->SetDiffuse(other.GetDiffuse());
    this->SetSpecular(other.GetSpecular());
    this->SetShininess(other.GetShininess());
    this->SetReflectivity(other.GetReflectivity());
    this->SetTransparency(other.GetTransparency());
    this->SetRefractiveIndex(other.GetRefractiveIndex());
    if (other.GetPattern())
    {
        this->SetPattern(Clone(other.GetPattern()));
    }

    return *this;
}
