/* Include files */

#include "m3dof_library_sfun.h"
#include "m3dof_library_sfun_debug_macros.h"
#include "c2_m3dof_library.h"
#include "c10_m3dof_library.h"
#include "c11_m3dof_library.h"
#include "c12_m3dof_library.h"
#include "c16_m3dof_library.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _m3dof_libraryMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void m3dof_library_initializer(void)
{
}

void m3dof_library_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_m3dof_library_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==2) {
    c2_m3dof_library_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==10) {
    c10_m3dof_library_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==11) {
    c11_m3dof_library_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==12) {
    c12_m3dof_library_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==16) {
    c16_m3dof_library_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_m3dof_library_process_check_sum_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>2 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"library")) {
      char machineName[100];
      mxGetString(prhs[2], machineName,sizeof(machineName)/sizeof(char));
      machineName[(sizeof(machineName)/sizeof(char)-1)] = '\0';
      if (!strcmp(machineName,"m3dof_library")) {
        if (nrhs==3) {
          ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(64562885U);
          ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3433943271U);
          ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1394579772U);
          ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3596955035U);
        } else if (nrhs==4) {
          unsigned int chartFileNumber;
          chartFileNumber = (unsigned int)mxGetScalar(prhs[3]);
          switch (chartFileNumber) {
           case 2:
            {
              extern void sf_c2_m3dof_library_get_check_sum(mxArray *plhs[]);
              sf_c2_m3dof_library_get_check_sum(plhs);
              break;
            }

           case 10:
            {
              extern void sf_c10_m3dof_library_get_check_sum(mxArray *plhs[]);
              sf_c10_m3dof_library_get_check_sum(plhs);
              break;
            }

           case 11:
            {
              extern void sf_c11_m3dof_library_get_check_sum(mxArray *plhs[]);
              sf_c11_m3dof_library_get_check_sum(plhs);
              break;
            }

           case 12:
            {
              extern void sf_c12_m3dof_library_get_check_sum(mxArray *plhs[]);
              sf_c12_m3dof_library_get_check_sum(plhs);
              break;
            }

           case 16:
            {
              extern void sf_c16_m3dof_library_get_check_sum(mxArray *plhs[]);
              sf_c16_m3dof_library_get_check_sum(plhs);
              break;
            }

           default:
            ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
            ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
            ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
            ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
          }
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    } else {
      return 0;
    }
  } else {
    return 0;
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_m3dof_library_autoinheritance_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(aiChksum, "yUZK09VDiaWwc8hbKcDX1F") == 0) {
          extern mxArray *sf_c2_m3dof_library_get_autoinheritance_info(void);
          plhs[0] = sf_c2_m3dof_library_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 10:
      {
        if (strcmp(aiChksum, "7tlHsWfU2aDNJydQ8jJh7G") == 0) {
          extern mxArray *sf_c10_m3dof_library_get_autoinheritance_info(void);
          plhs[0] = sf_c10_m3dof_library_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 11:
      {
        if (strcmp(aiChksum, "f5mh03n84ycac3vyTIXq3D") == 0) {
          extern mxArray *sf_c11_m3dof_library_get_autoinheritance_info(void);
          plhs[0] = sf_c11_m3dof_library_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 12:
      {
        if (strcmp(aiChksum, "v5PKewA288wkSV6ZELLHzC") == 0) {
          extern mxArray *sf_c12_m3dof_library_get_autoinheritance_info(void);
          plhs[0] = sf_c12_m3dof_library_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 16:
      {
        if (strcmp(aiChksum, "tcQ6qe435gckvJ3jaGWykC") == 0) {
          extern mxArray *sf_c16_m3dof_library_get_autoinheritance_info(void);
          plhs[0] = sf_c16_m3dof_library_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_m3dof_library_get_eml_resolved_functions_info( int nlhs, mxArray
  * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        extern const mxArray
          *sf_c2_m3dof_library_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_m3dof_library_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 10:
      {
        extern const mxArray
          *sf_c10_m3dof_library_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c10_m3dof_library_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 11:
      {
        extern const mxArray
          *sf_c11_m3dof_library_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c11_m3dof_library_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 12:
      {
        extern const mxArray
          *sf_c12_m3dof_library_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c12_m3dof_library_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 16:
      {
        extern const mxArray
          *sf_c16_m3dof_library_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c16_m3dof_library_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_m3dof_library_third_party_uses_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(tpChksum, "4AKay5lWZU733EqWqUlbKF") == 0) {
          extern mxArray *sf_c2_m3dof_library_third_party_uses_info(void);
          plhs[0] = sf_c2_m3dof_library_third_party_uses_info();
          break;
        }
      }

     case 10:
      {
        if (strcmp(tpChksum, "xTRDt0LbA83zt2EbCc5TbB") == 0) {
          extern mxArray *sf_c10_m3dof_library_third_party_uses_info(void);
          plhs[0] = sf_c10_m3dof_library_third_party_uses_info();
          break;
        }
      }

     case 11:
      {
        if (strcmp(tpChksum, "ZckjdleQrzDArRuVjAPR8E") == 0) {
          extern mxArray *sf_c11_m3dof_library_third_party_uses_info(void);
          plhs[0] = sf_c11_m3dof_library_third_party_uses_info();
          break;
        }
      }

     case 12:
      {
        if (strcmp(tpChksum, "ujnVDRbH8LlhOJD9n6ibWC") == 0) {
          extern mxArray *sf_c12_m3dof_library_third_party_uses_info(void);
          plhs[0] = sf_c12_m3dof_library_third_party_uses_info();
          break;
        }
      }

     case 16:
      {
        if (strcmp(tpChksum, "3fZKU2ENAlIr5JGvDet9QC") == 0) {
          extern mxArray *sf_c16_m3dof_library_third_party_uses_info(void);
          plhs[0] = sf_c16_m3dof_library_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_m3dof_library_updateBuildInfo_args_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(tpChksum, "4AKay5lWZU733EqWqUlbKF") == 0) {
          extern mxArray *sf_c2_m3dof_library_updateBuildInfo_args_info(void);
          plhs[0] = sf_c2_m3dof_library_updateBuildInfo_args_info();
          break;
        }
      }

     case 10:
      {
        if (strcmp(tpChksum, "xTRDt0LbA83zt2EbCc5TbB") == 0) {
          extern mxArray *sf_c10_m3dof_library_updateBuildInfo_args_info(void);
          plhs[0] = sf_c10_m3dof_library_updateBuildInfo_args_info();
          break;
        }
      }

     case 11:
      {
        if (strcmp(tpChksum, "ZckjdleQrzDArRuVjAPR8E") == 0) {
          extern mxArray *sf_c11_m3dof_library_updateBuildInfo_args_info(void);
          plhs[0] = sf_c11_m3dof_library_updateBuildInfo_args_info();
          break;
        }
      }

     case 12:
      {
        if (strcmp(tpChksum, "ujnVDRbH8LlhOJD9n6ibWC") == 0) {
          extern mxArray *sf_c12_m3dof_library_updateBuildInfo_args_info(void);
          plhs[0] = sf_c12_m3dof_library_updateBuildInfo_args_info();
          break;
        }
      }

     case 16:
      {
        if (strcmp(tpChksum, "3fZKU2ENAlIr5JGvDet9QC") == 0) {
          extern mxArray *sf_c16_m3dof_library_updateBuildInfo_args_info(void);
          plhs[0] = sf_c16_m3dof_library_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void m3dof_library_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _m3dof_libraryMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "m3dof_library","sfun",1,5,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _m3dof_libraryMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,
    _m3dof_libraryMachineNumber_,0);
}

void m3dof_library_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_m3dof_library_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("m3dof_library",
      "CollisionStrategies");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_m3dof_library_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
