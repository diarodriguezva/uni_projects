/* Include files */

#include <stddef.h>
#include "blas.h"
#include "m3dof_library_sfun.h"
#include "c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "m3dof_library_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c10_xTRDt0LbA83zt2EbCc5TbB_debug_family_names[41] = {
  "CORIOLIS", "qp", "t1", "t2", "t3", "t5", "t6", "t7", "t8", "t9", "t11", "t12",
  "t13", "t14", "t16", "t17", "t19", "t20", "t21", "t22", "t23", "t25", "t26",
  "t27", "t28", "t29", "t30", "t31", "t32", "t33", "i", "j", "nargin", "nargout",
  "q", "q_dot", "xi1", "xi2", "xi3", "a", "C" };

/* Function Declarations */
static void initialize_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance);
static void initialize_params_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance);
static void enable_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance);
static void disable_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance);
static void c10_xTRDt0LbA83zt2EbCc5TbB_update_debugger_state_c10_xTRDt0LbA83
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance);
static void set_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_st);
static void finalize_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance);
static void sf_gateway_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance);
static void c10_xTRDt0LbA83zt2EbCc5TbB_chartstep_c10_xTRDt0LbA83zt2EbCc5TbB_
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance);
static void initSimStructsc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T
  c10_xTRDt0LbA83zt2EbCc5TbB_machineNumber, uint32_T
  c10_xTRDt0LbA83zt2EbCc5TbB_chartNumber, uint32_T
  c10_xTRDt0LbA83zt2EbCc5TbB_instanceNumber);
static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_sf_marshallOut(void
  *chartInstanceVoid, void *c10_xTRDt0LbA83zt2EbCc5TbB_inData);
static void c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_C, const char_T
   *c10_xTRDt0LbA83zt2EbCc5TbB_identifier, real_T c10_xTRDt0LbA83zt2EbCc5TbB_y[9]);
static void c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_u, const emlrtMsgIdentifier
   *c10_xTRDt0LbA83zt2EbCc5TbB_parentId, real_T c10_xTRDt0LbA83zt2EbCc5TbB_y[9]);
static void c10_xTRDt0LbA83zt2EbCc5TbB_sf_marshallIn(void *chartInstanceVoid,
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData, const char_T
  *c10_xTRDt0LbA83zt2EbCc5TbB_varName, void *c10_xTRDt0LbA83zt2EbCc5TbB_outData);
static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut(void
  *chartInstanceVoid, void *c10_xTRDt0LbA83zt2EbCc5TbB_inData);
static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut(void
  *chartInstanceVoid, void *c10_xTRDt0LbA83zt2EbCc5TbB_inData);
static real_T c10_xTRDt0LbA83zt2EbCc5TbB_c_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_u, const emlrtMsgIdentifier
   *c10_xTRDt0LbA83zt2EbCc5TbB_parentId);
static void c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn(void *chartInstanceVoid,
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData, const char_T
  *c10_xTRDt0LbA83zt2EbCc5TbB_varName, void *c10_xTRDt0LbA83zt2EbCc5TbB_outData);
static void c10_xTRDt0LbA83zt2EbCc5TbB_d_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_u, const emlrtMsgIdentifier
   *c10_xTRDt0LbA83zt2EbCc5TbB_parentId, real_T c10_xTRDt0LbA83zt2EbCc5TbB_y[3]);
static void c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallIn(void *chartInstanceVoid,
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData, const char_T
  *c10_xTRDt0LbA83zt2EbCc5TbB_varName, void *c10_xTRDt0LbA83zt2EbCc5TbB_outData);
static void c10_xTRDt0LbA83zt2EbCc5TbB_info_helper(const mxArray
  **c10_xTRDt0LbA83zt2EbCc5TbB_info);
static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut(const char
  * c10_xTRDt0LbA83zt2EbCc5TbB_u);
static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(const
  uint32_T c10_xTRDt0LbA83zt2EbCc5TbB_u);
static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_d_sf_marshallOut(void
  *chartInstanceVoid, void *c10_xTRDt0LbA83zt2EbCc5TbB_inData);
static int32_T c10_xTRDt0LbA83zt2EbCc5TbB_e_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_u, const emlrtMsgIdentifier
   *c10_xTRDt0LbA83zt2EbCc5TbB_parentId);
static void c10_xTRDt0LbA83zt2EbCc5TbB_d_sf_marshallIn(void *chartInstanceVoid,
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData, const char_T
  *c10_xTRDt0LbA83zt2EbCc5TbB_varName, void *c10_xTRDt0LbA83zt2EbCc5TbB_outData);
static uint8_T c10_xTRDt0LbA83zt2EbCc5TbB_f_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray
   *c10_xTRDt0LbA83zt2EbCc5TbB_b_is_active_c10_xTRDt0LbA83zt2EbCc5Tb, const
   char_T *c10_xTRDt0LbA83zt2EbCc5TbB_identifier);
static uint8_T c10_xTRDt0LbA83zt2EbCc5TbB_g_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_u, const emlrtMsgIdentifier
   *c10_xTRDt0LbA83zt2EbCc5TbB_parentId);
static void init_dsm_address_info
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance)
{
  chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_is_active_c10_xTRDt0LbA83zt2EbCc5TbB_
    = 0U;
}

static void initialize_params_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c10_xTRDt0LbA83zt2EbCc5TbB_update_debugger_state_c10_xTRDt0LbA83
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_st;
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i0;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_u[9];
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_b_y = NULL;
  uint8_T c10_xTRDt0LbA83zt2EbCc5TbB_hoistedGlobal;
  uint8_T c10_xTRDt0LbA83zt2EbCc5TbB_b_u;
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_c_y = NULL;
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_C)[9];
  c10_xTRDt0LbA83zt2EbCc5TbB_C = (real_T (*)[9])ssGetOutputPortSignal
    (chartInstance->S, 1);
  c10_xTRDt0LbA83zt2EbCc5TbB_st = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_st = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_y, sf_mex_createcellmatrix(2, 1),
                false);
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i0 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i0 < 9;
       c10_xTRDt0LbA83zt2EbCc5TbB_i0++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_u[c10_xTRDt0LbA83zt2EbCc5TbB_i0] =
      (*c10_xTRDt0LbA83zt2EbCc5TbB_C)[c10_xTRDt0LbA83zt2EbCc5TbB_i0];
  }

  c10_xTRDt0LbA83zt2EbCc5TbB_b_y = NULL;
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_b_y, sf_mex_create("y",
    c10_xTRDt0LbA83zt2EbCc5TbB_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_setcell(c10_xTRDt0LbA83zt2EbCc5TbB_y, 0, c10_xTRDt0LbA83zt2EbCc5TbB_b_y);
  c10_xTRDt0LbA83zt2EbCc5TbB_hoistedGlobal =
    chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_is_active_c10_xTRDt0LbA83zt2EbCc5TbB_;
  c10_xTRDt0LbA83zt2EbCc5TbB_b_u = c10_xTRDt0LbA83zt2EbCc5TbB_hoistedGlobal;
  c10_xTRDt0LbA83zt2EbCc5TbB_c_y = NULL;
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_c_y, sf_mex_create("y",
    &c10_xTRDt0LbA83zt2EbCc5TbB_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c10_xTRDt0LbA83zt2EbCc5TbB_y, 1, c10_xTRDt0LbA83zt2EbCc5TbB_c_y);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_st, c10_xTRDt0LbA83zt2EbCc5TbB_y,
                false);
  return c10_xTRDt0LbA83zt2EbCc5TbB_st;
}

