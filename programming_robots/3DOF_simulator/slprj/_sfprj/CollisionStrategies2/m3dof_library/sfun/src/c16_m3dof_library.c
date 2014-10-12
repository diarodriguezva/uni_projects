/* Include files */

#include <stddef.h>
#include "blas.h"
#include "m3dof_library_sfun.h"
#include "c16_m3dof_library.h"
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
static const char * c16_debug_family_names[13] = { "c1", "s1", "c12", "s12",
  "c123", "s123", "nargin", "nargout", "q", "l1", "l2", "l3", "J" };

/* Function Declarations */
static void initialize_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance);
static void initialize_params_c16_m3dof_library
  (SFc16_m3dof_libraryInstanceStruct *chartInstance);
static void enable_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance);
static void disable_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance);
static void c16_update_debugger_state_c16_m3dof_library
  (SFc16_m3dof_libraryInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c16_m3dof_library
  (SFc16_m3dof_libraryInstanceStruct *chartInstance);
static void set_sim_state_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_st);
static void finalize_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance);
static void sf_gateway_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance);
static void initSimStructsc16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c16_machineNumber, uint32_T
  c16_chartNumber, uint32_T c16_instanceNumber);
static const mxArray *c16_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData);
static void c16_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_J, const char_T *c16_identifier, real_T
  c16_y[9]);
static void c16_b_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId,
  real_T c16_y[9]);
static void c16_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData);
static const mxArray *c16_b_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData);
static real_T c16_c_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId);
static void c16_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData);
static const mxArray *c16_c_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData);
static void c16_info_helper(const mxArray **c16_info);
static const mxArray *c16_emlrt_marshallOut(const char * c16_u);
static const mxArray *c16_b_emlrt_marshallOut(const uint32_T c16_u);
static const mxArray *c16_d_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData);
static int32_T c16_d_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId);
static void c16_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData);
static uint8_T c16_e_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_b_is_active_c16_m3dof_library, const char_T
  *c16_identifier);
static uint8_T c16_f_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId);
static void init_dsm_address_info(SFc16_m3dof_libraryInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance)
{
  chartInstance->c16_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c16_is_active_c16_m3dof_library = 0U;
}

static void initialize_params_c16_m3dof_library
  (SFc16_m3dof_libraryInstanceStruct *chartInstance)
{
  real_T c16_d0;
  real_T c16_d1;
  real_T c16_d2;
  sf_mex_import_named("l1", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c16_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c16_l1 = c16_d0;
  sf_mex_import_named("l2", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                      &c16_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c16_l2 = c16_d1;
  sf_mex_import_named("l3", sf_mex_get_sfun_param(chartInstance->S, 2, 0),
                      &c16_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c16_l3 = c16_d2;
}

static void enable_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c16_update_debugger_state_c16_m3dof_library
  (SFc16_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c16_m3dof_library
  (SFc16_m3dof_libraryInstanceStruct *chartInstance)
{
  const mxArray *c16_st;
  const mxArray *c16_y = NULL;
  int32_T c16_i0;
  real_T c16_u[9];
  const mxArray *c16_b_y = NULL;
  uint8_T c16_hoistedGlobal;
  uint8_T c16_b_u;
  const mxArray *c16_c_y = NULL;
  real_T (*c16_J)[9];
  c16_J = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c16_st = NULL;
  c16_st = NULL;
  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_createcellmatrix(2, 1), false);
  for (c16_i0 = 0; c16_i0 < 9; c16_i0++) {
    c16_u[c16_i0] = (*c16_J)[c16_i0];
  }

  c16_b_y = NULL;
  sf_mex_assign(&c16_b_y, sf_mex_create("y", c16_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_setcell(c16_y, 0, c16_b_y);
  c16_hoistedGlobal = chartInstance->c16_is_active_c16_m3dof_library;
  c16_b_u = c16_hoistedGlobal;
  c16_c_y = NULL;
  sf_mex_assign(&c16_c_y, sf_mex_create("y", &c16_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c16_y, 1, c16_c_y);
  sf_mex_assign(&c16_st, c16_y, false);
  return c16_st;
}

static void set_sim_state_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_st)
{
  const mxArray *c16_u;
  real_T c16_dv0[9];
  int32_T c16_i1;
  real_T (*c16_J)[9];
  c16_J = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c16_doneDoubleBufferReInit = true;
  c16_u = sf_mex_dup(c16_st);
  c16_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c16_u, 0)), "J",
                       c16_dv0);
  for (c16_i1 = 0; c16_i1 < 9; c16_i1++) {
    (*c16_J)[c16_i1] = c16_dv0[c16_i1];
  }

  chartInstance->c16_is_active_c16_m3dof_library = c16_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c16_u, 1)),
     "is_active_c16_m3dof_library");
  sf_mex_destroy(&c16_u);
  c16_update_debugger_state_c16_m3dof_library(chartInstance);
  sf_mex_destroy(&c16_st);
}

