/* Include files */

#include <stddef.h>
#include "blas.h"
#include "m3dof_library_sfun.h"
#include "c2_m3dof_library.h"
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
static const char * c2_debug_family_names[15] = { "c1", "s1", "c12", "s12",
  "c123", "s123", "nargin", "nargout", "q", "l1", "l2", "l3", "T01", "T02",
  "T03" };

/* Function Declarations */
static void initialize_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance);
static void initialize_params_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct *
  chartInstance);
static void enable_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance);
static void disable_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_m3dof_library
  (SFc2_m3dof_libraryInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_m3dof_library
  (SFc2_m3dof_libraryInstanceStruct *chartInstance);
static void set_sim_state_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance);
static void sf_gateway_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance);
static void initSimStructsc2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct *chartInstance,
  const mxArray *c2_T03, const char_T *c2_identifier, real_T c2_y[12]);
static void c2_b_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[12]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(const char * c2_u);
static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_d_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_e_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_m3dof_library, const char_T
  *c2_identifier);
static uint8_T c2_f_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_m3dof_libraryInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_m3dof_library = 0U;
}

static void initialize_params_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct *
  chartInstance)
{
  real_T c2_d0;
  real_T c2_d1;
  real_T c2_d2;
  sf_mex_import_named("l1", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c2_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_l1 = c2_d0;
  sf_mex_import_named("l2", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                      &c2_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_l2 = c2_d1;
  sf_mex_import_named("l3", sf_mex_get_sfun_param(chartInstance->S, 2, 0),
                      &c2_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_l3 = c2_d2;
}

static void enable_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_m3dof_library
  (SFc2_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_m3dof_library
  (SFc2_m3dof_libraryInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[12];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i1;
  real_T c2_b_u[12];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i2;
  real_T c2_c_u[12];
  const mxArray *c2_d_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  real_T (*c2_T03)[12];
  real_T (*c2_T02)[12];
  real_T (*c2_T01)[12];
  c2_T03 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_T02 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_T01 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(4, 1), false);
  for (c2_i0 = 0; c2_i0 < 12; c2_i0++) {
    c2_u[c2_i0] = (*c2_T01)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 4), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  for (c2_i1 = 0; c2_i1 < 12; c2_i1++) {
    c2_b_u[c2_i1] = (*c2_T02)[c2_i1];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 3, 4),
                false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  for (c2_i2 = 0; c2_i2 < 12; c2_i2++) {
    c2_c_u[c2_i2] = (*c2_T03)[c2_i2];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 3, 4),
                false);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_m3dof_library;
  c2_d_u = c2_hoistedGlobal;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 3, c2_e_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[12];
  int32_T c2_i3;
  real_T c2_dv1[12];
  int32_T c2_i4;
  real_T c2_dv2[12];
  int32_T c2_i5;
  real_T (*c2_T01)[12];
  real_T (*c2_T02)[12];
  real_T (*c2_T03)[12];
  c2_T03 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_T02 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_T01 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "T01",
                      c2_dv0);
  for (c2_i3 = 0; c2_i3 < 12; c2_i3++) {
    (*c2_T01)[c2_i3] = c2_dv0[c2_i3];
  }

  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)), "T02",
                      c2_dv1);
  for (c2_i4 = 0; c2_i4 < 12; c2_i4++) {
    (*c2_T02)[c2_i4] = c2_dv1[c2_i4];
  }

  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)), "T03",
                      c2_dv2);
  for (c2_i5 = 0; c2_i5 < 12; c2_i5++) {
    (*c2_T03)[c2_i5] = c2_dv2[c2_i5];
  }

  chartInstance->c2_is_active_c2_m3dof_library = c2_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 3)),
     "is_active_c2_m3dof_library");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_m3dof_library(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance)
{
  int32_T c2_i6;
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  real_T c2_c_hoistedGlobal;
  int32_T c2_i7;
  real_T c2_q[3];
  real_T c2_b_l1;
  real_T c2_b_l2;
  real_T c2_b_l3;
  uint32_T c2_debug_family_var_map[15];
  real_T c2_c1;
  real_T c2_s1;
  real_T c2_c12;
  real_T c2_s12;
  real_T c2_c123;
  real_T c2_s123;
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 3.0;
  real_T c2_T01[12];
  real_T c2_T02[12];
  real_T c2_T03[12];
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_l_x;
  int32_T c2_i8;
  int32_T c2_i9;
  static real_T c2_dv3[4] = { 0.0, 0.0, 1.0, 0.0 };

  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  int32_T c2_i13;
  int32_T c2_i14;
  int32_T c2_i15;
  int32_T c2_i16;
  int32_T c2_i17;
  int32_T c2_i18;
  int32_T c2_i19;
  real_T (*c2_b_T01)[12];
  real_T (*c2_b_T02)[12];
  real_T (*c2_b_T03)[12];
  real_T (*c2_b_q)[3];
  c2_b_T03 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_b_T02 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_b_T01 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_q = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i6 = 0; c2_i6 < 3; c2_i6++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_q)[c2_i6], 0U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = chartInstance->c2_l1;
  c2_b_hoistedGlobal = chartInstance->c2_l2;
  c2_c_hoistedGlobal = chartInstance->c2_l3;
  for (c2_i7 = 0; c2_i7 < 3; c2_i7++) {
    c2_q[c2_i7] = (*c2_b_q)[c2_i7];
  }

  c2_b_l1 = c2_hoistedGlobal;
  c2_b_l2 = c2_b_hoistedGlobal;
  c2_b_l3 = c2_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 15U, 15U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c1, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_s1, 1U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c12, 2U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_s12, 3U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c123, 4U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_s123, 5U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 6U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 7U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_q, 8U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_l1, 9U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_l2, 10U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_l3, 11U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_T01, 12U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_T02, 13U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_T03, 14U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  c2_x = c2_q[0];
  c2_c1 = c2_x;
  c2_b_x = c2_c1;
  c2_c1 = c2_b_x;
  c2_c1 = muDoubleScalarCos(c2_c1);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_c_x = c2_q[0];
  c2_s1 = c2_c_x;
  c2_d_x = c2_s1;
  c2_s1 = c2_d_x;
  c2_s1 = muDoubleScalarSin(c2_s1);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  c2_e_x = c2_q[0] + c2_q[1];
  c2_c12 = c2_e_x;
  c2_f_x = c2_c12;
  c2_c12 = c2_f_x;
  c2_c12 = muDoubleScalarCos(c2_c12);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_g_x = c2_q[0] + c2_q[1];
  c2_s12 = c2_g_x;
  c2_h_x = c2_s12;
  c2_s12 = c2_h_x;
  c2_s12 = muDoubleScalarSin(c2_s12);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  c2_i_x = (c2_q[0] + c2_q[1]) + c2_q[2];
  c2_c123 = c2_i_x;
  c2_j_x = c2_c123;
  c2_c123 = c2_j_x;
  c2_c123 = muDoubleScalarCos(c2_c123);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  c2_k_x = (c2_q[0] + c2_q[1]) + c2_q[2];
  c2_s123 = c2_k_x;
  c2_l_x = c2_s123;
  c2_s123 = c2_l_x;
  c2_s123 = muDoubleScalarSin(c2_s123);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
  c2_T01[0] = c2_c1;
  c2_T01[3] = -c2_s1;
  c2_T01[6] = 0.0;
  c2_T01[9] = c2_b_l1 * c2_c1;
  c2_T01[1] = c2_s1;
  c2_T01[4] = c2_c1;
  c2_T01[7] = 0.0;
  c2_T01[10] = c2_b_l1 * c2_s1;
  c2_i8 = 0;
  for (c2_i9 = 0; c2_i9 < 4; c2_i9++) {
    c2_T01[c2_i8 + 2] = c2_dv3[c2_i9];
    c2_i8 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
  c2_T02[0] = c2_c12;
  c2_T02[3] = -c2_s12;
  c2_T02[6] = 0.0;
  c2_T02[9] = c2_b_l1 * c2_c1 + c2_b_l2 * c2_c12;
  c2_T02[1] = c2_s12;
  c2_T02[4] = c2_c12;
  c2_T02[7] = 0.0;
  c2_T02[10] = c2_b_l1 * c2_s1 + c2_b_l2 * c2_s12;
  c2_i10 = 0;
  for (c2_i11 = 0; c2_i11 < 4; c2_i11++) {
    c2_T02[c2_i10 + 2] = c2_dv3[c2_i11];
    c2_i10 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
  c2_T03[0] = c2_c123;
  c2_T03[3] = -c2_s123;
  c2_T03[6] = 0.0;
  c2_T03[9] = (c2_b_l1 * c2_c1 + c2_b_l2 * c2_c12) + c2_b_l3 * c2_c123;
  c2_T03[1] = c2_s123;
  c2_T03[4] = c2_c123;
  c2_T03[7] = 0.0;
  c2_T03[10] = (c2_b_l1 * c2_s1 + c2_b_l2 * c2_s12) + c2_b_l3 * c2_s123;
  c2_i12 = 0;
  for (c2_i13 = 0; c2_i13 < 4; c2_i13++) {
    c2_T03[c2_i12 + 2] = c2_dv3[c2_i13];
    c2_i12 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -15);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i14 = 0; c2_i14 < 12; c2_i14++) {
    (*c2_b_T01)[c2_i14] = c2_T01[c2_i14];
  }

  for (c2_i15 = 0; c2_i15 < 12; c2_i15++) {
    (*c2_b_T02)[c2_i15] = c2_T02[c2_i15];
  }

  for (c2_i16 = 0; c2_i16 < 12; c2_i16++) {
    (*c2_b_T03)[c2_i16] = c2_T03[c2_i16];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_m3dof_libraryMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c2_i17 = 0; c2_i17 < 12; c2_i17++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_T01)[c2_i17], 1U);
  }

  for (c2_i18 = 0; c2_i18 < 12; c2_i18++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_T02)[c2_i18], 2U);
  }

  for (c2_i19 = 0; c2_i19 < 12; c2_i19++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_T03)[c2_i19], 3U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c2_l1, 4U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c2_l2, 5U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c2_l3, 6U);
}

