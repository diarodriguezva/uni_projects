/* Include files */

#include "CollisionStrategies2_sfun.h"
#include "CollisionStrategies2_sfun_debug_macros.h"
#include "c1_CollisionStrategies2.h"
#include "c2_CollisionStrategies2.h"
#include "c3_CollisionStrategies2.h"
#include "c4_CollisionStrategies2.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _CollisionStrategies2MachineNumber_;

/* Function Declarations */

/* Function Definitions */
void CollisionStrategies2_initializer(void)
{
}

void CollisionStrategies2_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_CollisionStrategies2_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_CollisionStrategies2_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_CollisionStrategies2_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_CollisionStrategies2_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_CollisionStrategies2_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_CollisionStrategies2_process_check_sum_call( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
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
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(863421189U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3171911646U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3866388153U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2738312749U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1558974978U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3774867310U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2673675649U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(257068996U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_CollisionStrategies2_get_check_sum(mxArray *plhs[]);
          sf_c1_CollisionStrategies2_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_CollisionStrategies2_get_check_sum(mxArray *plhs[]);
          sf_c2_CollisionStrategies2_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_CollisionStrategies2_get_check_sum(mxArray *plhs[]);
          sf_c3_CollisionStrategies2_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_CollisionStrategies2_get_check_sum(mxArray *plhs[]);
          sf_c4_CollisionStrategies2_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2083502392U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1110276785U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3258378658U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3926592909U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1887216090U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(857940209U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1354893476U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1086650327U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_CollisionStrategies2_autoinheritance_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
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
     case 1:
      {
        if (strcmp(aiChksum, "EROkReCRXJCOIBLHD7YM8C") == 0) {
          extern mxArray *sf_c1_CollisionStrategies2_get_autoinheritance_info
            (void);
          plhs[0] = sf_c1_CollisionStrategies2_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "EROkReCRXJCOIBLHD7YM8C") == 0) {
          extern mxArray *sf_c2_CollisionStrategies2_get_autoinheritance_info
            (void);
          plhs[0] = sf_c2_CollisionStrategies2_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "dldOEgf5GZzKRtb40lcEtF") == 0) {
          extern mxArray *sf_c3_CollisionStrategies2_get_autoinheritance_info
            (void);
          plhs[0] = sf_c3_CollisionStrategies2_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "wtMu9nQTvjlbjWqmhqOzdD") == 0) {
          extern mxArray *sf_c4_CollisionStrategies2_get_autoinheritance_info
            (void);
          plhs[0] = sf_c4_CollisionStrategies2_get_autoinheritance_info();
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

unsigned int sf_CollisionStrategies2_get_eml_resolved_functions_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
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
     case 1:
      {
        extern const mxArray
          *sf_c1_CollisionStrategies2_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_CollisionStrategies2_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray
          *sf_c2_CollisionStrategies2_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_CollisionStrategies2_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray
          *sf_c3_CollisionStrategies2_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_CollisionStrategies2_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray
          *sf_c4_CollisionStrategies2_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_CollisionStrategies2_get_eml_resolved_functions_info();
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

unsigned int sf_CollisionStrategies2_third_party_uses_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
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
     case 1:
      {
        if (strcmp(tpChksum, "ARGtbBB4TM9lz1qMhunj6B") == 0) {
          extern mxArray *sf_c1_CollisionStrategies2_third_party_uses_info(void);
          plhs[0] = sf_c1_CollisionStrategies2_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "ARGtbBB4TM9lz1qMhunj6B") == 0) {
          extern mxArray *sf_c2_CollisionStrategies2_third_party_uses_info(void);
          plhs[0] = sf_c2_CollisionStrategies2_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "4qTRrlBsIJseMjWcBjTeFC") == 0) {
          extern mxArray *sf_c3_CollisionStrategies2_third_party_uses_info(void);
          plhs[0] = sf_c3_CollisionStrategies2_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "mBas2ucAIbcuWhL9qHglqH") == 0) {
          extern mxArray *sf_c4_CollisionStrategies2_third_party_uses_info(void);
          plhs[0] = sf_c4_CollisionStrategies2_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_CollisionStrategies2_updateBuildInfo_args_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
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
     case 1:
      {
        if (strcmp(tpChksum, "ARGtbBB4TM9lz1qMhunj6B") == 0) {
          extern mxArray *sf_c1_CollisionStrategies2_updateBuildInfo_args_info
            (void);
          plhs[0] = sf_c1_CollisionStrategies2_updateBuildInfo_args_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "ARGtbBB4TM9lz1qMhunj6B") == 0) {
          extern mxArray *sf_c2_CollisionStrategies2_updateBuildInfo_args_info
            (void);
          plhs[0] = sf_c2_CollisionStrategies2_updateBuildInfo_args_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "4qTRrlBsIJseMjWcBjTeFC") == 0) {
          extern mxArray *sf_c3_CollisionStrategies2_updateBuildInfo_args_info
            (void);
          plhs[0] = sf_c3_CollisionStrategies2_updateBuildInfo_args_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "mBas2ucAIbcuWhL9qHglqH") == 0) {
          extern mxArray *sf_c4_CollisionStrategies2_updateBuildInfo_args_info
            (void);
          plhs[0] = sf_c4_CollisionStrategies2_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void CollisionStrategies2_debug_initialize(struct SfDebugInstanceStruct*
  debugInstance)
{
  _CollisionStrategies2MachineNumber_ = sf_debug_initialize_machine
    (debugInstance,"CollisionStrategies2","sfun",0,4,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,
    _CollisionStrategies2MachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,
    _CollisionStrategies2MachineNumber_,0);
}

void CollisionStrategies2_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_CollisionStrategies2_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info(
      "CollisionStrategies2", "CollisionStrategies2");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_CollisionStrategies2_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
