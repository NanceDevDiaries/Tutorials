	UPROPERTY(EditDefaultsOnly, Category = Teams)
	TMap<uint8, TObjectPtr<ULyraTeamDisplayAsset>> TeamsToCreate;

	/** @Game-Change start handle teams for non player characters, that won't spawn at PlayerStart and won't influence how many players there are per teams **/
	// Are there any teams that will be used for non-player characters? Example NPC that attack everyone and have their own team
	UPROPERTY(EditDefaultsOnly, Category = Teams, meta = (InlineEditConditionToggle))
	bool UseNPCTeams;

	// Which IDs won't be player characters. ServerAssignPlayersToTeams will ignore these indices when choosing a team for each player randomly.
	UPROPERTY(EditDefaultsOnly, Category = Teams, meta = (EditCondition = UseNPCTeams))
	TArray<int8> NPCTeamIDs;
	/** @Game-Change end handle teams for non player characters, that won't spawn at PlayerStart and won't influence how many players there are per teams **/

	UPROPERTY(EditDefaultsOnly, Category=Teams)
	TSubclassOf<ALyraTeamPublicInfo> PublicTeamInfoClass;
