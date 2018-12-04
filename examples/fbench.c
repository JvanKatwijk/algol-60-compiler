#

/* jff_algol (Jan van Katwijk) */
/* Version 2.1.1		*/
/* input file: fbench.alg		*/
/* Compiled at Tue May  1 21:39:03 2018		*/


#include	<stdio.h>
#include "fbench.h"

//      Code for the global declarations

int _a_line_41;			/* a_line declared at line 33 */
int _b_line_41;			/* b_line declared at line 33 */
int _c_line_41;			/* c_line declared at line 33 */
int _d_line_41;			/* d_line declared at line 33 */
int _e_line_41;			/* e_line declared at line 34 */
int _f_line_41;			/* f_line declared at line 34 */
int _g_prime_line_41;		/* g_prime_line declared at line 34 */
int _h_line_41;			/* h_line declared at line 35 */
double _spectral_line_41[8 - 1 + 1];	/* spectral_line declared at line 36 */
int _current_surfaces_41;	/* current_surfaces declared at line 38 */
int __dv0[2 * 2 + DOPE_BASE];
double *_test_case_41;		/* test_case declared at line 39 */
int _curvature_radius_41;	/* curvature_radius declared at line 40 */
int _index_of_refraction_41;	/* index_of_refraction declared at line 40 */
int _dispersion_41;		/* dispersion declared at line 40 */
int _edge_thickness_41;		/* edge_thickness declared at line 41 */
double _clear_aperture_41;	/* clear_aperture declared at line 43 */
double _aber_lspher_41;		/* aber_lspher declared at line 43 */
double _aberr_osc_41;		/* aberr_osc declared at line 43 */
double _aberr_lchrom_41;	/* aberr_lchrom declared at line 43 */
double _max_lspher_41;		/* max_lspher declared at line 44 */
double _mac_osc_41;		/* mac_osc declared at line 44 */
double _max_lchrom_41;		/* max_lchrom declared at line 44 */
double _radius_of_curvature_41;	/* radius_of_curvature declared at line 44 */
double _object_distance_41;	/* object_distance declared at line 45 */
double _ray_height_41;		/* ray_height declared at line 45 */
double _axis_slope_angle_41;	/* axis_slope_angle declared at line 45 */
double _from_index_41;		/* from_index declared at line 46 */
double _to_index_41;		/* to_index declared at line 46 */
int _number_of_iterations_41;	/* number_of_iterations declared at line 48 */
int _iteration_41;		/* iteration declared at line 48 */
int _paraxial_41;		/* paraxial declared at line 50 */
int _marginal_ray_41;		/* marginal_ray declared at line 50 */
int _paraxial_ray_41;		/* paraxial_ray declared at line 50 */
int _of_field_41;		/* of_field declared at line 59 */
int _sa_field_41;		/* sa_field declared at line 59 */
int __dv1[2 * 2 + DOPE_BASE];
double *_od_sa_41;		/* od_sa declared at line 60 */
double _od_cline_41;		/* od_cline declared at line 62 */
double _od_fline_41;		/* od_fline declared at line 62 */
 /* cot declared at line 68 */
double
_cot_42 (double x)
{
  double __res_val;
  __res_val = ((double) (1)) / ((sin (x)) / (cos (x)));
  return __res_val;

}

 /* arc_sin declared at line 79 */
double
_arc_sin_44 (double x)
{
  double __res_val;
  __res_val =
    ((double) (2)) *
    (arctan
     ((x) / (((double) (1)) + (sqrt (((double) 1) - (__npow (x, 2)))))));
  return __res_val;

}

 /* outbigreal declared at line 114 */
void
_outbigreal_46 (int channel, double x)
{
  outreal_16_11 (channel, x);
  ;				// null statement 

}

 /* transit_surface declared at line 161 */
