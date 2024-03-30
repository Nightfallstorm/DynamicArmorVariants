#include "Patches.h"
#include "RE/Offset.Ext.h"

void Patches::WriteInitWornPatch(InitWornArmorFunc* a_func)
{
	auto hook = util::MakeHook(RE::Offset::TESNPC::InitWornForm, 0x302);

	auto& trampoline = SKSE::GetTrampoline();
	SKSE::AllocTrampoline(14);

	trampoline.write_call<5>(hook.address(), reinterpret_cast<std::uintptr_t>(a_func));

}

void Patches::WriteGetWornMaskPatch(GetWornMaskFunc* a_func)
{
	auto hook = util::MakeHook(RE::Offset::InventoryChanges::GetWornMask);

	// Expected size: 0x15
	struct Patch : public Xbyak::CodeGenerator
	{
		Patch(std::uintptr_t a_funcAddr)
		{
			sub(rsp, 0x8);
			mov(rax, a_funcAddr);
			call(rax);
			add(rsp, 0x8);
			ret();
		}
	};

	Patch patch{ reinterpret_cast<std::uintptr_t>(a_func) };
	patch.ready();

	if (patch.getSize() > 0x40) {
		util::report_and_fail("Patch was too large, failed to install"sv);
	}

	REL::safe_fill(hook.address(), REL::INT3, 0x40);
	REL::safe_write(hook.address(), patch.getCode(), patch.getSize());
}
