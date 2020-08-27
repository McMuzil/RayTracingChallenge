#pragma once
#include <sstream>

#include "Helpers.h"
#include "Vector.h"

class Pattern;

class Material
{
public:

    Material();
    Material(const Material& other);
    ~Material();

    const Vec3D& GetColor() const { return m_color; }
    void SetColor(const Vec3D& val) { m_color = val; }

    float GetAmbient() const { return m_ambient; }
    void SetAmbient(float value) { m_ambient = value; }

    float GetDiffuse() const { return m_diffuse; }
    void SetDiffuse(float value) { m_diffuse = value; }

    float GetSpecular() const { return m_specular; }
    void SetSpecular(float value) { m_specular = value; }

    float GetShininess() const { return m_shininess; }
    void SetShininess(float value) { m_shininess = value; }

    float GetReflectivity() const { return m_reflectivity; }
    void SetReflectivity(float val) { m_reflectivity = val; }

    Pattern* GetPattern() const { return m_pattern.get(); }
    void SetPattern(std::unique_ptr<Pattern>&& val);

    Material& operator=(const Material& other);

    bool operator==(const Material& other) const
    {
        return Helpers::IsEqualWithEpsilon(m_ambient, other.m_ambient) &&
            Helpers::IsEqualWithEpsilon(m_diffuse, other.m_diffuse) &&
            Helpers::IsEqualWithEpsilon(m_specular, other.m_specular) &&
            Helpers::IsEqualWithEpsilon(m_shininess, other.m_shininess) &&
            Helpers::IsEqualWithEpsilon(m_reflectivity, other.m_reflectivity);
    }

private:

    std::unique_ptr<Pattern> m_pattern = nullptr;
    Vec3D m_color = Vec3D(1.f);
    float m_ambient = 0.1f;
    float m_diffuse = 0.9f;
    float m_specular = 0.9f;
    float m_shininess = 200.f;
    float m_reflectivity = 0.f;
};
