#pragma once

namespace Patches
{
	using InitWornArmorFunc = void(
		RE::TESObjectARMO* a_armor,
		RE::TESRace* a_race,
		RE::BSTSmartPointer<RE::BipedAnim>* a_biped,
		bool isFemale);

	void WriteInitWornPatch(InitWornArmorFunc* a_func);

	using GetWornMaskFunc = auto(RE::InventoryChanges* a_inventoryChanges) -> BipedObjectSlot;

	void WriteGetWornMaskPatch(GetWornMaskFunc* a_func);
}
