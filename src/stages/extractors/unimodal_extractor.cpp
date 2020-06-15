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
  // TODO(enhancement): Use an iterator over the state in order to make it independent of the state's contents!

  double x_bar = 0.0;
  double y_bar = 0.0;
  double theta_bar = 0.0;

  double weight_sum = 0.0;

  for (ParticleArray::iterator it = begin; it != end; ++it) {
    x_bar += it->state.x * it->weight;
    y_bar += it->state.y * it->weight;
    theta_bar += it->state.theta * it->weight;

    weight_sum += it->weight;
  }

  x_bar /= weight_sum;
  y_bar /= weight_sum;
  theta_bar /= weight_sum;

  extracted_state->x = x_bar;
  extracted_state->y = y_bar;
  extracted_state->theta = theta_bar;
}

}  // namespace extractors
}  // namespace stages
}  // namespace mcl
