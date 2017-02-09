#include "cma_optimizer.hpp"

#include "flut/system/assert.hpp"
#include <algorithm>

static void FATAL( char const *s1, char const *s2, char const *s3, char const *s4 )
{
	FLUT_EXCEPTION( std::string( s1 ) + s2 + s3 + s4 );
}


namespace flut
{
	typedef std::vector< double > dbl_vec;

	struct cmaes_random_t
	{
	  /* Variables for Uniform() */
	  long int startseed;
	  long int aktseed;
	  long int aktrand;
	  std::vector< long int > rgrand;
  
	  /* Variables for Gauss() */
	  short flgstored;
	  double hold;
	};



	struct cmaes_readpara_t
	{
		//char * filename;  /* keep record of the file that was taken to read parameters */
		//short flgsupplemented;

		/* input parameters */
		int N; /* problem dimension, must stay constant, should be unsigned or long? */
		unsigned int seed;
		dbl_vec xstart;
		dbl_vec typicalX;
		int typicalXcase;
		dbl_vec rgInitialStds;
		double * rgDiffMinChange;

		/* termination parameters */
		double stopMaxFunEvals;
		double facmaxeval;
		double stopMaxIter;
		struct { int flg; double val; } stStopFitness;
		double stopTolFun;
		double stopTolFunHist;
		double stopTolX;
		double stopTolUpXFactor;

		/* internal evolution strategy parameters */
		int lambda;          /* -> mu, <- N */
		int mu;              /* -> weights, (lambda) */
		double mucov, mueff; /* <- weights */
		dbl_vec weights;     /* <- mu, -> mueff, mucov, ccov */
		double damps;        /* <- cs, maxeval, lambda */
		double cs;           /* -> damps, <- N */
		double ccumcov;      /* <- N */
		double ccov;         /* <- mucov, <- N */
		double diagonalCov;  /* number of initial iterations */
		struct { int flgalways; double modulo; double maxtime; } updateCmode;
		double facupdateCmode;

		/* supplementary variables */

		char *weigkey;
		//char resumefile[ 99 ];
		//const char **rgsformat;
		//void **rgpadr;
		//const char **rgskeyar;
		//double ***rgp2adr;
		//int n1para, n1outpara;
		//int n2para;
	};



	struct cmaes_t
	{
		const char *version;
		/* char *signalsFilename; */
		cmaes_readpara_t sp;
		cmaes_random_t rand; /* random number generator */

		double sigma;  /* step size */

		dbl_vec rgxmean;  /* mean x vector, "parent" */
		dbl_vec rgxbestever;
		std::vector< dbl_vec > rgrgx;   /* range of x-vectors, lambda offspring */
		std::vector< int > index;       /* sorting index of sample pop. */
		dbl_vec arFuncValueHist;

		short flgIniphase; /* not really in use anymore */
		short flgStop;

		double chiN;
		std::vector< dbl_vec > C;  /* lower triangular matrix: i>=j for C[i][j] */
		std::vector< dbl_vec > B;  /* matrix with normalize eigenvectors in columns */
		dbl_vec rgD; /* axis lengths */

		dbl_vec rgpc;
		dbl_vec rgps;
		dbl_vec rgxold;
		dbl_vec rgout;
		dbl_vec rgBDz;   /* for B*D*z */
		dbl_vec rgdTmp;  /* temporary (random) vector used in different places */
		dbl_vec rgFuncValue;
		dbl_vec publicFitness; /* returned by cmaes_init() */

		double gen; /* Generation number */
		double countevals;
		double state; /* 1 == sampled, 2 == not in use anymore, 3 == updated */

		double maxdiagC; /* repeatedly used for output */
		double mindiagC;
		double maxEW;
		double minEW;

		char sOutString[ 330 ]; /* 4x80 */

		short flgEigensysIsUptodate;
		short flgCheckEigen; /* control via cmaes_signals.par */
		double genOfEigensysUpdate;

		double dMaxSignifKond;
		double dLastMinEWgroesserNull;

		short flgresumedone;
	};



	long cmaes_random_init( cmaes_random_t *t, long unsigned inseed )
	{
		t->flgstored = 0;
		t->rgrand.resize( 32 );

		t->flgstored = 0;
		t->startseed = inseed; /* purely for bookkeeping */
		while ( inseed > 2e9 )
			inseed /= 2; /* prevent infinite loop on 32 bit system */
		if ( inseed < 1 )
			inseed = 1;
		t->aktseed = inseed;
		for ( long i = 39; i >= 0; --i )
		{
			long tmp = t->aktseed / 127773;
			t->aktseed = 16807 * ( t->aktseed - tmp * 127773 )
				- 2836 * tmp;
			if ( t->aktseed < 0 ) t->aktseed += 2147483647;
			if ( i < 32 )
				t->rgrand[ i ] = t->aktseed;
		}
		t->aktrand = t->rgrand[ 0 ];
		return inseed;
	}



