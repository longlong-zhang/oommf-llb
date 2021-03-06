/* FILE: kl_timedriver.h            -*-Mode: c++-*-
 *
 * Example concrete Oxs_Driver class.
 * File based on origianl OOMMF code: timedriver.h
 * Added support for variable |M(r,t)| by Kristof Lebecki, nick KL(m),  
 * 2010, 2011, Universitšt Konstanz.
 *
 */

#ifndef _KLM_TIMEDRIVER
#define _KLM_TIMEDRIVER

#include <vector>

#include "simstate.h"
#include "key.h"
#include "driver.h"
#include "kl_timeevolvervarms.h" // KL(m)

OC_USE_STD_NAMESPACE;

/* End includes */

class Klm_TimeDriver:public Oxs_Driver {
private:
  Oxs_OwnedPointer<Klm_TimeEvolverVarMs> evolver_obj; // Evolver basket
  Oxs_Key<Klm_TimeEvolverVarMs> evolver_key;

  vector<OC_REAL8m> stopping_time;  // Seconds

  // KL(m)
  //vector<OC_REAL8m> stopping_dm_dt; // deg/ns
  vector<OC_REAL8m> stopping_dM_dt; //   A/m*s

  // KL(m)
  //Oxs_Output* max_dm_dt_obj_ptr; // Pointer to object providing
  Oxs_Output* max_dM_dt_obj_ptr; // Pointer to object providing
  /// max dM/dt data.  This is needed to determine StageDone events.

  // State-based outputs, maintained by the driver.  These are
  // conceptually public, but are specified private to force
  // clients to use the output_map interface in Oxs_Director.
#define OSO_DECL(name) \
void Fill__##name##_output(const Oxs_SimState&); \
Oxs_ScalarOutput<Klm_TimeDriver> name##_output
  OSO_DECL(last_timestep);
  OSO_DECL(simulation_time);
#undef OSO_DECL

  // Magnetization saturation for zero tmperature, T=0.
  /// You can also interpret it as second, reference magnetization.
  Oxs_MeshValue<OC_REAL8m> Ms_T0;

  // Initial magnetization
  Oxs_MeshValue<OC_REAL8m> Ms_initial;

  // Done checks, called by parent Oxs_Driver::IsStageDone and
  // Oxs_Driver::IsRunDone functions.
  virtual OC_BOOL ChildIsStageDone(const Oxs_SimState& state) const;
  virtual OC_BOOL ChildIsRunDone(const Oxs_SimState& state) const;

  // Disable copy constructor and assignment operator by declaring
  // them without defining them.
  Klm_TimeDriver(const Klm_TimeDriver&);
  Klm_TimeDriver& operator=(const Klm_TimeDriver&);

  // KL(m)
  // This method performs all constructor activities except
  // VerifyAllInitArgsUsed() - that will, or will not be run
  // from the constructor - see below
  void ConstructorBody();

public:
  Klm_TimeDriver(const char* name,     // Child instance id
                 Oxs_Director* newdtr, // App director
                 const char* argstr);  // MIF input block parameters

  virtual const char* ClassName() const; // ClassName() is
  /// automatically generated by the OXS_EXT_REGISTER macro.
  virtual OC_BOOL Init();
  virtual ~Klm_TimeDriver();

  virtual void StageRequestCount(unsigned int& min,
				 unsigned int& max) const;
  // Number of stages wanted by driver

  // Generic interface
  virtual Oxs_ConstKey<Oxs_SimState> GetInitialState() const;

  // Use FillState* and FillNewStageState* routines inherited from
  // parent.

  virtual OC_BOOL InitNewStage(Oxs_ConstKey<Oxs_SimState> state,
                            Oxs_ConstKey<Oxs_SimState> prevstate);

  virtual  OC_BOOL
  Step(Oxs_ConstKey<Oxs_SimState> current_state,
       const Oxs_DriverStepInfo& step_info,
       Oxs_ConstKey<Oxs_SimState>& next_state);
  // Returns true if step was successful, false if
  // unable to step as requested.

  // Time driver interface
  virtual void FillStateSupplemental(Oxs_SimState& work_state) const;
  /// FillStateSupplemental is called from time evolvers to adjust timestep.
};

#endif // _KLM_TIMEDRIVER
