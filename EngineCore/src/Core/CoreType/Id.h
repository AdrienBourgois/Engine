#pragma once

#include "Macros.h"
#include <unordered_map>

namespace Core
{
	namespace CoreType
	{

		/**
		 * \brief Main type of an object : 8 values max with Undefined
		 */
		enum ENGINEDLL_API EObjectType : uint8_t
		{
			Undefined = 1 << 0,
			GameObject = 1 << 1,
			ObjectComponent = 1 << 2,
		};

		/**
		 * \brief Secondary type of an object (directly implies the main type) : 32 values max with Undefined
		 */
		enum ENGINEDLL_API EObjectSubtype : uint32_t
		{
			/// EObjectType::Undefined
			UndefinedSubtype = 1 << 0,

			/// EObjectType::GameObject
			DefaultGameObject = 1 << 1,

			/// EObjectType::ObjectComponent
			GraphicComponent = 1 << 2,
		};

		/**
		 * \brief Create and handle id and type of an object
		 * Id is an 64 bits integer variable with :
		 * - 8 bits for Main Type (Core::CoreType::EObjectType)
		 * - 32 bits for Subtype (Core::CoreType::EObjectSubtype)
		 * - 8 bits for various flags
		 * - 16 bits for instance number of defined subtype
		 */
		class ENGINEDLL_API Id
		{
		public:
			/**
			 * \brief Constructor with main type
			 * \param _type Secondary type of object
			 */
			explicit Id(EObjectType _type);
			/**
			 * \brief Constructor with secondary type
			 * \param _subtype Secondary type of object
			 */
			explicit Id(EObjectSubtype _subtype);
			/**
			 * \brief Default destructor
			 */
			~Id() = default;

			/**
			 * \brief Change subtype of Id
			 * \param _subtype New subtype
			 */
			void operator=(EObjectSubtype _subtype);
			/**
			 * \brief Change type of Id
			 * \param _type New type
			 */
			void operator=(EObjectType _type);

			/**
			 * \brief Compare types of id's
			 * \param _other_id Other Id to compare
			 * \return Are id's sames
			 */
			bool operator==(Id _other_id);
			/**
			 * \brief Compare id main type
			 * \param _other_type Type to compare
			 * \return Is Id of type
			 */
			bool operator==(EObjectType _other_type);
			/**
			 * \brief Compare types of id's
			 * \param _other_subtype Subtype to compare
			 * \return Is Id of subtype
			 */
			bool operator==(EObjectSubtype _other_subtype);

			/**
			 * \brief Return main type of Id
			 * \return Type of Id
			 */
			EObjectType GetType();
			/**
			 * \brief Return secondary type of Id
			 * \return Subtype of Id
			 */
			EObjectSubtype GetSubtype();
			/**
			 * \brief Return instance number
			 * \return Instance number of object
			 */
			uint16_t GetInstanceNumber();

		private:
			/**
			 * \brief Id storage
			 */
			uint64_t id = 0;

			uint16_t Register();
			void Unregister();

			EObjectType GetMainType(EObjectSubtype _subtype) const;

			uint8_t* GetTypePointer();
			uint32_t* GetSubtypePointer();
			uint8_t* GetFlagPointer();
			uint16_t* GetInstanceNumberPointer();

			void SetType(uint8_t _new_type);
			void SetSubtype(uint32_t _new_subtype);
			void SetFlag(uint8_t _new_flag);
			void SetInstanceNumber(uint16_t _new_number);
		};

		/**
		 * \brief Static class that handle instance numbers for id's
		 */
		class InstancecountHandle
		{
		public:
			/**
			 * \brief Handle live objects numbers of each subtypes
			 */
			static std::unordered_map<EObjectSubtype, unsigned int> currentInstanceCount;
			/**
			 * \brief Handle next instance numbers of each subtypes
			 */
			static std::unordered_map<EObjectSubtype, unsigned int> nextInstanceCount;
		};
	}
}

