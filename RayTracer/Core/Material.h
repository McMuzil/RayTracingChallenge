#pragma once
#include "Helpers.h"
#include <sstream>

class Material
{
public:

    float GetAmbient() const { return m_ambient; }
    void SetAmbient(float value) { m_ambient = value; }

    float GetDiffuse() const { return m_diffuse; }
    void SetDiffuse(float value) { m_diffuse = value; }

    float GetSpecular() const { return m_specular; }
    void SetSpecular(float value) { m_specular = value; }

    float GetShininess() const { return m_shininess; }
    void SetShininess(float value) { m_shininess = value; }

    bool operator==(const Material& other) const
    {
        return Helpers::IsEqualWithEpsilon(m_ambient, other.m_ambient) &&
            Helpers::IsEqualWithEpsilon(m_diffuse, other.m_diffuse) &&
            Helpers::IsEqualWithEpsilon(m_specular, other.m_specular) &&
            Helpers::IsEqualWithEpsilon(m_shininess, other.m_shininess);
    }

private:

    float m_ambient = 0.1f;
    float m_diffuse = 0.9f;
    float m_specular = 0.9f;
    float m_shininess = 200.f;
};