static void initSimStructsc2_m3dof_library(SFc2_m3dof_libraryInstanceStruct
  *chartInstance)
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
  int32_T c2_i20;
  int32_T c2_i21;
  int32_T c2_i22;
  real_T c2_b_inData[12];
  int32_T c2_i23;
  int32_T c2_i24;
  int32_T c2_i25;
  real_T c2_u[12];
  const mxArray *c2_y = NULL;
  SFc2_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc2_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i20 = 0;
  for (c2_i21 = 0; c2_i21 < 4; c2_i21++) {
    for (c2_i22 = 0; c2_i22 < 3; c2_i22++) {
      c2_b_inData[c2_i22 + c2_i20] = (*(real_T (*)[12])c2_inData)[c2_i22 +
        c2_i20];
    }

    c2_i20 += 3;
  }

  c2_i23 = 0;
  for (c2_i24 = 0; c2_i24 < 4; c2_i24++) {
    for (c2_i25 = 0; c2_i25 < 3; c2_i25++) {
      c2_u[c2_i25 + c2_i23] = c2_b_inData[c2_i25 + c2_i23];
    }

    c2_i23 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 4), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct *chartInstance,
  const mxArray *c2_T03, const char_T *c2_identifier, real_T c2_y[12])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_T03), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_T03);
}

