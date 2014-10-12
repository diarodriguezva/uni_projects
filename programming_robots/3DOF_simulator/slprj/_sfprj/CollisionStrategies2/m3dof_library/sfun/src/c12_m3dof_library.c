/* Include files */

#include <stddef.h>
#include "blas.h"
#include "m3dof_library_sfun.h"
#include "c12_m3dof_library.h"
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
static const char * c12_debug_family_names[30] = { "MAS", "t1", "t3", "t4", "t6",
  "t7", "t9", "t10", "t12", "t14", "t15", "t16", "t18", "t20", "t23", "t24",
  "t26", "t27", "t28", "t30", "i", "j", "nargin", "nargout", "q", "xi1", "xi2",
  "xi3", "a", "M" };

/* Function Declarations */
static void initialize_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance);
static void initialize_params_c12_m3dof_library
  (SFc12_m3dof_libraryInstanceStruct *chartInstance);
static void enable_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance);
static void disable_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance);
static void c12_update_debugger_state_c12_m3dof_library
  (SFc12_m3dof_libraryInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c12_m3dof_library
  (SFc12_m3dof_libraryInstanceStruct *chartInstance);
static void set_sim_state_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_st);
static void finalize_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance);
static void sf_gateway_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance);
static void c12_chartstep_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance);
static void initSimStructsc12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber, uint32_T c12_instanceNumber);
static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_M, const char_T *c12_identifier, real_T
  c12_y[9]);
static void c12_b_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[9]);
static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static real_T c12_c_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static void c12_info_helper(const mxArray **c12_info);
static const mxArray *c12_emlrt_marshallOut(const char * c12_u);
static const mxArray *c12_b_emlrt_marshallOut(const uint32_T c12_u);
static real_T c12_mpower(SFc12_m3dof_libraryInstanceStruct *chartInstance,
  real_T c12_a);
static void c12_eml_scalar_eg(SFc12_m3dof_libraryInstanceStruct *chartInstance);
static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static int32_T c12_d_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static uint8_T c12_e_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_b_is_active_c12_m3dof_library, const char_T
  *c12_identifier);
static uint8_T c12_f_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void init_dsm_address_info(SFc12_m3dof_libraryInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance)
{
  chartInstance->c12_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c12_is_active_c12_m3dof_library = 0U;
}

static void initialize_params_c12_m3dof_library
  (SFc12_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c12_update_debugger_state_c12_m3dof_library
  (SFc12_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c12_m3dof_library
  (SFc12_m3dof_libraryInstanceStruct *chartInstance)
{
  const mxArray *c12_st;
  const mxArray *c12_y = NULL;
  int32_T c12_i0;
  real_T c12_u[9];
  const mxArray *c12_b_y = NULL;
  uint8_T c12_hoistedGlobal;
  uint8_T c12_b_u;
  const mxArray *c12_c_y = NULL;
  real_T (*c12_M)[9];
  c12_M = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_st = NULL;
  c12_st = NULL;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_createcellmatrix(2, 1), false);
  for (c12_i0 = 0; c12_i0 < 9; c12_i0++) {
    c12_u[c12_i0] = (*c12_M)[c12_i0];
  }

  c12_b_y = NULL;
  sf_mex_assign(&c12_b_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_setcell(c12_y, 0, c12_b_y);
  c12_hoistedGlobal = chartInstance->c12_is_active_c12_m3dof_library;
  c12_b_u = c12_hoistedGlobal;
  c12_c_y = NULL;
  sf_mex_assign(&c12_c_y, sf_mex_create("y", &c12_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c12_y, 1, c12_c_y);
  sf_mex_assign(&c12_st, c12_y, false);
  return c12_st;
}

static void set_sim_state_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_st)
{
  const mxArray *c12_u;
  real_T c12_dv0[9];
  int32_T c12_i1;
  real_T (*c12_M)[9];
  c12_M = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c12_doneDoubleBufferReInit = true;
  c12_u = sf_mex_dup(c12_st);
  c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 0)), "M",
                       c12_dv0);
  for (c12_i1 = 0; c12_i1 < 9; c12_i1++) {
    (*c12_M)[c12_i1] = c12_dv0[c12_i1];
  }

  chartInstance->c12_is_active_c12_m3dof_library = c12_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 1)),
     "is_active_c12_m3dof_library");
  sf_mex_destroy(&c12_u);
  c12_update_debugger_state_c12_m3dof_library(chartInstance);
  sf_mex_destroy(&c12_st);
}