static void finalize_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance)
{
  int32_T c16_i2;
  real_T c16_hoistedGlobal;
  real_T c16_b_hoistedGlobal;
  real_T c16_c_hoistedGlobal;
  int32_T c16_i3;
  real_T c16_q[3];
  real_T c16_b_l1;
  real_T c16_b_l2;
  real_T c16_b_l3;
  uint32_T c16_debug_family_var_map[13];
  real_T c16_c1;
  real_T c16_s1;
  real_T c16_c12;
  real_T c16_s12;
  real_T c16_c123;
  real_T c16_s123;
  real_T c16_nargin = 4.0;
  real_T c16_nargout = 1.0;
  real_T c16_J[9];
  int32_T c16_i4;
  real_T c16_x;
  real_T c16_b_x;
  real_T c16_c_x;
  real_T c16_d_x;
  real_T c16_e_x;
  real_T c16_f_x;
  real_T c16_g_x;
  real_T c16_h_x;
  real_T c16_i_x;
  real_T c16_j_x;
  real_T c16_k_x;
  real_T c16_l_x;
  int32_T c16_i5;
  int32_T c16_i6;
  real_T (*c16_b_J)[9];
  real_T (*c16_b_q)[3];
  c16_b_J = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c16_b_q = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c16_sfEvent);
  for (c16_i2 = 0; c16_i2 < 3; c16_i2++) {
    _SFD_DATA_RANGE_CHECK((*c16_b_q)[c16_i2], 0U);
  }

  chartInstance->c16_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c16_sfEvent);
  c16_hoistedGlobal = chartInstance->c16_l1;
  c16_b_hoistedGlobal = chartInstance->c16_l2;
  c16_c_hoistedGlobal = chartInstance->c16_l3;
  for (c16_i3 = 0; c16_i3 < 3; c16_i3++) {
    c16_q[c16_i3] = (*c16_b_q)[c16_i3];
  }

  c16_b_l1 = c16_hoistedGlobal;
  c16_b_l2 = c16_b_hoistedGlobal;
  c16_b_l3 = c16_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c16_debug_family_names,
    c16_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_c1, 0U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_s1, 1U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_c12, 2U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_s12, 3U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_c123, 4U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_s123, 5U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_nargin, 6U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_nargout, 7U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c16_q, 8U, c16_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_b_l1, 9U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_b_l2, 10U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c16_b_l3, 11U, c16_b_sf_marshallOut,
    c16_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c16_J, 12U, c16_sf_marshallOut,
    c16_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 3);
  for (c16_i4 = 0; c16_i4 < 9; c16_i4++) {
    c16_J[c16_i4] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 6);
  c16_x = c16_q[0];
  c16_c1 = c16_x;
  c16_b_x = c16_c1;
  c16_c1 = c16_b_x;
  c16_c1 = muDoubleScalarCos(c16_c1);
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 7);
  c16_c_x = c16_q[0];
  c16_s1 = c16_c_x;
  c16_d_x = c16_s1;
  c16_s1 = c16_d_x;
  c16_s1 = muDoubleScalarSin(c16_s1);
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 8);
  c16_e_x = c16_q[0] + c16_q[1];
  c16_c12 = c16_e_x;
  c16_f_x = c16_c12;
  c16_c12 = c16_f_x;
  c16_c12 = muDoubleScalarCos(c16_c12);
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 9);
  c16_g_x = c16_q[0] + c16_q[1];
  c16_s12 = c16_g_x;
  c16_h_x = c16_s12;
  c16_s12 = c16_h_x;
  c16_s12 = muDoubleScalarSin(c16_s12);
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 10);
  c16_i_x = (c16_q[0] + c16_q[1]) + c16_q[2];
  c16_c123 = c16_i_x;
  c16_j_x = c16_c123;
  c16_c123 = c16_j_x;
  c16_c123 = muDoubleScalarCos(c16_c123);
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 11);
  c16_k_x = (c16_q[0] + c16_q[1]) + c16_q[2];
  c16_s123 = c16_k_x;
  c16_l_x = c16_s123;
  c16_s123 = c16_l_x;
  c16_s123 = muDoubleScalarSin(c16_s123);
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 14);
  c16_J[0] = (-c16_b_l1 * c16_s1 - c16_b_l2 * c16_s12) - c16_b_l3 * c16_s123;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 15);
  c16_J[3] = -c16_b_l2 * c16_s12 - c16_b_l3 * c16_s123;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 16);
  c16_J[6] = -c16_b_l3 * c16_s123;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 17);
  c16_J[1] = (c16_b_l1 * c16_c1 + c16_b_l2 * c16_c12) + c16_b_l3 * c16_c123;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 18);
  c16_J[4] = c16_b_l2 * c16_c12 + c16_b_l3 * c16_c123;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 19);
  c16_J[7] = c16_b_l3 * c16_c123;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 20);
  c16_J[2] = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 21);
  c16_J[5] = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, 22);
  c16_J[8] = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c16_sfEvent, -22);
  _SFD_SYMBOL_SCOPE_POP();
  for (c16_i5 = 0; c16_i5 < 9; c16_i5++) {
    (*c16_b_J)[c16_i5] = c16_J[c16_i5];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c16_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_m3dof_libraryMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c16_i6 = 0; c16_i6 < 9; c16_i6++) {
    _SFD_DATA_RANGE_CHECK((*c16_b_J)[c16_i6], 1U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c16_l1, 2U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c16_l2, 3U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c16_l3, 4U);
}