static void set_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_st)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_u;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_dv0[9];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i1;
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_C)[9];
  c10_xTRDt0LbA83zt2EbCc5TbB_C = (real_T (*)[9])ssGetOutputPortSignal
    (chartInstance->S, 1);
  chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_doneDoubleBufferReInit = true;
  c10_xTRDt0LbA83zt2EbCc5TbB_u = sf_mex_dup(c10_xTRDt0LbA83zt2EbCc5TbB_st);
  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c10_xTRDt0LbA83zt2EbCc5TbB_u, 0)), "C",
    c10_xTRDt0LbA83zt2EbCc5TbB_dv0);
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i1 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i1 < 9;
       c10_xTRDt0LbA83zt2EbCc5TbB_i1++) {
    (*c10_xTRDt0LbA83zt2EbCc5TbB_C)[c10_xTRDt0LbA83zt2EbCc5TbB_i1] =
      c10_xTRDt0LbA83zt2EbCc5TbB_dv0[c10_xTRDt0LbA83zt2EbCc5TbB_i1];
  }

  chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_is_active_c10_xTRDt0LbA83zt2EbCc5TbB_
    = c10_xTRDt0LbA83zt2EbCc5TbB_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c10_xTRDt0LbA83zt2EbCc5TbB_u, 1)),
    "is_active_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library");
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_u);
  c10_xTRDt0LbA83zt2EbCc5TbB_update_debugger_state_c10_xTRDt0LbA83(chartInstance);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_st);
}

static void finalize_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance)
{
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i2;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i3;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i4;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i5;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i6;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i7;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i8;
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_a)[3];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_xi3)[3];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_xi2)[3];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_C)[9];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_xi1)[3];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_q_dot)[3];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_q)[3];
  c10_xTRDt0LbA83zt2EbCc5TbB_a = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 5);
  c10_xTRDt0LbA83zt2EbCc5TbB_xi3 = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 4);
  c10_xTRDt0LbA83zt2EbCc5TbB_xi2 = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 3);
  c10_xTRDt0LbA83zt2EbCc5TbB_C = (real_T (*)[9])ssGetOutputPortSignal
    (chartInstance->S, 1);
  c10_xTRDt0LbA83zt2EbCc5TbB_xi1 = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 2);
  c10_xTRDt0LbA83zt2EbCc5TbB_q_dot = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 1);
  c10_xTRDt0LbA83zt2EbCc5TbB_q = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U,
               chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent);
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i2 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i2 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i2++) {
    _SFD_DATA_RANGE_CHECK((*c10_xTRDt0LbA83zt2EbCc5TbB_q)
                          [c10_xTRDt0LbA83zt2EbCc5TbB_i2], 0U);
  }

  for (c10_xTRDt0LbA83zt2EbCc5TbB_i3 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i3 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i3++) {
    _SFD_DATA_RANGE_CHECK((*c10_xTRDt0LbA83zt2EbCc5TbB_q_dot)
                          [c10_xTRDt0LbA83zt2EbCc5TbB_i3], 1U);
  }

  for (c10_xTRDt0LbA83zt2EbCc5TbB_i4 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i4 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i4++) {
    _SFD_DATA_RANGE_CHECK((*c10_xTRDt0LbA83zt2EbCc5TbB_xi1)
                          [c10_xTRDt0LbA83zt2EbCc5TbB_i4], 2U);
  }

  chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent = CALL_EVENT;
  c10_xTRDt0LbA83zt2EbCc5TbB_chartstep_c10_xTRDt0LbA83zt2EbCc5TbB_(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_m3dof_libraryMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i5 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i5 < 9;
       c10_xTRDt0LbA83zt2EbCc5TbB_i5++) {
    _SFD_DATA_RANGE_CHECK((*c10_xTRDt0LbA83zt2EbCc5TbB_C)
                          [c10_xTRDt0LbA83zt2EbCc5TbB_i5], 3U);
  }

  for (c10_xTRDt0LbA83zt2EbCc5TbB_i6 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i6 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i6++) {
    _SFD_DATA_RANGE_CHECK((*c10_xTRDt0LbA83zt2EbCc5TbB_xi2)
                          [c10_xTRDt0LbA83zt2EbCc5TbB_i6], 4U);
  }

  for (c10_xTRDt0LbA83zt2EbCc5TbB_i7 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i7 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i7++) {
    _SFD_DATA_RANGE_CHECK((*c10_xTRDt0LbA83zt2EbCc5TbB_xi3)
                          [c10_xTRDt0LbA83zt2EbCc5TbB_i7], 5U);
  }

  for (c10_xTRDt0LbA83zt2EbCc5TbB_i8 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i8 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i8++) {
    _SFD_DATA_RANGE_CHECK((*c10_xTRDt0LbA83zt2EbCc5TbB_a)
                          [c10_xTRDt0LbA83zt2EbCc5TbB_i8], 6U);
  }
}