	void cmaes_readpara_SetWeights( cmaes_readpara_t *t, const char * mode )
	{
		double s1, s2;
		int i;

		t->weights.resize( t->mu );
		if ( strcmp( mode, "lin" ) == 0 )
			for ( i = 0; i < t->mu; ++i )
				t->weights[ i ] = t->mu - i;
		else if ( strncmp( mode, "equal", 3 ) == 0 )
			for ( i = 0; i < t->mu; ++i )
				t->weights[ i ] = 1;
		else if ( strcmp( mode, "log" ) == 0 )
			for ( i = 0; i < t->mu; ++i )
				t->weights[ i ] = log( t->mu + 1. ) - log( i + 1. );
		else
			for ( i = 0; i < t->mu; ++i )
				t->weights[ i ] = log( t->mu + 1. ) - log( i + 1. );

		/* normalize weights vector and set mueff */
		for ( i = 0, s1 = 0, s2 = 0; i < t->mu; ++i ) {
			s1 += t->weights[ i ];
			s2 += t->weights[ i ] * t->weights[ i ];
		}
		t->mueff = s1*s1 / s2;
		for ( i = 0; i < t->mu; ++i )
			t->weights[ i ] /= s1;

		if ( t->mu < 1 || t->mu > t->lambda ||
			( t->mu == t->lambda && t->weights[ 0 ] == t->weights[ t->mu - 1 ] ) )
			FATAL( "cmaes_readpara_SetWeights(): invalid setting of mu or lambda", 0, 0, 0 );

	} /* cmaes_readpara_SetWeights() */



	double cmaes_random_Uniform( cmaes_random_t *t )
	{
		long tmp;

		tmp = t->aktseed / 127773;
		t->aktseed = 16807 * ( t->aktseed - tmp * 127773 ) - 2836 * tmp;
		if ( t->aktseed < 0 )
			t->aktseed += 2147483647;
		tmp = t->aktrand / 67108865;
		t->aktrand = t->rgrand[ tmp ];
		t->rgrand[ tmp ] = t->aktseed;
		return (double)( t->aktrand ) / ( 2.147483647e9 );
	}

	double cmaes_random_Gauss( cmaes_random_t *t )
	{
		double x1, x2, rquad, fac;

		if ( t->flgstored )
		{
			t->flgstored = 0;
			return t->hold;
		}
		do
		{
			x1 = 2.0 * cmaes_random_Uniform( t ) - 1.0;
			x2 = 2.0 * cmaes_random_Uniform( t ) - 1.0;
			rquad = x1*x1 + x2*x2;
		}
		while ( rquad >= 1 || rquad <= 0 );
		fac = sqrt( -2.0*log( rquad ) / rquad );
		t->flgstored = 1;
		t->hold = fac * x1;
		return fac * x2;
	}



