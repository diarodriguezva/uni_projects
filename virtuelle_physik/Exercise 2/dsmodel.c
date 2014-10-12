/* DSblock model generated by Dymola from Modelica model CartPole
 Dymola Version 2013 FD01 (32-bit), 2012-10-18 translated this at Tue Oct 29 15:26:26 2013

   */

#include <matrixop.h>
/* Declaration of C-structs */
/* Prototypes for functions used in model */
/* Codes used in model */
/* DSblock C-code: */

BreakSectionFunctionDef(1)
BreakSectionFunctionDef(2)
#include <moutil.c>
PreNonAliasDef(0)
PreNonAliasDef(1)
DYMOLA_STATIC const char*modelName="CartPole";
DYMOLA_STATIC const char*usedLibraries[]={0};
DYMOLA_STATIC const char*dllLibraryPath[]={0};
DYMOLA_STATIC const char*default_dymosim_license_filename=
 "c:/programdata/dynasim/dymola.lic";
#define QJacobianCGDef_ 1
DYMOLA_STATIC long QJacobianCG_[7]={2 , 3 , 1 , 2 , 3 , 1 , 4};
DYMOLA_STATIC long QJacobianGC_[9]={
2 , 3 , 0 , 3 , 0 , 4 , 4 , 4 , 0};
DYMOLA_STATIC double QJacobianCD_[5]={0  , 44 , 55 , 66 , 70};
#include <dsblock1.c>

/* Define variable names. */

#define Sections_

TranslatedEquations

BoundParameterSection
W_[4] = DP_[1]*sqr(DP_[2]);
InitialSection
InitialSection
DefaultSection
InitializeData(0)
InitialSection
InitialSection2
X_[1] = DP_[3];
X_[3] = DP_[4];
X_[2] = DP_[6];
X_[0] = DP_[5];
InitialSection
Init=false;InitializeData(2);Init=true;
EndInitialSection

OutputSection

DynamicsSection
W_[2] = DP_[1]*DP_[2]*sqr(X_[3]);
BreakSectionFunctionNew(1);
 /* Linear system of equations to solve. */
/* Introducing 3 common subexpressions used in 5 expressions */
/* Of the common subexpressions 3 are reals, 0 are integers, and 0
   are booleans. */
helpvar[0] = cos(X_[2]);
helpvar[1] = sin(X_[2]);
helpvar[2] = DP_[1]*DP_[7]*helpvar[1];
F_[1] = RememberSimple_(F_[1], 0);
SolveScalarLinear(helpvar[0]*helpvar[0]*DP_[1]-DP_[0]-DP_[1],"cos(Theta)*(cos(Theta)*Mp)-Ms-Mp",
   helpvar[0]*helpvar[2]-W_[2]*helpvar[1],"cos(Theta)*(Mp*G*sin(Theta))-Fz*sin(Theta)",
   F_[1],"der(v)");
W_[1] = helpvar[2]-DP_[1]*F_[1]*helpvar[0];
W_[3] =  -DP_[0]*F_[1];
 /* End of Equation Block */ 

BreakSectionFunctionNew(2);
W_[0] = W_[1]*DP_[2];
 /* Linear system of equations to solve. */
F_[3] = RememberSimple_(F_[3], 1);
SolveScalarLinearParametric( -W_[4]," -I",  -W_[0]," -T", F_[3],"der(Omega)");
 /* End of Equation Block */ 

F_[2] = X_[3];
F_[0] = X_[1];

AcceptedSection1

AcceptedSection2

DefaultSection
InitializeData(1)
EndTranslatedEquations

#include <dsblock6.c>

PreNonAliasNew(0)
StartNonAlias(0)
DeclareParameter("Ms", "Kg", 0, 250, 0.0,0.0,0.0,0,560)
DeclareParameter("Mp", "Kg", 1, 70, 0.0,0.0,0.0,0,560)
DeclareParameter("R", "m", 2, 2.5, 0.0,0.0,0.0,0,560)
DeclareParameter("v0", "", 3, 0, 0.0,0.0,0.0,0,560)
DeclareParameter("Omega0", "", 4, 0, 0.0,0.0,0.0,0,560)
DeclareParameter("s0", "", 5, 0, 0.0,0.0,0.0,0,560)
DeclareParameter("Theta0", "", 6, 1.25, 0.0,0.0,0.0,0,560)
DeclareParameter("G", "", 7, -9.81, 0.0,0.0,0.0,0,560)
DeclareState("s", "", 0, 0.0, 0.0,0.0,0.0,0,544)
DeclareDerivative("der(s)", "", 0.0, 0.0,0.0,0.0,0,512)
DeclareState("v", "", 1, 0.0, 0.0,0.0,0.0,0,544)
DeclareDerivative("der(v)", "", 0.0, 0.0,0.0,0.0,0,512)
DeclareState("Theta", "", 2, 0.0, 0.0,0.0,0.0,0,544)
DeclareDerivative("der(Theta)", "", 0.0, 0.0,0.0,0.0,0,512)
DeclareState("Omega", "", 3, 0.0, 0.0,0.0,0.0,0,544)
DeclareDerivative("der(Omega)", "", 0.0, 0.0,0.0,0.0,0,512)
DeclareAlias2("a", "", "der(v)", 1, 6, 1, 0)
DeclareAlias2("Alpha", "", "der(Omega)", 1, 6, 3, 0)
DeclareVariable("T", "", 0.0, 0.0,0.0,0.0,0,512)
DeclareVariable("Fn", "", 0.0, 0.0,0.0,0.0,0,512)
DeclareVariable("Fz", "", 0.0, 0.0,0.0,0.0,0,512)
DeclareVariable("Fp", "", 0.0, 0.0,0.0,0.0,0,512)
DeclareAlias2("Fs", "", "Fp", -1, 5, 3, 0)
DeclareAlias2("ap", "", "der(v)", 1, 6, 1, 0)
DeclareVariable("I", "", 0.0, 0.0,0.0,0.0,0,513)
EndNonAlias(0)
#define NX_    4
#define NX2_   0
#define NU_    0
#define NY_    0
#define NW_    5
#define NP_    8
#define NPS_   0
#define MAXAuxStr_   0
#define MAXAuxStrLen_   500
#define NHash1_ 1641547192
#define NHash2_ -1425955321
#define NHash3_ 0
#define NI_    0
#define NRelF_ 0
#define NRel_  0
#define NTim_  0
#define NSamp_ 0
#define NCons_ 0
#define NA_    4
#define SizePre_ 0
#define SizeEq_ 2
#define SizeDelay_ 0
#define QNLmax_ 0
#define MAXAux 0
#define NrDymolaTimers_ 0
#define NWhen_ 0
#define NCheckIf_ 0
#define NGlobalHelp_ 3
#ifndef NExternalObject_
#define NExternalObject_ 0
#endif

#define DymolaHaveUpdateInitVars 1
#include <dsblock5.c>

DYMOLA_STATIC void UpdateInitVars(double *time, double X_[], double XD_[], double U_[], 
double DP_[], long IP_[], Dymola_bool LP_[], double F_[], double Y_[], double W_[], double QZ_[], double duser_[], long iuser_[], void*cuser_[]) {
static Real initStore[1];
}
StartDataBlock
StartEqBlock
DoRemember_(F_[3], 0.0, 1);
DoRemember_(F_[1], 0.0, 0);
EndEqBlock
EndDataBlock