static void c10_xTRDt0LbA83zt2EbCc5TbB_chartstep_c10_xTRDt0LbA83zt2EbCc5TbB_
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance)
{
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i9;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_q[3];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i10;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_q_dot[3];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i11;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_xi1[3];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i12;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_xi2[3];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i13;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_xi3[3];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i14;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_a[3];
  uint32_T c10_xTRDt0LbA83zt2EbCc5TbB_debug_family_var_map[41];
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[9];
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_qp[3];
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t1;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t2;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t3;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t5;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t6;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t7;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t8;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t9;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t11;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t12;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t13;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t14;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t16;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t17;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t19;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t20;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t21;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t22;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t23;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t25;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t26;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t27;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t28;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t29;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t30;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t31;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t32;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_t33;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_i;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_j;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_nargin = 6.0;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_nargout = 1.0;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_C[9];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i15;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i16;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i17;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_x;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_b_x;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_c_x;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_d_x;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_e_x;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_f_x;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_g_x;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_h_x;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_b_i;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_b_j;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i18;
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_b_C)[9];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_b_a)[3];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_b_xi3)[3];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_b_xi2)[3];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_b_xi1)[3];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_b_q_dot)[3];
  real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_b_q)[3];
  c10_xTRDt0LbA83zt2EbCc5TbB_b_a = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 5);
  c10_xTRDt0LbA83zt2EbCc5TbB_b_xi3 = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 4);
  c10_xTRDt0LbA83zt2EbCc5TbB_b_xi2 = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 3);
  c10_xTRDt0LbA83zt2EbCc5TbB_b_C = (real_T (*)[9])ssGetOutputPortSignal
    (chartInstance->S, 1);
  c10_xTRDt0LbA83zt2EbCc5TbB_b_xi1 = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 2);
  c10_xTRDt0LbA83zt2EbCc5TbB_b_q_dot = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 1);
  c10_xTRDt0LbA83zt2EbCc5TbB_b_q = (real_T (*)[3])ssGetInputPortSignal
    (chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U,
               chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent);
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i9 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i9 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i9++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_q[c10_xTRDt0LbA83zt2EbCc5TbB_i9] =
      (*c10_xTRDt0LbA83zt2EbCc5TbB_b_q)[c10_xTRDt0LbA83zt2EbCc5TbB_i9];
  }

  for (c10_xTRDt0LbA83zt2EbCc5TbB_i10 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i10 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i10++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_q_dot[c10_xTRDt0LbA83zt2EbCc5TbB_i10] =
      (*c10_xTRDt0LbA83zt2EbCc5TbB_b_q_dot)[c10_xTRDt0LbA83zt2EbCc5TbB_i10];
  }

  for (c10_xTRDt0LbA83zt2EbCc5TbB_i11 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i11 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i11++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_xi1[c10_xTRDt0LbA83zt2EbCc5TbB_i11] =
      (*c10_xTRDt0LbA83zt2EbCc5TbB_b_xi1)[c10_xTRDt0LbA83zt2EbCc5TbB_i11];
  }

  for (c10_xTRDt0LbA83zt2EbCc5TbB_i12 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i12 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i12++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_xi2[c10_xTRDt0LbA83zt2EbCc5TbB_i12] =
      (*c10_xTRDt0LbA83zt2EbCc5TbB_b_xi2)[c10_xTRDt0LbA83zt2EbCc5TbB_i12];
  }

  for (c10_xTRDt0LbA83zt2EbCc5TbB_i13 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i13 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i13++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_xi3[c10_xTRDt0LbA83zt2EbCc5TbB_i13] =
      (*c10_xTRDt0LbA83zt2EbCc5TbB_b_xi3)[c10_xTRDt0LbA83zt2EbCc5TbB_i13];
  }

  for (c10_xTRDt0LbA83zt2EbCc5TbB_i14 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i14 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i14++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_a[c10_xTRDt0LbA83zt2EbCc5TbB_i14] =
      (*c10_xTRDt0LbA83zt2EbCc5TbB_b_a)[c10_xTRDt0LbA83zt2EbCc5TbB_i14];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 41U, 41U,
    c10_xTRDt0LbA83zt2EbCc5TbB_debug_family_names,
    c10_xTRDt0LbA83zt2EbCc5TbB_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS, 0U,
    c10_xTRDt0LbA83zt2EbCc5TbB_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_xTRDt0LbA83zt2EbCc5TbB_qp, 1U,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t1, 2U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t2, 3U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t3, 4U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t5, 5U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t6, 6U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t7, 7U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t8, 8U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t9, 9U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t11, 10U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t12, 11U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t13, 12U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t14, 13U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t16, 14U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t17, 15U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t19, 16U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t20, 17U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t21, 18U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t22, 19U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t23, 20U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t25, 21U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t26, 22U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t27, 23U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t28, 24U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t29, 25U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t30, 26U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t31, 27U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t32, 28U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_t33, 29U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_i, 30U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_j, 31U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_nargin, 32U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c10_xTRDt0LbA83zt2EbCc5TbB_nargout, 33U,
    c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_xTRDt0LbA83zt2EbCc5TbB_q, 34U,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_xTRDt0LbA83zt2EbCc5TbB_q_dot, 35U,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_xTRDt0LbA83zt2EbCc5TbB_xi1, 36U,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_xTRDt0LbA83zt2EbCc5TbB_xi2, 37U,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_xTRDt0LbA83zt2EbCc5TbB_xi3, 38U,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c10_xTRDt0LbA83zt2EbCc5TbB_a, 39U,
    c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c10_xTRDt0LbA83zt2EbCc5TbB_C, 40U,
    c10_xTRDt0LbA83zt2EbCc5TbB_sf_marshallOut,
    c10_xTRDt0LbA83zt2EbCc5TbB_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 4);
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i15 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i15 < 9;
       c10_xTRDt0LbA83zt2EbCc5TbB_i15++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_C[c10_xTRDt0LbA83zt2EbCc5TbB_i15] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 5);
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i16 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i16 < 9;
       c10_xTRDt0LbA83zt2EbCc5TbB_i16++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[c10_xTRDt0LbA83zt2EbCc5TbB_i16] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 9);
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i17 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i17 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i17++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_qp[c10_xTRDt0LbA83zt2EbCc5TbB_i17] =
      c10_xTRDt0LbA83zt2EbCc5TbB_q_dot[c10_xTRDt0LbA83zt2EbCc5TbB_i17];
  }

  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 10);
  c10_xTRDt0LbA83zt2EbCc5TbB_x = c10_xTRDt0LbA83zt2EbCc5TbB_q[2];
  c10_xTRDt0LbA83zt2EbCc5TbB_t1 = c10_xTRDt0LbA83zt2EbCc5TbB_x;
  c10_xTRDt0LbA83zt2EbCc5TbB_b_x = c10_xTRDt0LbA83zt2EbCc5TbB_t1;
  c10_xTRDt0LbA83zt2EbCc5TbB_t1 = c10_xTRDt0LbA83zt2EbCc5TbB_b_x;
  c10_xTRDt0LbA83zt2EbCc5TbB_t1 = muDoubleScalarCos
    (c10_xTRDt0LbA83zt2EbCc5TbB_t1);
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 11);
  c10_xTRDt0LbA83zt2EbCc5TbB_c_x = c10_xTRDt0LbA83zt2EbCc5TbB_q[1];
  c10_xTRDt0LbA83zt2EbCc5TbB_t2 = c10_xTRDt0LbA83zt2EbCc5TbB_c_x;
  c10_xTRDt0LbA83zt2EbCc5TbB_d_x = c10_xTRDt0LbA83zt2EbCc5TbB_t2;
  c10_xTRDt0LbA83zt2EbCc5TbB_t2 = c10_xTRDt0LbA83zt2EbCc5TbB_d_x;
  c10_xTRDt0LbA83zt2EbCc5TbB_t2 = muDoubleScalarSin
    (c10_xTRDt0LbA83zt2EbCc5TbB_t2);
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 12);
  c10_xTRDt0LbA83zt2EbCc5TbB_t3 = c10_xTRDt0LbA83zt2EbCc5TbB_t1 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t2;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 13);
  c10_xTRDt0LbA83zt2EbCc5TbB_t5 = c10_xTRDt0LbA83zt2EbCc5TbB_qp[1] *
    c10_xTRDt0LbA83zt2EbCc5TbB_a[0] * c10_xTRDt0LbA83zt2EbCc5TbB_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 14);
  c10_xTRDt0LbA83zt2EbCc5TbB_t6 = c10_xTRDt0LbA83zt2EbCc5TbB_t3 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t5;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 15);
  c10_xTRDt0LbA83zt2EbCc5TbB_e_x = c10_xTRDt0LbA83zt2EbCc5TbB_q[2];
  c10_xTRDt0LbA83zt2EbCc5TbB_t7 = c10_xTRDt0LbA83zt2EbCc5TbB_e_x;
  c10_xTRDt0LbA83zt2EbCc5TbB_f_x = c10_xTRDt0LbA83zt2EbCc5TbB_t7;
  c10_xTRDt0LbA83zt2EbCc5TbB_t7 = c10_xTRDt0LbA83zt2EbCc5TbB_f_x;
  c10_xTRDt0LbA83zt2EbCc5TbB_t7 = muDoubleScalarSin
    (c10_xTRDt0LbA83zt2EbCc5TbB_t7);
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 16);
  c10_xTRDt0LbA83zt2EbCc5TbB_g_x = c10_xTRDt0LbA83zt2EbCc5TbB_q[1];
  c10_xTRDt0LbA83zt2EbCc5TbB_t8 = c10_xTRDt0LbA83zt2EbCc5TbB_g_x;
  c10_xTRDt0LbA83zt2EbCc5TbB_h_x = c10_xTRDt0LbA83zt2EbCc5TbB_t8;
  c10_xTRDt0LbA83zt2EbCc5TbB_t8 = c10_xTRDt0LbA83zt2EbCc5TbB_h_x;
  c10_xTRDt0LbA83zt2EbCc5TbB_t8 = muDoubleScalarCos
    (c10_xTRDt0LbA83zt2EbCc5TbB_t8);
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 17);
  c10_xTRDt0LbA83zt2EbCc5TbB_t9 = c10_xTRDt0LbA83zt2EbCc5TbB_t7 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t8;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 18);
  c10_xTRDt0LbA83zt2EbCc5TbB_t11 = c10_xTRDt0LbA83zt2EbCc5TbB_qp[2] *
    c10_xTRDt0LbA83zt2EbCc5TbB_a[0] * c10_xTRDt0LbA83zt2EbCc5TbB_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 19);
  c10_xTRDt0LbA83zt2EbCc5TbB_t12 = c10_xTRDt0LbA83zt2EbCc5TbB_t9 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t11;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 20);
  c10_xTRDt0LbA83zt2EbCc5TbB_t13 = c10_xTRDt0LbA83zt2EbCc5TbB_t3 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t11;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 21);
  c10_xTRDt0LbA83zt2EbCc5TbB_t14 = c10_xTRDt0LbA83zt2EbCc5TbB_t2 *
    c10_xTRDt0LbA83zt2EbCc5TbB_qp[1];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 22);
  c10_xTRDt0LbA83zt2EbCc5TbB_t16 = c10_xTRDt0LbA83zt2EbCc5TbB_a[0] *
    c10_xTRDt0LbA83zt2EbCc5TbB_a[1] * c10_xTRDt0LbA83zt2EbCc5TbB_xi3[0];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 23);
  c10_xTRDt0LbA83zt2EbCc5TbB_t17 = c10_xTRDt0LbA83zt2EbCc5TbB_t14 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t16;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 24);
  c10_xTRDt0LbA83zt2EbCc5TbB_t19 = c10_xTRDt0LbA83zt2EbCc5TbB_a[1] *
    c10_xTRDt0LbA83zt2EbCc5TbB_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 25);
  c10_xTRDt0LbA83zt2EbCc5TbB_t20 = c10_xTRDt0LbA83zt2EbCc5TbB_t7 *
    c10_xTRDt0LbA83zt2EbCc5TbB_qp[2] * c10_xTRDt0LbA83zt2EbCc5TbB_t19;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 26);
  c10_xTRDt0LbA83zt2EbCc5TbB_t21 = c10_xTRDt0LbA83zt2EbCc5TbB_t9 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t5;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 27);
  c10_xTRDt0LbA83zt2EbCc5TbB_t22 = c10_xTRDt0LbA83zt2EbCc5TbB_a[0] *
    c10_xTRDt0LbA83zt2EbCc5TbB_xi2[1];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 28);
  c10_xTRDt0LbA83zt2EbCc5TbB_t23 = c10_xTRDt0LbA83zt2EbCc5TbB_t14 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t22;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 29);
  c10_xTRDt0LbA83zt2EbCc5TbB_t25 = c10_xTRDt0LbA83zt2EbCc5TbB_qp[0] *
    c10_xTRDt0LbA83zt2EbCc5TbB_a[0];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 30);
  c10_xTRDt0LbA83zt2EbCc5TbB_t26 = c10_xTRDt0LbA83zt2EbCc5TbB_t25 *
    c10_xTRDt0LbA83zt2EbCc5TbB_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 31);
  c10_xTRDt0LbA83zt2EbCc5TbB_t27 = c10_xTRDt0LbA83zt2EbCc5TbB_t9 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t26;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 32);
  c10_xTRDt0LbA83zt2EbCc5TbB_t28 = c10_xTRDt0LbA83zt2EbCc5TbB_t2 *
    c10_xTRDt0LbA83zt2EbCc5TbB_qp[0];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 33);
  c10_xTRDt0LbA83zt2EbCc5TbB_t29 = c10_xTRDt0LbA83zt2EbCc5TbB_t28 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t22;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 34);
  c10_xTRDt0LbA83zt2EbCc5TbB_t30 = c10_xTRDt0LbA83zt2EbCc5TbB_t28 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t16;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 35);
  c10_xTRDt0LbA83zt2EbCc5TbB_t31 = c10_xTRDt0LbA83zt2EbCc5TbB_t3 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t26;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 36);
  c10_xTRDt0LbA83zt2EbCc5TbB_t32 = (((((((((-c10_xTRDt0LbA83zt2EbCc5TbB_t13 -
    c10_xTRDt0LbA83zt2EbCc5TbB_t27) - c10_xTRDt0LbA83zt2EbCc5TbB_t29) -
    c10_xTRDt0LbA83zt2EbCc5TbB_t6) - c10_xTRDt0LbA83zt2EbCc5TbB_t12) -
    c10_xTRDt0LbA83zt2EbCc5TbB_t21) - c10_xTRDt0LbA83zt2EbCc5TbB_t30) -
    c10_xTRDt0LbA83zt2EbCc5TbB_t17) - c10_xTRDt0LbA83zt2EbCc5TbB_t31) -
    c10_xTRDt0LbA83zt2EbCc5TbB_t23) - c10_xTRDt0LbA83zt2EbCc5TbB_t20;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 37);
  c10_xTRDt0LbA83zt2EbCc5TbB_t33 = (c10_xTRDt0LbA83zt2EbCc5TbB_qp[0] +
    c10_xTRDt0LbA83zt2EbCc5TbB_qp[1]) + c10_xTRDt0LbA83zt2EbCc5TbB_qp[2];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 38);
  c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[0] = (((((-c10_xTRDt0LbA83zt2EbCc5TbB_t6 -
    c10_xTRDt0LbA83zt2EbCc5TbB_t12) - c10_xTRDt0LbA83zt2EbCc5TbB_t13) -
    c10_xTRDt0LbA83zt2EbCc5TbB_t17) - c10_xTRDt0LbA83zt2EbCc5TbB_t20) -
    c10_xTRDt0LbA83zt2EbCc5TbB_t21) - c10_xTRDt0LbA83zt2EbCc5TbB_t23;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 39);
  c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[3] = c10_xTRDt0LbA83zt2EbCc5TbB_t32;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 40);
  c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[6] = -c10_xTRDt0LbA83zt2EbCc5TbB_t33 *
    ((c10_xTRDt0LbA83zt2EbCc5TbB_t3 * c10_xTRDt0LbA83zt2EbCc5TbB_a[0] +
      c10_xTRDt0LbA83zt2EbCc5TbB_t7 * c10_xTRDt0LbA83zt2EbCc5TbB_a[1]) +
     c10_xTRDt0LbA83zt2EbCc5TbB_t9 * c10_xTRDt0LbA83zt2EbCc5TbB_a[0]) *
    c10_xTRDt0LbA83zt2EbCc5TbB_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 41);
  c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[1] = (((c10_xTRDt0LbA83zt2EbCc5TbB_t31 +
    c10_xTRDt0LbA83zt2EbCc5TbB_t29) - c10_xTRDt0LbA83zt2EbCc5TbB_t20) +
    c10_xTRDt0LbA83zt2EbCc5TbB_t30) + c10_xTRDt0LbA83zt2EbCc5TbB_t27;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 42);
  c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[4] = -c10_xTRDt0LbA83zt2EbCc5TbB_t20;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 43);
  c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[7] = -c10_xTRDt0LbA83zt2EbCc5TbB_t7 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t33 * c10_xTRDt0LbA83zt2EbCc5TbB_t19;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 44);
  c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[2] = (((c10_xTRDt0LbA83zt2EbCc5TbB_t9 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t25 + c10_xTRDt0LbA83zt2EbCc5TbB_t3 *
    c10_xTRDt0LbA83zt2EbCc5TbB_t25) + c10_xTRDt0LbA83zt2EbCc5TbB_t7 *
    c10_xTRDt0LbA83zt2EbCc5TbB_qp[1] * c10_xTRDt0LbA83zt2EbCc5TbB_a[1]) +
    c10_xTRDt0LbA83zt2EbCc5TbB_t7 * c10_xTRDt0LbA83zt2EbCc5TbB_qp[0] *
    c10_xTRDt0LbA83zt2EbCc5TbB_a[1]) * c10_xTRDt0LbA83zt2EbCc5TbB_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 45);
  c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[5] = c10_xTRDt0LbA83zt2EbCc5TbB_t7 *
    (c10_xTRDt0LbA83zt2EbCc5TbB_qp[0] + c10_xTRDt0LbA83zt2EbCc5TbB_qp[1]) *
    c10_xTRDt0LbA83zt2EbCc5TbB_t19;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 46);
  c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[8] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 51);
  c10_xTRDt0LbA83zt2EbCc5TbB_i = 1.0;
  c10_xTRDt0LbA83zt2EbCc5TbB_b_i = 0;
  while (c10_xTRDt0LbA83zt2EbCc5TbB_b_i < 3) {
    c10_xTRDt0LbA83zt2EbCc5TbB_i = 1.0 + (real_T)c10_xTRDt0LbA83zt2EbCc5TbB_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 52);
    c10_xTRDt0LbA83zt2EbCc5TbB_j = 1.0;
    c10_xTRDt0LbA83zt2EbCc5TbB_b_j = 0;
    while (c10_xTRDt0LbA83zt2EbCc5TbB_b_j < 3) {
      c10_xTRDt0LbA83zt2EbCc5TbB_j = 1.0 + (real_T)
        c10_xTRDt0LbA83zt2EbCc5TbB_b_j;
      CV_EML_FOR(0, 1, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, 53);
      c10_xTRDt0LbA83zt2EbCc5TbB_C[(_SFD_EML_ARRAY_BOUNDS_CHECK("C", (int32_T)
        _SFD_INTEGER_CHECK("i", c10_xTRDt0LbA83zt2EbCc5TbB_i), 1, 3, 1, 0) + 3 *
                                    (_SFD_EML_ARRAY_BOUNDS_CHECK("C", (int32_T)
        _SFD_INTEGER_CHECK("j", c10_xTRDt0LbA83zt2EbCc5TbB_j), 1, 3, 2, 0) - 1))
        - 1] = c10_xTRDt0LbA83zt2EbCc5TbB_CORIOLIS[(_SFD_EML_ARRAY_BOUNDS_CHECK(
        "CORIOLIS", (int32_T)_SFD_INTEGER_CHECK("j",
        c10_xTRDt0LbA83zt2EbCc5TbB_j), 1, 3, 1, 0) + 3 *
        (_SFD_EML_ARRAY_BOUNDS_CHECK("CORIOLIS", (int32_T)_SFD_INTEGER_CHECK("i",
        c10_xTRDt0LbA83zt2EbCc5TbB_i), 1, 3, 2, 0) - 1)) - 1];
      c10_xTRDt0LbA83zt2EbCc5TbB_b_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 1, 0);
    c10_xTRDt0LbA83zt2EbCc5TbB_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent, -53);
  _SFD_SYMBOL_SCOPE_POP();
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i18 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i18 < 9;
       c10_xTRDt0LbA83zt2EbCc5TbB_i18++) {
    (*c10_xTRDt0LbA83zt2EbCc5TbB_b_C)[c10_xTRDt0LbA83zt2EbCc5TbB_i18] =
      c10_xTRDt0LbA83zt2EbCc5TbB_C[c10_xTRDt0LbA83zt2EbCc5TbB_i18];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U,
               chartInstance->c10_xTRDt0LbA83zt2EbCc5TbB_sfEvent);
}

