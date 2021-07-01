#ifndef _KNOISE_
#define _KNOISE_

#include <vector>
#include <random>
#include <algorithm>
#include <numeric>


namespace KNoise {

    struct Vec3f {
        Vec3f(float F_x,float F_y,float F_z) { x=F_x; y=F_y; z=F_z; }
        float x, y, z;
    };

    struct Vec3d {
        Vec3d(double F_x,double F_y,double F_z) { x=F_x; y=F_y; z=F_z; }
        double x, y, z;
    };

    struct Perlin {

		struct Seed {

			struct PTable {								// Permutation Table ( array with random numbers )
				unsigned int Seed = 0;					// Generated PTable seed
				std::vector<unsigned int> Permutation;	// Permutation
				bool Created = false;					// Was PTable generated?

				PTable(int F_Seed);				// Generate new PTable
				PTable();						// Allocate memory for PTable
			};
			
			enum CacheType {		// Seed cache types, Deafult is recomended
				None,				// Seed cache is disabled
				Deafult,			// Deafult seed cache cache is stored in array which is then searched to find ptable
				Fast,				// Seed = cache array index much faster but uses alot of memory if not used corectly
				Experimental		// Experimental features
			};

			std::vector<PTable> Cache;			// Seed cache array

			CacheType CacheID = None;			// Currently used seed cache

			int AllocationSize = 32;			// How much extra memory allocate in cache array

			Seed::PTable* GetPTable(unsigned int F_Seed);		// Get PTable using set seed cache
			Seed::PTable LastPTable;					// Last used PTable when cache is disabled

			void ResetCache();							// Reset cache
			void SetCacheType(CacheType F_CacheID);		// Set cache type
		};

		Seed Seed;

		float Get(Vec3f F_Position, int F_Seed);		// Get noise value for set seed and position
		double Get(Vec3d F_Position, int F_Seed);		// Get double precision noise value for set seed and position

    private:
		float Fade(float t);
		float Lerp(float t, float a, float b);
		float Grad(int hash, float x, float y, float z);

		double FadeD(double t);
		double LerpD(double t, double a, double b);
		double GradD(int hash, double x, double y, double z);
	};

}


#endif