/* Include files */

#include <stddef.h>
#include "blas.h"
#include "m3dof_library_sfun.h"
#include "c11_m3dof_library.h"
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
static const char * c11_debug_family_names[57] = { "g0", "t1", "t2", "t4", "t5",
  "t6", "t7", "t8", "t9", "t10", "t11", "t12", "t13", "t14", "t15", "t16", "t19",
  "t22", "t23", "t24", "t25", "t26", "t27", "t28", "t29", "t30", "t31", "t32",
  "t33", "t34", "t35", "t37", "t38", "t39", "t40", "t42", "t43", "t44", "t45",
  "t46", "t47", "t48", "t49", "t50", "t51", "t53", "t54", "t57", "nargin",
  "nargout", "q", "xi1", "xi2", "xi3", "a", "eg", "g" };

/* Function Declarations */
static void initialize_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance);
static void initialize_params_c11_m3dof_library
  (SFc11_m3dof_libraryInstanceStruct *chartInstance);
static void enable_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance);
static void disable_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance);
static void c11_update_debugger_state_c11_m3dof_library
  (SFc11_m3dof_libraryInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c11_m3dof_library
  (SFc11_m3dof_libraryInstanceStruct *chartInstance);
static void set_sim_state_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_st);
static void finalize_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance);
static void sf_gateway_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance);
static void c11_chartstep_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance);
static void initSimStructsc11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c11_machineNumber, uint32_T
  c11_chartNumber, uint32_T c11_instanceNumber);
static const mxArray *c11_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static void c11_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_g, const char_T *c11_identifier, real_T
  c11_y[3]);
static void c11_b_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId,
  real_T c11_y[3]);
static void c11_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static const mxArray *c11_b_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static real_T c11_c_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void c11_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static void c11_info_helper(const mxArray **c11_info);
static const mxArray *c11_emlrt_marshallOut(const char * c11_u);
static const mxArray *c11_b_emlrt_marshallOut(const uint32_T c11_u);
static const mxArray *c11_c_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static int32_T c11_d_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void c11_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static uint8_T c11_e_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_b_is_active_c11_m3dof_library, const char_T
  *c11_identifier);
static uint8_T c11_f_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void init_dsm_address_info(SFc11_m3dof_libraryInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance)
{
  chartInstance->c11_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c11_is_active_c11_m3dof_library = 0U;
}

static void initialize_params_c11_m3dof_library
  (SFc11_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c11_update_debugger_state_c11_m3dof_library
  (SFc11_m3dof_libraryInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c11_m3dof_library
  (SFc11_m3dof_libraryInstanceStruct *chartInstance)
{
  const mxArray *c11_st;
  const mxArray *c11_y = NULL;
  int32_T c11_i0;
  real_T c11_u[3];
  const mxArray *c11_b_y = NULL;
  uint8_T c11_hoistedGlobal;
  uint8_T c11_b_u;
  const mxArray *c11_c_y = NULL;
  real_T (*c11_g)[3];
  c11_g = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c11_st = NULL;
  c11_st = NULL;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_createcellmatrix(2, 1), false);
  for (c11_i0 = 0; c11_i0 < 3; c11_i0++) {
    c11_u[c11_i0] = (*c11_g)[c11_i0];
  }

  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", c11_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c11_y, 0, c11_b_y);
  c11_hoistedGlobal = chartInstance->c11_is_active_c11_m3dof_library;
  c11_b_u = c11_hoistedGlobal;
  c11_c_y = NULL;
  sf_mex_assign(&c11_c_y, sf_mex_create("y", &c11_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 1, c11_c_y);
  sf_mex_assign(&c11_st, c11_y, false);
  return c11_st;
}

static void set_sim_state_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_st)
{
  const mxArray *c11_u;
  real_T c11_dv0[3];
  int32_T c11_i1;
  real_T (*c11_g)[3];
  c11_g = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c11_doneDoubleBufferReInit = true;
  c11_u = sf_mex_dup(c11_st);
  c11_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c11_u, 0)), "g",
                       c11_dv0);
  for (c11_i1 = 0; c11_i1 < 3; c11_i1++) {
    (*c11_g)[c11_i1] = c11_dv0[c11_i1];
  }

  chartInstance->c11_is_active_c11_m3dof_library = c11_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c11_u, 1)),
     "is_active_c11_m3dof_library");
  sf_mex_destroy(&c11_u);
  c11_update_debugger_state_c11_m3dof_library(chartInstance);
  sf_mex_destroy(&c11_st);
}