static void c2_b_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[12])
{
  real_T c2_dv4[12];
  int32_T c2_i26;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv4, 1, 0, 0U, 1, 0U, 2, 3, 4);
  for (c2_i26 = 0; c2_i26 < 12; c2_i26++) {
    c2_y[c2_i26] = c2_dv4[c2_i26];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_T03;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[12];
  int32_T c2_i27;
  int32_T c2_i28;
  int32_T c2_i29;
  SFc2_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc2_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c2_T03 = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_T03), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_T03);
  c2_i27 = 0;
  for (c2_i28 = 0; c2_i28 < 4; c2_i28++) {
    for (c2_i29 = 0; c2_i29 < 3; c2_i29++) {
      (*(real_T (*)[12])c2_outData)[c2_i29 + c2_i27] = c2_y[c2_i29 + c2_i27];
    }

    c2_i27 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc2_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d3;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d3, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d3;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_l3;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc2_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c2_b_l3 = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_l3), &c2_thisId);
  sf_mex_destroy(&c2_b_l3);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i30;
  real_T c2_b_inData[3];
  int32_T c2_i31;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc2_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i30 = 0; c2_i30 < 3; c2_i30++) {
    c2_b_inData[c2_i30] = (*(real_T (*)[3])c2_inData)[c2_i30];
  }

  for (c2_i31 = 0; c2_i31 < 3; c2_i31++) {
    c2_u[c2_i31] = c2_b_inData[c2_i31];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

const mxArray *sf_c2_m3dof_library_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 4, 1),
                false);
  c2_info_helper(&c2_nameCaptureInfo);
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
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("cos"), "name", "name", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
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
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_cos"), "name",
                  "name", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818722U), "fileTimeLo",
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
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("sin"), "name", "name", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
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
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818736U), "fileTimeLo",
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
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
  sf_mex_destroy(&c2_rhs1);
  sf_mex_destroy(&c2_lhs1);
  sf_mex_destroy(&c2_rhs2);
  sf_mex_destroy(&c2_lhs2);
  sf_mex_destroy(&c2_rhs3);
  sf_mex_destroy(&c2_lhs3);
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

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc2_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_d_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i32;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i32, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i32;
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
  SFc2_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc2_m3dof_libraryInstanceStruct *)chartInstanceVoid;
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

static uint8_T c2_e_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_m3dof_library, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_m3dof_library), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_m3dof_library);
  return c2_y;
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_m3dof_libraryInstanceStruct
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

