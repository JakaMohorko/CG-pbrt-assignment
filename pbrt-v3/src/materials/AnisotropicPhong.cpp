// materials/AnisotropicPhong.cpp*
#include "materials/AnisotropicPhong.h"
#include "spectrum.h"
#include "reflection.h"
#include "paramset.h"
#include "texture.h"
#include "interaction.h"

namespace pbrt {

// AnisotropicPhongMaterial Method Definitions
void AnisotropicPhongMaterial::ComputeScatteringFunctions(
    SurfaceInteraction *si, MemoryArena &arena, TransportMode mode,
    bool allowMultipleLobes) const {
    // Perform bump mapping with _bumpMap_, if present
    if (bumpMap) Bump(bumpMap, si);
    si->bsdf = ARENA_ALLOC(arena, BSDF)(*si);

    // Initialize anisotropic phong material
    Spectrum rd = Rd->Evaluate(*si).Clamp();
    Spectrum rs = Rs->Evaluate(*si).Clamp();
    Float nu = Nu->Evaluate(*si);
    Float nv = Nv->Evaluate(*si);
    Float cosineWeight = CosineWeight->Evaluate(*si);

    if (!(rd.IsBlack() && rs.IsBlack()))
        si->bsdf->Add(ARENA_ALLOC(arena, AnisotropicModel)(rd, rs, nu, nv, cosineWeight));
    if (!rd.IsBlack())
		si->bsdf->Add(ARENA_ALLOC(arena, LambertianReflection)(rd));

}

AnisotropicPhongMaterial *CreateAnisotropicPhongMaterial(
    const TextureParams &mp) {
    std::shared_ptr<Texture<Spectrum>> Rd =
        mp.GetSpectrumTexture("Rd", Spectrum(0.25f));
    std::shared_ptr<Texture<Spectrum>> Rs =
        mp.GetSpectrumTexture("Rs", Spectrum(0.25f));
    std::shared_ptr<Texture<Float>> bumpMap =
        mp.GetFloatTextureOrNull("bumpmap");
    std::shared_ptr<Texture<Float>> Nu = 
		mp.GetFloatTexture("nu", 10.f);
    std::shared_ptr<Texture<Float>> Nv = 
		mp.GetFloatTexture("nv", 10.f);
    std::shared_ptr<Texture<Float>> CosineWeight = 
		mp.GetFloatTexture("cosineweight", 0.5f);
    return new AnisotropicPhongMaterial(Rd, Rs, Nu, Nv, bumpMap, CosineWeight);
}

}  // namespace pbrt
