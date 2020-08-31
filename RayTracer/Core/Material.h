#pragma once
#include <sstream>

#include "Vector.h"

class Pattern;
class Material;

class Material
{
public:

    Material();
    Material(const Material& other);
    ~Material();

    Pattern* GetPattern() const { return m_pattern.get(); }
    void SetPattern(std::unique_ptr<Pattern>&& val);

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

    float GetTransparency() const { return m_transparency; }
    void SetTransparency(float val) { m_transparency = val; }

    float GetRefractiveIndex() const { return m_refractiveIndex; }
    void SetRefractiveIndex(float val) { m_refractiveIndex = val; }

    Material& operator=(const Material& other);

    bool operator==(const Material& other) const;

private:

    std::unique_ptr<Pattern> m_pattern = nullptr;
    Vec3D m_color = Vec3D(1.f);
    float m_ambient = 0.1f;
    float m_diffuse = 0.9f;
    float m_specular = 0.9f;
    float m_shininess = 200.f;
    float m_reflectivity = 0.f;
    float m_transparency = 0.f;
    float m_refractiveIndex = 1.f;
};