static void finalize_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance)
{
  int32_T c11_i2;
  int32_T c11_i3;
  int32_T c11_i4;
  int32_T c11_i5;
  int32_T c11_i6;
  int32_T c11_i7;
  int32_T c11_i8;
  real_T (*c11_eg)[3];
  real_T (*c11_a)[3];
  real_T (*c11_xi3)[3];
  real_T (*c11_xi2)[3];
  real_T (*c11_g)[3];
  real_T (*c11_xi1)[3];
  real_T (*c11_q)[3];
  c11_eg = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
  c11_a = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c11_xi3 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c11_xi2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c11_g = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c11_xi1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c11_q = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c11_sfEvent);
  for (c11_i2 = 0; c11_i2 < 3; c11_i2++) {
    _SFD_DATA_RANGE_CHECK((*c11_q)[c11_i2], 0U);
  }

  for (c11_i3 = 0; c11_i3 < 3; c11_i3++) {
    _SFD_DATA_RANGE_CHECK((*c11_xi1)[c11_i3], 1U);
  }

  chartInstance->c11_sfEvent = CALL_EVENT;
  c11_chartstep_c11_m3dof_library(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_m3dof_libraryMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c11_i4 = 0; c11_i4 < 3; c11_i4++) {
    _SFD_DATA_RANGE_CHECK((*c11_g)[c11_i4], 2U);
  }

  for (c11_i5 = 0; c11_i5 < 3; c11_i5++) {
    _SFD_DATA_RANGE_CHECK((*c11_xi2)[c11_i5], 3U);
  }

  for (c11_i6 = 0; c11_i6 < 3; c11_i6++) {
    _SFD_DATA_RANGE_CHECK((*c11_xi3)[c11_i6], 4U);
  }

  for (c11_i7 = 0; c11_i7 < 3; c11_i7++) {
    _SFD_DATA_RANGE_CHECK((*c11_a)[c11_i7], 5U);
  }

  for (c11_i8 = 0; c11_i8 < 3; c11_i8++) {
    _SFD_DATA_RANGE_CHECK((*c11_eg)[c11_i8], 6U);
  }
}