static void finalize_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance)
{
  int32_T c12_i2;
  int32_T c12_i3;
  int32_T c12_i4;
  int32_T c12_i5;
  int32_T c12_i6;
  int32_T c12_i7;
  real_T (*c12_a)[3];
  real_T (*c12_xi3)[3];
  real_T (*c12_xi2)[3];
  real_T (*c12_M)[9];
  real_T (*c12_xi1)[3];
  real_T (*c12_q)[3];
  c12_a = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c12_xi3 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c12_xi2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c12_M = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_xi1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c12_q = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c12_sfEvent);
  for (c12_i2 = 0; c12_i2 < 3; c12_i2++) {
    _SFD_DATA_RANGE_CHECK((*c12_q)[c12_i2], 0U);
  }

  for (c12_i3 = 0; c12_i3 < 3; c12_i3++) {
    _SFD_DATA_RANGE_CHECK((*c12_xi1)[c12_i3], 1U);
  }

  chartInstance->c12_sfEvent = CALL_EVENT;
  c12_chartstep_c12_m3dof_library(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_m3dof_libraryMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c12_i4 = 0; c12_i4 < 9; c12_i4++) {
    _SFD_DATA_RANGE_CHECK((*c12_M)[c12_i4], 2U);
  }

  for (c12_i5 = 0; c12_i5 < 3; c12_i5++) {
    _SFD_DATA_RANGE_CHECK((*c12_xi2)[c12_i5], 3U);
  }

  for (c12_i6 = 0; c12_i6 < 3; c12_i6++) {
    _SFD_DATA_RANGE_CHECK((*c12_xi3)[c12_i6], 4U);
  }

  for (c12_i7 = 0; c12_i7 < 3; c12_i7++) {
    _SFD_DATA_RANGE_CHECK((*c12_a)[c12_i7], 5U);
  }
}