static void initSimStructsc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T
  c10_xTRDt0LbA83zt2EbCc5TbB_machineNumber, uint32_T
  c10_xTRDt0LbA83zt2EbCc5TbB_chartNumber, uint32_T
  c10_xTRDt0LbA83zt2EbCc5TbB_instanceNumber)
{
  (void)c10_xTRDt0LbA83zt2EbCc5TbB_machineNumber;
  (void)c10_xTRDt0LbA83zt2EbCc5TbB_chartNumber;
  (void)c10_xTRDt0LbA83zt2EbCc5TbB_instanceNumber;
}

static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_sf_marshallOut(void
  *chartInstanceVoid, void *c10_xTRDt0LbA83zt2EbCc5TbB_inData)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData = NULL;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i19;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i20;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i21;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_b_inData[9];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i22;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i23;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i24;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_u[9];
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *)
    chartInstanceVoid;
  c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_i19 = 0;
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i20 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i20 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i20++) {
    for (c10_xTRDt0LbA83zt2EbCc5TbB_i21 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i21 < 3;
         c10_xTRDt0LbA83zt2EbCc5TbB_i21++) {
      c10_xTRDt0LbA83zt2EbCc5TbB_b_inData[c10_xTRDt0LbA83zt2EbCc5TbB_i21 +
        c10_xTRDt0LbA83zt2EbCc5TbB_i19] = (*(real_T (*)[9])
        c10_xTRDt0LbA83zt2EbCc5TbB_inData)[c10_xTRDt0LbA83zt2EbCc5TbB_i21 +
        c10_xTRDt0LbA83zt2EbCc5TbB_i19];
    }

    c10_xTRDt0LbA83zt2EbCc5TbB_i19 += 3;
  }

  c10_xTRDt0LbA83zt2EbCc5TbB_i22 = 0;
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i23 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i23 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i23++) {
    for (c10_xTRDt0LbA83zt2EbCc5TbB_i24 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i24 < 3;
         c10_xTRDt0LbA83zt2EbCc5TbB_i24++) {
      c10_xTRDt0LbA83zt2EbCc5TbB_u[c10_xTRDt0LbA83zt2EbCc5TbB_i24 +
        c10_xTRDt0LbA83zt2EbCc5TbB_i22] =
        c10_xTRDt0LbA83zt2EbCc5TbB_b_inData[c10_xTRDt0LbA83zt2EbCc5TbB_i24 +
        c10_xTRDt0LbA83zt2EbCc5TbB_i22];
    }

    c10_xTRDt0LbA83zt2EbCc5TbB_i22 += 3;
  }

  c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_y, sf_mex_create("y",
    c10_xTRDt0LbA83zt2EbCc5TbB_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData,
                c10_xTRDt0LbA83zt2EbCc5TbB_y, false);
  return c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData;
}