static void c11_chartstep_c11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance)
{
  int32_T c11_i9;
  real_T c11_q[3];
  int32_T c11_i10;
  real_T c11_xi1[3];
  int32_T c11_i11;
  real_T c11_xi2[3];
  int32_T c11_i12;
  real_T c11_xi3[3];
  int32_T c11_i13;
  real_T c11_a[3];
  int32_T c11_i14;
  real_T c11_eg[3];
  uint32_T c11_debug_family_var_map[57];
  real_T c11_g0;
  real_T c11_t1;
  real_T c11_t2;
  real_T c11_t4;
  real_T c11_t5;
  real_T c11_t6;
  real_T c11_t7;
  real_T c11_t8;
  real_T c11_t9;
  real_T c11_t10;
  real_T c11_t11;
  real_T c11_t12;
  real_T c11_t13;
  real_T c11_t14;
  real_T c11_t15;
  real_T c11_t16;
  real_T c11_t19;
  real_T c11_t22;
  real_T c11_t23;
  real_T c11_t24;
  real_T c11_t25;
  real_T c11_t26;
  real_T c11_t27;
  real_T c11_t28;
  real_T c11_t29;
  real_T c11_t30;
  real_T c11_t31;
  real_T c11_t32;
  real_T c11_t33;
  real_T c11_t34;
  real_T c11_t35;
  real_T c11_t37;
  real_T c11_t38;
  real_T c11_t39;
  real_T c11_t40;
  real_T c11_t42;
  real_T c11_t43;
  real_T c11_t44;
  real_T c11_t45;
  real_T c11_t46;
  real_T c11_t47;
  real_T c11_t48;
  real_T c11_t49;
  real_T c11_t50;
  real_T c11_t51;
  real_T c11_t53;
  real_T c11_t54;
  real_T c11_t57;
  real_T c11_nargin = 6.0;
  real_T c11_nargout = 1.0;
  real_T c11_g[3];
  int32_T c11_i15;
  real_T c11_x;
  real_T c11_b_x;
  real_T c11_c_x;
  real_T c11_d_x;
  real_T c11_e_x;
  real_T c11_f_x;
  real_T c11_g_x;
  real_T c11_h_x;
  real_T c11_i_x;
  real_T c11_j_x;
  real_T c11_k_x;
  real_T c11_l_x;
  int32_T c11_i16;
  real_T (*c11_b_g)[3];
  real_T (*c11_b_eg)[3];
  real_T (*c11_b_a)[3];
  real_T (*c11_b_xi3)[3];
  real_T (*c11_b_xi2)[3];
  real_T (*c11_b_xi1)[3];
  real_T (*c11_b_q)[3];
  c11_b_eg = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
  c11_b_a = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
  c11_b_xi3 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c11_b_xi2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
  c11_b_g = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c11_b_xi1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c11_b_q = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c11_sfEvent);
  for (c11_i9 = 0; c11_i9 < 3; c11_i9++) {
    c11_q[c11_i9] = (*c11_b_q)[c11_i9];
  }

  for (c11_i10 = 0; c11_i10 < 3; c11_i10++) {
    c11_xi1[c11_i10] = (*c11_b_xi1)[c11_i10];
  }

  for (c11_i11 = 0; c11_i11 < 3; c11_i11++) {
    c11_xi2[c11_i11] = (*c11_b_xi2)[c11_i11];
  }

  for (c11_i12 = 0; c11_i12 < 3; c11_i12++) {
    c11_xi3[c11_i12] = (*c11_b_xi3)[c11_i12];
  }

  for (c11_i13 = 0; c11_i13 < 3; c11_i13++) {
    c11_a[c11_i13] = (*c11_b_a)[c11_i13];
  }

  for (c11_i14 = 0; c11_i14 < 3; c11_i14++) {
    c11_eg[c11_i14] = (*c11_b_eg)[c11_i14];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 57U, 57U, c11_debug_family_names,
    c11_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c11_g0, 0U, c11_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t1, 1U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t2, 2U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t4, 3U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t5, 4U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t6, 5U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t7, 6U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t8, 7U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t9, 8U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t10, 9U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t11, 10U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t12, 11U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t13, 12U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t14, 13U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t15, 14U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t16, 15U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t19, 16U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t22, 17U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t23, 18U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t24, 19U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t25, 20U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t26, 21U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t27, 22U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t28, 23U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t29, 24U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t30, 25U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t31, 26U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t32, 27U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t33, 28U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t34, 29U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t35, 30U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t37, 31U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t38, 32U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t39, 33U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t40, 34U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t42, 35U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t43, 36U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t44, 37U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t45, 38U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t46, 39U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t47, 40U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t48, 41U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t49, 42U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t50, 43U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t51, 44U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t53, 45U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t54, 46U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_t57, 47U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_nargin, 48U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_nargout, 49U, c11_b_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c11_q, 50U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c11_xi1, 51U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c11_xi2, 52U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c11_xi3, 53U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c11_a, 54U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c11_eg, 55U, c11_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c11_g, 56U, c11_sf_marshallOut,
    c11_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 21);
  for (c11_i15 = 0; c11_i15 < 3; c11_i15++) {
    c11_g[c11_i15] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 23);
  c11_g0 = -9.81;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 27);
  c11_x = c11_q[0];
  c11_t1 = c11_x;
  c11_b_x = c11_t1;
  c11_t1 = c11_b_x;
  c11_t1 = muDoubleScalarSin(c11_t1);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 28);
  c11_t2 = c11_eg[0] * c11_t1;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 29);
  c11_c_x = c11_q[0];
  c11_t4 = c11_c_x;
  c11_d_x = c11_t4;
  c11_t4 = c11_d_x;
  c11_t4 = muDoubleScalarCos(c11_t4);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 30);
  c11_t5 = c11_eg[0] * c11_t4;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 31);
  c11_e_x = c11_q[1];
  c11_t6 = c11_e_x;
  c11_f_x = c11_t6;
  c11_t6 = c11_f_x;
  c11_t6 = muDoubleScalarSin(c11_t6);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 32);
  c11_t7 = c11_t6 * c11_xi2[1];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 33);
  c11_t8 = c11_t5 * c11_t7;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 34);
  c11_g_x = c11_q[1];
  c11_t9 = c11_g_x;
  c11_h_x = c11_t9;
  c11_t9 = c11_h_x;
  c11_t9 = muDoubleScalarCos(c11_t9);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 35);
  c11_t10 = c11_t9 * c11_xi2[1];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 36);
  c11_t11 = c11_t2 * c11_t10;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 37);
  c11_t12 = c11_eg[1] * c11_t1;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 38);
  c11_t13 = c11_t12 * c11_t7;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 39);
  c11_t14 = c11_eg[1] * c11_t4;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 40);
  c11_t15 = c11_t14 * c11_t10;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 41);
  c11_t16 = c11_a[0] * c11_xi2[0];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 42);
  c11_t19 = c11_a[0] * c11_xi3[0];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 43);
  c11_i_x = c11_q[2];
  c11_t22 = c11_i_x;
  c11_j_x = c11_t22;
  c11_t22 = c11_j_x;
  c11_t22 = muDoubleScalarSin(c11_t22);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 44);
  c11_t23 = c11_eg[0] * c11_t22;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 45);
  c11_t24 = c11_t1 * c11_t6;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 46);
  c11_t25 = c11_t24 * c11_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 47);
  c11_t26 = c11_t23 * c11_t25;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 48);
  c11_k_x = c11_q[2];
  c11_t27 = c11_k_x;
  c11_l_x = c11_t27;
  c11_t27 = c11_l_x;
  c11_t27 = muDoubleScalarCos(c11_t27);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 49);
  c11_t28 = c11_eg[0] * c11_t27;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 50);
  c11_t29 = c11_t4 * c11_t6;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 51);
  c11_t30 = c11_t29 * c11_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 52);
  c11_t31 = c11_t28 * c11_t30;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 53);
  c11_t32 = (((((((((c11_t2 * c11_xi1[1] + c11_t8) + c11_t11) + c11_t13) -
                  c11_t15) - c11_t14 * c11_t16) + c11_t2 * c11_t16) - c11_t14 *
               c11_t19) + c11_t2 * c11_t19) - c11_t26) + c11_t31;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 54);
  c11_t33 = c11_t1 * c11_t9;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 55);
  c11_t34 = c11_t33 * c11_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 56);
  c11_t35 = c11_t28 * c11_t34;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 57);
  c11_t37 = c11_t9 * c11_a[1] * c11_xi3[0];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 58);
  c11_t38 = c11_t2 * c11_t37;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 59);
  c11_t39 = c11_eg[1] * c11_t22;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 60);
  c11_t40 = c11_t39 * c11_t30;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 61);
  c11_t42 = c11_t6 * c11_a[1] * c11_xi3[0];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 62);
  c11_t43 = c11_t12 * c11_t42;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 63);
  c11_t44 = c11_eg[1] * c11_t27;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 64);
  c11_t45 = c11_t4 * c11_t9;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 65);
  c11_t46 = c11_t45 * c11_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 66);
  c11_t47 = c11_t44 * c11_t46;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 67);
  c11_t48 = c11_t39 * c11_t34;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 68);
  c11_t49 = c11_t5 * c11_t42;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 69);
  c11_t50 = c11_t44 * c11_t25;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 70);
  c11_t51 = c11_t14 * c11_t37;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 71);
  c11_t53 = c11_t23 * c11_t46;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 72);
  c11_t54 = (((((((((c11_t35 + c11_t38) + c11_t40) + c11_t43) - c11_t47) +
                 c11_t48) + c11_t49) + c11_t50) - c11_t51) - c11_t14 * c11_xi1[1])
    + c11_t53;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 73);
  c11_t57 = ((((((((((((((c11_t53 - c11_t26) + c11_t50) + c11_t8) + c11_t13) +
                      c11_t35) + c11_t49) - c11_t15) + c11_t40) + c11_t48) +
                 c11_t11) - c11_t51) - c11_t47) + c11_t43) + c11_t38) + c11_t31;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 74);
  c11_g[0] = 9.81 * (c11_t32 + c11_t54);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 75);
  c11_g[1] = 9.81 * c11_t57;
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 76);
  c11_g[2] = 9.81 * (((((((c11_t28 * c11_t29 + c11_t28 * c11_t33) + c11_t23 *
    c11_t45) - c11_t23 * c11_t24) - c11_t44 * c11_t45) + c11_t44 * c11_t24) +
                      c11_t39 * c11_t29) + c11_t39 * c11_t33) * c11_xi3[1];
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, -76);
  _SFD_SYMBOL_SCOPE_POP();
  for (c11_i16 = 0; c11_i16 < 3; c11_i16++) {
    (*c11_b_g)[c11_i16] = c11_g[c11_i16];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c11_sfEvent);
}