	void cmaes_init_all( cmaes_t *t,
			int dim,
			const double * inxstart,
			const double * inrgsigma,
			int inseed,
			int lambda,
			const char * filename )
	{
		//
		// void cmaes_readpara_init
		//

		t->sp.N = dim;
		t->sp.seed = (unsigned)inseed;
		t->sp.typicalXcase = 0;
		t->sp.rgDiffMinChange = NULL;
		t->sp.stopMaxFunEvals = -1;
		t->sp.stopMaxIter = -1;
		t->sp.facmaxeval = 1;
		t->sp.stStopFitness.flg = -1;
		t->sp.stopTolFun = 1e-12;
		t->sp.stopTolFunHist = 1e-13;
		t->sp.stopTolX = 0; /* 1e-11*insigma would also be reasonable */
		t->sp.stopTolUpXFactor = 1e3;

		t->sp.lambda = lambda;
		t->sp.mu = -1;
		t->sp.mucov = -1;
		strcpy( t->sp.weigkey, "log" );

		t->sp.cs = -1;
		t->sp.ccumcov = -1;
		t->sp.damps = -1;
		t->sp.ccov = -1;

		t->sp.diagonalCov = 0; /* default is 0, but this might change in future, see below */

		t->sp.updateCmode.modulo = -1;
		t->sp.updateCmode.maxtime = -1;
		t->sp.updateCmode.flgalways = 0;
		t->sp.facupdateCmode = 1;

		int N = t->sp.N;

		if ( t->sp.xstart.empty() ) {
			t->sp.xstart.resize( N );

			/* put inxstart into xstart */
			if ( inxstart != NULL ) {
				for ( int i = 0; i < N; ++i )
					t->sp.xstart[ i ] = inxstart[ i ];
			}
		} /* xstart == NULL */

		if ( t->sp.rgInitialStds.empty() ) {
			t->sp.rgInitialStds.resize( N );
			for ( int i = 0; i < N; ++i )
				t->sp.rgInitialStds[ i ] = ( inrgsigma == NULL ) ? 0.3 : inrgsigma[ i ];
		}

		//
		// void cmaes_readpara_SupplementDefaults( cmaes_readpara_t *t )
		//

		double t1, t2;
		if ( t->sp.stStopFitness.flg == -1 )
			t->sp.stStopFitness.flg = 0;

		if ( t->sp.lambda < 2 )
			t->sp.lambda = 4 + (int)( 3 * log( (double)N ) );

		if ( t->sp.mu == -1 )
			t->sp.mu = t->sp.lambda / 2;

		if ( t->sp.weights.empty() )
			cmaes_readpara_SetWeights( &t->sp, t->sp.weigkey );

		if ( t->sp.cs > 0 ) /* factor was read */
			t->sp.cs *= ( t->sp.mueff + 2. ) / ( N + t->sp.mueff + 3. );
		if ( t->sp.cs <= 0 || t->sp.cs >= 1 )
			t->sp.cs = ( t->sp.mueff + 2. ) / ( N + t->sp.mueff + 3. );

		if ( t->sp.ccumcov <= 0 || t->sp.ccumcov > 1 )
			t->sp.ccumcov = 4. / ( N + 4 );

		if ( t->sp.mucov < 1 ) {
			t->sp.mucov = t->sp.mueff;
		}
		t1 = 2. / ( ( N + 1.4142 )*( N + 1.4142 ) );
		t2 = ( 2.*t->sp.mueff - 1. ) / ( ( N + 2. )*( N + 2. ) + t->sp.mueff );
		t2 = ( t2 > 1 ) ? 1 : t2;
		t2 = ( 1. / t->sp.mucov ) * t1 + ( 1. - 1. / t->sp.mucov ) * t2;
		if ( t->sp.ccov >= 0 ) /* ccov holds the read factor */
			t->sp.ccov *= t2;
		if ( t->sp.ccov < 0 || t->sp.ccov > 1 ) /* set default in case */
			t->sp.ccov = t2;

		if ( t->sp.diagonalCov == -1 )
			t->sp.diagonalCov = 2 + 100. * N / sqrt( (double)t->sp.lambda );

		if ( t->sp.stopMaxFunEvals == -1 )  /* may depend on ccov in near future */
			t->sp.stopMaxFunEvals = t->sp.facmaxeval * 900 * ( N + 3 )*( N + 3 );
		else
			t->sp.stopMaxFunEvals *= t->sp.facmaxeval;

		if ( t->sp.stopMaxIter == -1 )
			t->sp.stopMaxIter = ceil( (double)( t->sp.stopMaxFunEvals / t->sp.lambda ) );

		if ( t->sp.damps < 0 )
			t->sp.damps = 1; /* otherwise a factor was read */
		t->sp.damps = t->sp.damps
			* ( 1 + 2 * std::max( 0., sqrt( ( t->sp.mueff - 1. ) / ( N + 1. ) ) - 1 ) )     /* basic factor */
			* std::max( 0.3, 1. -                                       /* modify for short runs */
			(double)N / ( 1e-6 + std::min( t->sp.stopMaxIter, t->sp.stopMaxFunEvals / t->sp.lambda ) ) )
			+ t->sp.cs;                                                 /* minor increment */

		if ( t->sp.updateCmode.modulo < 0 )
			t->sp.updateCmode.modulo = 1. / t->sp.ccov / (double)( N ) / 10.;
		t->sp.updateCmode.modulo *= t->sp.facupdateCmode;
		if ( t->sp.updateCmode.maxtime < 0 )
			t->sp.updateCmode.maxtime = 0.20; /* maximal 20% of CPU-time */

		// 
		// cmaes_init_final()
		//

		int i, j;
		double dtest, trace;

		t->sp.seed = cmaes_random_init( &t->rand, ( long unsigned int ) t->sp.seed );

		N = t->sp.N; /* for convenience */

		/* initialization  */
		for ( i = 0, trace = 0.; i < N; ++i )
			trace += t->sp.rgInitialStds[ i ] * t->sp.rgInitialStds[ i ];
		t->sigma = sqrt( trace / N ); /* t->sp.mueff/(0.2*t->sp.mueff+sqrt(N)) * sqrt(trace/N); */

		t->chiN = sqrt( (double)N ) * ( 1. - 1. / ( 4.*N ) + 1. / ( 21.*N*N ) );
		t->flgEigensysIsUptodate = 1;
		t->flgCheckEigen = 0;
		t->genOfEigensysUpdate = 0;
		t->flgIniphase = 0; /* do not use iniphase, hsig does the job now */
		t->flgresumedone = 0;
		t->flgStop = 0;

		for ( dtest = 1.; dtest && dtest < 1.1 * dtest; dtest *= 2. )
			if ( dtest == dtest + 1. )
				break;
		t->dMaxSignifKond = dtest / 1000.; /* not sure whether this is really save, 100 does not work well enough */

		t->gen = 0;
		t->countevals = 0;
		t->state = 0;
		t->dLastMinEWgroesserNull = 1.0;

		t->rgpc.resize( N );
		t->rgps.resize( N );
		t->rgdTmp.resize( N + 1 );
		t->rgBDz.resize( N );
		t->rgxmean.resize( N + 2 ); // WTF? t->rgxmean[ 0 ] = N; ++t->rgxmean;
		t->rgxold.resize( N + 2 ); // WTF? t->rgxold[ 0 ] = N; ++t->rgxold;
		t->rgxbestever.resize( N + 3 ); // WTF? t->rgxbestever[ 0 ] = N; ++t->rgxbestever;
		t->rgout.resize( N + 2 ); // WTF? t->rgout[ 0 ] = N; ++t->rgout;
		t->rgD.resize( N );
		t->C.resize( N );
		t->B.resize( N );
		t->publicFitness.resize( t->sp.lambda );
		t->rgFuncValue.resize( t->sp.lambda + 1 ); // WTF? t->rgFuncValue[ 0 ] = t->sp.lambda; ++t->rgFuncValue;
		t->arFuncValueHist.resize( 10 + (int)ceil( 3.*10.*N / t->sp.lambda ) + 1 );
		// WTF? t->arFuncValueHist[ 0 ] = (double)( 10 + (int)ceil( 3.*10.*N / t->sp.lambda ) ); t->arFuncValueHist++;

		for ( i = 0; i < N; ++i ) {
			t->C[ i ].resize( i + 1 );
			t->B[ i ].resize( N );
		}
		t->index.resize( t->sp.lambda );
		for ( i = 0; i < t->sp.lambda; ++i )
			t->index[ i ] = i; /* should not be necessary */
		t->rgrgx.resize( t->sp.lambda );
		for ( i = 0; i < t->sp.lambda; ++i ) {
			t->rgrgx[ i ].resize( N + 2 ); // WTF? t->rgrgx[ i ][ 0 ] = N; t->rgrgx[ i ]++;
		}

		/* Initialize newed space  */

		for ( i = 0; i < N; ++i )
			for ( j = 0; j < i; ++j )
				t->C[ i ][ j ] = t->B[ i ][ j ] = t->B[ j ][ i ] = 0.;

		for ( i = 0; i < N; ++i )
		{
			t->B[ i ][ i ] = 1.;
			t->C[ i ][ i ] = t->rgD[ i ] = t->sp.rgInitialStds[ i ] * sqrt( N / trace );
			t->C[ i ][ i ] *= t->C[ i ][ i ];
			t->rgpc[ i ] = t->rgps[ i ] = 0.;
		}

		t->minEW = *std::min_element( t->rgD.begin(), t->rgD.end() );
		t->minEW = t->minEW * t->minEW;
		t->maxEW = *std::max_element( t->rgD.begin(), t->rgD.end() );
		t->maxEW = t->maxEW * t->maxEW;

		t->maxdiagC = t->C[ 0 ][ 0 ]; for ( i = 1; i < N; ++i ) if ( t->maxdiagC < t->C[ i ][ i ] ) t->maxdiagC = t->C[ i ][ i ];
		t->mindiagC = t->C[ 0 ][ 0 ]; for ( i = 1; i < N; ++i ) if ( t->mindiagC > t->C[ i ][ i ] ) t->mindiagC = t->C[ i ][ i ];

		/* set xmean */
		for ( i = 0; i < N; ++i )
			t->rgxmean[ i ] = t->rgxold[ i ] = t->sp.xstart[ i ];
		/* use in case xstart as typicalX */
		if ( t->sp.typicalXcase )
			for ( i = 0; i < N; ++i )
				t->rgxmean[ i ] += t->sigma * t->rgD[ i ] * cmaes_random_Gauss( &t->rand );
	}



	cma_optimizer::cma_optimizer( int dim, const real_vec& init_mean, const real_vec& init_std, objective_func_t func, cma_weights w ) :
	optimizer( dim, func )
	{ }

	cma_optimizer::cma_optimizer( int dim, const real_vec& init_mean, const real_vec& init_std, const real_vec& lower_bounds, const real_vec& upper_bounds, objective_func_t func, cma_weights w ) :
	optimizer( dim, lower_bounds, upper_bounds, func )
	{ }
}