static void c12_chartstep_c12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance)
{
  int32_T c12_i8;
  real_T c12_q[3];
  int32_T c12_i9;
  real_T c12_xi1[3];
  int32_T c12_i10;
  real_T c12_xi2[3];
  int32_T c12_i11;
  real_T c12_xi3[3];
  int32_T c12_i12;
  real_T c12_a[3];
  uint32_T c12_debug_family_var_map[30];
  real_T c12_MAS[9];
  real_T c12_t1;
  real_T c12_t3;
  real_T c12_t4;
  real_T c12_t6;
  real_T c12_t7;
  real_T c12_t9;
  real_T c12_t10;
  real_T c12_t12;
  real_T c12_t14;
  real_T c12_t15;
  real_T c12_t16;
  real_T c12_t18;
  real_T c12_t20;
  real_T c12_t23;
  real_T c12_t24;
  real_T c12_t26;
  real_T c12_t27;
  real_T c12_t28;
  real_T c12_t30;
  real_T c12_i;
  real_T c12_j;
  real_T c12_nargin = 5.0;
  real_T c12_nargout = 1.0;
  real_T c12_M[9];
  int32_T c12_i13;
  int32_T c12_i14;
  real_T c12_x;
  real_T c12_b_x;
  real_T c12_c_x;
  real_T c12_d_x;
  real_T c12_e_x;
  real_T c12_f_x;
  real_T c12_g_x;
  real_T c12_h_x;
  int32_T c12_b_i;
  int32_T c12_b_j;
  int32_T c12_i15;
  real_T (*c12_b_M)[9];
  real_T (*c12_b_a)[3];
  real_T (*c12_b_xi3)[3];
  real_T (*c12_b_xi2)[3];
  real_T (*c12_b_xi1)[3];
  real_T (*c12_b_q)[3];
  c12_b_a = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c12_b_xi3 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c12_b_xi2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c12_b_M = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_b_xi1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c12_b_q = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c12_sfEvent);
  for (c12_i8 = 0; c12_i8 < 3; c12_i8++) {
    c12_q[c12_i8] = (*c12_b_q)[c12_i8];
  }

  for (c12_i9 = 0; c12_i9 < 3; c12_i9++) {
    c12_xi1[c12_i9] = (*c12_b_xi1)[c12_i9];
  }

  for (c12_i10 = 0; c12_i10 < 3; c12_i10++) {
    c12_xi2[c12_i10] = (*c12_b_xi2)[c12_i10];
  }

  for (c12_i11 = 0; c12_i11 < 3; c12_i11++) {
    c12_xi3[c12_i11] = (*c12_b_xi3)[c12_i11];
  }

  for (c12_i12 = 0; c12_i12 < 3; c12_i12++) {
    c12_a[c12_i12] = (*c12_b_a)[c12_i12];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 30U, 30U, c12_debug_family_names,
    c12_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_MAS, 0U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t1, 1U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t3, 2U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t4, 3U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t6, 4U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t7, 5U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t9, 6U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t10, 7U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t12, 8U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t14, 9U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t15, 10U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t16, 11U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t18, 12U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t20, 13U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t23, 14U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t24, 15U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t26, 16U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t27, 17U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t28, 18U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_t30, 19U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_i, 20U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_j, 21U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargin, 22U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargout, 23U, c12_c_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_q, 24U, c12_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_xi1, 25U, c12_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_xi2, 26U, c12_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_xi3, 27U, c12_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_a, 28U, c12_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_M, 29U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 4);
  for (c12_i13 = 0; c12_i13 < 9; c12_i13++) {
    c12_M[c12_i13] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 5);
  for (c12_i14 = 0; c12_i14 < 9; c12_i14++) {
    c12_MAS[c12_i14] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 8);
  c12_t1 = c12_mpower(chartInstance, c12_a[0]);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 9);
  c12_x = c12_q[2];
  c12_t3 = c12_x;
  c12_b_x = c12_t3;
  c12_t3 = c12_b_x;
  c12_t3 = muDoubleScalarCos(c12_t3);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 10);
  c12_c_x = c12_q[1];
  c12_t4 = c12_c_x;
  c12_d_x = c12_t4;
  c12_t4 = c12_d_x;
  c12_t4 = muDoubleScalarCos(c12_t4);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 11);
  c12_t6 = c12_a[0] * c12_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 12);
  c12_t7 = c12_t3 * c12_t4 * c12_t6;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 13);
  c12_e_x = c12_q[2];
  c12_t9 = c12_e_x;
  c12_f_x = c12_t9;
  c12_t9 = c12_f_x;
  c12_t9 = muDoubleScalarSin(c12_t9);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 14);
  c12_g_x = c12_q[1];
  c12_t10 = c12_g_x;
  c12_h_x = c12_t10;
  c12_t10 = c12_h_x;
  c12_t10 = muDoubleScalarSin(c12_t10);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 15);
  c12_t12 = c12_t9 * c12_t10 * c12_t6;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 16);
  c12_t14 = c12_mpower(chartInstance, c12_a[1]);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 17);
  c12_t15 = c12_t14 * c12_xi3[0];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 18);
  c12_t16 = c12_t4 * c12_a[0];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 19);
  c12_t18 = c12_t16 * c12_a[1] * c12_xi3[0];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 20);
  c12_t20 = c12_t16 * c12_xi2[1];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 21);
  c12_t23 = c12_t3 * c12_a[1] * c12_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 22);
  c12_t24 = 2.0 * c12_t23;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 23);
  c12_t26 = (((((((((c12_xi3[2] + c12_t1 * c12_xi2[0]) + 2.0 * c12_t7) - 2.0 *
                   c12_t12) + c12_xi2[2]) + c12_xi1[2]) + c12_t15) + 2.0 *
               c12_t18) + 2.0 * c12_t20) + c12_t24) + c12_t1 * c12_xi3[0];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 24);
  c12_t27 = ((((((c12_xi2[2] + c12_t20) + c12_t15) + c12_t18) - c12_t12) +
              c12_t24) + c12_xi3[2]) + c12_t7;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 25);
  c12_t28 = ((c12_xi3[2] - c12_t12) + c12_t7) + c12_t23;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 26);
  c12_t30 = c12_xi3[2] + c12_t23;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 27);
  c12_MAS[0] = c12_t26;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 28);
  c12_MAS[3] = c12_t27;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 29);
  c12_MAS[6] = c12_t28;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 30);
  c12_MAS[1] = c12_t27;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 31);
  c12_MAS[4] = ((c12_xi3[2] + c12_xi2[2]) + c12_t24) + c12_t15;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 32);
  c12_MAS[7] = c12_t30;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 33);
  c12_MAS[2] = c12_t28;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 34);
  c12_MAS[5] = c12_t30;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 35);
  c12_MAS[8] = c12_xi3[2];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 39);
  c12_i = 1.0;
  c12_b_i = 0;
  while (c12_b_i < 3) {
    c12_i = 1.0 + (real_T)c12_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 40);
    c12_j = 1.0;
    c12_b_j = 0;
    while (c12_b_j < 3) {
      c12_j = 1.0 + (real_T)c12_b_j;
      CV_EML_FOR(0, 1, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 41);
      c12_M[(_SFD_EML_ARRAY_BOUNDS_CHECK("M", (int32_T)_SFD_INTEGER_CHECK("i",
               c12_i), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("M",
               (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0) - 1)) - 1] =
        c12_MAS[(_SFD_EML_ARRAY_BOUNDS_CHECK("MAS", (int32_T)_SFD_INTEGER_CHECK(
        "j", c12_j), 1, 3, 1, 0) + 3 * (_SFD_EML_ARRAY_BOUNDS_CHECK("MAS",
        (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 3, 2, 0) - 1)) - 1];
      c12_b_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 1, 0);
    c12_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, -41);
  _SFD_SYMBOL_SCOPE_POP();
  for (c12_i15 = 0; c12_i15 < 9; c12_i15++) {
    (*c12_b_M)[c12_i15] = c12_M[c12_i15];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c12_sfEvent);
}

