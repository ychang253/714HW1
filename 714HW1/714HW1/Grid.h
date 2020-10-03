#pragma once
class Grid
{
public:
	Grid();
	Grid(int m);
	~Grid();

	void SolveByJacobi(int iLoopMax, double dRelax);
	void SolveByMultiGrid(int iLoopMax);
	void OutputResultAsVTK();

	int m_iMeshM;
	int m_iNtotal;
	int m_iIterations;
	int m_iJacobiLoopMax;
	double m_dH;
	double m_dMaxError;

	double **m_pUij, **m_pU0ij , **m_pRij;
	double **m_pU00ij;
};

