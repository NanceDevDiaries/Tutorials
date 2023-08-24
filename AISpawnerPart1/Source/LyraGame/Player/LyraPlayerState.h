public:
	// @Game-Change function to listen to Experience ready for using default pawn data in the loaded Experiment
	void RegisterToExperienceLoadedToSetPawnData();

protected:
	// @Game-Change keep track to make sure the PawnData isn't set more than once while the playerState exists
	// needed since we're no longer calling that logic in PostInitializeComponents(); which only happened once per playerState
	bool bRegisteredToExperienceLoaded;
