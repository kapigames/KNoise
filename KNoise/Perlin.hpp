#pragma once

#include "KNoise.hpp"


#define PERLIN_ALLOCATION_SIZE 32


namespace KNoise {

    struct Perlin {

		Perlin();
		~Perlin();

		enum CacheType {		// Seed cache types, Deafult is recomended
			Disabled,			// Seed cache is disabled
			Array,				// PTables are stored in array, array needs to be searched to find cached PTable
			FastArray,			// Seed is index of cache array removing need for searching array
								// Faster with large numbers of cached seeds but uses more memory if used incorectly
			Experimental		// Experimental cache implementations that will probably be implemented later after fixing bugs
								// Currently nothing is tested here if selected behaves as FastArray cache
		};

		void SetCacheType(int F_CacheType);						// Sets cache type
		int GetCacheType();										// Returns cache type
		size_t GetCacheSize();									// Returns cache size (if any)
		void ClearCache();										// Clears cache (dosent do anything in some cache types)
		
		float Get(Vec3f F_Position, unsigned int F_Seed);		// Get noise value for set seed and position
		double Get(Vec3d F_Position, unsigned int F_Seed);		// Get double precision noise value for set seed and position

    private:

		// Main cache class
		struct SeedCache {

			// Cache needs to generate PTable and return it in GetPTable
			struct PTable {								// Permutation Table ( array with random numbers )
				unsigned int Seed = 0;					// Generated PTable seed
				std::vector<unsigned int> Permutation;	// Permutation
				bool Created = false;					// Was PTable generated?

				PTable(unsigned int F_Seed);			// Generate new PTable
				PTable();								// Allocate memory for PTable
			};

			// Set type to CacheType enum in constructor
			CacheType Type;

			// These functions are implemented by cache implementation
			virtual ~SeedCache() = 0;							// Virtual destructor leave it empty if you dont use it

			virtual PTable* GetPTable(unsigned int F_Seed) = 0;	// This function returns PTable for given seed
			virtual size_t 	GetCacheSize() = 0;					// Returns cache size (if any)
			virtual void 	Clear() = 0;						// This function clears cache (if there is any cache)

		};


		// Cache implementations:
		struct DisabledCache : public SeedCache {
			DisabledCache();

			PTable* GetPTable(unsigned int F_Seed) override;
			size_t 	GetCacheSize() override;
			void Clear() override;
		};

		struct ArrayCache : public SeedCache {
			ArrayCache();

			PTable* GetPTable(unsigned int F_Seed) override;
			size_t 	GetCacheSize() override;
			void Clear() override;
		
		private:
			std::vector<PTable> Cache;
		};

		struct FastArrayCache : public SeedCache {
			FastArrayCache();

			PTable* GetPTable(unsigned int F_Seed) override;
			size_t 	GetCacheSize() override;
			void Clear() override;
		
		private:
			unsigned int FirstSeed = (unsigned int)-1;
			std::vector<PTable> Cache;
		};

		struct ExperimentalCache : public SeedCache {
			ExperimentalCache();

			PTable* GetPTable(unsigned int F_Seed) override;
			size_t 	GetCacheSize() override;
			void Clear() override;
		
		private:
			unsigned int FirstSeed = (unsigned int)-1;
			std::vector<PTable> Cache;
		};


		// Cache implementation
		SeedCache* Seed = NULL;

		// These functions are used by Get() function to generate noise
		float Fade(float t);
		float Lerp(float t, float a, float b);
		float Grad(int hash, float x, float y, float z);

		// Double precision versions
		double FadeD(double t);
		double LerpD(double t, double a, double b);
		double GradD(int hash, double x, double y, double z);

	};

}