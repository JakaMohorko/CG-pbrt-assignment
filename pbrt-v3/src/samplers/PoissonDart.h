#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef PBRT_SAMPLERS_POISSONDART_H
#define PBRT_SAMPLERS_POISSONDART_H

// samplers/PoissonDart.h*
#include "sampler.h"
#include "rng.h"

namespace pbrt {

// PoissonDartSampler Declarations
class PoissonDartSampler : public PixelSampler {
  public:
    // PoissonDartSampler Public Methods
    PoissonDartSampler(int samples, Float radius,
                      int nSampledDimensions)
        : PixelSampler(samples, nSampledDimensions),
          samples(samples),
		  radius(radius){}
    void StartPixel(const Point2i &);
    std::unique_ptr<Sampler> Clone(int seed);

  private:
    // PoissonDartSampler Private Data
    const int samples;
    const Float radius;
};

PoissonDartSampler *CreatePoissonDartSampler(const ParamSet &params);

}  // namespace pbrt

#endif  // PBRT_SAMPLERS_POISSONDART_H