static void c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_C, const char_T
   *c10_xTRDt0LbA83zt2EbCc5TbB_identifier, real_T c10_xTRDt0LbA83zt2EbCc5TbB_y[9])
{
  emlrtMsgIdentifier c10_xTRDt0LbA83zt2EbCc5TbB_thisId;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fIdentifier =
    c10_xTRDt0LbA83zt2EbCc5TbB_identifier;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fParent = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c10_xTRDt0LbA83zt2EbCc5TbB_C), &c10_xTRDt0LbA83zt2EbCc5TbB_thisId,
    c10_xTRDt0LbA83zt2EbCc5TbB_y);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_C);
}

static void c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_u, const emlrtMsgIdentifier
   *c10_xTRDt0LbA83zt2EbCc5TbB_parentId, real_T c10_xTRDt0LbA83zt2EbCc5TbB_y[9])
{
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_dv1[9];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i25;
  (void)chartInstance;
  sf_mex_import(c10_xTRDt0LbA83zt2EbCc5TbB_parentId, sf_mex_dup
                (c10_xTRDt0LbA83zt2EbCc5TbB_u), c10_xTRDt0LbA83zt2EbCc5TbB_dv1,
                1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i25 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i25 < 9;
       c10_xTRDt0LbA83zt2EbCc5TbB_i25++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_y[c10_xTRDt0LbA83zt2EbCc5TbB_i25] =
      c10_xTRDt0LbA83zt2EbCc5TbB_dv1[c10_xTRDt0LbA83zt2EbCc5TbB_i25];
  }

  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_u);
}

static void c10_xTRDt0LbA83zt2EbCc5TbB_sf_marshallIn(void *chartInstanceVoid,
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData, const char_T
  *c10_xTRDt0LbA83zt2EbCc5TbB_varName, void *c10_xTRDt0LbA83zt2EbCc5TbB_outData)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_C;
  const char_T *c10_xTRDt0LbA83zt2EbCc5TbB_identifier;
  emlrtMsgIdentifier c10_xTRDt0LbA83zt2EbCc5TbB_thisId;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_y[9];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i26;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i27;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i28;
  SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *)
    chartInstanceVoid;
  c10_xTRDt0LbA83zt2EbCc5TbB_C = sf_mex_dup
    (c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData);
  c10_xTRDt0LbA83zt2EbCc5TbB_identifier = c10_xTRDt0LbA83zt2EbCc5TbB_varName;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fIdentifier =
    c10_xTRDt0LbA83zt2EbCc5TbB_identifier;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fParent = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c10_xTRDt0LbA83zt2EbCc5TbB_C), &c10_xTRDt0LbA83zt2EbCc5TbB_thisId,
    c10_xTRDt0LbA83zt2EbCc5TbB_y);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_C);
  c10_xTRDt0LbA83zt2EbCc5TbB_i26 = 0;
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i27 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i27 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i27++) {
    for (c10_xTRDt0LbA83zt2EbCc5TbB_i28 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i28 < 3;
         c10_xTRDt0LbA83zt2EbCc5TbB_i28++) {
      (*(real_T (*)[9])c10_xTRDt0LbA83zt2EbCc5TbB_outData)
        [c10_xTRDt0LbA83zt2EbCc5TbB_i28 + c10_xTRDt0LbA83zt2EbCc5TbB_i26] =
        c10_xTRDt0LbA83zt2EbCc5TbB_y[c10_xTRDt0LbA83zt2EbCc5TbB_i28 +
        c10_xTRDt0LbA83zt2EbCc5TbB_i26];
    }

    c10_xTRDt0LbA83zt2EbCc5TbB_i26 += 3;
  }

  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData);
}

