// -*- C++ -*-
// $Id: eig.h,v 1.4 2004-01-07 13:50:08 bjoo Exp $

/*! \file
 * \brief Eigenvalue measurements
 *
 * Central include file for all measurements of eigenvalues
 */

/*! \defgroup eig Eigenvalue measurements
 * \ingroup meas
 *
 * Central include file for all measurements related to calculations
 * of eigenvalues of various linear operators.
 */

#ifndef __eig_h__
#define __eig_h__

#ifdef CHROMA_BUILD_WILSON
#include "eig_w.h"
#elif CHROMA_BUILD_STAGGERED
#include "eig_s.h"
#endif

#endif
