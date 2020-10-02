
// samplers/PoissonRelaxation.cpp*
#include "samplers/PoissonRelaxation.h"
#include "paramset.h"
#include "sampling.h"
#include "stats.h"

namespace pbrt {

// PoissonRelaxationSampler Method Definitions
void PoissonRelaxationSampler::StartPixel(const Point2i &p) {
    ProfilePhase _(Prof::StartPixel);
    // Generate single poisson samples for the pixel
    for (size_t i = 0; i < samples1D.size(); ++i) {
        PoissonRelaxationSample1D(&samples1D[i][0], samples, radius, decay, 
								      missThreshold, rng);
    }
    for (size_t i = 0; i < samples2D.size(); ++i) {
        PoissonRelaxationSample2D(&samples2D[i][0], samples, radius, decay, 
									  missThreshold, rng);
    }

    // Generate arrays of poisson samples for the pixel
    for (size_t i = 0; i < samples1DArraySizes.size(); ++i)
        for (int64_t j = 0; j < samplesPerPixel; ++j) {
            int count = samples1DArraySizes[i];
            PoissonRelaxationSample1D(&sampleArray1D[i][j * count], count,
                                      radius, decay, missThreshold, rng);
        }
    for (size_t i = 0; i < samples2DArraySizes.size(); ++i)
        for (int64_t j = 0; j < samplesPerPixel; ++j) {
            int count = samples2DArraySizes[i];
            PoissonRelaxationSample2D(&sampleArray2D[i][j * count], count,
                                      radius, decay, missThreshold, rng);
        }
    PixelSampler::StartPixel(p);
}

std::unique_ptr<Sampler> PoissonRelaxationSampler::Clone(int seed) {
    PoissonRelaxationSampler *ss = new PoissonRelaxationSampler(*this);
    ss->rng.SetSequence(seed);
    return std::unique_ptr<Sampler>(ss);
}

PoissonRelaxationSampler *CreatePoissonRelaxationSampler(
    const ParamSet &params) {
    int samples = params.FindOneInt("pixelsamples", 16);
    Float radius = params.FindOneFloat("radius", 0.15);
    Float decay = params.FindOneFloat("decay", 0.99);
    int missThreshold = params.FindOneInt("missthreshold", 1000);
    int sd = params.FindOneInt("dimensions", 4);
    if (PbrtOptions.quickRender) samples = 1;
    return new PoissonRelaxationSampler(samples, radius, decay, missThreshold,
                                         sd);
}

}  // namespace pbrt
