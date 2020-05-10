/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_EXTRACTORS_UNIMODAL_EXTRACTOR
#define MCL_STAGES_EXTRACTORS_UNIMODAL_EXTRACTOR

// C++ Standard Library
#include <chrono>
#include <memory>
#include <random>

// YAML
#include <yaml-cpp/yaml.h>

// MCL
#include "mcl/particles.h"
#include "mcl/stages/extractor.h"

namespace mcl {
namespace stages {
namespace extractors {

struct UnimodalExtractorParams : public ExtractorParams {
  /**
   * @brief Constructor for the UnimodalExtractorParams
   *
   * @param config  The YAML Node from which to load the configuration
   */
  UnimodalExtractorParams(const YAML::Node& config) : ExtractorParams(config) {
  }
};

class UnimodalExtractor : public Extractor {
 public:
  /**
   * @brief Constructor for the UnimodalExtractor
   *
   * @param params  A parameter struct for the UnimodalExtractor
   */
  explicit UnimodalExtractor(const UnimodalExtractorParams& params);

  /// Destructor for the UnimodalExtractor
  ~UnimodalExtractor() = default;

  /**
   * @brief Extracts the state from the distribution.  This extractor does this by assuming the distribution is unimodal
   *        and calculating the weighted mean.  The weighted mean is then assumed to be the resultant state.
   * 
   * @param begin  The beginning of the particle array
   * @param end  The end of the particle array
   * @param[out] extracted_state  The extracted state from the distribution
   */
  void extract(ParticleArray::iterator begin, ParticleArray::iterator end, mcl::State* extracted_state);

 private:

};

}  // namespace extractors
}  // namespace stages
}  // namespace mcl

#endif  // MCL_STAGES_EXTRACTORS_UNIMODAL_EXTRACTOR
