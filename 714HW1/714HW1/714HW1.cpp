// 714HW1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <math.h>       
#include "Grid.h"


#define PI 3.14159265

int main()
{
	ErrorVsGridSpacing();
	
	// multi grid
	int mRef = 63; //255
	Grid oReference(mRef);
	oReference.SolveByMultiGrid(1e5);
	oReference.OutputResultAsVTK();

	getchar();
}

void ErrorVsGridSpacing()
{
	int mRef = 255; //255
	int iRatio = 4;
	int iLoopMax = 1e6;

	int mGrid_1 = (mRef + 1) / iRatio - 1;

	Grid oReference(mRef);
	oReference.SolveByJacobi(iLoopMax, 1.);
	oReference.OutputResultAsVTK();

	for (int iL = 0; iL <= 2; iL++)
	{
		Grid oGrid_1(mGrid_1);
		oGrid_1.SolveByJacobi(iLoopMax, 1.);
		oGrid_1.OutputResultAsVTK();


		// compara error
		double MaxError = 1.e-30;
		double Error;

		for (int i = 0; i <= mGrid_1 + 1; i++)
			for (int j = 0; j <= mGrid_1 + 1; j++)
			{
				{
					Error = fabs(oGrid_1.m_pUij[i][j] - oReference.m_pUij[i*iRatio][j*iRatio]);
					if (Error > MaxError) MaxError = Error;
				}
			}

		printf("Error beteen grid =%d and %d is %lg \n", mGrid_1, mRef, MaxError);

		iRatio *= 2;
		mGrid_1 = (mRef + 1) / iRatio - 1;
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