static void initSimStructsc16_m3dof_library(SFc16_m3dof_libraryInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c16_machineNumber, uint32_T
  c16_chartNumber, uint32_T c16_instanceNumber)
{
  (void)c16_machineNumber;
  (void)c16_chartNumber;
  (void)c16_instanceNumber;
}

static const mxArray *c16_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData)
{
  const mxArray *c16_mxArrayOutData = NULL;
  int32_T c16_i7;
  int32_T c16_i8;
  int32_T c16_i9;
  real_T c16_b_inData[9];
  int32_T c16_i10;
  int32_T c16_i11;
  int32_T c16_i12;
  real_T c16_u[9];
  const mxArray *c16_y = NULL;
  SFc16_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc16_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  c16_i7 = 0;
  for (c16_i8 = 0; c16_i8 < 3; c16_i8++) {
    for (c16_i9 = 0; c16_i9 < 3; c16_i9++) {
      c16_b_inData[c16_i9 + c16_i7] = (*(real_T (*)[9])c16_inData)[c16_i9 +
        c16_i7];
    }

    c16_i7 += 3;
  }

  c16_i10 = 0;
  for (c16_i11 = 0; c16_i11 < 3; c16_i11++) {
    for (c16_i12 = 0; c16_i12 < 3; c16_i12++) {
      c16_u[c16_i12 + c16_i10] = c16_b_inData[c16_i12 + c16_i10];
    }

    c16_i10 += 3;
  }

  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", c16_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, false);
  return c16_mxArrayOutData;
}

static void c16_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_J, const char_T *c16_identifier, real_T
  c16_y[9])
{
  emlrtMsgIdentifier c16_thisId;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_J), &c16_thisId, c16_y);
  sf_mex_destroy(&c16_J);
}

static void c16_b_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId,
  real_T c16_y[9])
{
  real_T c16_dv1[9];
  int32_T c16_i13;
  (void)chartInstance;
  sf_mex_import(c16_parentId, sf_mex_dup(c16_u), c16_dv1, 1, 0, 0U, 1, 0U, 2, 3,
                3);
  for (c16_i13 = 0; c16_i13 < 9; c16_i13++) {
    c16_y[c16_i13] = c16_dv1[c16_i13];
  }

  sf_mex_destroy(&c16_u);
}

