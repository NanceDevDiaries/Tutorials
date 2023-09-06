	/** Game-Change start support for checking if actor is in a team that's an NPC team. **/
	UFUNCTION(BlueprintCallable, Category=Teams)
	bool IsPartOfAnNPCTeam(const UObject* ActorWithTeam) const;

	// Gets if the team is NPC from the perspective of the specified team
	UFUNCTION(BlueprintCallable, Category=Teams)
	bool IsTeamNPC(int32 TeamId) const;
	/** Game-Change end support for checking if actor is in a team that's an NPC team. **/


USTRUCT()
struct FLyraTeamTrackingInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<ALyraTeamPublicInfo> PublicInfo = nullptr;

	UPROPERTY()
	TObjectPtr<ALyraTeamPrivateInfo> PrivateInfo = nullptr;

	UPROPERTY()
	TObjectPtr<ULyraTeamDisplayAsset> DisplayAsset = nullptr;

	/** @Game-Change start info about if the team is NPC only team **/
	UPROPERTY()
	bool IsNPCOnlyTeam = false;
	/** @Game-Change end info about if the team is NPC only team **/

	UPROPERTY()
	FOnLyraTeamDisplayAssetChangedDelegate OnTeamDisplayAssetChanged;

public:
	void SetTeamInfo(ALyraTeamInfoBase* Info);
	void RemoveTeamInfo(ALyraTeamInfoBase* Info);
};
