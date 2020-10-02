#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef PBRT_SAMPLERS_POISSONRELAXATION_H
#define PBRT_SAMPLERS_POISSONRELAXATION_H

// samplers/PoissonDart.h*
#include "sampler.h"
#include "rng.h"

namespace pbrt {

// PoissonRelaxationSampler Declarations
class PoissonRelaxationSampler : public PixelSampler {
  public:
    // PoissonRelaxationSampler Public Methods
    PoissonRelaxationSampler(int samples, Float radius, Float decay,
                      int missThreshold, int nSampledDimensions)
        : PixelSampler(samples, nSampledDimensions),
          samples(samples),
          radius(radius),  
		  decay(decay),
		  missThreshold(missThreshold){}
    void StartPixel(const Point2i &);
    std::unique_ptr<Sampler> Clone(int seed);

  private:
    // PoissonRelaxationSampler Private Data
    const int samples;
    const Float radius;
    const Float decay;
    const int missThreshold;
};

PoissonRelaxationSampler *CreatePoissonRelaxationSampler(
    const ParamSet &params);

}  // namespace pbrt

#endif  // PBRT_SAMPLERS_POISSONRELAXATION_H
