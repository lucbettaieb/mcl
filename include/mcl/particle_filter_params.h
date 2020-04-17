/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_PARTICLE_FILTER_PARAMS_H
#define MCL_PARTICLE_FILTER_PARAMS_H

// C++ Standard Library
#include <string>
#include <unordered_map>

// YAML
#include <yaml-cpp/yaml.h>

namespace mcl {
/**
 * @brief Parameters for the particle filter
 */
struct ParticleFilterParams {
  ParticleFilterParams(const YAML::Node& config)
      : distributor_type_(distributor_str_to_enum.at(config["distributor_type"].as<std::string>())),
        updater_type_(updater_str_to_enum.at(config["updater_type"].as<std::string>())),
        scorer_type_(scorer_str_to_enum.at(config["scorer_type"].as<std::string>())),
        resampler_type_(resampler_str_to_enum.at(config["resampler_type"].as<std::string>())),
        pose_extractor_type_(pose_extractor_str_to_enum.at(config["pose_extractor_type"].as<std::string>())) {
  }

 private:
  /// An enumerated type to allow for static typing of the distributor type
  enum DistributorType { DISTRIBUTOR_GAUSSIAN = 0 };

  /// An unordered map to convert a string to an enumerated type
  const std::unordered_map<std::string, DistributorType> distributor_str_to_enum{
      {"DISTRIBUTOR_GAUSSIAN", DistributorType::DISTRIBUTOR_GAUSSIAN}};

  /// An enumerated type to allow for static typing of the updater type
  enum UpdaterType { UPDATER_DIFF_DRIVE = 0, UPDATER_ACKERMANN = 1 };

  /// An unordered map to convert a string to an enumerated type
  const std::unordered_map<std::string, UpdaterType> updater_str_to_enum{
      {"UPDATER_DIFF_DRIVE", UpdaterType::UPDATER_DIFF_DRIVE}, {"UPDATER_ACKERMANN", UpdaterType::UPDATER_ACKERMANN}};

  /// An enumerated type to allow for static typing of the scorer type
  enum ScorerType { SCORER_LIKELIHOOD_FIELD = 0 };

  /// An unordered map to convert a string to an enumerated type
  const std::unordered_map<std::string, ScorerType> scorer_str_to_enum{
      {"SCORER_LIKELIHOOD_FIELD", ScorerType::SCORER_LIKELIHOOD_FIELD}};

  /// An enumerated type to allow for static typing of the resampler type
  enum ResamplerType { RESAMPLER_LOW_VARIANCE = 0 };

  /// An unordered map to convert a string to an enumerated type
  const std::unordered_map<std::string, ResamplerType> resampler_str_to_enum{
      {"RESAMPLER_LOW_VARIANCE", ResamplerType::RESAMPLER_LOW_VARIANCE}};

  /// An enumerated type to allow for static typing of the pose extractor type
  enum PoseExtractorType { POSE_EXTRACTOR_WEIGHTED_MEAN = 0 };

  /// An unordered map to convert a string to an enumerated type
  const std::unordered_map<std::string, PoseExtractorType> pose_extractor_str_to_enum{
      {"POSE_EXTRACTOR_WEIGHTED_MEAN", PoseExtractorType::POSE_EXTRACTOR_WEIGHTED_MEAN}};

  /// The type of distributor to use in the particle filter
  const DistributorType distributor_type_;

  /// The type of updater to use in the particle filter
  const UpdaterType updater_type_;

  /// The type of scorer to use in the particle filter
  const ScorerType scorer_type_;

  /// The type of resampler to use in the particle filter
  const ResamplerType resampler_type_;

  /// The type of pose extrator  to use in the particle filter
  const PoseExtractorType pose_extractor_type_;
};

}  // namespace mcl

#endif  // MCL_PARTICLE_FILTER_PARAMS_H