static void c16_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData)
{
  const mxArray *c16_J;
  const char_T *c16_identifier;
  emlrtMsgIdentifier c16_thisId;
  real_T c16_y[9];
  int32_T c16_i14;
  int32_T c16_i15;
  int32_T c16_i16;
  SFc16_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc16_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c16_J = sf_mex_dup(c16_mxArrayInData);
  c16_identifier = c16_varName;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_J), &c16_thisId, c16_y);
  sf_mex_destroy(&c16_J);
  c16_i14 = 0;
  for (c16_i15 = 0; c16_i15 < 3; c16_i15++) {
    for (c16_i16 = 0; c16_i16 < 3; c16_i16++) {
      (*(real_T (*)[9])c16_outData)[c16_i16 + c16_i14] = c16_y[c16_i16 + c16_i14];
    }

    c16_i14 += 3;
  }

  sf_mex_destroy(&c16_mxArrayInData);
}

static const mxArray *c16_b_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData)
{
  const mxArray *c16_mxArrayOutData = NULL;
  real_T c16_u;
  const mxArray *c16_y = NULL;
  SFc16_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc16_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  c16_u = *(real_T *)c16_inData;
  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", &c16_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, false);
  return c16_mxArrayOutData;
}

static real_T c16_c_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId)
{
  real_T c16_y;
  real_T c16_d3;
  (void)chartInstance;
  sf_mex_import(c16_parentId, sf_mex_dup(c16_u), &c16_d3, 1, 0, 0U, 0, 0U, 0);
  c16_y = c16_d3;
  sf_mex_destroy(&c16_u);
  return c16_y;
}

static void c16_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData)
{
  const mxArray *c16_b_l3;
  const char_T *c16_identifier;
  emlrtMsgIdentifier c16_thisId;
  real_T c16_y;
  SFc16_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc16_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c16_b_l3 = sf_mex_dup(c16_mxArrayInData);
  c16_identifier = c16_varName;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_y = c16_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_b_l3),
    &c16_thisId);
  sf_mex_destroy(&c16_b_l3);
  *(real_T *)c16_outData = c16_y;
  sf_mex_destroy(&c16_mxArrayInData);
}

static const mxArray *c16_c_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData)
{
  const mxArray *c16_mxArrayOutData = NULL;
  int32_T c16_i17;
  real_T c16_b_inData[3];
  int32_T c16_i18;
  real_T c16_u[3];
  const mxArray *c16_y = NULL;
  SFc16_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc16_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  for (c16_i17 = 0; c16_i17 < 3; c16_i17++) {
    c16_b_inData[c16_i17] = (*(real_T (*)[3])c16_inData)[c16_i17];
  }

  for (c16_i18 = 0; c16_i18 < 3; c16_i18++) {
    c16_u[c16_i18] = c16_b_inData[c16_i18];
  }

  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", c16_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, false);
  return c16_mxArrayOutData;
}

const mxArray *sf_c16_m3dof_library_get_eml_resolved_functions_info(void)
{
  const mxArray *c16_nameCaptureInfo = NULL;
  c16_nameCaptureInfo = NULL;
  sf_mex_assign(&c16_nameCaptureInfo, sf_mex_createstruct("structure", 2, 4, 1),
                false);
  c16_info_helper(&c16_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c16_nameCaptureInfo);
  return c16_nameCaptureInfo;
}

