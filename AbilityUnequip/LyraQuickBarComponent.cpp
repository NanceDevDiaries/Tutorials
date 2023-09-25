/* @Game-Change begin */
void ULyraQuickBarComponent::UnequipWeapons()
{
	UnequipItemInSlot();

	ActiveSlotIndex = -1;

	OnRep_ActiveSlotIndex();
}
/** @Game-Change end **/