static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut(void
  *chartInstanceVoid, void *c10_xTRDt0LbA83zt2EbCc5TbB_inData)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData = NULL;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i29;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_b_inData[3];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i30;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_u[3];
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *)
    chartInstanceVoid;
  c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData = NULL;
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i29 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i29 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i29++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_b_inData[c10_xTRDt0LbA83zt2EbCc5TbB_i29] =
      (*(real_T (*)[3])c10_xTRDt0LbA83zt2EbCc5TbB_inData)
      [c10_xTRDt0LbA83zt2EbCc5TbB_i29];
  }

  for (c10_xTRDt0LbA83zt2EbCc5TbB_i30 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i30 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i30++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_u[c10_xTRDt0LbA83zt2EbCc5TbB_i30] =
      c10_xTRDt0LbA83zt2EbCc5TbB_b_inData[c10_xTRDt0LbA83zt2EbCc5TbB_i30];
  }

  c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_y, sf_mex_create("y",
    c10_xTRDt0LbA83zt2EbCc5TbB_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData,
                c10_xTRDt0LbA83zt2EbCc5TbB_y, false);
  return c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData;
}

static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallOut(void
  *chartInstanceVoid, void *c10_xTRDt0LbA83zt2EbCc5TbB_inData)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData = NULL;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_u;
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *)
    chartInstanceVoid;
  c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_u = *(real_T *)c10_xTRDt0LbA83zt2EbCc5TbB_inData;
  c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_y, sf_mex_create("y",
    &c10_xTRDt0LbA83zt2EbCc5TbB_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData,
                c10_xTRDt0LbA83zt2EbCc5TbB_y, false);
  return c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData;
}

static real_T c10_xTRDt0LbA83zt2EbCc5TbB_c_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_u, const emlrtMsgIdentifier
   *c10_xTRDt0LbA83zt2EbCc5TbB_parentId)
{
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_y;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_d0;
  (void)chartInstance;
  sf_mex_import(c10_xTRDt0LbA83zt2EbCc5TbB_parentId, sf_mex_dup
                (c10_xTRDt0LbA83zt2EbCc5TbB_u), &c10_xTRDt0LbA83zt2EbCc5TbB_d0,
                1, 0, 0U, 0, 0U, 0);
  c10_xTRDt0LbA83zt2EbCc5TbB_y = c10_xTRDt0LbA83zt2EbCc5TbB_d0;
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_u);
  return c10_xTRDt0LbA83zt2EbCc5TbB_y;
}

static void c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallIn(void *chartInstanceVoid,
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData, const char_T
  *c10_xTRDt0LbA83zt2EbCc5TbB_varName, void *c10_xTRDt0LbA83zt2EbCc5TbB_outData)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_nargout;
  const char_T *c10_xTRDt0LbA83zt2EbCc5TbB_identifier;
  emlrtMsgIdentifier c10_xTRDt0LbA83zt2EbCc5TbB_thisId;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_y;
  SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *)
    chartInstanceVoid;
  c10_xTRDt0LbA83zt2EbCc5TbB_nargout = sf_mex_dup
    (c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData);
  c10_xTRDt0LbA83zt2EbCc5TbB_identifier = c10_xTRDt0LbA83zt2EbCc5TbB_varName;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fIdentifier =
    c10_xTRDt0LbA83zt2EbCc5TbB_identifier;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fParent = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_y = c10_xTRDt0LbA83zt2EbCc5TbB_c_emlrt_marshallIn
    (chartInstance, sf_mex_dup(c10_xTRDt0LbA83zt2EbCc5TbB_nargout),
     &c10_xTRDt0LbA83zt2EbCc5TbB_thisId);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_nargout);
  *(real_T *)c10_xTRDt0LbA83zt2EbCc5TbB_outData = c10_xTRDt0LbA83zt2EbCc5TbB_y;
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData);
}

static void c10_xTRDt0LbA83zt2EbCc5TbB_d_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_u, const emlrtMsgIdentifier
   *c10_xTRDt0LbA83zt2EbCc5TbB_parentId, real_T c10_xTRDt0LbA83zt2EbCc5TbB_y[3])
{
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_dv2[3];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i31;
  (void)chartInstance;
  sf_mex_import(c10_xTRDt0LbA83zt2EbCc5TbB_parentId, sf_mex_dup
                (c10_xTRDt0LbA83zt2EbCc5TbB_u), c10_xTRDt0LbA83zt2EbCc5TbB_dv2,
                1, 0, 0U, 1, 0U, 1, 3);
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i31 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i31 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i31++) {
    c10_xTRDt0LbA83zt2EbCc5TbB_y[c10_xTRDt0LbA83zt2EbCc5TbB_i31] =
      c10_xTRDt0LbA83zt2EbCc5TbB_dv2[c10_xTRDt0LbA83zt2EbCc5TbB_i31];
  }

  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_u);
}

static void c10_xTRDt0LbA83zt2EbCc5TbB_c_sf_marshallIn(void *chartInstanceVoid,
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData, const char_T
  *c10_xTRDt0LbA83zt2EbCc5TbB_varName, void *c10_xTRDt0LbA83zt2EbCc5TbB_outData)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_qp;
  const char_T *c10_xTRDt0LbA83zt2EbCc5TbB_identifier;
  emlrtMsgIdentifier c10_xTRDt0LbA83zt2EbCc5TbB_thisId;
  real_T c10_xTRDt0LbA83zt2EbCc5TbB_y[3];
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i32;
  SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *)
    chartInstanceVoid;
  c10_xTRDt0LbA83zt2EbCc5TbB_qp = sf_mex_dup
    (c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData);
  c10_xTRDt0LbA83zt2EbCc5TbB_identifier = c10_xTRDt0LbA83zt2EbCc5TbB_varName;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fIdentifier =
    c10_xTRDt0LbA83zt2EbCc5TbB_identifier;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fParent = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c10_xTRDt0LbA83zt2EbCc5TbB_qp), &c10_xTRDt0LbA83zt2EbCc5TbB_thisId,
    c10_xTRDt0LbA83zt2EbCc5TbB_y);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_qp);
  for (c10_xTRDt0LbA83zt2EbCc5TbB_i32 = 0; c10_xTRDt0LbA83zt2EbCc5TbB_i32 < 3;
       c10_xTRDt0LbA83zt2EbCc5TbB_i32++) {
    (*(real_T (*)[3])c10_xTRDt0LbA83zt2EbCc5TbB_outData)
      [c10_xTRDt0LbA83zt2EbCc5TbB_i32] =
      c10_xTRDt0LbA83zt2EbCc5TbB_y[c10_xTRDt0LbA83zt2EbCc5TbB_i32];
  }

  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData);
}

const mxArray
  *sf_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_nameCaptureInfo = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_nameCaptureInfo = NULL;
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_nameCaptureInfo, sf_mex_createstruct
                ("structure", 2, 4, 1), false);
  c10_xTRDt0LbA83zt2EbCc5TbB_info_helper
    (&c10_xTRDt0LbA83zt2EbCc5TbB_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a
    (&c10_xTRDt0LbA83zt2EbCc5TbB_nameCaptureInfo);
  return c10_xTRDt0LbA83zt2EbCc5TbB_nameCaptureInfo;
}

