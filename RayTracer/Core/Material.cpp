#include "Core/Material.h"

#include "Core/Pattern/Pattern.h"

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

Material& Material::operator=(const Material& other)
{
    this->SetColor(other.GetColor());
    this->SetAmbient(other.GetAmbient());
    this->SetDiffuse(other.GetDiffuse());
    this->SetSpecular(other.GetSpecular());
    this->SetShininess(other.GetShininess());
    if (other.GetPattern())
    {
        this->SetPattern(Clone(other.GetPattern()));
    }

    return *this;
}
