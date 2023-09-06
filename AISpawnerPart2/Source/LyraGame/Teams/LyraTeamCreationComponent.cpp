void ULyraTeamCreationComponent::ServerAssignPlayersToTeams()
{
	// Assign players that already exist to teams
	AGameStateBase* GameState = GetGameStateChecked<AGameStateBase>();
	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (ALyraPlayerState* LyraPS = Cast<ALyraPlayerState>(PS))
		{
			// @Game-Change start skip choosing a team for NPC spawned characters with a PlayerState
			// #todo handle when the NPC has the same team as the player ID. Should we balance the number of players on both sides?
			// Skip choosing a team for the player if they already have a team
			if (const int32 TeamID = LyraPS->GetTeamId(); TeamID != INDEX_NONE) // && NPCTeamIDs.Contains(TeamID))
			{
				continue;
			}
			// @Game-Change end skip choosing a team for NPC spawned characters with a PlayerState, should be set in the NPCSpawner

			ServerChooseTeamForPlayer(LyraPS);
		}
	}

	// Listen for new players logging in
	ALyraGameMode* GameMode = Cast<ALyraGameMode>(GameState->AuthorityGameMode);
	check(GameMode);

	GameMode->OnGameModePlayerInitialized.AddUObject(this, &ThisClass::OnPlayerInitialized);
}

void ULyraTeamCreationComponent::OnPlayerInitialized(AGameModeBase* GameMode, AController* NewPlayer)
{
	check(NewPlayer);
	check(NewPlayer->PlayerState);
	if (ALyraPlayerState* LyraPS = Cast<ALyraPlayerState>(NewPlayer->PlayerState))
	{
		// @Game-Change start skip choosing a team for NPC spawned characters with a PlayerState
		// #todo handle when the NPC has the same team as the player ID. Should we balance the number of players on both sides?
		// Skip choosing a team for the player if they already have a team
		if (const int32 TeamID = LyraPS->GetTeamId(); TeamID != INDEX_NONE) // && NPCTeamIDs.Contains(TeamID))
		{
			return;
		}
		// @Game-Change end skip choosing a team for NPC spawned characters with a PlayerState, should be set in the NPCSpawner

		ServerChooseTeamForPlayer(LyraPS);
	}
}

int32 ULyraTeamCreationComponent::GetLeastPopulatedTeamID() const
{
	// @Game-Change don't consider NPC teams when choosing the least populatedTeamID
	const int32 NumTeams = UseNPCTeams ? TeamsToCreate.Num() - NPCTeamIDs.Num() : TeamsToCreate.Num();
	if (NumTeams > 0)
	{
		TMap<int32, uint32> TeamMemberCounts;
		TeamMemberCounts.Reserve(NumTeams);
		for (const auto& KVP : TeamsToCreate)
		{
			const int32 TeamId = KVP.Key;
			// @Game-Change don't consider NPC teams when choosing the least populatedTeamID
			if (NPCTeamIDs.Contains(TeamId)) continue; // skip the npc teams
			TeamMemberCounts.Add(TeamId, 0);
		}

		AGameStateBase* GameState = GetGameStateChecked<AGameStateBase>();
		for (APlayerState* PS : GameState->PlayerArray)
		{
			if (ALyraPlayerState* LyraPS = Cast<ALyraPlayerState>(PS))
			{
				const int32 PlayerTeamID = LyraPS->GetTeamId();

				// @Game-Change don't consider NPC teams when choosing the least populatedTeamID
				if (NPCTeamIDs.Contains(PlayerTeamID)) continue; // skip the npc teams

				if ((PlayerTeamID != INDEX_NONE) && !LyraPS->IsInactive())
				// do not count unassigned or disconnected players
				{
					check(TeamMemberCounts.Contains(PlayerTeamID))
					TeamMemberCounts[PlayerTeamID] += 1;
				}
			}
		}
/// ....


// To add later with the LyraTeamPublicInfo change

void ULyraTeamCreationComponent::ServerCreateTeam(int32 TeamId, ULyraTeamDisplayAsset* DisplayAsset)
{
	check(HasAuthority());

	//@TODO: ensure the team doesn't already exist

	UWorld* World = GetWorld();
	check(World);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ALyraTeamPublicInfo* NewTeamPublicInfo = World->SpawnActor<ALyraTeamPublicInfo>(PublicTeamInfoClass, SpawnInfo);
	checkf(NewTeamPublicInfo != nullptr, TEXT("Failed to create public team actor from class %s"), *GetPathNameSafe(*PublicTeamInfoClass));
	NewTeamPublicInfo->SetTeamId(TeamId);
	// @Game-Change Set Is NPC only team so we can access that info after creating the teams, during gameplay
	NewTeamPublicInfo->SetIsNPCOnlyTeam(NPCTeamIDs.Contains(TeamId));
	NewTeamPublicInfo->SetTeamDisplayAsset(DisplayAsset);

	ALyraTeamPrivateInfo* NewTeamPrivateInfo = World->SpawnActor<ALyraTeamPrivateInfo>(PrivateTeamInfoClass, SpawnInfo);
	checkf(NewTeamPrivateInfo != nullptr, TEXT("Failed to create private team actor from class %s"), *GetPathNameSafe(*PrivateTeamInfoClass));
	NewTeamPrivateInfo->SetTeamId(TeamId);
}