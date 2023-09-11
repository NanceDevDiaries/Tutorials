	/** @Game-Change  **/
	void SetVolumeCameraMode(TSubclassOf<ULyraCameraMode> CameraMode);
	void ClearVolumeCameraMode();
    
protected:    
    
    /** @Game-Change Camera mode when walking in a CameraModeVolume. **/
	TSubclassOf<ULyraCameraMode> VolumeCameraMode;