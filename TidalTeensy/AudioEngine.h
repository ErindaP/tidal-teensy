/*
 * AudioEngine.h
 * 
 * Interface avec la librairie AudioStream.h
 * Gère la synthèse et les samples audio
 */

#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <Arduino.h>
#include <Audio.h>

#define MAX_VOICES 8

class AudioEngine : public AudioStream {
private:
  audio_block_t *inputQueueArray[1];
  
  // Générateurs pour différents sons
  struct Voice {
    bool active;
    int type; // 0=kick, 1=snare, 2=hihat, 3=clap
    float phase;
    float frequency;
    float decay;
    float amplitude;
    unsigned long startTime;
  };
  
  Voice voices[MAX_VOICES];
  
  // Génération de formes d'onde simples
  float generateKick(Voice& voice, unsigned long elapsed);
  float generateSnare(Voice& voice, unsigned long elapsed);
  float generateHihat(Voice& voice, unsigned long elapsed);
  float generateClap(Voice& voice, unsigned long elapsed);
  
  // Trouve une voix libre
  int findFreeVoice();
  
public:
  AudioEngine();
  
  virtual void update(void);
  
  // Déclenche un son
  void triggerSound(const char* sampleName, float velocity);
  
  // Contrôles
  void setMasterVolume(float vol);
};

#endif
