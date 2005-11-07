// -*- C++ -*-
// $Id: sink_smearing_factory.h,v 1.1 2005-11-07 06:24:09 edwards Exp $
/*! \file
 *  \brief Factory for producing quark prop sinks
 */

#ifndef __quark_sink_smearing_factory_h__
#define __quark_sink_smearing_factory_h__

#include "singleton.h"
#include "objfactory.h"
#include "chromabase.h"
#include "meas/smear/quark_source_sink.h"

namespace Chroma
{
  //! Propagator sink factory (foundry)
  /*! @ingroup sinks */
  typedef SingletonHolder< 
    ObjectFactory<QuarkSourceSink<LatticePropagator>, 
		  std::string,
		  TYPELIST_3(XMLReader&, const std::string&, const multi1d<LatticeColorMatrix>&),
		  QuarkSourceSink<LatticePropagator>* (*)(XMLReader&,
							  const std::string&,
							  const multi1d<LatticeColorMatrix>&), 
		  StringFactoryError> >
  ThePropSinkSmearingFactory;


  //! Propagator sink factory (foundry)
  /*! @ingroup sinks */
  typedef SingletonHolder< 
    ObjectFactory<QuarkSourceSink<LatticeFermion>, 
		  std::string,
		  TYPELIST_3(XMLReader&, const std::string&, const multi1d<LatticeColorMatrix>&),
		  QuarkSourceSink<LatticeFermion>* (*)(XMLReader&,
						       const std::string&,
						       const multi1d<LatticeColorMatrix>&), 
		  StringFactoryError> >
  TheFermSinkSmearingFactory;

}


#endif