static void initSimStructsc12_m3dof_library(SFc12_m3dof_libraryInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber, uint32_T c12_instanceNumber)
{
  (void)c12_machineNumber;
  (void)c12_chartNumber;
  (void)c12_instanceNumber;
}

static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i16;
  int32_T c12_i17;
  int32_T c12_i18;
  real_T c12_b_inData[9];
  int32_T c12_i19;
  int32_T c12_i20;
  int32_T c12_i21;
  real_T c12_u[9];
  const mxArray *c12_y = NULL;
  SFc12_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc12_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_i16 = 0;
  for (c12_i17 = 0; c12_i17 < 3; c12_i17++) {
    for (c12_i18 = 0; c12_i18 < 3; c12_i18++) {
      c12_b_inData[c12_i18 + c12_i16] = (*(real_T (*)[9])c12_inData)[c12_i18 +
        c12_i16];
    }

    c12_i16 += 3;
  }

  c12_i19 = 0;
  for (c12_i20 = 0; c12_i20 < 3; c12_i20++) {
    for (c12_i21 = 0; c12_i21 < 3; c12_i21++) {
      c12_u[c12_i21 + c12_i19] = c12_b_inData[c12_i21 + c12_i19];
    }

    c12_i19 += 3;
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, false);
  return c12_mxArrayOutData;
}

static void c12_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_M, const char_T *c12_identifier, real_T
  c12_y[9])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_M), &c12_thisId, c12_y);
  sf_mex_destroy(&c12_M);
}

static void c12_b_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[9])
{
  real_T c12_dv1[9];
  int32_T c12_i22;
  (void)chartInstance;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_dv1, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c12_i22 = 0; c12_i22 < 9; c12_i22++) {
    c12_y[c12_i22] = c12_dv1[c12_i22];
  }

  sf_mex_destroy(&c12_u);
}

static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_M;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y[9];
  int32_T c12_i23;
  int32_T c12_i24;
  int32_T c12_i25;
  SFc12_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc12_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c12_M = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_M), &c12_thisId, c12_y);
  sf_mex_destroy(&c12_M);
  c12_i23 = 0;
  for (c12_i24 = 0; c12_i24 < 3; c12_i24++) {
    for (c12_i25 = 0; c12_i25 < 3; c12_i25++) {
      (*(real_T (*)[9])c12_outData)[c12_i25 + c12_i23] = c12_y[c12_i25 + c12_i23];
    }

    c12_i23 += 3;
  }

  sf_mex_destroy(&c12_mxArrayInData);
}

static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i26;
  real_T c12_b_inData[3];
  int32_T c12_i27;
  real_T c12_u[3];
  const mxArray *c12_y = NULL;
  SFc12_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc12_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i26 = 0; c12_i26 < 3; c12_i26++) {
    c12_b_inData[c12_i26] = (*(real_T (*)[3])c12_inData)[c12_i26];
  }

  for (c12_i27 = 0; c12_i27 < 3; c12_i27++) {
    c12_u[c12_i27] = c12_b_inData[c12_i27];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, false);
  return c12_mxArrayOutData;
}