static void initSimStructsc11_m3dof_library(SFc11_m3dof_libraryInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c11_machineNumber, uint32_T
  c11_chartNumber, uint32_T c11_instanceNumber)
{
  (void)c11_machineNumber;
  (void)c11_chartNumber;
  (void)c11_instanceNumber;
}

static const mxArray *c11_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  int32_T c11_i17;
  real_T c11_b_inData[3];
  int32_T c11_i18;
  real_T c11_u[3];
  const mxArray *c11_y = NULL;
  SFc11_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc11_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  for (c11_i17 = 0; c11_i17 < 3; c11_i17++) {
    c11_b_inData[c11_i17] = (*(real_T (*)[3])c11_inData)[c11_i17];
  }

  for (c11_i18 = 0; c11_i18 < 3; c11_i18++) {
    c11_u[c11_i18] = c11_b_inData[c11_i18];
  }

  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", c11_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, false);
  return c11_mxArrayOutData;
}

static void c11_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_g, const char_T *c11_identifier, real_T
  c11_y[3])
{
  emlrtMsgIdentifier c11_thisId;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_g), &c11_thisId, c11_y);
  sf_mex_destroy(&c11_g);
}

static void c11_b_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId,
  real_T c11_y[3])
{
  real_T c11_dv1[3];
  int32_T c11_i19;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), c11_dv1, 1, 0, 0U, 1, 0U, 1, 3);
  for (c11_i19 = 0; c11_i19 < 3; c11_i19++) {
    c11_y[c11_i19] = c11_dv1[c11_i19];
  }

  sf_mex_destroy(&c11_u);
}

