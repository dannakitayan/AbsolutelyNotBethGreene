#ifndef BUFFERS_H
#define BUFFERS_H

void InitializeBuffers();

void FeelModelsBuffer();
void FeelSoundsBuffer();
void FeelTexturesBuffer();

void FreeModelsBuffer();
void FreeSoundsBuffer();
void FreeTexturesBuffer();

void AddToModelsBuffer();
void AddToSoundsBuffer(); 
void AddToTexturesBuffer();

#endif
