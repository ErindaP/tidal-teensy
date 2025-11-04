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
    voices[i].isNote = false;
    voices[i].envelope = 0.0f;
    voices[i].release = 0.5f;
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
        // Percussion
        case SOUND_KICK: voiceSample = generateKick(voices[v], elapsed); break;
        case SOUND_SNARE: voiceSample = generateSnare(voices[v], elapsed); break;
        case SOUND_HIHAT: voiceSample = generateHihat(voices[v], elapsed); break;
        case SOUND_CLAP: voiceSample = generateClap(voices[v], elapsed); break;
        case SOUND_TOM: voiceSample = generateTom(voices[v], elapsed); break;
        case SOUND_RIM: voiceSample = generateRim(voices[v], elapsed); break;
        case SOUND_CYMBAL: voiceSample = generateCymbal(voices[v], elapsed); break;
        // Instruments mélodiques
        case SOUND_SINE: voiceSample = generateSine(voices[v], elapsed); break;
        case SOUND_SAW: voiceSample = generateSaw(voices[v], elapsed); break;
        case SOUND_SQUARE: voiceSample = generateSquare(voices[v], elapsed); break;
        case SOUND_TRIANGLE: voiceSample = generateTriangle(voices[v], elapsed); break;
        case SOUND_BASS: voiceSample = generateBass(voices[v], elapsed); break;
        case SOUND_LEAD: voiceSample = generateLead(voices[v], elapsed); break;
        case SOUND_PAD: voiceSample = generatePad(voices[v], elapsed); break;
        case SOUND_PLUCK: voiceSample = generatePluck(voices[v], elapsed); break;
      }
      
      sample += voiceSample * voices[v].amplitude;
      
      // Désactiver si terminé
      unsigned long maxDuration = voices[v].isNote ? 
                                  (unsigned long)(voices[v].release * 1000000.0f) : 500000;
      if (elapsed > maxDuration) {
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

// ============ NOUVELLES PERCUSSIONS ============

float AudioEngine::generateTom(Voice& voice, unsigned long elapsed) {
  float t = elapsed / 1000000.0f;
  if (t > 0.4f) return 0.0f;
  
  // Tom = sine avec pitch qui descend (plus aigu que kick)
  float freq = 150.0f - (t * 250.0f);
  if (freq < 80.0f) freq = 80.0f;
  
  voice.phase += freq * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  
  float env = exp(-t * 10.0f);
  return sin(voice.phase) * env * 0.8f;
}

float AudioEngine::generateRim(Voice& voice, unsigned long elapsed) {
  float t = elapsed / 1000000.0f;
  if (t > 0.05f) return 0.0f;
  
  // Rimshot = click très court + harmoniques
  float noise = ((float)random(-32768, 32767) / 32768.0f) * 0.5f;
  
  voice.phase += 2000.0f * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  float tone = sin(voice.phase) * 0.5f;
  
  float env = exp(-t * 60.0f);
  return (noise + tone) * env;
}

float AudioEngine::generateCymbal(Voice& voice, unsigned long elapsed) {
  float t = elapsed / 1000000.0f;
  if (t > 0.8f) return 0.0f;
  
  // Cymbal = noise filtré avec release long
  float noise = ((float)random(-32768, 32767) / 32768.0f);
  float env = exp(-t * 3.5f);
  
  return noise * env * 0.4f;
}

// ============ INSTRUMENTS MÉLODIQUES ============

float AudioEngine::generateSine(Voice& voice, unsigned long elapsed) {
  float t = elapsed / 1000000.0f;
  if (t > voice.release) return 0.0f;
  
  // Envelope ADSR simple
  float env;
  if (t < 0.01f) {
    env = t / 0.01f;  // Attack
  } else if (t < 0.1f) {
    env = 1.0f - (t - 0.01f) / 0.09f * 0.3f;  // Decay to 0.7
  } else if (t < voice.release * 0.7f) {
    env = 0.7f;  // Sustain
  } else {
    env = 0.7f * (1.0f - (t - voice.release * 0.7f) / (voice.release * 0.3f));  // Release
  }
  
  // Sine wave
  voice.phase += voice.noteFreq * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  
  return sin(voice.phase) * env;
}

float AudioEngine::generateSaw(Voice& voice, unsigned long elapsed) {
  float t = elapsed / 1000000.0f;
  if (t > voice.release) return 0.0f;
  
  // Envelope
  float env;
  if (t < 0.005f) {
    env = t / 0.005f;
  } else if (t < 0.05f) {
    env = 1.0f - (t - 0.005f) / 0.045f * 0.2f;
  } else if (t < voice.release * 0.7f) {
    env = 0.8f;
  } else {
    env = 0.8f * (1.0f - (t - voice.release * 0.7f) / (voice.release * 0.3f));
  }
  
  // Sawtooth wave (plus brillant)
  voice.phase += voice.noteFreq * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  
  float saw = 2.0f * (voice.phase / (2.0f * PI)) - 1.0f;
  return saw * env * 0.7f;
}

float AudioEngine::generateSquare(Voice& voice, unsigned long elapsed) {
  float t = elapsed / 1000000.0f;
  if (t > voice.release) return 0.0f;
  
  // Envelope
  float env;
  if (t < 0.005f) {
    env = t / 0.005f;
  } else if (t < voice.release * 0.8f) {
    env = 1.0f;
  } else {
    env = 1.0f - (t - voice.release * 0.8f) / (voice.release * 0.2f);
  }
  
  // Square wave (son 8-bit)
  voice.phase += voice.noteFreq * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  
  float square = (voice.phase < PI) ? 1.0f : -1.0f;
  return square * env * 0.5f;
}

float AudioEngine::generateTriangle(Voice& voice, unsigned long elapsed) {
  float t = elapsed / 1000000.0f;
  if (t > voice.release) return 0.0f;
  
  // Envelope
  float env;
  if (t < 0.01f) {
    env = t / 0.01f;
  } else if (t < voice.release * 0.7f) {
    env = 1.0f;
  } else {
    env = 1.0f - (t - voice.release * 0.7f) / (voice.release * 0.3f);
  }
  
  // Triangle wave (son de flûte)
  voice.phase += voice.noteFreq * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  
  float tri = (voice.phase < PI) ? 
              (2.0f * voice.phase / PI - 1.0f) : 
              (3.0f - 2.0f * voice.phase / PI);
  return tri * env * 0.6f;
}

float AudioEngine::generateBass(Voice& voice, unsigned long elapsed) {
  float t = elapsed / 1000000.0f;
  if (t > voice.release) return 0.0f;
  
  // Envelope court pour la basse
  float env;
  if (t < 0.003f) {
    env = t / 0.003f;
  } else if (t < 0.05f) {
    env = 1.0f - (t - 0.003f) / 0.047f * 0.5f;
  } else {
    env = 0.5f * exp(-(t - 0.05f) * 8.0f);
  }
  
  // Sine wave avec harmonique (son plus riche)
  voice.phase += voice.noteFreq * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  
  float fundamental = sin(voice.phase);
  float harmonic = sin(voice.phase * 2.0f) * 0.3f;
  
  return (fundamental + harmonic) * env * 0.9f;
}

float AudioEngine::generateLead(Voice& voice, unsigned long elapsed) {
  float t = elapsed / 1000000.0f;
  if (t > voice.release) return 0.0f;
  
  // Envelope
  float env;
  if (t < 0.01f) {
    env = t / 0.01f;
  } else if (t < 0.1f) {
    env = 1.0f;
  } else if (t < voice.release * 0.6f) {
    env = 1.0f - (t - 0.1f) / (voice.release * 0.6f - 0.1f) * 0.3f;
  } else {
    env = 0.7f * (1.0f - (t - voice.release * 0.6f) / (voice.release * 0.4f));
  }
  
  // Sawtooth avec vibrato
  float vibrato = 1.0f + 0.003f * sin(2.0f * PI * 5.0f * t);  // 5Hz vibrato
  voice.phase += voice.noteFreq * vibrato * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  
  float saw = 2.0f * (voice.phase / (2.0f * PI)) - 1.0f;
  return saw * env * 0.6f;
}

float AudioEngine::generatePad(Voice& voice, unsigned long elapsed) {
  float t = elapsed / 1000000.0f;
  if (t > voice.release) return 0.0f;
  
  // Envelope très doux
  float env;
  if (t < 0.3f) {
    env = t / 0.3f;  // Attack lent
  } else if (t < voice.release * 0.5f) {
    env = 1.0f;
  } else {
    env = 1.0f - (t - voice.release * 0.5f) / (voice.release * 0.5f);
  }
  
  // Mix de plusieurs ondes sinusoïdales (accord)
  voice.phase += voice.noteFreq * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  
  float sine1 = sin(voice.phase);
  float sine2 = sin(voice.phase * 1.5f) * 0.5f;  // Quinte
  float sine3 = sin(voice.phase * 2.0f) * 0.3f;  // Octave
  
  return (sine1 + sine2 + sine3) * env * 0.4f;
}

float AudioEngine::generatePluck(Voice& voice, unsigned long elapsed) {
  float t = elapsed / 1000000.0f;
  if (t > voice.release) return 0.0f;
  
  // Envelope qui décroît rapidement (son pincé)
  float env = exp(-t * 5.0f);
  
  // Triangle wave avec harmoniques
  voice.phase += voice.noteFreq * (2.0f * PI) / AUDIO_SAMPLE_RATE_EXACT;
  if (voice.phase > 2.0f * PI) voice.phase -= 2.0f * PI;
  
  float tri = (voice.phase < PI) ? 
              (2.0f * voice.phase / PI - 1.0f) : 
              (3.0f - 2.0f * voice.phase / PI);
              
  float harmonic = sin(voice.phase * 2.0f) * 0.3f;
  
  return (tri + harmonic) * env * 0.7f;
}

int AudioEngine::findFreeVoice() {
  for (int i = 0; i < MAX_VOICES; i++) {
    if (!voices[i].active) return i;
  }
  // Si aucune voix libre, prendre la plus ancienne
  return 0;
}

void AudioEngine::triggerSound(const char* sampleName, float velocity) {
  // Vérifie si c'est une note musicale (ex: "sine:c4", "bass:a3")
  if (strchr(sampleName, ':') != NULL) {
    // Format: "instrument:note"
    char inst[16], note[8];
    int colonPos = 0;
    while (sampleName[colonPos] != ':' && sampleName[colonPos] != '\0') colonPos++;
    
    strncpy(inst, sampleName, colonPos);
    inst[colonPos] = '\0';
    strcpy(note, sampleName + colonPos + 1);
    
    triggerNote(inst, note, velocity, 0.5f);
    return;
  }
  
  // Sinon, c'est une percussion classique
  int voiceIdx = findFreeVoice();
  Voice& voice = voices[voiceIdx];
  
  voice.active = true;
  voice.phase = 0.0f;
  voice.amplitude = velocity;
  voice.startTime = micros();
  voice.isNote = false;
  
  // Déterminer le type de son (percussion)
  if (strcmp(sampleName, "bd") == 0 || strcmp(sampleName, "kick") == 0) {
    voice.type = SOUND_KICK;
  } else if (strcmp(sampleName, "sd") == 0 || strcmp(sampleName, "snare") == 0 || 
             strcmp(sampleName, "sn") == 0) {
    voice.type = SOUND_SNARE;
  } else if (strcmp(sampleName, "hh") == 0 || strcmp(sampleName, "hat") == 0) {
    voice.type = SOUND_HIHAT;
  } else if (strcmp(sampleName, "cp") == 0 || strcmp(sampleName, "clap") == 0) {
    voice.type = SOUND_CLAP;
  } else if (strcmp(sampleName, "tom") == 0 || strcmp(sampleName, "lt") == 0 || strcmp(sampleName, "mt") == 0) {
    voice.type = SOUND_TOM;
  } else if (strcmp(sampleName, "rim") == 0 || strcmp(sampleName, "rs") == 0) {
    voice.type = SOUND_RIM;
  } else if (strcmp(sampleName, "cymbal") == 0 || strcmp(sampleName, "crash") == 0 || strcmp(sampleName, "ride") == 0) {
    voice.type = SOUND_CYMBAL;
  } else {
    voice.type = SOUND_KICK; // default
  }
}

void AudioEngine::triggerNote(const char* instrument, const char* note, float velocity, float duration) {
  int voiceIdx = findFreeVoice();
  Voice& voice = voices[voiceIdx];
  
  voice.active = true;
  voice.phase = 0.0f;
  voice.amplitude = velocity;
  voice.startTime = micros();
  voice.isNote = true;
  voice.release = duration;
  voice.noteFreq = noteToFrequency(note);
  voice.type = getInstrumentType(instrument);
  
  Serial.print("[AudioEngine] Note: ");
  Serial.print(instrument);
  Serial.print(" ");
  Serial.print(note);
  Serial.print(" @ ");
  Serial.print(voice.noteFreq);
  Serial.println(" Hz");
}

float AudioEngine::noteToFrequency(const char* noteName) {
  // Format: "c4", "d#3", "ab5", etc.
  // Notes: c, c#/db, d, d#/eb, e, f, f#/gb, g, g#/ab, a, a#/bb, b
  
  if (strlen(noteName) < 2) return 440.0f;  // La par défaut
  
  char note = tolower(noteName[0]);
  int octave = noteName[strlen(noteName) - 1] - '0';
  bool sharp = (noteName[1] == '#');
  bool flat = (noteName[1] == 'b');
  
  // Correspondance note -> demi-tons depuis C
  int semitone = 0;
  switch (note) {
    case 'c': semitone = 0; break;
    case 'd': semitone = 2; break;
    case 'e': semitone = 4; break;
    case 'f': semitone = 5; break;
    case 'g': semitone = 7; break;
    case 'a': semitone = 9; break;
    case 'b': semitone = 11; break;
    default: semitone = 9; // La par défaut
  }
  
  if (sharp) semitone++;
  if (flat) semitone--;
  
  // Calcul de la fréquence : f = 440 * 2^((n-57)/12)
  // où n = numéro de note MIDI (A4 = 69, C4 = 60)
  int midiNote = (octave + 1) * 12 + semitone;
  float freq = 440.0f * pow(2.0f, (midiNote - 69) / 12.0f);
  
  return freq;
}

int AudioEngine::getInstrumentType(const char* name) {
  if (strcmp(name, "sine") == 0 || strcmp(name, "sin") == 0) return SOUND_SINE;
  if (strcmp(name, "saw") == 0 || strcmp(name, "sawtooth") == 0) return SOUND_SAW;
  if (strcmp(name, "square") == 0 || strcmp(name, "pulse") == 0) return SOUND_SQUARE;
  if (strcmp(name, "triangle") == 0 || strcmp(name, "tri") == 0) return SOUND_TRIANGLE;
  if (strcmp(name, "bass") == 0) return SOUND_BASS;
  if (strcmp(name, "lead") == 0) return SOUND_LEAD;
  if (strcmp(name, "pad") == 0) return SOUND_PAD;
  if (strcmp(name, "pluck") == 0 || strcmp(name, "harp") == 0) return SOUND_PLUCK;
  
  return SOUND_SINE;  // Default
}

void AudioEngine::setMasterVolume(float vol) {
  // À implémenter si besoin
}