void
_transit_surface_48 ()
{
  double _iang_50;
  double _rang_50;
  double _iang_sin_50;
  double _rang_sin_50;
  double _old_axis_slope_angle_50;
  double _sagitta_50;

  {				// code for block at line 163
    if ((_paraxial_41) == (_paraxial_ray_41))
      if ((_radius_of_curvature_41) != ((double) (0)))
	{
	  if ((_object_distance_41) == ((double) (0)))
	    {
	      _axis_slope_angle_41 = (double) (0);
	      _iang_sin_50 = (_ray_height_41) / (_radius_of_curvature_41);
	    }

	  else
	    _iang_sin_50 =
	      (((_object_distance_41) -
		(_radius_of_curvature_41)) / (_radius_of_curvature_41)) *
	      (_axis_slope_angle_41);
	  _rang_sin_50 = ((_from_index_41) / (_to_index_41)) * (_iang_sin_50);
	  _old_axis_slope_angle_50 = _axis_slope_angle_41;
	  _axis_slope_angle_41 =
	    ((_axis_slope_angle_41) + (_iang_sin_50)) - (_rang_sin_50);
	  if ((_object_distance_41) != ((double) (0)))
	    _ray_height_41 =
	      (_object_distance_41) * (_old_axis_slope_angle_50);
	  _object_distance_41 = (_ray_height_41) / (_axis_slope_angle_41);
	}

      else
	{
	  _object_distance_41 =
	    (_object_distance_41) * ((_to_index_41) / (_from_index_41));
	  _axis_slope_angle_41 =
	    (_axis_slope_angle_41) * ((_from_index_41) / (_to_index_41));
	}

    else if ((_radius_of_curvature_41) != ((double) (0)))
      {
	if ((_object_distance_41) == ((double) (0)))
	  {
	    _axis_slope_angle_41 = (double) (0);
	    _iang_sin_50 = (_ray_height_41) / (_radius_of_curvature_41);
	  }

	else
	  _iang_sin_50 =
	    (((_object_distance_41) -
	      (_radius_of_curvature_41)) / (_radius_of_curvature_41)) *
	    (sin (_axis_slope_angle_41));
	_iang_50 = _arc_sin_44 (_iang_sin_50);
	_rang_sin_50 = ((_from_index_41) / (_to_index_41)) * (_iang_sin_50);
	_old_axis_slope_angle_50 = _axis_slope_angle_41;
	_axis_slope_angle_41 =
	  ((_axis_slope_angle_41) + (_iang_50)) -
	  (_arc_sin_44 (_rang_sin_50));
	_sagitta_50 =
	  sin (((_old_axis_slope_angle_50) + (_iang_50)) / ((double) (2)));
	_sagitta_50 =
	  (((double) (2)) * (_radius_of_curvature_41)) *
	  (__npow (_sagitta_50, 2));
	_object_distance_41 =
	  (((_radius_of_curvature_41) *
	    (sin ((_old_axis_slope_angle_50) + (_iang_50)))) *
	   (_cot_42 (_axis_slope_angle_41))) + (_sagitta_50);
      }

    else
      {
	_rang_50 =
	  -(_arc_sin_44
	    (((_from_index_41) / (_to_index_41)) *
	     (sin (_axis_slope_angle_41))));
	_object_distance_41 =
	  (_object_distance_41) * (((_to_index_41) * (cos (-(_rang_50)))) /
				   ((_from_index_41) *
				    (cos (_axis_slope_angle_41))));
	_axis_slope_angle_41 = -(_rang_50);
      }
  }

}

 /* trace_line declared at line 225 */
void
_trace_line_51 (int line, double ray_h)
{
  int _i_53;

  {				// code for block at line 230
    _object_distance_41 = (double) (0);
    _ray_height_41 = ray_h;
    _from_index_41 = (double) (1);
    for (_i_53 = 1; (_i_53 - (_current_surfaces_41)) * sign ((double) 1) <= 0;
	 _i_53 += 1)
      {
	_radius_of_curvature_41 =
	  *(double *) __jff_element_address (_test_case_41, __dv0, 2, _i_53,
					     _curvature_radius_41);
	_to_index_41 =
	  *(double *) __jff_element_address (_test_case_41, __dv0, 2, _i_53,
					     _index_of_refraction_41);
	if ((_to_index_41) > ((double) (1)))
	  _to_index_41 =
	    (_to_index_41) +
	    ((((_spectral_line_41[_d_line_41 - 1]) -
	       (_spectral_line_41[line - 1])) /
	      ((_spectral_line_41[_c_line_41 - 1]) -
	       (_spectral_line_41[_f_line_41 - 1]))) *
	     (((*(double *)
		__jff_element_address (_test_case_41, __dv0, 2, _i_53,
				       _index_of_refraction_41)) -
	       (1.0)) / (*(double *) __jff_element_address (_test_case_41,
							    __dv0, 2, _i_53,
							    _dispersion_41))));
	_transit_surface_48 ();
	_from_index_41 = _to_index_41;
	if ((_i_53) < (_current_surfaces_41))
	  _object_distance_41 =
	    (_object_distance_41) -
	    (*(double *)
	     __jff_element_address (_test_case_41, __dv0, 2, _i_53,
				    _edge_thickness_41));
      }
  }

}


