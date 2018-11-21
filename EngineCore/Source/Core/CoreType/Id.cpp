#include "Id.h"

std::unordered_map<Core::CoreType::EObjectSubtype, unsigned int> Core::CoreType::InstanceCountHandle::currentInstanceCount;
std::unordered_map<Core::CoreType::EObjectSubtype, unsigned int> Core::CoreType::InstanceCountHandle::nextInstanceCount;

bool operator&(const Core::CoreType::EObjectSubtype& _lhs, const Core::CoreType::EObjectSubtype& _rhs)
{
	return static_cast<int>(_lhs) == static_cast<int>(_rhs);
}

bool operator&(const Core::CoreType::EObjectType& _lhs, const Core::CoreType::EObjectType& _rhs)
{
	return static_cast<int>(_lhs) == static_cast<int>(_rhs);
}

Core::CoreType::Id::Id(const EObjectType _type)
{
	SetType(_type);
	SetSubtype(EObjectSubtype::UndefinedSubtype);
	SetInstanceNumber(Register());
}

Core::CoreType::Id::Id(const EObjectSubtype _subtype)
{
	const EObjectType type = GetMainType(_subtype);

	SetType(type);
	SetSubtype(_subtype);
	SetInstanceNumber(Register());
}

Core::CoreType::Id& Core::CoreType::Id::operator=(const EObjectSubtype _subtype)
{
	Unregister();
	SetSubtype(_subtype);
	SetType(GetMainType(_subtype));
	Register();

	return *this;
}

Core::CoreType::Id& Core::CoreType::Id::operator=(const EObjectType _type)
{
	Unregister();
	SetSubtype(EObjectSubtype::UndefinedSubtype);
	SetType(_type);
	Register();

	return *this;
}

uint16_t Core::CoreType::Id::Register()
{
	const EObjectSubtype subtype = GetSubtype();
	InstanceCountHandle::currentInstanceCount[subtype]++;
	InstanceCountHandle::nextInstanceCount[subtype]++;
	return InstanceCountHandle::nextInstanceCount[subtype];
}

void Core::CoreType::Id::Unregister()
{
	const EObjectSubtype subtype = GetSubtype();
	InstanceCountHandle::currentInstanceCount[subtype]--;
}

bool Core::CoreType::Id::operator==(Id _other_id)
{
	if (GetType() & _other_id.GetType())
		if (GetSubtype() & GetSubtype())
			return true;

	return false;
}

bool Core::CoreType::Id::operator==(const EObjectType _other_type)
{
	return GetType() & _other_type;
}

bool Core::CoreType::Id::operator==(const EObjectSubtype _other_subtype)
{
	return GetSubtype() & _other_subtype;
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

Core::CoreType::EObjectType Core::CoreType::Id::GetMainType(const EObjectSubtype _subtype)
{
	EObjectType type = EObjectType::Undefined;

	if (_subtype & EObjectSubtype::UndefinedSubtype)
		type = EObjectType::Undefined;
	else if (_subtype & EObjectSubtype::DefaultGameObject)
		type = EObjectType::GameObject;
	else if (_subtype & EObjectSubtype::GraphicComponent)
		type = EObjectType::ObjectComponent;
	else if (_subtype & EObjectSubtype::SimpleScript)
		type = EObjectType::Script;
	else if (_subtype & EObjectSubtype::GameScript)
		type = EObjectType::Script;

	return type;
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

void Core::CoreType::Id::SetType(EObjectType _new_type)
{
	uint8_t* pointer = GetTypePointer();
	*pointer = static_cast<uint8_t>(_new_type);
}

void Core::CoreType::Id::SetSubtype(EObjectSubtype _new_subtype)
{
	uint32_t* pointer = GetSubtypePointer();
	*pointer = static_cast<uint32_t>(_new_subtype);
}

void Core::CoreType::Id::SetFlag(const uint8_t _new_flag)
{
	uint8_t* pointer = GetFlagPointer();
	*pointer = _new_flag;
}

void Core::CoreType::Id::SetInstanceNumber(const uint16_t _new_number)
{
	uint16_t* pointer = GetInstanceNumberPointer();
	*pointer = _new_number;
}