static void c11_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_g;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  real_T c11_y[3];
  int32_T c11_i20;
  SFc11_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc11_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c11_g = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_g), &c11_thisId, c11_y);
  sf_mex_destroy(&c11_g);
  for (c11_i20 = 0; c11_i20 < 3; c11_i20++) {
    (*(real_T (*)[3])c11_outData)[c11_i20] = c11_y[c11_i20];
  }

  sf_mex_destroy(&c11_mxArrayInData);
}

static const mxArray *c11_b_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  real_T c11_u;
  const mxArray *c11_y = NULL;
  SFc11_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc11_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  c11_u = *(real_T *)c11_inData;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", &c11_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, false);
  return c11_mxArrayOutData;
}

static real_T c11_c_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  real_T c11_y;
  real_T c11_d0;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_d0, 1, 0, 0U, 0, 0U, 0);
  c11_y = c11_d0;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void c11_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_nargout;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  real_T c11_y;
  SFc11_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc11_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c11_nargout = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_nargout),
    &c11_thisId);
  sf_mex_destroy(&c11_nargout);
  *(real_T *)c11_outData = c11_y;
  sf_mex_destroy(&c11_mxArrayInData);
}

const mxArray *sf_c11_m3dof_library_get_eml_resolved_functions_info(void)
{
  const mxArray *c11_nameCaptureInfo = NULL;
  c11_nameCaptureInfo = NULL;
  sf_mex_assign(&c11_nameCaptureInfo, sf_mex_createstruct("structure", 2, 4, 1),
                false);
  c11_info_helper(&c11_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c11_nameCaptureInfo);
  return c11_nameCaptureInfo;
}