static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  real_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc12_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(real_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, false);
  return c12_mxArrayOutData;
}

static real_T c12_c_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  real_T c12_y;
  real_T c12_d0;
  (void)chartInstance;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_d0, 1, 0, 0U, 0, 0U, 0);
  c12_y = c12_d0;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_nargout;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y;
  SFc12_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc12_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c12_nargout = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_nargout),
    &c12_thisId);
  sf_mex_destroy(&c12_nargout);
  *(real_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

const mxArray *sf_c12_m3dof_library_get_eml_resolved_functions_info(void)
{
  const mxArray *c12_nameCaptureInfo = NULL;
  c12_nameCaptureInfo = NULL;
  sf_mex_assign(&c12_nameCaptureInfo, sf_mex_createstruct("structure", 2, 17, 1),
                false);
  c12_info_helper(&c12_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c12_nameCaptureInfo);
  return c12_nameCaptureInfo;
}

static void c12_info_helper(const mxArray **c12_info)
{
  const mxArray *c12_rhs0 = NULL;
  const mxArray *c12_lhs0 = NULL;
  const mxArray *c12_rhs1 = NULL;
  const mxArray *c12_lhs1 = NULL;
  const mxArray *c12_rhs2 = NULL;
  const mxArray *c12_lhs2 = NULL;
  const mxArray *c12_rhs3 = NULL;
  const mxArray *c12_lhs3 = NULL;
  const mxArray *c12_rhs4 = NULL;
  const mxArray *c12_lhs4 = NULL;
  const mxArray *c12_rhs5 = NULL;
  const mxArray *c12_lhs5 = NULL;
  const mxArray *c12_rhs6 = NULL;
  const mxArray *c12_lhs6 = NULL;
  const mxArray *c12_rhs7 = NULL;
  const mxArray *c12_lhs7 = NULL;
  const mxArray *c12_rhs8 = NULL;
  const mxArray *c12_lhs8 = NULL;
  const mxArray *c12_rhs9 = NULL;
  const mxArray *c12_lhs9 = NULL;
  const mxArray *c12_rhs10 = NULL;
  const mxArray *c12_lhs10 = NULL;
  const mxArray *c12_rhs11 = NULL;
  const mxArray *c12_lhs11 = NULL;
  const mxArray *c12_rhs12 = NULL;
  const mxArray *c12_lhs12 = NULL;
  const mxArray *c12_rhs13 = NULL;
  const mxArray *c12_lhs13 = NULL;
  const mxArray *c12_rhs14 = NULL;
  const mxArray *c12_lhs14 = NULL;
  const mxArray *c12_rhs15 = NULL;
  const mxArray *c12_lhs15 = NULL;
  const mxArray *c12_rhs16 = NULL;
  const mxArray *c12_lhs16 = NULL;
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("mpower"), "name", "name", 0);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1363713878U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c12_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c12_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("ismatrix"), "name", "name",
                  2);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1331304858U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c12_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("power"), "name", "name", 3);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c12_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs3), "lhs", "lhs",
                  3);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 4);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c12_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs4), "rhs", "rhs",
                  4);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs4), "lhs", "lhs",
                  4);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 5);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 5);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c12_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs5), "rhs", "rhs",
                  5);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs5), "lhs", "lhs",
                  5);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 6);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c12_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs6), "rhs", "rhs",
                  6);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs6), "lhs", "lhs",
                  6);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 7);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 7);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c12_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs7), "rhs", "rhs",
                  7);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs7), "lhs", "lhs",
                  7);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 8);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 8);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c12_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs8), "rhs", "rhs",
                  8);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs8), "lhs", "lhs",
                  8);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 9);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("floor"), "name", "name", 9);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c12_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs9), "rhs", "rhs",
                  9);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs9), "lhs", "lhs",
                  9);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 10);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c12_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 11);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c12_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 12);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 12);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c12_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(""), "context", "context", 13);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("cos"), "name", "name", 13);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c12_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("eml_scalar_cos"), "name",
                  "name", 14);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1286818722U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c12_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(""), "context", "context", 15);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("sin"), "name", "name", 15);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 15);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c12_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 16);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 16);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c12_info, c12_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(1286818736U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c12_info, c12_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c12_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c12_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c12_info, sf_mex_duplicatearraysafe(&c12_lhs16), "lhs", "lhs",
                  16);
  sf_mex_destroy(&c12_rhs0);
  sf_mex_destroy(&c12_lhs0);
  sf_mex_destroy(&c12_rhs1);
  sf_mex_destroy(&c12_lhs1);
  sf_mex_destroy(&c12_rhs2);
  sf_mex_destroy(&c12_lhs2);
  sf_mex_destroy(&c12_rhs3);
  sf_mex_destroy(&c12_lhs3);
  sf_mex_destroy(&c12_rhs4);
  sf_mex_destroy(&c12_lhs4);
  sf_mex_destroy(&c12_rhs5);
  sf_mex_destroy(&c12_lhs5);
  sf_mex_destroy(&c12_rhs6);
  sf_mex_destroy(&c12_lhs6);
  sf_mex_destroy(&c12_rhs7);
  sf_mex_destroy(&c12_lhs7);
  sf_mex_destroy(&c12_rhs8);
  sf_mex_destroy(&c12_lhs8);
  sf_mex_destroy(&c12_rhs9);
  sf_mex_destroy(&c12_lhs9);
  sf_mex_destroy(&c12_rhs10);
  sf_mex_destroy(&c12_lhs10);
  sf_mex_destroy(&c12_rhs11);
  sf_mex_destroy(&c12_lhs11);
  sf_mex_destroy(&c12_rhs12);
  sf_mex_destroy(&c12_lhs12);
  sf_mex_destroy(&c12_rhs13);
  sf_mex_destroy(&c12_lhs13);
  sf_mex_destroy(&c12_rhs14);
  sf_mex_destroy(&c12_lhs14);
  sf_mex_destroy(&c12_rhs15);
  sf_mex_destroy(&c12_lhs15);
  sf_mex_destroy(&c12_rhs16);
  sf_mex_destroy(&c12_lhs16);
}