static void c10_xTRDt0LbA83zt2EbCc5TbB_info_helper(const mxArray
  **c10_xTRDt0LbA83zt2EbCc5TbB_info)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_rhs0 = NULL;
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_lhs0 = NULL;
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_rhs1 = NULL;
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_lhs1 = NULL;
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_rhs2 = NULL;
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_lhs2 = NULL;
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_rhs3 = NULL;
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_lhs3 = NULL;
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut(""), "context",
                  "context", 0);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut("cos"), "name",
                  "name", 0);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut("double"),
                  "dominantType", "dominantType", 0);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(1343830372U),
                  "fileTimeLo", "fileTimeLo", 0);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "fileTimeHi", "fileTimeHi", 0);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "mFileTimeLo", "mFileTimeLo", 0);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "mFileTimeHi", "mFileTimeHi", 0);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_rhs0, sf_mex_createcellmatrix(0, 1),
                false);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_lhs0, sf_mex_createcellmatrix(0, 1),
                false);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info, sf_mex_duplicatearraysafe
                  (&c10_xTRDt0LbA83zt2EbCc5TbB_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info, sf_mex_duplicatearraysafe
                  (&c10_xTRDt0LbA83zt2EbCc5TbB_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut("eml_scalar_cos"),
                  "name", "name", 1);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut("double"),
                  "dominantType", "dominantType", 1);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(1286818722U),
                  "fileTimeLo", "fileTimeLo", 1);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "fileTimeHi", "fileTimeHi", 1);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "mFileTimeLo", "mFileTimeLo", 1);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "mFileTimeHi", "mFileTimeHi", 1);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_rhs1, sf_mex_createcellmatrix(0, 1),
                false);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_lhs1, sf_mex_createcellmatrix(0, 1),
                false);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info, sf_mex_duplicatearraysafe
                  (&c10_xTRDt0LbA83zt2EbCc5TbB_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info, sf_mex_duplicatearraysafe
                  (&c10_xTRDt0LbA83zt2EbCc5TbB_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut(""), "context",
                  "context", 2);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut("sin"), "name",
                  "name", 2);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut("double"),
                  "dominantType", "dominantType", 2);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(1343830386U),
                  "fileTimeLo", "fileTimeLo", 2);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "fileTimeHi", "fileTimeHi", 2);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "mFileTimeLo", "mFileTimeLo", 2);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "mFileTimeHi", "mFileTimeHi", 2);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_rhs2, sf_mex_createcellmatrix(0, 1),
                false);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_lhs2, sf_mex_createcellmatrix(0, 1),
                false);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info, sf_mex_duplicatearraysafe
                  (&c10_xTRDt0LbA83zt2EbCc5TbB_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info, sf_mex_duplicatearraysafe
                  (&c10_xTRDt0LbA83zt2EbCc5TbB_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut("eml_scalar_sin"),
                  "name", "name", 3);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut("double"),
                  "dominantType", "dominantType", 3);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(1286818736U),
                  "fileTimeLo", "fileTimeLo", 3);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "fileTimeHi", "fileTimeHi", 3);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "mFileTimeLo", "mFileTimeLo", 3);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info,
                  c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(0U),
                  "mFileTimeHi", "mFileTimeHi", 3);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_rhs3, sf_mex_createcellmatrix(0, 1),
                false);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_lhs3, sf_mex_createcellmatrix(0, 1),
                false);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info, sf_mex_duplicatearraysafe
                  (&c10_xTRDt0LbA83zt2EbCc5TbB_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c10_xTRDt0LbA83zt2EbCc5TbB_info, sf_mex_duplicatearraysafe
                  (&c10_xTRDt0LbA83zt2EbCc5TbB_lhs3), "lhs", "lhs", 3);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_rhs0);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_lhs0);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_rhs1);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_lhs1);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_rhs2);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_lhs2);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_rhs3);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_lhs3);
}

static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_emlrt_marshallOut(const char
  * c10_xTRDt0LbA83zt2EbCc5TbB_u)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_y, sf_mex_create("y",
    c10_xTRDt0LbA83zt2EbCc5TbB_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c10_xTRDt0LbA83zt2EbCc5TbB_u)), false);
  return c10_xTRDt0LbA83zt2EbCc5TbB_y;
}

static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_b_emlrt_marshallOut(const
  uint32_T c10_xTRDt0LbA83zt2EbCc5TbB_u)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_y, sf_mex_create("y",
    &c10_xTRDt0LbA83zt2EbCc5TbB_u, 7, 0U, 0U, 0U, 0), false);
  return c10_xTRDt0LbA83zt2EbCc5TbB_y;
}

static const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_d_sf_marshallOut(void
  *chartInstanceVoid, void *c10_xTRDt0LbA83zt2EbCc5TbB_inData)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData = NULL;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_u;
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *)
    chartInstanceVoid;
  c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_u = *(int32_T *)c10_xTRDt0LbA83zt2EbCc5TbB_inData;
  c10_xTRDt0LbA83zt2EbCc5TbB_y = NULL;
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_y, sf_mex_create("y",
    &c10_xTRDt0LbA83zt2EbCc5TbB_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData,
                c10_xTRDt0LbA83zt2EbCc5TbB_y, false);
  return c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayOutData;
}

static int32_T c10_xTRDt0LbA83zt2EbCc5TbB_e_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_u, const emlrtMsgIdentifier
   *c10_xTRDt0LbA83zt2EbCc5TbB_parentId)
{
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_y;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_i33;
  (void)chartInstance;
  sf_mex_import(c10_xTRDt0LbA83zt2EbCc5TbB_parentId, sf_mex_dup
                (c10_xTRDt0LbA83zt2EbCc5TbB_u), &c10_xTRDt0LbA83zt2EbCc5TbB_i33,
                1, 6, 0U, 0, 0U, 0);
  c10_xTRDt0LbA83zt2EbCc5TbB_y = c10_xTRDt0LbA83zt2EbCc5TbB_i33;
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_u);
  return c10_xTRDt0LbA83zt2EbCc5TbB_y;
}

static void c10_xTRDt0LbA83zt2EbCc5TbB_d_sf_marshallIn(void *chartInstanceVoid,
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData, const char_T
  *c10_xTRDt0LbA83zt2EbCc5TbB_varName, void *c10_xTRDt0LbA83zt2EbCc5TbB_outData)
{
  const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_b_sfEvent;
  const char_T *c10_xTRDt0LbA83zt2EbCc5TbB_identifier;
  emlrtMsgIdentifier c10_xTRDt0LbA83zt2EbCc5TbB_thisId;
  int32_T c10_xTRDt0LbA83zt2EbCc5TbB_y;
  SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *)
    chartInstanceVoid;
  c10_xTRDt0LbA83zt2EbCc5TbB_b_sfEvent = sf_mex_dup
    (c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData);
  c10_xTRDt0LbA83zt2EbCc5TbB_identifier = c10_xTRDt0LbA83zt2EbCc5TbB_varName;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fIdentifier =
    c10_xTRDt0LbA83zt2EbCc5TbB_identifier;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fParent = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_y = c10_xTRDt0LbA83zt2EbCc5TbB_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(c10_xTRDt0LbA83zt2EbCc5TbB_b_sfEvent),
     &c10_xTRDt0LbA83zt2EbCc5TbB_thisId);
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_b_sfEvent);
  *(int32_T *)c10_xTRDt0LbA83zt2EbCc5TbB_outData = c10_xTRDt0LbA83zt2EbCc5TbB_y;
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_mxArrayInData);
}

