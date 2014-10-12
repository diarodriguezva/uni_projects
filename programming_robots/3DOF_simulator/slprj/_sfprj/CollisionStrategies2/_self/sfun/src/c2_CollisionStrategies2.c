/* Include files */

#include <stddef.h>
#include "blas.h"
#include "CollisionStrategies2_sfun.h"
#include "c2_CollisionStrategies2.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "CollisionStrategies2_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[4] = { "nargin", "nargout", "u", "y" };

/* Function Declarations */
static void initialize_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void initialize_params_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void enable_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void disable_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void set_sim_state_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance, const mxArray *c2_st);
static void finalize_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void sf_gateway_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void initSimStructsc2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_y, const char_T *c2_identifier, real_T
  c2_b_y[9]);
static void c2_b_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(const char * c2_u);
static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u);
static void c2_b_info_helper(const mxArray **c2_info);
static void c2_c_info_helper(const mxArray **c2_info);
static void c2_d_info_helper(const mxArray **c2_info);
static void c2_e_info_helper(const mxArray **c2_info);
static void c2_sqrtm(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                     real_T c2_A[9], creal_T c2_X[9]);
static void c2_schur(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                     real_T c2_A[9], creal_T c2_V[9], creal_T c2_T[9]);
static void c2_eml_switch_helper(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static void c2_eml_scalar_eg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static void c2_threshold(SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static real_T c2_abs(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                     real_T c2_x);
static void c2_realmin(SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static real_T c2_eml_xnrm2(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[9], int32_T c2_ix0);
static void c2_check_forloop_overflow_error
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance, boolean_T c2_overflow);
static void c2_eps(SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void c2_eml_eps(SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void c2_eml_xscal(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_a, real_T c2_x[9], int32_T c2_ix0, real_T c2_b_x[9]);
static void c2_b_threshold(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static void c2_eml_matlab_zlarf(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, int32_T c2_iv0, real_T c2_tau, real_T c2_C[9],
  int32_T c2_ic0, real_T c2_work[3], real_T c2_b_C[9], real_T c2_b_work[3]);
static void c2_eml_xgemv(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_m, int32_T c2_n, real_T c2_A[9], int32_T c2_ia0, real_T c2_x[9],
  int32_T c2_ix0, real_T c2_y[3], real_T c2_b_y[3]);
static void c2_c_threshold(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static void c2_b_eml_scalar_eg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static void c2_d_threshold(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static void c2_b_eml_matlab_zlarf(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_iv0, real_T c2_tau,
  real_T c2_C[9], int32_T c2_ic0, real_T c2_work[3], real_T c2_b_C[9], real_T
  c2_b_work[3]);
static void c2_b_eml_xgemv(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_A[9], int32_T c2_ia0,
  real_T c2_x[9], int32_T c2_ix0, real_T c2_y[3], real_T c2_b_y[3]);
static void c2_eml_matlab_zunghr(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_tau[2], real_T c2_b_A[9]);
static void c2_eml_dlahqr(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  real_T c2_h[9], real_T c2_z[9], real_T c2_b_h[9], int32_T *c2_info, real_T
  c2_b_z[9]);
static real_T c2_sqrt(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                      real_T c2_x);
static void c2_eml_error(SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void c2_eml_matlab_zlarfg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_alpha1, real_T c2_x[3], real_T
  *c2_b_alpha1, real_T c2_b_x[3], real_T *c2_tau);
static real_T c2_b_eml_xnrm2(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[3]);
static void c2_b_eml_xscal(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[3], real_T c2_b_x[3]);
static void c2_eml_dlanv2(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  real_T c2_a, real_T c2_b, real_T c2_c, real_T c2_d, real_T *c2_rt1r, real_T
  *c2_rt1i, real_T *c2_rt2r, real_T *c2_rt2i, real_T *c2_b_a, real_T *c2_b_b,
  real_T *c2_b_c, real_T *c2_b_d, real_T *c2_cs, real_T *c2_sn);
static void c2_c_eml_scalar_eg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static void c2_b_eps(SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void c2_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c,
  real_T c2_s, real_T c2_b_x[9]);
static void c2_e_threshold(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static void c2_b_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c,
  real_T c2_s, real_T c2_b_x[9]);
static void c2_c_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c, real_T c2_s,
  real_T c2_b_x[9]);
static void c2_rsf2csf(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  real_T c2_Ur[9], real_T c2_Tr[9], creal_T c2_U[9], creal_T c2_T[9]);
static void c2_b_eml_dlanv2(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, real_T c2_a, real_T c2_b, real_T c2_c, real_T c2_d, real_T
  *c2_rt1r, real_T *c2_rt1i);
static void c2_scalarEg(SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void c2_eml_warning(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static void c2_d_eml_scalar_eg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static boolean_T c2_isUTmatD(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, creal_T c2_T[9]);
static creal_T c2_b_sqrt(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  creal_T c2_x);
static void c2_realmax(SFc2_CollisionStrategies2InstanceStruct *chartInstance);
static void c2_e_eml_scalar_eg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static void c2_eml_xgemm(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  creal_T c2_A[9], creal_T c2_B[9], creal_T c2_C[9], creal_T c2_b_C[9]);
static void c2_b_eml_warning(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static real_T c2_abs1(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                      creal_T c2_x);
static void c2_c_eml_warning(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_d_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_e_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_CollisionStrategies2, const
  char_T *c2_identifier);
static uint8_T c2_f_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_eml_xscal(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[9], int32_T c2_ix0);
static void c2_c_eml_matlab_zlarf(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, int32_T c2_iv0, real_T c2_tau, real_T c2_C[9],
  int32_T c2_ic0, real_T c2_work[3]);
static void c2_c_eml_xgemv(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_A[9], int32_T c2_ia0,
  real_T c2_x[9], int32_T c2_ix0, real_T c2_y[3]);
static void c2_d_eml_matlab_zlarf(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_iv0, real_T c2_tau,
  real_T c2_C[9], int32_T c2_ic0, real_T c2_work[3]);
static void c2_d_eml_xgemv(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_A[9], int32_T c2_ia0,
  real_T c2_x[9], int32_T c2_ix0, real_T c2_y[3]);
static void c2_b_eml_matlab_zunghr(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_tau[2]);
static int32_T c2_b_eml_dlahqr(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, real_T c2_h[9], real_T c2_z[9]);
static void c2_c_sqrt(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                      real_T *c2_x);
static real_T c2_b_eml_matlab_zlarfg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T *c2_alpha1, real_T c2_x[3]);
static void c2_d_eml_xscal(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[3]);
static void c2_c_eml_dlanv2(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, real_T *c2_a, real_T *c2_b, real_T *c2_c, real_T *c2_d, real_T
  *c2_rt1r, real_T *c2_rt1i, real_T *c2_rt2r, real_T *c2_rt2i, real_T *c2_cs,
  real_T *c2_sn);
static void c2_d_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c,
  real_T c2_s);
static void c2_e_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c,
  real_T c2_s);
static void c2_f_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c, real_T c2_s);
static void c2_d_sqrt(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                      creal_T *c2_x);
static void c2_b_eml_xgemm(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, creal_T c2_A[9], creal_T c2_B[9], creal_T c2_C[9]);
static void init_dsm_address_info(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_CollisionStrategies2 = 0U;
}

static void initialize_params_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[9];
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real_T (*c2_d_y)[9];
  c2_d_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(2, 1), false);
  for (c2_i0 = 0; c2_i0 < 9; c2_i0++) {
    c2_u[c2_i0] = (*c2_d_y)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_CollisionStrategies2;
  c2_b_u = c2_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[9];
  int32_T c2_i1;
  real_T (*c2_y)[9];
  c2_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "y",
                      c2_dv0);
  for (c2_i1 = 0; c2_i1 < 9; c2_i1++) {
    (*c2_y)[c2_i1] = c2_dv0[c2_i1];
  }

  chartInstance->c2_is_active_c2_CollisionStrategies2 = c2_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
     "is_active_c2_CollisionStrategies2");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_CollisionStrategies2(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  int32_T c2_i2;
  int32_T c2_i3;
  real_T c2_u[9];
  uint32_T c2_debug_family_var_map[4];
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  real_T c2_y[9];
  int32_T c2_i4;
  real_T c2_b_u[9];
  creal_T c2_dcv0[9];
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  real_T (*c2_b_y)[9];
  real_T (*c2_c_u)[9];
  c2_b_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_c_u = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i2 = 0; c2_i2 < 9; c2_i2++) {
    _SFD_DATA_RANGE_CHECK((*c2_c_u)[c2_i2], 0U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i3 = 0; c2_i3 < 9; c2_i3++) {
    c2_u[c2_i3] = (*c2_c_u)[c2_i3];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 1U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_u, 2U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_y, 3U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  for (c2_i4 = 0; c2_i4 < 9; c2_i4++) {
    c2_b_u[c2_i4] = c2_u[c2_i4];
  }

  c2_sqrtm(chartInstance, c2_b_u, c2_dcv0);
  for (c2_i5 = 0; c2_i5 < 9; c2_i5++) {
    c2_y[c2_i5] = c2_dcv0[c2_i5].re;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i6 = 0; c2_i6 < 9; c2_i6++) {
    (*c2_b_y)[c2_i6] = c2_y[c2_i6];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_CollisionStrategies2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c2_i7 = 0; c2_i7 < 9; c2_i7++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_y)[c2_i7], 1U);
  }
}

static void initSimStructsc2_CollisionStrategies2
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  real_T c2_b_inData[9];
  int32_T c2_i11;
  int32_T c2_i12;
  int32_T c2_i13;
  real_T c2_u[9];
  const mxArray *c2_y = NULL;
  SFc2_CollisionStrategies2InstanceStruct *chartInstance;
  chartInstance = (SFc2_CollisionStrategies2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i8 = 0;
  for (c2_i9 = 0; c2_i9 < 3; c2_i9++) {
    for (c2_i10 = 0; c2_i10 < 3; c2_i10++) {
      c2_b_inData[c2_i10 + c2_i8] = (*(real_T (*)[9])c2_inData)[c2_i10 + c2_i8];
    }

    c2_i8 += 3;
  }

  c2_i11 = 0;
  for (c2_i12 = 0; c2_i12 < 3; c2_i12++) {
    for (c2_i13 = 0; c2_i13 < 3; c2_i13++) {
      c2_u[c2_i13 + c2_i11] = c2_b_inData[c2_i13 + c2_i11];
    }

    c2_i11 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_y, const char_T *c2_identifier, real_T
  c2_b_y[9])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_y), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_y);
}

static void c2_b_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9])
{
  real_T c2_dv1[9];
  int32_T c2_i14;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv1, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c2_i14 = 0; c2_i14 < 9; c2_i14++) {
    c2_y[c2_i14] = c2_dv1[c2_i14];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_y;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_b_y[9];
  int32_T c2_i15;
  int32_T c2_i16;
  int32_T c2_i17;
  SFc2_CollisionStrategies2InstanceStruct *chartInstance;
  chartInstance = (SFc2_CollisionStrategies2InstanceStruct *)chartInstanceVoid;
  c2_y = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_y), &c2_thisId, c2_b_y);
  sf_mex_destroy(&c2_y);
  c2_i15 = 0;
  for (c2_i16 = 0; c2_i16 < 3; c2_i16++) {
    for (c2_i17 = 0; c2_i17 < 3; c2_i17++) {
      (*(real_T (*)[9])c2_outData)[c2_i17 + c2_i15] = c2_b_y[c2_i17 + c2_i15];
    }

    c2_i15 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_CollisionStrategies2InstanceStruct *chartInstance;
  chartInstance = (SFc2_CollisionStrategies2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_CollisionStrategies2InstanceStruct *chartInstance;
  chartInstance = (SFc2_CollisionStrategies2InstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_CollisionStrategies2_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 288, 1),
                false);
  c2_info_helper(&c2_nameCaptureInfo);
  c2_b_info_helper(&c2_nameCaptureInfo);
  c2_c_info_helper(&c2_nameCaptureInfo);
  c2_d_info_helper(&c2_nameCaptureInfo);
  c2_e_info_helper(&c2_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs0 = NULL;
  const mxArray *c2_lhs0 = NULL;
  const mxArray *c2_rhs1 = NULL;
  const mxArray *c2_lhs1 = NULL;
  const mxArray *c2_rhs2 = NULL;
  const mxArray *c2_lhs2 = NULL;
  const mxArray *c2_rhs3 = NULL;
  const mxArray *c2_lhs3 = NULL;
  const mxArray *c2_rhs4 = NULL;
  const mxArray *c2_lhs4 = NULL;
  const mxArray *c2_rhs5 = NULL;
  const mxArray *c2_lhs5 = NULL;
  const mxArray *c2_rhs6 = NULL;
  const mxArray *c2_lhs6 = NULL;
  const mxArray *c2_rhs7 = NULL;
  const mxArray *c2_lhs7 = NULL;
  const mxArray *c2_rhs8 = NULL;
  const mxArray *c2_lhs8 = NULL;
  const mxArray *c2_rhs9 = NULL;
  const mxArray *c2_lhs9 = NULL;
  const mxArray *c2_rhs10 = NULL;
  const mxArray *c2_lhs10 = NULL;
  const mxArray *c2_rhs11 = NULL;
  const mxArray *c2_lhs11 = NULL;
  const mxArray *c2_rhs12 = NULL;
  const mxArray *c2_lhs12 = NULL;
  const mxArray *c2_rhs13 = NULL;
  const mxArray *c2_lhs13 = NULL;
  const mxArray *c2_rhs14 = NULL;
  const mxArray *c2_lhs14 = NULL;
  const mxArray *c2_rhs15 = NULL;
  const mxArray *c2_lhs15 = NULL;
  const mxArray *c2_rhs16 = NULL;
  const mxArray *c2_lhs16 = NULL;
  const mxArray *c2_rhs17 = NULL;
  const mxArray *c2_lhs17 = NULL;
  const mxArray *c2_rhs18 = NULL;
  const mxArray *c2_lhs18 = NULL;
  const mxArray *c2_rhs19 = NULL;
  const mxArray *c2_lhs19 = NULL;
  const mxArray *c2_rhs20 = NULL;
  const mxArray *c2_lhs20 = NULL;
  const mxArray *c2_rhs21 = NULL;
  const mxArray *c2_lhs21 = NULL;
  const mxArray *c2_rhs22 = NULL;
  const mxArray *c2_lhs22 = NULL;
  const mxArray *c2_rhs23 = NULL;
  const mxArray *c2_lhs23 = NULL;
  const mxArray *c2_rhs24 = NULL;
  const mxArray *c2_lhs24 = NULL;
  const mxArray *c2_rhs25 = NULL;
  const mxArray *c2_lhs25 = NULL;
  const mxArray *c2_rhs26 = NULL;
  const mxArray *c2_lhs26 = NULL;
  const mxArray *c2_rhs27 = NULL;
  const mxArray *c2_lhs27 = NULL;
  const mxArray *c2_rhs28 = NULL;
  const mxArray *c2_lhs28 = NULL;
  const mxArray *c2_rhs29 = NULL;
  const mxArray *c2_lhs29 = NULL;
  const mxArray *c2_rhs30 = NULL;
  const mxArray *c2_lhs30 = NULL;
  const mxArray *c2_rhs31 = NULL;
  const mxArray *c2_lhs31 = NULL;
  const mxArray *c2_rhs32 = NULL;
  const mxArray *c2_lhs32 = NULL;
  const mxArray *c2_rhs33 = NULL;
  const mxArray *c2_lhs33 = NULL;
  const mxArray *c2_rhs34 = NULL;
  const mxArray *c2_lhs34 = NULL;
  const mxArray *c2_rhs35 = NULL;
  const mxArray *c2_lhs35 = NULL;
  const mxArray *c2_rhs36 = NULL;
  const mxArray *c2_lhs36 = NULL;
  const mxArray *c2_rhs37 = NULL;
  const mxArray *c2_lhs37 = NULL;
  const mxArray *c2_rhs38 = NULL;
  const mxArray *c2_lhs38 = NULL;
  const mxArray *c2_rhs39 = NULL;
  const mxArray *c2_lhs39 = NULL;
  const mxArray *c2_rhs40 = NULL;
  const mxArray *c2_lhs40 = NULL;
  const mxArray *c2_rhs41 = NULL;
  const mxArray *c2_lhs41 = NULL;
  const mxArray *c2_rhs42 = NULL;
  const mxArray *c2_lhs42 = NULL;
  const mxArray *c2_rhs43 = NULL;
  const mxArray *c2_lhs43 = NULL;
  const mxArray *c2_rhs44 = NULL;
  const mxArray *c2_lhs44 = NULL;
  const mxArray *c2_rhs45 = NULL;
  const mxArray *c2_lhs45 = NULL;
  const mxArray *c2_rhs46 = NULL;
  const mxArray *c2_lhs46 = NULL;
  const mxArray *c2_rhs47 = NULL;
  const mxArray *c2_lhs47 = NULL;
  const mxArray *c2_rhs48 = NULL;
  const mxArray *c2_lhs48 = NULL;
  const mxArray *c2_rhs49 = NULL;
  const mxArray *c2_lhs49 = NULL;
  const mxArray *c2_rhs50 = NULL;
  const mxArray *c2_lhs50 = NULL;
  const mxArray *c2_rhs51 = NULL;
  const mxArray *c2_lhs51 = NULL;
  const mxArray *c2_rhs52 = NULL;
  const mxArray *c2_lhs52 = NULL;
  const mxArray *c2_rhs53 = NULL;
  const mxArray *c2_lhs53 = NULL;
  const mxArray *c2_rhs54 = NULL;
  const mxArray *c2_lhs54 = NULL;
  const mxArray *c2_rhs55 = NULL;
  const mxArray *c2_lhs55 = NULL;
  const mxArray *c2_rhs56 = NULL;
  const mxArray *c2_lhs56 = NULL;
  const mxArray *c2_rhs57 = NULL;
  const mxArray *c2_lhs57 = NULL;
  const mxArray *c2_rhs58 = NULL;
  const mxArray *c2_lhs58 = NULL;
  const mxArray *c2_rhs59 = NULL;
  const mxArray *c2_lhs59 = NULL;
  const mxArray *c2_rhs60 = NULL;
  const mxArray *c2_lhs60 = NULL;
  const mxArray *c2_rhs61 = NULL;
  const mxArray *c2_lhs61 = NULL;
  const mxArray *c2_rhs62 = NULL;
  const mxArray *c2_lhs62 = NULL;
  const mxArray *c2_rhs63 = NULL;
  const mxArray *c2_lhs63 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("sqrtm"), "name", "name", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1305318002U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c2_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("schur"), "name", "name", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/schur.m"), "resolved",
                  "resolved", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1305318002U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c2_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/schur.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c2_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/schur.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xgehrd"), "name", "name",
                  3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgehrd.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818804U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c2_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgehrd.m"),
                  "context", "context", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_lapack_xgehrd"), "name",
                  "name", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgehrd.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818808U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c2_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgehrd.m"),
                  "context", "context", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_matlab_zgehrd"), "name",
                  "name", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818816U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c2_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "context", "context", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c2_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "context", "context", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c2_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c2_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "context", "context", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c2_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c2_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "context", "context", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c2_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c2_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c2_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "context", "context", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c2_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c2_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "context", "context", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c2_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "context", "context", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c2_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "context", "context", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311255318U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c2_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378295984U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c2_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c2_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c2_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c2_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c2_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c2_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c2_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c2_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "context", "context", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c2_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c2_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "context", "context", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c2_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c2_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "context", "context", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_matlab_zlarfg"), "name",
                  "name", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818822U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c2_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "context", "context", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c2_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "context", "context", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xnrm2"), "name", "name",
                  33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980692U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c2_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m"), "context",
                  "context", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c2_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m"), "context",
                  "context", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xnrm2"),
                  "name", "name", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xnrm2.p"),
                  "resolved", "resolved", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c2_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xnrm2.p"),
                  "context", "context", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c2_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xnrm2.p!below_threshold"),
                  "context", "context", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c2_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c2_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xnrm2.p!below_threshold"),
                  "context", "context", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("length"), "name", "name", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1303146206U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c2_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength"),
                  "context", "context", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c2_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xnrm2.p"),
                  "context", "context", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xnrm2"),
                  "name", "name", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "resolved", "resolved", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c2_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c2_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c2_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818712U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c2_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("realmin"), "name", "name", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "resolved",
                  "resolved", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1307651242U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c2_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "context",
                  "context", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_realmin"), "name", "name",
                  46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "resolved",
                  "resolved", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1307651244U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c2_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "context",
                  "context", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c2_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c2_rhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c2_rhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c2_rhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c2_rhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "context", "context", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_dlapy2"), "name", "name",
                  52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlapy2.m"), "resolved",
                  "resolved", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1350410654U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c2_rhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "context", "context", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("realmin"), "name", "name", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "resolved",
                  "resolved", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1307651242U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c2_rhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "context", "context", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eps"), "name", "name", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c2_rhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs54), "lhs", "lhs",
                  54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_is_float_class"), "name",
                  "name", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m"),
                  "resolved", "resolved", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818782U), "fileTimeLo",
                  "fileTimeLo", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 55);
  sf_mex_assign(&c2_rhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs55), "rhs", "rhs",
                  55);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs55), "lhs", "lhs",
                  55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_eps"), "name", "name", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "resolved",
                  "resolved", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 56);
  sf_mex_assign(&c2_rhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs56), "rhs", "rhs",
                  56);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs56), "lhs", "lhs",
                  56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "context",
                  "context", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 57);
  sf_mex_assign(&c2_rhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs57), "rhs", "rhs",
                  57);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs57), "lhs", "lhs",
                  57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "context", "context", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 58);
  sf_mex_assign(&c2_rhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs58), "rhs", "rhs",
                  58);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs58), "lhs", "lhs",
                  58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "context", "context", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 59);
  sf_mex_assign(&c2_rhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs59), "rhs", "rhs",
                  59);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs59), "lhs", "lhs",
                  59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "context", "context", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 60);
  sf_mex_assign(&c2_rhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs60), "rhs", "rhs",
                  60);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs60), "lhs", "lhs",
                  60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "context", "context", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xscal"), "name", "name",
                  61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xscal.m"),
                  "resolved", "resolved", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980692U), "fileTimeLo",
                  "fileTimeLo", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 61);
  sf_mex_assign(&c2_rhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs61), "rhs", "rhs",
                  61);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs61), "lhs", "lhs",
                  61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xscal.m"), "context",
                  "context", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 62);
  sf_mex_assign(&c2_rhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs62), "rhs", "rhs",
                  62);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs62), "lhs", "lhs",
                  62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xscal.m"), "context",
                  "context", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xscal"),
                  "name", "name", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xscal.p"),
                  "resolved", "resolved", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 63);
  sf_mex_assign(&c2_rhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs63), "rhs", "rhs",
                  63);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs63), "lhs", "lhs",
                  63);
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
  sf_mex_destroy(&c2_rhs1);
  sf_mex_destroy(&c2_lhs1);
  sf_mex_destroy(&c2_rhs2);
  sf_mex_destroy(&c2_lhs2);
  sf_mex_destroy(&c2_rhs3);
  sf_mex_destroy(&c2_lhs3);
  sf_mex_destroy(&c2_rhs4);
  sf_mex_destroy(&c2_lhs4);
  sf_mex_destroy(&c2_rhs5);
  sf_mex_destroy(&c2_lhs5);
  sf_mex_destroy(&c2_rhs6);
  sf_mex_destroy(&c2_lhs6);
  sf_mex_destroy(&c2_rhs7);
  sf_mex_destroy(&c2_lhs7);
  sf_mex_destroy(&c2_rhs8);
  sf_mex_destroy(&c2_lhs8);
  sf_mex_destroy(&c2_rhs9);
  sf_mex_destroy(&c2_lhs9);
  sf_mex_destroy(&c2_rhs10);
  sf_mex_destroy(&c2_lhs10);
  sf_mex_destroy(&c2_rhs11);
  sf_mex_destroy(&c2_lhs11);
  sf_mex_destroy(&c2_rhs12);
  sf_mex_destroy(&c2_lhs12);
  sf_mex_destroy(&c2_rhs13);
  sf_mex_destroy(&c2_lhs13);
  sf_mex_destroy(&c2_rhs14);
  sf_mex_destroy(&c2_lhs14);
  sf_mex_destroy(&c2_rhs15);
  sf_mex_destroy(&c2_lhs15);
  sf_mex_destroy(&c2_rhs16);
  sf_mex_destroy(&c2_lhs16);
  sf_mex_destroy(&c2_rhs17);
  sf_mex_destroy(&c2_lhs17);
  sf_mex_destroy(&c2_rhs18);
  sf_mex_destroy(&c2_lhs18);
  sf_mex_destroy(&c2_rhs19);
  sf_mex_destroy(&c2_lhs19);
  sf_mex_destroy(&c2_rhs20);
  sf_mex_destroy(&c2_lhs20);
  sf_mex_destroy(&c2_rhs21);
  sf_mex_destroy(&c2_lhs21);
  sf_mex_destroy(&c2_rhs22);
  sf_mex_destroy(&c2_lhs22);
  sf_mex_destroy(&c2_rhs23);
  sf_mex_destroy(&c2_lhs23);
  sf_mex_destroy(&c2_rhs24);
  sf_mex_destroy(&c2_lhs24);
  sf_mex_destroy(&c2_rhs25);
  sf_mex_destroy(&c2_lhs25);
  sf_mex_destroy(&c2_rhs26);
  sf_mex_destroy(&c2_lhs26);
  sf_mex_destroy(&c2_rhs27);
  sf_mex_destroy(&c2_lhs27);
  sf_mex_destroy(&c2_rhs28);
  sf_mex_destroy(&c2_lhs28);
  sf_mex_destroy(&c2_rhs29);
  sf_mex_destroy(&c2_lhs29);
  sf_mex_destroy(&c2_rhs30);
  sf_mex_destroy(&c2_lhs30);
  sf_mex_destroy(&c2_rhs31);
  sf_mex_destroy(&c2_lhs31);
  sf_mex_destroy(&c2_rhs32);
  sf_mex_destroy(&c2_lhs32);
  sf_mex_destroy(&c2_rhs33);
  sf_mex_destroy(&c2_lhs33);
  sf_mex_destroy(&c2_rhs34);
  sf_mex_destroy(&c2_lhs34);
  sf_mex_destroy(&c2_rhs35);
  sf_mex_destroy(&c2_lhs35);
  sf_mex_destroy(&c2_rhs36);
  sf_mex_destroy(&c2_lhs36);
  sf_mex_destroy(&c2_rhs37);
  sf_mex_destroy(&c2_lhs37);
  sf_mex_destroy(&c2_rhs38);
  sf_mex_destroy(&c2_lhs38);
  sf_mex_destroy(&c2_rhs39);
  sf_mex_destroy(&c2_lhs39);
  sf_mex_destroy(&c2_rhs40);
  sf_mex_destroy(&c2_lhs40);
  sf_mex_destroy(&c2_rhs41);
  sf_mex_destroy(&c2_lhs41);
  sf_mex_destroy(&c2_rhs42);
  sf_mex_destroy(&c2_lhs42);
  sf_mex_destroy(&c2_rhs43);
  sf_mex_destroy(&c2_lhs43);
  sf_mex_destroy(&c2_rhs44);
  sf_mex_destroy(&c2_lhs44);
  sf_mex_destroy(&c2_rhs45);
  sf_mex_destroy(&c2_lhs45);
  sf_mex_destroy(&c2_rhs46);
  sf_mex_destroy(&c2_lhs46);
  sf_mex_destroy(&c2_rhs47);
  sf_mex_destroy(&c2_lhs47);
  sf_mex_destroy(&c2_rhs48);
  sf_mex_destroy(&c2_lhs48);
  sf_mex_destroy(&c2_rhs49);
  sf_mex_destroy(&c2_lhs49);
  sf_mex_destroy(&c2_rhs50);
  sf_mex_destroy(&c2_lhs50);
  sf_mex_destroy(&c2_rhs51);
  sf_mex_destroy(&c2_lhs51);
  sf_mex_destroy(&c2_rhs52);
  sf_mex_destroy(&c2_lhs52);
  sf_mex_destroy(&c2_rhs53);
  sf_mex_destroy(&c2_lhs53);
  sf_mex_destroy(&c2_rhs54);
  sf_mex_destroy(&c2_lhs54);
  sf_mex_destroy(&c2_rhs55);
  sf_mex_destroy(&c2_lhs55);
  sf_mex_destroy(&c2_rhs56);
  sf_mex_destroy(&c2_lhs56);
  sf_mex_destroy(&c2_rhs57);
  sf_mex_destroy(&c2_lhs57);
  sf_mex_destroy(&c2_rhs58);
  sf_mex_destroy(&c2_lhs58);
  sf_mex_destroy(&c2_rhs59);
  sf_mex_destroy(&c2_lhs59);
  sf_mex_destroy(&c2_rhs60);
  sf_mex_destroy(&c2_lhs60);
  sf_mex_destroy(&c2_rhs61);
  sf_mex_destroy(&c2_lhs61);
  sf_mex_destroy(&c2_rhs62);
  sf_mex_destroy(&c2_lhs62);
  sf_mex_destroy(&c2_rhs63);
  sf_mex_destroy(&c2_lhs63);
}

static const mxArray *c2_emlrt_marshallOut(const char * c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c2_u)), false);
  return c2_y;
}

static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 7, 0U, 0U, 0U, 0), false);
  return c2_y;
}

static void c2_b_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs64 = NULL;
  const mxArray *c2_lhs64 = NULL;
  const mxArray *c2_rhs65 = NULL;
  const mxArray *c2_lhs65 = NULL;
  const mxArray *c2_rhs66 = NULL;
  const mxArray *c2_lhs66 = NULL;
  const mxArray *c2_rhs67 = NULL;
  const mxArray *c2_lhs67 = NULL;
  const mxArray *c2_rhs68 = NULL;
  const mxArray *c2_lhs68 = NULL;
  const mxArray *c2_rhs69 = NULL;
  const mxArray *c2_lhs69 = NULL;
  const mxArray *c2_rhs70 = NULL;
  const mxArray *c2_lhs70 = NULL;
  const mxArray *c2_rhs71 = NULL;
  const mxArray *c2_lhs71 = NULL;
  const mxArray *c2_rhs72 = NULL;
  const mxArray *c2_lhs72 = NULL;
  const mxArray *c2_rhs73 = NULL;
  const mxArray *c2_lhs73 = NULL;
  const mxArray *c2_rhs74 = NULL;
  const mxArray *c2_lhs74 = NULL;
  const mxArray *c2_rhs75 = NULL;
  const mxArray *c2_lhs75 = NULL;
  const mxArray *c2_rhs76 = NULL;
  const mxArray *c2_lhs76 = NULL;
  const mxArray *c2_rhs77 = NULL;
  const mxArray *c2_lhs77 = NULL;
  const mxArray *c2_rhs78 = NULL;
  const mxArray *c2_lhs78 = NULL;
  const mxArray *c2_rhs79 = NULL;
  const mxArray *c2_lhs79 = NULL;
  const mxArray *c2_rhs80 = NULL;
  const mxArray *c2_lhs80 = NULL;
  const mxArray *c2_rhs81 = NULL;
  const mxArray *c2_lhs81 = NULL;
  const mxArray *c2_rhs82 = NULL;
  const mxArray *c2_lhs82 = NULL;
  const mxArray *c2_rhs83 = NULL;
  const mxArray *c2_lhs83 = NULL;
  const mxArray *c2_rhs84 = NULL;
  const mxArray *c2_lhs84 = NULL;
  const mxArray *c2_rhs85 = NULL;
  const mxArray *c2_lhs85 = NULL;
  const mxArray *c2_rhs86 = NULL;
  const mxArray *c2_lhs86 = NULL;
  const mxArray *c2_rhs87 = NULL;
  const mxArray *c2_lhs87 = NULL;
  const mxArray *c2_rhs88 = NULL;
  const mxArray *c2_lhs88 = NULL;
  const mxArray *c2_rhs89 = NULL;
  const mxArray *c2_lhs89 = NULL;
  const mxArray *c2_rhs90 = NULL;
  const mxArray *c2_lhs90 = NULL;
  const mxArray *c2_rhs91 = NULL;
  const mxArray *c2_lhs91 = NULL;
  const mxArray *c2_rhs92 = NULL;
  const mxArray *c2_lhs92 = NULL;
  const mxArray *c2_rhs93 = NULL;
  const mxArray *c2_lhs93 = NULL;
  const mxArray *c2_rhs94 = NULL;
  const mxArray *c2_lhs94 = NULL;
  const mxArray *c2_rhs95 = NULL;
  const mxArray *c2_lhs95 = NULL;
  const mxArray *c2_rhs96 = NULL;
  const mxArray *c2_lhs96 = NULL;
  const mxArray *c2_rhs97 = NULL;
  const mxArray *c2_lhs97 = NULL;
  const mxArray *c2_rhs98 = NULL;
  const mxArray *c2_lhs98 = NULL;
  const mxArray *c2_rhs99 = NULL;
  const mxArray *c2_lhs99 = NULL;
  const mxArray *c2_rhs100 = NULL;
  const mxArray *c2_lhs100 = NULL;
  const mxArray *c2_rhs101 = NULL;
  const mxArray *c2_lhs101 = NULL;
  const mxArray *c2_rhs102 = NULL;
  const mxArray *c2_lhs102 = NULL;
  const mxArray *c2_rhs103 = NULL;
  const mxArray *c2_lhs103 = NULL;
  const mxArray *c2_rhs104 = NULL;
  const mxArray *c2_lhs104 = NULL;
  const mxArray *c2_rhs105 = NULL;
  const mxArray *c2_lhs105 = NULL;
  const mxArray *c2_rhs106 = NULL;
  const mxArray *c2_lhs106 = NULL;
  const mxArray *c2_rhs107 = NULL;
  const mxArray *c2_lhs107 = NULL;
  const mxArray *c2_rhs108 = NULL;
  const mxArray *c2_lhs108 = NULL;
  const mxArray *c2_rhs109 = NULL;
  const mxArray *c2_lhs109 = NULL;
  const mxArray *c2_rhs110 = NULL;
  const mxArray *c2_lhs110 = NULL;
  const mxArray *c2_rhs111 = NULL;
  const mxArray *c2_lhs111 = NULL;
  const mxArray *c2_rhs112 = NULL;
  const mxArray *c2_lhs112 = NULL;
  const mxArray *c2_rhs113 = NULL;
  const mxArray *c2_lhs113 = NULL;
  const mxArray *c2_rhs114 = NULL;
  const mxArray *c2_lhs114 = NULL;
  const mxArray *c2_rhs115 = NULL;
  const mxArray *c2_lhs115 = NULL;
  const mxArray *c2_rhs116 = NULL;
  const mxArray *c2_lhs116 = NULL;
  const mxArray *c2_rhs117 = NULL;
  const mxArray *c2_lhs117 = NULL;
  const mxArray *c2_rhs118 = NULL;
  const mxArray *c2_lhs118 = NULL;
  const mxArray *c2_rhs119 = NULL;
  const mxArray *c2_lhs119 = NULL;
  const mxArray *c2_rhs120 = NULL;
  const mxArray *c2_lhs120 = NULL;
  const mxArray *c2_rhs121 = NULL;
  const mxArray *c2_lhs121 = NULL;
  const mxArray *c2_rhs122 = NULL;
  const mxArray *c2_lhs122 = NULL;
  const mxArray *c2_rhs123 = NULL;
  const mxArray *c2_lhs123 = NULL;
  const mxArray *c2_rhs124 = NULL;
  const mxArray *c2_lhs124 = NULL;
  const mxArray *c2_rhs125 = NULL;
  const mxArray *c2_lhs125 = NULL;
  const mxArray *c2_rhs126 = NULL;
  const mxArray *c2_lhs126 = NULL;
  const mxArray *c2_rhs127 = NULL;
  const mxArray *c2_lhs127 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xscal.p"),
                  "context", "context", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 64);
  sf_mex_assign(&c2_rhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs64), "rhs", "rhs",
                  64);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs64), "lhs", "lhs",
                  64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xscal.p!below_threshold"),
                  "context", "context", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 65);
  sf_mex_assign(&c2_rhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs65), "rhs", "rhs",
                  65);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs65), "lhs", "lhs",
                  65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xscal.p!below_threshold"),
                  "context", "context", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("length"), "name", "name", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1303146206U), "fileTimeLo",
                  "fileTimeLo", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 66);
  sf_mex_assign(&c2_rhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs66), "rhs", "rhs",
                  66);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs66), "lhs", "lhs",
                  66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xscal.p"),
                  "context", "context", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 67);
  sf_mex_assign(&c2_rhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs67), "rhs", "rhs",
                  67);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs67), "lhs", "lhs",
                  67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xscal.p"),
                  "context", "context", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xscal"),
                  "name", "name", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xscal.p"),
                  "resolved", "resolved", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 68);
  sf_mex_assign(&c2_rhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs68), "rhs", "rhs",
                  68);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs68), "lhs", "lhs",
                  68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xscal.p"),
                  "context", "context", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 69);
  sf_mex_assign(&c2_rhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs69), "rhs", "rhs",
                  69);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs69), "lhs", "lhs",
                  69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xscal.p"),
                  "context", "context", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 70);
  sf_mex_assign(&c2_rhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs70), "rhs", "rhs",
                  70);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs70), "lhs", "lhs",
                  70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xscal.p"),
                  "context", "context", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 71);
  sf_mex_assign(&c2_rhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs71), "rhs", "rhs",
                  71);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs71), "lhs", "lhs",
                  71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xscal.p"),
                  "context", "context", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 72);
  sf_mex_assign(&c2_rhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs72), "rhs", "rhs",
                  72);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs72), "lhs", "lhs",
                  72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "context", "context", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_div"), "name", "name", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 73);
  sf_mex_assign(&c2_rhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs73), "rhs", "rhs",
                  73);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs73), "lhs", "lhs",
                  73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 74);
  sf_mex_assign(&c2_rhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs74), "rhs", "rhs",
                  74);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs74), "lhs", "lhs",
                  74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "context", "context", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 75);
  sf_mex_assign(&c2_rhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs75), "rhs", "rhs",
                  75);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs75), "lhs", "lhs",
                  75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgehrd.m"),
                  "context", "context", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_matlab_zlarf"), "name",
                  "name", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m"),
                  "resolved", "resolved", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818822U), "fileTimeLo",
                  "fileTimeLo", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 76);
  sf_mex_assign(&c2_rhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs76), "rhs", "rhs",
                  76);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs76), "lhs", "lhs",
                  76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m"),
                  "context", "context", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 77);
  sf_mex_assign(&c2_rhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs77), "rhs", "rhs",
                  77);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs77), "lhs", "lhs",
                  77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m"),
                  "context", "context", 78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 78);
  sf_mex_assign(&c2_rhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs78), "rhs", "rhs",
                  78);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs78), "lhs", "lhs",
                  78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m"),
                  "context", "context", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isequal"), "name", "name", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818758U), "fileTimeLo",
                  "fileTimeLo", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 79);
  sf_mex_assign(&c2_rhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs79), "rhs", "rhs",
                  79);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs79), "lhs", "lhs",
                  79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818786U), "fileTimeLo",
                  "fileTimeLo", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 80);
  sf_mex_assign(&c2_rhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs80), "rhs", "rhs",
                  80);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs80), "lhs", "lhs",
                  80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m"),
                  "context", "context", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 81);
  sf_mex_assign(&c2_rhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs81), "rhs", "rhs",
                  81);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs81), "lhs", "lhs",
                  81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m"),
                  "context", "context", 82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 82);
  sf_mex_assign(&c2_rhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs82), "rhs", "rhs",
                  82);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs82), "lhs", "lhs",
                  82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m"),
                  "context", "context", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 83);
  sf_mex_assign(&c2_rhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs83), "rhs", "rhs",
                  83);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs83), "lhs", "lhs",
                  83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m"),
                  "context", "context", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 84);
  sf_mex_assign(&c2_rhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs84), "rhs", "rhs",
                  84);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs84), "lhs", "lhs",
                  84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m!ilazlr"),
                  "context", "context", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 85);
  sf_mex_assign(&c2_rhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs85), "rhs", "rhs",
                  85);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs85), "lhs", "lhs",
                  85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m!ilazlr"),
                  "context", "context", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 86);
  sf_mex_assign(&c2_rhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs86), "rhs", "rhs",
                  86);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs86), "lhs", "lhs",
                  86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m!ilazlr"),
                  "context", "context", 87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 87);
  sf_mex_assign(&c2_rhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs87), "rhs", "rhs",
                  87);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs87), "lhs", "lhs",
                  87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m!ilazlr"),
                  "context", "context", 88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 88);
  sf_mex_assign(&c2_rhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs88), "rhs", "rhs",
                  88);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs88), "lhs", "lhs",
                  88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m!ilazlr"),
                  "context", "context", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 89);
  sf_mex_assign(&c2_rhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs89), "rhs", "rhs",
                  89);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs89), "lhs", "lhs",
                  89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m"),
                  "context", "context", 90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xgemv"), "name", "name",
                  90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemv.m"),
                  "resolved", "resolved", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 90);
  sf_mex_assign(&c2_rhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs90), "rhs", "rhs",
                  90);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs90), "lhs", "lhs",
                  90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemv.m"), "context",
                  "context", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 91);
  sf_mex_assign(&c2_rhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs91), "rhs", "rhs",
                  91);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs91), "lhs", "lhs",
                  91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemv.m"), "context",
                  "context", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xgemv"),
                  "name", "name", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemv.p"),
                  "resolved", "resolved", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 92);
  sf_mex_assign(&c2_rhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs92), "rhs", "rhs",
                  92);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs92), "lhs", "lhs",
                  92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemv.p"),
                  "context", "context", 93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 93);
  sf_mex_assign(&c2_rhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs93), "rhs", "rhs",
                  93);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs93), "lhs", "lhs",
                  93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemv.p!below_threshold"),
                  "context", "context", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 94);
  sf_mex_assign(&c2_rhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs94), "rhs", "rhs",
                  94);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs94), "lhs", "lhs",
                  94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemv.p!below_threshold"),
                  "context", "context", 95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("length"), "name", "name", 95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1303146206U), "fileTimeLo",
                  "fileTimeLo", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 95);
  sf_mex_assign(&c2_rhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs95), "rhs", "rhs",
                  95);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs95), "lhs", "lhs",
                  95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemv.p!below_threshold"),
                  "context", "context", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311255318U), "fileTimeLo",
                  "fileTimeLo", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 96);
  sf_mex_assign(&c2_rhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs96), "rhs", "rhs",
                  96);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs96), "lhs", "lhs",
                  96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 97);
  sf_mex_assign(&c2_rhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs97), "rhs", "rhs",
                  97);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs97), "lhs", "lhs",
                  97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 98);
  sf_mex_assign(&c2_rhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs98), "rhs", "rhs",
                  98);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs98), "lhs", "lhs",
                  98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 99);
  sf_mex_assign(&c2_rhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs99), "rhs", "rhs",
                  99);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs99), "lhs", "lhs",
                  99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 100);
  sf_mex_assign(&c2_rhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs100), "rhs", "rhs",
                  100);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs100), "lhs", "lhs",
                  100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 101);
  sf_mex_assign(&c2_rhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs101), "rhs", "rhs",
                  101);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs101), "lhs", "lhs",
                  101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemv.p"),
                  "context", "context", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 102);
  sf_mex_assign(&c2_rhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs102), "rhs", "rhs",
                  102);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs102), "lhs", "lhs",
                  102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemv.p"),
                  "context", "context", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xgemv"),
                  "name", "name", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemv.p"),
                  "resolved", "resolved", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 103);
  sf_mex_assign(&c2_rhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs103), "rhs", "rhs",
                  103);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs103), "lhs", "lhs",
                  103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemv.p"),
                  "context", "context", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 104);
  sf_mex_assign(&c2_rhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs104), "rhs", "rhs",
                  104);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs104), "lhs", "lhs",
                  104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemv.p"),
                  "context", "context", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 105);
  sf_mex_assign(&c2_rhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs105), "rhs", "rhs",
                  105);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs105), "lhs", "lhs",
                  105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemv.p"),
                  "context", "context", 106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 106);
  sf_mex_assign(&c2_rhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs106), "rhs", "rhs",
                  106);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs106), "lhs", "lhs",
                  106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemv.p"),
                  "context", "context", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 107);
  sf_mex_assign(&c2_rhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs107), "rhs", "rhs",
                  107);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs107), "lhs", "lhs",
                  107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m"),
                  "context", "context", 108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xgerc"), "name", "name",
                  108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgerc.m"),
                  "resolved", "resolved", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 108);
  sf_mex_assign(&c2_rhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs108), "rhs", "rhs",
                  108);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs108), "lhs", "lhs",
                  108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgerc.m"), "context",
                  "context", 109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 109);
  sf_mex_assign(&c2_rhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs109), "rhs", "rhs",
                  109);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs109), "lhs", "lhs",
                  109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgerc.m"), "context",
                  "context", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xgerc"),
                  "name", "name", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgerc.p"),
                  "resolved", "resolved", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 110);
  sf_mex_assign(&c2_rhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs110), "rhs", "rhs",
                  110);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs110), "lhs", "lhs",
                  110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgerc.p"),
                  "context", "context", 111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xger"),
                  "name", "name", 111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "resolved", "resolved", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 111);
  sf_mex_assign(&c2_rhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs111), "rhs", "rhs",
                  111);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs111), "lhs", "lhs",
                  111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "context", "context", 112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 112);
  sf_mex_assign(&c2_rhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs112), "rhs", "rhs",
                  112);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs112), "lhs", "lhs",
                  112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 113);
  sf_mex_assign(&c2_rhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs113), "rhs", "rhs",
                  113);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs113), "lhs", "lhs",
                  113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("length"), "name", "name", 114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1303146206U), "fileTimeLo",
                  "fileTimeLo", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 114);
  sf_mex_assign(&c2_rhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs114), "rhs", "rhs",
                  114);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs114), "lhs", "lhs",
                  114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311255318U), "fileTimeLo",
                  "fileTimeLo", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 115);
  sf_mex_assign(&c2_rhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs115), "rhs", "rhs",
                  115);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs115), "lhs", "lhs",
                  115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.int"),
                  "name", "name", 116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/int.p"),
                  "resolved", "resolved", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 116);
  sf_mex_assign(&c2_rhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs116), "rhs", "rhs",
                  116);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs116), "lhs", "lhs",
                  116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 117);
  sf_mex_assign(&c2_rhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs117), "rhs", "rhs",
                  117);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs117), "lhs", "lhs",
                  117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "context", "context", 118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xger"),
                  "name", "name", 118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xger.p"),
                  "resolved", "resolved", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 118);
  sf_mex_assign(&c2_rhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs118), "rhs", "rhs",
                  118);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs118), "lhs", "lhs",
                  118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xger.p"),
                  "context", "context", 119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xgerx"),
                  "name", "name", 119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "resolved", "resolved", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 119);
  sf_mex_assign(&c2_rhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs119), "rhs", "rhs",
                  119);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs119), "lhs", "lhs",
                  119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 120);
  sf_mex_assign(&c2_rhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs120), "rhs", "rhs",
                  120);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs120), "lhs", "lhs",
                  120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 121);
  sf_mex_assign(&c2_rhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs121), "rhs", "rhs",
                  121);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs121), "lhs", "lhs",
                  121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818712U), "fileTimeLo",
                  "fileTimeLo", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 122);
  sf_mex_assign(&c2_rhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs122), "rhs", "rhs",
                  122);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs122), "lhs", "lhs",
                  122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 123);
  sf_mex_assign(&c2_rhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs123), "rhs", "rhs",
                  123);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs123), "lhs", "lhs",
                  123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 124);
  sf_mex_assign(&c2_rhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs124), "rhs", "rhs",
                  124);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs124), "lhs", "lhs",
                  124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 125);
  sf_mex_assign(&c2_rhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs125), "rhs", "rhs",
                  125);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs125), "lhs", "lhs",
                  125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 126);
  sf_mex_assign(&c2_rhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs126), "rhs", "rhs",
                  126);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs126), "lhs", "lhs",
                  126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m!ilazlc"),
                  "context", "context", 127);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 127);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 127);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 127);
  sf_mex_assign(&c2_rhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs127), "rhs", "rhs",
                  127);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs127), "lhs", "lhs",
                  127);
  sf_mex_destroy(&c2_rhs64);
  sf_mex_destroy(&c2_lhs64);
  sf_mex_destroy(&c2_rhs65);
  sf_mex_destroy(&c2_lhs65);
  sf_mex_destroy(&c2_rhs66);
  sf_mex_destroy(&c2_lhs66);
  sf_mex_destroy(&c2_rhs67);
  sf_mex_destroy(&c2_lhs67);
  sf_mex_destroy(&c2_rhs68);
  sf_mex_destroy(&c2_lhs68);
  sf_mex_destroy(&c2_rhs69);
  sf_mex_destroy(&c2_lhs69);
  sf_mex_destroy(&c2_rhs70);
  sf_mex_destroy(&c2_lhs70);
  sf_mex_destroy(&c2_rhs71);
  sf_mex_destroy(&c2_lhs71);
  sf_mex_destroy(&c2_rhs72);
  sf_mex_destroy(&c2_lhs72);
  sf_mex_destroy(&c2_rhs73);
  sf_mex_destroy(&c2_lhs73);
  sf_mex_destroy(&c2_rhs74);
  sf_mex_destroy(&c2_lhs74);
  sf_mex_destroy(&c2_rhs75);
  sf_mex_destroy(&c2_lhs75);
  sf_mex_destroy(&c2_rhs76);
  sf_mex_destroy(&c2_lhs76);
  sf_mex_destroy(&c2_rhs77);
  sf_mex_destroy(&c2_lhs77);
  sf_mex_destroy(&c2_rhs78);
  sf_mex_destroy(&c2_lhs78);
  sf_mex_destroy(&c2_rhs79);
  sf_mex_destroy(&c2_lhs79);
  sf_mex_destroy(&c2_rhs80);
  sf_mex_destroy(&c2_lhs80);
  sf_mex_destroy(&c2_rhs81);
  sf_mex_destroy(&c2_lhs81);
  sf_mex_destroy(&c2_rhs82);
  sf_mex_destroy(&c2_lhs82);
  sf_mex_destroy(&c2_rhs83);
  sf_mex_destroy(&c2_lhs83);
  sf_mex_destroy(&c2_rhs84);
  sf_mex_destroy(&c2_lhs84);
  sf_mex_destroy(&c2_rhs85);
  sf_mex_destroy(&c2_lhs85);
  sf_mex_destroy(&c2_rhs86);
  sf_mex_destroy(&c2_lhs86);
  sf_mex_destroy(&c2_rhs87);
  sf_mex_destroy(&c2_lhs87);
  sf_mex_destroy(&c2_rhs88);
  sf_mex_destroy(&c2_lhs88);
  sf_mex_destroy(&c2_rhs89);
  sf_mex_destroy(&c2_lhs89);
  sf_mex_destroy(&c2_rhs90);
  sf_mex_destroy(&c2_lhs90);
  sf_mex_destroy(&c2_rhs91);
  sf_mex_destroy(&c2_lhs91);
  sf_mex_destroy(&c2_rhs92);
  sf_mex_destroy(&c2_lhs92);
  sf_mex_destroy(&c2_rhs93);
  sf_mex_destroy(&c2_lhs93);
  sf_mex_destroy(&c2_rhs94);
  sf_mex_destroy(&c2_lhs94);
  sf_mex_destroy(&c2_rhs95);
  sf_mex_destroy(&c2_lhs95);
  sf_mex_destroy(&c2_rhs96);
  sf_mex_destroy(&c2_lhs96);
  sf_mex_destroy(&c2_rhs97);
  sf_mex_destroy(&c2_lhs97);
  sf_mex_destroy(&c2_rhs98);
  sf_mex_destroy(&c2_lhs98);
  sf_mex_destroy(&c2_rhs99);
  sf_mex_destroy(&c2_lhs99);
  sf_mex_destroy(&c2_rhs100);
  sf_mex_destroy(&c2_lhs100);
  sf_mex_destroy(&c2_rhs101);
  sf_mex_destroy(&c2_lhs101);
  sf_mex_destroy(&c2_rhs102);
  sf_mex_destroy(&c2_lhs102);
  sf_mex_destroy(&c2_rhs103);
  sf_mex_destroy(&c2_lhs103);
  sf_mex_destroy(&c2_rhs104);
  sf_mex_destroy(&c2_lhs104);
  sf_mex_destroy(&c2_rhs105);
  sf_mex_destroy(&c2_lhs105);
  sf_mex_destroy(&c2_rhs106);
  sf_mex_destroy(&c2_lhs106);
  sf_mex_destroy(&c2_rhs107);
  sf_mex_destroy(&c2_lhs107);
  sf_mex_destroy(&c2_rhs108);
  sf_mex_destroy(&c2_lhs108);
  sf_mex_destroy(&c2_rhs109);
  sf_mex_destroy(&c2_lhs109);
  sf_mex_destroy(&c2_rhs110);
  sf_mex_destroy(&c2_lhs110);
  sf_mex_destroy(&c2_rhs111);
  sf_mex_destroy(&c2_lhs111);
  sf_mex_destroy(&c2_rhs112);
  sf_mex_destroy(&c2_lhs112);
  sf_mex_destroy(&c2_rhs113);
  sf_mex_destroy(&c2_lhs113);
  sf_mex_destroy(&c2_rhs114);
  sf_mex_destroy(&c2_lhs114);
  sf_mex_destroy(&c2_rhs115);
  sf_mex_destroy(&c2_lhs115);
  sf_mex_destroy(&c2_rhs116);
  sf_mex_destroy(&c2_lhs116);
  sf_mex_destroy(&c2_rhs117);
  sf_mex_destroy(&c2_lhs117);
  sf_mex_destroy(&c2_rhs118);
  sf_mex_destroy(&c2_lhs118);
  sf_mex_destroy(&c2_rhs119);
  sf_mex_destroy(&c2_lhs119);
  sf_mex_destroy(&c2_rhs120);
  sf_mex_destroy(&c2_lhs120);
  sf_mex_destroy(&c2_rhs121);
  sf_mex_destroy(&c2_lhs121);
  sf_mex_destroy(&c2_rhs122);
  sf_mex_destroy(&c2_lhs122);
  sf_mex_destroy(&c2_rhs123);
  sf_mex_destroy(&c2_lhs123);
  sf_mex_destroy(&c2_rhs124);
  sf_mex_destroy(&c2_lhs124);
  sf_mex_destroy(&c2_rhs125);
  sf_mex_destroy(&c2_lhs125);
  sf_mex_destroy(&c2_rhs126);
  sf_mex_destroy(&c2_lhs126);
  sf_mex_destroy(&c2_rhs127);
  sf_mex_destroy(&c2_lhs127);
}

static void c2_c_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs128 = NULL;
  const mxArray *c2_lhs128 = NULL;
  const mxArray *c2_rhs129 = NULL;
  const mxArray *c2_lhs129 = NULL;
  const mxArray *c2_rhs130 = NULL;
  const mxArray *c2_lhs130 = NULL;
  const mxArray *c2_rhs131 = NULL;
  const mxArray *c2_lhs131 = NULL;
  const mxArray *c2_rhs132 = NULL;
  const mxArray *c2_lhs132 = NULL;
  const mxArray *c2_rhs133 = NULL;
  const mxArray *c2_lhs133 = NULL;
  const mxArray *c2_rhs134 = NULL;
  const mxArray *c2_lhs134 = NULL;
  const mxArray *c2_rhs135 = NULL;
  const mxArray *c2_lhs135 = NULL;
  const mxArray *c2_rhs136 = NULL;
  const mxArray *c2_lhs136 = NULL;
  const mxArray *c2_rhs137 = NULL;
  const mxArray *c2_lhs137 = NULL;
  const mxArray *c2_rhs138 = NULL;
  const mxArray *c2_lhs138 = NULL;
  const mxArray *c2_rhs139 = NULL;
  const mxArray *c2_lhs139 = NULL;
  const mxArray *c2_rhs140 = NULL;
  const mxArray *c2_lhs140 = NULL;
  const mxArray *c2_rhs141 = NULL;
  const mxArray *c2_lhs141 = NULL;
  const mxArray *c2_rhs142 = NULL;
  const mxArray *c2_lhs142 = NULL;
  const mxArray *c2_rhs143 = NULL;
  const mxArray *c2_lhs143 = NULL;
  const mxArray *c2_rhs144 = NULL;
  const mxArray *c2_lhs144 = NULL;
  const mxArray *c2_rhs145 = NULL;
  const mxArray *c2_lhs145 = NULL;
  const mxArray *c2_rhs146 = NULL;
  const mxArray *c2_lhs146 = NULL;
  const mxArray *c2_rhs147 = NULL;
  const mxArray *c2_lhs147 = NULL;
  const mxArray *c2_rhs148 = NULL;
  const mxArray *c2_lhs148 = NULL;
  const mxArray *c2_rhs149 = NULL;
  const mxArray *c2_lhs149 = NULL;
  const mxArray *c2_rhs150 = NULL;
  const mxArray *c2_lhs150 = NULL;
  const mxArray *c2_rhs151 = NULL;
  const mxArray *c2_lhs151 = NULL;
  const mxArray *c2_rhs152 = NULL;
  const mxArray *c2_lhs152 = NULL;
  const mxArray *c2_rhs153 = NULL;
  const mxArray *c2_lhs153 = NULL;
  const mxArray *c2_rhs154 = NULL;
  const mxArray *c2_lhs154 = NULL;
  const mxArray *c2_rhs155 = NULL;
  const mxArray *c2_lhs155 = NULL;
  const mxArray *c2_rhs156 = NULL;
  const mxArray *c2_lhs156 = NULL;
  const mxArray *c2_rhs157 = NULL;
  const mxArray *c2_lhs157 = NULL;
  const mxArray *c2_rhs158 = NULL;
  const mxArray *c2_lhs158 = NULL;
  const mxArray *c2_rhs159 = NULL;
  const mxArray *c2_lhs159 = NULL;
  const mxArray *c2_rhs160 = NULL;
  const mxArray *c2_lhs160 = NULL;
  const mxArray *c2_rhs161 = NULL;
  const mxArray *c2_lhs161 = NULL;
  const mxArray *c2_rhs162 = NULL;
  const mxArray *c2_lhs162 = NULL;
  const mxArray *c2_rhs163 = NULL;
  const mxArray *c2_lhs163 = NULL;
  const mxArray *c2_rhs164 = NULL;
  const mxArray *c2_lhs164 = NULL;
  const mxArray *c2_rhs165 = NULL;
  const mxArray *c2_lhs165 = NULL;
  const mxArray *c2_rhs166 = NULL;
  const mxArray *c2_lhs166 = NULL;
  const mxArray *c2_rhs167 = NULL;
  const mxArray *c2_lhs167 = NULL;
  const mxArray *c2_rhs168 = NULL;
  const mxArray *c2_lhs168 = NULL;
  const mxArray *c2_rhs169 = NULL;
  const mxArray *c2_lhs169 = NULL;
  const mxArray *c2_rhs170 = NULL;
  const mxArray *c2_lhs170 = NULL;
  const mxArray *c2_rhs171 = NULL;
  const mxArray *c2_lhs171 = NULL;
  const mxArray *c2_rhs172 = NULL;
  const mxArray *c2_lhs172 = NULL;
  const mxArray *c2_rhs173 = NULL;
  const mxArray *c2_lhs173 = NULL;
  const mxArray *c2_rhs174 = NULL;
  const mxArray *c2_lhs174 = NULL;
  const mxArray *c2_rhs175 = NULL;
  const mxArray *c2_lhs175 = NULL;
  const mxArray *c2_rhs176 = NULL;
  const mxArray *c2_lhs176 = NULL;
  const mxArray *c2_rhs177 = NULL;
  const mxArray *c2_lhs177 = NULL;
  const mxArray *c2_rhs178 = NULL;
  const mxArray *c2_lhs178 = NULL;
  const mxArray *c2_rhs179 = NULL;
  const mxArray *c2_lhs179 = NULL;
  const mxArray *c2_rhs180 = NULL;
  const mxArray *c2_lhs180 = NULL;
  const mxArray *c2_rhs181 = NULL;
  const mxArray *c2_lhs181 = NULL;
  const mxArray *c2_rhs182 = NULL;
  const mxArray *c2_lhs182 = NULL;
  const mxArray *c2_rhs183 = NULL;
  const mxArray *c2_lhs183 = NULL;
  const mxArray *c2_rhs184 = NULL;
  const mxArray *c2_lhs184 = NULL;
  const mxArray *c2_rhs185 = NULL;
  const mxArray *c2_lhs185 = NULL;
  const mxArray *c2_rhs186 = NULL;
  const mxArray *c2_lhs186 = NULL;
  const mxArray *c2_rhs187 = NULL;
  const mxArray *c2_lhs187 = NULL;
  const mxArray *c2_rhs188 = NULL;
  const mxArray *c2_lhs188 = NULL;
  const mxArray *c2_rhs189 = NULL;
  const mxArray *c2_lhs189 = NULL;
  const mxArray *c2_rhs190 = NULL;
  const mxArray *c2_lhs190 = NULL;
  const mxArray *c2_rhs191 = NULL;
  const mxArray *c2_lhs191 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m!ilazlc"),
                  "context", "context", 128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 128);
  sf_mex_assign(&c2_rhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs128), "rhs", "rhs",
                  128);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs128), "lhs", "lhs",
                  128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m!ilazlc"),
                  "context", "context", 129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 129);
  sf_mex_assign(&c2_rhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs129), "rhs", "rhs",
                  129);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs129), "lhs", "lhs",
                  129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m!ilazlc"),
                  "context", "context", 130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 130);
  sf_mex_assign(&c2_rhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs130), "rhs", "rhs",
                  130);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs130), "lhs", "lhs",
                  130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m!ilazlc"),
                  "context", "context", 131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 131);
  sf_mex_assign(&c2_rhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs131), "rhs", "rhs",
                  131);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs131), "lhs", "lhs",
                  131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemv.p"),
                  "context", "context", 132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 132);
  sf_mex_assign(&c2_rhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs132), "rhs", "rhs",
                  132);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs132), "lhs", "lhs",
                  132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemv.p"),
                  "context", "context", 133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.conjtimes"),
                  "name", "name", 133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/conjtimes.m"),
                  "resolved", "resolved", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1360282586U), "fileTimeLo",
                  "fileTimeLo", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 133);
  sf_mex_assign(&c2_rhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs133), "rhs", "rhs",
                  133);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs133), "lhs", "lhs",
                  133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/schur.m"), "context",
                  "context", 134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xunghr"), "name", "name",
                  134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xunghr.m"),
                  "resolved", "resolved", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818808U), "fileTimeLo",
                  "fileTimeLo", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 134);
  sf_mex_assign(&c2_rhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs134), "rhs", "rhs",
                  134);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs134), "lhs", "lhs",
                  134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xunghr.m"),
                  "context", "context", 135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_lapack_xunghr"), "name",
                  "name", 135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xunghr.m"),
                  "resolved", "resolved", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818812U), "fileTimeLo",
                  "fileTimeLo", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 135);
  sf_mex_assign(&c2_rhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs135), "rhs", "rhs",
                  135);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs135), "lhs", "lhs",
                  135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xunghr.m"),
                  "context", "context", 136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_matlab_zunghr"), "name",
                  "name", 136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zunghr.m"),
                  "resolved", "resolved", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818826U), "fileTimeLo",
                  "fileTimeLo", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 136);
  sf_mex_assign(&c2_rhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs136), "rhs", "rhs",
                  136);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs136), "lhs", "lhs",
                  136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zunghr.m"),
                  "context", "context", 137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 137);
  sf_mex_assign(&c2_rhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs137), "rhs", "rhs",
                  137);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs137), "lhs", "lhs",
                  137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zunghr.m"),
                  "context", "context", 138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 138);
  sf_mex_assign(&c2_rhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs138), "rhs", "rhs",
                  138);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs138), "lhs", "lhs",
                  138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zunghr.m"),
                  "context", "context", 139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 139);
  sf_mex_assign(&c2_rhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs139), "rhs", "rhs",
                  139);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs139), "lhs", "lhs",
                  139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zunghr.m"),
                  "context", "context", 140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 140);
  sf_mex_assign(&c2_rhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs140), "rhs", "rhs",
                  140);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs140), "lhs", "lhs",
                  140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zunghr.m"),
                  "context", "context", 141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 141);
  sf_mex_assign(&c2_rhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs141), "rhs", "rhs",
                  141);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs141), "lhs", "lhs",
                  141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 142);
  sf_mex_assign(&c2_rhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs142), "rhs", "rhs",
                  142);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs142), "lhs", "lhs",
                  142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 143);
  sf_mex_assign(&c2_rhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs143), "rhs", "rhs",
                  143);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs143), "lhs", "lhs",
                  143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zunghr.m"),
                  "context", "context", 144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 144);
  sf_mex_assign(&c2_rhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs144), "rhs", "rhs",
                  144);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs144), "lhs", "lhs",
                  144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zunghr.m"),
                  "context", "context", 145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 145);
  sf_mex_assign(&c2_rhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs145), "rhs", "rhs",
                  145);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs145), "lhs", "lhs",
                  145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zunghr.m"),
                  "context", "context", 146);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_matlab_zungqr"), "name",
                  "name", 146);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 146);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zungqr.m"),
                  "resolved", "resolved", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818826U), "fileTimeLo",
                  "fileTimeLo", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 146);
  sf_mex_assign(&c2_rhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs146), "rhs", "rhs",
                  146);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs146), "lhs", "lhs",
                  146);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zungqr.m"),
                  "context", "context", 147);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 147);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 147);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 147);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 147);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 147);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 147);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 147);
  sf_mex_assign(&c2_rhs147, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs147, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs147), "rhs", "rhs",
                  147);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs147), "lhs", "lhs",
                  147);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zungqr.m"),
                  "context", "context", 148);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 148);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 148);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 148);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 148);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 148);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 148);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 148);
  sf_mex_assign(&c2_rhs148, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs148, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs148), "rhs", "rhs",
                  148);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs148), "lhs", "lhs",
                  148);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zungqr.m"),
                  "context", "context", 149);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 149);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 149);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 149);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 149);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 149);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 149);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 149);
  sf_mex_assign(&c2_rhs149, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs149, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs149), "rhs", "rhs",
                  149);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs149), "lhs", "lhs",
                  149);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zungqr.m"),
                  "context", "context", 150);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 150);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 150);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 150);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 150);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 150);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 150);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 150);
  sf_mex_assign(&c2_rhs150, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs150, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs150), "rhs", "rhs",
                  150);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs150), "lhs", "lhs",
                  150);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zungqr.m"),
                  "context", "context", 151);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 151);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 151);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 151);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 151);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 151);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 151);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 151);
  sf_mex_assign(&c2_rhs151, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs151, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs151), "rhs", "rhs",
                  151);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs151), "lhs", "lhs",
                  151);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zungqr.m"),
                  "context", "context", 152);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 152);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 152);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 152);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 152);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 152);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 152);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 152);
  sf_mex_assign(&c2_rhs152, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs152, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs152), "rhs", "rhs",
                  152);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs152), "lhs", "lhs",
                  152);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zungqr.m"),
                  "context", "context", 153);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 153);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 153);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 153);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 153);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 153);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 153);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 153);
  sf_mex_assign(&c2_rhs153, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs153, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs153), "rhs", "rhs",
                  153);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs153), "lhs", "lhs",
                  153);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zungqr.m"),
                  "context", "context", 154);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 154);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 154);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 154);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 154);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 154);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 154);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 154);
  sf_mex_assign(&c2_rhs154, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs154, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs154), "rhs", "rhs",
                  154);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs154), "lhs", "lhs",
                  154);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zungqr.m"),
                  "context", "context", 155);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_matlab_zlarf"), "name",
                  "name", 155);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 155);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarf.m"),
                  "resolved", "resolved", 155);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818822U), "fileTimeLo",
                  "fileTimeLo", 155);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 155);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 155);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 155);
  sf_mex_assign(&c2_rhs155, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs155, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs155), "rhs", "rhs",
                  155);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs155), "lhs", "lhs",
                  155);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zungqr.m"),
                  "context", "context", 156);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xscal"), "name", "name",
                  156);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 156);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xscal.m"),
                  "resolved", "resolved", 156);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980692U), "fileTimeLo",
                  "fileTimeLo", 156);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 156);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 156);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 156);
  sf_mex_assign(&c2_rhs156, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs156, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs156), "rhs", "rhs",
                  156);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs156), "lhs", "lhs",
                  156);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/schur.m"), "context",
                  "context", 157);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xhseqr"), "name", "name",
                  157);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 157);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xhseqr.m"),
                  "resolved", "resolved", 157);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818808U), "fileTimeLo",
                  "fileTimeLo", 157);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 157);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 157);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 157);
  sf_mex_assign(&c2_rhs157, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs157, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs157), "rhs", "rhs",
                  157);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs157), "lhs", "lhs",
                  157);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xhseqr.m"),
                  "context", "context", 158);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_lapack_xhseqr"), "name",
                  "name", 158);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 158);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xhseqr.m"),
                  "resolved", "resolved", 158);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818812U), "fileTimeLo",
                  "fileTimeLo", 158);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 158);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 158);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 158);
  sf_mex_assign(&c2_rhs158, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs158, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs158), "rhs", "rhs",
                  158);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs158), "lhs", "lhs",
                  158);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xhseqr.m"),
                  "context", "context", 159);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_matlab_dhseqr"), "name",
                  "name", 159);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 159);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m"),
                  "resolved", "resolved", 159);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818814U), "fileTimeLo",
                  "fileTimeLo", 159);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 159);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 159);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 159);
  sf_mex_assign(&c2_rhs159, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs159, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs159), "rhs", "rhs",
                  159);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs159), "lhs", "lhs",
                  159);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 160);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 160);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 160);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 160);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 160);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 160);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 160);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 160);
  sf_mex_assign(&c2_rhs160, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs160, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs160), "rhs", "rhs",
                  160);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs160), "lhs", "lhs",
                  160);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 161);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 161);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 161);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 161);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 161);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 161);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 161);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 161);
  sf_mex_assign(&c2_rhs161, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs161, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs161), "rhs", "rhs",
                  161);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs161), "lhs", "lhs",
                  161);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 162);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 162);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 162);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 162);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 162);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 162);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 162);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 162);
  sf_mex_assign(&c2_rhs162, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs162, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs162), "rhs", "rhs",
                  162);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs162), "lhs", "lhs",
                  162);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 163);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 163);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 163);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 163);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 163);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 163);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 163);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 163);
  sf_mex_assign(&c2_rhs163, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs163, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs163), "rhs", "rhs",
                  163);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs163), "lhs", "lhs",
                  163);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 164);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("realmin"), "name", "name", 164);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 164);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "resolved",
                  "resolved", 164);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1307651242U), "fileTimeLo",
                  "fileTimeLo", 164);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 164);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 164);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 164);
  sf_mex_assign(&c2_rhs164, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs164, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs164), "rhs", "rhs",
                  164);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs164), "lhs", "lhs",
                  164);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 165);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eps"), "name", "name", 165);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 165);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 165);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 165);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 165);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 165);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 165);
  sf_mex_assign(&c2_rhs165, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs165, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs165), "rhs", "rhs",
                  165);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs165), "lhs", "lhs",
                  165);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 166);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mrdivide"), "name", "name",
                  166);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 166);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 166);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 166);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 166);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 166);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 166);
  sf_mex_assign(&c2_rhs166, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs166, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs166), "rhs", "rhs",
                  166);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs166), "lhs", "lhs",
                  166);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 167);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 167);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 167);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 167);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 167);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 167);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 167);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 167);
  sf_mex_assign(&c2_rhs167, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs167, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs167), "rhs", "rhs",
                  167);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs167), "lhs", "lhs",
                  167);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 168);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("rdivide"), "name", "name", 168);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 168);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 168);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 168);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 168);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 168);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 168);
  sf_mex_assign(&c2_rhs168, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs168, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs168), "rhs", "rhs",
                  168);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs168), "lhs", "lhs",
                  168);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 169);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 169);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 169);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 169);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 169);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 169);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 169);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 169);
  sf_mex_assign(&c2_rhs169, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs169, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs169), "rhs", "rhs",
                  169);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs169), "lhs", "lhs",
                  169);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 170);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 170);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 170);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 170);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 170);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 170);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 170);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 170);
  sf_mex_assign(&c2_rhs170, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs170, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs170), "rhs", "rhs",
                  170);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs170), "lhs", "lhs",
                  170);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 171);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_div"), "name", "name", 171);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 171);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 171);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 171);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 171);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 171);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 171);
  sf_mex_assign(&c2_rhs171, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs171, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs171), "rhs", "rhs",
                  171);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs171), "lhs", "lhs",
                  171);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 172);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 172);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 172);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 172);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 172);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 172);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 172);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 172);
  sf_mex_assign(&c2_rhs172, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs172, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs172), "rhs", "rhs",
                  172);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs172), "lhs", "lhs",
                  172);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 173);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 173);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 173);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 173);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 173);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 173);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 173);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 173);
  sf_mex_assign(&c2_rhs173, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs173, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs173), "rhs", "rhs",
                  173);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs173), "lhs", "lhs",
                  173);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 174);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("max"), "name", "name", 174);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 174);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "resolved",
                  "resolved", 174);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311255316U), "fileTimeLo",
                  "fileTimeLo", 174);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 174);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 174);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 174);
  sf_mex_assign(&c2_rhs174, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs174, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs174), "rhs", "rhs",
                  174);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs174), "lhs", "lhs",
                  174);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "context",
                  "context", 175);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 175);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 175);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 175);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378295984U), "fileTimeLo",
                  "fileTimeLo", 175);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 175);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 175);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 175);
  sf_mex_assign(&c2_rhs175, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs175, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs175), "rhs", "rhs",
                  175);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs175), "lhs", "lhs",
                  175);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 176);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("sqrt"), "name", "name", 176);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 176);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "resolved",
                  "resolved", 176);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 176);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 176);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 176);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 176);
  sf_mex_assign(&c2_rhs176, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs176, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs176), "rhs", "rhs",
                  176);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs176), "lhs", "lhs",
                  176);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 177);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_error"), "name", "name",
                  177);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 177);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 177);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830358U), "fileTimeLo",
                  "fileTimeLo", 177);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 177);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 177);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 177);
  sf_mex_assign(&c2_rhs177, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs177, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs177), "rhs", "rhs",
                  177);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs177), "lhs", "lhs",
                  177);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 178);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_sqrt"), "name",
                  "name", 178);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 178);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m"),
                  "resolved", "resolved", 178);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818738U), "fileTimeLo",
                  "fileTimeLo", 178);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 178);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 178);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 178);
  sf_mex_assign(&c2_rhs178, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs178, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs178), "rhs", "rhs",
                  178);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs178), "lhs", "lhs",
                  178);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 179);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 179);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 179);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 179);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311255318U), "fileTimeLo",
                  "fileTimeLo", 179);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 179);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 179);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 179);
  sf_mex_assign(&c2_rhs179, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs179, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs179), "rhs", "rhs",
                  179);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs179), "lhs", "lhs",
                  179);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 180);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 180);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 180);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 180);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 180);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 180);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 180);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 180);
  sf_mex_assign(&c2_rhs180, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs180, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs180), "rhs", "rhs",
                  180);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs180), "lhs", "lhs",
                  180);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 181);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 181);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 181);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 181);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 181);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 181);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 181);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 181);
  sf_mex_assign(&c2_rhs181, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs181, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs181), "rhs", "rhs",
                  181);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs181), "lhs", "lhs",
                  181);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 182);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_matlab_zlarfg"), "name",
                  "name", 182);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 182);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zlarfg.m"),
                  "resolved", "resolved", 182);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818822U), "fileTimeLo",
                  "fileTimeLo", 182);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 182);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 182);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 182);
  sf_mex_assign(&c2_rhs182, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs182, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs182), "rhs", "rhs",
                  182);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs182), "lhs", "lhs",
                  182);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 183);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_dlanv2"), "name", "name",
                  183);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 183);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlanv2.m"), "resolved",
                  "resolved", 183);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818698U), "fileTimeLo",
                  "fileTimeLo", 183);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 183);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 183);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 183);
  sf_mex_assign(&c2_rhs183, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs183, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs183), "rhs", "rhs",
                  183);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs183), "lhs", "lhs",
                  183);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlanv2.m"), "context",
                  "context", 184);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 184);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 184);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 184);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 184);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 184);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 184);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 184);
  sf_mex_assign(&c2_rhs184, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs184, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs184), "rhs", "rhs",
                  184);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs184), "lhs", "lhs",
                  184);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlanv2.m"), "context",
                  "context", 185);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 185);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 185);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 185);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 185);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 185);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 185);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 185);
  sf_mex_assign(&c2_rhs185, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs185, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs185), "rhs", "rhs",
                  185);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs185), "lhs", "lhs",
                  185);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlanv2.m"), "context",
                  "context", 186);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("max"), "name", "name", 186);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 186);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "resolved",
                  "resolved", 186);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311255316U), "fileTimeLo",
                  "fileTimeLo", 186);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 186);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 186);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 186);
  sf_mex_assign(&c2_rhs186, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs186, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs186), "rhs", "rhs",
                  186);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs186), "lhs", "lhs",
                  186);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlanv2.m"), "context",
                  "context", 187);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 187);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 187);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 187);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311255318U), "fileTimeLo",
                  "fileTimeLo", 187);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 187);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 187);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 187);
  sf_mex_assign(&c2_rhs187, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs187, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs187), "rhs", "rhs",
                  187);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs187), "lhs", "lhs",
                  187);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlanv2.m"), "context",
                  "context", 188);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mrdivide"), "name", "name",
                  188);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 188);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 188);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 188);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 188);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 188);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 188);
  sf_mex_assign(&c2_rhs188, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs188, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs188), "rhs", "rhs",
                  188);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs188), "lhs", "lhs",
                  188);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlanv2.m"), "context",
                  "context", 189);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eps"), "name", "name", 189);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 189);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 189);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 189);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 189);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 189);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 189);
  sf_mex_assign(&c2_rhs189, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs189, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs189), "rhs", "rhs",
                  189);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs189), "lhs", "lhs",
                  189);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlanv2.m"), "context",
                  "context", 190);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("sqrt"), "name", "name", 190);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 190);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "resolved",
                  "resolved", 190);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 190);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 190);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 190);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 190);
  sf_mex_assign(&c2_rhs190, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs190, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs190), "rhs", "rhs",
                  190);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs190), "lhs", "lhs",
                  190);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlanv2.m"), "context",
                  "context", 191);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_dlapy2"), "name", "name",
                  191);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 191);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlapy2.m"), "resolved",
                  "resolved", 191);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1350410654U), "fileTimeLo",
                  "fileTimeLo", 191);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 191);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 191);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 191);
  sf_mex_assign(&c2_rhs191, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs191, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs191), "rhs", "rhs",
                  191);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs191), "lhs", "lhs",
                  191);
  sf_mex_destroy(&c2_rhs128);
  sf_mex_destroy(&c2_lhs128);
  sf_mex_destroy(&c2_rhs129);
  sf_mex_destroy(&c2_lhs129);
  sf_mex_destroy(&c2_rhs130);
  sf_mex_destroy(&c2_lhs130);
  sf_mex_destroy(&c2_rhs131);
  sf_mex_destroy(&c2_lhs131);
  sf_mex_destroy(&c2_rhs132);
  sf_mex_destroy(&c2_lhs132);
  sf_mex_destroy(&c2_rhs133);
  sf_mex_destroy(&c2_lhs133);
  sf_mex_destroy(&c2_rhs134);
  sf_mex_destroy(&c2_lhs134);
  sf_mex_destroy(&c2_rhs135);
  sf_mex_destroy(&c2_lhs135);
  sf_mex_destroy(&c2_rhs136);
  sf_mex_destroy(&c2_lhs136);
  sf_mex_destroy(&c2_rhs137);
  sf_mex_destroy(&c2_lhs137);
  sf_mex_destroy(&c2_rhs138);
  sf_mex_destroy(&c2_lhs138);
  sf_mex_destroy(&c2_rhs139);
  sf_mex_destroy(&c2_lhs139);
  sf_mex_destroy(&c2_rhs140);
  sf_mex_destroy(&c2_lhs140);
  sf_mex_destroy(&c2_rhs141);
  sf_mex_destroy(&c2_lhs141);
  sf_mex_destroy(&c2_rhs142);
  sf_mex_destroy(&c2_lhs142);
  sf_mex_destroy(&c2_rhs143);
  sf_mex_destroy(&c2_lhs143);
  sf_mex_destroy(&c2_rhs144);
  sf_mex_destroy(&c2_lhs144);
  sf_mex_destroy(&c2_rhs145);
  sf_mex_destroy(&c2_lhs145);
  sf_mex_destroy(&c2_rhs146);
  sf_mex_destroy(&c2_lhs146);
  sf_mex_destroy(&c2_rhs147);
  sf_mex_destroy(&c2_lhs147);
  sf_mex_destroy(&c2_rhs148);
  sf_mex_destroy(&c2_lhs148);
  sf_mex_destroy(&c2_rhs149);
  sf_mex_destroy(&c2_lhs149);
  sf_mex_destroy(&c2_rhs150);
  sf_mex_destroy(&c2_lhs150);
  sf_mex_destroy(&c2_rhs151);
  sf_mex_destroy(&c2_lhs151);
  sf_mex_destroy(&c2_rhs152);
  sf_mex_destroy(&c2_lhs152);
  sf_mex_destroy(&c2_rhs153);
  sf_mex_destroy(&c2_lhs153);
  sf_mex_destroy(&c2_rhs154);
  sf_mex_destroy(&c2_lhs154);
  sf_mex_destroy(&c2_rhs155);
  sf_mex_destroy(&c2_lhs155);
  sf_mex_destroy(&c2_rhs156);
  sf_mex_destroy(&c2_lhs156);
  sf_mex_destroy(&c2_rhs157);
  sf_mex_destroy(&c2_lhs157);
  sf_mex_destroy(&c2_rhs158);
  sf_mex_destroy(&c2_lhs158);
  sf_mex_destroy(&c2_rhs159);
  sf_mex_destroy(&c2_lhs159);
  sf_mex_destroy(&c2_rhs160);
  sf_mex_destroy(&c2_lhs160);
  sf_mex_destroy(&c2_rhs161);
  sf_mex_destroy(&c2_lhs161);
  sf_mex_destroy(&c2_rhs162);
  sf_mex_destroy(&c2_lhs162);
  sf_mex_destroy(&c2_rhs163);
  sf_mex_destroy(&c2_lhs163);
  sf_mex_destroy(&c2_rhs164);
  sf_mex_destroy(&c2_lhs164);
  sf_mex_destroy(&c2_rhs165);
  sf_mex_destroy(&c2_lhs165);
  sf_mex_destroy(&c2_rhs166);
  sf_mex_destroy(&c2_lhs166);
  sf_mex_destroy(&c2_rhs167);
  sf_mex_destroy(&c2_lhs167);
  sf_mex_destroy(&c2_rhs168);
  sf_mex_destroy(&c2_lhs168);
  sf_mex_destroy(&c2_rhs169);
  sf_mex_destroy(&c2_lhs169);
  sf_mex_destroy(&c2_rhs170);
  sf_mex_destroy(&c2_lhs170);
  sf_mex_destroy(&c2_rhs171);
  sf_mex_destroy(&c2_lhs171);
  sf_mex_destroy(&c2_rhs172);
  sf_mex_destroy(&c2_lhs172);
  sf_mex_destroy(&c2_rhs173);
  sf_mex_destroy(&c2_lhs173);
  sf_mex_destroy(&c2_rhs174);
  sf_mex_destroy(&c2_lhs174);
  sf_mex_destroy(&c2_rhs175);
  sf_mex_destroy(&c2_lhs175);
  sf_mex_destroy(&c2_rhs176);
  sf_mex_destroy(&c2_lhs176);
  sf_mex_destroy(&c2_rhs177);
  sf_mex_destroy(&c2_lhs177);
  sf_mex_destroy(&c2_rhs178);
  sf_mex_destroy(&c2_lhs178);
  sf_mex_destroy(&c2_rhs179);
  sf_mex_destroy(&c2_lhs179);
  sf_mex_destroy(&c2_rhs180);
  sf_mex_destroy(&c2_lhs180);
  sf_mex_destroy(&c2_rhs181);
  sf_mex_destroy(&c2_lhs181);
  sf_mex_destroy(&c2_rhs182);
  sf_mex_destroy(&c2_lhs182);
  sf_mex_destroy(&c2_rhs183);
  sf_mex_destroy(&c2_lhs183);
  sf_mex_destroy(&c2_rhs184);
  sf_mex_destroy(&c2_lhs184);
  sf_mex_destroy(&c2_rhs185);
  sf_mex_destroy(&c2_lhs185);
  sf_mex_destroy(&c2_rhs186);
  sf_mex_destroy(&c2_lhs186);
  sf_mex_destroy(&c2_rhs187);
  sf_mex_destroy(&c2_lhs187);
  sf_mex_destroy(&c2_rhs188);
  sf_mex_destroy(&c2_lhs188);
  sf_mex_destroy(&c2_rhs189);
  sf_mex_destroy(&c2_lhs189);
  sf_mex_destroy(&c2_rhs190);
  sf_mex_destroy(&c2_lhs190);
  sf_mex_destroy(&c2_rhs191);
  sf_mex_destroy(&c2_lhs191);
}

static void c2_d_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs192 = NULL;
  const mxArray *c2_lhs192 = NULL;
  const mxArray *c2_rhs193 = NULL;
  const mxArray *c2_lhs193 = NULL;
  const mxArray *c2_rhs194 = NULL;
  const mxArray *c2_lhs194 = NULL;
  const mxArray *c2_rhs195 = NULL;
  const mxArray *c2_lhs195 = NULL;
  const mxArray *c2_rhs196 = NULL;
  const mxArray *c2_lhs196 = NULL;
  const mxArray *c2_rhs197 = NULL;
  const mxArray *c2_lhs197 = NULL;
  const mxArray *c2_rhs198 = NULL;
  const mxArray *c2_lhs198 = NULL;
  const mxArray *c2_rhs199 = NULL;
  const mxArray *c2_lhs199 = NULL;
  const mxArray *c2_rhs200 = NULL;
  const mxArray *c2_lhs200 = NULL;
  const mxArray *c2_rhs201 = NULL;
  const mxArray *c2_lhs201 = NULL;
  const mxArray *c2_rhs202 = NULL;
  const mxArray *c2_lhs202 = NULL;
  const mxArray *c2_rhs203 = NULL;
  const mxArray *c2_lhs203 = NULL;
  const mxArray *c2_rhs204 = NULL;
  const mxArray *c2_lhs204 = NULL;
  const mxArray *c2_rhs205 = NULL;
  const mxArray *c2_lhs205 = NULL;
  const mxArray *c2_rhs206 = NULL;
  const mxArray *c2_lhs206 = NULL;
  const mxArray *c2_rhs207 = NULL;
  const mxArray *c2_lhs207 = NULL;
  const mxArray *c2_rhs208 = NULL;
  const mxArray *c2_lhs208 = NULL;
  const mxArray *c2_rhs209 = NULL;
  const mxArray *c2_lhs209 = NULL;
  const mxArray *c2_rhs210 = NULL;
  const mxArray *c2_lhs210 = NULL;
  const mxArray *c2_rhs211 = NULL;
  const mxArray *c2_lhs211 = NULL;
  const mxArray *c2_rhs212 = NULL;
  const mxArray *c2_lhs212 = NULL;
  const mxArray *c2_rhs213 = NULL;
  const mxArray *c2_lhs213 = NULL;
  const mxArray *c2_rhs214 = NULL;
  const mxArray *c2_lhs214 = NULL;
  const mxArray *c2_rhs215 = NULL;
  const mxArray *c2_lhs215 = NULL;
  const mxArray *c2_rhs216 = NULL;
  const mxArray *c2_lhs216 = NULL;
  const mxArray *c2_rhs217 = NULL;
  const mxArray *c2_lhs217 = NULL;
  const mxArray *c2_rhs218 = NULL;
  const mxArray *c2_lhs218 = NULL;
  const mxArray *c2_rhs219 = NULL;
  const mxArray *c2_lhs219 = NULL;
  const mxArray *c2_rhs220 = NULL;
  const mxArray *c2_lhs220 = NULL;
  const mxArray *c2_rhs221 = NULL;
  const mxArray *c2_lhs221 = NULL;
  const mxArray *c2_rhs222 = NULL;
  const mxArray *c2_lhs222 = NULL;
  const mxArray *c2_rhs223 = NULL;
  const mxArray *c2_lhs223 = NULL;
  const mxArray *c2_rhs224 = NULL;
  const mxArray *c2_lhs224 = NULL;
  const mxArray *c2_rhs225 = NULL;
  const mxArray *c2_lhs225 = NULL;
  const mxArray *c2_rhs226 = NULL;
  const mxArray *c2_lhs226 = NULL;
  const mxArray *c2_rhs227 = NULL;
  const mxArray *c2_lhs227 = NULL;
  const mxArray *c2_rhs228 = NULL;
  const mxArray *c2_lhs228 = NULL;
  const mxArray *c2_rhs229 = NULL;
  const mxArray *c2_lhs229 = NULL;
  const mxArray *c2_rhs230 = NULL;
  const mxArray *c2_lhs230 = NULL;
  const mxArray *c2_rhs231 = NULL;
  const mxArray *c2_lhs231 = NULL;
  const mxArray *c2_rhs232 = NULL;
  const mxArray *c2_lhs232 = NULL;
  const mxArray *c2_rhs233 = NULL;
  const mxArray *c2_lhs233 = NULL;
  const mxArray *c2_rhs234 = NULL;
  const mxArray *c2_lhs234 = NULL;
  const mxArray *c2_rhs235 = NULL;
  const mxArray *c2_lhs235 = NULL;
  const mxArray *c2_rhs236 = NULL;
  const mxArray *c2_lhs236 = NULL;
  const mxArray *c2_rhs237 = NULL;
  const mxArray *c2_lhs237 = NULL;
  const mxArray *c2_rhs238 = NULL;
  const mxArray *c2_lhs238 = NULL;
  const mxArray *c2_rhs239 = NULL;
  const mxArray *c2_lhs239 = NULL;
  const mxArray *c2_rhs240 = NULL;
  const mxArray *c2_lhs240 = NULL;
  const mxArray *c2_rhs241 = NULL;
  const mxArray *c2_lhs241 = NULL;
  const mxArray *c2_rhs242 = NULL;
  const mxArray *c2_lhs242 = NULL;
  const mxArray *c2_rhs243 = NULL;
  const mxArray *c2_lhs243 = NULL;
  const mxArray *c2_rhs244 = NULL;
  const mxArray *c2_lhs244 = NULL;
  const mxArray *c2_rhs245 = NULL;
  const mxArray *c2_lhs245 = NULL;
  const mxArray *c2_rhs246 = NULL;
  const mxArray *c2_lhs246 = NULL;
  const mxArray *c2_rhs247 = NULL;
  const mxArray *c2_lhs247 = NULL;
  const mxArray *c2_rhs248 = NULL;
  const mxArray *c2_lhs248 = NULL;
  const mxArray *c2_rhs249 = NULL;
  const mxArray *c2_lhs249 = NULL;
  const mxArray *c2_rhs250 = NULL;
  const mxArray *c2_lhs250 = NULL;
  const mxArray *c2_rhs251 = NULL;
  const mxArray *c2_lhs251 = NULL;
  const mxArray *c2_rhs252 = NULL;
  const mxArray *c2_lhs252 = NULL;
  const mxArray *c2_rhs253 = NULL;
  const mxArray *c2_lhs253 = NULL;
  const mxArray *c2_rhs254 = NULL;
  const mxArray *c2_lhs254 = NULL;
  const mxArray *c2_rhs255 = NULL;
  const mxArray *c2_lhs255 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m!eml_dlahqr"),
                  "context", "context", 192);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xrot"), "name", "name",
                  192);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 192);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xrot.m"), "resolved",
                  "resolved", 192);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980692U), "fileTimeLo",
                  "fileTimeLo", 192);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 192);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 192);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 192);
  sf_mex_assign(&c2_rhs192, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs192, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs192), "rhs", "rhs",
                  192);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs192), "lhs", "lhs",
                  192);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xrot.m"), "context",
                  "context", 193);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 193);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 193);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 193);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 193);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 193);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 193);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 193);
  sf_mex_assign(&c2_rhs193, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs193, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs193), "rhs", "rhs",
                  193);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs193), "lhs", "lhs",
                  193);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xrot.m"), "context",
                  "context", 194);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xrot"),
                  "name", "name", 194);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 194);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xrot.p"),
                  "resolved", "resolved", 194);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 194);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 194);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 194);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 194);
  sf_mex_assign(&c2_rhs194, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs194, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs194), "rhs", "rhs",
                  194);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs194), "lhs", "lhs",
                  194);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xrot.p"),
                  "context", "context", 195);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 195);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 195);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 195);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 195);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 195);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 195);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 195);
  sf_mex_assign(&c2_rhs195, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs195, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs195), "rhs", "rhs",
                  195);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs195), "lhs", "lhs",
                  195);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xrot.p!below_threshold"),
                  "context", "context", 196);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 196);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 196);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 196);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 196);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 196);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 196);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 196);
  sf_mex_assign(&c2_rhs196, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs196, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs196), "rhs", "rhs",
                  196);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs196), "lhs", "lhs",
                  196);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xrot.p!below_threshold"),
                  "context", "context", 197);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("length"), "name", "name", 197);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 197);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 197);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1303146206U), "fileTimeLo",
                  "fileTimeLo", 197);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 197);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 197);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 197);
  sf_mex_assign(&c2_rhs197, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs197, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs197), "rhs", "rhs",
                  197);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs197), "lhs", "lhs",
                  197);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xrot.p"),
                  "context", "context", 198);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 198);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 198);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 198);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 198);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 198);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 198);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 198);
  sf_mex_assign(&c2_rhs198, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs198, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs198), "rhs", "rhs",
                  198);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs198), "lhs", "lhs",
                  198);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xrot.p"),
                  "context", "context", 199);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xrot"),
                  "name", "name", 199);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 199);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xrot.p"),
                  "resolved", "resolved", 199);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 199);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 199);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 199);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 199);
  sf_mex_assign(&c2_rhs199, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs199, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs199), "rhs", "rhs",
                  199);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs199), "lhs", "lhs",
                  199);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xrot.p"),
                  "context", "context", 200);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 200);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 200);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 200);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 200);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 200);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 200);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 200);
  sf_mex_assign(&c2_rhs200, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs200, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs200), "rhs", "rhs",
                  200);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs200), "lhs", "lhs",
                  200);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xrot.p"),
                  "context", "context", 201);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 201);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 201);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 201);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 201);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 201);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 201);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 201);
  sf_mex_assign(&c2_rhs201, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs201, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs201), "rhs", "rhs",
                  201);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs201), "lhs", "lhs",
                  201);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_dhseqr.m"),
                  "context", "context", 202);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("triu"), "name", "name", 202);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 202);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/triu.m"), "resolved",
                  "resolved", 202);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713864U), "fileTimeLo",
                  "fileTimeLo", 202);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 202);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 202);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 202);
  sf_mex_assign(&c2_rhs202, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs202, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs202), "rhs", "rhs",
                  202);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs202), "lhs", "lhs",
                  202);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/triu.m"), "context",
                  "context", 203);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 203);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 203);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 203);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 203);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 203);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 203);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 203);
  sf_mex_assign(&c2_rhs203, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs203, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs203), "rhs", "rhs",
                  203);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs203), "lhs", "lhs",
                  203);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/triu.m"), "context",
                  "context", 204);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 204);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 204);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 204);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 204);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 204);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 204);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 204);
  sf_mex_assign(&c2_rhs204, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs204, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs204), "rhs", "rhs",
                  204);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs204), "lhs", "lhs",
                  204);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/triu.m"), "context",
                  "context", 205);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 205);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 205);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 205);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 205);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 205);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 205);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 205);
  sf_mex_assign(&c2_rhs205, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs205, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs205), "rhs", "rhs",
                  205);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs205), "lhs", "lhs",
                  205);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 206);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 206);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 206);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 206);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 206);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 206);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 206);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 206);
  sf_mex_assign(&c2_rhs206, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs206, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs206), "rhs", "rhs",
                  206);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs206), "lhs", "lhs",
                  206);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 207);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 207);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 207);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 207);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 207);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 207);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 207);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 207);
  sf_mex_assign(&c2_rhs207, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs207, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs207), "rhs", "rhs",
                  207);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs207), "lhs", "lhs",
                  207);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/schur.m"), "context",
                  "context", 208);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("rsf2csf"), "name", "name", 208);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 208);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/rsf2csf.m"), "resolved",
                  "resolved", 208);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818832U), "fileTimeLo",
                  "fileTimeLo", 208);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 208);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 208);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 208);
  sf_mex_assign(&c2_rhs208, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs208, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs208), "rhs", "rhs",
                  208);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs208), "lhs", "lhs",
                  208);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/rsf2csf.m"), "context",
                  "context", 209);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_rsf2csf"), "name", "name",
                  209);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 209);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rsf2csf.m"), "resolved",
                  "resolved", 209);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1360282350U), "fileTimeLo",
                  "fileTimeLo", 209);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 209);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 209);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 209);
  sf_mex_assign(&c2_rhs209, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs209, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs209), "rhs", "rhs",
                  209);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs209), "lhs", "lhs",
                  209);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rsf2csf.m"), "context",
                  "context", 210);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 210);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 210);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 210);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311255318U), "fileTimeLo",
                  "fileTimeLo", 210);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 210);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 210);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 210);
  sf_mex_assign(&c2_rhs210, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs210, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs210), "rhs", "rhs",
                  210);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs210), "lhs", "lhs",
                  210);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum"),
                  "context", "context", 211);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_const_nonsingleton_dim"),
                  "name", "name", 211);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 211);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m"),
                  "resolved", "resolved", 211);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 211);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 211);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 211);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 211);
  sf_mex_assign(&c2_rhs211, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs211, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs211), "rhs", "rhs",
                  211);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs211), "lhs", "lhs",
                  211);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m"),
                  "context", "context", 212);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.constNonSingletonDim"), "name", "name", 212);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 212);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/constNonSingletonDim.m"),
                  "resolved", "resolved", 212);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 212);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 212);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 212);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 212);
  sf_mex_assign(&c2_rhs212, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs212, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs212), "rhs", "rhs",
                  212);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs212), "lhs", "lhs",
                  212);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum"),
                  "context", "context", 213);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 213);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 213);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 213);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 213);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 213);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 213);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 213);
  sf_mex_assign(&c2_rhs213, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs213, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs213), "rhs", "rhs",
                  213);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs213), "lhs", "lhs",
                  213);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum"),
                  "context", "context", 214);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 214);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 214);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 214);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 214);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 214);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 214);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 214);
  sf_mex_assign(&c2_rhs214, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs214, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs214), "rhs", "rhs",
                  214);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs214), "lhs", "lhs",
                  214);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub"),
                  "context", "context", 215);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 215);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 215);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 215);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 215);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 215);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 215);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 215);
  sf_mex_assign(&c2_rhs215, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs215, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs215), "rhs", "rhs",
                  215);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs215), "lhs", "lhs",
                  215);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub"),
                  "context", "context", 216);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnan"), "name", "name", 216);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 216);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 216);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713858U), "fileTimeLo",
                  "fileTimeLo", 216);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 216);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 216);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 216);
  sf_mex_assign(&c2_rhs216, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs216, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs216), "rhs", "rhs",
                  216);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs216), "lhs", "lhs",
                  216);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "context",
                  "context", 217);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 217);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 217);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 217);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 217);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 217);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 217);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 217);
  sf_mex_assign(&c2_rhs217, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs217, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs217), "rhs", "rhs",
                  217);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs217), "lhs", "lhs",
                  217);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub"),
                  "context", "context", 218);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 218);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 218);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 218);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 218);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 218);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 218);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 218);
  sf_mex_assign(&c2_rhs218, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs218, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs218), "rhs", "rhs",
                  218);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs218), "lhs", "lhs",
                  218);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub"),
                  "context", "context", 219);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 219);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 219);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 219);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 219);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 219);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 219);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 219);
  sf_mex_assign(&c2_rhs219, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs219, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs219), "rhs", "rhs",
                  219);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs219), "lhs", "lhs",
                  219);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub"),
                  "context", "context", 220);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_relop"), "name", "name",
                  220);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("function_handle"),
                  "dominantType", "dominantType", 220);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_relop.m"), "resolved",
                  "resolved", 220);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1342451182U), "fileTimeLo",
                  "fileTimeLo", 220);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 220);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 220);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 220);
  sf_mex_assign(&c2_rhs220, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs220, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs220), "rhs", "rhs",
                  220);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs220), "lhs", "lhs",
                  220);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rsf2csf.m"), "context",
                  "context", 221);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 221);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 221);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 221);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 221);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 221);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 221);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 221);
  sf_mex_assign(&c2_rhs221, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs221, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs221), "rhs", "rhs",
                  221);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs221), "lhs", "lhs",
                  221);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rsf2csf.m"), "context",
                  "context", 222);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 222);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 222);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 222);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 222);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 222);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 222);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 222);
  sf_mex_assign(&c2_rhs222, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs222, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs222), "rhs", "rhs",
                  222);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs222), "lhs", "lhs",
                  222);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rsf2csf.m"), "context",
                  "context", 223);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_dlanv2"), "name", "name",
                  223);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 223);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlanv2.m"), "resolved",
                  "resolved", 223);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818698U), "fileTimeLo",
                  "fileTimeLo", 223);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 223);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 223);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 223);
  sf_mex_assign(&c2_rhs223, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs223, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs223), "rhs", "rhs",
                  223);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs223), "lhs", "lhs",
                  223);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rsf2csf.m"), "context",
                  "context", 224);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("hypot"), "name", "name", 224);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 224);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/hypot.m"), "resolved",
                  "resolved", 224);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830380U), "fileTimeLo",
                  "fileTimeLo", 224);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 224);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 224);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 224);
  sf_mex_assign(&c2_rhs224, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs224, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs224), "rhs", "rhs",
                  224);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs224), "lhs", "lhs",
                  224);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/hypot.m"), "context",
                  "context", 225);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 225);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 225);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 225);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 225);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 225);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 225);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 225);
  sf_mex_assign(&c2_rhs225, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs225, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs225), "rhs", "rhs",
                  225);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs225), "lhs", "lhs",
                  225);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/hypot.m"), "context",
                  "context", 226);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 226);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 226);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 226);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 226);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 226);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 226);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 226);
  sf_mex_assign(&c2_rhs226, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs226, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs226), "rhs", "rhs",
                  226);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs226), "lhs", "lhs",
                  226);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/hypot.m"), "context",
                  "context", 227);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_hypot"), "name",
                  "name", 227);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 227);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_hypot.m"),
                  "resolved", "resolved", 227);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 227);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 227);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 227);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 227);
  sf_mex_assign(&c2_rhs227, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs227, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs227), "rhs", "rhs",
                  227);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs227), "lhs", "lhs",
                  227);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_hypot.m"),
                  "context", "context", 228);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 228);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 228);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 228);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 228);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 228);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 228);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 228);
  sf_mex_assign(&c2_rhs228, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs228, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs228), "rhs", "rhs",
                  228);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs228), "lhs", "lhs",
                  228);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_hypot.m"),
                  "context", "context", 229);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_dlapy2"), "name", "name",
                  229);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 229);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlapy2.m"), "resolved",
                  "resolved", 229);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1350410654U), "fileTimeLo",
                  "fileTimeLo", 229);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 229);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 229);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 229);
  sf_mex_assign(&c2_rhs229, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs229, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs229), "rhs", "rhs",
                  229);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs229), "lhs", "lhs",
                  229);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rsf2csf.m"), "context",
                  "context", 230);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mrdivide"), "name", "name",
                  230);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 230);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 230);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 230);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 230);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 230);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 230);
  sf_mex_assign(&c2_rhs230, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs230, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs230), "rhs", "rhs",
                  230);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs230), "lhs", "lhs",
                  230);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p!eml_fldiv"),
                  "context", "context", 231);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 231);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 231);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 231);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 231);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 231);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 231);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 231);
  sf_mex_assign(&c2_rhs231, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs231, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs231), "rhs", "rhs",
                  231);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs231), "lhs", "lhs",
                  231);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p!eml_fldiv"),
                  "context", "context", 232);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 232);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 232);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 232);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 232);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 232);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 232);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 232);
  sf_mex_assign(&c2_rhs232, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs232, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs232), "rhs", "rhs",
                  232);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs232), "lhs", "lhs",
                  232);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p!eml_fldiv"),
                  "context", "context", 233);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 233);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 233);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 233);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 233);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 233);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 233);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 233);
  sf_mex_assign(&c2_rhs233, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs233, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs233), "rhs", "rhs",
                  233);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs233), "lhs", "lhs",
                  233);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rsf2csf.m"), "context",
                  "context", 234);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 234);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 234);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 234);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 234);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 234);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 234);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 234);
  sf_mex_assign(&c2_rhs234, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs234, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs234), "rhs", "rhs",
                  234);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs234), "lhs", "lhs",
                  234);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rsf2csf.m"), "context",
                  "context", 235);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.conjtimes"),
                  "name", "name", 235);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 235);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/conjtimes.m"),
                  "resolved", "resolved", 235);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1360282586U), "fileTimeLo",
                  "fileTimeLo", 235);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 235);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 235);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 235);
  sf_mex_assign(&c2_rhs235, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs235, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs235), "rhs", "rhs",
                  235);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs235), "lhs", "lhs",
                  235);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_rsf2csf.m"), "context",
                  "context", 236);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 236);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 236);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 236);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 236);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 236);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 236);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 236);
  sf_mex_assign(&c2_rhs236, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs236, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs236), "rhs", "rhs",
                  236);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs236), "lhs", "lhs",
                  236);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 237);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 237);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 237);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 237);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 237);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 237);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 237);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 237);
  sf_mex_assign(&c2_rhs237, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs237, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs237), "rhs", "rhs",
                  237);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs237), "lhs", "lhs",
                  237);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/schur.m"), "context",
                  "context", 238);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_warning"), "name", "name",
                  238);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 238);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m"), "resolved",
                  "resolved", 238);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818802U), "fileTimeLo",
                  "fileTimeLo", 238);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 238);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 238);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 238);
  sf_mex_assign(&c2_rhs238, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs238, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs238), "rhs", "rhs",
                  238);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs238), "lhs", "lhs",
                  238);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 239);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 239);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 239);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 239);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 239);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 239);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 239);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 239);
  sf_mex_assign(&c2_rhs239, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs239, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs239), "rhs", "rhs",
                  239);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs239), "lhs", "lhs",
                  239);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 240);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 240);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 240);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 240);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 240);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 240);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 240);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 240);
  sf_mex_assign(&c2_rhs240, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs240, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs240), "rhs", "rhs",
                  240);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs240), "lhs", "lhs",
                  240);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m!isUTmatD"),
                  "context", "context", 241);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 241);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 241);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 241);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 241);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 241);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 241);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 241);
  sf_mex_assign(&c2_rhs241, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs241, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs241), "rhs", "rhs",
                  241);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs241), "lhs", "lhs",
                  241);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m!isUTmatD"),
                  "context", "context", 242);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 242);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 242);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 242);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 242);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 242);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 242);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 242);
  sf_mex_assign(&c2_rhs242, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs242, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs242), "rhs", "rhs",
                  242);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs242), "lhs", "lhs",
                  242);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m!isUTmatD"),
                  "context", "context", 243);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 243);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 243);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 243);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 243);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 243);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 243);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 243);
  sf_mex_assign(&c2_rhs243, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs243, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs243), "rhs", "rhs",
                  243);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs243), "lhs", "lhs",
                  243);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 244);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 244);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 244);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 244);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 244);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 244);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 244);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 244);
  sf_mex_assign(&c2_rhs244, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs244, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs244), "rhs", "rhs",
                  244);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs244), "lhs", "lhs",
                  244);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 245);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("sqrt"), "name", "name", 245);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 245);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "resolved",
                  "resolved", 245);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 245);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 245);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 245);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 245);
  sf_mex_assign(&c2_rhs245, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs245, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs245), "rhs", "rhs",
                  245);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs245), "lhs", "lhs",
                  245);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m!eml_complex_scalar_sqrt"),
                  "context", "context", 246);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("rdivide"), "name", "name", 246);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 246);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 246);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 246);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 246);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 246);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 246);
  sf_mex_assign(&c2_rhs246, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs246, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs246), "rhs", "rhs",
                  246);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs246), "lhs", "lhs",
                  246);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m!eml_complex_scalar_sqrt"),
                  "context", "context", 247);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnan"), "name", "name", 247);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 247);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 247);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713858U), "fileTimeLo",
                  "fileTimeLo", 247);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 247);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 247);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 247);
  sf_mex_assign(&c2_rhs247, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs247, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs247), "rhs", "rhs",
                  247);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs247), "lhs", "lhs",
                  247);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m!eml_complex_scalar_sqrt"),
                  "context", "context", 248);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_guarded_nan"), "name",
                  "name", 248);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 248);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m"),
                  "resolved", "resolved", 248);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818776U), "fileTimeLo",
                  "fileTimeLo", 248);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 248);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 248);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 248);
  sf_mex_assign(&c2_rhs248, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs248, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs248), "rhs", "rhs",
                  248);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs248), "lhs", "lhs",
                  248);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m"),
                  "context", "context", 249);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_is_float_class"), "name",
                  "name", 249);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 249);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m"),
                  "resolved", "resolved", 249);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818782U), "fileTimeLo",
                  "fileTimeLo", 249);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 249);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 249);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 249);
  sf_mex_assign(&c2_rhs249, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs249, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs249), "rhs", "rhs",
                  249);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs249), "lhs", "lhs",
                  249);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m!eml_complex_scalar_sqrt"),
                  "context", "context", 250);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isinf"), "name", "name", 250);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 250);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m"), "resolved",
                  "resolved", 250);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713856U), "fileTimeLo",
                  "fileTimeLo", 250);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 250);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 250);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 250);
  sf_mex_assign(&c2_rhs250, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs250, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs250), "rhs", "rhs",
                  250);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs250), "lhs", "lhs",
                  250);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m"), "context",
                  "context", 251);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 251);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 251);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 251);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 251);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 251);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 251);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 251);
  sf_mex_assign(&c2_rhs251, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs251, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs251), "rhs", "rhs",
                  251);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs251), "lhs", "lhs",
                  251);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m!eml_complex_scalar_sqrt"),
                  "context", "context", 252);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_guarded_inf"), "name",
                  "name", 252);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 252);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_inf.m"),
                  "resolved", "resolved", 252);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818776U), "fileTimeLo",
                  "fileTimeLo", 252);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 252);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 252);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 252);
  sf_mex_assign(&c2_rhs252, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs252, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs252), "rhs", "rhs",
                  252);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs252), "lhs", "lhs",
                  252);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_inf.m"),
                  "context", "context", 253);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_is_float_class"), "name",
                  "name", 253);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 253);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m"),
                  "resolved", "resolved", 253);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818782U), "fileTimeLo",
                  "fileTimeLo", 253);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 253);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 253);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 253);
  sf_mex_assign(&c2_rhs253, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs253, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs253), "rhs", "rhs",
                  253);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs253), "lhs", "lhs",
                  253);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m!eml_complex_scalar_sqrt"),
                  "context", "context", 254);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("realmax"), "name", "name", 254);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 254);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m"), "resolved",
                  "resolved", 254);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1307651242U), "fileTimeLo",
                  "fileTimeLo", 254);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 254);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 254);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 254);
  sf_mex_assign(&c2_rhs254, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs254, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs254), "rhs", "rhs",
                  254);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs254), "lhs", "lhs",
                  254);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m"), "context",
                  "context", 255);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_realmax"), "name", "name",
                  255);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 255);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m"), "resolved",
                  "resolved", 255);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 255);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 255);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 255);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 255);
  sf_mex_assign(&c2_rhs255, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs255, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs255), "rhs", "rhs",
                  255);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs255), "lhs", "lhs",
                  255);
  sf_mex_destroy(&c2_rhs192);
  sf_mex_destroy(&c2_lhs192);
  sf_mex_destroy(&c2_rhs193);
  sf_mex_destroy(&c2_lhs193);
  sf_mex_destroy(&c2_rhs194);
  sf_mex_destroy(&c2_lhs194);
  sf_mex_destroy(&c2_rhs195);
  sf_mex_destroy(&c2_lhs195);
  sf_mex_destroy(&c2_rhs196);
  sf_mex_destroy(&c2_lhs196);
  sf_mex_destroy(&c2_rhs197);
  sf_mex_destroy(&c2_lhs197);
  sf_mex_destroy(&c2_rhs198);
  sf_mex_destroy(&c2_lhs198);
  sf_mex_destroy(&c2_rhs199);
  sf_mex_destroy(&c2_lhs199);
  sf_mex_destroy(&c2_rhs200);
  sf_mex_destroy(&c2_lhs200);
  sf_mex_destroy(&c2_rhs201);
  sf_mex_destroy(&c2_lhs201);
  sf_mex_destroy(&c2_rhs202);
  sf_mex_destroy(&c2_lhs202);
  sf_mex_destroy(&c2_rhs203);
  sf_mex_destroy(&c2_lhs203);
  sf_mex_destroy(&c2_rhs204);
  sf_mex_destroy(&c2_lhs204);
  sf_mex_destroy(&c2_rhs205);
  sf_mex_destroy(&c2_lhs205);
  sf_mex_destroy(&c2_rhs206);
  sf_mex_destroy(&c2_lhs206);
  sf_mex_destroy(&c2_rhs207);
  sf_mex_destroy(&c2_lhs207);
  sf_mex_destroy(&c2_rhs208);
  sf_mex_destroy(&c2_lhs208);
  sf_mex_destroy(&c2_rhs209);
  sf_mex_destroy(&c2_lhs209);
  sf_mex_destroy(&c2_rhs210);
  sf_mex_destroy(&c2_lhs210);
  sf_mex_destroy(&c2_rhs211);
  sf_mex_destroy(&c2_lhs211);
  sf_mex_destroy(&c2_rhs212);
  sf_mex_destroy(&c2_lhs212);
  sf_mex_destroy(&c2_rhs213);
  sf_mex_destroy(&c2_lhs213);
  sf_mex_destroy(&c2_rhs214);
  sf_mex_destroy(&c2_lhs214);
  sf_mex_destroy(&c2_rhs215);
  sf_mex_destroy(&c2_lhs215);
  sf_mex_destroy(&c2_rhs216);
  sf_mex_destroy(&c2_lhs216);
  sf_mex_destroy(&c2_rhs217);
  sf_mex_destroy(&c2_lhs217);
  sf_mex_destroy(&c2_rhs218);
  sf_mex_destroy(&c2_lhs218);
  sf_mex_destroy(&c2_rhs219);
  sf_mex_destroy(&c2_lhs219);
  sf_mex_destroy(&c2_rhs220);
  sf_mex_destroy(&c2_lhs220);
  sf_mex_destroy(&c2_rhs221);
  sf_mex_destroy(&c2_lhs221);
  sf_mex_destroy(&c2_rhs222);
  sf_mex_destroy(&c2_lhs222);
  sf_mex_destroy(&c2_rhs223);
  sf_mex_destroy(&c2_lhs223);
  sf_mex_destroy(&c2_rhs224);
  sf_mex_destroy(&c2_lhs224);
  sf_mex_destroy(&c2_rhs225);
  sf_mex_destroy(&c2_lhs225);
  sf_mex_destroy(&c2_rhs226);
  sf_mex_destroy(&c2_lhs226);
  sf_mex_destroy(&c2_rhs227);
  sf_mex_destroy(&c2_lhs227);
  sf_mex_destroy(&c2_rhs228);
  sf_mex_destroy(&c2_lhs228);
  sf_mex_destroy(&c2_rhs229);
  sf_mex_destroy(&c2_lhs229);
  sf_mex_destroy(&c2_rhs230);
  sf_mex_destroy(&c2_lhs230);
  sf_mex_destroy(&c2_rhs231);
  sf_mex_destroy(&c2_lhs231);
  sf_mex_destroy(&c2_rhs232);
  sf_mex_destroy(&c2_lhs232);
  sf_mex_destroy(&c2_rhs233);
  sf_mex_destroy(&c2_lhs233);
  sf_mex_destroy(&c2_rhs234);
  sf_mex_destroy(&c2_lhs234);
  sf_mex_destroy(&c2_rhs235);
  sf_mex_destroy(&c2_lhs235);
  sf_mex_destroy(&c2_rhs236);
  sf_mex_destroy(&c2_lhs236);
  sf_mex_destroy(&c2_rhs237);
  sf_mex_destroy(&c2_lhs237);
  sf_mex_destroy(&c2_rhs238);
  sf_mex_destroy(&c2_lhs238);
  sf_mex_destroy(&c2_rhs239);
  sf_mex_destroy(&c2_lhs239);
  sf_mex_destroy(&c2_rhs240);
  sf_mex_destroy(&c2_lhs240);
  sf_mex_destroy(&c2_rhs241);
  sf_mex_destroy(&c2_lhs241);
  sf_mex_destroy(&c2_rhs242);
  sf_mex_destroy(&c2_lhs242);
  sf_mex_destroy(&c2_rhs243);
  sf_mex_destroy(&c2_lhs243);
  sf_mex_destroy(&c2_rhs244);
  sf_mex_destroy(&c2_lhs244);
  sf_mex_destroy(&c2_rhs245);
  sf_mex_destroy(&c2_lhs245);
  sf_mex_destroy(&c2_rhs246);
  sf_mex_destroy(&c2_lhs246);
  sf_mex_destroy(&c2_rhs247);
  sf_mex_destroy(&c2_lhs247);
  sf_mex_destroy(&c2_rhs248);
  sf_mex_destroy(&c2_lhs248);
  sf_mex_destroy(&c2_rhs249);
  sf_mex_destroy(&c2_lhs249);
  sf_mex_destroy(&c2_rhs250);
  sf_mex_destroy(&c2_lhs250);
  sf_mex_destroy(&c2_rhs251);
  sf_mex_destroy(&c2_lhs251);
  sf_mex_destroy(&c2_rhs252);
  sf_mex_destroy(&c2_lhs252);
  sf_mex_destroy(&c2_rhs253);
  sf_mex_destroy(&c2_lhs253);
  sf_mex_destroy(&c2_rhs254);
  sf_mex_destroy(&c2_lhs254);
  sf_mex_destroy(&c2_rhs255);
  sf_mex_destroy(&c2_lhs255);
}

static void c2_e_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs256 = NULL;
  const mxArray *c2_lhs256 = NULL;
  const mxArray *c2_rhs257 = NULL;
  const mxArray *c2_lhs257 = NULL;
  const mxArray *c2_rhs258 = NULL;
  const mxArray *c2_lhs258 = NULL;
  const mxArray *c2_rhs259 = NULL;
  const mxArray *c2_lhs259 = NULL;
  const mxArray *c2_rhs260 = NULL;
  const mxArray *c2_lhs260 = NULL;
  const mxArray *c2_rhs261 = NULL;
  const mxArray *c2_lhs261 = NULL;
  const mxArray *c2_rhs262 = NULL;
  const mxArray *c2_lhs262 = NULL;
  const mxArray *c2_rhs263 = NULL;
  const mxArray *c2_lhs263 = NULL;
  const mxArray *c2_rhs264 = NULL;
  const mxArray *c2_lhs264 = NULL;
  const mxArray *c2_rhs265 = NULL;
  const mxArray *c2_lhs265 = NULL;
  const mxArray *c2_rhs266 = NULL;
  const mxArray *c2_lhs266 = NULL;
  const mxArray *c2_rhs267 = NULL;
  const mxArray *c2_lhs267 = NULL;
  const mxArray *c2_rhs268 = NULL;
  const mxArray *c2_lhs268 = NULL;
  const mxArray *c2_rhs269 = NULL;
  const mxArray *c2_lhs269 = NULL;
  const mxArray *c2_rhs270 = NULL;
  const mxArray *c2_lhs270 = NULL;
  const mxArray *c2_rhs271 = NULL;
  const mxArray *c2_lhs271 = NULL;
  const mxArray *c2_rhs272 = NULL;
  const mxArray *c2_lhs272 = NULL;
  const mxArray *c2_rhs273 = NULL;
  const mxArray *c2_lhs273 = NULL;
  const mxArray *c2_rhs274 = NULL;
  const mxArray *c2_lhs274 = NULL;
  const mxArray *c2_rhs275 = NULL;
  const mxArray *c2_lhs275 = NULL;
  const mxArray *c2_rhs276 = NULL;
  const mxArray *c2_lhs276 = NULL;
  const mxArray *c2_rhs277 = NULL;
  const mxArray *c2_lhs277 = NULL;
  const mxArray *c2_rhs278 = NULL;
  const mxArray *c2_lhs278 = NULL;
  const mxArray *c2_rhs279 = NULL;
  const mxArray *c2_lhs279 = NULL;
  const mxArray *c2_rhs280 = NULL;
  const mxArray *c2_lhs280 = NULL;
  const mxArray *c2_rhs281 = NULL;
  const mxArray *c2_lhs281 = NULL;
  const mxArray *c2_rhs282 = NULL;
  const mxArray *c2_lhs282 = NULL;
  const mxArray *c2_rhs283 = NULL;
  const mxArray *c2_lhs283 = NULL;
  const mxArray *c2_rhs284 = NULL;
  const mxArray *c2_lhs284 = NULL;
  const mxArray *c2_rhs285 = NULL;
  const mxArray *c2_lhs285 = NULL;
  const mxArray *c2_rhs286 = NULL;
  const mxArray *c2_lhs286 = NULL;
  const mxArray *c2_rhs287 = NULL;
  const mxArray *c2_lhs287 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m"), "context",
                  "context", 256);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 256);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 256);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 256);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 256);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 256);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 256);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 256);
  sf_mex_assign(&c2_rhs256, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs256, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs256), "rhs", "rhs",
                  256);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs256), "lhs", "lhs",
                  256);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m!eml_complex_scalar_sqrt"),
                  "context", "context", 257);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mrdivide"), "name", "name",
                  257);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 257);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 257);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 257);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 257);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 257);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 257);
  sf_mex_assign(&c2_rhs257, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs257, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs257), "rhs", "rhs",
                  257);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs257), "lhs", "lhs",
                  257);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m!eml_complex_scalar_sqrt"),
                  "context", "context", 258);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_hypot"), "name",
                  "name", 258);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 258);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_hypot.m"),
                  "resolved", "resolved", 258);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 258);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 258);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 258);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 258);
  sf_mex_assign(&c2_rhs258, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs258, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs258), "rhs", "rhs",
                  258);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs258), "lhs", "lhs",
                  258);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 259);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 259);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 259);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 259);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 259);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 259);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 259);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 259);
  sf_mex_assign(&c2_rhs259, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs259, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs259), "rhs", "rhs",
                  259);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs259), "lhs", "lhs",
                  259);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 260);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 260);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 260);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 260);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 260);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 260);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 260);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 260);
  sf_mex_assign(&c2_rhs260, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs260, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs260), "rhs", "rhs",
                  260);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs260), "lhs", "lhs",
                  260);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 261);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mrdivide"), "name", "name",
                  261);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 261);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 261);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 261);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 261);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 261);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 261);
  sf_mex_assign(&c2_rhs261, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs261, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs261), "rhs", "rhs",
                  261);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs261), "lhs", "lhs",
                  261);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 262);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 262);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 262);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 262);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 262);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 262);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 262);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 262);
  sf_mex_assign(&c2_rhs262, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs262, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs262), "rhs", "rhs",
                  262);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs262), "lhs", "lhs",
                  262);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 263);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 263);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 263);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 263);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 263);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 263);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 263);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 263);
  sf_mex_assign(&c2_rhs263, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs263, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs263), "rhs", "rhs",
                  263);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs263), "lhs", "lhs",
                  263);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 264);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 264);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 264);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 264);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 264);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 264);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 264);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 264);
  sf_mex_assign(&c2_rhs264, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs264, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs264), "rhs", "rhs",
                  264);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs264), "lhs", "lhs",
                  264);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 265);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  265);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 265);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 265);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 265);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 265);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 265);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 265);
  sf_mex_assign(&c2_rhs265, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs265, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs265), "rhs", "rhs",
                  265);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs265), "lhs", "lhs",
                  265);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 266);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 266);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 266);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 266);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 266);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 266);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 266);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 266);
  sf_mex_assign(&c2_rhs266, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs266, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs266), "rhs", "rhs",
                  266);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs266), "lhs", "lhs",
                  266);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 267);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 267);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 267);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 267);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 267);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 267);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 267);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 267);
  sf_mex_assign(&c2_rhs267, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs267, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs267), "rhs", "rhs",
                  267);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs267), "lhs", "lhs",
                  267);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 268);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 268);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 268);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 268);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 268);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 268);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 268);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 268);
  sf_mex_assign(&c2_rhs268, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs268, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs268), "rhs", "rhs",
                  268);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs268), "lhs", "lhs",
                  268);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 269);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 269);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 269);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 269);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 269);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 269);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 269);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 269);
  sf_mex_assign(&c2_rhs269, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs269, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs269), "rhs", "rhs",
                  269);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs269), "lhs", "lhs",
                  269);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 270);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 270);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 270);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 270);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 270);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 270);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 270);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 270);
  sf_mex_assign(&c2_rhs270, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs270, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs270), "rhs", "rhs",
                  270);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs270), "lhs", "lhs",
                  270);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 271);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xgemm"),
                  "name", "name", 271);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 271);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 271);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 271);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 271);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 271);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 271);
  sf_mex_assign(&c2_rhs271, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs271, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs271), "rhs", "rhs",
                  271);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs271), "lhs", "lhs",
                  271);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 272);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_warning"), "name", "name",
                  272);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 272);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m"), "resolved",
                  "resolved", 272);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818802U), "fileTimeLo",
                  "fileTimeLo", 272);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 272);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 272);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 272);
  sf_mex_assign(&c2_rhs272, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs272, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs272), "rhs", "rhs",
                  272);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs272), "lhs", "lhs",
                  272);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m!check_for_cancellation"),
                  "context", "context", 273);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 273);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 273);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 273);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 273);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 273);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 273);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 273);
  sf_mex_assign(&c2_rhs273, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs273, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs273), "rhs", "rhs",
                  273);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs273), "lhs", "lhs",
                  273);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m!check_for_cancellation"),
                  "context", "context", 274);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 274);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 274);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 274);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 274);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 274);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 274);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 274);
  sf_mex_assign(&c2_rhs274, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs274, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs274), "rhs", "rhs",
                  274);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs274), "lhs", "lhs",
                  274);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m!check_for_cancellation"),
                  "context", "context", 275);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 275);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 275);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 275);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 275);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 275);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 275);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 275);
  sf_mex_assign(&c2_rhs275, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs275, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs275), "rhs", "rhs",
                  275);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs275), "lhs", "lhs",
                  275);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m!check_for_cancellation"),
                  "context", "context", 276);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 276);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 276);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 276);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 276);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 276);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 276);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 276);
  sf_mex_assign(&c2_rhs276, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs276, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs276), "rhs", "rhs",
                  276);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs276), "lhs", "lhs",
                  276);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m!abs1"), "context",
                  "context", 277);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 277);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 277);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 277);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 277);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 277);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 277);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 277);
  sf_mex_assign(&c2_rhs277, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs277, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs277), "rhs", "rhs",
                  277);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs277), "lhs", "lhs",
                  277);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m!check_for_cancellation"),
                  "context", "context", 278);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eps"), "name", "name", 278);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 278);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 278);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 278);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 278);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 278);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 278);
  sf_mex_assign(&c2_rhs278, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs278, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs278), "rhs", "rhs",
                  278);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs278), "lhs", "lhs",
                  278);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m!check_for_cancellation"),
                  "context", "context", 279);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("sqrt"), "name", "name", 279);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 279);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "resolved",
                  "resolved", 279);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 279);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 279);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 279);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 279);
  sf_mex_assign(&c2_rhs279, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs279, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs279), "rhs", "rhs",
                  279);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs279), "lhs", "lhs",
                  279);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m!check_for_cancellation"),
                  "context", "context", 280);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_warning"), "name", "name",
                  280);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 280);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m"), "resolved",
                  "resolved", 280);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818802U), "fileTimeLo",
                  "fileTimeLo", 280);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 280);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 280);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 280);
  sf_mex_assign(&c2_rhs280, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs280, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs280), "rhs", "rhs",
                  280);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs280), "lhs", "lhs",
                  280);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 281);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("norm"), "name", "name", 281);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 281);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m"), "resolved",
                  "resolved", 281);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713868U), "fileTimeLo",
                  "fileTimeLo", 281);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 281);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 281);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 281);
  sf_mex_assign(&c2_rhs281, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs281, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs281), "rhs", "rhs",
                  281);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs281), "lhs", "lhs",
                  281);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m"), "context",
                  "context", 282);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 282);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 282);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 282);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 282);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 282);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 282);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 282);
  sf_mex_assign(&c2_rhs282, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs282, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs282), "rhs", "rhs",
                  282);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs282), "lhs", "lhs",
                  282);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm"),
                  "context", "context", 283);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 283);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 283);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 283);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 283);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 283);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 283);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 283);
  sf_mex_assign(&c2_rhs283, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs283, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs283), "rhs", "rhs",
                  283);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs283), "lhs", "lhs",
                  283);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm"),
                  "context", "context", 284);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnan"), "name", "name", 284);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 284);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 284);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713858U), "fileTimeLo",
                  "fileTimeLo", 284);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 284);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 284);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 284);
  sf_mex_assign(&c2_rhs284, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs284, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs284), "rhs", "rhs",
                  284);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs284), "lhs", "lhs",
                  284);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm"),
                  "context", "context", 285);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_guarded_nan"), "name",
                  "name", 285);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 285);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m"),
                  "resolved", "resolved", 285);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818776U), "fileTimeLo",
                  "fileTimeLo", 285);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 285);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 285);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 285);
  sf_mex_assign(&c2_rhs285, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs285, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs285), "rhs", "rhs",
                  285);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs285), "lhs", "lhs",
                  285);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/sqrtm.m"), "context",
                  "context", 286);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eps"), "name", "name", 286);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 286);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 286);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 286);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 286);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 286);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 286);
  sf_mex_assign(&c2_rhs286, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs286, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs286), "rhs", "rhs",
                  286);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs286), "lhs", "lhs",
                  286);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "context", "context", 287);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_dlapy2"), "name", "name",
                  287);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 287);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlapy2.m"), "resolved",
                  "resolved", 287);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1350410654U), "fileTimeLo",
                  "fileTimeLo", 287);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 287);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 287);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 287);
  sf_mex_assign(&c2_rhs287, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs287, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs287), "rhs", "rhs",
                  287);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs287), "lhs", "lhs",
                  287);
  sf_mex_destroy(&c2_rhs256);
  sf_mex_destroy(&c2_lhs256);
  sf_mex_destroy(&c2_rhs257);
  sf_mex_destroy(&c2_lhs257);
  sf_mex_destroy(&c2_rhs258);
  sf_mex_destroy(&c2_lhs258);
  sf_mex_destroy(&c2_rhs259);
  sf_mex_destroy(&c2_lhs259);
  sf_mex_destroy(&c2_rhs260);
  sf_mex_destroy(&c2_lhs260);
  sf_mex_destroy(&c2_rhs261);
  sf_mex_destroy(&c2_lhs261);
  sf_mex_destroy(&c2_rhs262);
  sf_mex_destroy(&c2_lhs262);
  sf_mex_destroy(&c2_rhs263);
  sf_mex_destroy(&c2_lhs263);
  sf_mex_destroy(&c2_rhs264);
  sf_mex_destroy(&c2_lhs264);
  sf_mex_destroy(&c2_rhs265);
  sf_mex_destroy(&c2_lhs265);
  sf_mex_destroy(&c2_rhs266);
  sf_mex_destroy(&c2_lhs266);
  sf_mex_destroy(&c2_rhs267);
  sf_mex_destroy(&c2_lhs267);
  sf_mex_destroy(&c2_rhs268);
  sf_mex_destroy(&c2_lhs268);
  sf_mex_destroy(&c2_rhs269);
  sf_mex_destroy(&c2_lhs269);
  sf_mex_destroy(&c2_rhs270);
  sf_mex_destroy(&c2_lhs270);
  sf_mex_destroy(&c2_rhs271);
  sf_mex_destroy(&c2_lhs271);
  sf_mex_destroy(&c2_rhs272);
  sf_mex_destroy(&c2_lhs272);
  sf_mex_destroy(&c2_rhs273);
  sf_mex_destroy(&c2_lhs273);
  sf_mex_destroy(&c2_rhs274);
  sf_mex_destroy(&c2_lhs274);
  sf_mex_destroy(&c2_rhs275);
  sf_mex_destroy(&c2_lhs275);
  sf_mex_destroy(&c2_rhs276);
  sf_mex_destroy(&c2_lhs276);
  sf_mex_destroy(&c2_rhs277);
  sf_mex_destroy(&c2_lhs277);
  sf_mex_destroy(&c2_rhs278);
  sf_mex_destroy(&c2_lhs278);
  sf_mex_destroy(&c2_rhs279);
  sf_mex_destroy(&c2_lhs279);
  sf_mex_destroy(&c2_rhs280);
  sf_mex_destroy(&c2_lhs280);
  sf_mex_destroy(&c2_rhs281);
  sf_mex_destroy(&c2_lhs281);
  sf_mex_destroy(&c2_rhs282);
  sf_mex_destroy(&c2_lhs282);
  sf_mex_destroy(&c2_rhs283);
  sf_mex_destroy(&c2_lhs283);
  sf_mex_destroy(&c2_rhs284);
  sf_mex_destroy(&c2_lhs284);
  sf_mex_destroy(&c2_rhs285);
  sf_mex_destroy(&c2_lhs285);
  sf_mex_destroy(&c2_rhs286);
  sf_mex_destroy(&c2_lhs286);
  sf_mex_destroy(&c2_rhs287);
  sf_mex_destroy(&c2_lhs287);
}

static void c2_sqrtm(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                     real_T c2_A[9], creal_T c2_X[9])
{
  int32_T c2_i18;
  real_T c2_b_A[9];
  creal_T c2_T[9];
  creal_T c2_Q[9];
  int32_T c2_i19;
  static creal_T c2_dc0 = { 0.0, 0.0 };

  creal_T c2_R[9];
  int32_T c2_i20;
  creal_T c2_b_T[9];
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_c_j;
  int32_T c2_a;
  int32_T c2_b_a;
  int32_T c2_i21;
  int32_T c2_c_a;
  int32_T c2_d_a;
  boolean_T c2_overflow;
  int32_T c2_i;
  int32_T c2_b_i;
  creal_T c2_s;
  int32_T c2_e_a;
  int32_T c2_f_a;
  int32_T c2_i22;
  int32_T c2_g_a;
  int32_T c2_h_a;
  int32_T c2_i23;
  int32_T c2_i_a;
  int32_T c2_b;
  int32_T c2_j_a;
  int32_T c2_b_b;
  boolean_T c2_b_overflow;
  int32_T c2_k;
  int32_T c2_b_k;
  creal_T c2_b_R;
  creal_T c2_B;
  creal_T c2_b_s;
  real_T c2_ar;
  real_T c2_ai;
  real_T c2_br;
  real_T c2_bi;
  real_T c2_brm;
  real_T c2_bim;
  real_T c2_c_s;
  real_T c2_d;
  real_T c2_nr;
  real_T c2_ni;
  real_T c2_sgnbr;
  real_T c2_sgnbi;
  int32_T c2_i24;
  creal_T c2_y[9];
  int32_T c2_i25;
  creal_T c2_b_Q[9];
  int32_T c2_i26;
  creal_T c2_c_R[9];
  int32_T c2_i27;
  int32_T c2_i28;
  int32_T c2_i29;
  int32_T c2_i30;
  creal_T c2_c_b[9];
  int32_T c2_i31;
  int32_T c2_i32;
  creal_T c2_b_y[9];
  int32_T c2_i33;
  creal_T c2_d_b[9];
  int32_T c2_c_k;
  boolean_T c2_c_T;
  int32_T c2_d_j;
  int32_T c2_e_j;
  int32_T c2_k_a;
  int32_T c2_l_a;
  int32_T c2_i34;
  int32_T c2_m_a;
  int32_T c2_n_a;
  boolean_T c2_c_overflow;
  int32_T c2_c_i;
  int32_T c2_d_i;
  creal_T c2_d_R;
  creal_T c2_e_R;
  creal_T c2_f_R;
  real_T c2_d1;
  real_T c2_d2;
  real_T c2_d3;
  int32_T c2_i35;
  real_T c2_x[9];
  real_T c2_c_y;
  int32_T c2_f_j;
  real_T c2_g_j;
  real_T c2_d_s;
  int32_T c2_e_i;
  real_T c2_f_i;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_y;
  real_T c2_d_x;
  boolean_T c2_e_b;
  real_T c2_e_y;
  int32_T c2_h_j;
  real_T c2_i_j;
  real_T c2_e_s;
  int32_T c2_g_i;
  real_T c2_h_i;
  real_T c2_x1;
  real_T c2_x2;
  real_T c2_o_a;
  real_T c2_f_b;
  real_T c2_f_y;
  real_T c2_e_x;
  boolean_T c2_g_b;
  int32_T c2_j_j;
  int32_T c2_i_i;
  creal_T c2_b_X;
  boolean_T exitg1;
  boolean_T exitg2;
  int32_T exitg3;
  boolean_T exitg4;
  boolean_T exitg5;
  for (c2_i18 = 0; c2_i18 < 9; c2_i18++) {
    c2_b_A[c2_i18] = c2_A[c2_i18];
  }

  c2_schur(chartInstance, c2_b_A, c2_Q, c2_T);
  c2_d_eml_scalar_eg(chartInstance);
  for (c2_i19 = 0; c2_i19 < 9; c2_i19++) {
    c2_R[c2_i19] = c2_dc0;
  }

  for (c2_i20 = 0; c2_i20 < 9; c2_i20++) {
    c2_b_T[c2_i20] = c2_T[c2_i20];
  }

  if (c2_isUTmatD(chartInstance, c2_b_T)) {
    for (c2_j = 1; c2_j < 4; c2_j++) {
      c2_b_j = c2_j;
      c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
        - 1].re = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].re;
      c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
        - 1].im = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].im;
      c2_d_sqrt(chartInstance, &c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                 (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1]);
    }
  } else {
    for (c2_c_j = 1; c2_c_j < 4; c2_c_j++) {
      c2_b_j = c2_c_j;
      c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
        - 1].re = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].re;
      c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
        - 1].im = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].im;
      c2_d_sqrt(chartInstance, &c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                 (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1]);
      c2_a = c2_b_j;
      c2_b_a = c2_a - 1;
      c2_i21 = c2_b_a;
      c2_c_a = c2_i21;
      c2_d_a = c2_c_a;
      if (c2_d_a < 1) {
        c2_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_overflow = false;
      }

      if (c2_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_overflow);
      }

      for (c2_i = c2_i21; c2_i > 0; c2_i--) {
        c2_b_i = c2_i;
        c2_d_eml_scalar_eg(chartInstance);
        c2_s = c2_dc0;
        c2_e_a = c2_b_i;
        c2_f_a = c2_e_a + 1;
        c2_i22 = c2_f_a;
        c2_g_a = c2_b_j;
        c2_h_a = c2_g_a - 1;
        c2_i23 = c2_h_a;
        c2_i_a = c2_i22;
        c2_b = c2_i23;
        c2_j_a = c2_i_a;
        c2_b_b = c2_b;
        if (c2_j_a > c2_b_b) {
          c2_b_overflow = false;
        } else {
          c2_eml_switch_helper(chartInstance);
          c2_b_overflow = (c2_b_b > 2147483646);
        }

        if (c2_b_overflow) {
          c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
        }

        for (c2_k = c2_i22; c2_k <= c2_i23; c2_k++) {
          c2_b_k = c2_k;
          c2_b_R.re = c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 2, 0) - 1)) - 1].re *
            c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_b_k), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].re - c2_R
            [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 2, 0)
               - 1)) - 1].im * c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 1, 0) + 3 *
            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].im;
          c2_b_R.im = c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 2, 0) - 1)) - 1].re *
            c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_b_k), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].im + c2_R
            [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 2, 0)
               - 1)) - 1].im * c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 1, 0) + 3 *
            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].re;
          c2_s.re += c2_b_R.re;
          c2_s.im += c2_b_R.im;
        }

        c2_s.re = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].re -
          c2_s.re;
        c2_s.im = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].im -
          c2_s.im;
        c2_B.re = c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 2, 0) - 1)) - 1].re +
          c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].re;
        c2_B.im = c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 2, 0) - 1)) - 1].im +
          c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].im;
        c2_b_s = c2_s;
        c2_ar = c2_b_s.re;
        c2_ai = c2_b_s.im;
        c2_br = c2_B.re;
        c2_bi = c2_B.im;
        if (c2_bi == 0.0) {
          if (c2_ai == 0.0) {
            c2_s.re = c2_ar / c2_br;
            c2_s.im = 0.0;
          } else if (c2_ar == 0.0) {
            c2_s.re = 0.0;
            c2_s.im = c2_ai / c2_br;
          } else {
            c2_s.re = c2_ar / c2_br;
            c2_s.im = c2_ai / c2_br;
          }
        } else if (c2_br == 0.0) {
          if (c2_ar == 0.0) {
            c2_s.re = c2_ai / c2_bi;
            c2_s.im = 0.0;
          } else if (c2_ai == 0.0) {
            c2_s.re = 0.0;
            c2_s.im = -(c2_ar / c2_bi);
          } else {
            c2_s.re = c2_ai / c2_bi;
            c2_s.im = -(c2_ar / c2_bi);
          }
        } else {
          c2_brm = muDoubleScalarAbs(c2_br);
          c2_bim = muDoubleScalarAbs(c2_bi);
          if (c2_brm > c2_bim) {
            c2_c_s = c2_bi / c2_br;
            c2_d = c2_br + c2_c_s * c2_bi;
            c2_nr = c2_ar + c2_c_s * c2_ai;
            c2_ni = c2_ai - c2_c_s * c2_ar;
            c2_s.re = c2_nr / c2_d;
            c2_s.im = c2_ni / c2_d;
          } else if (c2_bim == c2_brm) {
            if (c2_br > 0.0) {
              c2_sgnbr = 0.5;
            } else {
              c2_sgnbr = -0.5;
            }

            if (c2_bi > 0.0) {
              c2_sgnbi = 0.5;
            } else {
              c2_sgnbi = -0.5;
            }

            c2_nr = c2_ar * c2_sgnbr + c2_ai * c2_sgnbi;
            c2_ni = c2_ai * c2_sgnbr - c2_ar * c2_sgnbi;
            c2_s.re = c2_nr / c2_brm;
            c2_s.im = c2_ni / c2_brm;
          } else {
            c2_c_s = c2_br / c2_bi;
            c2_d = c2_bi + c2_c_s * c2_br;
            c2_nr = c2_c_s * c2_ar + c2_ai;
            c2_ni = c2_c_s * c2_ai - c2_ar;
            c2_s.re = c2_nr / c2_d;
            c2_s.im = c2_ni / c2_d;
          }
        }

        c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0)
               - 1)) - 1].re = c2_s.re;
        c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0)
               - 1)) - 1].im = c2_s.im;
      }
    }
  }

  c2_e_eml_scalar_eg(chartInstance);
  c2_e_eml_scalar_eg(chartInstance);
  for (c2_i24 = 0; c2_i24 < 9; c2_i24++) {
    c2_y[c2_i24].re = 0.0;
    c2_y[c2_i24].im = 0.0;
  }

  for (c2_i25 = 0; c2_i25 < 9; c2_i25++) {
    c2_b_Q[c2_i25] = c2_Q[c2_i25];
  }

  for (c2_i26 = 0; c2_i26 < 9; c2_i26++) {
    c2_c_R[c2_i26] = c2_R[c2_i26];
  }

  c2_b_eml_xgemm(chartInstance, c2_b_Q, c2_c_R, c2_y);
  c2_i27 = 0;
  for (c2_i28 = 0; c2_i28 < 3; c2_i28++) {
    c2_i29 = 0;
    for (c2_i30 = 0; c2_i30 < 3; c2_i30++) {
      c2_c_b[c2_i30 + c2_i27].re = c2_Q[c2_i29 + c2_i28].re;
      c2_c_b[c2_i30 + c2_i27].im = -c2_Q[c2_i29 + c2_i28].im;
      c2_i29 += 3;
    }

    c2_i27 += 3;
  }

  c2_e_eml_scalar_eg(chartInstance);
  c2_e_eml_scalar_eg(chartInstance);
  for (c2_i31 = 0; c2_i31 < 9; c2_i31++) {
    c2_X[c2_i31].re = 0.0;
    c2_X[c2_i31].im = 0.0;
  }

  for (c2_i32 = 0; c2_i32 < 9; c2_i32++) {
    c2_b_y[c2_i32] = c2_y[c2_i32];
  }

  for (c2_i33 = 0; c2_i33 < 9; c2_i33++) {
    c2_d_b[c2_i33] = c2_c_b[c2_i33];
  }

  c2_b_eml_xgemm(chartInstance, c2_b_y, c2_d_b, c2_X);
  c2_c_k = 1;
  exitg5 = false;
  while ((exitg5 == false) && (c2_c_k < 4)) {
    c2_b_k = c2_c_k;
    c2_c_T = ((c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                 ("", (real_T)c2_b_k), 1, 3, 1, 0) + 3 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 2, 0) - 1)) - 1].re ==
               c2_dc0.re) && (c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 1, 0) + 3 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c2_b_k), 1, 3, 2, 0) - 1)) - 1].im == c2_dc0.im));
    if (c2_c_T) {
      c2_b_eml_warning(chartInstance);
      exitg5 = true;
    } else {
      c2_c_k++;
    }
  }

  c2_d_j = 1;
  exitg4 = false;
  while ((exitg4 == false) && (c2_d_j < 3)) {
    c2_e_j = c2_d_j;
    c2_k_a = c2_e_j;
    c2_l_a = c2_k_a + 1;
    c2_i34 = c2_l_a;
    c2_m_a = c2_i34;
    c2_n_a = c2_m_a;
    if (c2_n_a > 3) {
      c2_c_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_c_overflow = false;
    }

    if (c2_c_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_c_overflow);
    }

    c2_c_i = c2_i34;
    do {
      exitg3 = 0;
      if (c2_c_i < 4) {
        c2_d_i = c2_c_i;
        c2_eml_eps(chartInstance);
        c2_d_R.re = c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_d_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_d_i), 1, 3, 2, 0) - 1)) - 1].re +
          c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_e_j), 1, 3, 1, 0) + 3 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c2_e_j), 1, 3, 2, 0) - 1)) - 1].re;
        c2_d_R.im = c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_d_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_d_i), 1, 3, 2, 0) - 1)) - 1].im +
          c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_e_j), 1, 3, 1, 0) + 3 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c2_e_j), 1, 3, 2, 0) - 1)) - 1].im;
        c2_e_R.re = c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_d_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_d_i), 1, 3, 2, 0) - 1)) - 1].re;
        c2_e_R.im = c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_d_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_d_i), 1, 3, 2, 0) - 1)) - 1].im;
        c2_f_R.re = c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_e_j), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_e_j), 1, 3, 2, 0) - 1)) - 1].re;
        c2_f_R.im = c2_R[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_e_j), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_e_j), 1, 3, 2, 0) - 1)) - 1].im;
        c2_d1 = c2_abs1(chartInstance, c2_e_R);
        c2_d2 = c2_abs1(chartInstance, c2_f_R);
        c2_d3 = c2_abs1(chartInstance, c2_d_R);
        if (c2_d3 <= 1.4901161193847656E-7 * (c2_d1 + c2_d2)) {
          c2_c_eml_warning(chartInstance);
          exitg3 = 1;
        } else {
          c2_c_i++;
        }
      } else {
        c2_d_j++;
        exitg3 = 2;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      exitg4 = true;
    }
  }

  c2_eml_eps(chartInstance);
  for (c2_i35 = 0; c2_i35 < 9; c2_i35++) {
    c2_x[c2_i35] = c2_X[c2_i35].im;
  }

  c2_c_y = 0.0;
  c2_f_j = 0;
  exitg2 = false;
  while ((exitg2 == false) && (c2_f_j < 3)) {
    c2_g_j = 1.0 + (real_T)c2_f_j;
    c2_d_s = 0.0;
    for (c2_e_i = 0; c2_e_i < 3; c2_e_i++) {
      c2_f_i = 1.0 + (real_T)c2_e_i;
      c2_b_x = c2_x[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", c2_f_i), 1, 3, 1, 0) + 3 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c2_g_j), 1, 3, 2, 0) - 1)) - 1];
      c2_c_x = c2_b_x;
      c2_d_y = muDoubleScalarAbs(c2_c_x);
      c2_d_s += c2_d_y;
    }

    c2_d_x = c2_d_s;
    c2_e_b = muDoubleScalarIsNaN(c2_d_x);
    if (c2_e_b) {
      c2_c_y = rtNaN;
      exitg2 = true;
    } else {
      if (c2_d_s > c2_c_y) {
        c2_c_y = c2_d_s;
      }

      c2_f_j++;
    }
  }

  c2_e_y = 0.0;
  c2_h_j = 0;
  exitg1 = false;
  while ((exitg1 == false) && (c2_h_j < 3)) {
    c2_i_j = 1.0 + (real_T)c2_h_j;
    c2_e_s = 0.0;
    for (c2_g_i = 0; c2_g_i < 3; c2_g_i++) {
      c2_h_i = 1.0 + (real_T)c2_g_i;
      c2_s.re = c2_X[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c2_h_i), 1, 3, 1, 0) + 3 *
                      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c2_i_j), 1, 3, 2, 0) - 1)) - 1].re;
      c2_s.im = c2_X[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c2_h_i), 1, 3, 1, 0) + 3 *
                      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c2_i_j), 1, 3, 2, 0) - 1)) - 1].im;
      c2_x1 = c2_s.re;
      c2_x2 = c2_s.im;
      c2_o_a = c2_x1;
      c2_f_b = c2_x2;
      c2_f_y = muDoubleScalarHypot(c2_o_a, c2_f_b);
      c2_e_s += c2_f_y;
    }

    c2_e_x = c2_e_s;
    c2_g_b = muDoubleScalarIsNaN(c2_e_x);
    if (c2_g_b) {
      c2_e_y = rtNaN;
      exitg1 = true;
    } else {
      if (c2_e_s > c2_e_y) {
        c2_e_y = c2_e_s;
      }

      c2_h_j++;
    }
  }

  if (c2_c_y <= 6.6613381477509392E-15 * c2_e_y) {
    for (c2_j_j = 1; c2_j_j < 4; c2_j_j++) {
      c2_b_j = c2_j_j;
      for (c2_i_i = 1; c2_i_i < 4; c2_i_i++) {
        c2_b_i = c2_i_i;
        c2_b_X.re = c2_X[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].re;
        c2_b_X.im = c2_X[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].im;
        c2_X[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0)
               - 1)) - 1].re = c2_b_X.re;
        c2_X[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0)
               - 1)) - 1].im = 0.0;
      }
    }
  }
}

static void c2_schur(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                     real_T c2_A[9], creal_T c2_V[9], creal_T c2_T[9])
{
  int32_T c2_i36;
  real_T c2_work[3];
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_a;
  int32_T c2_b_a;
  int32_T c2_im1;
  int32_T c2_c_a;
  int32_T c2_d_a;
  int32_T c2_ip1;
  int32_T c2_e_a;
  int32_T c2_f_a;
  int32_T c2_im1n;
  int32_T c2_g_a;
  int32_T c2_h_a;
  int32_T c2_in;
  real_T c2_alpha1;
  int32_T c2_i_a;
  int32_T c2_j_a;
  int32_T c2_c;
  int32_T c2_varargin_1;
  int32_T c2_varargin_2;
  int32_T c2_x;
  int32_T c2_b_x;
  int32_T c2_xk;
  int32_T c2_c_x;
  int32_T c2_minval;
  int32_T c2_k_a;
  int32_T c2_l_a;
  int32_T c2_b_c;
  int32_T c2_m_a;
  int32_T c2_b;
  int32_T c2_n_a;
  int32_T c2_b_b;
  int32_T c2_ia0;
  int32_T c2_c_b;
  int32_T c2_d_b;
  int32_T c2_c_c;
  int32_T c2_n;
  real_T c2_b_alpha1;
  int32_T c2_ix0;
  real_T c2_c_alpha1;
  real_T c2_d4;
  int32_T c2_nm1;
  int32_T c2_i37;
  real_T c2_b_A[9];
  real_T c2_xnorm;
  real_T c2_x1;
  real_T c2_x2;
  real_T c2_o_a;
  real_T c2_e_b;
  real_T c2_beta1;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_y;
  int32_T c2_knt;
  int32_T c2_p_a;
  int32_T c2_q_a;
  real_T c2_d5;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_b_y;
  int32_T c2_i38;
  real_T c2_c_A[9];
  real_T c2_b_x1;
  real_T c2_b_x2;
  real_T c2_r_a;
  real_T c2_f_b;
  real_T c2_h_x;
  real_T c2_c_y;
  real_T c2_i_x;
  real_T c2_d_y;
  real_T c2_e_y;
  real_T c2_f_y;
  int32_T c2_b_knt;
  int32_T c2_g_b;
  int32_T c2_h_b;
  boolean_T c2_overflow;
  int32_T c2_k;
  real_T c2_j_x;
  real_T c2_g_y;
  real_T c2_k_x;
  real_T c2_h_y;
  real_T c2_i_y;
  real_T c2_j_y;
  real_T c2_tau[2];
  int32_T c2_i_b;
  int32_T c2_j_b;
  int32_T c2_d_c;
  int32_T c2_s_a;
  int32_T c2_k_b;
  int32_T c2_t_a;
  int32_T c2_l_b;
  int32_T c2_e_c;
  int32_T c2_u_a;
  int32_T c2_v_a;
  int32_T c2_f_c;
  int32_T c2_m_b;
  int32_T c2_n_b;
  int32_T c2_g_c;
  int32_T c2_o_b;
  int32_T c2_p_b;
  int32_T c2_h_c;
  int32_T c2_w_a;
  int32_T c2_q_b;
  int32_T c2_x_a;
  int32_T c2_r_b;
  int32_T c2_i_c;
  int32_T c2_y_a;
  int32_T c2_s_b;
  int32_T c2_ab_a;
  int32_T c2_t_b;
  int32_T c2_j_c;
  int32_T c2_i39;
  real_T c2_Vr[9];
  int32_T c2_i40;
  real_T c2_b_tau[2];
  int32_T c2_i41;
  real_T c2_Tr[9];
  int32_T c2_info;
  int32_T c2_b_info;
  int32_T c2_c_info;
  int32_T c2_d_info;
  int32_T c2_e_info;
  int32_T c2_i42;
  real_T c2_b_Vr[9];
  int32_T c2_i43;
  real_T c2_b_Tr[9];
  for (c2_i36 = 0; c2_i36 < 3; c2_i36++) {
    c2_work[c2_i36] = 0.0;
  }

  for (c2_i = 1; c2_i < 3; c2_i++) {
    c2_b_i = c2_i;
    c2_a = c2_b_i;
    c2_b_a = c2_a - 1;
    c2_im1 = c2_b_a;
    c2_c_a = c2_b_i;
    c2_d_a = c2_c_a + 1;
    c2_ip1 = c2_d_a;
    c2_e_a = c2_im1;
    c2_f_a = c2_e_a;
    c2_im1n = c2_f_a * 3;
    c2_g_a = c2_b_i;
    c2_h_a = c2_g_a;
    c2_in = c2_h_a * 3;
    c2_alpha1 = c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_ip1), 1, 3, 1, 0) + 3 *
                      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 2, 0) - 1)) - 1];
    c2_i_a = c2_b_i;
    c2_j_a = c2_i_a + 2;
    c2_c = c2_j_a;
    c2_varargin_1 = c2_c;
    c2_varargin_2 = c2_varargin_1;
    c2_x = c2_varargin_2;
    c2_b_x = c2_x;
    c2_eml_scalar_eg(chartInstance);
    c2_xk = c2_b_x;
    c2_c_x = c2_xk;
    c2_eml_scalar_eg(chartInstance);
    c2_minval = muIntScalarMin_sint32(c2_c_x, 3);
    c2_k_a = c2_im1;
    c2_l_a = c2_k_a;
    c2_b_c = c2_l_a * 3;
    c2_m_a = c2_minval;
    c2_b = c2_b_c;
    c2_n_a = c2_m_a;
    c2_b_b = c2_b;
    c2_ia0 = c2_n_a + c2_b_b;
    c2_c_b = c2_b_i;
    c2_d_b = c2_c_b;
    c2_c_c = 3 - c2_d_b;
    c2_n = c2_c_c;
    c2_b_alpha1 = c2_alpha1;
    c2_ix0 = c2_ia0;
    c2_c_alpha1 = c2_b_alpha1;
    c2_d4 = 0.0;
    if (c2_n <= 0) {
    } else {
      c2_nm1 = c2_n - 1;
      for (c2_i37 = 0; c2_i37 < 9; c2_i37++) {
        c2_b_A[c2_i37] = c2_A[c2_i37];
      }

      c2_xnorm = c2_eml_xnrm2(chartInstance, c2_nm1, c2_b_A, c2_ix0);
      if (c2_xnorm != 0.0) {
        c2_x1 = c2_c_alpha1;
        c2_x2 = c2_xnorm;
        c2_o_a = c2_x1;
        c2_e_b = c2_x2;
        c2_beta1 = muDoubleScalarHypot(c2_o_a, c2_e_b);
        if (c2_c_alpha1 >= 0.0) {
          c2_beta1 = -c2_beta1;
        }

        c2_realmin(chartInstance);
        c2_eml_eps(chartInstance);
        c2_d_x = c2_beta1;
        c2_e_x = c2_d_x;
        c2_y = muDoubleScalarAbs(c2_e_x);
        if (c2_y < 1.0020841800044864E-292) {
          c2_knt = 0;
          do {
            c2_p_a = c2_knt;
            c2_q_a = c2_p_a + 1;
            c2_knt = c2_q_a;
            c2_d5 = 9.9792015476736E+291;
            c2_c_eml_xscal(chartInstance, c2_nm1, c2_d5, c2_A, c2_ix0);
            c2_beta1 *= 9.9792015476736E+291;
            c2_c_alpha1 *= 9.9792015476736E+291;
            c2_f_x = c2_beta1;
            c2_g_x = c2_f_x;
            c2_b_y = muDoubleScalarAbs(c2_g_x);
          } while (!(c2_b_y >= 1.0020841800044864E-292));

          for (c2_i38 = 0; c2_i38 < 9; c2_i38++) {
            c2_c_A[c2_i38] = c2_A[c2_i38];
          }

          c2_xnorm = c2_eml_xnrm2(chartInstance, c2_nm1, c2_c_A, c2_ix0);
          c2_b_x1 = c2_c_alpha1;
          c2_b_x2 = c2_xnorm;
          c2_r_a = c2_b_x1;
          c2_f_b = c2_b_x2;
          c2_beta1 = muDoubleScalarHypot(c2_r_a, c2_f_b);
          if (c2_c_alpha1 >= 0.0) {
            c2_beta1 = -c2_beta1;
          }

          c2_h_x = c2_beta1 - c2_c_alpha1;
          c2_c_y = c2_beta1;
          c2_i_x = c2_h_x;
          c2_d_y = c2_c_y;
          c2_d4 = c2_i_x / c2_d_y;
          c2_e_y = c2_c_alpha1 - c2_beta1;
          c2_f_y = c2_e_y;
          c2_c_alpha1 = 1.0 / c2_f_y;
          c2_c_eml_xscal(chartInstance, c2_nm1, c2_c_alpha1, c2_A, c2_ix0);
          c2_b_knt = c2_knt;
          c2_g_b = c2_b_knt;
          c2_h_b = c2_g_b;
          if (1 > c2_h_b) {
            c2_overflow = false;
          } else {
            c2_eml_switch_helper(chartInstance);
            c2_overflow = (c2_h_b > 2147483646);
          }

          if (c2_overflow) {
            c2_check_forloop_overflow_error(chartInstance, c2_overflow);
          }

          for (c2_k = 1; c2_k <= c2_b_knt; c2_k++) {
            c2_beta1 *= 1.0020841800044864E-292;
          }

          c2_c_alpha1 = c2_beta1;
        } else {
          c2_j_x = c2_beta1 - c2_c_alpha1;
          c2_g_y = c2_beta1;
          c2_k_x = c2_j_x;
          c2_h_y = c2_g_y;
          c2_d4 = c2_k_x / c2_h_y;
          c2_i_y = c2_c_alpha1 - c2_beta1;
          c2_j_y = c2_i_y;
          c2_c_alpha1 = 1.0 / c2_j_y;
          c2_c_eml_xscal(chartInstance, c2_nm1, c2_c_alpha1, c2_A, c2_ix0);
          c2_c_alpha1 = c2_beta1;
        }
      }
    }

    c2_alpha1 = c2_c_alpha1;
    c2_tau[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_i), 1, 2, 1, 0) - 1] = c2_d4;
    c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_ip1), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 2, 0) - 1)) -
      1] = 1.0;
    c2_i_b = c2_b_i;
    c2_j_b = c2_i_b;
    c2_d_c = 3 - c2_j_b;
    c2_s_a = c2_ip1;
    c2_k_b = c2_im1n;
    c2_t_a = c2_s_a;
    c2_l_b = c2_k_b;
    c2_e_c = c2_t_a + c2_l_b;
    c2_u_a = c2_in;
    c2_v_a = c2_u_a + 1;
    c2_f_c = c2_v_a;
    c2_c_eml_matlab_zlarf(chartInstance, c2_d_c, c2_e_c,
                          c2_tau[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 2, 1, 0) - 1], c2_A, c2_f_c,
                          c2_work);
    c2_m_b = c2_b_i;
    c2_n_b = c2_m_b;
    c2_g_c = 3 - c2_n_b;
    c2_o_b = c2_b_i;
    c2_p_b = c2_o_b;
    c2_h_c = 3 - c2_p_b;
    c2_w_a = c2_ip1;
    c2_q_b = c2_im1n;
    c2_x_a = c2_w_a;
    c2_r_b = c2_q_b;
    c2_i_c = c2_x_a + c2_r_b;
    c2_y_a = c2_ip1;
    c2_s_b = c2_in;
    c2_ab_a = c2_y_a;
    c2_t_b = c2_s_b;
    c2_j_c = c2_ab_a + c2_t_b;
    c2_d_eml_matlab_zlarf(chartInstance, c2_g_c, c2_h_c, c2_i_c,
                          c2_tau[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 2, 1, 0) - 1], c2_A, c2_j_c,
                          c2_work);
    c2_A[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_ip1), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 2, 0) - 1)) -
      1] = c2_alpha1;
  }

  for (c2_i39 = 0; c2_i39 < 9; c2_i39++) {
    c2_Vr[c2_i39] = c2_A[c2_i39];
  }

  for (c2_i40 = 0; c2_i40 < 2; c2_i40++) {
    c2_b_tau[c2_i40] = c2_tau[c2_i40];
  }

  c2_b_eml_matlab_zunghr(chartInstance, c2_Vr, c2_b_tau);
  for (c2_i41 = 0; c2_i41 < 9; c2_i41++) {
    c2_Tr[c2_i41] = c2_A[c2_i41];
  }

  c2_info = c2_b_eml_dlahqr(chartInstance, c2_Tr, c2_Vr);
  c2_b_info = c2_info;
  c2_c_info = c2_b_info;
  c2_d_info = c2_c_info;
  c2_e_info = c2_d_info;
  for (c2_i42 = 0; c2_i42 < 9; c2_i42++) {
    c2_b_Vr[c2_i42] = c2_Vr[c2_i42];
  }

  for (c2_i43 = 0; c2_i43 < 9; c2_i43++) {
    c2_b_Tr[c2_i43] = c2_Tr[c2_i43];
  }

  c2_rsf2csf(chartInstance, c2_b_Vr, c2_b_Tr, c2_V, c2_T);
  if (c2_e_info != 0) {
    c2_eml_warning(chartInstance);
  }
}

static void c2_eml_switch_helper(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_eml_scalar_eg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_threshold(SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static real_T c2_abs(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                     real_T c2_x)
{
  real_T c2_b_x;
  (void)chartInstance;
  c2_b_x = c2_x;
  return muDoubleScalarAbs(c2_b_x);
}

static void c2_realmin(SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static real_T c2_eml_xnrm2(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[9], int32_T c2_ix0)
{
  real_T c2_y;
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_c_n;
  int32_T c2_c_ix0;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_scale;
  int32_T c2_kstart;
  int32_T c2_a;
  int32_T c2_c;
  int32_T c2_b_a;
  int32_T c2_b_c;
  int32_T c2_c_a;
  int32_T c2_b;
  int32_T c2_kend;
  int32_T c2_b_kstart;
  int32_T c2_b_kend;
  int32_T c2_d_a;
  int32_T c2_b_b;
  int32_T c2_e_a;
  int32_T c2_c_b;
  boolean_T c2_overflow;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_absxk;
  real_T c2_t;
  c2_b_n = c2_n;
  c2_b_ix0 = c2_ix0;
  c2_threshold(chartInstance);
  c2_c_n = c2_b_n;
  c2_c_ix0 = c2_b_ix0;
  c2_y = 0.0;
  if (c2_c_n < 1) {
  } else if (c2_c_n == 1) {
    c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_c_ix0), 1, 9, 1, 0) - 1];
    c2_c_x = c2_b_x;
    c2_y = muDoubleScalarAbs(c2_c_x);
  } else {
    c2_realmin(chartInstance);
    c2_scale = 2.2250738585072014E-308;
    c2_kstart = c2_c_ix0;
    c2_a = c2_c_n;
    c2_c = c2_a;
    c2_b_a = c2_c - 1;
    c2_b_c = c2_b_a;
    c2_c_a = c2_kstart;
    c2_b = c2_b_c;
    c2_kend = c2_c_a + c2_b;
    c2_b_kstart = c2_kstart;
    c2_b_kend = c2_kend;
    c2_d_a = c2_b_kstart;
    c2_b_b = c2_b_kend;
    c2_e_a = c2_d_a;
    c2_c_b = c2_b_b;
    if (c2_e_a > c2_c_b) {
      c2_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_overflow = (c2_c_b > 2147483646);
    }

    if (c2_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_overflow);
    }

    for (c2_k = c2_b_kstart; c2_k <= c2_b_kend; c2_k++) {
      c2_b_k = c2_k;
      c2_d_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_b_k), 1, 9, 1, 0) - 1];
      c2_e_x = c2_d_x;
      c2_absxk = muDoubleScalarAbs(c2_e_x);
      if (c2_absxk > c2_scale) {
        c2_t = c2_scale / c2_absxk;
        c2_y = 1.0 + c2_y * c2_t * c2_t;
        c2_scale = c2_absxk;
      } else {
        c2_t = c2_absxk / c2_scale;
        c2_y += c2_t * c2_t;
      }
    }

    c2_y = c2_scale * muDoubleScalarSqrt(c2_y);
  }

  return c2_y;
}

static void c2_check_forloop_overflow_error
  (SFc2_CollisionStrategies2InstanceStruct *chartInstance, boolean_T c2_overflow)
{
  int32_T c2_i44;
  static char_T c2_cv0[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c2_u[34];
  const mxArray *c2_y = NULL;
  int32_T c2_i45;
  static char_T c2_cv1[23] = { 'c', 'o', 'd', 'e', 'r', '.', 'i', 'n', 't', 'e',
    'r', 'n', 'a', 'l', '.', 'i', 'n', 'd', 'e', 'x', 'I', 'n', 't' };

  char_T c2_b_u[23];
  const mxArray *c2_b_y = NULL;
  (void)chartInstance;
  if (!c2_overflow) {
  } else {
    for (c2_i44 = 0; c2_i44 < 34; c2_i44++) {
      c2_u[c2_i44] = c2_cv0[c2_i44];
    }

    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  false);
    for (c2_i45 = 0; c2_i45 < 23; c2_i45++) {
      c2_b_u[c2_i45] = c2_cv1[c2_i45];
    }

    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 23),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
      1U, 2U, 14, c2_y, 14, c2_b_y));
  }
}

static void c2_eps(SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  c2_eml_eps(chartInstance);
}

static void c2_eml_eps(SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_eml_xscal(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_a, real_T c2_x[9], int32_T c2_ix0, real_T c2_b_x[9])
{
  int32_T c2_i46;
  for (c2_i46 = 0; c2_i46 < 9; c2_i46++) {
    c2_b_x[c2_i46] = c2_x[c2_i46];
  }

  c2_c_eml_xscal(chartInstance, c2_n, c2_a, c2_b_x, c2_ix0);
}

static void c2_b_threshold(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_eml_matlab_zlarf(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, int32_T c2_iv0, real_T c2_tau, real_T c2_C[9],
  int32_T c2_ic0, real_T c2_work[3], real_T c2_b_C[9], real_T c2_b_work[3])
{
  int32_T c2_i47;
  int32_T c2_i48;
  for (c2_i47 = 0; c2_i47 < 9; c2_i47++) {
    c2_b_C[c2_i47] = c2_C[c2_i47];
  }

  for (c2_i48 = 0; c2_i48 < 3; c2_i48++) {
    c2_b_work[c2_i48] = c2_work[c2_i48];
  }

  c2_c_eml_matlab_zlarf(chartInstance, c2_n, c2_iv0, c2_tau, c2_b_C, c2_ic0,
                        c2_b_work);
}

static void c2_eml_xgemv(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_m, int32_T c2_n, real_T c2_A[9], int32_T c2_ia0, real_T c2_x[9],
  int32_T c2_ix0, real_T c2_y[3], real_T c2_b_y[3])
{
  int32_T c2_i49;
  int32_T c2_i50;
  real_T c2_b_A[9];
  int32_T c2_i51;
  real_T c2_b_x[9];
  for (c2_i49 = 0; c2_i49 < 3; c2_i49++) {
    c2_b_y[c2_i49] = c2_y[c2_i49];
  }

  for (c2_i50 = 0; c2_i50 < 9; c2_i50++) {
    c2_b_A[c2_i50] = c2_A[c2_i50];
  }

  for (c2_i51 = 0; c2_i51 < 9; c2_i51++) {
    c2_b_x[c2_i51] = c2_x[c2_i51];
  }

  c2_c_eml_xgemv(chartInstance, c2_m, c2_n, c2_b_A, c2_ia0, c2_b_x, c2_ix0,
                 c2_b_y);
}

static void c2_c_threshold(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_eml_scalar_eg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_d_threshold(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_eml_matlab_zlarf(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_iv0, real_T c2_tau,
  real_T c2_C[9], int32_T c2_ic0, real_T c2_work[3], real_T c2_b_C[9], real_T
  c2_b_work[3])
{
  int32_T c2_i52;
  int32_T c2_i53;
  for (c2_i52 = 0; c2_i52 < 9; c2_i52++) {
    c2_b_C[c2_i52] = c2_C[c2_i52];
  }

  for (c2_i53 = 0; c2_i53 < 3; c2_i53++) {
    c2_b_work[c2_i53] = c2_work[c2_i53];
  }

  c2_d_eml_matlab_zlarf(chartInstance, c2_m, c2_n, c2_iv0, c2_tau, c2_b_C,
                        c2_ic0, c2_b_work);
}

static void c2_b_eml_xgemv(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_A[9], int32_T c2_ia0,
  real_T c2_x[9], int32_T c2_ix0, real_T c2_y[3], real_T c2_b_y[3])
{
  int32_T c2_i54;
  int32_T c2_i55;
  real_T c2_b_A[9];
  int32_T c2_i56;
  real_T c2_b_x[9];
  for (c2_i54 = 0; c2_i54 < 3; c2_i54++) {
    c2_b_y[c2_i54] = c2_y[c2_i54];
  }

  for (c2_i55 = 0; c2_i55 < 9; c2_i55++) {
    c2_b_A[c2_i55] = c2_A[c2_i55];
  }

  for (c2_i56 = 0; c2_i56 < 9; c2_i56++) {
    c2_b_x[c2_i56] = c2_x[c2_i56];
  }

  c2_d_eml_xgemv(chartInstance, c2_m, c2_n, c2_b_A, c2_ia0, c2_b_x, c2_ix0,
                 c2_b_y);
}

static void c2_eml_matlab_zunghr(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_tau[2], real_T c2_b_A[9])
{
  int32_T c2_i57;
  int32_T c2_i58;
  real_T c2_b_tau[2];
  for (c2_i57 = 0; c2_i57 < 9; c2_i57++) {
    c2_b_A[c2_i57] = c2_A[c2_i57];
  }

  for (c2_i58 = 0; c2_i58 < 2; c2_i58++) {
    c2_b_tau[c2_i58] = c2_tau[c2_i58];
  }

  c2_b_eml_matlab_zunghr(chartInstance, c2_b_A, c2_b_tau);
}

static void c2_eml_dlahqr(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  real_T c2_h[9], real_T c2_z[9], real_T c2_b_h[9], int32_T *c2_info, real_T
  c2_b_z[9])
{
  int32_T c2_i59;
  int32_T c2_i60;
  for (c2_i59 = 0; c2_i59 < 9; c2_i59++) {
    c2_b_h[c2_i59] = c2_h[c2_i59];
  }

  for (c2_i60 = 0; c2_i60 < 9; c2_i60++) {
    c2_b_z[c2_i60] = c2_z[c2_i60];
  }

  *c2_info = c2_b_eml_dlahqr(chartInstance, c2_b_h, c2_b_z);
}

static real_T c2_sqrt(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                      real_T c2_x)
{
  real_T c2_b_x;
  c2_b_x = c2_x;
  c2_c_sqrt(chartInstance, &c2_b_x);
  return c2_b_x;
}

static void c2_eml_error(SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  int32_T c2_i61;
  static char_T c2_cv2[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c2_u[30];
  const mxArray *c2_y = NULL;
  int32_T c2_i62;
  static char_T c2_cv3[4] = { 's', 'q', 'r', 't' };

  char_T c2_b_u[4];
  const mxArray *c2_b_y = NULL;
  (void)chartInstance;
  for (c2_i61 = 0; c2_i61 < 30; c2_i61++) {
    c2_u[c2_i61] = c2_cv2[c2_i61];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 30), false);
  for (c2_i62 = 0; c2_i62 < 4; c2_i62++) {
    c2_b_u[c2_i62] = c2_cv3[c2_i62];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c2_y, 14, c2_b_y));
}

static void c2_eml_matlab_zlarfg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_alpha1, real_T c2_x[3], real_T
  *c2_b_alpha1, real_T c2_b_x[3], real_T *c2_tau)
{
  int32_T c2_i63;
  *c2_b_alpha1 = c2_alpha1;
  for (c2_i63 = 0; c2_i63 < 3; c2_i63++) {
    c2_b_x[c2_i63] = c2_x[c2_i63];
  }

  *c2_tau = c2_b_eml_matlab_zlarfg(chartInstance, c2_n, c2_b_alpha1, c2_b_x);
}

static real_T c2_b_eml_xnrm2(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[3])
{
  real_T c2_y;
  int32_T c2_b_n;
  int32_T c2_c_n;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_scale;
  int32_T c2_a;
  int32_T c2_c;
  int32_T c2_b_a;
  int32_T c2_b_c;
  int32_T c2_b;
  int32_T c2_kend;
  int32_T c2_b_kend;
  int32_T c2_b_b;
  int32_T c2_c_b;
  boolean_T c2_overflow;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_absxk;
  real_T c2_t;
  c2_b_n = c2_n;
  c2_threshold(chartInstance);
  c2_c_n = c2_b_n;
  c2_y = 0.0;
  if (c2_c_n < 1) {
  } else if (c2_c_n == 1) {
    c2_b_x = c2_x[1];
    c2_c_x = c2_b_x;
    c2_y = muDoubleScalarAbs(c2_c_x);
  } else {
    c2_realmin(chartInstance);
    c2_scale = 2.2250738585072014E-308;
    c2_a = c2_c_n;
    c2_c = c2_a;
    c2_b_a = c2_c - 1;
    c2_b_c = c2_b_a;
    c2_b = c2_b_c;
    c2_kend = c2_b;
    c2_b_kend = c2_kend + 2;
    c2_b_b = c2_b_kend;
    c2_c_b = c2_b_b;
    if (2 > c2_c_b) {
      c2_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_overflow = (c2_c_b > 2147483646);
    }

    if (c2_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_overflow);
    }

    for (c2_k = 2; c2_k <= c2_b_kend; c2_k++) {
      c2_b_k = c2_k;
      c2_d_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_b_k), 1, 3, 1, 0) - 1];
      c2_e_x = c2_d_x;
      c2_absxk = muDoubleScalarAbs(c2_e_x);
      if (c2_absxk > c2_scale) {
        c2_t = c2_scale / c2_absxk;
        c2_y = 1.0 + c2_y * c2_t * c2_t;
        c2_scale = c2_absxk;
      } else {
        c2_t = c2_absxk / c2_scale;
        c2_y += c2_t * c2_t;
      }
    }

    c2_y = c2_scale * muDoubleScalarSqrt(c2_y);
  }

  return c2_y;
}

static void c2_b_eml_xscal(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[3], real_T c2_b_x[3])
{
  int32_T c2_i64;
  for (c2_i64 = 0; c2_i64 < 3; c2_i64++) {
    c2_b_x[c2_i64] = c2_x[c2_i64];
  }

  c2_d_eml_xscal(chartInstance, c2_n, c2_a, c2_b_x);
}

static void c2_eml_dlanv2(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  real_T c2_a, real_T c2_b, real_T c2_c, real_T c2_d, real_T *c2_rt1r, real_T
  *c2_rt1i, real_T *c2_rt2r, real_T *c2_rt2i, real_T *c2_b_a, real_T *c2_b_b,
  real_T *c2_b_c, real_T *c2_b_d, real_T *c2_cs, real_T *c2_sn)
{
  *c2_b_a = c2_a;
  *c2_b_b = c2_b;
  *c2_b_c = c2_c;
  *c2_b_d = c2_d;
  c2_c_eml_dlanv2(chartInstance, c2_b_a, c2_b_b, c2_b_c, c2_b_d, c2_rt1r,
                  c2_rt1i, c2_rt2r, c2_rt2i, c2_cs, c2_sn);
}

static void c2_c_eml_scalar_eg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_eps(SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  c2_eml_eps(chartInstance);
}

static void c2_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c,
  real_T c2_s, real_T c2_b_x[9])
{
  int32_T c2_i65;
  for (c2_i65 = 0; c2_i65 < 9; c2_i65++) {
    c2_b_x[c2_i65] = c2_x[c2_i65];
  }

  c2_d_eml_xrot(chartInstance, c2_n, c2_b_x, c2_ix0, c2_iy0, c2_c, c2_s);
}

static void c2_e_threshold(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c,
  real_T c2_s, real_T c2_b_x[9])
{
  int32_T c2_i66;
  for (c2_i66 = 0; c2_i66 < 9; c2_i66++) {
    c2_b_x[c2_i66] = c2_x[c2_i66];
  }

  c2_e_eml_xrot(chartInstance, c2_n, c2_b_x, c2_ix0, c2_iy0, c2_c, c2_s);
}

static void c2_c_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c, real_T c2_s,
  real_T c2_b_x[9])
{
  int32_T c2_i67;
  for (c2_i67 = 0; c2_i67 < 9; c2_i67++) {
    c2_b_x[c2_i67] = c2_x[c2_i67];
  }

  c2_f_eml_xrot(chartInstance, c2_b_x, c2_ix0, c2_iy0, c2_c, c2_s);
}

static void c2_rsf2csf(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  real_T c2_Ur[9], real_T c2_Tr[9], creal_T c2_U[9], creal_T c2_T[9])
{
  int32_T c2_i68;
  int32_T c2_i69;
  int32_T c2_m;
  int32_T c2_a;
  int32_T c2_b_a;
  int32_T c2_mm1;
  real_T c2_rt1i;
  real_T c2_rt1r;
  real_T c2_b_rt1r;
  real_T c2_b_rt1i;
  creal_T c2_mu1;
  real_T c2_y;
  real_T c2_b_y;
  real_T c2_x2;
  real_T c2_c_a;
  real_T c2_b;
  real_T c2_r;
  real_T c2_B;
  real_T c2_c_y;
  real_T c2_d_y;
  real_T c2_e_y;
  real_T c2_ar;
  real_T c2_ai;
  real_T c2_br;
  real_T c2_bi;
  creal_T c2_c;
  real_T c2_brm;
  real_T c2_bim;
  real_T c2_s;
  real_T c2_d;
  real_T c2_nr;
  real_T c2_ni;
  real_T c2_sgnbr;
  real_T c2_sgnbi;
  real_T c2_A;
  real_T c2_b_B;
  real_T c2_x;
  real_T c2_f_y;
  real_T c2_b_x;
  real_T c2_g_y;
  real_T c2_c_x;
  real_T c2_h_y;
  real_T c2_b_s;
  int32_T c2_b_mm1;
  int32_T c2_d_a;
  int32_T c2_e_a;
  boolean_T c2_overflow;
  int32_T c2_j;
  int32_T c2_b_j;
  creal_T c2_t1;
  creal_T c2_z;
  real_T c2_f_a;
  real_T c2_g_a;
  creal_T c2_b_c;
  int32_T c2_b_m;
  int32_T c2_b_b;
  int32_T c2_c_b;
  boolean_T c2_b_overflow;
  int32_T c2_i;
  int32_T c2_b_i;
  real_T c2_h_a;
  creal_T c2_c_c;
  real_T c2_i_a;
  int32_T c2_c_i;
  real_T c2_j_a;
  creal_T c2_d_c;
  real_T c2_k_a;
  static creal_T c2_dc1 = { 0.0, 0.0 };

  for (c2_i68 = 0; c2_i68 < 9; c2_i68++) {
    c2_T[c2_i68].re = c2_Tr[c2_i68];
    c2_T[c2_i68].im = 0.0;
  }

  for (c2_i69 = 0; c2_i69 < 9; c2_i69++) {
    c2_U[c2_i69].re = c2_Ur[c2_i69];
    c2_U[c2_i69].im = 0.0;
  }

  c2_m = 3;
  while (c2_m >= 2) {
    c2_a = c2_m;
    c2_b_a = c2_a - 1;
    c2_mm1 = c2_b_a;
    if (c2_Tr[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
           (real_T)c2_m), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
           (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0) - 1)) -
        1] != 0.0) {
      c2_b_eml_dlanv2(chartInstance, c2_Tr[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 1, 0) + 3 *
        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
        c2_mm1), 1, 3, 2, 0) - 1)) - 1], c2_Tr[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
                        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 1,
        0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                          (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1], c2_Tr
                      [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0) - 1)) - 1], c2_Tr
                      [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1], &c2_rt1r,
                      &c2_rt1i);
      c2_b_rt1r = c2_rt1r;
      c2_b_rt1i = c2_rt1i;
      c2_mu1.re = c2_b_rt1r - c2_Tr[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
        c2_m), 1, 3, 2, 0) - 1)) - 1];
      c2_mu1.im = c2_b_rt1i;
      c2_y = c2_Tr[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_m), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0) - 1)) - 1];
      c2_b_eml_scalar_eg(chartInstance);
      c2_b_y = c2_y;
      c2_scalarEg(chartInstance);
      c2_x2 = c2_b_y;
      c2_c_a = muDoubleScalarHypot(c2_mu1.re, c2_mu1.im);
      c2_b = c2_x2;
      c2_r = muDoubleScalarHypot(c2_c_a, c2_b);
      c2_B = c2_r;
      c2_c_y = c2_B;
      c2_d_y = c2_c_y;
      c2_e_y = c2_d_y;
      c2_ar = c2_mu1.re;
      c2_ai = c2_mu1.im;
      c2_br = c2_e_y;
      c2_bi = 0.0;
      if (c2_bi == 0.0) {
        if (c2_ai == 0.0) {
          c2_c.re = c2_ar / c2_br;
          c2_c.im = 0.0;
        } else if (c2_ar == 0.0) {
          c2_c.re = 0.0;
          c2_c.im = c2_ai / c2_br;
        } else {
          c2_c.re = c2_ar / c2_br;
          c2_c.im = c2_ai / c2_br;
        }
      } else if (c2_br == 0.0) {
        if (c2_ar == 0.0) {
          c2_c.re = c2_ai / c2_bi;
          c2_c.im = 0.0;
        } else if (c2_ai == 0.0) {
          c2_c.re = 0.0;
          c2_c.im = -(c2_ar / c2_bi);
        } else {
          c2_c.re = c2_ai / c2_bi;
          c2_c.im = -(c2_ar / c2_bi);
        }
      } else {
        c2_brm = muDoubleScalarAbs(c2_br);
        c2_bim = muDoubleScalarAbs(c2_bi);
        if (c2_brm > c2_bim) {
          c2_s = c2_bi / c2_br;
          c2_d = c2_br + c2_s * c2_bi;
          c2_nr = c2_ar + c2_s * c2_ai;
          c2_ni = c2_ai - c2_s * c2_ar;
          c2_c.re = c2_nr / c2_d;
          c2_c.im = c2_ni / c2_d;
        } else if (c2_bim == c2_brm) {
          if (c2_br > 0.0) {
            c2_sgnbr = 0.5;
          } else {
            c2_sgnbr = -0.5;
          }

          if (c2_bi > 0.0) {
            c2_sgnbi = 0.5;
          } else {
            c2_sgnbi = -0.5;
          }

          c2_nr = c2_ar * c2_sgnbr + c2_ai * c2_sgnbi;
          c2_ni = c2_ai * c2_sgnbr - c2_ar * c2_sgnbi;
          c2_c.re = c2_nr / c2_brm;
          c2_c.im = c2_ni / c2_brm;
        } else {
          c2_s = c2_br / c2_bi;
          c2_d = c2_bi + c2_s * c2_br;
          c2_nr = c2_s * c2_ar + c2_ai;
          c2_ni = c2_s * c2_ai - c2_ar;
          c2_c.re = c2_nr / c2_d;
          c2_c.im = c2_ni / c2_d;
        }
      }

      c2_A = c2_Tr[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_m), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0) - 1)) - 1];
      c2_b_B = c2_r;
      c2_x = c2_A;
      c2_f_y = c2_b_B;
      c2_b_x = c2_x;
      c2_g_y = c2_f_y;
      c2_c_x = c2_b_x;
      c2_h_y = c2_g_y;
      c2_b_s = c2_c_x / c2_h_y;
      c2_b_mm1 = c2_mm1;
      c2_d_a = c2_b_mm1;
      c2_e_a = c2_d_a;
      if (c2_e_a > 3) {
        c2_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_overflow = false;
      }

      if (c2_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_overflow);
      }

      for (c2_j = c2_b_mm1; c2_j < 4; c2_j++) {
        c2_b_j = c2_j;
        c2_t1.re = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].re;
        c2_t1.im = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].im;
        c2_z.re = c2_c.re * c2_t1.re + c2_c.im * c2_t1.im;
        c2_z.im = c2_c.re * c2_t1.im - c2_c.im * c2_t1.re;
        c2_f_a = c2_b_s;
        c2_mu1.re = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].re;
        c2_mu1.im = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].im;
        c2_mu1.re *= c2_f_a;
        c2_mu1.im *= c2_f_a;
        c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_mm1), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0)
               - 1)) - 1].re = c2_z.re + c2_mu1.re;
        c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_mm1), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0)
               - 1)) - 1].im = c2_z.im + c2_mu1.im;
        c2_g_a = c2_b_s;
        c2_mu1.re = c2_g_a * c2_t1.re;
        c2_mu1.im = c2_g_a * c2_t1.im;
        c2_b_c.re = c2_c.re * c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].re - c2_c.im * c2_T
          [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_m), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
          - 1].im;
        c2_b_c.im = c2_c.re * c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].im + c2_c.im * c2_T
          [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_m), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
          - 1].re;
        c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_m), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
                (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
          - 1].re = c2_b_c.re - c2_mu1.re;
        c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_m), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
                (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
          - 1].im = c2_b_c.im - c2_mu1.im;
      }

      c2_b_m = c2_m;
      c2_b_b = c2_b_m;
      c2_c_b = c2_b_b;
      if (1 > c2_c_b) {
        c2_b_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_b_overflow = (c2_c_b > 2147483646);
      }

      if (c2_b_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
      }

      for (c2_i = 1; c2_i <= c2_b_m; c2_i++) {
        c2_b_i = c2_i;
        c2_t1.re = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0) - 1)) - 1].re;
        c2_t1.im = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0) - 1)) - 1].im;
        c2_h_a = c2_b_s;
        c2_mu1.re = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1].re;
        c2_mu1.im = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1].im;
        c2_z.re = c2_h_a * c2_mu1.re;
        c2_z.im = c2_h_a * c2_mu1.im;
        c2_c_c.re = c2_c.re * c2_t1.re - c2_c.im * c2_t1.im;
        c2_c_c.im = c2_c.re * c2_t1.im + c2_c.im * c2_t1.re;
        c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0)
               - 1)) - 1].re = c2_c_c.re + c2_z.re;
        c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0)
               - 1)) - 1].im = c2_c_c.im + c2_z.im;
        c2_mu1.re = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1].re;
        c2_mu1.im = c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1].im;
        c2_z.re = c2_c.re * c2_mu1.re + c2_c.im * c2_mu1.im;
        c2_z.im = c2_c.re * c2_mu1.im - c2_c.im * c2_mu1.re;
        c2_i_a = c2_b_s;
        c2_mu1.re = c2_i_a * c2_t1.re;
        c2_mu1.im = c2_i_a * c2_t1.im;
        c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) -
               1)) - 1].re = c2_z.re - c2_mu1.re;
        c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) -
               1)) - 1].im = c2_z.im - c2_mu1.im;
      }

      for (c2_c_i = 1; c2_c_i < 4; c2_c_i++) {
        c2_b_i = c2_c_i;
        c2_t1.re = c2_U[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0) - 1)) - 1].re;
        c2_t1.im = c2_U[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0) - 1)) - 1].im;
        c2_j_a = c2_b_s;
        c2_mu1.re = c2_U[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1].re;
        c2_mu1.im = c2_U[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1].im;
        c2_z.re = c2_j_a * c2_mu1.re;
        c2_z.im = c2_j_a * c2_mu1.im;
        c2_d_c.re = c2_c.re * c2_t1.re - c2_c.im * c2_t1.im;
        c2_d_c.im = c2_c.re * c2_t1.im + c2_c.im * c2_t1.re;
        c2_U[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0)
               - 1)) - 1].re = c2_d_c.re + c2_z.re;
        c2_U[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0)
               - 1)) - 1].im = c2_d_c.im + c2_z.im;
        c2_mu1.re = c2_U[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1].re;
        c2_mu1.im = c2_U[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1].im;
        c2_z.re = c2_c.re * c2_mu1.re + c2_c.im * c2_mu1.im;
        c2_z.im = c2_c.re * c2_mu1.im - c2_c.im * c2_mu1.re;
        c2_k_a = c2_b_s;
        c2_mu1.re = c2_k_a * c2_t1.re;
        c2_mu1.im = c2_k_a * c2_t1.im;
        c2_U[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) -
               1)) - 1].re = c2_z.re - c2_mu1.re;
        c2_U[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) -
               1)) - 1].im = c2_z.im - c2_mu1.im;
      }

      c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_m), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0) - 1))
        - 1].re = c2_dc1.re;
      c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_m), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
              (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_mm1), 1, 3, 2, 0) - 1))
        - 1].im = c2_dc1.im;
    }

    c2_m = c2_mm1;
  }
}

static void c2_b_eml_dlanv2(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, real_T c2_a, real_T c2_b, real_T c2_c, real_T c2_d, real_T
  *c2_rt1r, real_T *c2_rt1i)
{
  real_T c2_b_d;
  real_T c2_b_c;
  real_T c2_b_b;
  real_T c2_b_a;
  real_T c2_temp;
  real_T c2_p;
  real_T c2_varargin_1;
  real_T c2_varargin_2;
  real_T c2_b_varargin_2;
  real_T c2_varargin_3;
  real_T c2_x;
  real_T c2_y;
  real_T c2_b_x;
  real_T c2_b_y;
  real_T c2_xk;
  real_T c2_yk;
  real_T c2_c_x;
  real_T c2_c_y;
  real_T c2_bcmax;
  real_T c2_b_varargin_1;
  real_T c2_c_varargin_2;
  real_T c2_d_varargin_2;
  real_T c2_b_varargin_3;
  real_T c2_d_x;
  real_T c2_d_y;
  real_T c2_e_x;
  real_T c2_e_y;
  real_T c2_b_xk;
  real_T c2_b_yk;
  real_T c2_f_x;
  real_T c2_f_y;
  real_T c2_minval;
  real_T c2_c_b;
  real_T c2_g_y;
  real_T c2_d_b;
  real_T c2_h_y;
  real_T c2_bcmis;
  real_T c2_c_varargin_1;
  real_T c2_e_varargin_2;
  real_T c2_f_varargin_2;
  real_T c2_c_varargin_3;
  real_T c2_g_x;
  real_T c2_i_y;
  real_T c2_h_x;
  real_T c2_j_y;
  real_T c2_c_xk;
  real_T c2_c_yk;
  real_T c2_i_x;
  real_T c2_k_y;
  real_T c2_scale;
  real_T c2_A;
  real_T c2_B;
  real_T c2_j_x;
  real_T c2_l_y;
  real_T c2_k_x;
  real_T c2_m_y;
  real_T c2_l_x;
  real_T c2_n_y;
  real_T c2_o_y;
  real_T c2_b_A;
  real_T c2_b_B;
  real_T c2_m_x;
  real_T c2_p_y;
  real_T c2_n_x;
  real_T c2_q_y;
  real_T c2_o_x;
  real_T c2_r_y;
  real_T c2_s_y;
  real_T c2_z;
  real_T c2_d6;
  real_T c2_d7;
  real_T c2_c_a;
  real_T c2_e_b;
  real_T c2_t_y;
  real_T c2_sigma;
  real_T c2_x1;
  real_T c2_x2;
  real_T c2_d_a;
  real_T c2_f_b;
  real_T c2_tau;
  real_T c2_p_x;
  real_T c2_q_x;
  real_T c2_u_y;
  real_T c2_c_A;
  real_T c2_c_B;
  real_T c2_r_x;
  real_T c2_v_y;
  real_T c2_s_x;
  real_T c2_w_y;
  real_T c2_t_x;
  real_T c2_x_y;
  real_T c2_y_y;
  real_T c2_u_x;
  real_T c2_cs;
  real_T c2_d_A;
  real_T c2_d_B;
  real_T c2_v_x;
  real_T c2_ab_y;
  real_T c2_w_x;
  real_T c2_bb_y;
  real_T c2_x_x;
  real_T c2_cb_y;
  real_T c2_db_y;
  real_T c2_g_b;
  real_T c2_eb_y;
  real_T c2_sn;
  real_T c2_aa;
  real_T c2_bb;
  real_T c2_cc;
  real_T c2_dd;
  real_T c2_y_x;
  real_T c2_ab_x;
  real_T c2_fb_y;
  real_T c2_bb_x;
  real_T c2_sab;
  real_T c2_cb_x;
  real_T c2_db_x;
  real_T c2_gb_y;
  real_T c2_eb_x;
  real_T c2_sac;
  real_T c2_e_a;
  real_T c2_h_b;
  real_T c2_fb_x;
  real_T c2_gb_x;
  real_T c2_hb_y;
  real_T c2_hb_x;
  real_T c2_ib_x;
  real_T c2_jb_x;
  real_T c2_kb_x;
  real_T c2_ib_y;
  real_T c2_lb_x;
  real_T c2_mb_x;
  real_T c2_nb_x;
  real_T c2_ob_x;
  real_T c2_jb_y;
  real_T c2_pb_x;
  real_T c2_qb_x;
  boolean_T guard1 = false;
  c2_b_d = c2_d;
  c2_b_c = c2_c;
  c2_b_b = c2_b;
  c2_b_a = c2_a;
  c2_c_eml_scalar_eg(chartInstance);
  if (c2_b_c == 0.0) {
  } else if (c2_b_b == 0.0) {
    c2_temp = c2_b_d;
    c2_b_a = c2_temp;
    c2_b_b = -c2_b_c;
    c2_b_c = 0.0;
  } else {
    guard1 = false;
    if (c2_b_a - c2_b_d == 0.0) {
      if (c2_b_b < 0.0 != c2_b_c < 0.0) {
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1 == true) {
      c2_temp = c2_b_a - c2_b_d;
      c2_p = 0.5 * c2_temp;
      c2_varargin_1 = c2_abs(chartInstance, c2_b_b);
      c2_varargin_2 = c2_abs(chartInstance, c2_b_c);
      c2_b_varargin_2 = c2_varargin_1;
      c2_varargin_3 = c2_varargin_2;
      c2_x = c2_b_varargin_2;
      c2_y = c2_varargin_3;
      c2_b_x = c2_x;
      c2_b_y = c2_y;
      c2_b_eml_scalar_eg(chartInstance);
      c2_xk = c2_b_x;
      c2_yk = c2_b_y;
      c2_c_x = c2_xk;
      c2_c_y = c2_yk;
      c2_b_eml_scalar_eg(chartInstance);
      c2_bcmax = muDoubleScalarMax(c2_c_x, c2_c_y);
      c2_b_varargin_1 = c2_abs(chartInstance, c2_b_b);
      c2_c_varargin_2 = c2_abs(chartInstance, c2_b_c);
      c2_d_varargin_2 = c2_b_varargin_1;
      c2_b_varargin_3 = c2_c_varargin_2;
      c2_d_x = c2_d_varargin_2;
      c2_d_y = c2_b_varargin_3;
      c2_e_x = c2_d_x;
      c2_e_y = c2_d_y;
      c2_b_eml_scalar_eg(chartInstance);
      c2_b_xk = c2_e_x;
      c2_b_yk = c2_e_y;
      c2_f_x = c2_b_xk;
      c2_f_y = c2_b_yk;
      c2_b_eml_scalar_eg(chartInstance);
      c2_minval = muDoubleScalarMin(c2_f_x, c2_f_y);
      c2_c_b = c2_b_b;
      if (!(c2_c_b < 0.0)) {
        c2_g_y = 1.0;
      } else {
        c2_g_y = -1.0;
      }

      c2_d_b = c2_b_c;
      if (!(c2_d_b < 0.0)) {
        c2_h_y = 1.0;
      } else {
        c2_h_y = -1.0;
      }

      c2_bcmis = c2_minval * c2_g_y * c2_h_y;
      c2_c_varargin_1 = c2_abs(chartInstance, c2_p);
      c2_e_varargin_2 = c2_bcmax;
      c2_f_varargin_2 = c2_c_varargin_1;
      c2_c_varargin_3 = c2_e_varargin_2;
      c2_g_x = c2_f_varargin_2;
      c2_i_y = c2_c_varargin_3;
      c2_h_x = c2_g_x;
      c2_j_y = c2_i_y;
      c2_b_eml_scalar_eg(chartInstance);
      c2_c_xk = c2_h_x;
      c2_c_yk = c2_j_y;
      c2_i_x = c2_c_xk;
      c2_k_y = c2_c_yk;
      c2_b_eml_scalar_eg(chartInstance);
      c2_scale = muDoubleScalarMax(c2_i_x, c2_k_y);
      c2_A = c2_p;
      c2_B = c2_scale;
      c2_j_x = c2_A;
      c2_l_y = c2_B;
      c2_k_x = c2_j_x;
      c2_m_y = c2_l_y;
      c2_l_x = c2_k_x;
      c2_n_y = c2_m_y;
      c2_o_y = c2_l_x / c2_n_y;
      c2_b_A = c2_bcmax;
      c2_b_B = c2_scale;
      c2_m_x = c2_b_A;
      c2_p_y = c2_b_B;
      c2_n_x = c2_m_x;
      c2_q_y = c2_p_y;
      c2_o_x = c2_n_x;
      c2_r_y = c2_q_y;
      c2_s_y = c2_o_x / c2_r_y;
      c2_z = c2_o_y * c2_p + c2_s_y * c2_bcmis;
      c2_b_eps(chartInstance);
      if (c2_z >= 8.8817841970012523E-16) {
        c2_d6 = c2_scale;
        c2_c_sqrt(chartInstance, &c2_d6);
        c2_d7 = c2_z;
        c2_c_sqrt(chartInstance, &c2_d7);
        c2_c_a = c2_d6 * c2_d7;
        c2_e_b = c2_p;
        if (c2_e_b < 0.0 == c2_c_a < 0.0) {
          c2_t_y = c2_c_a;
        } else {
          c2_t_y = -c2_c_a;
        }

        c2_z = c2_p + c2_t_y;
        c2_b_a = c2_b_d + c2_z;
        c2_b_b -= c2_b_c;
        c2_b_c = 0.0;
      } else {
        c2_sigma = c2_b_b + c2_b_c;
        c2_x1 = c2_sigma;
        c2_x2 = c2_temp;
        c2_d_a = c2_x1;
        c2_f_b = c2_x2;
        c2_tau = muDoubleScalarHypot(c2_d_a, c2_f_b);
        c2_p_x = c2_sigma;
        c2_q_x = c2_p_x;
        c2_u_y = muDoubleScalarAbs(c2_q_x);
        c2_c_A = c2_u_y;
        c2_c_B = c2_tau;
        c2_r_x = c2_c_A;
        c2_v_y = c2_c_B;
        c2_s_x = c2_r_x;
        c2_w_y = c2_v_y;
        c2_t_x = c2_s_x;
        c2_x_y = c2_w_y;
        c2_y_y = c2_t_x / c2_x_y;
        c2_u_x = 0.5 * (1.0 + c2_y_y);
        c2_cs = c2_u_x;
        if (c2_cs < 0.0) {
          c2_eml_error(chartInstance);
        }

        c2_cs = muDoubleScalarSqrt(c2_cs);
        c2_d_A = c2_p;
        c2_d_B = c2_tau * c2_cs;
        c2_v_x = c2_d_A;
        c2_ab_y = c2_d_B;
        c2_w_x = c2_v_x;
        c2_bb_y = c2_ab_y;
        c2_x_x = c2_w_x;
        c2_cb_y = c2_bb_y;
        c2_db_y = c2_x_x / c2_cb_y;
        c2_g_b = c2_sigma;
        if (!(c2_g_b < 0.0)) {
          c2_eb_y = 1.0;
        } else {
          c2_eb_y = -1.0;
        }

        c2_sn = -c2_db_y * c2_eb_y;
        c2_aa = c2_b_a * c2_cs + c2_b_b * c2_sn;
        c2_bb = -c2_b_a * c2_sn + c2_b_b * c2_cs;
        c2_cc = c2_b_c * c2_cs + c2_b_d * c2_sn;
        c2_dd = -c2_b_c * c2_sn + c2_b_d * c2_cs;
        c2_b_a = c2_aa * c2_cs + c2_cc * c2_sn;
        c2_b_b = c2_bb * c2_cs + c2_dd * c2_sn;
        c2_b_c = -c2_aa * c2_sn + c2_cc * c2_cs;
        c2_b_d = -c2_bb * c2_sn + c2_dd * c2_cs;
        c2_temp = 0.5 * (c2_b_a + c2_b_d);
        c2_b_a = c2_temp;
        if (c2_b_c != 0.0) {
          if (c2_b_b != 0.0) {
            if (c2_b_b < 0.0 == c2_b_c < 0.0) {
              c2_y_x = c2_b_b;
              c2_ab_x = c2_y_x;
              c2_fb_y = muDoubleScalarAbs(c2_ab_x);
              c2_bb_x = c2_fb_y;
              c2_sab = c2_bb_x;
              if (c2_sab < 0.0) {
                c2_eml_error(chartInstance);
              }

              c2_sab = muDoubleScalarSqrt(c2_sab);
              c2_cb_x = c2_b_c;
              c2_db_x = c2_cb_x;
              c2_gb_y = muDoubleScalarAbs(c2_db_x);
              c2_eb_x = c2_gb_y;
              c2_sac = c2_eb_x;
              if (c2_sac < 0.0) {
                c2_eml_error(chartInstance);
              }

              c2_sac = muDoubleScalarSqrt(c2_sac);
              c2_e_a = c2_sab * c2_sac;
              c2_h_b = c2_b_c;
              if (c2_h_b < 0.0 == c2_e_a < 0.0) {
                c2_p = c2_e_a;
              } else {
                c2_p = -c2_e_a;
              }

              c2_fb_x = c2_b_b + c2_b_c;
              c2_gb_x = c2_fb_x;
              c2_hb_y = muDoubleScalarAbs(c2_gb_x);
              c2_hb_x = c2_hb_y;
              c2_ib_x = c2_hb_x;
              if (c2_ib_x < 0.0) {
                c2_eml_error(chartInstance);
              }

              c2_b_a = c2_temp + c2_p;
              c2_b_b -= c2_b_c;
              c2_b_c = 0.0;
            }
          } else {
            c2_b_b = -c2_b_c;
            c2_b_c = 0.0;
          }
        }
      }
    }
  }

  *c2_rt1r = c2_b_a;
  if (c2_b_c == 0.0) {
    *c2_rt1i = 0.0;
  } else {
    c2_jb_x = c2_b_b;
    c2_kb_x = c2_jb_x;
    c2_ib_y = muDoubleScalarAbs(c2_kb_x);
    c2_lb_x = c2_ib_y;
    c2_mb_x = c2_lb_x;
    if (c2_mb_x < 0.0) {
      c2_eml_error(chartInstance);
    }

    c2_mb_x = muDoubleScalarSqrt(c2_mb_x);
    c2_nb_x = c2_b_c;
    c2_ob_x = c2_nb_x;
    c2_jb_y = muDoubleScalarAbs(c2_ob_x);
    c2_pb_x = c2_jb_y;
    c2_qb_x = c2_pb_x;
    if (c2_qb_x < 0.0) {
      c2_eml_error(chartInstance);
    }

    c2_qb_x = muDoubleScalarSqrt(c2_qb_x);
    *c2_rt1i = c2_mb_x * c2_qb_x;
  }
}

static void c2_scalarEg(SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_eml_warning(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  int32_T c2_i70;
  static char_T c2_varargin_1[26] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o',
    'o', 'l', 'b', 'o', 'x', ':', 's', 'c', 'h', 'u', 'r', '_', 'f', 'a', 'i',
    'l', 'e', 'd' };

  char_T c2_u[26];
  const mxArray *c2_y = NULL;
  (void)chartInstance;
  for (c2_i70 = 0; c2_i70 < 26; c2_i70++) {
    c2_u[c2_i70] = c2_varargin_1[c2_i70];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 26), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "warning", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c2_y));
}

static void c2_d_eml_scalar_eg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static boolean_T c2_isUTmatD(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, creal_T c2_T[9])
{
  boolean_T c2_p;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_b_a;
  int32_T c2_i71;
  int32_T c2_b;
  int32_T c2_b_b;
  boolean_T c2_overflow;
  int32_T c2_i;
  int32_T c2_b_i;
  static creal_T c2_dc2 = { 0.0, 0.0 };

  boolean_T c2_b_T;
  int32_T exitg1;
  int32_T exitg2;
  c2_j = 1;
  do {
    exitg2 = 0;
    if (c2_j < 4) {
      c2_b_j = c2_j;
      c2_a = c2_b_j;
      c2_b_a = c2_a - 1;
      c2_i71 = c2_b_a;
      c2_b = c2_i71;
      c2_b_b = c2_b;
      if (1 > c2_b_b) {
        c2_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_overflow = (c2_b_b > 2147483646);
      }

      if (c2_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_overflow);
      }

      c2_i = 1;
      do {
        exitg1 = 0;
        if (c2_i <= c2_i71) {
          c2_b_i = c2_i;
          c2_b_T = ((c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                           (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].re !=
                     c2_dc2.re) || (c2_T[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 3, 1, 0) + 3 *
                      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1].im !=
                     c2_dc2.im));
          if (c2_b_T) {
            c2_p = false;
            exitg1 = 1;
          } else {
            c2_i++;
          }
        } else {
          c2_j++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = 1;
      }
    } else {
      c2_p = true;
      exitg2 = 1;
    }
  } while (exitg2 == 0);

  return c2_p;
}

static creal_T c2_b_sqrt(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  creal_T c2_x)
{
  creal_T c2_b_x;
  c2_b_x = c2_x;
  c2_d_sqrt(chartInstance, &c2_b_x);
  return c2_b_x;
}

static void c2_realmax(SFc2_CollisionStrategies2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_e_eml_scalar_eg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_eml_xgemm(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  creal_T c2_A[9], creal_T c2_B[9], creal_T c2_C[9], creal_T c2_b_C[9])
{
  int32_T c2_i72;
  int32_T c2_i73;
  creal_T c2_b_A[9];
  int32_T c2_i74;
  creal_T c2_b_B[9];
  for (c2_i72 = 0; c2_i72 < 9; c2_i72++) {
    c2_b_C[c2_i72] = c2_C[c2_i72];
  }

  for (c2_i73 = 0; c2_i73 < 9; c2_i73++) {
    c2_b_A[c2_i73] = c2_A[c2_i73];
  }

  for (c2_i74 = 0; c2_i74 < 9; c2_i74++) {
    c2_b_B[c2_i74] = c2_B[c2_i74];
  }

  c2_b_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_b_eml_warning(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  int32_T c2_i75;
  static char_T c2_varargin_1[27] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 's',
    'q', 'r', 't', 'm', ':', 'S', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c2_u[27];
  const mxArray *c2_y = NULL;
  (void)chartInstance;
  for (c2_i75 = 0; c2_i75 < 27; c2_i75++) {
    c2_u[c2_i75] = c2_varargin_1[c2_i75];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 27), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "warning", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c2_y));
}

static real_T c2_abs1(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                      creal_T c2_x)
{
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_b_y;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_c_y;
  (void)chartInstance;
  c2_b_x = c2_x.re;
  c2_c_x = c2_b_x;
  c2_b_y = muDoubleScalarAbs(c2_c_x);
  c2_d_x = c2_x.im;
  c2_e_x = c2_d_x;
  c2_c_y = muDoubleScalarAbs(c2_e_x);
  return c2_b_y + c2_c_y;
}

static void c2_c_eml_warning(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
{
  int32_T c2_i76;
  static char_T c2_varargin_1[35] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o',
    'o', 'l', 'b', 'o', 'x', ':', 's', 'q', 'r', 't', 'm', '_', 'r', 'o', 'o',
    't', 'E', 'i', 'g', 'e', 'n', 'C', 'a', 'n', 'c', 'e', 'l' };

  char_T c2_u[35];
  const mxArray *c2_y = NULL;
  (void)chartInstance;
  for (c2_i76 = 0; c2_i76 < 35; c2_i76++) {
    c2_u[c2_i76] = c2_varargin_1[c2_i76];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 35), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "warning", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c2_y));
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_CollisionStrategies2InstanceStruct *chartInstance;
  chartInstance = (SFc2_CollisionStrategies2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_d_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i77;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i77, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i77;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_CollisionStrategies2InstanceStruct *chartInstance;
  chartInstance = (SFc2_CollisionStrategies2InstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_e_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_CollisionStrategies2, const
  char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_CollisionStrategies2), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_CollisionStrategies2);
  return c2_y;
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_eml_xscal(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[9], int32_T c2_ix0)
{
  int32_T c2_b_n;
  real_T c2_b_a;
  int32_T c2_b_ix0;
  int32_T c2_c_n;
  real_T c2_c_a;
  int32_T c2_c_ix0;
  int32_T c2_d_ix0;
  int32_T c2_d_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_c;
  int32_T c2_e_a;
  int32_T c2_b_b;
  int32_T c2_i78;
  int32_T c2_f_a;
  int32_T c2_c_b;
  int32_T c2_g_a;
  int32_T c2_d_b;
  boolean_T c2_overflow;
  int32_T c2_k;
  int32_T c2_b_k;
  c2_b_n = c2_n;
  c2_b_a = c2_a;
  c2_b_ix0 = c2_ix0;
  c2_b_threshold(chartInstance);
  c2_c_n = c2_b_n;
  c2_c_a = c2_b_a;
  c2_c_ix0 = c2_b_ix0;
  c2_d_ix0 = c2_c_ix0;
  c2_d_a = c2_c_n;
  c2_c = c2_d_a;
  c2_b = c2_c - 1;
  c2_b_c = c2_b;
  c2_e_a = c2_c_ix0;
  c2_b_b = c2_b_c;
  c2_i78 = c2_e_a + c2_b_b;
  c2_f_a = c2_d_ix0;
  c2_c_b = c2_i78;
  c2_g_a = c2_f_a;
  c2_d_b = c2_c_b;
  if (c2_g_a > c2_d_b) {
    c2_overflow = false;
  } else {
    c2_eml_switch_helper(chartInstance);
    c2_overflow = (c2_d_b > 2147483646);
  }

  if (c2_overflow) {
    c2_check_forloop_overflow_error(chartInstance, c2_overflow);
  }

  for (c2_k = c2_d_ix0; c2_k <= c2_i78; c2_k++) {
    c2_b_k = c2_k;
    c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_b_k), 1, 9, 1, 0) - 1] = c2_c_a * c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 9, 1, 0) - 1];
  }
}

static void c2_c_eml_matlab_zlarf(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, int32_T c2_iv0, real_T c2_tau, real_T c2_C[9],
  int32_T c2_ic0, real_T c2_work[3])
{
  int32_T c2_lastv;
  int32_T c2_a;
  int32_T c2_b_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_b;
  int32_T c2_b_c;
  int32_T c2_c_a;
  int32_T c2_c_b;
  int32_T c2_d_a;
  int32_T c2_d_b;
  int32_T c2_i;
  int32_T c2_e_a;
  int32_T c2_f_a;
  int32_T c2_g_a;
  int32_T c2_h_a;
  int32_T c2_b_n;
  int32_T c2_ia0;
  int32_T c2_lastc;
  int32_T c2_i_a;
  int32_T c2_j_a;
  int32_T c2_c_c;
  int32_T c2_k_a;
  int32_T c2_e_b;
  int32_T c2_l_a;
  int32_T c2_f_b;
  int32_T c2_rowleft;
  int32_T c2_m_a;
  int32_T c2_n_a;
  int32_T c2_d_c;
  int32_T c2_o_a;
  int32_T c2_p_a;
  int32_T c2_e_c;
  int32_T c2_q_a;
  int32_T c2_g_b;
  int32_T c2_r_a;
  int32_T c2_h_b;
  int32_T c2_rowright;
  int32_T c2_b_rowleft;
  int32_T c2_b_rowright;
  int32_T c2_s_a;
  int32_T c2_i_b;
  int32_T c2_t_a;
  int32_T c2_j_b;
  boolean_T c2_overflow;
  int32_T c2_ia;
  int32_T c2_b_ia;
  int32_T c2_u_a;
  int32_T c2_v_a;
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  real_T c2_b_C[9];
  int32_T c2_i82;
  int32_T c2_i83;
  int32_T c2_i84;
  real_T c2_c_C[9];
  int32_T c2_m;
  int32_T c2_c_n;
  real_T c2_alpha1;
  int32_T c2_iy0;
  int32_T c2_b_ia0;
  int32_T c2_b_m;
  int32_T c2_d_n;
  real_T c2_b_alpha1;
  int32_T c2_b_iy0;
  int32_T c2_c_ia0;
  int32_T c2_c_m;
  int32_T c2_e_n;
  real_T c2_c_alpha1;
  int32_T c2_c_iy0;
  int32_T c2_d_ia0;
  int32_T c2_d_m;
  int32_T c2_f_n;
  real_T c2_d_alpha1;
  int32_T c2_d_iy0;
  int32_T c2_e_ia0;
  int32_T c2_e_m;
  int32_T c2_g_n;
  real_T c2_e_alpha1;
  int32_T c2_e_iy0;
  int32_T c2_f_ia0;
  int32_T c2_w_a;
  int32_T c2_jA;
  int32_T c2_jy;
  int32_T c2_h_n;
  int32_T c2_k_b;
  int32_T c2_l_b;
  boolean_T c2_b_overflow;
  int32_T c2_j;
  real_T c2_yjy;
  real_T c2_temp;
  int32_T c2_ix;
  int32_T c2_m_b;
  int32_T c2_i85;
  int32_T c2_x_a;
  int32_T c2_n_b;
  int32_T c2_i86;
  int32_T c2_y_a;
  int32_T c2_o_b;
  int32_T c2_ab_a;
  int32_T c2_p_b;
  boolean_T c2_c_overflow;
  int32_T c2_ijA;
  int32_T c2_b_ijA;
  int32_T c2_bb_a;
  int32_T c2_cb_a;
  int32_T c2_db_a;
  int32_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  if (c2_tau != 0.0) {
    c2_lastv = c2_n;
    c2_a = c2_lastv;
    c2_b_a = c2_a;
    c2_c = c2_b_a;
    c2_b = c2_c - 1;
    c2_b_b = c2_b;
    c2_b_c = c2_b_b;
    c2_c_a = c2_iv0;
    c2_c_b = c2_b_c;
    c2_d_a = c2_c_a;
    c2_d_b = c2_c_b;
    c2_i = c2_d_a + c2_d_b;
    exitg3 = false;
    while ((exitg3 == false) && (c2_lastv > 0)) {
      if (c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_i), 1, 9, 1, 0) - 1] == 0.0) {
        c2_e_a = c2_lastv;
        c2_f_a = c2_e_a - 1;
        c2_lastv = c2_f_a;
        c2_g_a = c2_i;
        c2_h_a = c2_g_a - 1;
        c2_i = c2_h_a;
      } else {
        exitg3 = true;
      }
    }

    c2_b_n = c2_lastv;
    c2_ia0 = c2_ic0;
    c2_lastc = 3;
    exitg2 = false;
    while ((exitg2 == false) && (c2_lastc > 0)) {
      c2_i_a = c2_lastc;
      c2_j_a = c2_i_a;
      c2_c_c = c2_j_a;
      c2_k_a = c2_ia0;
      c2_e_b = c2_c_c - 1;
      c2_l_a = c2_k_a;
      c2_f_b = c2_e_b;
      c2_rowleft = c2_l_a + c2_f_b;
      c2_m_a = c2_b_n;
      c2_n_a = c2_m_a;
      c2_d_c = c2_n_a;
      c2_o_a = c2_d_c - 1;
      c2_p_a = c2_o_a;
      c2_e_c = c2_p_a * 3;
      c2_q_a = c2_rowleft;
      c2_g_b = c2_e_c;
      c2_r_a = c2_q_a;
      c2_h_b = c2_g_b;
      c2_rowright = c2_r_a + c2_h_b;
      c2_b_rowleft = c2_rowleft;
      c2_b_rowright = c2_rowright;
      c2_s_a = c2_b_rowleft;
      c2_i_b = c2_b_rowright;
      c2_t_a = c2_s_a;
      c2_j_b = c2_i_b;
      if (c2_t_a > c2_j_b) {
        c2_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_overflow = (c2_j_b > 2147483644);
      }

      if (c2_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_overflow);
      }

      c2_ia = c2_b_rowleft;
      do {
        exitg1 = 0;
        if (c2_ia <= c2_b_rowright) {
          c2_b_ia = c2_ia;
          if (c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                "", (real_T)c2_b_ia), 1, 9, 1, 0) - 1] != 0.0) {
            exitg1 = 1;
          } else {
            c2_ia += 3;
          }
        } else {
          c2_u_a = c2_lastc;
          c2_v_a = c2_u_a - 1;
          c2_lastc = c2_v_a;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    c2_lastv = 0;
    c2_lastc = 0;
  }

  if (c2_lastv > 0) {
    c2_i79 = 0;
    for (c2_i80 = 0; c2_i80 < 3; c2_i80++) {
      for (c2_i81 = 0; c2_i81 < 3; c2_i81++) {
        c2_b_C[c2_i81 + c2_i79] = c2_C[c2_i81 + c2_i79];
      }

      c2_i79 += 3;
    }

    c2_i82 = 0;
    for (c2_i83 = 0; c2_i83 < 3; c2_i83++) {
      for (c2_i84 = 0; c2_i84 < 3; c2_i84++) {
        c2_c_C[c2_i84 + c2_i82] = c2_C[c2_i84 + c2_i82];
      }

      c2_i82 += 3;
    }

    c2_c_eml_xgemv(chartInstance, c2_lastc, c2_lastv, c2_b_C, c2_ic0, c2_c_C,
                   c2_iv0, c2_work);
    c2_m = c2_lastc;
    c2_c_n = c2_lastv;
    c2_alpha1 = -c2_tau;
    c2_iy0 = c2_iv0;
    c2_b_ia0 = c2_ic0;
    c2_b_m = c2_m;
    c2_d_n = c2_c_n;
    c2_b_alpha1 = c2_alpha1;
    c2_b_iy0 = c2_iy0;
    c2_c_ia0 = c2_b_ia0;
    c2_c_m = c2_b_m;
    c2_e_n = c2_d_n;
    c2_c_alpha1 = c2_b_alpha1;
    c2_c_iy0 = c2_b_iy0;
    c2_d_ia0 = c2_c_ia0;
    c2_d_threshold(chartInstance);
    c2_d_m = c2_c_m;
    c2_f_n = c2_e_n;
    c2_d_alpha1 = c2_c_alpha1;
    c2_d_iy0 = c2_c_iy0;
    c2_e_ia0 = c2_d_ia0;
    c2_e_m = c2_d_m;
    c2_g_n = c2_f_n;
    c2_e_alpha1 = c2_d_alpha1;
    c2_e_iy0 = c2_d_iy0;
    c2_f_ia0 = c2_e_ia0;
    if (c2_e_alpha1 == 0.0) {
    } else {
      c2_w_a = c2_f_ia0 - 1;
      c2_jA = c2_w_a;
      c2_jy = c2_e_iy0;
      c2_h_n = c2_g_n;
      c2_k_b = c2_h_n;
      c2_l_b = c2_k_b;
      if (1 > c2_l_b) {
        c2_b_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_b_overflow = (c2_l_b > 2147483646);
      }

      if (c2_b_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
      }

      for (c2_j = 1; c2_j <= c2_h_n; c2_j++) {
        c2_yjy = c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_jy), 1, 9, 1, 0) - 1];
        if (c2_yjy != 0.0) {
          c2_temp = c2_yjy * c2_e_alpha1;
          c2_ix = 1;
          c2_m_b = c2_jA + 1;
          c2_i85 = c2_m_b;
          c2_x_a = c2_e_m;
          c2_n_b = c2_jA;
          c2_i86 = c2_x_a + c2_n_b;
          c2_y_a = c2_i85;
          c2_o_b = c2_i86;
          c2_ab_a = c2_y_a;
          c2_p_b = c2_o_b;
          if (c2_ab_a > c2_p_b) {
            c2_c_overflow = false;
          } else {
            c2_eml_switch_helper(chartInstance);
            c2_c_overflow = (c2_p_b > 2147483646);
          }

          if (c2_c_overflow) {
            c2_check_forloop_overflow_error(chartInstance, c2_c_overflow);
          }

          for (c2_ijA = c2_i85; c2_ijA <= c2_i86; c2_ijA++) {
            c2_b_ijA = c2_ijA;
            c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_ijA), 1, 9, 1, 0) - 1] =
              c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c2_b_ijA), 1, 9, 1, 0) - 1] +
              c2_work[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 3, 1, 0) - 1] * c2_temp;
            c2_bb_a = c2_ix + 1;
            c2_ix = c2_bb_a;
          }
        }

        c2_cb_a = c2_jy + 1;
        c2_jy = c2_cb_a;
        c2_db_a = c2_jA + 3;
        c2_jA = c2_db_a;
      }
    }
  }
}

static void c2_c_eml_xgemv(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_A[9], int32_T c2_ia0,
  real_T c2_x[9], int32_T c2_ix0, real_T c2_y[3])
{
  int32_T c2_b_m;
  int32_T c2_b_n;
  int32_T c2_b_ia0;
  int32_T c2_b_ix0;
  int32_T c2_c_m;
  int32_T c2_c_n;
  int32_T c2_c_ia0;
  int32_T c2_c_ix0;
  int32_T c2_a;
  int32_T c2_mm1;
  int32_T c2_b_a;
  int32_T c2_nm1;
  int32_T c2_b;
  int32_T c2_c;
  int32_T c2_b_b;
  int32_T c2_iyend;
  int32_T c2_b_iyend;
  int32_T c2_c_b;
  int32_T c2_d_b;
  boolean_T c2_overflow;
  int32_T c2_iy;
  int32_T c2_b_iy;
  int32_T c2_ix;
  int32_T c2_d_ia0;
  int32_T c2_e_b;
  int32_T c2_b_c;
  int32_T c2_c_a;
  int32_T c2_f_b;
  int32_T c2_i87;
  int32_T c2_d_a;
  int32_T c2_g_b;
  int32_T c2_e_a;
  int32_T c2_h_b;
  boolean_T c2_b_overflow;
  int32_T c2_iac;
  int32_T c2_b_iac;
  real_T c2_c_c;
  int32_T c2_c_iac;
  int32_T c2_f_a;
  int32_T c2_i_b;
  int32_T c2_i88;
  int32_T c2_g_a;
  int32_T c2_j_b;
  int32_T c2_h_a;
  int32_T c2_k_b;
  boolean_T c2_c_overflow;
  int32_T c2_ia;
  int32_T c2_b_ia;
  int32_T c2_i_a;
  int32_T c2_j_a;
  c2_b_m = c2_m;
  c2_b_n = c2_n;
  c2_b_ia0 = c2_ia0;
  c2_b_ix0 = c2_ix0;
  c2_c_threshold(chartInstance);
  c2_c_m = c2_b_m;
  c2_c_n = c2_b_n;
  c2_c_ia0 = c2_b_ia0;
  c2_c_ix0 = c2_b_ix0;
  if (c2_c_m == 0) {
  } else if (c2_c_n == 0) {
  } else {
    c2_a = c2_c_m - 1;
    c2_mm1 = c2_a;
    c2_b_a = c2_c_n;
    c2_nm1 = c2_b_a;
    c2_b = c2_mm1;
    c2_c = c2_b;
    c2_b_b = c2_c;
    c2_iyend = c2_b_b;
    c2_b_iyend = c2_iyend + 1;
    c2_c_b = c2_b_iyend;
    c2_d_b = c2_c_b;
    if (1 > c2_d_b) {
      c2_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_overflow = (c2_d_b > 2147483646);
    }

    if (c2_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_overflow);
    }

    for (c2_iy = 1; c2_iy <= c2_b_iyend; c2_iy++) {
      c2_b_iy = c2_iy;
      c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_iy), 1, 3, 1, 0) - 1] = 0.0;
    }

    c2_ix = c2_c_ix0;
    c2_d_ia0 = c2_c_ia0;
    c2_e_b = c2_nm1 - 1;
    c2_b_c = 3 * c2_e_b;
    c2_c_a = c2_c_ia0;
    c2_f_b = c2_b_c;
    c2_i87 = c2_c_a + c2_f_b;
    c2_d_a = c2_d_ia0;
    c2_g_b = c2_i87;
    c2_e_a = c2_d_a;
    c2_h_b = c2_g_b;
    if (c2_e_a > c2_h_b) {
      c2_b_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_b_overflow = (c2_h_b > 2147483644);
    }

    if (c2_b_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
    }

    for (c2_iac = c2_d_ia0; c2_iac <= c2_i87; c2_iac += 3) {
      c2_b_iac = c2_iac;
      c2_c_c = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_ix), 1, 9, 1, 0) - 1];
      c2_b_iy = 1;
      c2_c_iac = c2_b_iac;
      c2_f_a = c2_b_iac;
      c2_i_b = c2_mm1;
      c2_i88 = c2_f_a + c2_i_b;
      c2_g_a = c2_c_iac;
      c2_j_b = c2_i88;
      c2_h_a = c2_g_a;
      c2_k_b = c2_j_b;
      if (c2_h_a > c2_k_b) {
        c2_c_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_c_overflow = (c2_k_b > 2147483646);
      }

      if (c2_c_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_c_overflow);
      }

      for (c2_ia = c2_c_iac; c2_ia <= c2_i88; c2_ia++) {
        c2_b_ia = c2_ia;
        c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_iy), 1, 3, 1, 0) - 1] = c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK(
          "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_iy), 1, 3, 1, 0) - 1]
          + c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_ia), 1, 9, 1, 0) - 1] * c2_c_c;
        c2_i_a = c2_b_iy + 1;
        c2_b_iy = c2_i_a;
      }

      c2_j_a = c2_ix + 1;
      c2_ix = c2_j_a;
    }
  }
}

static void c2_d_eml_matlab_zlarf(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, int32_T c2_iv0, real_T c2_tau,
  real_T c2_C[9], int32_T c2_ic0, real_T c2_work[3])
{
  int32_T c2_lastv;
  int32_T c2_a;
  int32_T c2_b_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_b;
  int32_T c2_b_c;
  int32_T c2_c_a;
  int32_T c2_c_b;
  int32_T c2_d_a;
  int32_T c2_d_b;
  int32_T c2_i;
  int32_T c2_e_a;
  int32_T c2_f_a;
  int32_T c2_g_a;
  int32_T c2_h_a;
  int32_T c2_b_m;
  int32_T c2_b_n;
  int32_T c2_ia0;
  int32_T c2_lastc;
  int32_T c2_i_a;
  int32_T c2_j_a;
  int32_T c2_c_c;
  int32_T c2_k_a;
  int32_T c2_l_a;
  int32_T c2_d_c;
  int32_T c2_m_a;
  int32_T c2_e_b;
  int32_T c2_n_a;
  int32_T c2_f_b;
  int32_T c2_coltop;
  int32_T c2_o_a;
  int32_T c2_p_a;
  int32_T c2_e_c;
  int32_T c2_q_a;
  int32_T c2_g_b;
  int32_T c2_r_a;
  int32_T c2_h_b;
  int32_T c2_colbottom;
  int32_T c2_b_coltop;
  int32_T c2_b_colbottom;
  int32_T c2_s_a;
  int32_T c2_i_b;
  int32_T c2_t_a;
  int32_T c2_j_b;
  boolean_T c2_overflow;
  int32_T c2_ia;
  int32_T c2_b_ia;
  int32_T c2_u_a;
  int32_T c2_v_a;
  int32_T c2_i89;
  int32_T c2_i90;
  int32_T c2_i91;
  real_T c2_b_C[9];
  int32_T c2_i92;
  int32_T c2_i93;
  int32_T c2_i94;
  real_T c2_c_C[9];
  int32_T c2_c_m;
  int32_T c2_c_n;
  real_T c2_alpha1;
  int32_T c2_ix0;
  int32_T c2_b_ia0;
  int32_T c2_d_m;
  int32_T c2_d_n;
  real_T c2_b_alpha1;
  int32_T c2_b_ix0;
  int32_T c2_c_ia0;
  int32_T c2_e_m;
  int32_T c2_e_n;
  real_T c2_c_alpha1;
  int32_T c2_c_ix0;
  int32_T c2_d_ia0;
  int32_T c2_f_m;
  int32_T c2_f_n;
  real_T c2_d_alpha1;
  int32_T c2_d_ix0;
  int32_T c2_e_ia0;
  int32_T c2_g_m;
  int32_T c2_g_n;
  real_T c2_e_alpha1;
  int32_T c2_e_ix0;
  int32_T c2_f_ia0;
  int32_T c2_ixstart;
  int32_T c2_w_a;
  int32_T c2_jA;
  int32_T c2_jy;
  int32_T c2_h_n;
  int32_T c2_k_b;
  int32_T c2_l_b;
  boolean_T c2_b_overflow;
  int32_T c2_j;
  real_T c2_yjy;
  real_T c2_temp;
  int32_T c2_ix;
  int32_T c2_m_b;
  int32_T c2_i95;
  int32_T c2_x_a;
  int32_T c2_n_b;
  int32_T c2_i96;
  int32_T c2_y_a;
  int32_T c2_o_b;
  int32_T c2_ab_a;
  int32_T c2_p_b;
  boolean_T c2_c_overflow;
  int32_T c2_ijA;
  int32_T c2_b_ijA;
  int32_T c2_bb_a;
  int32_T c2_cb_a;
  int32_T c2_db_a;
  int32_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  if (c2_tau != 0.0) {
    c2_lastv = c2_m;
    c2_a = c2_lastv;
    c2_b_a = c2_a;
    c2_c = c2_b_a;
    c2_b = c2_c - 1;
    c2_b_b = c2_b;
    c2_b_c = c2_b_b;
    c2_c_a = c2_iv0;
    c2_c_b = c2_b_c;
    c2_d_a = c2_c_a;
    c2_d_b = c2_c_b;
    c2_i = c2_d_a + c2_d_b;
    exitg3 = false;
    while ((exitg3 == false) && (c2_lastv > 0)) {
      if (c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_i), 1, 9, 1, 0) - 1] == 0.0) {
        c2_e_a = c2_lastv;
        c2_f_a = c2_e_a - 1;
        c2_lastv = c2_f_a;
        c2_g_a = c2_i;
        c2_h_a = c2_g_a - 1;
        c2_i = c2_h_a;
      } else {
        exitg3 = true;
      }
    }

    c2_b_m = c2_lastv;
    c2_b_n = c2_n;
    c2_ia0 = c2_ic0;
    c2_lastc = c2_b_n;
    exitg2 = false;
    while ((exitg2 == false) && (c2_lastc > 0)) {
      c2_i_a = c2_lastc;
      c2_j_a = c2_i_a;
      c2_c_c = c2_j_a;
      c2_k_a = c2_c_c - 1;
      c2_l_a = c2_k_a;
      c2_d_c = c2_l_a * 3;
      c2_m_a = c2_ia0;
      c2_e_b = c2_d_c;
      c2_n_a = c2_m_a;
      c2_f_b = c2_e_b;
      c2_coltop = c2_n_a + c2_f_b;
      c2_o_a = c2_b_m;
      c2_p_a = c2_o_a;
      c2_e_c = c2_p_a;
      c2_q_a = c2_coltop;
      c2_g_b = c2_e_c - 1;
      c2_r_a = c2_q_a;
      c2_h_b = c2_g_b;
      c2_colbottom = c2_r_a + c2_h_b;
      c2_b_coltop = c2_coltop;
      c2_b_colbottom = c2_colbottom;
      c2_s_a = c2_b_coltop;
      c2_i_b = c2_b_colbottom;
      c2_t_a = c2_s_a;
      c2_j_b = c2_i_b;
      if (c2_t_a > c2_j_b) {
        c2_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_overflow = (c2_j_b > 2147483646);
      }

      if (c2_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_overflow);
      }

      c2_ia = c2_b_coltop;
      do {
        exitg1 = 0;
        if (c2_ia <= c2_b_colbottom) {
          c2_b_ia = c2_ia;
          if (c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                "", (real_T)c2_b_ia), 1, 9, 1, 0) - 1] != 0.0) {
            exitg1 = 1;
          } else {
            c2_ia++;
          }
        } else {
          c2_u_a = c2_lastc;
          c2_v_a = c2_u_a - 1;
          c2_lastc = c2_v_a;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    c2_lastv = 0;
    c2_lastc = 0;
  }

  if (c2_lastv > 0) {
    c2_i89 = 0;
    for (c2_i90 = 0; c2_i90 < 3; c2_i90++) {
      for (c2_i91 = 0; c2_i91 < 3; c2_i91++) {
        c2_b_C[c2_i91 + c2_i89] = c2_C[c2_i91 + c2_i89];
      }

      c2_i89 += 3;
    }

    c2_i92 = 0;
    for (c2_i93 = 0; c2_i93 < 3; c2_i93++) {
      for (c2_i94 = 0; c2_i94 < 3; c2_i94++) {
        c2_c_C[c2_i94 + c2_i92] = c2_C[c2_i94 + c2_i92];
      }

      c2_i92 += 3;
    }

    c2_d_eml_xgemv(chartInstance, c2_lastv, c2_lastc, c2_b_C, c2_ic0, c2_c_C,
                   c2_iv0, c2_work);
    c2_c_m = c2_lastv;
    c2_c_n = c2_lastc;
    c2_alpha1 = -c2_tau;
    c2_ix0 = c2_iv0;
    c2_b_ia0 = c2_ic0;
    c2_d_m = c2_c_m;
    c2_d_n = c2_c_n;
    c2_b_alpha1 = c2_alpha1;
    c2_b_ix0 = c2_ix0;
    c2_c_ia0 = c2_b_ia0;
    c2_e_m = c2_d_m;
    c2_e_n = c2_d_n;
    c2_c_alpha1 = c2_b_alpha1;
    c2_c_ix0 = c2_b_ix0;
    c2_d_ia0 = c2_c_ia0;
    c2_d_threshold(chartInstance);
    c2_f_m = c2_e_m;
    c2_f_n = c2_e_n;
    c2_d_alpha1 = c2_c_alpha1;
    c2_d_ix0 = c2_c_ix0;
    c2_e_ia0 = c2_d_ia0;
    c2_g_m = c2_f_m;
    c2_g_n = c2_f_n;
    c2_e_alpha1 = c2_d_alpha1;
    c2_e_ix0 = c2_d_ix0;
    c2_f_ia0 = c2_e_ia0;
    if (c2_e_alpha1 == 0.0) {
    } else {
      c2_ixstart = c2_e_ix0;
      c2_w_a = c2_f_ia0 - 1;
      c2_jA = c2_w_a;
      c2_jy = 1;
      c2_h_n = c2_g_n;
      c2_k_b = c2_h_n;
      c2_l_b = c2_k_b;
      if (1 > c2_l_b) {
        c2_b_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_b_overflow = (c2_l_b > 2147483646);
      }

      if (c2_b_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
      }

      for (c2_j = 1; c2_j <= c2_h_n; c2_j++) {
        c2_yjy = c2_work[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_jy), 1, 3, 1, 0) - 1];
        if (c2_yjy != 0.0) {
          c2_temp = c2_yjy * c2_e_alpha1;
          c2_ix = c2_ixstart;
          c2_m_b = c2_jA + 1;
          c2_i95 = c2_m_b;
          c2_x_a = c2_g_m;
          c2_n_b = c2_jA;
          c2_i96 = c2_x_a + c2_n_b;
          c2_y_a = c2_i95;
          c2_o_b = c2_i96;
          c2_ab_a = c2_y_a;
          c2_p_b = c2_o_b;
          if (c2_ab_a > c2_p_b) {
            c2_c_overflow = false;
          } else {
            c2_eml_switch_helper(chartInstance);
            c2_c_overflow = (c2_p_b > 2147483646);
          }

          if (c2_c_overflow) {
            c2_check_forloop_overflow_error(chartInstance, c2_c_overflow);
          }

          for (c2_ijA = c2_i95; c2_ijA <= c2_i96; c2_ijA++) {
            c2_b_ijA = c2_ijA;
            c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
              (real_T)c2_b_ijA), 1, 9, 1, 0) - 1] =
              c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c2_b_ijA), 1, 9, 1, 0) - 1] +
              c2_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c2_ix), 1, 9, 1, 0) - 1] * c2_temp;
            c2_bb_a = c2_ix + 1;
            c2_ix = c2_bb_a;
          }
        }

        c2_cb_a = c2_jy + 1;
        c2_jy = c2_cb_a;
        c2_db_a = c2_jA + 3;
        c2_jA = c2_db_a;
      }
    }
  }
}

static void c2_d_eml_xgemv(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_m, int32_T c2_n, real_T c2_A[9], int32_T c2_ia0,
  real_T c2_x[9], int32_T c2_ix0, real_T c2_y[3])
{
  int32_T c2_b_m;
  int32_T c2_b_n;
  int32_T c2_b_ia0;
  int32_T c2_b_ix0;
  int32_T c2_c_m;
  int32_T c2_c_n;
  int32_T c2_c_ia0;
  int32_T c2_c_ix0;
  int32_T c2_a;
  int32_T c2_mm1;
  int32_T c2_b_a;
  int32_T c2_nm1;
  int32_T c2_b;
  int32_T c2_c;
  int32_T c2_b_b;
  int32_T c2_iyend;
  int32_T c2_b_iyend;
  int32_T c2_c_b;
  int32_T c2_d_b;
  boolean_T c2_overflow;
  int32_T c2_iy;
  int32_T c2_b_iy;
  int32_T c2_d_ia0;
  int32_T c2_e_b;
  int32_T c2_b_c;
  int32_T c2_c_a;
  int32_T c2_f_b;
  int32_T c2_i97;
  int32_T c2_d_a;
  int32_T c2_g_b;
  int32_T c2_e_a;
  int32_T c2_h_b;
  boolean_T c2_b_overflow;
  int32_T c2_iac;
  int32_T c2_b_iac;
  int32_T c2_ix;
  real_T c2_c_c;
  int32_T c2_c_iac;
  int32_T c2_f_a;
  int32_T c2_i_b;
  int32_T c2_i98;
  int32_T c2_g_a;
  int32_T c2_j_b;
  int32_T c2_h_a;
  int32_T c2_k_b;
  boolean_T c2_c_overflow;
  int32_T c2_ia;
  int32_T c2_b_ia;
  real_T c2_i_a;
  real_T c2_l_b;
  real_T c2_z;
  int32_T c2_j_a;
  int32_T c2_k_a;
  c2_b_m = c2_m;
  c2_b_n = c2_n;
  c2_b_ia0 = c2_ia0;
  c2_b_ix0 = c2_ix0;
  c2_c_threshold(chartInstance);
  c2_c_m = c2_b_m;
  c2_c_n = c2_b_n;
  c2_c_ia0 = c2_b_ia0;
  c2_c_ix0 = c2_b_ix0;
  if (c2_c_m == 0) {
  } else if (c2_c_n == 0) {
  } else {
    c2_a = c2_c_m;
    c2_mm1 = c2_a;
    c2_b_a = c2_c_n - 1;
    c2_nm1 = c2_b_a;
    c2_b = c2_nm1;
    c2_c = c2_b;
    c2_b_b = c2_c;
    c2_iyend = c2_b_b;
    c2_b_iyend = c2_iyend + 1;
    c2_c_b = c2_b_iyend;
    c2_d_b = c2_c_b;
    if (1 > c2_d_b) {
      c2_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_overflow = (c2_d_b > 2147483646);
    }

    if (c2_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_overflow);
    }

    for (c2_iy = 1; c2_iy <= c2_b_iyend; c2_iy++) {
      c2_b_iy = c2_iy;
      c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_iy), 1, 3, 1, 0) - 1] = 0.0;
    }

    c2_b_iy = 1;
    c2_d_ia0 = c2_c_ia0;
    c2_e_b = c2_nm1;
    c2_b_c = 3 * c2_e_b;
    c2_c_a = c2_c_ia0;
    c2_f_b = c2_b_c;
    c2_i97 = c2_c_a + c2_f_b;
    c2_d_a = c2_d_ia0;
    c2_g_b = c2_i97;
    c2_e_a = c2_d_a;
    c2_h_b = c2_g_b;
    if (c2_e_a > c2_h_b) {
      c2_b_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_b_overflow = (c2_h_b > 2147483644);
    }

    if (c2_b_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
    }

    for (c2_iac = c2_d_ia0; c2_iac <= c2_i97; c2_iac += 3) {
      c2_b_iac = c2_iac;
      c2_ix = c2_c_ix0;
      c2_c_c = 0.0;
      c2_c_iac = c2_b_iac;
      c2_f_a = c2_b_iac;
      c2_i_b = c2_mm1 - 1;
      c2_i98 = c2_f_a + c2_i_b;
      c2_g_a = c2_c_iac;
      c2_j_b = c2_i98;
      c2_h_a = c2_g_a;
      c2_k_b = c2_j_b;
      if (c2_h_a > c2_k_b) {
        c2_c_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_c_overflow = (c2_k_b > 2147483646);
      }

      if (c2_c_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_c_overflow);
      }

      for (c2_ia = c2_c_iac; c2_ia <= c2_i98; c2_ia++) {
        c2_b_ia = c2_ia;
        c2_i_a = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_b_ia), 1, 9, 1, 0) - 1];
        c2_l_b = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 9, 1, 0) - 1];
        c2_z = c2_i_a * c2_l_b;
        c2_c_c += c2_z;
        c2_j_a = c2_ix + 1;
        c2_ix = c2_j_a;
      }

      c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_iy), 1, 3, 1, 0) - 1] = c2_y[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_iy), 1, 3, 1, 0) - 1] +
        c2_c_c;
      c2_k_a = c2_b_iy + 1;
      c2_b_iy = c2_k_a;
    }
  }
}

static void c2_b_eml_matlab_zunghr(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, real_T c2_A[9], real_T c2_tau[2])
{
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_b_a;
  int32_T c2_c;
  int32_T c2_c_a;
  int32_T c2_d_a;
  int32_T c2_b_c;
  int32_T c2_b;
  int32_T c2_b_b;
  int32_T c2_ia;
  int32_T c2_e_a;
  int32_T c2_f_a;
  int32_T c2_i99;
  int32_T c2_c_b;
  int32_T c2_d_b;
  boolean_T c2_overflow;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_g_a;
  int32_T c2_e_b;
  int32_T c2_h_a;
  int32_T c2_f_b;
  int32_T c2_c_c;
  int32_T c2_i_a;
  int32_T c2_j_a;
  int32_T c2_iajm1;
  int32_T c2_k_a;
  int32_T c2_l_a;
  int32_T c2_i100;
  int32_T c2_m_a;
  int32_T c2_n_a;
  boolean_T c2_b_overflow;
  int32_T c2_c_i;
  int32_T c2_o_a;
  int32_T c2_g_b;
  int32_T c2_p_a;
  int32_T c2_h_b;
  int32_T c2_d_c;
  int32_T c2_q_a;
  int32_T c2_i_b;
  int32_T c2_r_a;
  int32_T c2_j_b;
  int32_T c2_e_c;
  int32_T c2_d_i;
  int32_T c2_k_b;
  int32_T c2_l_b;
  int32_T c2_f_c;
  int32_T c2_itau;
  int32_T c2_i101;
  real_T c2_work[3];
  int32_T c2_e_i;
  int32_T c2_m_b;
  int32_T c2_n_b;
  int32_T c2_g_c;
  int32_T c2_s_a;
  int32_T c2_t_a;
  int32_T c2_h_c;
  int32_T c2_u_a;
  int32_T c2_v_a;
  int32_T c2_i_c;
  int32_T c2_w_a;
  int32_T c2_o_b;
  int32_T c2_x_a;
  int32_T c2_p_b;
  int32_T c2_iaii;
  int32_T c2_q_b;
  int32_T c2_r_b;
  int32_T c2_j_c;
  int32_T c2_y_a;
  int32_T c2_ab_a;
  int32_T c2_k_c;
  int32_T c2_s_b;
  int32_T c2_t_b;
  int32_T c2_l_c;
  int32_T c2_bb_a;
  int32_T c2_cb_a;
  int32_T c2_m_c;
  int32_T c2_u_b;
  int32_T c2_v_b;
  int32_T c2_n_c;
  int32_T c2_db_a;
  int32_T c2_eb_a;
  int32_T c2_o_c;
  int32_T c2_fb_a;
  int32_T c2_gb_a;
  int32_T c2_i102;
  int32_T c2_w_b;
  int32_T c2_x_b;
  boolean_T c2_c_overflow;
  int32_T c2_c_j;
  int32_T c2_d_j;
  int32_T c2_hb_a;
  int32_T c2_y_b;
  int32_T c2_ib_a;
  int32_T c2_ab_b;
  int32_T c2_p_c;
  int32_T c2_jb_a;
  int32_T c2_kb_a;
  int32_T c2_lb_a;
  int32_T c2_mb_a;
  for (c2_j = 3; c2_j > 1; c2_j--) {
    c2_b_j = c2_j;
    c2_a = c2_b_j;
    c2_b_a = c2_a;
    c2_c = c2_b_a;
    c2_c_a = c2_c - 1;
    c2_d_a = c2_c_a;
    c2_b_c = c2_d_a * 3;
    c2_b = c2_b_c;
    c2_b_b = c2_b;
    c2_ia = c2_b_b;
    c2_e_a = c2_b_j;
    c2_f_a = c2_e_a - 1;
    c2_i99 = c2_f_a;
    c2_c_b = c2_i99;
    c2_d_b = c2_c_b;
    if (1 > c2_d_b) {
      c2_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_overflow = (c2_d_b > 2147483646);
    }

    if (c2_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_overflow);
    }

    for (c2_i = 1; c2_i <= c2_i99; c2_i++) {
      c2_b_i = c2_i;
      c2_g_a = c2_ia;
      c2_e_b = c2_b_i;
      c2_h_a = c2_g_a;
      c2_f_b = c2_e_b;
      c2_c_c = c2_h_a + c2_f_b;
      c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_c_c), 1, 9, 1, 0) - 1] = 0.0;
    }

    c2_i_a = c2_ia;
    c2_j_a = c2_i_a;
    c2_iajm1 = c2_j_a;
    c2_k_a = c2_b_j;
    c2_l_a = c2_k_a + 1;
    c2_i100 = c2_l_a;
    c2_m_a = c2_i100;
    c2_n_a = c2_m_a;
    if (c2_n_a > 3) {
      c2_b_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_b_overflow = false;
    }

    if (c2_b_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
    }

    for (c2_c_i = c2_i100; c2_c_i < 4; c2_c_i++) {
      c2_b_i = c2_c_i;
      c2_o_a = c2_ia;
      c2_g_b = c2_b_i;
      c2_p_a = c2_o_a;
      c2_h_b = c2_g_b;
      c2_d_c = c2_p_a + c2_h_b;
      c2_q_a = c2_iajm1 - 3;
      c2_i_b = c2_b_i;
      c2_r_a = c2_q_a;
      c2_j_b = c2_i_b;
      c2_e_c = c2_r_a + c2_j_b;
      c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_d_c), 1, 9, 1, 0) - 1] = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_e_c), 1, 9, 1, 0) - 1];
    }
  }

  for (c2_d_i = 1; c2_d_i < 4; c2_d_i++) {
    c2_b_i = c2_d_i;
    c2_k_b = c2_b_i;
    c2_l_b = c2_k_b;
    c2_f_c = c2_l_b;
    c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_f_c), 1, 9, 1, 0) - 1] = 0.0;
  }

  c2_A[0] = 1.0;
  c2_itau = 2;
  for (c2_i101 = 0; c2_i101 < 3; c2_i101++) {
    c2_work[c2_i101] = 0.0;
  }

  c2_e_i = 2;
  while (c2_e_i >= 1) {
    c2_m_b = c2_e_i;
    c2_n_b = c2_m_b;
    c2_g_c = c2_n_b;
    c2_s_a = c2_e_i;
    c2_t_a = c2_s_a;
    c2_h_c = c2_t_a;
    c2_u_a = c2_h_c - 1;
    c2_v_a = c2_u_a;
    c2_i_c = c2_v_a * 3;
    c2_w_a = c2_g_c + 4;
    c2_o_b = c2_i_c;
    c2_x_a = c2_w_a;
    c2_p_b = c2_o_b;
    c2_iaii = c2_x_a + c2_p_b;
    if (c2_e_i < 2) {
      c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_iaii), 1, 9, 1, 0) - 1] = 1.0;
      c2_q_b = c2_e_i;
      c2_r_b = c2_q_b;
      c2_j_c = 2 - c2_r_b;
      c2_y_a = c2_j_c;
      c2_ab_a = c2_y_a;
      c2_k_c = c2_ab_a;
      c2_s_b = c2_e_i;
      c2_t_b = c2_s_b;
      c2_l_c = 2 - c2_t_b;
      c2_bb_a = c2_iaii;
      c2_cb_a = c2_bb_a;
      c2_m_c = c2_cb_a;
      c2_d_eml_matlab_zlarf(chartInstance, c2_k_c + 1, c2_l_c, c2_iaii,
                            c2_tau[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_itau), 1, 2, 1, 0) - 1], c2_A, c2_m_c
                            + 3, c2_work);
    }

    if (c2_e_i < 2) {
      c2_u_b = c2_e_i;
      c2_v_b = c2_u_b;
      c2_n_c = 2 - c2_v_b;
      c2_db_a = c2_iaii;
      c2_eb_a = c2_db_a;
      c2_o_c = c2_eb_a;
      c2_c_eml_xscal(chartInstance, c2_n_c, -c2_tau[_SFD_EML_ARRAY_BOUNDS_CHECK(
        "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_itau), 1, 2, 1, 0) - 1],
                     c2_A, c2_o_c + 1);
    }

    c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_iaii), 1, 9, 1, 0) - 1] = 1.0 - c2_tau[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_itau), 1, 2, 1, 0) - 1];
    c2_fb_a = c2_e_i;
    c2_gb_a = c2_fb_a - 1;
    c2_i102 = c2_gb_a;
    c2_w_b = c2_i102;
    c2_x_b = c2_w_b;
    if (1 > c2_x_b) {
      c2_c_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_c_overflow = (c2_x_b > 2147483646);
    }

    if (c2_c_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_c_overflow);
    }

    for (c2_c_j = 1; c2_c_j <= c2_i102; c2_c_j++) {
      c2_d_j = c2_c_j;
      c2_hb_a = c2_iaii;
      c2_y_b = c2_d_j;
      c2_ib_a = c2_hb_a;
      c2_ab_b = c2_y_b;
      c2_p_c = c2_ib_a - c2_ab_b;
      c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_p_c), 1, 9, 1, 0) - 1] = 0.0;
    }

    c2_jb_a = c2_itau;
    c2_kb_a = c2_jb_a - 1;
    c2_itau = c2_kb_a;
    c2_lb_a = c2_e_i;
    c2_mb_a = c2_lb_a - 1;
    c2_e_i = c2_mb_a;
  }
}

static int32_T c2_b_eml_dlahqr(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, real_T c2_h[9], real_T c2_z[9])
{
  int32_T c2_info;
  int32_T c2_i;
  int32_T c2_L;
  boolean_T c2_goto150;
  int32_T c2_its;
  int32_T c2_b_its;
  int32_T c2_k;
  int32_T c2_a;
  int32_T c2_b_a;
  int32_T c2_c;
  int32_T c2_c_a;
  int32_T c2_d_a;
  int32_T c2_b_c;
  int32_T c2_e_a;
  int32_T c2_f_a;
  int32_T c2_c_c;
  real_T c2_tst;
  int32_T c2_g_a;
  int32_T c2_h_a;
  int32_T c2_d_c;
  int32_T c2_i_a;
  int32_T c2_j_a;
  int32_T c2_e_c;
  int32_T c2_k_a;
  int32_T c2_l_a;
  int32_T c2_f_c;
  int32_T c2_m_a;
  int32_T c2_n_a;
  int32_T c2_g_c;
  int32_T c2_o_a;
  int32_T c2_p_a;
  int32_T c2_h_c;
  int32_T c2_q_a;
  int32_T c2_r_a;
  int32_T c2_i_c;
  int32_T c2_s_a;
  int32_T c2_t_a;
  int32_T c2_j_c;
  real_T c2_htmp1;
  int32_T c2_u_a;
  int32_T c2_v_a;
  int32_T c2_k_c;
  real_T c2_htmp2;
  real_T c2_ab;
  real_T c2_ba;
  int32_T c2_w_a;
  int32_T c2_x_a;
  int32_T c2_l_c;
  int32_T c2_y_a;
  int32_T c2_ab_a;
  int32_T c2_m_c;
  real_T c2_aa;
  real_T c2_bb;
  real_T c2_s;
  real_T c2_A;
  real_T c2_B;
  real_T c2_x;
  real_T c2_y;
  real_T c2_b_x;
  real_T c2_b_y;
  real_T c2_c_x;
  real_T c2_c_y;
  real_T c2_d_y;
  real_T c2_b_A;
  real_T c2_b_B;
  real_T c2_d_x;
  real_T c2_e_y;
  real_T c2_e_x;
  real_T c2_f_y;
  real_T c2_f_x;
  real_T c2_g_y;
  real_T c2_h_y;
  real_T c2_varargin_2;
  real_T c2_varargin_3;
  real_T c2_i_y;
  real_T c2_j_y;
  real_T c2_yk;
  real_T c2_k_y;
  real_T c2_maxval;
  int32_T c2_bb_a;
  int32_T c2_cb_a;
  int32_T c2_db_a;
  int32_T c2_eb_a;
  int32_T c2_n_c;
  int32_T c2_fb_a;
  int32_T c2_gb_a;
  int32_T c2_o_c;
  int32_T c2_hb_a;
  int32_T c2_ib_a;
  int32_T c2_p_c;
  int32_T c2_jb_a;
  int32_T c2_kb_a;
  int32_T c2_q_c;
  int32_T c2_lb_a;
  int32_T c2_mb_a;
  int32_T c2_r_c;
  real_T c2_h11;
  real_T c2_h12;
  real_T c2_h21;
  real_T c2_h22;
  int32_T c2_nb_a;
  int32_T c2_ob_a;
  int32_T c2_s_c;
  int32_T c2_pb_a;
  int32_T c2_qb_a;
  int32_T c2_t_c;
  int32_T c2_rb_a;
  int32_T c2_sb_a;
  int32_T c2_u_c;
  int32_T c2_tb_a;
  int32_T c2_ub_a;
  int32_T c2_v_c;
  int32_T c2_vb_a;
  int32_T c2_wb_a;
  int32_T c2_w_c;
  int32_T c2_xb_a;
  int32_T c2_yb_a;
  int32_T c2_x_c;
  int32_T c2_ac_a;
  int32_T c2_bc_a;
  int32_T c2_y_c;
  real_T c2_rt1r;
  real_T c2_rt1i;
  real_T c2_rt2r;
  real_T c2_rt2i;
  real_T c2_c_A;
  real_T c2_c_B;
  real_T c2_g_x;
  real_T c2_l_y;
  real_T c2_h_x;
  real_T c2_m_y;
  real_T c2_i_x;
  real_T c2_n_y;
  real_T c2_d_A;
  real_T c2_d_B;
  real_T c2_j_x;
  real_T c2_o_y;
  real_T c2_k_x;
  real_T c2_p_y;
  real_T c2_l_x;
  real_T c2_q_y;
  real_T c2_e_A;
  real_T c2_e_B;
  real_T c2_m_x;
  real_T c2_r_y;
  real_T c2_n_x;
  real_T c2_s_y;
  real_T c2_o_x;
  real_T c2_t_y;
  real_T c2_f_A;
  real_T c2_f_B;
  real_T c2_p_x;
  real_T c2_u_y;
  real_T c2_q_x;
  real_T c2_v_y;
  real_T c2_r_x;
  real_T c2_w_y;
  real_T c2_g_A;
  real_T c2_s_x;
  real_T c2_t_x;
  real_T c2_u_x;
  real_T c2_tr;
  real_T c2_det;
  real_T c2_rtdisc;
  int32_T c2_cc_a;
  int32_T c2_dc_a;
  int32_T c2_m;
  int32_T c2_ec_a;
  int32_T c2_fc_a;
  int32_T c2_ab_c;
  real_T c2_h21s;
  int32_T c2_gc_a;
  int32_T c2_hc_a;
  int32_T c2_bb_c;
  real_T c2_h_A;
  real_T c2_g_B;
  real_T c2_v_x;
  real_T c2_x_y;
  real_T c2_w_x;
  real_T c2_y_y;
  real_T c2_x_x;
  real_T c2_ab_y;
  int32_T c2_ic_a;
  int32_T c2_jc_a;
  int32_T c2_cb_c;
  real_T c2_i_A;
  real_T c2_h_B;
  real_T c2_y_x;
  real_T c2_bb_y;
  real_T c2_ab_x;
  real_T c2_cb_y;
  real_T c2_bb_x;
  real_T c2_db_y;
  real_T c2_eb_y;
  real_T c2_j_A;
  real_T c2_i_B;
  real_T c2_cb_x;
  real_T c2_fb_y;
  real_T c2_db_x;
  real_T c2_gb_y;
  real_T c2_eb_x;
  real_T c2_hb_y;
  real_T c2_ib_y;
  real_T c2_v[3];
  int32_T c2_kc_a;
  int32_T c2_lc_a;
  int32_T c2_db_c;
  int32_T c2_mc_a;
  int32_T c2_nc_a;
  int32_T c2_eb_c;
  int32_T c2_oc_a;
  int32_T c2_pc_a;
  int32_T c2_fb_c;
  int32_T c2_qc_a;
  int32_T c2_rc_a;
  int32_T c2_gb_c;
  real_T c2_k_A;
  real_T c2_j_B;
  real_T c2_fb_x;
  real_T c2_jb_y;
  real_T c2_gb_x;
  real_T c2_kb_y;
  real_T c2_hb_x;
  real_T c2_lb_y;
  real_T c2_mb_y;
  real_T c2_l_A;
  real_T c2_k_B;
  real_T c2_ib_x;
  real_T c2_nb_y;
  real_T c2_jb_x;
  real_T c2_ob_y;
  real_T c2_kb_x;
  real_T c2_pb_y;
  real_T c2_qb_y;
  real_T c2_m_A;
  real_T c2_l_B;
  real_T c2_lb_x;
  real_T c2_rb_y;
  real_T c2_mb_x;
  real_T c2_sb_y;
  real_T c2_nb_x;
  real_T c2_tb_y;
  real_T c2_ub_y;
  int32_T c2_sc_a;
  int32_T c2_tc_a;
  int32_T c2_hb_c;
  int32_T c2_uc_a;
  int32_T c2_vc_a;
  int32_T c2_ib_c;
  int32_T c2_wc_a;
  int32_T c2_xc_a;
  int32_T c2_jb_c;
  int32_T c2_yc_a;
  int32_T c2_ad_a;
  int32_T c2_kb_c;
  int32_T c2_bd_a;
  int32_T c2_cd_a;
  int32_T c2_lb_c;
  int32_T c2_dd_a;
  int32_T c2_ed_a;
  int32_T c2_b_m;
  int32_T c2_fd_a;
  int32_T c2_gd_a;
  int32_T c2_i103;
  int32_T c2_hd_a;
  int32_T c2_b;
  int32_T c2_id_a;
  int32_T c2_b_b;
  boolean_T c2_overflow;
  int32_T c2_b_k;
  int32_T c2_jd_a;
  int32_T c2_c_b;
  int32_T c2_kd_a;
  int32_T c2_d_b;
  int32_T c2_mb_c;
  int32_T c2_ld_a;
  int32_T c2_md_a;
  int32_T c2_nb_c;
  int32_T c2_b_varargin_2;
  int32_T c2_b_varargin_3;
  int32_T c2_vb_y;
  int32_T c2_wb_y;
  int32_T c2_b_yk;
  int32_T c2_xb_y;
  int32_T c2_nr;
  int32_T c2_nd_a;
  int32_T c2_od_a;
  int32_T c2_ob_c;
  int32_T c2_pd_a;
  int32_T c2_qd_a;
  int32_T c2_pb_c;
  int32_T c2_e_b;
  int32_T c2_f_b;
  int32_T c2_qb_c;
  int32_T c2_rd_a;
  int32_T c2_g_b;
  int32_T c2_sd_a;
  int32_T c2_h_b;
  int32_T c2_hoffset;
  int32_T c2_b_nr;
  int32_T c2_i_b;
  int32_T c2_j_b;
  boolean_T c2_b_overflow;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_td_a;
  int32_T c2_k_b;
  int32_T c2_ud_a;
  int32_T c2_l_b;
  int32_T c2_rb_c;
  real_T c2_alpha;
  real_T c2_b_alpha;
  real_T c2_t1;
  real_T c2_b_t1;
  int32_T c2_vd_a;
  int32_T c2_wd_a;
  int32_T c2_sb_c;
  int32_T c2_xd_a;
  int32_T c2_yd_a;
  int32_T c2_tb_c;
  int32_T c2_ae_a;
  int32_T c2_be_a;
  int32_T c2_ub_c;
  int32_T c2_ce_a;
  int32_T c2_de_a;
  int32_T c2_vb_c;
  int32_T c2_ee_a;
  int32_T c2_fe_a;
  int32_T c2_wb_c;
  int32_T c2_ge_a;
  int32_T c2_he_a;
  int32_T c2_xb_c;
  int32_T c2_ie_a;
  int32_T c2_je_a;
  int32_T c2_yb_c;
  int32_T c2_ke_a;
  int32_T c2_le_a;
  int32_T c2_ac_c;
  real_T c2_v2;
  real_T c2_t2;
  real_T c2_v3;
  real_T c2_t3;
  int32_T c2_c_k;
  int32_T c2_me_a;
  int32_T c2_ne_a;
  boolean_T c2_c_overflow;
  int32_T c2_c_j;
  int32_T c2_oe_a;
  int32_T c2_pe_a;
  int32_T c2_bc_c;
  int32_T c2_qe_a;
  int32_T c2_re_a;
  int32_T c2_cc_c;
  real_T c2_sum1;
  int32_T c2_se_a;
  int32_T c2_te_a;
  int32_T c2_dc_c;
  int32_T c2_ue_a;
  int32_T c2_ve_a;
  int32_T c2_ec_c;
  int32_T c2_we_a;
  int32_T c2_xe_a;
  int32_T c2_fc_c;
  int32_T c2_ye_a;
  int32_T c2_af_a;
  int32_T c2_gc_c;
  int32_T c2_bf_a;
  int32_T c2_cf_a;
  int32_T c2_hc_c;
  int32_T c2_varargin_1;
  int32_T c2_c_varargin_2;
  int32_T c2_d_varargin_2;
  int32_T c2_c_varargin_3;
  int32_T c2_ob_x;
  int32_T c2_yb_y;
  int32_T c2_pb_x;
  int32_T c2_ac_y;
  int32_T c2_xk;
  int32_T c2_c_yk;
  int32_T c2_qb_x;
  int32_T c2_bc_y;
  int32_T c2_i104;
  int32_T c2_m_b;
  int32_T c2_n_b;
  boolean_T c2_d_overflow;
  int32_T c2_d_j;
  int32_T c2_df_a;
  int32_T c2_ef_a;
  int32_T c2_ic_c;
  int32_T c2_ff_a;
  int32_T c2_gf_a;
  int32_T c2_jc_c;
  int32_T c2_hf_a;
  int32_T c2_if_a;
  int32_T c2_kc_c;
  int32_T c2_jf_a;
  int32_T c2_kf_a;
  int32_T c2_lc_c;
  int32_T c2_lf_a;
  int32_T c2_mf_a;
  int32_T c2_mc_c;
  int32_T c2_nf_a;
  int32_T c2_of_a;
  int32_T c2_nc_c;
  int32_T c2_e_j;
  int32_T c2_pf_a;
  int32_T c2_qf_a;
  int32_T c2_oc_c;
  int32_T c2_rf_a;
  int32_T c2_sf_a;
  int32_T c2_pc_c;
  int32_T c2_tf_a;
  int32_T c2_uf_a;
  int32_T c2_qc_c;
  int32_T c2_vf_a;
  int32_T c2_wf_a;
  int32_T c2_rc_c;
  int32_T c2_xf_a;
  int32_T c2_yf_a;
  int32_T c2_sc_c;
  int32_T c2_ag_a;
  int32_T c2_bg_a;
  int32_T c2_tc_c;
  int32_T c2_d_k;
  int32_T c2_cg_a;
  int32_T c2_dg_a;
  boolean_T c2_e_overflow;
  int32_T c2_f_j;
  int32_T c2_eg_a;
  int32_T c2_fg_a;
  int32_T c2_uc_c;
  int32_T c2_gg_a;
  int32_T c2_hg_a;
  int32_T c2_vc_c;
  int32_T c2_ig_a;
  int32_T c2_jg_a;
  int32_T c2_wc_c;
  int32_T c2_b_i;
  int32_T c2_o_b;
  int32_T c2_p_b;
  boolean_T c2_f_overflow;
  int32_T c2_g_j;
  int32_T c2_kg_a;
  int32_T c2_lg_a;
  int32_T c2_xc_c;
  int32_T c2_mg_a;
  int32_T c2_ng_a;
  int32_T c2_yc_c;
  int32_T c2_og_a;
  int32_T c2_pg_a;
  int32_T c2_ad_c;
  int32_T c2_h_j;
  int32_T c2_qg_a;
  int32_T c2_rg_a;
  int32_T c2_bd_c;
  int32_T c2_sg_a;
  int32_T c2_tg_a;
  int32_T c2_cd_c;
  int32_T c2_ug_a;
  int32_T c2_vg_a;
  int32_T c2_dd_c;
  int32_T c2_wg_a;
  int32_T c2_xg_a;
  int32_T c2_ed_c;
  int32_T c2_yg_a;
  int32_T c2_ah_a;
  int32_T c2_im1;
  real_T c2_d8;
  real_T c2_d9;
  real_T c2_d10;
  real_T c2_d11;
  real_T c2_sn;
  real_T c2_cs;
  real_T c2_unusedU3;
  real_T c2_unusedU2;
  real_T c2_unusedU1;
  real_T c2_unusedU0;
  real_T c2_b_cs;
  real_T c2_b_sn;
  int32_T c2_q_b;
  int32_T c2_r_b;
  int32_T c2_fd_c;
  int32_T c2_bh_a;
  int32_T c2_ch_a;
  int32_T c2_gd_c;
  int32_T c2_dh_a;
  int32_T c2_s_b;
  int32_T c2_eh_a;
  int32_T c2_t_b;
  int32_T c2_hd_c;
  int32_T c2_fh_a;
  int32_T c2_gh_a;
  int32_T c2_id_c;
  int32_T c2_hh_a;
  int32_T c2_u_b;
  int32_T c2_ih_a;
  int32_T c2_v_b;
  int32_T c2_jd_c;
  int32_T c2_jh_a;
  int32_T c2_kh_a;
  int32_T c2_kd_c;
  int32_T c2_lh_a;
  int32_T c2_mh_a;
  int32_T c2_ld_c;
  int32_T c2_nh_a;
  int32_T c2_oh_a;
  int32_T c2_md_c;
  int32_T c2_w_b;
  int32_T c2_x_b;
  int32_T c2_nd_c;
  int32_T c2_ph_a;
  int32_T c2_qh_a;
  int32_T c2_od_c;
  int32_T c2_y_b;
  int32_T c2_ab_b;
  int32_T c2_pd_c;
  int32_T c2_rh_a;
  int32_T c2_sh_a;
  int32_T c2_qd_c;
  int32_T c2_th_a;
  int32_T c2_uh_a;
  int32_T c2_rd_c;
  int32_T c2_bb_b;
  int32_T c2_cb_b;
  int32_T c2_sd_c;
  int32_T c2_vh_a;
  int32_T c2_wh_a;
  int32_T c2_td_c;
  int32_T c2_db_b;
  int32_T c2_eb_b;
  int32_T c2_ud_c;
  int32_T c2_xh_a;
  int32_T c2_yh_a;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  boolean_T exitg4;
  boolean_T guard1 = false;
  c2_info = 0;
  c2_h[2] = 0.0;
  c2_realmin(chartInstance);
  c2_eps(chartInstance);
  c2_i = 3;
  exitg1 = false;
  while ((exitg1 == false) && (c2_i >= 1)) {
    c2_L = 1;
    c2_goto150 = false;
    c2_its = 0;
    exitg2 = false;
    while ((exitg2 == false) && (c2_its < 31)) {
      c2_b_its = c2_its;
      c2_k = c2_i;
      exitg4 = false;
      while ((exitg4 == false) && (c2_k > c2_L)) {
        c2_a = c2_k;
        c2_b_a = c2_a - 1;
        c2_c = c2_b_a;
        if (c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
               _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 1, 0) + 3 *
              (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                 (real_T)c2_c), 1, 3, 2, 0) - 1)) - 1]) <=
            3.0062525400134592E-292) {
          exitg4 = true;
        } else {
          c2_c_a = c2_k;
          c2_d_a = c2_c_a - 1;
          c2_b_c = c2_d_a;
          c2_e_a = c2_k;
          c2_f_a = c2_e_a - 1;
          c2_c_c = c2_f_a;
          c2_tst = c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_c), 1, 3, 1, 0) + 3 *
            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_c_c), 1, 3, 2, 0) - 1)) - 1]) + c2_abs(chartInstance,
            c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_k), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1]);
          if (c2_tst == 0.0) {
            c2_g_a = c2_k;
            c2_h_a = c2_g_a - 2;
            c2_d_c = c2_h_a;
            if (c2_d_c >= 1) {
              c2_i_a = c2_k;
              c2_j_a = c2_i_a - 1;
              c2_e_c = c2_j_a;
              c2_k_a = c2_k;
              c2_l_a = c2_k_a - 2;
              c2_f_c = c2_l_a;
              c2_tst += c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_e_c), 1, 3, 1, 0)
                + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_f_c), 1, 3, 2, 0) - 1)) - 1]);
            }

            c2_m_a = c2_k;
            c2_n_a = c2_m_a + 1;
            c2_g_c = c2_n_a;
            if (c2_g_c <= 3) {
              c2_o_a = c2_k;
              c2_p_a = c2_o_a + 1;
              c2_h_c = c2_p_a;
              c2_tst += c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_h_c), 1, 3, 1, 0)
                + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1]);
            }
          }

          c2_q_a = c2_k;
          c2_r_a = c2_q_a - 1;
          c2_i_c = c2_r_a;
          guard1 = false;
          if (c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
                 (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 1, 0) + 3 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c2_i_c), 1, 3, 2, 0) - 1)) - 1]) <=
              2.2204460492503131E-16 * c2_tst) {
            c2_s_a = c2_k;
            c2_t_a = c2_s_a - 1;
            c2_j_c = c2_t_a;
            c2_htmp1 = c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK(
              "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 1, 0) + 3
              * (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                                  (real_T)c2_j_c), 1, 3, 2, 0) - 1)) - 1]);
            c2_u_a = c2_k;
            c2_v_a = c2_u_a - 1;
            c2_k_c = c2_v_a;
            c2_htmp2 = c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK(
              "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_k_c), 1, 3, 1, 0) +
              3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1]);
            if (c2_htmp1 > c2_htmp2) {
              c2_ab = c2_htmp1;
              c2_ba = c2_htmp2;
            } else {
              c2_ab = c2_htmp2;
              c2_ba = c2_htmp1;
            }

            c2_htmp1 = c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK(
              "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 1, 0) + 3
              * (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                                  (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1]);
            c2_w_a = c2_k;
            c2_x_a = c2_w_a - 1;
            c2_l_c = c2_x_a;
            c2_y_a = c2_k;
            c2_ab_a = c2_y_a - 1;
            c2_m_c = c2_ab_a;
            c2_htmp2 = c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK(
              "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_l_c), 1, 3, 1, 0) +
              3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
              "", (real_T)c2_m_c), 1, 3, 2, 0) - 1)) - 1] - c2_h
                              [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 1, 0) + 3 *
                                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
              _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1]);
            if (c2_htmp1 > c2_htmp2) {
              c2_aa = c2_htmp1;
              c2_bb = c2_htmp2;
            } else {
              c2_aa = c2_htmp2;
              c2_bb = c2_htmp1;
            }

            c2_s = c2_aa + c2_ab;
            c2_A = c2_ab;
            c2_B = c2_s;
            c2_x = c2_A;
            c2_y = c2_B;
            c2_b_x = c2_x;
            c2_b_y = c2_y;
            c2_c_x = c2_b_x;
            c2_c_y = c2_b_y;
            c2_d_y = c2_c_x / c2_c_y;
            c2_b_A = c2_aa;
            c2_b_B = c2_s;
            c2_d_x = c2_b_A;
            c2_e_y = c2_b_B;
            c2_e_x = c2_d_x;
            c2_f_y = c2_e_y;
            c2_f_x = c2_e_x;
            c2_g_y = c2_f_y;
            c2_h_y = c2_f_x / c2_g_y;
            c2_varargin_2 = 2.2204460492503131E-16 * (c2_bb * c2_h_y);
            c2_varargin_3 = c2_varargin_2;
            c2_i_y = c2_varargin_3;
            c2_j_y = c2_i_y;
            c2_b_eml_scalar_eg(chartInstance);
            c2_yk = c2_j_y;
            c2_k_y = c2_yk;
            c2_b_eml_scalar_eg(chartInstance);
            c2_maxval = muDoubleScalarMax(3.0062525400134592E-292, c2_k_y);
            if (c2_ba * c2_d_y <= c2_maxval) {
              exitg4 = true;
            } else {
              guard1 = true;
            }
          } else {
            guard1 = true;
          }

          if (guard1 == true) {
            c2_bb_a = c2_k;
            c2_cb_a = c2_bb_a - 1;
            c2_k = c2_cb_a;
          }
        }
      }

      c2_L = c2_k;
      if (c2_L > 1) {
        c2_db_a = c2_L;
        c2_eb_a = c2_db_a - 1;
        c2_n_c = c2_eb_a;
        c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_L), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
                (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_n_c), 1, 3, 2, 0) - 1))
          - 1] = 0.0;
      }

      c2_fb_a = c2_i;
      c2_gb_a = c2_fb_a - 1;
      c2_o_c = c2_gb_a;
      if (c2_L >= c2_o_c) {
        c2_goto150 = true;
        exitg2 = true;
      } else {
        if (c2_b_its == 10) {
          c2_hb_a = c2_L;
          c2_ib_a = c2_hb_a + 1;
          c2_p_c = c2_ib_a;
          c2_jb_a = c2_L;
          c2_kb_a = c2_jb_a + 2;
          c2_q_c = c2_kb_a;
          c2_lb_a = c2_L;
          c2_mb_a = c2_lb_a + 1;
          c2_r_c = c2_mb_a;
          c2_s = c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_p_c), 1, 3, 1, 0) + 3 *
            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_L), 1, 3, 2, 0) - 1)) - 1]) + c2_abs(chartInstance, c2_h
            [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_q_c), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_r_c), 1, 3, 2, 0) - 1)) -
            1]);
          c2_h11 = 0.75 * c2_s + c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_L), 1, 3, 1, 0) + 3 *
            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_L), 1, 3, 2, 0) - 1)) - 1];
          c2_h12 = -0.4375 * c2_s;
          c2_h21 = c2_s;
          c2_h22 = c2_h11;
        } else if (c2_b_its == 20) {
          c2_nb_a = c2_i;
          c2_ob_a = c2_nb_a - 1;
          c2_s_c = c2_ob_a;
          c2_pb_a = c2_i;
          c2_qb_a = c2_pb_a - 1;
          c2_t_c = c2_qb_a;
          c2_rb_a = c2_i;
          c2_sb_a = c2_rb_a - 2;
          c2_u_c = c2_sb_a;
          c2_s = c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_i), 1, 3, 1, 0) + 3 *
            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_s_c), 1, 3, 2, 0) - 1)) - 1]) + c2_abs(chartInstance,
            c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_t_c), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_u_c), 1, 3, 2, 0) - 1)) -
            1]);
          c2_h11 = 0.75 * c2_s + c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_i), 1, 3, 1, 0) + 3 *
            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_i), 1, 3, 2, 0) - 1)) - 1];
          c2_h12 = -0.4375 * c2_s;
          c2_h21 = c2_s;
          c2_h22 = c2_h11;
        } else {
          c2_tb_a = c2_i;
          c2_ub_a = c2_tb_a - 1;
          c2_v_c = c2_ub_a;
          c2_vb_a = c2_i;
          c2_wb_a = c2_vb_a - 1;
          c2_w_c = c2_wb_a;
          c2_h11 = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_v_c), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_w_c), 1, 3, 2, 0) - 1)) - 1];
          c2_xb_a = c2_i;
          c2_yb_a = c2_xb_a - 1;
          c2_x_c = c2_yb_a;
          c2_h21 = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_i), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_x_c), 1, 3, 2, 0) - 1)) - 1];
          c2_ac_a = c2_i;
          c2_bc_a = c2_ac_a - 1;
          c2_y_c = c2_bc_a;
          c2_h12 = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_y_c), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_i), 1, 3, 2, 0) - 1)) - 1];
          c2_h22 = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_i), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_i), 1, 3, 2, 0) - 1)) - 1];
        }

        c2_s = ((c2_abs(chartInstance, c2_h11) + c2_abs(chartInstance, c2_h12))
                + c2_abs(chartInstance, c2_h21)) + c2_abs(chartInstance, c2_h22);
        if (c2_s == 0.0) {
          c2_rt1r = 0.0;
          c2_rt1i = 0.0;
          c2_rt2r = 0.0;
          c2_rt2i = 0.0;
        } else {
          c2_c_A = c2_h11;
          c2_c_B = c2_s;
          c2_g_x = c2_c_A;
          c2_l_y = c2_c_B;
          c2_h_x = c2_g_x;
          c2_m_y = c2_l_y;
          c2_i_x = c2_h_x;
          c2_n_y = c2_m_y;
          c2_h11 = c2_i_x / c2_n_y;
          c2_d_A = c2_h21;
          c2_d_B = c2_s;
          c2_j_x = c2_d_A;
          c2_o_y = c2_d_B;
          c2_k_x = c2_j_x;
          c2_p_y = c2_o_y;
          c2_l_x = c2_k_x;
          c2_q_y = c2_p_y;
          c2_h21 = c2_l_x / c2_q_y;
          c2_e_A = c2_h12;
          c2_e_B = c2_s;
          c2_m_x = c2_e_A;
          c2_r_y = c2_e_B;
          c2_n_x = c2_m_x;
          c2_s_y = c2_r_y;
          c2_o_x = c2_n_x;
          c2_t_y = c2_s_y;
          c2_h12 = c2_o_x / c2_t_y;
          c2_f_A = c2_h22;
          c2_f_B = c2_s;
          c2_p_x = c2_f_A;
          c2_u_y = c2_f_B;
          c2_q_x = c2_p_x;
          c2_v_y = c2_u_y;
          c2_r_x = c2_q_x;
          c2_w_y = c2_v_y;
          c2_h22 = c2_r_x / c2_w_y;
          c2_g_A = c2_h11 + c2_h22;
          c2_s_x = c2_g_A;
          c2_t_x = c2_s_x;
          c2_u_x = c2_t_x;
          c2_tr = c2_u_x / 2.0;
          c2_det = (c2_h11 - c2_tr) * (c2_h22 - c2_tr) - c2_h12 * c2_h21;
          c2_rtdisc = c2_abs(chartInstance, c2_det);
          c2_c_sqrt(chartInstance, &c2_rtdisc);
          if (c2_det >= 0.0) {
            c2_rt1r = c2_tr * c2_s;
            c2_rt2r = c2_rt1r;
            c2_rt1i = c2_rtdisc * c2_s;
            c2_rt2i = -c2_rt1i;
          } else {
            c2_rt1r = c2_tr + c2_rtdisc;
            c2_rt2r = c2_tr - c2_rtdisc;
            if (c2_abs(chartInstance, c2_rt1r - c2_h22) <= c2_abs(chartInstance,
                 c2_rt2r - c2_h22)) {
              c2_rt1r *= c2_s;
              c2_rt2r = c2_rt1r;
            } else {
              c2_rt2r *= c2_s;
              c2_rt1r = c2_rt2r;
            }

            c2_rt1i = 0.0;
            c2_rt2i = 0.0;
          }
        }

        c2_cc_a = c2_i;
        c2_dc_a = c2_cc_a - 2;
        c2_m = c2_dc_a;
        exitg3 = false;
        while ((exitg3 == false) && (c2_m >= c2_L)) {
          c2_ec_a = c2_m;
          c2_fc_a = c2_ec_a + 1;
          c2_ab_c = c2_fc_a;
          c2_h21s = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_ab_c), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1];
          c2_s = (c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
                     (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0)
                    + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                      _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) -
                         1] - c2_rt2r) + c2_abs(chartInstance, c2_rt2i)) +
            c2_abs(chartInstance, c2_h21s);
          c2_gc_a = c2_m;
          c2_hc_a = c2_gc_a + 1;
          c2_bb_c = c2_hc_a;
          c2_h_A = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_bb_c), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1];
          c2_g_B = c2_s;
          c2_v_x = c2_h_A;
          c2_x_y = c2_g_B;
          c2_w_x = c2_v_x;
          c2_y_y = c2_x_y;
          c2_x_x = c2_w_x;
          c2_ab_y = c2_y_y;
          c2_h21s = c2_x_x / c2_ab_y;
          c2_ic_a = c2_m;
          c2_jc_a = c2_ic_a + 1;
          c2_cb_c = c2_jc_a;
          c2_i_A = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1] -
            c2_rt2r;
          c2_h_B = c2_s;
          c2_y_x = c2_i_A;
          c2_bb_y = c2_h_B;
          c2_ab_x = c2_y_x;
          c2_cb_y = c2_bb_y;
          c2_bb_x = c2_ab_x;
          c2_db_y = c2_cb_y;
          c2_eb_y = c2_bb_x / c2_db_y;
          c2_j_A = c2_rt2i;
          c2_i_B = c2_s;
          c2_cb_x = c2_j_A;
          c2_fb_y = c2_i_B;
          c2_db_x = c2_cb_x;
          c2_gb_y = c2_fb_y;
          c2_eb_x = c2_db_x;
          c2_hb_y = c2_gb_y;
          c2_ib_y = c2_eb_x / c2_hb_y;
          c2_v[0] = (c2_h21s * c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
                      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_cb_c), 1, 3, 2, 0) - 1)) - 1] +
                     (c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
                            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1] -
                      c2_rt1r) * c2_eb_y) - c2_rt1i * c2_ib_y;
          c2_kc_a = c2_m;
          c2_lc_a = c2_kc_a + 1;
          c2_db_c = c2_lc_a;
          c2_mc_a = c2_m;
          c2_nc_a = c2_mc_a + 1;
          c2_eb_c = c2_nc_a;
          c2_v[1] = c2_h21s * (((c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_m), 1, 3, 2, 0) - 1)) - 1] + c2_h
            [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_db_c), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
                                    (int32_T)_SFD_INTEGER_CHECK("", (real_T)
            c2_eb_c), 1, 3, 2, 0) - 1)) - 1]) - c2_rt1r) - c2_rt2r);
          c2_oc_a = c2_m;
          c2_pc_a = c2_oc_a + 2;
          c2_fb_c = c2_pc_a;
          c2_qc_a = c2_m;
          c2_rc_a = c2_qc_a + 1;
          c2_gb_c = c2_rc_a;
          c2_v[2] = c2_h21s * c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_fb_c), 1, 3, 1, 0) + 3 *
            (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_gb_c), 1, 3, 2, 0) - 1)) - 1];
          c2_s = (c2_abs(chartInstance, c2_v[0]) + c2_abs(chartInstance, c2_v[1]))
            + c2_abs(chartInstance, c2_v[2]);
          c2_k_A = c2_v[0];
          c2_j_B = c2_s;
          c2_fb_x = c2_k_A;
          c2_jb_y = c2_j_B;
          c2_gb_x = c2_fb_x;
          c2_kb_y = c2_jb_y;
          c2_hb_x = c2_gb_x;
          c2_lb_y = c2_kb_y;
          c2_mb_y = c2_hb_x / c2_lb_y;
          c2_v[0] = c2_mb_y;
          c2_l_A = c2_v[1];
          c2_k_B = c2_s;
          c2_ib_x = c2_l_A;
          c2_nb_y = c2_k_B;
          c2_jb_x = c2_ib_x;
          c2_ob_y = c2_nb_y;
          c2_kb_x = c2_jb_x;
          c2_pb_y = c2_ob_y;
          c2_qb_y = c2_kb_x / c2_pb_y;
          c2_v[1] = c2_qb_y;
          c2_m_A = c2_v[2];
          c2_l_B = c2_s;
          c2_lb_x = c2_m_A;
          c2_rb_y = c2_l_B;
          c2_mb_x = c2_lb_x;
          c2_sb_y = c2_rb_y;
          c2_nb_x = c2_mb_x;
          c2_tb_y = c2_sb_y;
          c2_ub_y = c2_nb_x / c2_tb_y;
          c2_v[2] = c2_ub_y;
          if (c2_m == c2_L) {
            exitg3 = true;
          } else {
            c2_sc_a = c2_m;
            c2_tc_a = c2_sc_a - 1;
            c2_hb_c = c2_tc_a;
            c2_uc_a = c2_m;
            c2_vc_a = c2_uc_a - 1;
            c2_ib_c = c2_vc_a;
            c2_wc_a = c2_m;
            c2_xc_a = c2_wc_a - 1;
            c2_jb_c = c2_xc_a;
            c2_yc_a = c2_m;
            c2_ad_a = c2_yc_a + 1;
            c2_kb_c = c2_ad_a;
            c2_bd_a = c2_m;
            c2_cd_a = c2_bd_a + 1;
            c2_lb_c = c2_cd_a;
            if (c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
                   (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 1, 0) +
                  3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                    _SFD_INTEGER_CHECK("", (real_T)c2_hb_c), 1, 3, 2, 0) - 1)) -
                       1]) * (c2_abs(chartInstance, c2_v[1]) + c2_abs
                              (chartInstance, c2_v[2])) <=
                2.2204460492503131E-16 * c2_abs(chartInstance, c2_v[0]) *
                ((c2_abs(chartInstance, c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("",
                     (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_ib_c), 1, 3, 1,
                     0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                      _SFD_INTEGER_CHECK("", (real_T)c2_jb_c), 1, 3, 2, 0) - 1))
                         - 1]) + c2_abs(chartInstance, c2_h
                   [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                     ("", (real_T)c2_m), 1, 3, 1, 0) + 3 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                      _SFD_INTEGER_CHECK("", (real_T)c2_m), 1, 3, 2, 0) - 1)) -
                   1])) + c2_abs(chartInstance, c2_h
                                 [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                    _SFD_INTEGER_CHECK("", (real_T)c2_kb_c), 1, 3, 1, 0) + 3 *
                                   (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                     _SFD_INTEGER_CHECK("", (real_T)c2_lb_c), 1, 3, 2, 0) - 1))
                                 - 1]))) {
              exitg3 = true;
            } else {
              c2_dd_a = c2_m;
              c2_ed_a = c2_dd_a - 1;
              c2_m = c2_ed_a;
            }
          }
        }

        c2_b_m = c2_m;
        c2_fd_a = c2_i;
        c2_gd_a = c2_fd_a - 1;
        c2_i103 = c2_gd_a;
        c2_hd_a = c2_b_m;
        c2_b = c2_i103;
        c2_id_a = c2_hd_a;
        c2_b_b = c2_b;
        if (c2_id_a > c2_b_b) {
          c2_overflow = false;
        } else {
          c2_eml_switch_helper(chartInstance);
          c2_overflow = (c2_b_b > 2147483646);
        }

        if (c2_overflow) {
          c2_check_forloop_overflow_error(chartInstance, c2_overflow);
        }

        for (c2_b_k = c2_b_m; c2_b_k <= c2_i103; c2_b_k++) {
          c2_k = c2_b_k;
          c2_jd_a = c2_i;
          c2_c_b = c2_k;
          c2_kd_a = c2_jd_a;
          c2_d_b = c2_c_b;
          c2_mb_c = c2_kd_a - c2_d_b;
          c2_ld_a = c2_mb_c;
          c2_md_a = c2_ld_a + 1;
          c2_nb_c = c2_md_a;
          c2_b_varargin_2 = c2_nb_c;
          c2_b_varargin_3 = c2_b_varargin_2;
          c2_vb_y = c2_b_varargin_3;
          c2_wb_y = c2_vb_y;
          c2_eml_scalar_eg(chartInstance);
          c2_b_yk = c2_wb_y;
          c2_xb_y = c2_b_yk;
          c2_eml_scalar_eg(chartInstance);
          c2_nr = muIntScalarMin_sint32(3, c2_xb_y);
          if (c2_k > c2_m) {
            c2_nd_a = c2_k;
            c2_od_a = c2_nd_a - 1;
            c2_ob_c = c2_od_a;
            c2_pd_a = c2_k;
            c2_qd_a = c2_pd_a - 2;
            c2_pb_c = c2_qd_a;
            c2_e_b = c2_pb_c;
            c2_f_b = c2_e_b;
            c2_qb_c = 3 * c2_f_b;
            c2_rd_a = c2_ob_c;
            c2_g_b = c2_qb_c;
            c2_sd_a = c2_rd_a;
            c2_h_b = c2_g_b;
            c2_hoffset = c2_sd_a + c2_h_b;
            c2_b_nr = c2_nr;
            c2_i_b = c2_b_nr;
            c2_j_b = c2_i_b;
            if (1 > c2_j_b) {
              c2_b_overflow = false;
            } else {
              c2_eml_switch_helper(chartInstance);
              c2_b_overflow = (c2_j_b > 2147483646);
            }

            if (c2_b_overflow) {
              c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
            }

            for (c2_j = 1; c2_j <= c2_b_nr; c2_j++) {
              c2_b_j = c2_j;
              c2_td_a = c2_b_j;
              c2_k_b = c2_hoffset;
              c2_ud_a = c2_td_a;
              c2_l_b = c2_k_b;
              c2_rb_c = c2_ud_a + c2_l_b;
              c2_v[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                "", (real_T)c2_b_j), 1, 3, 1, 0) - 1] =
                c2_h[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                ("", (real_T)c2_rb_c), 1, 9, 1, 0) - 1];
            }
          }

          c2_alpha = c2_v[0];
          c2_b_alpha = c2_alpha;
          c2_t1 = c2_b_eml_matlab_zlarfg(chartInstance, c2_nr, &c2_b_alpha, c2_v);
          c2_alpha = c2_b_alpha;
          c2_b_t1 = c2_t1;
          c2_v[0] = c2_alpha;
          if (c2_k > c2_m) {
            c2_vd_a = c2_k;
            c2_wd_a = c2_vd_a - 1;
            c2_sb_c = c2_wd_a;
            c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_k), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_sb_c), 1, 3, 2, 0) - 1)) - 1] = c2_v[0];
            c2_xd_a = c2_k;
            c2_yd_a = c2_xd_a + 1;
            c2_tb_c = c2_yd_a;
            c2_ae_a = c2_k;
            c2_be_a = c2_ae_a - 1;
            c2_ub_c = c2_be_a;
            c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_tb_c), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_ub_c), 1, 3, 2, 0) - 1)) - 1] = 0.0;
            c2_ce_a = c2_i;
            c2_de_a = c2_ce_a - 1;
            c2_vb_c = c2_de_a;
            if (c2_k < c2_vb_c) {
              c2_ee_a = c2_k;
              c2_fe_a = c2_ee_a + 2;
              c2_wb_c = c2_fe_a;
              c2_ge_a = c2_k;
              c2_he_a = c2_ge_a - 1;
              c2_xb_c = c2_he_a;
              c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c2_wb_c), 1, 3, 1, 0) + 3 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_xb_c), 1, 3, 2, 0) - 1)) - 1] = 0.0;
            }
          } else {
            if (c2_m > c2_L) {
              c2_ie_a = c2_k;
              c2_je_a = c2_ie_a - 1;
              c2_yb_c = c2_je_a;
              c2_ke_a = c2_k;
              c2_le_a = c2_ke_a - 1;
              c2_ac_c = c2_le_a;
              c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c2_k), 1, 3, 1, 0) + 3 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_yb_c), 1, 3, 2, 0) - 1)) - 1] = c2_h
                [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_k), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_ac_c), 1, 3, 2, 0) - 1)) - 1] * (1.0 -
                c2_b_t1);
            }
          }

          c2_v2 = c2_v[1];
          c2_t2 = c2_b_t1 * c2_v2;
          if (c2_nr == 3) {
            c2_v3 = c2_v[2];
            c2_t3 = c2_b_t1 * c2_v3;
            c2_c_k = c2_k;
            c2_me_a = c2_c_k;
            c2_ne_a = c2_me_a;
            if (c2_ne_a > 3) {
              c2_c_overflow = false;
            } else {
              c2_eml_switch_helper(chartInstance);
              c2_c_overflow = false;
            }

            if (c2_c_overflow) {
              c2_check_forloop_overflow_error(chartInstance, c2_c_overflow);
            }

            for (c2_c_j = c2_c_k; c2_c_j < 4; c2_c_j++) {
              c2_b_j = c2_c_j;
              c2_oe_a = c2_k;
              c2_pe_a = c2_oe_a + 1;
              c2_bc_c = c2_pe_a;
              c2_qe_a = c2_k;
              c2_re_a = c2_qe_a + 2;
              c2_cc_c = c2_re_a;
              c2_sum1 = (c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 1, 0) + 3 *
                               (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1] +
                         c2_v2 * c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_bc_c), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1])
                + c2_v3 * c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_cc_c), 1, 3, 1, 0) + 3 *
                                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1];
              c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c2_k), 1, 3, 1, 0) + 3 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1] = c2_h
                [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_k), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1] - c2_sum1 *
                c2_b_t1;
              c2_se_a = c2_k;
              c2_te_a = c2_se_a + 1;
              c2_dc_c = c2_te_a;
              c2_ue_a = c2_k;
              c2_ve_a = c2_ue_a + 1;
              c2_ec_c = c2_ve_a;
              c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c2_dc_c), 1, 3, 1, 0) + 3 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1] = c2_h
                [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_ec_c), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1] - c2_sum1 *
                c2_t2;
              c2_we_a = c2_k;
              c2_xe_a = c2_we_a + 2;
              c2_fc_c = c2_xe_a;
              c2_ye_a = c2_k;
              c2_af_a = c2_ye_a + 2;
              c2_gc_c = c2_af_a;
              c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c2_fc_c), 1, 3, 1, 0) + 3 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1] = c2_h
                [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_gc_c), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1] - c2_sum1 *
                c2_t3;
            }

            c2_bf_a = c2_k;
            c2_cf_a = c2_bf_a + 3;
            c2_hc_c = c2_cf_a;
            c2_varargin_1 = c2_hc_c;
            c2_c_varargin_2 = c2_i;
            c2_d_varargin_2 = c2_varargin_1;
            c2_c_varargin_3 = c2_c_varargin_2;
            c2_ob_x = c2_d_varargin_2;
            c2_yb_y = c2_c_varargin_3;
            c2_pb_x = c2_ob_x;
            c2_ac_y = c2_yb_y;
            c2_eml_scalar_eg(chartInstance);
            c2_xk = c2_pb_x;
            c2_c_yk = c2_ac_y;
            c2_qb_x = c2_xk;
            c2_bc_y = c2_c_yk;
            c2_eml_scalar_eg(chartInstance);
            c2_i104 = muIntScalarMin_sint32(c2_qb_x, c2_bc_y);
            c2_m_b = c2_i104;
            c2_n_b = c2_m_b;
            if (1 > c2_n_b) {
              c2_d_overflow = false;
            } else {
              c2_eml_switch_helper(chartInstance);
              c2_d_overflow = (c2_n_b > 2147483646);
            }

            if (c2_d_overflow) {
              c2_check_forloop_overflow_error(chartInstance, c2_d_overflow);
            }

            for (c2_d_j = 1; c2_d_j <= c2_i104; c2_d_j++) {
              c2_b_j = c2_d_j;
              c2_df_a = c2_k;
              c2_ef_a = c2_df_a + 1;
              c2_ic_c = c2_ef_a;
              c2_ff_a = c2_k;
              c2_gf_a = c2_ff_a + 2;
              c2_jc_c = c2_gf_a;
              c2_sum1 = (c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                               (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1] +
                         c2_v2 * c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_ic_c), 1, 3, 2, 0) - 1)) - 1])
                + c2_v3 * c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_jc_c), 1, 3, 2, 0) - 1)) - 1];
              c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1] = c2_h
                [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1] - c2_sum1 *
                c2_b_t1;
              c2_hf_a = c2_k;
              c2_if_a = c2_hf_a + 1;
              c2_kc_c = c2_if_a;
              c2_jf_a = c2_k;
              c2_kf_a = c2_jf_a + 1;
              c2_lc_c = c2_kf_a;
              c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_kc_c), 1, 3, 2, 0) - 1)) - 1] = c2_h
                [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_lc_c), 1, 3, 2, 0) - 1)) - 1] - c2_sum1 *
                c2_t2;
              c2_lf_a = c2_k;
              c2_mf_a = c2_lf_a + 2;
              c2_mc_c = c2_mf_a;
              c2_nf_a = c2_k;
              c2_of_a = c2_nf_a + 2;
              c2_nc_c = c2_of_a;
              c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_mc_c), 1, 3, 2, 0) - 1)) - 1] = c2_h
                [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_nc_c), 1, 3, 2, 0) - 1)) - 1] - c2_sum1 *
                c2_t3;
            }

            for (c2_e_j = 1; c2_e_j < 4; c2_e_j++) {
              c2_b_j = c2_e_j;
              c2_pf_a = c2_k;
              c2_qf_a = c2_pf_a + 1;
              c2_oc_c = c2_qf_a;
              c2_rf_a = c2_k;
              c2_sf_a = c2_rf_a + 2;
              c2_pc_c = c2_sf_a;
              c2_sum1 = (c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                               (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1] +
                         c2_v2 * c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                          (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_oc_c), 1, 3, 2, 0) - 1)) - 1])
                + c2_v3 * c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                _SFD_INTEGER_CHECK("", (real_T)c2_pc_c), 1, 3, 2, 0) - 1)) - 1];
              c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1] = c2_z
                [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1] - c2_sum1 *
                c2_b_t1;
              c2_tf_a = c2_k;
              c2_uf_a = c2_tf_a + 1;
              c2_qc_c = c2_uf_a;
              c2_vf_a = c2_k;
              c2_wf_a = c2_vf_a + 1;
              c2_rc_c = c2_wf_a;
              c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_qc_c), 1, 3, 2, 0) - 1)) - 1] = c2_z
                [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_rc_c), 1, 3, 2, 0) - 1)) - 1] - c2_sum1 *
                c2_t2;
              c2_xf_a = c2_k;
              c2_yf_a = c2_xf_a + 2;
              c2_sc_c = c2_yf_a;
              c2_ag_a = c2_k;
              c2_bg_a = c2_ag_a + 2;
              c2_tc_c = c2_bg_a;
              c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                      "", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                    (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", (real_T)c2_sc_c), 1, 3, 2, 0) - 1)) - 1] = c2_z
                [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                    (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
                     "", (real_T)c2_tc_c), 1, 3, 2, 0) - 1)) - 1] - c2_sum1 *
                c2_t3;
            }
          } else {
            if (c2_nr == 2) {
              c2_d_k = c2_k;
              c2_cg_a = c2_d_k;
              c2_dg_a = c2_cg_a;
              if (c2_dg_a > 3) {
                c2_e_overflow = false;
              } else {
                c2_eml_switch_helper(chartInstance);
                c2_e_overflow = false;
              }

              if (c2_e_overflow) {
                c2_check_forloop_overflow_error(chartInstance, c2_e_overflow);
              }

              for (c2_f_j = c2_d_k; c2_f_j < 4; c2_f_j++) {
                c2_b_j = c2_f_j;
                c2_eg_a = c2_k;
                c2_fg_a = c2_eg_a + 1;
                c2_uc_c = c2_fg_a;
                c2_sum1 = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 1, 0) + 3 *
                                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1]
                  + c2_v2 * c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_uc_c), 1, 3, 1, 0) + 3 *
                                  (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1];
                c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                       _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 1, 0) + 3 *
                      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
                  - 1] = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 1, 0) + 3 *
                               (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1]
                  - c2_sum1 * c2_b_t1;
                c2_gg_a = c2_k;
                c2_hg_a = c2_gg_a + 1;
                c2_vc_c = c2_hg_a;
                c2_ig_a = c2_k;
                c2_jg_a = c2_ig_a + 1;
                c2_wc_c = c2_jg_a;
                c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                       _SFD_INTEGER_CHECK("", (real_T)c2_vc_c), 1, 3, 1, 0) + 3 *
                      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                        _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1))
                  - 1] = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_wc_c), 1, 3, 1, 0) + 3 *
                               (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 2, 0) - 1)) - 1]
                  - c2_sum1 * c2_t2;
              }

              c2_b_i = c2_i;
              c2_o_b = c2_b_i;
              c2_p_b = c2_o_b;
              if (1 > c2_p_b) {
                c2_f_overflow = false;
              } else {
                c2_eml_switch_helper(chartInstance);
                c2_f_overflow = (c2_p_b > 2147483646);
              }

              if (c2_f_overflow) {
                c2_check_forloop_overflow_error(chartInstance, c2_f_overflow);
              }

              for (c2_g_j = 1; c2_g_j <= c2_b_i; c2_g_j++) {
                c2_b_j = c2_g_j;
                c2_kg_a = c2_k;
                c2_lg_a = c2_kg_a + 1;
                c2_xc_c = c2_lg_a;
                c2_sum1 = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1] +
                  c2_v2 * c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_xc_c), 1, 3, 2, 0) - 1)) - 1];
                c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                       _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                        _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 2, 0) - 1))
                  - 1] = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                               (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1] -
                  c2_sum1 * c2_b_t1;
                c2_mg_a = c2_k;
                c2_ng_a = c2_mg_a + 1;
                c2_yc_c = c2_ng_a;
                c2_og_a = c2_k;
                c2_pg_a = c2_og_a + 1;
                c2_ad_c = c2_pg_a;
                c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                       _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                        _SFD_INTEGER_CHECK("", (real_T)c2_yc_c), 1, 3, 2, 0) - 1))
                  - 1] = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                               (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_ad_c), 1, 3, 2, 0) - 1)) - 1]
                  - c2_sum1 * c2_t2;
              }

              for (c2_h_j = 1; c2_h_j < 4; c2_h_j++) {
                c2_b_j = c2_h_j;
                c2_qg_a = c2_k;
                c2_rg_a = c2_qg_a + 1;
                c2_bd_c = c2_rg_a;
                c2_sum1 = c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1] +
                  c2_v2 * c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_bd_c), 1, 3, 2, 0) - 1)) - 1];
                c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                       _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                        _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 2, 0) - 1))
                  - 1] = c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                               (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_k), 1, 3, 2, 0) - 1)) - 1] -
                  c2_sum1 * c2_b_t1;
                c2_sg_a = c2_k;
                c2_tg_a = c2_sg_a + 1;
                c2_cd_c = c2_tg_a;
                c2_ug_a = c2_k;
                c2_vg_a = c2_ug_a + 1;
                c2_dd_c = c2_vg_a;
                c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                       _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                      (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                        _SFD_INTEGER_CHECK("", (real_T)c2_cd_c), 1, 3, 2, 0) - 1))
                  - 1] = c2_z[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 3, 1, 0) + 3 *
                               (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
                  _SFD_INTEGER_CHECK("", (real_T)c2_dd_c), 1, 3, 2, 0) - 1)) - 1]
                  - c2_sum1 * c2_t2;
              }
            }
          }
        }

        c2_its++;
      }
    }

    if (!c2_goto150) {
      c2_info = c2_i;
      exitg1 = true;
    } else {
      if (c2_L == c2_i) {
      } else {
        c2_wg_a = c2_i;
        c2_xg_a = c2_wg_a - 1;
        c2_ed_c = c2_xg_a;
        if (c2_L == c2_ed_c) {
          c2_yg_a = c2_i;
          c2_ah_a = c2_yg_a - 1;
          c2_im1 = c2_ah_a;
          c2_d8 = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_im1), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_im1), 1, 3, 2, 0) - 1)) - 1];
          c2_d9 = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_im1), 1, 3, 1, 0) + 3 *
                        (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_i), 1, 3, 2, 0) - 1)) - 1];
          c2_d10 = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_i), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_im1), 1, 3, 2, 0) - 1)) - 1];
          c2_d11 = c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_i), 1, 3, 1, 0) + 3 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_i), 1, 3, 2, 0) - 1)) - 1];
          c2_c_eml_dlanv2(chartInstance, &c2_d8, &c2_d9, &c2_d10, &c2_d11,
                          &c2_unusedU0, &c2_unusedU1, &c2_unusedU2, &c2_unusedU3,
                          &c2_cs, &c2_sn);
          c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_im1), 1, 3, 1, 0) + 3 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c2_im1), 1, 3, 2, 0) - 1)) - 1] = c2_d8;
          c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_im1), 1, 3, 1, 0) + 3 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c2_i), 1, 3, 2, 0) - 1)) - 1] = c2_d9;
          c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                  "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_im1), 1, 3, 2,
                  0) - 1)) - 1] = c2_d10;
          c2_h[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                  "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_i), 1, 3, 2, 0)
                 - 1)) - 1] = c2_d11;
          c2_b_cs = c2_cs;
          c2_b_sn = c2_sn;
          if (3 > c2_i) {
            c2_q_b = c2_i;
            c2_r_b = c2_q_b;
            c2_fd_c = 3 - c2_r_b;
            c2_bh_a = c2_i;
            c2_ch_a = c2_bh_a;
            c2_gd_c = c2_ch_a * 3;
            c2_dh_a = c2_im1;
            c2_s_b = c2_gd_c;
            c2_eh_a = c2_dh_a;
            c2_t_b = c2_s_b;
            c2_hd_c = c2_eh_a + c2_t_b;
            c2_fh_a = c2_i;
            c2_gh_a = c2_fh_a;
            c2_id_c = c2_gh_a * 3;
            c2_hh_a = c2_i;
            c2_u_b = c2_id_c;
            c2_ih_a = c2_hh_a;
            c2_v_b = c2_u_b;
            c2_jd_c = c2_ih_a + c2_v_b;
            c2_d_eml_xrot(chartInstance, c2_fd_c, c2_h, c2_hd_c, c2_jd_c,
                          c2_b_cs, c2_b_sn);
          }

          c2_jh_a = c2_im1;
          c2_kh_a = c2_jh_a - 1;
          c2_kd_c = c2_kh_a;
          c2_lh_a = c2_i;
          c2_mh_a = c2_lh_a - 2;
          c2_ld_c = c2_mh_a;
          c2_nh_a = c2_ld_c;
          c2_oh_a = c2_nh_a;
          c2_md_c = c2_oh_a * 3;
          c2_w_b = c2_md_c;
          c2_x_b = c2_w_b + 1;
          c2_nd_c = c2_x_b;
          c2_ph_a = c2_im1;
          c2_qh_a = c2_ph_a;
          c2_od_c = c2_qh_a * 3;
          c2_y_b = c2_od_c;
          c2_ab_b = c2_y_b + 1;
          c2_pd_c = c2_ab_b;
          c2_e_eml_xrot(chartInstance, c2_kd_c, c2_h, c2_nd_c, c2_pd_c, c2_b_cs,
                        c2_b_sn);
          c2_rh_a = c2_i;
          c2_sh_a = c2_rh_a - 2;
          c2_qd_c = c2_sh_a;
          c2_th_a = c2_qd_c;
          c2_uh_a = c2_th_a;
          c2_rd_c = c2_uh_a * 3;
          c2_bb_b = c2_rd_c;
          c2_cb_b = c2_bb_b + 1;
          c2_sd_c = c2_cb_b;
          c2_vh_a = c2_im1;
          c2_wh_a = c2_vh_a;
          c2_td_c = c2_wh_a * 3;
          c2_db_b = c2_td_c;
          c2_eb_b = c2_db_b + 1;
          c2_ud_c = c2_eb_b;
          c2_f_eml_xrot(chartInstance, c2_z, c2_sd_c, c2_ud_c, c2_b_cs, c2_b_sn);
        }
      }

      c2_xh_a = c2_L;
      c2_yh_a = c2_xh_a - 1;
      c2_i = c2_yh_a;
    }
  }

  return c2_info;
}

static void c2_c_sqrt(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                      real_T *c2_x)
{
  if (*c2_x < 0.0) {
    c2_eml_error(chartInstance);
  }

  *c2_x = muDoubleScalarSqrt(*c2_x);
}

static real_T c2_b_eml_matlab_zlarfg(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T *c2_alpha1, real_T c2_x[3])
{
  real_T c2_tau;
  int32_T c2_nm1;
  int32_T c2_i105;
  real_T c2_b_x[3];
  real_T c2_xnorm;
  real_T c2_x1;
  real_T c2_x2;
  real_T c2_a;
  real_T c2_b;
  real_T c2_beta1;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_y;
  int32_T c2_knt;
  int32_T c2_b_a;
  int32_T c2_c_a;
  real_T c2_d12;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_b_y;
  int32_T c2_i106;
  real_T c2_g_x[3];
  real_T c2_b_x1;
  real_T c2_b_x2;
  real_T c2_d_a;
  real_T c2_b_b;
  real_T c2_h_x;
  real_T c2_c_y;
  real_T c2_i_x;
  real_T c2_d_y;
  real_T c2_e_y;
  real_T c2_f_y;
  int32_T c2_b_knt;
  int32_T c2_c_b;
  int32_T c2_d_b;
  boolean_T c2_overflow;
  int32_T c2_k;
  real_T c2_j_x;
  real_T c2_g_y;
  real_T c2_k_x;
  real_T c2_h_y;
  real_T c2_i_y;
  real_T c2_j_y;
  c2_tau = 0.0;
  if (c2_n <= 0) {
  } else {
    c2_nm1 = c2_n - 1;
    for (c2_i105 = 0; c2_i105 < 3; c2_i105++) {
      c2_b_x[c2_i105] = c2_x[c2_i105];
    }

    c2_xnorm = c2_b_eml_xnrm2(chartInstance, c2_nm1, c2_b_x);
    if (c2_xnorm != 0.0) {
      c2_x1 = *c2_alpha1;
      c2_x2 = c2_xnorm;
      c2_a = c2_x1;
      c2_b = c2_x2;
      c2_beta1 = muDoubleScalarHypot(c2_a, c2_b);
      if (*c2_alpha1 >= 0.0) {
        c2_beta1 = -c2_beta1;
      }

      c2_realmin(chartInstance);
      c2_eml_eps(chartInstance);
      c2_c_x = c2_beta1;
      c2_d_x = c2_c_x;
      c2_y = muDoubleScalarAbs(c2_d_x);
      if (c2_y < 1.0020841800044864E-292) {
        c2_knt = 0;
        do {
          c2_b_a = c2_knt;
          c2_c_a = c2_b_a + 1;
          c2_knt = c2_c_a;
          c2_d12 = 9.9792015476736E+291;
          c2_d_eml_xscal(chartInstance, c2_nm1, c2_d12, c2_x);
          c2_beta1 *= 9.9792015476736E+291;
          *c2_alpha1 *= 9.9792015476736E+291;
          c2_e_x = c2_beta1;
          c2_f_x = c2_e_x;
          c2_b_y = muDoubleScalarAbs(c2_f_x);
        } while (!(c2_b_y >= 1.0020841800044864E-292));

        for (c2_i106 = 0; c2_i106 < 3; c2_i106++) {
          c2_g_x[c2_i106] = c2_x[c2_i106];
        }

        c2_xnorm = c2_b_eml_xnrm2(chartInstance, c2_nm1, c2_g_x);
        c2_b_x1 = *c2_alpha1;
        c2_b_x2 = c2_xnorm;
        c2_d_a = c2_b_x1;
        c2_b_b = c2_b_x2;
        c2_beta1 = muDoubleScalarHypot(c2_d_a, c2_b_b);
        if (*c2_alpha1 >= 0.0) {
          c2_beta1 = -c2_beta1;
        }

        c2_h_x = c2_beta1 - *c2_alpha1;
        c2_c_y = c2_beta1;
        c2_i_x = c2_h_x;
        c2_d_y = c2_c_y;
        c2_tau = c2_i_x / c2_d_y;
        c2_e_y = *c2_alpha1 - c2_beta1;
        c2_f_y = c2_e_y;
        *c2_alpha1 = 1.0 / c2_f_y;
        c2_d_eml_xscal(chartInstance, c2_nm1, *c2_alpha1, c2_x);
        c2_b_knt = c2_knt;
        c2_c_b = c2_b_knt;
        c2_d_b = c2_c_b;
        if (1 > c2_d_b) {
          c2_overflow = false;
        } else {
          c2_eml_switch_helper(chartInstance);
          c2_overflow = (c2_d_b > 2147483646);
        }

        if (c2_overflow) {
          c2_check_forloop_overflow_error(chartInstance, c2_overflow);
        }

        for (c2_k = 1; c2_k <= c2_b_knt; c2_k++) {
          c2_beta1 *= 1.0020841800044864E-292;
        }

        *c2_alpha1 = c2_beta1;
      } else {
        c2_j_x = c2_beta1 - *c2_alpha1;
        c2_g_y = c2_beta1;
        c2_k_x = c2_j_x;
        c2_h_y = c2_g_y;
        c2_tau = c2_k_x / c2_h_y;
        c2_i_y = *c2_alpha1 - c2_beta1;
        c2_j_y = c2_i_y;
        *c2_alpha1 = 1.0 / c2_j_y;
        c2_d_eml_xscal(chartInstance, c2_nm1, *c2_alpha1, c2_x);
        *c2_alpha1 = c2_beta1;
      }
    }
  }

  return c2_tau;
}

static void c2_d_eml_xscal(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_a, real_T c2_x[3])
{
  int32_T c2_b_n;
  real_T c2_b_a;
  int32_T c2_c_n;
  real_T c2_c_a;
  int32_T c2_d_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_c;
  int32_T c2_b_b;
  int32_T c2_i107;
  int32_T c2_c_b;
  int32_T c2_d_b;
  boolean_T c2_overflow;
  int32_T c2_k;
  int32_T c2_b_k;
  c2_b_n = c2_n;
  c2_b_a = c2_a;
  c2_b_threshold(chartInstance);
  c2_c_n = c2_b_n;
  c2_c_a = c2_b_a;
  c2_d_a = c2_c_n;
  c2_c = c2_d_a;
  c2_b = c2_c - 1;
  c2_b_c = c2_b;
  c2_b_b = c2_b_c + 2;
  c2_i107 = c2_b_b;
  c2_c_b = c2_i107;
  c2_d_b = c2_c_b;
  if (2 > c2_d_b) {
    c2_overflow = false;
  } else {
    c2_eml_switch_helper(chartInstance);
    c2_overflow = (c2_d_b > 2147483646);
  }

  if (c2_overflow) {
    c2_check_forloop_overflow_error(chartInstance, c2_overflow);
  }

  for (c2_k = 2; c2_k <= c2_i107; c2_k++) {
    c2_b_k = c2_k;
    c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_b_k), 1, 3, 1, 0) - 1] = c2_c_a * c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_k), 1, 3, 1, 0) - 1];
  }
}

static void c2_c_eml_dlanv2(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, real_T *c2_a, real_T *c2_b, real_T *c2_c, real_T *c2_d, real_T
  *c2_rt1r, real_T *c2_rt1i, real_T *c2_rt2r, real_T *c2_rt2i, real_T *c2_cs,
  real_T *c2_sn)
{
  real_T c2_temp;
  real_T c2_p;
  real_T c2_varargin_1;
  real_T c2_varargin_2;
  real_T c2_b_varargin_2;
  real_T c2_varargin_3;
  real_T c2_x;
  real_T c2_y;
  real_T c2_b_x;
  real_T c2_b_y;
  real_T c2_xk;
  real_T c2_yk;
  real_T c2_c_x;
  real_T c2_c_y;
  real_T c2_bcmax;
  real_T c2_b_varargin_1;
  real_T c2_c_varargin_2;
  real_T c2_d_varargin_2;
  real_T c2_b_varargin_3;
  real_T c2_d_x;
  real_T c2_d_y;
  real_T c2_e_x;
  real_T c2_e_y;
  real_T c2_b_xk;
  real_T c2_b_yk;
  real_T c2_f_x;
  real_T c2_f_y;
  real_T c2_minval;
  real_T c2_b_b;
  real_T c2_g_y;
  real_T c2_c_b;
  real_T c2_h_y;
  real_T c2_bcmis;
  real_T c2_c_varargin_1;
  real_T c2_e_varargin_2;
  real_T c2_f_varargin_2;
  real_T c2_c_varargin_3;
  real_T c2_g_x;
  real_T c2_i_y;
  real_T c2_h_x;
  real_T c2_j_y;
  real_T c2_c_xk;
  real_T c2_c_yk;
  real_T c2_i_x;
  real_T c2_k_y;
  real_T c2_scale;
  real_T c2_A;
  real_T c2_B;
  real_T c2_j_x;
  real_T c2_l_y;
  real_T c2_k_x;
  real_T c2_m_y;
  real_T c2_l_x;
  real_T c2_n_y;
  real_T c2_o_y;
  real_T c2_b_A;
  real_T c2_b_B;
  real_T c2_m_x;
  real_T c2_p_y;
  real_T c2_n_x;
  real_T c2_q_y;
  real_T c2_o_x;
  real_T c2_r_y;
  real_T c2_s_y;
  real_T c2_z;
  real_T c2_p_x;
  real_T c2_q_x;
  real_T c2_r_x;
  real_T c2_s_x;
  real_T c2_b_a;
  real_T c2_d_b;
  real_T c2_t_y;
  real_T c2_c_A;
  real_T c2_c_B;
  real_T c2_t_x;
  real_T c2_u_y;
  real_T c2_u_x;
  real_T c2_v_y;
  real_T c2_v_x;
  real_T c2_w_y;
  real_T c2_x_y;
  real_T c2_x1;
  real_T c2_x2;
  real_T c2_c_a;
  real_T c2_e_b;
  real_T c2_tau;
  real_T c2_d_A;
  real_T c2_d_B;
  real_T c2_w_x;
  real_T c2_y_y;
  real_T c2_x_x;
  real_T c2_ab_y;
  real_T c2_y_x;
  real_T c2_bb_y;
  real_T c2_e_A;
  real_T c2_e_B;
  real_T c2_ab_x;
  real_T c2_cb_y;
  real_T c2_bb_x;
  real_T c2_db_y;
  real_T c2_cb_x;
  real_T c2_eb_y;
  real_T c2_sigma;
  real_T c2_b_x1;
  real_T c2_b_x2;
  real_T c2_d_a;
  real_T c2_f_b;
  real_T c2_db_x;
  real_T c2_eb_x;
  real_T c2_fb_y;
  real_T c2_f_A;
  real_T c2_f_B;
  real_T c2_fb_x;
  real_T c2_gb_y;
  real_T c2_gb_x;
  real_T c2_hb_y;
  real_T c2_hb_x;
  real_T c2_ib_y;
  real_T c2_jb_y;
  real_T c2_ib_x;
  real_T c2_g_A;
  real_T c2_g_B;
  real_T c2_jb_x;
  real_T c2_kb_y;
  real_T c2_kb_x;
  real_T c2_lb_y;
  real_T c2_lb_x;
  real_T c2_mb_y;
  real_T c2_nb_y;
  real_T c2_g_b;
  real_T c2_ob_y;
  real_T c2_aa;
  real_T c2_bb;
  real_T c2_cc;
  real_T c2_dd;
  real_T c2_mb_x;
  real_T c2_nb_x;
  real_T c2_pb_y;
  real_T c2_ob_x;
  real_T c2_sab;
  real_T c2_pb_x;
  real_T c2_qb_x;
  real_T c2_qb_y;
  real_T c2_rb_x;
  real_T c2_sac;
  real_T c2_e_a;
  real_T c2_h_b;
  real_T c2_sb_x;
  real_T c2_tb_x;
  real_T c2_rb_y;
  real_T c2_ub_x;
  real_T c2_vb_x;
  real_T c2_h_B;
  real_T c2_sb_y;
  real_T c2_tb_y;
  real_T c2_ub_y;
  real_T c2_cs1;
  real_T c2_sn1;
  real_T c2_wb_x;
  real_T c2_xb_x;
  real_T c2_vb_y;
  real_T c2_yb_x;
  real_T c2_ac_x;
  real_T c2_bc_x;
  real_T c2_cc_x;
  real_T c2_wb_y;
  real_T c2_dc_x;
  real_T c2_ec_x;
  boolean_T guard1 = false;
  c2_c_eml_scalar_eg(chartInstance);
  if (*c2_c == 0.0) {
    *c2_cs = 1.0;
    *c2_sn = 0.0;
  } else if (*c2_b == 0.0) {
    *c2_cs = 0.0;
    *c2_sn = 1.0;
    c2_temp = *c2_d;
    *c2_d = *c2_a;
    *c2_a = c2_temp;
    *c2_b = -*c2_c;
    *c2_c = 0.0;
  } else {
    guard1 = false;
    if (*c2_a - *c2_d == 0.0) {
      if (*c2_b < 0.0 != *c2_c < 0.0) {
        *c2_cs = 1.0;
        *c2_sn = 0.0;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1 == true) {
      c2_temp = *c2_a - *c2_d;
      c2_p = 0.5 * c2_temp;
      c2_varargin_1 = c2_abs(chartInstance, *c2_b);
      c2_varargin_2 = c2_abs(chartInstance, *c2_c);
      c2_b_varargin_2 = c2_varargin_1;
      c2_varargin_3 = c2_varargin_2;
      c2_x = c2_b_varargin_2;
      c2_y = c2_varargin_3;
      c2_b_x = c2_x;
      c2_b_y = c2_y;
      c2_b_eml_scalar_eg(chartInstance);
      c2_xk = c2_b_x;
      c2_yk = c2_b_y;
      c2_c_x = c2_xk;
      c2_c_y = c2_yk;
      c2_b_eml_scalar_eg(chartInstance);
      c2_bcmax = muDoubleScalarMax(c2_c_x, c2_c_y);
      c2_b_varargin_1 = c2_abs(chartInstance, *c2_b);
      c2_c_varargin_2 = c2_abs(chartInstance, *c2_c);
      c2_d_varargin_2 = c2_b_varargin_1;
      c2_b_varargin_3 = c2_c_varargin_2;
      c2_d_x = c2_d_varargin_2;
      c2_d_y = c2_b_varargin_3;
      c2_e_x = c2_d_x;
      c2_e_y = c2_d_y;
      c2_b_eml_scalar_eg(chartInstance);
      c2_b_xk = c2_e_x;
      c2_b_yk = c2_e_y;
      c2_f_x = c2_b_xk;
      c2_f_y = c2_b_yk;
      c2_b_eml_scalar_eg(chartInstance);
      c2_minval = muDoubleScalarMin(c2_f_x, c2_f_y);
      c2_b_b = *c2_b;
      if (!(c2_b_b < 0.0)) {
        c2_g_y = 1.0;
      } else {
        c2_g_y = -1.0;
      }

      c2_c_b = *c2_c;
      if (!(c2_c_b < 0.0)) {
        c2_h_y = 1.0;
      } else {
        c2_h_y = -1.0;
      }

      c2_bcmis = c2_minval * c2_g_y * c2_h_y;
      c2_c_varargin_1 = c2_abs(chartInstance, c2_p);
      c2_e_varargin_2 = c2_bcmax;
      c2_f_varargin_2 = c2_c_varargin_1;
      c2_c_varargin_3 = c2_e_varargin_2;
      c2_g_x = c2_f_varargin_2;
      c2_i_y = c2_c_varargin_3;
      c2_h_x = c2_g_x;
      c2_j_y = c2_i_y;
      c2_b_eml_scalar_eg(chartInstance);
      c2_c_xk = c2_h_x;
      c2_c_yk = c2_j_y;
      c2_i_x = c2_c_xk;
      c2_k_y = c2_c_yk;
      c2_b_eml_scalar_eg(chartInstance);
      c2_scale = muDoubleScalarMax(c2_i_x, c2_k_y);
      c2_A = c2_p;
      c2_B = c2_scale;
      c2_j_x = c2_A;
      c2_l_y = c2_B;
      c2_k_x = c2_j_x;
      c2_m_y = c2_l_y;
      c2_l_x = c2_k_x;
      c2_n_y = c2_m_y;
      c2_o_y = c2_l_x / c2_n_y;
      c2_b_A = c2_bcmax;
      c2_b_B = c2_scale;
      c2_m_x = c2_b_A;
      c2_p_y = c2_b_B;
      c2_n_x = c2_m_x;
      c2_q_y = c2_p_y;
      c2_o_x = c2_n_x;
      c2_r_y = c2_q_y;
      c2_s_y = c2_o_x / c2_r_y;
      c2_z = c2_o_y * c2_p + c2_s_y * c2_bcmis;
      c2_eml_eps(chartInstance);
      if (c2_z >= 8.8817841970012523E-16) {
        c2_p_x = c2_scale;
        c2_q_x = c2_p_x;
        if (c2_q_x < 0.0) {
          c2_eml_error(chartInstance);
        }

        c2_q_x = muDoubleScalarSqrt(c2_q_x);
        c2_r_x = c2_z;
        c2_s_x = c2_r_x;
        if (c2_s_x < 0.0) {
          c2_eml_error(chartInstance);
        }

        c2_s_x = muDoubleScalarSqrt(c2_s_x);
        c2_b_a = c2_q_x * c2_s_x;
        c2_d_b = c2_p;
        if (c2_d_b < 0.0 == c2_b_a < 0.0) {
          c2_t_y = c2_b_a;
        } else {
          c2_t_y = -c2_b_a;
        }

        c2_z = c2_p + c2_t_y;
        *c2_a = *c2_d + c2_z;
        c2_c_A = c2_bcmax;
        c2_c_B = c2_z;
        c2_t_x = c2_c_A;
        c2_u_y = c2_c_B;
        c2_u_x = c2_t_x;
        c2_v_y = c2_u_y;
        c2_v_x = c2_u_x;
        c2_w_y = c2_v_y;
        c2_x_y = c2_v_x / c2_w_y;
        *c2_d -= c2_x_y * c2_bcmis;
        c2_x1 = *c2_c;
        c2_x2 = c2_z;
        c2_c_a = c2_x1;
        c2_e_b = c2_x2;
        c2_tau = muDoubleScalarHypot(c2_c_a, c2_e_b);
        c2_d_A = c2_z;
        c2_d_B = c2_tau;
        c2_w_x = c2_d_A;
        c2_y_y = c2_d_B;
        c2_x_x = c2_w_x;
        c2_ab_y = c2_y_y;
        c2_y_x = c2_x_x;
        c2_bb_y = c2_ab_y;
        *c2_cs = c2_y_x / c2_bb_y;
        c2_e_A = *c2_c;
        c2_e_B = c2_tau;
        c2_ab_x = c2_e_A;
        c2_cb_y = c2_e_B;
        c2_bb_x = c2_ab_x;
        c2_db_y = c2_cb_y;
        c2_cb_x = c2_bb_x;
        c2_eb_y = c2_db_y;
        *c2_sn = c2_cb_x / c2_eb_y;
        *c2_b -= *c2_c;
        *c2_c = 0.0;
      } else {
        c2_sigma = *c2_b + *c2_c;
        c2_b_x1 = c2_sigma;
        c2_b_x2 = c2_temp;
        c2_d_a = c2_b_x1;
        c2_f_b = c2_b_x2;
        c2_tau = muDoubleScalarHypot(c2_d_a, c2_f_b);
        c2_db_x = c2_sigma;
        c2_eb_x = c2_db_x;
        c2_fb_y = muDoubleScalarAbs(c2_eb_x);
        c2_f_A = c2_fb_y;
        c2_f_B = c2_tau;
        c2_fb_x = c2_f_A;
        c2_gb_y = c2_f_B;
        c2_gb_x = c2_fb_x;
        c2_hb_y = c2_gb_y;
        c2_hb_x = c2_gb_x;
        c2_ib_y = c2_hb_y;
        c2_jb_y = c2_hb_x / c2_ib_y;
        c2_ib_x = 0.5 * (1.0 + c2_jb_y);
        *c2_cs = c2_ib_x;
        if (*c2_cs < 0.0) {
          c2_eml_error(chartInstance);
        }

        *c2_cs = muDoubleScalarSqrt(*c2_cs);
        c2_g_A = c2_p;
        c2_g_B = c2_tau * *c2_cs;
        c2_jb_x = c2_g_A;
        c2_kb_y = c2_g_B;
        c2_kb_x = c2_jb_x;
        c2_lb_y = c2_kb_y;
        c2_lb_x = c2_kb_x;
        c2_mb_y = c2_lb_y;
        c2_nb_y = c2_lb_x / c2_mb_y;
        c2_g_b = c2_sigma;
        if (!(c2_g_b < 0.0)) {
          c2_ob_y = 1.0;
        } else {
          c2_ob_y = -1.0;
        }

        *c2_sn = -c2_nb_y * c2_ob_y;
        c2_aa = *c2_a * *c2_cs + *c2_b * *c2_sn;
        c2_bb = -*c2_a * *c2_sn + *c2_b * *c2_cs;
        c2_cc = *c2_c * *c2_cs + *c2_d * *c2_sn;
        c2_dd = -*c2_c * *c2_sn + *c2_d * *c2_cs;
        *c2_a = c2_aa * *c2_cs + c2_cc * *c2_sn;
        *c2_b = c2_bb * *c2_cs + c2_dd * *c2_sn;
        *c2_c = -c2_aa * *c2_sn + c2_cc * *c2_cs;
        *c2_d = -c2_bb * *c2_sn + c2_dd * *c2_cs;
        c2_temp = 0.5 * (*c2_a + *c2_d);
        *c2_a = c2_temp;
        *c2_d = c2_temp;
        if (*c2_c != 0.0) {
          if (*c2_b != 0.0) {
            if (*c2_b < 0.0 == *c2_c < 0.0) {
              c2_mb_x = *c2_b;
              c2_nb_x = c2_mb_x;
              c2_pb_y = muDoubleScalarAbs(c2_nb_x);
              c2_ob_x = c2_pb_y;
              c2_sab = c2_ob_x;
              if (c2_sab < 0.0) {
                c2_eml_error(chartInstance);
              }

              c2_sab = muDoubleScalarSqrt(c2_sab);
              c2_pb_x = *c2_c;
              c2_qb_x = c2_pb_x;
              c2_qb_y = muDoubleScalarAbs(c2_qb_x);
              c2_rb_x = c2_qb_y;
              c2_sac = c2_rb_x;
              if (c2_sac < 0.0) {
                c2_eml_error(chartInstance);
              }

              c2_sac = muDoubleScalarSqrt(c2_sac);
              c2_e_a = c2_sab * c2_sac;
              c2_h_b = *c2_c;
              if (c2_h_b < 0.0 == c2_e_a < 0.0) {
                c2_p = c2_e_a;
              } else {
                c2_p = -c2_e_a;
              }

              c2_sb_x = *c2_b + *c2_c;
              c2_tb_x = c2_sb_x;
              c2_rb_y = muDoubleScalarAbs(c2_tb_x);
              c2_ub_x = c2_rb_y;
              c2_vb_x = c2_ub_x;
              if (c2_vb_x < 0.0) {
                c2_eml_error(chartInstance);
              }

              c2_vb_x = muDoubleScalarSqrt(c2_vb_x);
              c2_h_B = c2_vb_x;
              c2_sb_y = c2_h_B;
              c2_tb_y = c2_sb_y;
              c2_ub_y = c2_tb_y;
              c2_tau = 1.0 / c2_ub_y;
              *c2_a = c2_temp + c2_p;
              *c2_d = c2_temp - c2_p;
              *c2_b -= *c2_c;
              *c2_c = 0.0;
              c2_cs1 = c2_sab * c2_tau;
              c2_sn1 = c2_sac * c2_tau;
              c2_temp = *c2_cs * c2_cs1 - *c2_sn * c2_sn1;
              *c2_sn = *c2_cs * c2_sn1 + *c2_sn * c2_cs1;
              *c2_cs = c2_temp;
            }
          } else {
            *c2_b = -*c2_c;
            *c2_c = 0.0;
            c2_temp = *c2_cs;
            *c2_cs = -*c2_sn;
            *c2_sn = c2_temp;
          }
        }
      }
    }
  }

  *c2_rt1r = *c2_a;
  *c2_rt2r = *c2_d;
  if (*c2_c == 0.0) {
    *c2_rt1i = 0.0;
    *c2_rt2i = 0.0;
  } else {
    c2_wb_x = *c2_b;
    c2_xb_x = c2_wb_x;
    c2_vb_y = muDoubleScalarAbs(c2_xb_x);
    c2_yb_x = c2_vb_y;
    c2_ac_x = c2_yb_x;
    if (c2_ac_x < 0.0) {
      c2_eml_error(chartInstance);
    }

    c2_ac_x = muDoubleScalarSqrt(c2_ac_x);
    c2_bc_x = *c2_c;
    c2_cc_x = c2_bc_x;
    c2_wb_y = muDoubleScalarAbs(c2_cc_x);
    c2_dc_x = c2_wb_y;
    c2_ec_x = c2_dc_x;
    if (c2_ec_x < 0.0) {
      c2_eml_error(chartInstance);
    }

    c2_ec_x = muDoubleScalarSqrt(c2_ec_x);
    *c2_rt1i = c2_ac_x * c2_ec_x;
    *c2_rt2i = -*c2_rt1i;
  }
}

static void c2_d_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c,
  real_T c2_s)
{
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  real_T c2_b_c;
  real_T c2_b_s;
  int32_T c2_c_n;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  real_T c2_c_c;
  real_T c2_c_s;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_d_n;
  int32_T c2_b;
  int32_T c2_b_b;
  boolean_T c2_overflow;
  int32_T c2_k;
  real_T c2_temp;
  int32_T c2_a;
  int32_T c2_b_a;
  c2_b_n = c2_n;
  c2_b_ix0 = c2_ix0;
  c2_b_iy0 = c2_iy0;
  c2_b_c = c2_c;
  c2_b_s = c2_s;
  c2_e_threshold(chartInstance);
  c2_c_n = c2_b_n;
  c2_c_ix0 = c2_b_ix0;
  c2_c_iy0 = c2_b_iy0;
  c2_c_c = c2_b_c;
  c2_c_s = c2_b_s;
  if (c2_c_n < 1) {
  } else {
    c2_ix = c2_c_ix0;
    c2_iy = c2_c_iy0;
    c2_d_n = c2_c_n;
    c2_b = c2_d_n;
    c2_b_b = c2_b;
    if (1 > c2_b_b) {
      c2_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_overflow = (c2_b_b > 2147483646);
    }

    if (c2_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_overflow);
    }

    for (c2_k = 1; c2_k <= c2_d_n; c2_k++) {
      c2_temp = c2_c_c * c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 9, 1, 0) - 1] + c2_c_s *
        c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_iy), 1, 9, 1, 0) - 1];
      c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_iy), 1, 9, 1, 0) - 1] = c2_c_c *
        c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_iy), 1, 9, 1, 0) - 1] - c2_c_s *
        c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_ix), 1, 9, 1, 0) - 1];
      c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_ix), 1, 9, 1, 0) - 1] = c2_temp;
      c2_a = c2_iy + 3;
      c2_iy = c2_a;
      c2_b_a = c2_ix + 3;
      c2_ix = c2_b_a;
    }
  }
}

static void c2_e_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c,
  real_T c2_s)
{
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  real_T c2_b_c;
  real_T c2_b_s;
  int32_T c2_c_n;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  real_T c2_c_c;
  real_T c2_c_s;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_d_n;
  int32_T c2_b;
  int32_T c2_b_b;
  boolean_T c2_overflow;
  int32_T c2_k;
  real_T c2_temp;
  int32_T c2_a;
  int32_T c2_b_a;
  c2_b_n = c2_n;
  c2_b_ix0 = c2_ix0;
  c2_b_iy0 = c2_iy0;
  c2_b_c = c2_c;
  c2_b_s = c2_s;
  c2_e_threshold(chartInstance);
  c2_c_n = c2_b_n;
  c2_c_ix0 = c2_b_ix0;
  c2_c_iy0 = c2_b_iy0;
  c2_c_c = c2_b_c;
  c2_c_s = c2_b_s;
  if (c2_c_n < 1) {
  } else {
    c2_ix = c2_c_ix0;
    c2_iy = c2_c_iy0;
    c2_d_n = c2_c_n;
    c2_b = c2_d_n;
    c2_b_b = c2_b;
    if (1 > c2_b_b) {
      c2_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_overflow = (c2_b_b > 2147483646);
    }

    if (c2_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_overflow);
    }

    for (c2_k = 1; c2_k <= c2_d_n; c2_k++) {
      c2_temp = c2_c_c * c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 9, 1, 0) - 1] + c2_c_s *
        c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_iy), 1, 9, 1, 0) - 1];
      c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_iy), 1, 9, 1, 0) - 1] = c2_c_c *
        c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_iy), 1, 9, 1, 0) - 1] - c2_c_s *
        c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_ix), 1, 9, 1, 0) - 1];
      c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_ix), 1, 9, 1, 0) - 1] = c2_temp;
      c2_a = c2_iy + 1;
      c2_iy = c2_a;
      c2_b_a = c2_ix + 1;
      c2_ix = c2_b_a;
    }
  }
}

static void c2_f_eml_xrot(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
  real_T c2_x[9], int32_T c2_ix0, int32_T c2_iy0, real_T c2_c, real_T c2_s)
{
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  real_T c2_b_c;
  real_T c2_b_s;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  real_T c2_c_c;
  real_T c2_c_s;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_k;
  real_T c2_temp;
  int32_T c2_a;
  int32_T c2_b_a;
  c2_b_ix0 = c2_ix0;
  c2_b_iy0 = c2_iy0;
  c2_b_c = c2_c;
  c2_b_s = c2_s;
  c2_e_threshold(chartInstance);
  c2_c_ix0 = c2_b_ix0;
  c2_c_iy0 = c2_b_iy0;
  c2_c_c = c2_b_c;
  c2_c_s = c2_b_s;
  c2_ix = c2_c_ix0;
  c2_iy = c2_c_iy0;
  for (c2_k = 1; c2_k < 4; c2_k++) {
    c2_temp = c2_c_c * c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
      _SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 9, 1, 0) - 1] + c2_c_s *
      c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_iy), 1, 9, 1, 0) - 1];
    c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_iy), 1, 9, 1, 0) - 1] = c2_c_c * c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_iy), 1, 9, 1, 0) - 1] - c2_c_s *
      c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_ix), 1, 9, 1, 0) - 1];
    c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
      c2_ix), 1, 9, 1, 0) - 1] = c2_temp;
    c2_a = c2_iy + 1;
    c2_iy = c2_a;
    c2_b_a = c2_ix + 1;
    c2_ix = c2_b_a;
  }
}

static void c2_d_sqrt(SFc2_CollisionStrategies2InstanceStruct *chartInstance,
                      creal_T *c2_x)
{
  real_T c2_yr;
  real_T c2_yi;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_z;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_b_z;
  boolean_T c2_b0;
  boolean_T c2_b1;
  boolean_T c2_b;
  real_T c2_h_x;
  boolean_T c2_b_b;
  real_T c2_i_x;
  boolean_T c2_c_b;
  real_T c2_absxr;
  real_T c2_absxi;
  real_T c2_j_x;
  real_T c2_y;
  real_T c2_x1;
  real_T c2_x2;
  real_T c2_a;
  real_T c2_d_b;
  real_T c2_absxd2;
  real_T c2_k_x;
  real_T c2_b_y;
  real_T c2_l_x;
  real_T c2_c_y;
  real_T c2_m_x;
  real_T c2_d_y;
  real_T c2_c_z;
  real_T c2_n_x;
  real_T c2_e_y;
  real_T c2_b_x1;
  real_T c2_b_x2;
  real_T c2_b_a;
  real_T c2_e_b;
  real_T c2_d_z;
  real_T c2_o_x;
  real_T c2_f_y;
  real_T c2_p_x;
  real_T c2_g_y;
  real_T c2_q_x;
  real_T c2_h_y;
  real_T c2_e_z;
  real_T c2_r_x;
  real_T c2_i_y;
  real_T c2_s_x;
  real_T c2_j_y;
  real_T c2_t_x;
  real_T c2_k_y;
  real_T c2_f_z;
  boolean_T guard1 = false;
  if (c2_x->im == 0.0) {
    if (c2_x->re < 0.0) {
      c2_yr = 0.0;
      c2_yi = muDoubleScalarSqrt(muDoubleScalarAbs(c2_x->re));
    } else {
      c2_yr = muDoubleScalarSqrt(c2_x->re);
      c2_yi = 0.0;
    }
  } else if (c2_x->re == 0.0) {
    if (c2_x->im < 0.0) {
      c2_b_x = -c2_x->im;
      c2_c_x = c2_b_x;
      c2_d_x = c2_c_x;
      c2_z = c2_d_x / 2.0;
      c2_yr = muDoubleScalarSqrt(c2_z);
      c2_yi = -c2_yr;
    } else {
      c2_e_x = c2_x->im;
      c2_f_x = c2_e_x;
      c2_g_x = c2_f_x;
      c2_b_z = c2_g_x / 2.0;
      c2_yr = muDoubleScalarSqrt(c2_b_z);
      c2_yi = c2_yr;
    }
  } else {
    c2_b0 = muDoubleScalarIsNaN(c2_x->re);
    c2_b1 = muDoubleScalarIsNaN(c2_x->im);
    c2_b = (c2_b0 || c2_b1);
    if (c2_b) {
      c2_yr = rtNaN;
      c2_yi = rtNaN;
    } else {
      c2_h_x = c2_x->im;
      c2_b_b = muDoubleScalarIsInf(c2_h_x);
      if (c2_b_b) {
        c2_yr = rtInf;
        c2_yi = c2_x->im;
      } else {
        c2_i_x = c2_x->re;
        c2_c_b = muDoubleScalarIsInf(c2_i_x);
        if (c2_c_b) {
          if (c2_x->re < 0.0) {
            c2_yr = 0.0;
            c2_yi = rtInf;
          } else {
            c2_yr = rtInf;
            c2_yi = 0.0;
          }
        } else {
          c2_absxr = muDoubleScalarAbs(c2_x->re);
          c2_absxi = muDoubleScalarAbs(c2_x->im);
          c2_realmax(chartInstance);
          guard1 = false;
          if (c2_absxr > 4.4942328371557893E+307) {
            guard1 = true;
          } else {
            c2_realmax(chartInstance);
            if (c2_absxi > 4.4942328371557893E+307) {
              guard1 = true;
            } else {
              c2_n_x = c2_absxr;
              c2_e_y = c2_absxi;
              c2_b_eml_scalar_eg(chartInstance);
              c2_b_x1 = c2_n_x;
              c2_b_x2 = c2_e_y;
              c2_b_a = c2_b_x1;
              c2_e_b = c2_b_x2;
              c2_d_z = muDoubleScalarHypot(c2_b_a, c2_e_b);
              c2_yr = muDoubleScalarSqrt((c2_d_z + c2_absxr) * 0.5);
            }
          }

          if (guard1 == true) {
            c2_absxr *= 0.5;
            c2_absxi *= 0.5;
            c2_j_x = c2_absxr;
            c2_y = c2_absxi;
            c2_b_eml_scalar_eg(chartInstance);
            c2_x1 = c2_j_x;
            c2_x2 = c2_y;
            c2_a = c2_x1;
            c2_d_b = c2_x2;
            c2_absxd2 = muDoubleScalarHypot(c2_a, c2_d_b);
            if (c2_absxd2 > c2_absxr) {
              c2_k_x = c2_absxr;
              c2_b_y = c2_absxd2;
              c2_l_x = c2_k_x;
              c2_c_y = c2_b_y;
              c2_m_x = c2_l_x;
              c2_d_y = c2_c_y;
              c2_c_z = c2_m_x / c2_d_y;
              c2_yr = muDoubleScalarSqrt(c2_absxd2) * muDoubleScalarSqrt(1.0 +
                c2_c_z);
            } else {
              c2_yr = muDoubleScalarSqrt(c2_absxd2) * 1.4142135623730951;
            }
          }

          if (c2_x->re > 0.0) {
            c2_o_x = c2_x->im;
            c2_f_y = c2_yr;
            c2_p_x = c2_o_x;
            c2_g_y = c2_f_y;
            c2_q_x = c2_p_x;
            c2_h_y = c2_g_y;
            c2_e_z = c2_q_x / c2_h_y;
            c2_yi = 0.5 * c2_e_z;
          } else {
            if (c2_x->im < 0.0) {
              c2_yi = -c2_yr;
            } else {
              c2_yi = c2_yr;
            }

            c2_r_x = c2_x->im;
            c2_i_y = c2_yi;
            c2_s_x = c2_r_x;
            c2_j_y = c2_i_y;
            c2_t_x = c2_s_x;
            c2_k_y = c2_j_y;
            c2_f_z = c2_t_x / c2_k_y;
            c2_yr = 0.5 * c2_f_z;
          }
        }
      }
    }
  }

  c2_x->re = c2_yr;
  c2_x->im = c2_yi;
}

static void c2_b_eml_xgemm(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance, creal_T c2_A[9], creal_T c2_B[9], creal_T c2_C[9])
{
  int32_T c2_i108;
  int32_T c2_i109;
  int32_T c2_i110;
  int32_T c2_i111;
  int32_T c2_i112;
  creal_T c2_b_A;
  (void)chartInstance;
  for (c2_i108 = 0; c2_i108 < 3; c2_i108++) {
    c2_i109 = 0;
    for (c2_i110 = 0; c2_i110 < 3; c2_i110++) {
      c2_C[c2_i109 + c2_i108].re = 0.0;
      c2_C[c2_i109 + c2_i108].im = 0.0;
      c2_i111 = 0;
      for (c2_i112 = 0; c2_i112 < 3; c2_i112++) {
        c2_b_A.re = c2_A[c2_i111 + c2_i108].re * c2_B[c2_i112 + c2_i109].re -
          c2_A[c2_i111 + c2_i108].im * c2_B[c2_i112 + c2_i109].im;
        c2_b_A.im = c2_A[c2_i111 + c2_i108].re * c2_B[c2_i112 + c2_i109].im +
          c2_A[c2_i111 + c2_i108].im * c2_B[c2_i112 + c2_i109].re;
        c2_C[c2_i109 + c2_i108].re += c2_b_A.re;
        c2_C[c2_i109 + c2_i108].im += c2_b_A.im;
        c2_i111 += 3;
      }

      c2_i109 += 3;
    }
  }
}

static void init_dsm_address_info(SFc2_CollisionStrategies2InstanceStruct
  *chartInstance)
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

void sf_c2_CollisionStrategies2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(763846690U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4093679225U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1035552234U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1079551490U);
}

mxArray *sf_c2_CollisionStrategies2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("EROkReCRXJCOIBLHD7YM8C");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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

mxArray *sf_c2_CollisionStrategies2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_CollisionStrategies2_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_CollisionStrategies2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c2_CollisionStrategies2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_CollisionStrategies2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_CollisionStrategies2InstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_CollisionStrategies2InstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _CollisionStrategies2MachineNumber_,
           2,
           1,
           1,
           0,
           2,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_CollisionStrategies2MachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_CollisionStrategies2MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _CollisionStrategies2MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_SET_DATA_PROPS(1,2,0,1,"y");
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
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,56);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          real_T (*c2_u)[9];
          real_T (*c2_y)[9];
          c2_y = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_u = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_u);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_y);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _CollisionStrategies2MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "ARGtbBB4TM9lz1qMhunj6B";
}

static void sf_opaque_initialize_c2_CollisionStrategies2(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_CollisionStrategies2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_CollisionStrategies2
    ((SFc2_CollisionStrategies2InstanceStruct*) chartInstanceVar);
  initialize_c2_CollisionStrategies2((SFc2_CollisionStrategies2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_CollisionStrategies2(void *chartInstanceVar)
{
  enable_c2_CollisionStrategies2((SFc2_CollisionStrategies2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_CollisionStrategies2(void *chartInstanceVar)
{
  disable_c2_CollisionStrategies2((SFc2_CollisionStrategies2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_CollisionStrategies2(void *chartInstanceVar)
{
  sf_gateway_c2_CollisionStrategies2((SFc2_CollisionStrategies2InstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_CollisionStrategies2
  (SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_CollisionStrategies2
    ((SFc2_CollisionStrategies2InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_CollisionStrategies2();/* state var info */
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

extern void sf_internal_set_sim_state_c2_CollisionStrategies2(SimStruct* S,
  const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c2_CollisionStrategies2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_CollisionStrategies2((SFc2_CollisionStrategies2InstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_CollisionStrategies2(SimStruct*
  S)
{
  return sf_internal_get_sim_state_c2_CollisionStrategies2(S);
}

static void sf_opaque_set_sim_state_c2_CollisionStrategies2(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_CollisionStrategies2(S, st);
}

static void sf_opaque_terminate_c2_CollisionStrategies2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_CollisionStrategies2InstanceStruct*) chartInstanceVar
      )->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_CollisionStrategies2_optimization_info();
    }

    finalize_c2_CollisionStrategies2((SFc2_CollisionStrategies2InstanceStruct*)
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
  initSimStructsc2_CollisionStrategies2((SFc2_CollisionStrategies2InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_CollisionStrategies2(SimStruct *S)
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
    initialize_params_c2_CollisionStrategies2
      ((SFc2_CollisionStrategies2InstanceStruct*)(chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_CollisionStrategies2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_CollisionStrategies2_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1001685567U));
  ssSetChecksum1(S,(302164723U));
  ssSetChecksum2(S,(2075021511U));
  ssSetChecksum3(S,(1407823288U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_CollisionStrategies2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_CollisionStrategies2(SimStruct *S)
{
  SFc2_CollisionStrategies2InstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_CollisionStrategies2InstanceStruct *)utMalloc(sizeof
    (SFc2_CollisionStrategies2InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_CollisionStrategies2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_CollisionStrategies2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_CollisionStrategies2;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_CollisionStrategies2;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c2_CollisionStrategies2;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c2_CollisionStrategies2;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_CollisionStrategies2;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_CollisionStrategies2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_CollisionStrategies2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_CollisionStrategies2;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_CollisionStrategies2;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_CollisionStrategies2;
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

void c2_CollisionStrategies2_method_dispatcher(SimStruct *S, int_T method, void *
  data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_CollisionStrategies2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_CollisionStrategies2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_CollisionStrategies2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_CollisionStrategies2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