static const mxArray *c12_emlrt_marshallOut(const char * c12_u)
{
  const mxArray *c12_y = NULL;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c12_u)), false);
  return c12_y;
}

static const mxArray *c12_b_emlrt_marshallOut(const uint32_T c12_u)
{
  const mxArray *c12_y = NULL;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 7, 0U, 0U, 0U, 0), false);
  return c12_y;
}

static real_T c12_mpower(SFc12_m3dof_libraryInstanceStruct *chartInstance,
  real_T c12_a)
{
  real_T c12_b_a;
  real_T c12_c_a;
  real_T c12_ak;
  real_T c12_d_a;
  c12_b_a = c12_a;
  c12_c_a = c12_b_a;
  c12_eml_scalar_eg(chartInstance);
  c12_ak = c12_c_a;
  c12_d_a = c12_ak;
  c12_eml_scalar_eg(chartInstance);
  return c12_d_a * c12_d_a;
}

static void c12_eml_scalar_eg(SFc12_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc12_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(int32_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, false);
  return c12_mxArrayOutData;
}

static int32_T c12_d_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  int32_T c12_y;
  int32_T c12_i28;
  (void)chartInstance;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_i28, 1, 6, 0U, 0, 0U, 0);
  c12_y = c12_i28;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_b_sfEvent;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  int32_T c12_y;
  SFc12_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc12_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c12_b_sfEvent = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_b_sfEvent),
    &c12_thisId);
  sf_mex_destroy(&c12_b_sfEvent);
  *(int32_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

static uint8_T c12_e_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_b_is_active_c12_m3dof_library, const char_T
  *c12_identifier)
{
  uint8_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c12_b_is_active_c12_m3dof_library), &c12_thisId);
  sf_mex_destroy(&c12_b_is_active_c12_m3dof_library);
  return c12_y;
}

static uint8_T c12_f_emlrt_marshallIn(SFc12_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint8_T c12_y;
  uint8_T c12_u0;
  (void)chartInstance;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u0, 1, 3, 0U, 0, 0U, 0);
  c12_y = c12_u0;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void init_dsm_address_info(SFc12_m3dof_libraryInstanceStruct
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

void sf_c12_m3dof_library_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4119877414U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3365625637U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2099294122U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2929124903U);
}

