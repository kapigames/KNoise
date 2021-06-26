// Deafult class for other noise classes
// This makes changing noise type easier
// (if they would exist)


#ifndef _KNOISE_
#define _KNOISE_

#include "kstd.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <future>


namespace KNoise {

    struct Perlin {

		struct Seed {

			struct PTable {
				unsigned int Seed = 0;
				std::vector<unsigned int> Permutation;
				bool Created = false;

				PTable(int F_Seed);				// Generate new PTable
				PTable();						// Allocate memory for PTable
			};
			
			enum CacheType {
				None,				// Seed cache is disabled
				Deafult,			// Deafult seed cache cache is stored in array which is then searched to find ptable
				Fast,				// Seed = cache array index much faster but uses alot of memory if not used corectly
				Experimental		// Experimental features
			};

			std::vector<PTable> Cache;			// Seed cache array

			CacheType CacheID = None;			// Currently used seed cache

			int AllocationSize = 32;

			Seed::PTable* GetPTable(int F_Seed);		// Get PTable using set seed cache
			Seed::PTable LastPTable;

			void ResetCache();							// Reset cache
			void SetCacheType(CacheType F_CacheID);		// Set cache type
		};

		Seed Seed;

		float Get(kstd::vec3f F_Position, int F_Seed);
		double Get(kstd::vec3d F_Position, int F_Seed);

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