#pragma once
#include <cinttypes>
#include "custom_status.h"

void GameLoad();

void GameInit(CustomStatus cs);
void GameInput(uint64_t dt);
int GameUpdate(uint64_t dt);
void GameRender(uint64_t dt);
void GameDispose();