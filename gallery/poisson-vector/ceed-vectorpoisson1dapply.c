// Copyright (c) 2017-2025, Lawrence Livermore National Security, LLC and other CEED contributors.
// All Rights Reserved. See the top-level LICENSE and NOTICE files for details.
//
// SPDX-License-Identifier: BSD-2-Clause
//
// This file is part of CEED:  http://github.com/ceed

#include <ceed.h>
#include <ceed/backend.h>
#include <ceed/jit-source/gallery/ceed-vectorpoisson1dapply.h>
#include <string.h>

/**
  @brief Set fields for `CeedQFunction` applying the 1D Poisson operator on a vector system with three components
**/
static int CeedQFunctionInit_Vector3Poisson1DApply(Ceed ceed, const char *requested, CeedQFunction qf) {
  // Check QFunction name
  const char *name = "Vector3Poisson1DApply";
  CeedCheck(!strcmp(name, requested), ceed, CEED_ERROR_UNSUPPORTED, "QFunction '%s' does not match requested name: %s", name, requested);

  // Add QFunction fields
  const CeedInt dim = 1, num_comp = 3;
  CeedCall(CeedQFunctionAddInput(qf, "du", num_comp * dim, CEED_EVAL_GRAD));
  CeedCall(CeedQFunctionAddInput(qf, "qdata", dim * (dim + 1) / 2, CEED_EVAL_NONE));
  CeedCall(CeedQFunctionAddOutput(qf, "dv", num_comp * dim, CEED_EVAL_GRAD));

  CeedCall(CeedQFunctionSetUserFlopsEstimate(qf, num_comp));

  return CEED_ERROR_SUCCESS;
}

/**
  @brief Register `CeedQFunction` for applying the 1D Poisson operator on a vector system with three components
**/
CEED_INTERN int CeedQFunctionRegister_Vector3Poisson1DApply(void) {
  return CeedQFunctionRegister("Vector3Poisson1DApply", Vector3Poisson1DApply_loc, 1, Vector3Poisson1DApply, CeedQFunctionInit_Vector3Poisson1DApply);
}
