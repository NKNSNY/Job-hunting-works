#pragma once
#include <cinttypes>
#include "custom_status.h"
#include "result_score.h"

void GameLoad();

void GameInit(CustomStatus cs);
void GameInput(uint64_t dt);
ResultScore GameUpdate(uint64_t dt);
void GameRender(uint64_t dt);
void GameDispose();