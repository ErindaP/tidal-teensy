/*
 * AudioEngine.cpp
 * 
 * Implémentation du moteur audio
 * Synthèse simple de sons de batterie
 */

#include "AudioEngine.h"

AudioEngine::AudioEngine() : AudioStream(0, inputQueueArray) {
  for (int i = 0; i < MAX_VOICES; i++) {
    voices[i].active = false;
    voices[i].phase = 0.0f;
  }
}

void AudioEngine::update(void) {
  audio_block_t *block;
  
  block = allocate();
  if (!block) return;
  
  // Remplir le buffer avec les sons actifs
  for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
    float sample = 0.0f;
    unsigned long currentTime = micros();
    
    // Mixer toutes les voix actives
    for (int v = 0; v < MAX_VOICES; v++) {
      if (!voices[v].active) continue;
      
      unsigned long elapsed = currentTime - voices[v].startTime;
      float voiceSample = 0.0f;
      
      switch (voices[v].type) {
        case 0: voiceSample = generateKick(voices[v], elapsed); break;
        case 1: voiceSample = generateSnare(voices[v], elapsed); break;
        case 2: voiceSample = generateHihat(voices[v], elapsed); break;
        case 3: voiceSample = generateClap(voices[v], elapsed); break;
      }
      
      sample += voiceSample * voices[v].amplitude;
      
      // Désactiver si terminé (après 500ms)
      if (elapsed > 500000) {
        voices[v].active = false;
      }
    }
    
    // Limiter et convertir en int16
    if (sample > 1.0f) sample = 1.0f;
    if (sample < -1.0f) sample = -1.0f;
    block->data[i] = (int16_t)(sample * 32767.0f);
  }
  
  transmit(block);
  release(block);
}

float AudioEngine::generateKick(Voice& voice, unsigned long elapsed) {
  // Kick = sine wave avec pitch qui descend + envelope
  float t = elapsed / 1000000.0f; // temps en secondes
  
  if (t > 0.3f) return 0.0f;
  
  // Pitch envelope: 80Hz -> 40Hz
  float freq = 80.0f - (t * 133.0f);
  if (freq < 40.0f) freq = 40.0f;
  
  // Amplitude envelope
  float env = exp(-t * 8.0f);
  
  // Sine wave
  voice.phase += freq * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  
  return sin(voice.phase) * env;
}

float AudioEngine::generateSnare(Voice& voice, unsigned long elapsed) {
  // Snare = noise + pitched tone + envelope
  float t = elapsed / 1000000.0f;
  
  if (t > 0.2f) return 0.0f;
  
  // Noise component
  float noise = ((float)random(-32768, 32767) / 32768.0f) * 0.7f;
  
  // Tone component (200Hz)
  voice.phase += 200.0f * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  float tone = sin(voice.phase) * 0.3f;
  
  // Sharp envelope
  float env = exp(-t * 15.0f);
  
  return (noise + tone) * env;
}

float AudioEngine::generateHihat(Voice& voice, unsigned long elapsed) {
  // Hihat = filtered noise + très court
  float t = elapsed / 1000000.0f;
  
  if (t > 0.1f) return 0.0f;
  
  // High-frequency noise
  float noise = ((float)random(-32768, 32767) / 32768.0f);
  
  // Very sharp envelope
  float env = exp(-t * 25.0f);
  
  return noise * env * 0.5f;
}

float AudioEngine::generateClap(Voice& voice, unsigned long elapsed) {
  // Clap = burst of noise with multiple hits
  float t = elapsed / 1000000.0f;
  
  if (t > 0.15f) return 0.0f;
  
  float noise = ((float)random(-32768, 32767) / 32768.0f);
  
  // Multiple attack envelopes to simulate multiple reflections
  float env = 0.0f;
  if (t < 0.02f) env += exp(-t * 80.0f);
  if (t > 0.01f && t < 0.04f) env += exp(-(t - 0.01f) * 60.0f) * 0.7f;
  if (t > 0.02f && t < 0.06f) env += exp(-(t - 0.02f) * 40.0f) * 0.5f;
  
  return noise * env * 0.6f;
}

int AudioEngine::findFreeVoice() {
  for (int i = 0; i < MAX_VOICES; i++) {
    if (!voices[i].active) return i;
  }
  // Si aucune voix libre, prendre la plus ancienne
  return 0;
}

void AudioEngine::triggerSound(const char* sampleName, float velocity) {
  int voiceIdx = findFreeVoice();
  Voice& voice = voices[voiceIdx];
  
  voice.active = true;
  voice.phase = 0.0f;
  voice.amplitude = velocity;
  voice.startTime = micros();
  
  // Déterminer le type de son
  if (strcmp(sampleName, "bd") == 0 || strcmp(sampleName, "kick") == 0) {
    voice.type = 0;
  } else if (strcmp(sampleName, "sd") == 0 || strcmp(sampleName, "snare") == 0 || 
             strcmp(sampleName, "sn") == 0) {
    voice.type = 1;
  } else if (strcmp(sampleName, "hh") == 0 || strcmp(sampleName, "hat") == 0) {
    voice.type = 2;
  } else if (strcmp(sampleName, "cp") == 0 || strcmp(sampleName, "clap") == 0) {
    voice.type = 3;
  } else {
    voice.type = 0; // default to kick
  }
}

void AudioEngine::setMasterVolume(float vol) {
  // À implémenter si besoin
}
