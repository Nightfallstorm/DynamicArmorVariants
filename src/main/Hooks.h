#pragma once

class Hooks
{
public:
	Hooks() = delete;

	static void Install();

private:
	static void InitWornArmor(
		RE::TESObjectARMO* a_armor,
		RE::TESRace* a_race,
		RE::BSTSmartPointer<RE::BipedAnim>* a_biped,
		bool isFemale);

	static auto GetWornMask(RE::InventoryChanges* a_inventoryChanges) -> BipedObjectSlot;
};