static uint8_T c10_xTRDt0LbA83zt2EbCc5TbB_f_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray
   *c10_xTRDt0LbA83zt2EbCc5TbB_b_is_active_c10_xTRDt0LbA83zt2EbCc5Tb, const
   char_T *c10_xTRDt0LbA83zt2EbCc5TbB_identifier)
{
  uint8_T c10_xTRDt0LbA83zt2EbCc5TbB_y;
  emlrtMsgIdentifier c10_xTRDt0LbA83zt2EbCc5TbB_thisId;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fIdentifier =
    c10_xTRDt0LbA83zt2EbCc5TbB_identifier;
  c10_xTRDt0LbA83zt2EbCc5TbB_thisId.fParent = NULL;
  c10_xTRDt0LbA83zt2EbCc5TbB_y = c10_xTRDt0LbA83zt2EbCc5TbB_g_emlrt_marshallIn
    (chartInstance, sf_mex_dup
     (c10_xTRDt0LbA83zt2EbCc5TbB_b_is_active_c10_xTRDt0LbA83zt2EbCc5Tb),
     &c10_xTRDt0LbA83zt2EbCc5TbB_thisId);
  sf_mex_destroy
    (&c10_xTRDt0LbA83zt2EbCc5TbB_b_is_active_c10_xTRDt0LbA83zt2EbCc5Tb);
  return c10_xTRDt0LbA83zt2EbCc5TbB_y;
}

static uint8_T c10_xTRDt0LbA83zt2EbCc5TbB_g_emlrt_marshallIn
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance,
   const mxArray *c10_xTRDt0LbA83zt2EbCc5TbB_u, const emlrtMsgIdentifier
   *c10_xTRDt0LbA83zt2EbCc5TbB_parentId)
{
  uint8_T c10_xTRDt0LbA83zt2EbCc5TbB_y;
  uint8_T c10_xTRDt0LbA83zt2EbCc5TbB_u0;
  (void)chartInstance;
  sf_mex_import(c10_xTRDt0LbA83zt2EbCc5TbB_parentId, sf_mex_dup
                (c10_xTRDt0LbA83zt2EbCc5TbB_u), &c10_xTRDt0LbA83zt2EbCc5TbB_u0,
                1, 3, 0U, 0, 0U, 0);
  c10_xTRDt0LbA83zt2EbCc5TbB_y = c10_xTRDt0LbA83zt2EbCc5TbB_u0;
  sf_mex_destroy(&c10_xTRDt0LbA83zt2EbCc5TbB_u);
  return c10_xTRDt0LbA83zt2EbCc5TbB_y;
}

static void init_dsm_address_info
  (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4271314776U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2293838034U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1873026310U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3795665475U);
}

mxArray *sf_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library_get_autoinheritance_info
  (void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("7tlHsWfU2aDNJydQ8jJh7G");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library_updateBuildInfo_args_info
  (void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray
  *sf_get_sim_state_info_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"C\",},{M[8],M[0],T\"is_active_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _m3dof_libraryMachineNumber_,
           10,
           1,
           1,
           0,
           7,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_m3dof_libraryMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_m3dof_libraryMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _m3dof_libraryMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"q");
          _SFD_SET_DATA_PROPS(1,1,1,0,"q_dot");
          _SFD_SET_DATA_PROPS(2,1,1,0,"xi1");
          _SFD_SET_DATA_PROPS(3,2,0,1,"C");
          _SFD_SET_DATA_PROPS(4,1,1,0,"xi2");
          _SFD_SET_DATA_PROPS(5,1,1,0,"xi3");
          _SFD_SET_DATA_PROPS(6,1,1,0,"a");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,2,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1223);
        _SFD_CV_INIT_EML_FOR(0,1,0,1147,1159,1218);
        _SFD_CV_INIT_EML_FOR(0,1,1,1163,1175,1214);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut,
            (MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut,
            (MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut,
            (MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_xTRDt0LbA83zt2EbCc5TbB_sf_marshallOut,
            (MexInFcnForType)c10_xTRDt0LbA83zt2EbCc5TbB_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut,
            (MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut,
            (MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c10_xTRDt0LbA83zt2EbCc5TbB_b_sf_marshallOut,
            (MexInFcnForType)NULL);
        }

        {
          real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_q)[3];
          real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_q_dot)[3];
          real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_xi1)[3];
          real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_C)[9];
          real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_xi2)[3];
          real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_xi3)[3];
          real_T (*c10_xTRDt0LbA83zt2EbCc5TbB_a)[3];
          c10_xTRDt0LbA83zt2EbCc5TbB_a = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 5);
          c10_xTRDt0LbA83zt2EbCc5TbB_xi3 = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 4);
          c10_xTRDt0LbA83zt2EbCc5TbB_xi2 = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 3);
          c10_xTRDt0LbA83zt2EbCc5TbB_C = (real_T (*)[9])ssGetOutputPortSignal
            (chartInstance->S, 1);
          c10_xTRDt0LbA83zt2EbCc5TbB_xi1 = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 2);
          c10_xTRDt0LbA83zt2EbCc5TbB_q_dot = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 1);
          c10_xTRDt0LbA83zt2EbCc5TbB_q = (real_T (*)[3])ssGetInputPortSignal
            (chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c10_xTRDt0LbA83zt2EbCc5TbB_q);
          _SFD_SET_DATA_VALUE_PTR(1U, *c10_xTRDt0LbA83zt2EbCc5TbB_q_dot);
          _SFD_SET_DATA_VALUE_PTR(2U, *c10_xTRDt0LbA83zt2EbCc5TbB_xi1);
          _SFD_SET_DATA_VALUE_PTR(3U, *c10_xTRDt0LbA83zt2EbCc5TbB_C);
          _SFD_SET_DATA_VALUE_PTR(4U, *c10_xTRDt0LbA83zt2EbCc5TbB_xi2);
          _SFD_SET_DATA_VALUE_PTR(5U, *c10_xTRDt0LbA83zt2EbCc5TbB_xi3);
          _SFD_SET_DATA_VALUE_PTR(6U, *c10_xTRDt0LbA83zt2EbCc5TbB_a);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _m3dof_libraryMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "xTRDt0LbA83zt2EbCc5TbB";
}

static void sf_opaque_initialize_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(void
  *chartInstanceVar)
{
  chart_debug_initialization
    (((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
      chartInstanceVar)->S,0);
  initialize_params_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
    ((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
     chartInstanceVar);
  initialize_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
    ((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
     chartInstanceVar);
}

static void sf_opaque_enable_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(void
  *chartInstanceVar)
{
  enable_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
    ((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
     chartInstanceVar);
}

static void sf_opaque_disable_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(void
  *chartInstanceVar)
{
  disable_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
    ((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
     chartInstanceVar);
}

static void sf_opaque_gateway_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(void
  *chartInstanceVar)
{
  sf_gateway_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
    ((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
     chartInstanceVar);
}

extern const mxArray*
  sf_internal_get_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(SimStruct*
  S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
    ((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
     chartInfo->chartInstance);        /* raw sim ctx */
  prhs[3] = (mxArray*)
    sf_get_sim_state_info_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*)
    sf_get_sim_state_info_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
    ((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
     chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray*
  sf_opaque_get_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(SimStruct* S)
{
  return sf_internal_get_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(S);
}

static void sf_opaque_set_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(S, st);
}

static void sf_opaque_terminate_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
                    chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_m3dof_library_optimization_info();
    }

    finalize_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
      ((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
       chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
    ((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
     chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
  (SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library
      ((SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct*)
       (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(SimStruct *
  S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_m3dof_library_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      10);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,10,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,10,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,10);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,10,6);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,10,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 6; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,10);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3421613376U));
  ssSetChecksum1(S,(148285053U));
  ssSetChecksum2(S,(711386178U));
  ssSetChecksum3(S,(2138450950U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(SimStruct *S)
{
  SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct *)
    utMalloc(sizeof(SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc10_xTRDt0LbA83zt2EbCc5TbB_m3dof_libraryInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW =
    mdlRTW_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library;
  chartInstance->chartInfo.mdlStart =
    mdlStart_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library_method_dispatcher(SimStruct *S,
  int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c10_xTRDt0LbA83zt2EbCc5TbB_m3dof_library_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
