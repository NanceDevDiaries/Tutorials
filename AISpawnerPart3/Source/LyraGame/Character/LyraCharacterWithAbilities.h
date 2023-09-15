class ULyraPawnData; // @Game-Change
class UAbilitySystemComponent;
class ULyraAbilitySystemComponent;
class UObject;

// ALyraCharacter typically gets the ability system component from the possessing player state
// This represents a character with a self-contained ability system component.
UCLASS(Blueprintable)
class LYRAGAME_API ALyraCharacterWithAbilities : public ALyraCharacter
{
	GENERATED_BODY()

public:
	ALyraCharacterWithAbilities(const FObjectInitializer& ObjectInitializer);

	virtual void PostInitializeComponents() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/* @Game-Change start since the ability system lives here and not on the playerState we want to set the ability set here */
	static const FName NAME_LyraAbilityReady;
	
	void SetPawnData(const ULyraPawnData* InPawnData);

protected:
	virtual void OnAbilitySystemInitialized() override;
	/* @Game-Change end since the ability system lives here and not on the playerState we want to set the ability set here */
	
private:

	// The ability system component sub-object used by player characters.
	UPROPERTY(VisibleAnywhere, Category = "Lyra|PlayerState")
	TObjectPtr<ULyraAbilitySystemComponent> AbilitySystemComponent;
};
