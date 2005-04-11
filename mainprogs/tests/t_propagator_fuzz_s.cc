// $Id: t_propagator_fuzz_s.cc,v 1.19 2005-04-11 02:44:11 edwards Exp $
/*! \file
 *  \brief Main code for propagator generation
 *
 *  Start to add fuzzed source to the staggered 
 *  project.
 */

#include <iostream>
#include <cstdio>

#define MAIN

// Include everything...
#include "chroma.h"

  // more work -- this should be in chroma.h
#include "meas/smear/fuzz_smear.h"

/*
 *  Here we have various temporary definitions
 */
/*


enum FermType {
  FERM_TYPE_STAGGERED,
  FERM_TYPE_UNKNOWN
};


using namespace Chroma;


/*
 * Input 
 */


// Parameters which must be determined from the XML input
// and written to the XML output
struct Param_t
{
  FermType     FermTypeP;
  Real         Mass;      // Staggered mass
  Real         u0;        // Tadpole Factor
 
  PropType prop_type;      // storage order for stored propagator

  InvertParam_t  invParam;

  Real GFAccu, OrPara;    // Gauge fixing tolerance and over-relaxation param
  int GFMax;              // Maximum gauge fixing iterations

  multi1d<int> nrow;
  multi1d<int> boundary;
  multi1d<int> t_srce; 
};


struct Prop_t
{
  string       source_file;
  string       prop_file;
};

struct Propagator_input_t
{
  IO_version_t     io_version;
  Param_t          param;
  Cfg_t            cfg;
  Prop_t           prop;
};


//
void read(XMLReader& xml, const string& path, Prop_t& input)
{
  XMLReader inputtop(xml, path);

//  read(inputtop, "source_file", input.source_file);
  read(inputtop, "prop_file", input.prop_file);
}



// Reader for input parameters
void read(XMLReader& xml, const string& path, Propagator_input_t& input)
{
  XMLReader inputtop(xml, path);


  // First, read the input parameter version.  Then, if this version
  // includes 'Nc' and 'Nd', verify they agree with values compiled
  // into QDP++

  // Read in the IO_version
  try
  {
    read(inputtop, "IO_version/version", input.io_version.version);
  }
  catch (const string& e) 
  {
    QDPIO::cerr << "Error reading data: " << e << endl;
    throw;
  }


  // Currently, in the supported IO versions, there is only a small difference
  // in the inputs. So, to make code simpler, extract the common bits 

  // Read the uncommon bits first
  try
  {
    XMLReader paramtop(inputtop, "param"); // push into 'param' group

    switch (input.io_version.version) 
    {
      /**************************************************************************/
    case 1 :
      /**************************************************************************/
      break;

    default :
      /**************************************************************************/

      QDPIO::cerr << "Input parameter version " << input.io_version.version << " unsupported." << endl;
      QDP_abort(1);
    }
  }
  catch (const string& e) 
  {
    QDPIO::cerr << "Error reading data: " << e << endl;
    throw;
  }


  // Read the common bits
  try 
  {
    XMLReader paramtop(inputtop, "param"); // push into 'param' group

    {
      string ferm_type_str;
      read(paramtop, "FermTypeP", ferm_type_str);
      if (ferm_type_str == "STAGGERED") {
	input.param.FermTypeP = FERM_TYPE_STAGGERED;
      } 
    }

    // GTF NOTE: I'm going to switch on FermTypeP here because I want
    // to leave open the option of treating masses differently.
    switch (input.param.FermTypeP) {
    case FERM_TYPE_STAGGERED :

      QDPIO::cout << " PROPAGATOR: Propagator for Staggered fermions" << endl;

      read(paramtop, "Mass", input.param.Mass);
      read(paramtop, "u0" , input.param.u0);

      break;

    default :
      QDP_error_exit("Fermion type not supported\n.");
    }

//    read(paramtop, "invType", input.param.invType);
    input.param.invParam.invType = CG_INVERTER;   //need to fix this
    read(paramtop, "RsdCG", input.param.invParam.RsdCG);
    read(paramtop, "MaxCG", input.param.invParam.MaxCG);
    read(paramtop, "GFAccu", input.param.GFAccu);
    read(paramtop, "OrPara", input.param.OrPara);
    read(paramtop, "GFMax", input.param.GFMax);

    read(paramtop, "nrow", input.param.nrow);
    read(paramtop, "boundary", input.param.boundary);
    read(paramtop, "t_srce", input.param.t_srce);
  }
  catch (const string& e) 
  {
    QDPIO::cerr << "Error reading data: " << e << endl;
    throw;
  }


  // Read in the gauge configuration file name
  try
  {
    read(inputtop, "Cfg", input.cfg);
    read(inputtop, "Prop", input.prop);
  }
  catch (const string& e) 
  {
    QDPIO::cerr << "Error reading data: " << e << endl;
    throw;
  }
}


