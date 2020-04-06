/**
 * Author: Luc Bettaieb, 2020
 * BSD-Licensed
 */

#ifndef MCL_DISTRIBUTOR_H
#define MCL_DISTRIBUTOR_H

#include "particles.h"

namespace mcl
{

class Distributor
{
public:
  explicit Distributor();

  virtual ~Distributor();

  virtual void distribute(ParticleArray::iterator begin, ParticleArray::iterator end) = 0;

};
}  // namespace mcl

#endif  // MCL_DISTRIBUTOR_H
