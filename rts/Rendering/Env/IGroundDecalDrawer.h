/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#pragma once

#include "Decals/GroundDecal.h"

class CSolidObject;
class GhostSolidObject;

class IGroundDecalDrawer
{
public:
	static bool GetDrawDecals() { return (decalLevel > 0); }
	static void SetDrawDecals(bool v);

	static void Init();
	static void FreeInstance();
	static IGroundDecalDrawer* singleton;

public:
	virtual void ReloadTextures() = 0;
	virtual void DumpAtlasTextures() = 0;

	virtual void Draw() = 0;

	virtual uint32_t CreateLuaDecal() = 0;
	virtual bool DeleteLuaDecal(uint32_t id) = 0;
	virtual       GroundDecal* GetDecalById(uint32_t id)       = 0;
	virtual const GroundDecal* GetDecalById(uint32_t id) const = 0;
	virtual bool SetDecalTexture(uint32_t id, const std::string& texName, bool mainTex) = 0;
	virtual std::string GetDecalTexture(uint32_t id, bool mainTex) const = 0;
	virtual const std::vector<std::string> GetDecalTextures(bool mainTex) const = 0;
	virtual const CSolidObject* GetDecalSolidObjectOwner(uint32_t id) const = 0;

	virtual void AddSolidObject(const CSolidObject* object) = 0;
	virtual void ForceRemoveSolidObject(const CSolidObject* object) = 0;

	//FIXME move to eventhandler?
	virtual void GhostDestroyed(const GhostSolidObject* gb) = 0;
	virtual void GhostCreated(const CSolidObject* object, const GhostSolidObject* gb) = 0;

	const auto& GetAllDecals() const { return decals; }
public:
	virtual ~IGroundDecalDrawer() {}

protected:
	virtual void OnDecalLevelChanged() = 0;
protected:
	std::vector<GroundDecal> decals;
	static int decalLevel;
};



class NullGroundDecalDrawer: public IGroundDecalDrawer
{
public:
	void ReloadTextures() override {}
	void DumpAtlasTextures() override {}

	void Draw() override {}

	void AddSolidObject(const CSolidObject* object) override {}
	void ForceRemoveSolidObject(const CSolidObject* object) override {}

	void GhostDestroyed(const GhostSolidObject* gb) override {}
	void GhostCreated(const CSolidObject* object, const GhostSolidObject* gb) override {}

	void OnDecalLevelChanged() override {}

	uint32_t CreateLuaDecal() override { return 0; }
	bool DeleteLuaDecal(uint32_t id) override { return false; }
	      GroundDecal* GetDecalById(uint32_t id)       override { return nullptr; }
	const GroundDecal* GetDecalById(uint32_t id) const override { return nullptr; }
	bool SetDecalTexture(uint32_t id, const std::string& texName, bool mainTex) override { return false; }
	std::string GetDecalTexture(uint32_t id, bool mainTex) const override { return ""; }
	const std::vector<std::string> GetDecalTextures(bool mainTex) const override { return {}; }
	const CSolidObject* GetDecalSolidObjectOwner(uint32_t id) const override { return nullptr; }
};


#define groundDecals IGroundDecalDrawer::singleton