/** @Game-Change start support for checking if actor is in a team that's an NPC team. **/
bool ULyraTeamSubsystem::IsPartOfAnNPCTeam(const UObject* ActorWithTeam) const
{
	const int32 TeamID = FindTeamFromObject(Cast<const AActor>(ActorWithTeam));
	return IsTeamNPC(TeamID);
}

bool ULyraTeamSubsystem::IsTeamNPC(const int32 TeamId) const
{
	if (const FLyraTeamTrackingInfo* Entry = TeamMap.Find(TeamId))
	{
		return Entry->IsNPCOnlyTeam;
	}

	return false;
}
/** @Game-Change end support for checking if actor is in a team that's an NPC team. **/

void FLyraTeamTrackingInfo::SetTeamInfo(ALyraTeamInfoBase* Info)
{
	if (ALyraTeamPublicInfo* NewPublicInfo = Cast<ALyraTeamPublicInfo>(Info))
	{
		ensure((PublicInfo == nullptr) || (PublicInfo == NewPublicInfo));
		PublicInfo = NewPublicInfo;

		ULyraTeamDisplayAsset* OldDisplayAsset = DisplayAsset;
		DisplayAsset = NewPublicInfo->GetTeamDisplayAsset();

		if (OldDisplayAsset != DisplayAsset)
		{
			OnTeamDisplayAssetChanged.Broadcast(DisplayAsset);
		}

		/** @Game-Change start update info on the team **/
		IsNPCOnlyTeam = NewPublicInfo->GetIsNPCOnlyTeam();
		/** @Game-Change end update info on the team **/
	}
	else if (ALyraTeamPrivateInfo* NewPrivateInfo = Cast<ALyraTeamPrivateInfo>(Info))
	{
		ensure((PrivateInfo == nullptr) || (PrivateInfo == NewPrivateInfo));
		PrivateInfo = NewPrivateInfo;
	}
	else
	{
		checkf(false, TEXT("Expected a public or private team info but got %s"), *GetPathNameSafe(Info))
	}
}