static void c16_info_helper(const mxArray **c16_info)
{
  const mxArray *c16_rhs0 = NULL;
  const mxArray *c16_lhs0 = NULL;
  const mxArray *c16_rhs1 = NULL;
  const mxArray *c16_lhs1 = NULL;
  const mxArray *c16_rhs2 = NULL;
  const mxArray *c16_lhs2 = NULL;
  const mxArray *c16_rhs3 = NULL;
  const mxArray *c16_lhs3 = NULL;
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut("cos"), "name", "name", 0);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c16_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c16_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c16_info, sf_mex_duplicatearraysafe(&c16_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c16_info, sf_mex_duplicatearraysafe(&c16_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut("eml_scalar_cos"), "name",
                  "name", 1);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(1286818722U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c16_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c16_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c16_info, sf_mex_duplicatearraysafe(&c16_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c16_info, sf_mex_duplicatearraysafe(&c16_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut("sin"), "name", "name", 2);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c16_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c16_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c16_info, sf_mex_duplicatearraysafe(&c16_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c16_info, sf_mex_duplicatearraysafe(&c16_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 3);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c16_info, c16_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(1286818736U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c16_info, c16_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c16_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c16_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c16_info, sf_mex_duplicatearraysafe(&c16_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c16_info, sf_mex_duplicatearraysafe(&c16_lhs3), "lhs", "lhs",
                  3);
  sf_mex_destroy(&c16_rhs0);
  sf_mex_destroy(&c16_lhs0);
  sf_mex_destroy(&c16_rhs1);
  sf_mex_destroy(&c16_lhs1);
  sf_mex_destroy(&c16_rhs2);
  sf_mex_destroy(&c16_lhs2);
  sf_mex_destroy(&c16_rhs3);
  sf_mex_destroy(&c16_lhs3);
}

static const mxArray *c16_emlrt_marshallOut(const char * c16_u)
{
  const mxArray *c16_y = NULL;
  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", c16_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c16_u)), false);
  return c16_y;
}

static const mxArray *c16_b_emlrt_marshallOut(const uint32_T c16_u)
{
  const mxArray *c16_y = NULL;
  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", &c16_u, 7, 0U, 0U, 0U, 0), false);
  return c16_y;
}

static const mxArray *c16_d_sf_marshallOut(void *chartInstanceVoid, void
  *c16_inData)
{
  const mxArray *c16_mxArrayOutData = NULL;
  int32_T c16_u;
  const mxArray *c16_y = NULL;
  SFc16_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc16_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c16_mxArrayOutData = NULL;
  c16_u = *(int32_T *)c16_inData;
  c16_y = NULL;
  sf_mex_assign(&c16_y, sf_mex_create("y", &c16_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c16_mxArrayOutData, c16_y, false);
  return c16_mxArrayOutData;
}

static int32_T c16_d_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId)
{
  int32_T c16_y;
  int32_T c16_i19;
  (void)chartInstance;
  sf_mex_import(c16_parentId, sf_mex_dup(c16_u), &c16_i19, 1, 6, 0U, 0, 0U, 0);
  c16_y = c16_i19;
  sf_mex_destroy(&c16_u);
  return c16_y;
}

static void c16_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c16_mxArrayInData, const char_T *c16_varName, void *c16_outData)
{
  const mxArray *c16_b_sfEvent;
  const char_T *c16_identifier;
  emlrtMsgIdentifier c16_thisId;
  int32_T c16_y;
  SFc16_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc16_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c16_b_sfEvent = sf_mex_dup(c16_mxArrayInData);
  c16_identifier = c16_varName;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_y = c16_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c16_b_sfEvent),
    &c16_thisId);
  sf_mex_destroy(&c16_b_sfEvent);
  *(int32_T *)c16_outData = c16_y;
  sf_mex_destroy(&c16_mxArrayInData);
}

static uint8_T c16_e_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_b_is_active_c16_m3dof_library, const char_T
  *c16_identifier)
{
  uint8_T c16_y;
  emlrtMsgIdentifier c16_thisId;
  c16_thisId.fIdentifier = c16_identifier;
  c16_thisId.fParent = NULL;
  c16_y = c16_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c16_b_is_active_c16_m3dof_library), &c16_thisId);
  sf_mex_destroy(&c16_b_is_active_c16_m3dof_library);
  return c16_y;
}

static uint8_T c16_f_emlrt_marshallIn(SFc16_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c16_u, const emlrtMsgIdentifier *c16_parentId)
{
  uint8_T c16_y;
  uint8_T c16_u0;
  (void)chartInstance;
  sf_mex_import(c16_parentId, sf_mex_dup(c16_u), &c16_u0, 1, 3, 0U, 0, 0U, 0);
  c16_y = c16_u0;
  sf_mex_destroy(&c16_u);
  return c16_y;
}

static void init_dsm_address_info(SFc16_m3dof_libraryInstanceStruct
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

void sf_c16_m3dof_library_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3368457047U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3358450999U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3250326069U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(545693553U);
}

mxArray *sf_c16_m3dof_library_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("tcQ6qe435gckvJ3jaGWykC");
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

