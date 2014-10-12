#ifndef __c10_QID9R45YhBrXXzvR4mF7tE_m3dof_library_h__
#define __c10_QID9R45YhBrXXzvR4mF7tE_m3dof_library_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc10_QID9R45YhBrXXzvR4mF7tE_m3dof_libraryInstanceStruct
#define typedef_SFc10_QID9R45YhBrXXzvR4mF7tE_m3dof_libraryInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c10_QID9R45YhBrXXzvR4mF7tE_sfEvent;
  boolean_T c10_QID9R45YhBrXXzvR4mF7tE_isStable;
  boolean_T c10_QID9R45YhBrXXzvR4mF7tE_doneDoubleBufferReInit;
  uint8_T c10_QID9R45YhBrXXzvR4mF7tE_is_active_c10_QID9R45YhBrXXzvR4mF7tE_;
} SFc10_QID9R45YhBrXXzvR4mF7tE_m3dof_libraryInstanceStruct;

#endif                                 /*typedef_SFc10_QID9R45YhBrXXzvR4mF7tE_m3dof_libraryInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c10_QID9R45YhBrXXzvR4mF7tE_m3dof_library_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c10_QID9R45YhBrXXzvR4mF7tE_m3dof_library_get_check_sum(mxArray
  *plhs[]);
extern void c10_QID9R45YhBrXXzvR4mF7tE_m3dof_library_method_dispatcher(SimStruct
  *S, int_T method, void *data);

#endif