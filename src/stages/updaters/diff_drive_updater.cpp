/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

// C++ Standard Library
#include <iostream>
#include <random>

// MCL
#include "mcl/stages/updaters/diff_drive_updater.h"

namespace mcl {
namespace stages {
namespace updaters {

DiffDriveUpdater::DiffDriveUpdater(const DiffDriveUpdaterParams& params) :
  params_(params),
  previous_stamp_(std::chrono::system_clock::now()) {}  // TODO(lucbettaieb): Probably should inject this in the PF call

void DiffDriveUpdater::update(ParticleArray::iterator begin,
                              ParticleArray::iterator end,
                              const mcl::Measurement& measurement) {
  // Probablistic Robotics p. 124, Table 5.3
  // Accidentally implemented the velocity model -- fix to diff drive / odometry p. 136 t5.6
  // Switch this to alternate class

  std::mt19937 gen(params_.seed);

  std::uniform_real_distribution<double> v_hat_dist(0, params_.alpha_1 * std::fabs(measurement.v) + params_.alpha_2 * std::fabs(measurement.w));
  std::uniform_real_distribution<double> w_hat_dist(0, params_.alpha_3 * std::fabs(measurement.v) + params_.alpha_4 * std::fabs(measurement.w));
  std::uniform_real_distribution<double> g_hat_dist(0, params_.alpha_5 * std::fabs(measurement.v) + params_.alpha_6 * std::fabs(measurement.w));

  const double v_hat = measurement.v + v_hat_dist(gen);
  const double w_hat = measurement.w + w_hat_dist(gen);
  const double g_hat = g_hat_dist(gen);

  const size_t dt_us = std::chrono::duration_cast<std::chrono::microseconds>(measurement.stamp - previous_stamp_).count();
  const double dt = static_cast<double>(dt_us) * static_cast<double>(10e-6);

  const double v_hat_on_w_hat = (v_hat / w_hat);
  const double w_hat_dt = (w_hat * dt);
  
  for (ParticleArray::iterator iter = begin; iter != end; ++iter) {
    mcl::Particle& p = *iter;

    p.state.x -= v_hat_on_w_hat * std::sin(p.state.theta) + v_hat_on_w_hat * std::sin(p.state.theta + w_hat_dt);
    p.state.y += v_hat_on_w_hat * std::cos(p.state.theta) - v_hat_on_w_hat * std::cos(p.state.theta + w_hat_dt);
    p.state.theta += w_hat_dt * g_hat * dt;
  }

  previous_stamp_ = measurement.stamp;
}

}  // namespace updaters
}  // namespace stages
}  // namespace mcl
