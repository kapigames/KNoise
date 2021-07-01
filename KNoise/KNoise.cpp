#include "KNoise.hpp"


float KNoise::Perlin::Get(KNoise::Vec3f F_Position, int F_Seed) {
	Seed::PTable* Permutation = Seed.GetPTable(F_Seed); // Generate new permutation layer when seed changed

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

	return (res + 1.0f) / 2.0f;
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



double KNoise::Perlin::Get(KNoise::Vec3d F_Position, int F_Seed) {
	Seed::PTable* Permutation = Seed.GetPTable(F_Seed); // Generate new permutation layer when seed changed

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
	float res =
		LerpD(w,
			LerpD(v,
				LerpD(u, GradD(Permutation->Permutation[AA], F_Position.x, F_Position.y, F_Position.z), GradD(Permutation->Permutation[BA], F_Position.x - 1, F_Position.y, F_Position.z)),
				LerpD(u, GradD(Permutation->Permutation[AB], F_Position.x, F_Position.y - 1, F_Position.z), GradD(Permutation->Permutation[BB], F_Position.x - 1, F_Position.y - 1, F_Position.z))),
			LerpD(v,
				LerpD(u, GradD(Permutation->Permutation[AA + 1], F_Position.x, F_Position.y, F_Position.z - 1), GradD(Permutation->Permutation[BA + 1], F_Position.x - 1, F_Position.y, F_Position.z - 1)),
				LerpD(u, GradD(Permutation->Permutation[AB + 1], F_Position.x, F_Position.y - 1, F_Position.z - 1), GradD(Permutation->Permutation[BB + 1], F_Position.x - 1, F_Position.y - 1, F_Position.z - 1))));

	return (res + 1.0f) / 2.0f;
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



KNoise::Perlin::Seed::PTable* KNoise::Perlin::Seed::GetPTable(int F_Seed) {
	switch (CacheID)
	{
	case None:
		LastPTable = PTable(F_Seed);
		return &LastPTable;

	case Deafult:
		for (unsigned int i = 0; i < Cache.size(); i++)
		{
			if (Cache[i].Seed == F_Seed) {
				return &Cache[i];
			}
		}
		Cache.reserve((unsigned int)ceil(Cache.size() / AllocationSize) * AllocationSize);
		Cache.push_back(PTable(F_Seed));
		return &Cache[Cache.size() - 1];

	case Fast:
		if (F_Seed+1 > Cache.size()) { Cache.resize(F_Seed + AllocationSize); }
		if (Cache[F_Seed].Created == false) { Cache[F_Seed] = PTable(F_Seed); }
		return &Cache[F_Seed];

	case Experimental:
		CacheID = None;
		return GetPTable(F_Seed);

	default:
		CacheID = None;
		return GetPTable(F_Seed);
	}
}



void KNoise::Perlin::Seed::SetCacheType(CacheType F_CacheID) { ResetCache(); CacheID = F_CacheID; }
void KNoise::Perlin::Seed::ResetCache() { Cache.clear(); }



KNoise::Perlin::Seed::PTable::PTable() { Permutation.reserve(256); }
KNoise::Perlin::Seed::PTable::PTable(int F_Seed) {
	Seed = F_Seed;

	Permutation.resize(256);
	std::iota(Permutation.begin(), Permutation.end(), 0);							// Fill Permutation with values from 0 to 255
	std::default_random_engine engine(Seed);										// Initialize a random engine with seed
	std::shuffle(Permutation.begin(), Permutation.end(), engine);					// Suffle  using the above random engine
	Permutation.insert(Permutation.end(), Permutation.begin(), Permutation.end());	// Duplicate the permutation vector

	Created = true;
}