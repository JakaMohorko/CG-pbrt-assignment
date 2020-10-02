
// samplers/PoissonDart.cpp*
#include "samplers/PoissonDart.h"
#include "paramset.h"
#include "sampling.h"
#include "stats.h"

namespace pbrt {

// StratifiedSampler Method Definitions
void PoissonDartSampler::StartPixel(const Point2i &p) {
    ProfilePhase _(Prof::StartPixel);
    // Generate single poisson samples for the pixel
    for (size_t i = 0; i < samples1D.size(); ++i) {
        PoissonDartSample1D(&samples1D[i][0], samples, radius, rng);
    }
    for (size_t i = 0; i < samples2D.size(); ++i) {
        PoissonDartSample2D(&samples2D[i][0], samples, radius, rng);
    }

    // Generate arrays of poisson samples for the pixel
    for (size_t i = 0; i < samples1DArraySizes.size(); ++i)
        for (int64_t j = 0; j < samplesPerPixel; ++j) {
            int count = samples1DArraySizes[i];
            PoissonDartSample1D(&sampleArray1D[i][j * count], count, radius, rng);
        }
    for (size_t i = 0; i < samples2DArraySizes.size(); ++i)
        for (int64_t j = 0; j < samplesPerPixel; ++j) {
            int count = samples2DArraySizes[i];
            PoissonDartSample2D(&sampleArray2D[i][j * count], count, radius, rng);
        }
    PixelSampler::StartPixel(p);
}

std::unique_ptr<Sampler> PoissonDartSampler::Clone(int seed) {
    PoissonDartSampler *ss = new PoissonDartSampler(*this);
    ss->rng.SetSequence(seed);
    return std::unique_ptr<Sampler>(ss);
}

PoissonDartSampler *CreatePoissonDartSampler(const ParamSet &params) {
    int samples = params.FindOneInt("pixelsamples", 16);
    Float radius = params.FindOneFloat("radius", 0.04);
    int sd = params.FindOneInt("dimensions", 4);
    if (PbrtOptions.quickRender) samples = 1;
    return new PoissonDartSampler(samples, radius, sd);
}

}  // namespace pbrt