static void c11_info_helper(const mxArray **c11_info)
{
  const mxArray *c11_rhs0 = NULL;
  const mxArray *c11_lhs0 = NULL;
  const mxArray *c11_rhs1 = NULL;
  const mxArray *c11_lhs1 = NULL;
  const mxArray *c11_rhs2 = NULL;
  const mxArray *c11_lhs2 = NULL;
  const mxArray *c11_rhs3 = NULL;
  const mxArray *c11_lhs3 = NULL;
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("sin"), "name", "name", 0);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c11_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs0), "rhs", "rhs",
                  0);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs0), "lhs", "lhs",
                  0);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 1);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1286818736U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c11_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs1), "rhs", "rhs",
                  1);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs1), "lhs", "lhs",
                  1);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("cos"), "name", "name", 2);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c11_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs2), "rhs", "rhs",
                  2);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs2), "lhs", "lhs",
                  2);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("eml_scalar_cos"), "name",
                  "name", 3);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c11_info, c11_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(1286818722U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c11_info, c11_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c11_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c11_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_rhs3), "rhs", "rhs",
                  3);
  sf_mex_addfield(*c11_info, sf_mex_duplicatearraysafe(&c11_lhs3), "lhs", "lhs",
                  3);
  sf_mex_destroy(&c11_rhs0);
  sf_mex_destroy(&c11_lhs0);
  sf_mex_destroy(&c11_rhs1);
  sf_mex_destroy(&c11_lhs1);
  sf_mex_destroy(&c11_rhs2);
  sf_mex_destroy(&c11_lhs2);
  sf_mex_destroy(&c11_rhs3);
  sf_mex_destroy(&c11_lhs3);
}

static const mxArray *c11_emlrt_marshallOut(const char * c11_u)
{
  const mxArray *c11_y = NULL;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", c11_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c11_u)), false);
  return c11_y;
}

static const mxArray *c11_b_emlrt_marshallOut(const uint32_T c11_u)
{
  const mxArray *c11_y = NULL;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", &c11_u, 7, 0U, 0U, 0U, 0), false);
  return c11_y;
}

static const mxArray *c11_c_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  int32_T c11_u;
  const mxArray *c11_y = NULL;
  SFc11_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc11_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  c11_u = *(int32_T *)c11_inData;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", &c11_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, false);
  return c11_mxArrayOutData;
}

static int32_T c11_d_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  int32_T c11_y;
  int32_T c11_i21;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_i21, 1, 6, 0U, 0, 0U, 0);
  c11_y = c11_i21;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void c11_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_b_sfEvent;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  int32_T c11_y;
  SFc11_m3dof_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc11_m3dof_libraryInstanceStruct *)chartInstanceVoid;
  c11_b_sfEvent = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_b_sfEvent),
    &c11_thisId);
  sf_mex_destroy(&c11_b_sfEvent);
  *(int32_T *)c11_outData = c11_y;
  sf_mex_destroy(&c11_mxArrayInData);
}

static uint8_T c11_e_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_b_is_active_c11_m3dof_library, const char_T
  *c11_identifier)
{
  uint8_T c11_y;
  emlrtMsgIdentifier c11_thisId;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c11_b_is_active_c11_m3dof_library), &c11_thisId);
  sf_mex_destroy(&c11_b_is_active_c11_m3dof_library);
  return c11_y;
}

static uint8_T c11_f_emlrt_marshallIn(SFc11_m3dof_libraryInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  uint8_T c11_y;
  uint8_T c11_u0;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_u0, 1, 3, 0U, 0, 0U, 0);
  c11_y = c11_u0;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void init_dsm_address_info(SFc11_m3dof_libraryInstanceStruct
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

void sf_c11_m3dof_library_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2304148275U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3189879251U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3390716311U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(918594032U);
}

