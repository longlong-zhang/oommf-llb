/* FILE: uniaxialanisotropy.h            -*-Mode: c++-*-
 *
 * Uniaxial Anisotropy, derived from Oxs_Energy class.
 *
 */

#ifndef _KLM_LLB_TERM
#define _KLM_LLB_TERM

#include "nb.h"
//#include "threevector.h"
#include "util.h"
#include "chunkenergy.h"
#include "energy.h"
#include "key.h"
#include "simstate.h"
#include "mesh.h"
#include "meshvalue.h"
#include "oxsthread.h"
//#include "scalarfield.h"
//#include "vectorfield.h"

/* End includes */

class Klm_LLB_Term:public Oxs_ChunkEnergy {
private:
  // KL(m)
  OC_REAL8m chi_parallel; // Parallel susceptibility (units: 1)

protected:
  virtual void GetEnergy(const Oxs_SimState& state,
			 Oxs_EnergyData& oed) const {
    GetEnergyAlt(state,oed);
  }

  virtual void ComputeEnergy(const Oxs_SimState& state,
                             Oxs_ComputeEnergyData& oced) const {
    ComputeEnergyAlt(state,oced);
  }

  virtual void ComputeEnergyChunk(const Oxs_SimState& state,
                                  Oxs_ComputeEnergyDataThreaded& ocedt,
                                  Oxs_ComputeEnergyDataThreadedAux& ocedtaux,
                                  OC_INDEX node_start,OC_INDEX node_stop,
                                  int threadnumber) const;
public:
  virtual const char* ClassName() const; // ClassName() is
  /// automatically generated by the OXS_EXT_REGISTER macro.
  Klm_LLB_Term(const char* name,  // Child instance id
			 Oxs_Director* newdtr, // App director
			 const char* argstr);  // MIF input block parameters
  virtual ~Klm_LLB_Term() {}
  virtual OC_BOOL Init();
};


#endif // _KLM_LLB_TERM
