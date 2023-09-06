// Add at the top bellow LyraTeamInfoBase.h
#include "LyraTeamSubsystem.h"

public:
	ALyraTeamPublicInfo(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	ULyraTeamDisplayAsset* GetTeamDisplayAsset() const { return TeamDisplayAsset; }
	/** @Game-Change start added info for if this team is NPC only Team **/
	bool GetIsNPCOnlyTeam() const { return IsNPCTeam; }

private:
	void SetIsNPCOnlyTeam(bool InitIsNPCTeam);

	UPROPERTY()
	bool IsNPCTeam = false;
	/** @Game-Change end added info for if this team is NPC only Team **/
