// Fill out your copyright notice in the Description page of Project Settings.


#include "PacPongPlayerState.h"

bool APacPongPlayerState::UpdateHighScore(int64 NewScore)
{
	return true;
}

int64 APacPongPlayerState::GetPacScore() const
{
	return 123;
}

void APacPongPlayerState::AddScore(int64 NewScore)
{
}

bool APacPongPlayerState::RemoveScore(int64 NewScore)
{
	return true;
}

void APacPongPlayerState::SavePlayerState(USavePacGame* PacSaveObject)
{
}

void APacPongPlayerState::LoadPlayerState(USavePacGame* PacSaveObject)
{
}