enum stag_src_enum { LOCAL_SRC  , FUZZED_SRC , GAUGE_INVAR_LOCAL_SOURCE } ;
typedef   stag_src_enum stag_src_type ;

/*
  Function to return the type of staggered
  source.
*/

stag_src_type get_stag_src(XMLReader& xml, const string& path)
{
  stag_src_type ans ; 

  try
    {
      string src_name;
      read(xml, path, src_name);
      if (src_name == "LOCAL_SRC") 
	{
	  QDPIO::cout << "****> LOCAL SOURCE <****" << endl;
	  ans = LOCAL_SRC ; 
	} 
      else if (src_name == "GAUGE_INVAR_LOCAL_SOURCE") 
	{
	  QDPIO::cout << "****> GAUGE INVARIANT LOCAL SOURCE <****" << endl;
	  ans = GAUGE_INVAR_LOCAL_SOURCE ; 
	} 
      else if (src_name == "FUZZED_SRC") 
	{
	  QDPIO::cout << "***> FUZZED SOURCE ****" << endl;
	  ans = FUZZED_SRC ; 
	} 

      else
	{
	  QDPIO::cerr << "src_name " << src_name << " out of range " << endl;
	  QDP_abort(1);
	}
    }
  catch (const string& e) 
  {
    QDPIO::cerr << "Error reading data: " << e << endl;
    throw;
  }

  return ans ; 
}



//! Propagator generation
/*! \defgroup t_propagator_fuzz Propagator generation
 *  \ingroup testsmain
 *
 * Main program for propagator generation. 
 */

