#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: fbench.alg		*/
/* Compiled at Tue May  1 21:39:03 2018		*/


#include	<stdio.h>
#include "/usr/local/include/jff_header.h"
/* Headers		*/
extern	double sqrt (double); /* sqrt declared at line 5*/
extern	double sin (double); /* sin declared at line 6*/
extern	double cos (double); /* cos declared at line 7*/
extern	double arctan (double); /* arctan declared at line 8*/
extern	void outstring (int,char	*); /* outstring declared at line 26*/
extern	void outinteger (int,int); /* outinteger declared at line 40*/
extern	void outreal_16_11 (int,double); /* outreal_16_11 declared at line 47*/
extern int _a_line_41; /* a_line declared at line 33*/
extern int _b_line_41; /* b_line declared at line 33*/
extern int _c_line_41; /* c_line declared at line 33*/
extern int _d_line_41; /* d_line declared at line 33*/
extern int _e_line_41; /* e_line declared at line 34*/
extern int _f_line_41; /* f_line declared at line 34*/
extern int _g_prime_line_41; /* g_prime_line declared at line 34*/
extern int _h_line_41; /* h_line declared at line 35*/
extern double _spectral_line_41 []; // 
extern int _current_surfaces_41; /* current_surfaces declared at line 38*/
extern	int __dv0 [];
extern double	*_test_case_41; /* test_case declared at line 39*/
extern int _curvature_radius_41; /* curvature_radius declared at line 40*/
extern int _index_of_refraction_41; /* index_of_refraction declared at line 40*/
extern int _dispersion_41; /* dispersion declared at line 40*/
extern int _edge_thickness_41; /* edge_thickness declared at line 41*/
extern double _clear_aperture_41; /* clear_aperture declared at line 43*/
extern double _aber_lspher_41; /* aber_lspher declared at line 43*/
extern double _aberr_osc_41; /* aberr_osc declared at line 43*/
extern double _aberr_lchrom_41; /* aberr_lchrom declared at line 43*/
extern double _max_lspher_41; /* max_lspher declared at line 44*/
extern double _mac_osc_41; /* mac_osc declared at line 44*/
extern double _max_lchrom_41; /* max_lchrom declared at line 44*/
extern double _radius_of_curvature_41; /* radius_of_curvature declared at line 44*/
extern double _object_distance_41; /* object_distance declared at line 45*/
extern double _ray_height_41; /* ray_height declared at line 45*/
extern double _axis_slope_angle_41; /* axis_slope_angle declared at line 45*/
extern double _from_index_41; /* from_index declared at line 46*/
extern double _to_index_41; /* to_index declared at line 46*/
extern int _number_of_iterations_41; /* number_of_iterations declared at line 48*/
extern int _iteration_41; /* iteration declared at line 48*/
extern int _paraxial_41; /* paraxial declared at line 50*/
extern int _marginal_ray_41; /* marginal_ray declared at line 50*/
extern int _paraxial_ray_41; /* paraxial_ray declared at line 50*/
extern int _of_field_41; /* of_field declared at line 59*/
extern int _sa_field_41; /* sa_field declared at line 59*/
extern	int __dv1 [];
extern double	*_od_sa_41; /* od_sa declared at line 60*/
extern double _od_cline_41; /* od_cline declared at line 62*/
extern double _od_fline_41; /* od_fline declared at line 62*/
extern	double _cot_42 (double); /* cot declared at line 68*/
extern	double _arc_sin_44 (double); /* arc_sin declared at line 79*/
extern	void _outbigreal_46 (int,double); /* outbigreal declared at line 114*/
extern	void _transit_surface_48 (); /* transit_surface declared at line 161*/
extern	void _trace_line_51 (int,double); /* trace_line declared at line 225*/
