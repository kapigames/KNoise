#include "Perlin.hpp"


KNoise::Perlin::Perlin() {
	SetCacheType(KNoise::Perlin::CacheType::Array);
}



void KNoise::Perlin::SetCacheType(int F_CacheType) {
	switch (F_CacheType)
	{
	case Disabled:
		Seed = std::make_unique<DisabledCache>();
		break;
	
	case Single:
		Seed = std::make_unique<SingleCache>();
		break;
	
	case Array:
		Seed = std::make_unique<ArrayCache>();
		break;
	
	case FastArray:
		Seed = std::make_unique<FastArrayCache>();
		break;
	
	case Experimental:
		Seed = std::make_unique<ExperimentalCache>();
		break;
	
	default:
		std::cerr << "Undefined cache type in " << __func__ << "() in KNoise::Perlin object, cache type was not changed." << std::endl;
		break;
	}
}


void KNoise::Perlin::ClearCache() {
	Seed->Clear();
}



float KNoise::Perlin::Get(Vec3f F_Position, unsigned int F_Seed) {
	SeedCache::PTable* Permutation = Seed->GetPTable(F_Seed); // Generate new permutation layer when seed changed

	// Find the unit cube that contains the point
	int X = (int)floor(F_Position.x) & 255;
	int Y = (int)floor(F_Position.y) & 255;
	int Z = (int)floor(F_Position.z) & 255;

	// Find relative x, y,z of point in cube
	F_Position.x -= floor(F_Position.x);
	F_Position.y -= floor(F_Position.y);
	F_Position.z -= floor(F_Position.z);

	// Compute fade curves for each of x, y, z
	float u = Fade(F_Position.x);
	float v = Fade(F_Position.y);
	float w = Fade(F_Position.z);

	// Hash coordinates of the 8 cube corners
	int A = Permutation->Permutation[X] + Y;
	int AA = Permutation->Permutation[A] + Z;
	int AB = Permutation->Permutation[A + 1] + Z;
	int B = Permutation->Permutation[X + 1] + Y;
	int BA = Permutation->Permutation[B] + Z;
	int BB = Permutation->Permutation[B + 1] + Z;

	// Add blended results from 8 corners of cube
	float res =
		Lerp(w,
			Lerp(v,
				Lerp(u, Grad(Permutation->Permutation[AA], F_Position.x, F_Position.y, F_Position.z), Grad(Permutation->Permutation[BA], F_Position.x - 1, F_Position.y, F_Position.z)),
				Lerp(u, Grad(Permutation->Permutation[AB], F_Position.x, F_Position.y - 1, F_Position.z), Grad(Permutation->Permutation[BB], F_Position.x - 1, F_Position.y - 1, F_Position.z))),
			Lerp(v,
				Lerp(u, Grad(Permutation->Permutation[AA + 1], F_Position.x, F_Position.y, F_Position.z - 1), Grad(Permutation->Permutation[BA + 1], F_Position.x - 1, F_Position.y, F_Position.z - 1)),
				Lerp(u, Grad(Permutation->Permutation[AB + 1], F_Position.x, F_Position.y - 1, F_Position.z - 1), Grad(Permutation->Permutation[BB + 1], F_Position.x - 1, F_Position.y - 1, F_Position.z - 1))));

	return (res + 1.f) / 2.f;
}

float KNoise::Perlin::Fade(float t) { return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f); }
float KNoise::Perlin::Lerp(float t, float a, float b) { return a + t * (b - a); }
float KNoise::Perlin::Grad(int hash, float x, float y, float z) {
	int h = hash & 15;
	// Convert lower 4 bits of hash into 12 gradient directions
	float u = h < 8 ? x : y,
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}



double KNoise::Perlin::Get(Vec3d F_Position, unsigned int F_Seed) {
	SeedCache::PTable* Permutation = Seed->GetPTable(F_Seed); // Generate new permutation layer when seed changed

	// Find the unit cube that contains the point
	int X = (int)floor(F_Position.x) & 255;
	int Y = (int)floor(F_Position.y) & 255;
	int Z = (int)floor(F_Position.z) & 255;

	// Find relative x, y,z of point in cube
	F_Position.x -= floor(F_Position.x);
	F_Position.y -= floor(F_Position.y);
	F_Position.z -= floor(F_Position.z);

	// Compute fade curves for each of x, y, z
	double u = FadeD(F_Position.x);
	double v = FadeD(F_Position.y);
	double w = FadeD(F_Position.z);

	// Hash coordinates of the 8 cube corners
	int A = Permutation->Permutation[X] + Y;
	int AA = Permutation->Permutation[A] + Z;
	int AB = Permutation->Permutation[A + 1] + Z;
	int B = Permutation->Permutation[X + 1] + Y;
	int BA = Permutation->Permutation[B] + Z;
	int BB = Permutation->Permutation[B + 1] + Z;

	// Add blended results from 8 corners of cube
	double res =
		LerpD(w,
			LerpD(v,
				LerpD(u, GradD(Permutation->Permutation[AA], F_Position.x, F_Position.y, F_Position.z), GradD(Permutation->Permutation[BA], F_Position.x - 1, F_Position.y, F_Position.z)),
				LerpD(u, GradD(Permutation->Permutation[AB], F_Position.x, F_Position.y - 1, F_Position.z), GradD(Permutation->Permutation[BB], F_Position.x - 1, F_Position.y - 1, F_Position.z))),
			LerpD(v,
				LerpD(u, GradD(Permutation->Permutation[AA + 1], F_Position.x, F_Position.y, F_Position.z - 1), GradD(Permutation->Permutation[BA + 1], F_Position.x - 1, F_Position.y, F_Position.z - 1)),
				LerpD(u, GradD(Permutation->Permutation[AB + 1], F_Position.x, F_Position.y - 1, F_Position.z - 1), GradD(Permutation->Permutation[BB + 1], F_Position.x - 1, F_Position.y - 1, F_Position.z - 1))));

	return (res + 1.0) / 2.0;
}

