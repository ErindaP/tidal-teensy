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

#define MAX_VOICES 16  // Augmenté pour la polyphonie musicale

// Types de sons
enum SoundType {
  SOUND_KICK = 0,
  SOUND_SNARE = 1,
  SOUND_HIHAT = 2,
  SOUND_CLAP = 3,
  SOUND_TOM = 4,
  SOUND_RIM = 5,
  SOUND_CYMBAL = 6,
  // Instruments mélodiques
  SOUND_SINE = 10,      // Synthé sine wave (doux)
  SOUND_SAW = 11,       // Synthé saw wave (brillant)
  SOUND_SQUARE = 12,    // Synthé square wave (8-bit)
  SOUND_TRIANGLE = 13,  // Synthé triangle wave (flûte)
  SOUND_BASS = 14,      // Basse synthétique
  SOUND_LEAD = 15,      // Lead synthétique
  SOUND_PAD = 16,       // Pad atmosphérique
  SOUND_PLUCK = 17      // Son pincé (guitare/harpe)
};

class AudioEngine : public AudioStream {
private:
  audio_block_t *inputQueueArray[1];
  
  // Générateurs pour différents sons
  struct Voice {
    bool active;
    int type;            // Type de son (voir SoundType)
    float phase;         // Phase de l'oscillateur
    float frequency;     // Fréquence en Hz
    float decay;         // Taux de déclin
    float amplitude;     // Volume
    unsigned long startTime;
    
    // Paramètres additionnels pour instruments mélodiques
    float noteFreq;      // Fréquence de la note
    float envelope;      // Valeur actuelle de l'envelope
    float release;       // Durée du release
    bool isNote;         // True si c'est une note musicale
  };
  
  Voice voices[MAX_VOICES];
  
  // Génération de formes d'onde simples (percussion)
  float generateKick(Voice& voice, unsigned long elapsed);
  float generateSnare(Voice& voice, unsigned long elapsed);
  float generateHihat(Voice& voice, unsigned long elapsed);
  float generateClap(Voice& voice, unsigned long elapsed);
  float generateTom(Voice& voice, unsigned long elapsed);
  float generateRim(Voice& voice, unsigned long elapsed);
  float generateCymbal(Voice& voice, unsigned long elapsed);
  
  // Génération de formes d'onde pour instruments mélodiques
  float generateSine(Voice& voice, unsigned long elapsed);
  float generateSaw(Voice& voice, unsigned long elapsed);
  float generateSquare(Voice& voice, unsigned long elapsed);
  float generateTriangle(Voice& voice, unsigned long elapsed);
  float generateBass(Voice& voice, unsigned long elapsed);
  float generateLead(Voice& voice, unsigned long elapsed);
  float generatePad(Voice& voice, unsigned long elapsed);
  float generatePluck(Voice& voice, unsigned long elapsed);
  
  // Trouve une voix libre
  int findFreeVoice();
  
  // Conversion note -> fréquence (ex: "c4" -> 261.63 Hz)
  float noteToFrequency(const char* noteName);
  
  // Parse le nom de l'instrument
  int getInstrumentType(const char* name);
  
public:
  AudioEngine();
  
  virtual void update(void);
  
  // Déclenche un son (percussion ou note)
  void triggerSound(const char* sampleName, float velocity);
  
  // Déclenche une note musicale avec un instrument spécifique
  void triggerNote(const char* instrument, const char* note, float velocity, float duration = 0.5f);
  
  // Contrôles
  void setMasterVolume(float vol);
};

#endif