int main(int argc, char **argv)
{
  // Put the machine into a known state
  Chroma::initialize(&argc, &argv);

  // Input parameter structure
  Propagator_input_t  input;

  // Instantiate xml reader for DATA
  XMLReader xml_in(Chroma::getXMLInputFileName());

  // Read data
  read(xml_in, "/propagator", input);

  // Specify lattice size, shape, etc.
  Layout::setLattSize(input.param.nrow);
  Layout::create();

  // Read in the configuration along with relevant information.
  multi1d<LatticeColorMatrix> u(Nd);
  
  XMLReader  gauge_file_xml,  gauge_xml;
  gaugeStartup(gauge_file_xml, gauge_xml, u, input.cfg);

  // 
  //  gauge invariance test
  //  

  // this parameter will be read from the input file
  bool do_gauge_transform ;
  do_gauge_transform = false ;
  read(xml_in, "/propagator/param/do_gauge_transform",do_gauge_transform );

  if( do_gauge_transform )
    {
      // gauge transform the gauge fields
      multi1d<LatticeColorMatrix> u_trans(Nd);

      // create a random gauge transform
       LatticeColorMatrix v ;
  
       gaussian(v);
       reunit(v) ; 

       for(int dir = 0 ; dir < Nd ; ++dir)
	 {
	   u_trans[dir] = v*u[dir]*adj(shift(v,FORWARD,dir)) ;
	   u[dir] = u_trans[dir] ;
	 }

       QDPIO::cout << "Random gauge transform done" << endl;

    } // end of gauge transform



  // Instantiate XML writer for the output
  // XMLFileWriter xml_out("t_propagator_fuzz_s.xml");
  XMLFileWriter& xml_out = Chroma::getXMLOutputInstance();
  push(xml_out, "fuzzed_hadron_corr");

  // Write out the input parameter file
  write(xml_out, "Input", xml_in);

  // Write out the config header
  write(xml_out, "Config_info", gauge_xml);


  push(xml_out, "Output_version");
  write(xml_out, "out_version", 1);
  pop(xml_out);

  xml_out.flush();

  // Check if the gauge field configuration is unitarized
  unitarityCheck(u);

  // Calculate some gauge invariant observables just for info.
  MesPlq(xml_out, "Observables", u);
  xml_out.flush();

  // Fix to the coulomb gauge
  int n_gf;
  int j_decay = Nd-1;

#ifdef NNNNNNNNNNNNNN
  coulGauge(u, n_gf, j_decay, input.param.GFAccu, input.param.GFMax, true, input.param.OrPara);
  QDPIO::cout << "No. of gauge fixing iterations =" << n_gf << endl;
#endif

  // 
  // Ape fuzz the gauge fields
  //

  Real sm_fact = 2.5;   // typical parameter
  int sm_numb = 10;     // number of smearing hits

  int BlkMax = 100;    // max iterations in max-ing trace
  Real BlkAccu = 1.0e-5;  // accuracy of max-ing

  multi1d<LatticeColorMatrix> u_smr(Nd);
  u_smr = u;
  for(int i=0; i < sm_numb; ++i)
  {
    multi1d<LatticeColorMatrix> u_tmp(Nd);

    for(int mu = 0; mu < Nd; ++mu)
      if ( mu != j_decay )
	APE_Smear(u_smr, u_tmp[mu], mu, 0, sm_fact, BlkAccu, BlkMax, j_decay);
      else
	u_tmp[mu] = u_smr[mu];
    
    u_smr = u_tmp;
  }

  //
  //  --- end of APE smearing -----
  //



  // Calcluate plaq on the gauge fixed field
  MesPlq(xml_out, "Observables", u);
  xml_out.flush();

  // Create a fermion BC. Note, the handle is on an ABSTRACT type.
  Handle< FermBC<LatticeStaggeredFermion> >  fbc(new SimpleFermBC<LatticeStaggeredFermion>(input.param.boundary));

  //
  // Initialize fermion action
  //
  AsqtadFermAct S_f(fbc, input.param.Mass, input.param.u0);

  // Set up a state for the current u,
  // (compute fat & triple links)
  // Use S_f.createState so that S_f can pass in u0

  Handle<const ConnectState > state(S_f.createState(u));
  // Handle<const EvenOddLinearOperator<LatticeStaggeredFermion> > D_asqtad(S_f.linOp(state));

  //Handle<const LinearOperator<LatticeStaggeredFermion> > MdagM_asqtad(S_f.lMdagM(state));

  Handle<const SystemSolver<LatticeStaggeredFermion> > qprop(S_f.qprop(state,input.param.invParam));


  //
  // Loop over the source color, creating the source
  // and calling the relevant propagator routines.
  // 

  LatticeStaggeredPropagator quark_propagator;
  XMLBufferWriter xml_buf;
  int ncg_had = 0;
  int n_count;

  LatticeStaggeredFermion q_source, psi;
  LatticeStaggeredFermion q_source_fuzz ; 
  multi1d<LatticeStaggeredPropagator> stag_prop(8);

  // the staggered spectroscopy code is hardwired
  // for many pions (why range of 0)
  for(int src_ind = 0; src_ind < 0; ++src_ind)
    stag_prop[src_ind] = zero ;


  // pass the origin from input file
  int t_source = 0;
  QDPIO::cout << "Source time slice = " << t_source << endl;

  stag_src_type type_of_src = 
    get_stag_src(xml_in,"/propagator/param/src_type")   ;

  // just look at the local pion (8 should be system constant)
  for(int src_ind = 0; src_ind < 8 ; ++src_ind){
    psi = zero;   // note this is ``zero'' and not 0
    

      for(int color_source = 0; color_source < Nc; ++color_source) 
	{
	  QDPIO::cout << "Inversion for Color =  " << color_source << endl;

	  q_source = zero ;

	  if( type_of_src == LOCAL_SRC )
	    {
	      q_source = zero ;
	      multi1d<int> coord(Nd);

	      PropIndexTodelta(src_ind, coord) ; 
	      srcfil(q_source, coord,color_source ) ;
	    }
	  else if( type_of_src == GAUGE_INVAR_LOCAL_SOURCE  )
	    {
	      q_source = zero ;
	      multi1d<int> coord(Nd);
	      
	      // start with local source 
	      coord[0]=0; coord[1] = 0; coord[2] = 0; coord[3] = 0;
	      srcfil(q_source, coord,color_source ) ;
	      
	      // now do the shift
	      PropIndexTodelta(src_ind, coord) ; 
	      q_source_fuzz = q_source  ;
	      q_source = shiftDeltaPropCov(coord,q_source_fuzz,u,
					   false); 

	    }
	  else if( type_of_src == FUZZED_SRC )
	    {
	      int fuzz_width = 2 ; 

	      //	      QDPIO::cout << "fuzz width = " << fuzz_width  << endl;
	    
	      q_source = zero ;
	      multi1d<int> coord(Nd);

	      PropIndexTodelta(src_ind, coord) ; 
	      srcfil(q_source, coord,color_source ) ;


	      fuzz_smear(u_smr, q_source,q_source_fuzz, 
			 fuzz_width, j_decay) ; 

	      q_source = q_source_fuzz  ;
	    }



	  // Use the last initial guess as the current guess

	  // Compute the propagator for given source color/spin 
	  // int n_count;

	  // S_f.qprop(psi, state, q_source, input.param.invParam, n_count);
	  n_count = (*qprop)(psi, q_source);
    
	  ncg_had += n_count;

	// this is done for xmldif reasons
	if( src_ind == 0 )
	  {
	    push(xml_out,"Qprop");
	    write(xml_out, "Mass" , input.param.Mass);
	    write(xml_out, "RsdCG", input.param.invParam.RsdCG);
	    write(xml_out, "n_count", n_count);
	    pop(xml_out);
	  }

        /*
         * Move the solution to the appropriate components
         * of quark propagator.
        */
        FermToProp(psi, quark_propagator, color_source);
      }  //color_source
    
      stag_prop[src_ind] = quark_propagator;
      } // end src_ind
  

      push(xml_out, "Hadrons_from_time_source");
      write(xml_out, "source_time", t_source);
      if( type_of_src == LOCAL_SRC )
	{ write(xml_out, "source_type", "LOCAL_SRC"); }
      else if( type_of_src == GAUGE_INVAR_LOCAL_SOURCE  )
	{ write(xml_out, "source_type", "GAUGE_INVAR_LOCAL_SOURCE"); }
      else if( type_of_src == FUZZED_SRC )
	{ write(xml_out, "source_type", "FUZZED_SRC"); }

      bool use_gauge_invar_oper ;
      use_gauge_invar_oper = false ;
      read(xml_in, "/propagator/param/use_gauge_invar_oper",use_gauge_invar_oper );

      int t_length = input.param.nrow[3];
      staggered_pions pseudoscalar(t_length,u) ; 

      write(xml_out, "use_gauge_invar_oper", use_gauge_invar_oper);
      if( use_gauge_invar_oper )
	{
	  cout << "Using gauge invariant operators "  << endl ; 
	  pseudoscalar.use_gauge_invar() ;

	}
      else
	{
	  cout << "Using NON-gauge invariant operators "  << endl ; 
	  pseudoscalar.use_NON_gauge_invar()  ;
	}


      pseudoscalar.compute(stag_prop, j_decay);
      pseudoscalar.dump(t_source,xml_out);
      pop(xml_out);
  
      //
      // compute some simple baryon operators
      //
      int bc_spec = 0 ;
      multi1d<int> coord(Nd);
      coord[0]=0; coord[1] = 0; coord[2] = 0; coord[3] = 0;
      
      multi1d<Complex>  barprop(input.param.nrow[3]) ;
      
      baryon_s(quark_propagator,barprop,
	       coord,j_decay, bc_spec) ;
      
      push(xml_out, "baryon");
      write(xml_out, "nucleon", barprop);
      pop(xml_out);
      
      
      pop(xml_out);
      xml_out.close();
      xml_in.close();

      // Time to bolt
      Chroma::finalize();

      exit(0);
}