double KNoise::Perlin::FadeD(double t) { return t * t * t * (t * (t * 6.0 - 15.0) + 10.0); }
double KNoise::Perlin::LerpD(double t, double a, double b) { return a + t * (b - a); }
double KNoise::Perlin::GradD(int hash, double x, double y, double z) {
	int h = hash & 15;
	// Convert lower 4 bits of hash into 12 gradient directions
	double u = h < 8 ? x : y,
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}



float KNoise::Perlin::GetFractal(Vec3f F_Position, unsigned int F_Seed, unsigned int F_Quality) {
	float Return = 0.f;
	for (unsigned int i = 0; i < F_Quality+1; i++)
	{
		Return = Return + Get(F_Position, F_Seed * i);
	}

	Return = Return / (float)(F_Quality+1);

	return Return;
}

double KNoise::Perlin::GetFractal(Vec3d F_Position, unsigned int F_Seed, unsigned int F_Quality) {
	double Return = 0.0;
	for (unsigned int i = 0; i < F_Quality+1; i++)
	{
		Return = Return + Get(F_Position, F_Seed * i);
	}

	Return = Return / (float)(F_Quality+1);

	return Return;
}



KNoise::Perlin::SeedCache::PTable::PTable() { Permutation.reserve(256); }	// Allocate memory for permutation
KNoise::Perlin::SeedCache::PTable::PTable(unsigned int F_Seed) {
	Seed = F_Seed;

	Permutation.resize(256);
	std::iota(Permutation.begin(), Permutation.end(), 0);							// Fill Permutation with values from 0 to 255
	std::default_random_engine engine(Seed);										// Initialize a random engine with seed
	std::shuffle(Permutation.begin(), Permutation.end(), engine);					// Suffle  using the above random engine
	Permutation.insert(Permutation.end(), Permutation.begin(), Permutation.end());	// Duplicate the permutation vector

	Created = true;
}



KNoise::Perlin::SeedCache::PTable* KNoise::Perlin::DisabledCache::GetPTable(unsigned int F_Seed) {
	return new PTable(F_Seed);
}

void KNoise::Perlin::DisabledCache::Clear() {}



KNoise::Perlin::SeedCache::PTable* KNoise::Perlin::SingleCache::GetPTable(unsigned int F_Seed) {
	if(LastPTable.Seed != F_Seed) LastPTable = PTable(F_Seed);
	return &LastPTable;
}

void KNoise::Perlin::SingleCache::Clear() {
	LastPTable = 0;
}



KNoise::Perlin::SeedCache::PTable* KNoise::Perlin::ArrayCache::GetPTable(unsigned int F_Seed) {
	for (unsigned int i = 0; i < Cache.size(); i++)	// Cycle through cache array
	{
		if (Cache[i].Seed == F_Seed) {				// Try to find permutation with set seed
			return &Cache[i];						// If found return PTable cache array pointer
		}
	}
	Cache.reserve((unsigned int)ceil(Cache.size() / PERLIN_ALLOCATION_SIZE) * PERLIN_ALLOCATION_SIZE);	// If not found allocate more memory in cache array
	Cache.push_back(PTable(F_Seed));													// Generate new PTable
	return &Cache[Cache.size() - 1];													// Return PTable pointer
}

void KNoise::Perlin::ArrayCache::Clear() {
	Cache.clear();
}



KNoise::Perlin::SeedCache::PTable* KNoise::Perlin::FastArrayCache::GetPTable(unsigned int F_Seed) {
	if (F_Seed+1 > Cache.size()) { Cache.resize(F_Seed + PERLIN_ALLOCATION_SIZE); }	// If seed is bigger than cache array resize array
	if (Cache[F_Seed].Created == false) { Cache[F_Seed] = PTable(F_Seed); }			// If PTable is not generated generate PTable
	return &Cache[F_Seed];															// Return PTable cache array pointer
}

void KNoise::Perlin::FastArrayCache::Clear() {
	Cache.clear();
}



KNoise::Perlin::SeedCache::PTable* KNoise::Perlin::ExperimentalCache::GetPTable(unsigned int F_Seed) {
	if (F_Seed < FirstSeed) { FirstSeed = F_Seed; Clear(); }
	if (F_Seed+1-FirstSeed > Cache.size()) { Cache.resize(F_Seed-FirstSeed + PERLIN_ALLOCATION_SIZE); }		// If seed is bigger than cache array resize array
	if (Cache[F_Seed-FirstSeed].Created == false) { Cache[F_Seed-FirstSeed] = PTable(F_Seed); }				// If PTable is not generated generate PTable
	return &Cache[F_Seed-FirstSeed];																		// Return PTable cache array pointer
}

void KNoise::Perlin::ExperimentalCache::Clear() {
	Cache.clear();
}