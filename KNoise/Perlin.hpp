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
								// Currently nothing is tested here if selected enables array cache
		};

		void SetCacheType(int F_CacheType);
		void ClearCache();
		
		float Get(Vec3f F_Position, unsigned int F_Seed);		// Get noise value for set seed and position
		double Get(Vec3d F_Position, unsigned int F_Seed);		// Get double precision noise value for set seed and position

		float GetFractal(Vec3f F_Position, unsigned int F_Seed, unsigned int F_Quality);	// IDK if it works but i hope so
		double GetFractal(Vec3d F_Position, unsigned int F_Seed, unsigned int F_Quality);	// IDK if it works but i hope so

    private:

		struct SeedCache {

			struct PTable {								// Permutation Table ( array with random numbers )
				unsigned int Seed = 0;					// Generated PTable seed
				std::vector<unsigned int> Permutation;	// Permutation
				bool Created = false;					// Was PTable generated?

				PTable(unsigned int F_Seed);			// Generate new PTable
				PTable();								// Allocate memory for PTable
			};

			// Thiese functions are implemented by other cache strategies
			virtual PTable* GetPTable(unsigned int F_Seed) = 0;	// This function returns PTable for given seed
			virtual void Clear() = 0;							// This function clears cache (if there is any cache)

		};


		struct DisabledCacheStrategy : public SeedCache {
			PTable* GetPTable(unsigned int F_Seed) override;
			void Clear() override;
		};

		struct SingleCacheStrategy : public SeedCache {
			PTable LastPTable;

			PTable* GetPTable(unsigned int F_Seed) override;
			void Clear() override;
		};

		struct ArrayCacheStrategy : public SeedCache {
			std::vector<PTable> Cache;

			PTable* GetPTable(unsigned int F_Seed) override;
			void Clear() override;
		};

		struct FastArrayCacheStrategy : public SeedCache {
			std::vector<PTable> Cache;

			PTable* GetPTable(unsigned int F_Seed) override;
			void Clear() override;
		};

		struct ExperimentalCacheStrategy : public SeedCache {
			PTable LastPTable;

			PTable* GetPTable(unsigned int F_Seed) override;
			void Clear() override;
		};


		std::unique_ptr<SeedCache> Seed;


		float Fade(float t);
		float Lerp(float t, float a, float b);
		float Grad(int hash, float x, float y, float z);

		double FadeD(double t);
		double LerpD(double t, double a, double b);
		double GradD(int hash, double x, double y, double z);

	};

}


#endif