static void init_dsm_address_info(SFc2_m3dof_libraryInstanceStruct
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

void sf_c2_m3dof_library_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3210569515U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1811551492U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(964686200U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3131999434U);
}

mxArray *sf_c2_m3dof_library_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("yUZK09VDiaWwc8hbKcDX1F");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
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
      pr[0] = (double)(1);
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
      pr[0] = (double)(1);
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
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(4);
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
      pr[1] = (double)(4);
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
      pr[1] = (double)(4);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_m3dof_library_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_m3dof_library_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_m3dof_library(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[5],T\"T01\",},{M[1],M[6],T\"T02\",},{M[1],M[7],T\"T03\",},{M[8],M[0],T\"is_active_c2_m3dof_library\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_m3dof_library_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_m3dof_libraryInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_m3dof_libraryInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _m3dof_libraryMachineNumber_,
           2,
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
          _SFD_SET_DATA_PROPS(1,2,0,1,"T01");
          _SFD_SET_DATA_PROPS(2,2,0,1,"T02");
          _SFD_SET_DATA_PROPS(3,2,0,1,"T03");
          _SFD_SET_DATA_PROPS(4,10,0,0,"l1");
          _SFD_SET_DATA_PROPS(5,10,0,0,"l2");
          _SFD_SET_DATA_PROPS(6,10,0,0,"l3");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,461);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);

        {
          real_T (*c2_q)[3];
          real_T (*c2_T01)[12];
          real_T (*c2_T02)[12];
          real_T (*c2_T03)[12];
          c2_T03 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 3);
          c2_T02 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 2);
          c2_T01 = (real_T (*)[12])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_q = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_q);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_T01);
          _SFD_SET_DATA_VALUE_PTR(2U, *c2_T02);
          _SFD_SET_DATA_VALUE_PTR(3U, *c2_T03);
          _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance->c2_l1);
          _SFD_SET_DATA_VALUE_PTR(5U, &chartInstance->c2_l2);
          _SFD_SET_DATA_VALUE_PTR(6U, &chartInstance->c2_l3);
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
  return "4AKay5lWZU733EqWqUlbKF";
}

static void sf_opaque_initialize_c2_m3dof_library(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_m3dof_libraryInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_m3dof_library((SFc2_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
  initialize_c2_m3dof_library((SFc2_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_m3dof_library(void *chartInstanceVar)
{
  enable_c2_m3dof_library((SFc2_m3dof_libraryInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_m3dof_library(void *chartInstanceVar)
{
  disable_c2_m3dof_library((SFc2_m3dof_libraryInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_m3dof_library(void *chartInstanceVar)
{
  sf_gateway_c2_m3dof_library((SFc2_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_m3dof_library(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_m3dof_library
    ((SFc2_m3dof_libraryInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_m3dof_library();/* state var info */
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

extern void sf_internal_set_sim_state_c2_m3dof_library(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c2_m3dof_library();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_m3dof_library((SFc2_m3dof_libraryInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_m3dof_library(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_m3dof_library(S);
}

static void sf_opaque_set_sim_state_c2_m3dof_library(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c2_m3dof_library(S, st);
}

static void sf_opaque_terminate_c2_m3dof_library(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_m3dof_libraryInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_m3dof_library_optimization_info();
    }

    finalize_c2_m3dof_library((SFc2_m3dof_libraryInstanceStruct*)
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
  initSimStructsc2_m3dof_library((SFc2_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_m3dof_library(SimStruct *S)
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
    initialize_params_c2_m3dof_library((SFc2_m3dof_libraryInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_m3dof_library(SimStruct *S)
{
  /* Actual parameters from chart:
     l1 l2 l3
   */
  const char_T *rtParamNames[] = { "l1", "l2", "l3" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for l1*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for l2*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* registration for l3*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_DOUBLE);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_m3dof_library_optimization_info();
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
        infoStruct,2,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
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
  ssSetChecksum0(S,(1637945053U));
  ssSetChecksum1(S,(1294203137U));
  ssSetChecksum2(S,(506367278U));
  ssSetChecksum3(S,(3958915865U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_m3dof_library(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_m3dof_library(SimStruct *S)
{
  SFc2_m3dof_libraryInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_m3dof_libraryInstanceStruct *)utMalloc(sizeof
    (SFc2_m3dof_libraryInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_m3dof_libraryInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_m3dof_library;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_m3dof_library;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_m3dof_library;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_m3dof_library;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_m3dof_library;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_m3dof_library;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_m3dof_library;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_m3dof_library;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_m3dof_library;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_m3dof_library;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_m3dof_library;
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

void c2_m3dof_library_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_m3dof_library(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_m3dof_library(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_m3dof_library(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_m3dof_library_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
