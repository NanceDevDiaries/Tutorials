/** @Game-Change start set info for NPC only Team **/
void ALyraTeamPublicInfo::SetIsNPCOnlyTeam(bool InitIsNPCTeam)
{
	IsNPCTeam = InitIsNPCTeam;

	TryRegisterWithTeamSubsystem();
}
/** @Game-Change end set info for NPC only Team **/