mxArray *sf_c11_m3dof_library_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("f5mh03n84ycac3vyTIXq3D");
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c11_m3dof_library_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c11_m3dof_library_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c11_m3dof_library(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"g\",},{M[8],M[0],T\"is_active_c11_m3dof_library\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c11_m3dof_library_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc11_m3dof_libraryInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc11_m3dof_libraryInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _m3dof_libraryMachineNumber_,
           11,
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
          _SFD_SET_DATA_PROPS(1,1,1,0,"xi1");
          _SFD_SET_DATA_PROPS(2,2,0,1,"g");
          _SFD_SET_DATA_PROPS(3,1,1,0,"xi2");
          _SFD_SET_DATA_PROPS(4,1,1,0,"xi3");
          _SFD_SET_DATA_PROPS(5,1,1,0,"a");
          _SFD_SET_DATA_PROPS(6,1,1,0,"eg");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1598);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)
            c11_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c11_q)[3];
          real_T (*c11_xi1)[3];
          real_T (*c11_g)[3];
          real_T (*c11_xi2)[3];
          real_T (*c11_xi3)[3];
          real_T (*c11_a)[3];
          real_T (*c11_eg)[3];
          c11_eg = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 5);
          c11_a = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 4);
          c11_xi3 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c11_xi2 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 2);
          c11_g = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c11_xi1 = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c11_q = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c11_q);
          _SFD_SET_DATA_VALUE_PTR(1U, *c11_xi1);
          _SFD_SET_DATA_VALUE_PTR(2U, *c11_g);
          _SFD_SET_DATA_VALUE_PTR(3U, *c11_xi2);
          _SFD_SET_DATA_VALUE_PTR(4U, *c11_xi3);
          _SFD_SET_DATA_VALUE_PTR(5U, *c11_a);
          _SFD_SET_DATA_VALUE_PTR(6U, *c11_eg);
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
  return "ZckjdleQrzDArRuVjAPR8E";
}

static void sf_opaque_initialize_c11_m3dof_library(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc11_m3dof_libraryInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c11_m3dof_library((SFc11_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
  initialize_c11_m3dof_library((SFc11_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c11_m3dof_library(void *chartInstanceVar)
{
  enable_c11_m3dof_library((SFc11_m3dof_libraryInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c11_m3dof_library(void *chartInstanceVar)
{
  disable_c11_m3dof_library((SFc11_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c11_m3dof_library(void *chartInstanceVar)
{
  sf_gateway_c11_m3dof_library((SFc11_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c11_m3dof_library(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c11_m3dof_library
    ((SFc11_m3dof_libraryInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c11_m3dof_library();/* state var info */
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

extern void sf_internal_set_sim_state_c11_m3dof_library(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c11_m3dof_library();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c11_m3dof_library((SFc11_m3dof_libraryInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c11_m3dof_library(SimStruct* S)
{
  return sf_internal_get_sim_state_c11_m3dof_library(S);
}

static void sf_opaque_set_sim_state_c11_m3dof_library(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c11_m3dof_library(S, st);
}

static void sf_opaque_terminate_c11_m3dof_library(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc11_m3dof_libraryInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_m3dof_library_optimization_info();
    }

    finalize_c11_m3dof_library((SFc11_m3dof_libraryInstanceStruct*)
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
  initSimStructsc11_m3dof_library((SFc11_m3dof_libraryInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c11_m3dof_library(SimStruct *S)
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
    initialize_params_c11_m3dof_library((SFc11_m3dof_libraryInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c11_m3dof_library(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_m3dof_library_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      11);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,11,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,11,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,11);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,11,6);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,11,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,11);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3310090538U));
  ssSetChecksum1(S,(1652335499U));
  ssSetChecksum2(S,(3586539706U));
  ssSetChecksum3(S,(2194001154U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c11_m3dof_library(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c11_m3dof_library(SimStruct *S)
{
  SFc11_m3dof_libraryInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc11_m3dof_libraryInstanceStruct *)utMalloc(sizeof
    (SFc11_m3dof_libraryInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc11_m3dof_libraryInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c11_m3dof_library;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c11_m3dof_library;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c11_m3dof_library;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c11_m3dof_library;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c11_m3dof_library;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c11_m3dof_library;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c11_m3dof_library;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c11_m3dof_library;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c11_m3dof_library;
  chartInstance->chartInfo.mdlStart = mdlStart_c11_m3dof_library;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c11_m3dof_library;
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

void c11_m3dof_library_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c11_m3dof_library(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c11_m3dof_library(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c11_m3dof_library(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c11_m3dof_library_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
