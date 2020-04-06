/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#include "mcl/particle_filter.h"

int main(int argc, char const *argv[])
{
  YAML::Node config = YAML::LoadFile(argv[1]);

  mcl::ParticleFilter pf_{config};

  return 0;
}