mxArray *sf_c12_m3dof_library_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("v5PKewA288wkSV6ZELLHzC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

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

mxArray *sf_c12_m3dof_library_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c12_m3dof_library_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c12_m3dof_library(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"M\",},{M[8],M[0],T\"is_active_c12_m3dof_library\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c12_m3dof_library_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc12_m3dof_libraryInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc12_m3dof_libraryInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _m3dof_libraryMachineNumber_,
           12,
           1,
           1,
           0,
           6,
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
          _SFD_SET_DATA_PROPS(1,1,1,0,"xi1");
          _SFD_SET_DATA_PROPS(2,2,0,1,"M");
          _SFD_SET_DATA_PROPS(3,1,1,0,"xi2");
          _SFD_SET_DATA_PROPS(4,1,1,0,"xi3");
          _SFD_SET_DATA_PROPS(5,1,1,0,"a");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,899);
        _SFD_CV_INIT_EML_FOR(0,1,0,828,840,894);
        _SFD_CV_INIT_EML_FOR(0,1,1,844,856,890);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)
            c12_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c12_q)[3];
          real_T (*c12_xi1)[3];
          real_T (*c12_M)[9];
          real_T (*c12_xi2)[3];
          real_T (*c12_xi3)[3];
          real_T (*c12_a)[3];
          c12_a = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
          c12_xi3 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c12_xi2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c12_M = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
          c12_xi1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c12_q = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c12_q);
          _SFD_SET_DATA_VALUE_PTR(1U, *c12_xi1);
          _SFD_SET_DATA_VALUE_PTR(2U, *c12_M);
          _SFD_SET_DATA_VALUE_PTR(3U, *c12_xi2);
          _SFD_SET_DATA_VALUE_PTR(4U, *c12_xi3);
          _SFD_SET_DATA_VALUE_PTR(5U, *c12_a);
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
  return "ujnVDRbH8LlhOJD9n6ibWC";
}

static void sf_opaque_initialize_c12_m3dof_library(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc12_m3dof_libraryInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c12_m3dof_library((SFc12_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
  initialize_c12_m3dof_library((SFc12_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c12_m3dof_library(void *chartInstanceVar)
{
  enable_c12_m3dof_library((SFc12_m3dof_libraryInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c12_m3dof_library(void *chartInstanceVar)
{
  disable_c12_m3dof_library((SFc12_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c12_m3dof_library(void *chartInstanceVar)
{
  sf_gateway_c12_m3dof_library((SFc12_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c12_m3dof_library(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c12_m3dof_library
    ((SFc12_m3dof_libraryInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c12_m3dof_library();/* state var info */
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

extern void sf_internal_set_sim_state_c12_m3dof_library(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c12_m3dof_library();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c12_m3dof_library((SFc12_m3dof_libraryInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c12_m3dof_library(SimStruct* S)
{
  return sf_internal_get_sim_state_c12_m3dof_library(S);
}

static void sf_opaque_set_sim_state_c12_m3dof_library(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c12_m3dof_library(S, st);
}

static void sf_opaque_terminate_c12_m3dof_library(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc12_m3dof_libraryInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_m3dof_library_optimization_info();
    }

    finalize_c12_m3dof_library((SFc12_m3dof_libraryInstanceStruct*)
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
  initSimStructsc12_m3dof_library((SFc12_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c12_m3dof_library(SimStruct *S)
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
    initialize_params_c12_m3dof_library((SFc12_m3dof_libraryInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c12_m3dof_library(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_m3dof_library_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      12);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,12,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,12,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,12);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,12,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,12,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,12);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2571988120U));
  ssSetChecksum1(S,(3058475102U));
  ssSetChecksum2(S,(4263362624U));
  ssSetChecksum3(S,(2421256955U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c12_m3dof_library(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c12_m3dof_library(SimStruct *S)
{
  SFc12_m3dof_libraryInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc12_m3dof_libraryInstanceStruct *)utMalloc(sizeof
    (SFc12_m3dof_libraryInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc12_m3dof_libraryInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c12_m3dof_library;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c12_m3dof_library;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c12_m3dof_library;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c12_m3dof_library;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c12_m3dof_library;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c12_m3dof_library;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c12_m3dof_library;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c12_m3dof_library;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c12_m3dof_library;
  chartInstance->chartInfo.mdlStart = mdlStart_c12_m3dof_library;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c12_m3dof_library;
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

void c12_m3dof_library_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c12_m3dof_library(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c12_m3dof_library(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c12_m3dof_library(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c12_m3dof_library_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
