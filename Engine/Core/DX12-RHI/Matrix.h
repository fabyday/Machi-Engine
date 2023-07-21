#pragma once
#include <DirectXMath.h>
#include <Platform/types.h>
namespace Machi {
	namespace NativeGraphics {

		
		template <int T, int D = 4>
		struct is_vectorizable {
			static const bool flag = (T < 0) || (D > 0) ||(T % D) == 0 ? true : struct is_vectorizable<T, D-1>::value;
			static const int dn = D;
			static const int quotient = T / D;
		};
		
		template <int T>
		struct is_vectorizable<T, 1> {
			static const bool flag = false;
		};




		template <typename T, int R, int C>
		struct select_matrix_type {
			using matrix_type = float;
		};
		template <>
		struct select_matrix_type<MINT, 1,2> {
			using matrix_type = DirectX::XMINT2;
		};

		template <>
		struct select_matrix_type<MINT, 1, 3> {
			using matrix_type = DirectX::XMINT3;
		};

		template <>
		struct select_matrix_type<MDOUBLE, 1, 2> {
			using matrix_type = DirectX::XMFLOAT2;
		};

		template <>
		struct select_matrix_type<MDOUBLE,1, 3> {
			using matrix_type = DirectX::XMFLOAT3;

		};
		template <>
		struct select_matrix_type<MDOUBLE, 3,3> {
			using matrix_type = DirectX::XMFLOAT3X3;

		};

		template <>
		struct select_matrix_type<MDOUBLE, 3, 4> {
			using matrix_type = DirectX::XMFLOAT3X4;

		};


		template <>
		struct select_matrix_type<MDOUBLE, 1, 4> {
			using matrix_type = DirectX::XMFLOAT4;
		};
		template <>
		struct select_matrix_type<MDOUBLE, 4, 3> {
			using matrix_type = DirectX::XMFLOAT4X3;
		};
		template <>
		struct select_matrix_type<MDOUBLE, 4, 4> {
			using matrix_type = DirectX::XMFLOAT4X4;
		};




		template <typename T, int N, bool checker>
		class PlatformNativeMatrix {
		};


		template <typename T, int N  >
		class PlatformNativeMatrix<T, N, true> {

			using TYPE = typename select_matrix_type<T, is_vectorizable<N>::quotient, is_vectorizable<N>::dn >::matrix_type;

			TYPE m_data;


		};

		template <typename T, int N  >
		class PlatformNativeMatrix<T, N, false> {

			void* t;


		};

		//template <typename T, int N,  typename is_vectorizable<N>::flag = false>
		//class PlatformNativeMatrix {


		//};
		//typedef PlatformNativeMatrix<> Matrix4X4;



	}
}