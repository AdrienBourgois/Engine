#include "Id.h"

std::unordered_map<Core::CoreType::EObjectSubtype, unsigned int> Core::CoreType::Id::currentCount;

Core::CoreType::Id::Id(EObjectSubtype _subtype)
{
	uint8_t type = Undefined;

	if (_subtype & UndefinedSubtype)
		type = Undefined;
	else if (_subtype & DefaultGameObject || _subtype & OtherGameObject)
		type = GameObject;


	currentCount[_subtype]++;
	uint16_t instance_number = currentCount[_subtype];

	SetType(type);
	SetSubtype(_subtype);
	SetInstanceNumber(instance_number);
}

bool Core::CoreType::Id::operator==(Id _other_id)
{
	if (GetType() & _other_id.GetType())
		if (GetSubtype() & GetSubtype())
			return true;

	return false;
}

bool Core::CoreType::Id::operator==(EObjectType _other_type)
{
	if (GetType() & _other_type)
		return true;

	return false;
}

bool Core::CoreType::Id::operator==(EObjectSubtype _other_subtype)
{
	if (GetSubtype() & _other_subtype)
		return true;

	return false;
}

Core::CoreType::EObjectType Core::CoreType::Id::GetType()
{
	return EObjectType(*GetTypePointer());
}

Core::CoreType::EObjectSubtype Core::CoreType::Id::GetSubtype()
{
	return EObjectSubtype(*GetSubtypePointer());
}

uint16_t Core::CoreType::Id::GetInstanceNumber()
{
	return *GetInstanceNumberPointer();
}

uint8_t* Core::CoreType::Id::GetTypePointer()
{
	return reinterpret_cast<uint8_t*>(&id);
}

uint32_t* Core::CoreType::Id::GetSubtypePointer()
{
	return reinterpret_cast<uint32_t*>(GetTypePointer() + 1);
}

uint8_t* Core::CoreType::Id::GetFlagPointer()
{
	return reinterpret_cast<uint8_t*>(GetTypePointer() + 5);
}

uint16_t* Core::CoreType::Id::GetInstanceNumberPointer()
{
	return reinterpret_cast<uint16_t*>(GetTypePointer() + 6);
}

void Core::CoreType::Id::SetType(uint8_t _new_type)
{
	uint8_t* pointer = GetTypePointer();
	*pointer = _new_type;
}

void Core::CoreType::Id::SetSubtype(uint32_t _new_subtype)
{
	uint32_t* pointer = GetSubtypePointer();
	*pointer = _new_subtype;
}

void Core::CoreType::Id::SetFlag(uint8_t _new_flag)
{
	uint8_t* pointer = GetFlagPointer();
	*pointer = _new_flag;
}

void Core::CoreType::Id::SetInstanceNumber(uint16_t _new_number)
{
	uint16_t* pointer = GetInstanceNumberPointer();
	*pointer = _new_number;
}