// The main program
int
main ()
{
  char *LP = (char *) NULL;

  {				// code for block at line 33
    __dv0[0] = (2 * 256) + sizeof (double);
    __dv0[DOPE_BASE + 0] = 1;
    __dv0[DOPE_BASE + 1] = 4;
    __dv0[DOPE_BASE + 2] = 1;
    __dv0[DOPE_BASE + 3] = 4;
    __dv_init (__dv0);
    _test_case_41 = (double *) __jff_allocate_array (__dv0, LP);
    __dv1[0] = (2 * 256) + sizeof (double);
    __dv1[DOPE_BASE + 0] = 1;
    __dv1[DOPE_BASE + 1] = 2;
    __dv1[DOPE_BASE + 2] = 1;
    __dv1[DOPE_BASE + 3] = 2;
    __dv_init (__dv1);
    _od_sa_41 = (double *) __jff_allocate_array (__dv1, LP);
    _number_of_iterations_41 = 100000000;
    outstring (1,
	       "Ready to begin John Walker's floating point accuracy and performance benchmark.");
    outinteger (1, _number_of_iterations_41);
    outstring (1, " will be made\n");
    _a_line_41 = 1;
    _b_line_41 = 2;
    _c_line_41 = 3;
    _d_line_41 = 4;
    _e_line_41 = 5;
    _f_line_41 = 6;
    _g_prime_line_41 = 7;
    _h_line_41 = 8;
    _spectral_line_41[_a_line_41 - 1] = 7621.0;
    _spectral_line_41[_b_line_41 - 1] = 6869.955;
    _spectral_line_41[_c_line_41 - 1] = 6562.8160;
    _spectral_line_41[_d_line_41 - 1] = 5895.944;
    _spectral_line_41[_e_line_41 - 1] = 5269.557;
    _spectral_line_41[_f_line_41 - 1] = 4861.344;
    _spectral_line_41[_g_prime_line_41 - 1] = 4340.477;
    _spectral_line_41[_h_line_41 - 1] = 3968.494;
    _current_surfaces_41 = 4;
    _curvature_radius_41 = 1;
    _index_of_refraction_41 = 2;
    _dispersion_41 = 3;
    _edge_thickness_41 = 4;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 1,
				       _curvature_radius_41) = 27.05;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 1,
				       _index_of_refraction_41) = 1.5137;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 1,
				       _dispersion_41) = 63.6;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 1,
				       _edge_thickness_41) = 0.52;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 2,
				       _curvature_radius_41) = -(16.68);
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 2,
				       _index_of_refraction_41) = 1.0;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 2,
				       _dispersion_41) = 0.0;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 2,
				       _edge_thickness_41) = 0.138;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 3,
				       _curvature_radius_41) = -(16.68);
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 3,
				       _index_of_refraction_41) = 1.6164;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 3,
				       _dispersion_41) = 36.7;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 3,
				       _edge_thickness_41) = 0.38;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 4,
				       _curvature_radius_41) = -(78.1);
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 4,
				       _index_of_refraction_41) = 1.0;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 4,
				       _dispersion_41) = 0.0;
    *(double *) __jff_element_address (_test_case_41, __dv0, 2, 4,
				       _edge_thickness_41) = 0.0;
    _marginal_ray_41 = 1;
    _paraxial_ray_41 = 2;
    _of_field_41 = 1;
    _sa_field_41 = 2;
    _clear_aperture_41 = (double) (4);
    for (_iteration_41 = 1;
	 (_iteration_41 - (_number_of_iterations_41)) * sign ((double) 1) <=
	 0; _iteration_41 += 1)
      {
	for (_paraxial_41 = _marginal_ray_41;
	     (_paraxial_41 - (_paraxial_ray_41)) * sign ((double) 1) <= 0;
	     _paraxial_41 += 1)
	  {
	    _trace_line_51 (_d_line_41,
			    (_clear_aperture_41) / ((double) (2)));
	    *(double *) __jff_element_address (_od_sa_41, __dv1, 2,
					       _paraxial_41, _of_field_41) =
	      _object_distance_41;
	    *(double *) __jff_element_address (_od_sa_41, __dv1, 2,
					       _paraxial_41, _sa_field_41) =
	      _axis_slope_angle_41;
	  }
	_paraxial_41 = _marginal_ray_41;
	_trace_line_51 (_c_line_41, (_clear_aperture_41) / ((double) (2)));
	_od_cline_41 = _object_distance_41;
	_trace_line_51 (_f_line_41, (_clear_aperture_41) / ((double) (2)));
	_od_fline_41 = _object_distance_41;
	_aber_lspher_41 =
	  (*(double *)
	   __jff_element_address (_od_sa_41, __dv1, 2, _paraxial_ray_41,
				  _of_field_41)) -
	  (*(double *)
	   __jff_element_address (_od_sa_41, __dv1, 2, _marginal_ray_41,
				  _of_field_41));
	_aberr_osc_41 =
	  ((double) 1) -
	  (((*(double *)
	     __jff_element_address (_od_sa_41, __dv1, 2, _paraxial_ray_41,
				    _of_field_41)) *
	    (*(double *)
	     __jff_element_address (_od_sa_41, __dv1, 2, _paraxial_ray_41,
				    _sa_field_41))) /
	   ((sin
	     (*(double *)
	      __jff_element_address (_od_sa_41, __dv1, 2, _marginal_ray_41,
				     _sa_field_41))) *
	    (*(double *)
	     __jff_element_address (_od_sa_41, __dv1, 2, _marginal_ray_41,
				    _of_field_41))));
	_aberr_lchrom_41 = (_od_fline_41) - (_od_cline_41);
	_max_lspher_41 =
	  (0.0000926) /
	  (__npow
	   (sin
	    (*(double *)
	     __jff_element_address (_od_sa_41, __dv1, 2, _marginal_ray_41,
				    _sa_field_41)), 2));
	_max_lchrom_41 = _max_lspher_41;
	_mac_osc_41 = 0.0025;
      }
    outstring (1, "  Marginal_ray    ");
    _outbigreal_46 (1,
		    *(double *) __jff_element_address (_od_sa_41, __dv1, 2,
						       _marginal_ray_41,
						       _of_field_41));
    outstring (1, "   ");
    _outbigreal_46 (1,
		    *(double *) __jff_element_address (_od_sa_41, __dv1, 2,
						       _marginal_ray_41,
						       _sa_field_41));
    outstring (1, "\n");
    outstring (1, "  Paraxial_ray    ");
    _outbigreal_46 (1,
		    *(double *) __jff_element_address (_od_sa_41, __dv1, 2,
						       _paraxial_ray_41,
						       _of_field_41));
    outstring (1, "   ");
    _outbigreal_46 (1,
		    *(double *) __jff_element_address (_od_sa_41, __dv1, 2,
						       _paraxial_ray_41,
						       _sa_field_41));
    outstring (1, "\n");
    outstring (1, "Longitudinal spherical aberration: ");
    _outbigreal_46 (1, _aber_lspher_41);
    outstring (1, "\n");
    outstring (1, "    (Maximum permissible): ");
    _outbigreal_46 (1, _max_lspher_41);
    outstring (1, "\n");
    outstring (1, "Offense against sine condition (coma): ");
    _outbigreal_46 (1, _aberr_osc_41);
    outstring (1, "\n");
    outstring (1, "    (Maximum permissible): ");
    _outbigreal_46 (1, _mac_osc_41);
    outstring (1, "\n");
    outstring (1, "Axial chromatic aberration: ");
    _outbigreal_46 (1, _aberr_lchrom_41);
    outstring (1, "\n");
    outstring (1, "    (Maximum permissible): ");
    _outbigreal_46 (1, _max_lchrom_41);
    outstring (1, "\n");
    outstring (1, "Measured run time in seconds should be divided by ");
    outinteger (1, (_number_of_iterations_41) / (1000));
    outstring (1, " to normalise for reporting results.\n");
    outstring (1,
	       "For archival results, adjust iteration count so the benchmark runs about five minutes.\n");
    ;				// null statement 
  }
}
