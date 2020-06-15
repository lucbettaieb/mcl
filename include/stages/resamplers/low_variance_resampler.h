/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_STAGES_RESAMPLERS_LOW_VARIANCE_RESAMPLER
#define MCL_STAGES_RESAMPLERS_LOW_VARIANCE_RESAMPLER

namespace mcl {
namespace stages {
namespace extractors {

struct LowVarianceResamplerParams : public ResamplerParams {
  /**
   * @brief Constructor for the LowVarianceResamplerParams
   *
   * @param config  The YAML Node from which to load the configuration
   */
  LowVarianceResamplerParams(const YAML::Node& config) : ResamplerParams(config) {
  }
};

class LowVarianceResampler : public Extractor {
 public:
  /**
   * @brief Constructor for the LowVarianceResampler
   *
   * @param params  A parameter struct for the LowVarianceResampler
   */
  explicit LowVarianceResampler(const LowVarianceResamplerParams& params);

  /// Destructor for the LowVarianceResampler
  ~LowVarianceResampler() = default;

  /**
   * @brief Performs low variance resampling 
   *
   * @param begin  The beginning of the particle array
   * @param end  The end of the particle array
   */
  void resample(ParticleArray::iterator begin, ParticleArray::iterator end);

 private:
  /// Parameters for the low variance resampler
  LowVarianceResamplerParams params_;
};

}  // namespace extractors
}  // namespace stages
}  // namespace mcl

#endif  // MCL_STAGES_RESAMPLERS_LOW_VARIANCE_RESAMPLER
