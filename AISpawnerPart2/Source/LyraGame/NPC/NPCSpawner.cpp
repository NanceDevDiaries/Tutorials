
// In ANPCSpawner::SpawnAIFromClass
			if (NewPawn->Controller == NULL)
			{
				// NOTE: SpawnDefaultController ALSO calls Possess() to possess the pawn (if a controller is successfully spawned).
				NewPawn->SpawnDefaultController();

				// New Change From Part 2 start
				if (APlayerState* PlayerState = NewPawn->Controller->PlayerState)
				{
					PlayerState->SetPlayerName("NPC Pawn"); // #todo get the name from PawnData maybe or other ways
				}
				// New Change From Part 2 end
			}