mxArray *sf_c16_m3dof_library_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c16_m3dof_library_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c16_m3dof_library(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"J\",},{M[8],M[0],T\"is_active_c16_m3dof_library\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c16_m3dof_library_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc16_m3dof_libraryInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc16_m3dof_libraryInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _m3dof_libraryMachineNumber_,
           16,
           1,
           1,
           0,
           5,
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
          _SFD_SET_DATA_PROPS(1,2,0,1,"J");
          _SFD_SET_DATA_PROPS(2,10,0,0,"l1");
          _SFD_SET_DATA_PROPS(3,10,0,0,"l2");
          _SFD_SET_DATA_PROPS(4,10,0,0,"l3");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,450);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c16_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c16_sf_marshallOut,(MexInFcnForType)
            c16_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c16_b_sf_marshallOut,(MexInFcnForType)
          c16_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c16_b_sf_marshallOut,(MexInFcnForType)
          c16_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c16_b_sf_marshallOut,(MexInFcnForType)
          c16_b_sf_marshallIn);

        {
          real_T (*c16_q)[3];
          real_T (*c16_J)[9];
          c16_J = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
          c16_q = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c16_q);
          _SFD_SET_DATA_VALUE_PTR(1U, *c16_J);
          _SFD_SET_DATA_VALUE_PTR(2U, &chartInstance->c16_l1);
          _SFD_SET_DATA_VALUE_PTR(3U, &chartInstance->c16_l2);
          _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance->c16_l3);
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
  return "3fZKU2ENAlIr5JGvDet9QC";
}

static void sf_opaque_initialize_c16_m3dof_library(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc16_m3dof_libraryInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c16_m3dof_library((SFc16_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
  initialize_c16_m3dof_library((SFc16_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c16_m3dof_library(void *chartInstanceVar)
{
  enable_c16_m3dof_library((SFc16_m3dof_libraryInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c16_m3dof_library(void *chartInstanceVar)
{
  disable_c16_m3dof_library((SFc16_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c16_m3dof_library(void *chartInstanceVar)
{
  sf_gateway_c16_m3dof_library((SFc16_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c16_m3dof_library(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c16_m3dof_library
    ((SFc16_m3dof_libraryInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c16_m3dof_library();/* state var info */
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

extern void sf_internal_set_sim_state_c16_m3dof_library(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c16_m3dof_library();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c16_m3dof_library((SFc16_m3dof_libraryInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c16_m3dof_library(SimStruct* S)
{
  return sf_internal_get_sim_state_c16_m3dof_library(S);
}

static void sf_opaque_set_sim_state_c16_m3dof_library(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c16_m3dof_library(S, st);
}

static void sf_opaque_terminate_c16_m3dof_library(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc16_m3dof_libraryInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_m3dof_library_optimization_info();
    }

    finalize_c16_m3dof_library((SFc16_m3dof_libraryInstanceStruct*)
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
  initSimStructsc16_m3dof_library((SFc16_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c16_m3dof_library(SimStruct *S)
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
    initialize_params_c16_m3dof_library((SFc16_m3dof_libraryInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c16_m3dof_library(SimStruct *S)
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
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      16);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,16,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,16,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,16);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,16,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,16,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,16);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3155668433U));
  ssSetChecksum1(S,(227410259U));
  ssSetChecksum2(S,(603924017U));
  ssSetChecksum3(S,(677714762U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c16_m3dof_library(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c16_m3dof_library(SimStruct *S)
{
  SFc16_m3dof_libraryInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc16_m3dof_libraryInstanceStruct *)utMalloc(sizeof
    (SFc16_m3dof_libraryInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc16_m3dof_libraryInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c16_m3dof_library;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c16_m3dof_library;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c16_m3dof_library;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c16_m3dof_library;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c16_m3dof_library;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c16_m3dof_library;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c16_m3dof_library;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c16_m3dof_library;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c16_m3dof_library;
  chartInstance->chartInfo.mdlStart = mdlStart_c16_m3dof_library;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c16_m3dof_library;
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

void c16_m3dof_library_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c16_m3dof_library(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c16_m3dof_library(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c16_m3dof_library(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c16_m3dof_library_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
