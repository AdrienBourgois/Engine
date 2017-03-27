#pragma once

///@cond DUPLICATE_MACRO
#ifdef ENGINECORE_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif
///@endcond

namespace Core
{
	namespace CoreType
	{
		/**
		 * \brief RGBA Color class
		 */
		class ENGINEDLL_API Color
		{
		public:
			/**
			 * \brief Default constructor
			 */
			Color() = default;
			/**
			 * \brief Contructor for range value 0-1
			 * \param _r Red component
			 * \param _g Green component
			 * \param _b Blue component
			 * \param _a Alpha component
			 */
			Color(float _r, float _g, float _b, float _a = 0.f);
			/**
			 * \brief Contructor for range value 0-255
			 * \param _r Red component
			 * \param _g Green component
			 * \param _b Blue component
			 * \param _a Alpha component
			 */
			Color(int _r, int _g, int _b, int _a = 0.f);
			/**
			 * \brief Default destructor
			 */
			~Color() = default;

			/**
			 * \brief Red component
			 */
			float r = 0;
			/**
			 * \brief Green component
			 */
			float g = 0;
			/**
			 * \brief Blue component
			 */
			float b = 0;
			/**
			 * \brief Alpha component
			 */
			float a = 0;

			/**
			 * \brief White (1, 1, 1, 1)
			 */
			static Color White;
			/**
			 * \brief Black (0, 0, 0, 1)
			 */
			static Color Black;
			/**
			 * \brief Red (1, 0, 0, 1)
			 */
			static Color Red;
			/**
			 * \brief Green (0, 1, 0, 1)
			 */
			static Color Green;
			/**
			 * \brief Blue (0, 0, 1, 1)
			 */
			static Color Blue;
		};
	}
}

