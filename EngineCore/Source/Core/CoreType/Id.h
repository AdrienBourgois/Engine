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
		enum class EObjectType : uint8_t
		{
			/**
			 * \brief Generic main type
			 */
			Undefined = 1 << 0,
			/**
			 * \brief For GameObjects
			 */
			GameObject = 1 << 1,
			/**
			 * \brief For component of objects
			 */
			ObjectComponent = 1 << 2,
			/**
			 * \brief For scripts
			 */
			Script = 1 << 3,
		};

		/**
		 * \brief Secondary type of an object (directly implies the main type) : 32 values max with Undefined
		 */
		enum class EObjectSubtype : uint32_t
		{
			/// EObjectType::Undefined
			UndefinedSubtype = 1 << 0,

			/// EObjectType::GameObject
			DefaultGameObject = 1 << 1,

			/// EObjectType::ObjectComponent
			GraphicComponent = 1 << 2,

			/// EObjectType::Script
			SimpleScript = 1 << 3,

			/// EObjectType::Script
			GameScript = 1 << 4,
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
			Id& operator=(EObjectSubtype _subtype);
			/**
			 * \brief Change type of Id
			 * \param _type New type
			 */
			Id& operator=(EObjectType _type);

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

			/**
			 * \brief Register the id in list
			 * \return Instance count of the registered id
			 */
			uint16_t Register();
			/**
			 * \brief Remove id from list
			 */
			void Unregister();

			/**
			 * \brief Return a main type for a subtype
			 * \param _subtype Subtype to test
			 * \return Main type of the subtype
			 */
			static EObjectType GetMainType(EObjectSubtype _subtype);

			/**
			 * \brief Return pointer to type data
			 * \return Pointer to type data
			 */
			uint8_t* GetTypePointer();
			/**
			 * \brief Return pointer to subtype data
			 * \return Pointer to subtype data
			 */
			uint32_t* GetSubtypePointer();
			/**
			 * \brief Return pointer to flag data
			 * \return Pointer to flag data
			 */
			uint8_t* GetFlagPointer();
			/**
			 * \brief Return pointer to instance number data
			 * \return Pointer to instance number data
			 */
			uint16_t* GetInstanceNumberPointer();

			/**
			 * \brief Set a new main type
			 * \param _new_type New main type
			 */
			void SetType(EObjectType _new_type);
			/**
			 * \brief Set a new subtype
			 * \param _new_subtype New subtype
			 */
			void SetSubtype(EObjectSubtype _new_subtype);
			/**
			 * \brief Set a new flag
			 * \param _new_flag New flag
			 */
			void SetFlag(uint8_t _new_flag);
			/**
			 * \brief Set a new main type
			 * \param _new_number New instance number
			 */
			void SetInstanceNumber(uint16_t _new_number);
		};

		/**
		 * \brief Static class that handle instance numbers for id's
		 */
		class InstanceCountHandle
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

