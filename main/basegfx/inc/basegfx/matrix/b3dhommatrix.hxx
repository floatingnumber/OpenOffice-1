/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef _BGFX_MATRIX_B3DHOMMATRIX_HXX
#define _BGFX_MATRIX_B3DHOMMATRIX_HXX

#include <sal/types.h>
#include <basegfx/point/b3dpoint.hxx>
#include <basegfx/vector/b3dvector.hxx>
#include <o3tl/cow_wrapper.hxx>

namespace basegfx
{
	class B3DTuple;
    class Impl3DHomMatrix;

	class B3DHomMatrix
	{
    public:
        typedef o3tl::cow_wrapper< Impl3DHomMatrix > ImplType;

	private:
        ImplType                                     mpImpl;

	public:
		B3DHomMatrix();
		B3DHomMatrix(const B3DHomMatrix& rMat);
		~B3DHomMatrix();

        /// unshare this matrix with all internally shared instances
        void makeUnique();

		double get(sal_uInt16 nRow, sal_uInt16 nColumn) const;
		void set(sal_uInt16 nRow, sal_uInt16 nColumn, double fValue);

		// test if last line is default to see if last line needs to be
		// involved in calculations
		bool isLastLineDefault() const;

		bool isIdentity() const;
		/// Reset to the identity matrix
		void identity();

		bool isInvertible() const;
		/// Invert the matrix (if possible)
		bool invert();

		bool isNormalized() const;
		/// Normalize (i.e. force w=1) the matrix
		void normalize();

		/// Calc the matrix determinant
		double determinant() const;

		/// Calc the matrix trace
		double trace() const;

		/// Transpose the matrix
		void transpose();

		/// Rotation
		void rotate(double fAngleX,double fAngleY,double fAngleZ);

		/// Translation
		void translate(double fX, double fY, double fZ);

		/// Scaling
		void scale(double fX, double fY, double fZ);

		// Shearing-Matrices
		void shearXY(double fSx, double fSy);
		void shearYZ(double fSy, double fSz);
		void shearXZ(double fSx, double fSz);

		// Projection matrices, used for converting between eye and
		// clip coordinates
		void frustum(double fLeft = -1.0, double fRight = 1.0,
			double fBottom = -1.0, double fTop = 1.0,
			double fNear = 0.001, double fFar = 1.0);
		
		void ortho(double fLeft = -1.0, double fRight = 1.0,
			double fBottom = -1.0, double fTop = 1.0,
			double fNear = 0.0, double fFar = 1.0);

		// build orientation matrix
		void orientation(
			B3DPoint aVRP = B3DPoint(0.0,0.0,1.0),
			B3DVector aVPN = B3DVector(0.0,0.0,1.0),
			B3DVector aVUV = B3DVector(0.0,1.0,0.0));

		// addition, subtraction
		B3DHomMatrix& operator+=(const B3DHomMatrix& rMat);
		B3DHomMatrix& operator-=(const B3DHomMatrix& rMat);

		// comparison
		bool operator==(const B3DHomMatrix& rMat) const;
		bool operator!=(const B3DHomMatrix& rMat) const;

		// multiplication, division by constant value
		B3DHomMatrix& operator*=(double fValue);
		B3DHomMatrix& operator/=(double fValue);

		// matrix multiplication (from the left)
		B3DHomMatrix& operator*=(const B3DHomMatrix& rMat);

		// assignment operator
		B3DHomMatrix& operator=(const B3DHomMatrix& rMat);

		// decomposition
		bool decompose(B3DTuple& rScale, B3DTuple& rTranslate, B3DTuple& rRotate, B3DTuple& rShear) const;
	};

	// addition, subtraction
	inline B3DHomMatrix	operator+(const B3DHomMatrix& rMatA, const B3DHomMatrix& rMatB)
	{
		B3DHomMatrix aSum(rMatA);
		aSum += rMatB;
		return aSum;
	}

	inline B3DHomMatrix	operator-(const B3DHomMatrix& rMatA, const B3DHomMatrix& rMatB)
	{
		B3DHomMatrix aDiv(rMatA);
		aDiv -= rMatB;
		return aDiv;
	}

	// multiplication, division by constant value
	inline B3DHomMatrix	operator*(const B3DHomMatrix& rMat, double fValue)
	{
		B3DHomMatrix aNew(rMat); 
		aNew *= fValue; 
		return aNew; 
	}

	inline B3DHomMatrix	operator/(const B3DHomMatrix& rMat, double fValue)
	{
		B3DHomMatrix aNew(rMat); 
		aNew *= 1.0 / fValue;
		return aNew; 
	}

	inline B3DHomMatrix	operator*(const B3DHomMatrix& rMatA, const B3DHomMatrix& rMatB)
	{
		B3DHomMatrix aMul(rMatB);
		aMul *= rMatA;
		return aMul;
	}
} // end of namespace basegfx

#endif /* _BGFX_MATRIX_B3DHOMMATRIX_HXX */
