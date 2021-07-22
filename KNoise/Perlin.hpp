#ifndef _KNOISE_PERLIN_
#define _KNOISE_PERLIN_

#include "KNoise.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <memory>


#define PERLIN_ALLOCATION_SIZE 32


namespace KNoise {

    struct Perlin {

		Perlin();

		enum CacheType {		// Seed cache types, Deafult is recomended
			Disabled,			// Seed cache is disabled
			Single,				// Only one generated PTable is cached
			Array,				// PTables are stored in array, array needs to be searched to find cached PTable
			FastArray,			// Seed is index of cache array removing need for searching array
								// Faster with large numbers of cached seeds but uses more memory if used incorectly
			Experimental		// Experimental cache implementations that will probably be implemented later after fixing bugs
								// Currently nothing is tested here if selected behaves as single cache
		};

		void SetCacheType(int F_CacheType);						// Sets cache type
		void ClearCache();										// Clears cache (dosent do anything in some cache types)
		
		float Get(Vec3f F_Position, unsigned int F_Seed);		// Get noise value for set seed and position
		double Get(Vec3d F_Position, unsigned int F_Seed);		// Get double precision noise value for set seed and position

		float GetFractal(Vec3f F_Position, unsigned int F_Seed, unsigned int F_Quality);	// IDK if it works but i hope so
		double GetFractal(Vec3d F_Position, unsigned int F_Seed, unsigned int F_Quality);	// IDK if it works but i hope so

    private:

		struct SeedCache {								// Main class for other cache types

			struct PTable {								// Permutation Table ( array with random numbers )
				unsigned int Seed = 0;					// Generated PTable seed
				std::vector<unsigned int> Permutation;	// Permutation
				bool Created = false;					// Was PTable generated?

				PTable(unsigned int F_Seed);			// Generate new PTable
				PTable();								// Allocate memory for PTable
			};

			// These functions are implemented by other cache types
			virtual PTable* GetPTable(unsigned int F_Seed) = 0;	// This function returns PTable for given seed
			virtual void Clear() = 0;							// This function clears cache (if there is any cache)

		};


		struct DisabledCache : public SeedCache {		// Disabled
			PTable* GetPTable(unsigned int F_Seed) override;
			void Clear() override;
		};

		struct SingleCache : public SeedCache {			// Stores last generated PTable
			PTable* GetPTable(unsigned int F_Seed) override;
			void Clear() override;
		
		private:
			PTable LastPTable;
		};

		struct ArrayCache : public SeedCache {			// Stores all generated PTables and thes searches through them can be slow with alot of cached PTables
			PTable* GetPTable(unsigned int F_Seed) override;
			void Clear() override;
		
		private:
			std::vector<PTable> Cache;
		};

		struct FastArrayCache : public SeedCache {		// Same as upper cache type but seed is index of cache array removing the need for searching
			PTable* GetPTable(unsigned int F_Seed) override;
			void Clear() override;
		
		private:
			std::vector<PTable> Cache;
		};

		struct ExperimentalCache : public SeedCache {	// Same as single cache type currently
			PTable* GetPTable(unsigned int F_Seed) override;
			void Clear() override;
		
		private:
		};


		std::unique_ptr<SeedCache> Seed;	// Current cache type

		// These functions are used by Get() function to generate noise
		float Fade(float t);
		float Lerp(float t, float a, float b);
		float Grad(int hash, float x, float y, float z);

		// Double precision version
		double FadeD(double t);
		double LerpD(double t, double a, double b);
		double GradD(int hash, double x, double y, double z);

	};

}


#endif