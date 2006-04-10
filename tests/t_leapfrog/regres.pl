#
#  $Id: regres.pl,v 3.1 2006-04-10 21:06:34 edwards Exp $
#
#  This is the portion of a script this is included recursively
#

#
# Each test has a name, input file name, output file name,
# and the good output that is tested against.
#
@regres_list = 
    (
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.unprec_clover.ini.xml" , 
	 output      => "t_leapfrog.unprec_clover.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.unprec_clover.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.unprec_clover.out.xml" ,
     },  
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.prec_2flav_clover.ini.xml" , 
	 output      => "t_leapfrog.prec_2flav_clover.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.prec_2flav_clover.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.prec_2flav_clover.out.xml" ,
     },
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.prec_2flav_clover.sfnonpert.ini.xml" , 
	 output      => "t_leapfrog.prec_2flav_clover.sfnonpert.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.prec_2flav_clover.sfnonpert.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.prec_2flav_clover.sfnonpert.out.xml" ,
     },


     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.prec_2flav_clover_ee_oo.ini.xml" , 
	 output      => "t_leapfrog.prec_2flav_clover.ee_oo_candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.prec_2flav_clover_ee_oo.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.prec_2flav_clover_ee_oo.out.xml" ,
     },


     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.prec_wilson.ini.xml" , 
	 output      => "t_leapfrog.prec_wilson.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.prec_wilson.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.prec_wilson.out.xml" ,
     },
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.prec_parwilson.ini.xml" , 
	 output      => "t_leapfrog.prec_parwilson.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.prec_parwilson.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.prec_parwilson.out.xml" ,
     },

     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.parwilson_pqp_integrator_mts.ini.xml" , 
	 output      => "t_leapfrog.parwilson_pqp_integrator_mts.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.parwilson_pqp_integrator_mts.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.parwilson_pqp_integrator_mts.out.xml" ,
     },
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.parwilson_minimal_norm_2nd_order_integrator_mts.ini.xml" , 
	 output      => "t_leapfrog.parwilson_minimal_norm_2nd_order_integrator_mts.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.parwilson_minimal_norm_2nd_order_integrator_mts.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.parwilson_minimal_norm_2nd_order_integrator_mts.out.xml" ,
     },

     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.parwilson_minimal_norm_2nd_order_qpq_integrator_mts.ini.xml" , 
	 output      => "t_leapfrog.parwilson_minimal_norm_2nd_order_qpq_integrator_mts.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.parwilson_minimal_norm_2nd_order_qpq_integrator_mts.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.parwilson_minimal_norm_2nd_order_qpq_integrator_mts.out.xml" ,
     },

     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.prec_dwf.ini.xml" , 
	 output      => "t_leapfrog.prec_dwf.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.prec_dwf.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.prec_dwf.out.xml" ,
     },
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.prec_contfrac.ini.xml" , 
	 output      => "t_leapfrog.prec_contfrac.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.prec_contfrac.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.prec_contfrac.out.xml" ,
     },
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.unprec_dwf.ini.xml" , 
	 output      => "t_leapfrog.unprec_dwf.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.unprec_dwf.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.unprec_dwf.out.xml" ,
     },
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.unprec_wilson.ini.xml" , 
	 output      => "t_leapfrog.unprec_wilson.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.unprec_wilson.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.unprec_wilson.out.xml" ,
     },
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.unprec_hasenbusch_wilson.ini.xml" , 
	 output      => "t_leapfrog.unprec_hasenbusch_wilson.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.unprec_hasenbusch_wilson.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.unprec_hasenbusch_wilson.out.xml" ,
     },
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.prec_hasenbusch_wilson.ini.xml" , 
	 output      => "t_leapfrog.prec_hasenbusch_wilson.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.prec_hasenbusch_wilson.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.prec_hasenbusch_wilson.out.xml" ,
     },
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.prec_1flav_wilson.ini.xml" , 
	 output      => "t_leapfrog.prec_1flav_wilson.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.prec_1flav_wilson.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.prec_1flav_wilson.out.xml" ,
     },
     {
	 exec_path   => "$top_builddir/mainprogs/tests" , 
	 execute     => "t_leapfrog" , 
	 input       => "$test_dir/t_leapfrog/t_leapfrog.prec_1flav_dwf.ini.xml" , 
	 output      => "t_leapfrog.prec_1flav_dwf.candidate.xml",
	 metric      => "$test_dir/t_leapfrog/t_leapfrog.prec_1flav_dwf.metric.xml" ,
	 controlfile => "$test_dir/t_leapfrog/t_leapfrog.prec_1flav_dwf.out.xml" ,
     }

     );
