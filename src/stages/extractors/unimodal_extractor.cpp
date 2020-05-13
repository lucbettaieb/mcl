/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// MCL
#include "mcl/stages/extractors/unimodal_extractor.h"

namespace mcl {
namespace stages {
namespace extractors {

UnimodalExtractor::UnimodalExtractor(const UnimodalExtractorParams& params) : params_(params) {
}

void UnimodalExtractor::extract(ParticleArray::iterator begin,
                                ParticleArray::iterator end,
                                mcl::State* extracted_state) {

  double x_bar = 0.0;
  double y_bar = 0.0;
  double theta_bar = 0.0;

  for (ParticleArray::iterator it = begin; it != end; ++it) {
    x_bar += it->state.x;
    y_bar += it->state.y;
    theta_bar += it->state.theta;
    
  }

}

}  // namespace extractors
}  // namespace stages
}  // namespace mcl
