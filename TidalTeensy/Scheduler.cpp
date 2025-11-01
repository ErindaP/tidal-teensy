/*
 * Scheduler.cpp
 * 
 * Implémentation du scheduler de patterns
 */

#include "Scheduler.h"

Scheduler::Scheduler() {
  bpm = 120.0f;
  currentCycle = 0.0f;
  queueHead = 0;
  queueTail = 0;
  
  for (int i = 0; i < MAX_PATTERNS; i++) {
    patterns[i].active = false;
    patterns[i].eventCount = 0;
    patterns[i].channel = i;
    lastCycleProcessed[i] = -1;
    for (int e = 0; e < MAX_EVENTS; e++) {
      patterns[i].eventTriggered[e] = false;
    }
  }
}

void Scheduler::begin(float initialBPM) {
  setBPM(initialBPM);
  cycleStartMicros = micros();
  currentCycle = 0.0f;
  
  Serial.print("[Scheduler] Initialisé à ");
  Serial.print(bpm);
  Serial.println(" BPM");
}

void Scheduler::setBPM(float newBPM) {
  if (newBPM < 20.0f) newBPM = 20.0f;
  if (newBPM > 300.0f) newBPM = 300.0f;
  
  bpm = newBPM;
  // 1 cycle = 1 mesure 4/4 = 4 beats
  // Durée d'un beat en microsecondes = 60000000 / BPM
  // Durée d'un cycle = 4 * (60000000 / BPM)
  cycleDurationMicros = (unsigned long)(240000000.0f / bpm);
  
  Serial.print("[Scheduler] BPM changé à ");
  Serial.println(bpm);
}

void Scheduler::update() {
  unsigned long currentMicros = micros();
  unsigned long elapsed = currentMicros - cycleStartMicros;
  
  // Calculer la position dans le cycle
  float cyclePos = (float)elapsed / (float)cycleDurationMicros;
  
  // Nouveau cycle ?
  if (cyclePos >= 1.0f) {
    cycleStartMicros = currentMicros;
    currentCycle += 1.0f;
    cyclePos = 0.0f;
    
    // Reset des cycles traités
    for (int i = 0; i < MAX_PATTERNS; i++) {
      lastCycleProcessed[i] = -1;
    }
  }
  
  // Vérifier les patterns
  checkPatterns();
}

float Scheduler::getCurrentCyclePosition() {
  unsigned long currentMicros = micros();
  unsigned long elapsed = currentMicros - cycleStartMicros;
  float cyclePos = (float)elapsed / (float)cycleDurationMicros;
  return (cyclePos >= 1.0f) ? 0.0f : cyclePos;
}

void Scheduler::checkPatterns() {
  float cyclePos = getCurrentCyclePosition();
  int currentCycleInt = (int)currentCycle;
  unsigned long currentTime = micros();
  
  for (int p = 0; p < MAX_PATTERNS; p++) {
    if (!patterns[p].active) continue;
    
    Pattern& pattern = patterns[p];
    
    // Si c'est un nouveau cycle, réinitialiser les flags
    if (lastCycleProcessed[p] != currentCycleInt) {
      for (int e = 0; e < pattern.eventCount; e++) {
        pattern.eventTriggered[e] = false;
      }
      lastCycleProcessed[p] = currentCycleInt;
    }
    
    // Vérifier chaque événement du pattern
    for (int e = 0; e < pattern.eventCount; e++) {
      PatternEvent& evt = pattern.events[e];
      
      if (!evt.active) continue;
      if (pattern.eventTriggered[e]) continue; // Déjà déclenché
      
      // Calculer le temps absolu de l'événement
      unsigned long eventTime = cycleStartMicros + (unsigned long)(evt.start * cycleDurationMicros);
      
      // Si on a atteint ou dépassé le moment de déclenchement
      if ((long)(currentTime - eventTime) >= 0) {
        enqueueEvent(evt.sample, evt.velocity);
        pattern.eventTriggered[e] = true;
      }
    }
  }
}

void Scheduler::enqueueEvent(const char* sample, float velocity) {
  int nextTail = (queueTail + 1) % EVENT_QUEUE_SIZE;
  
  if (nextTail == queueHead) {
    Serial.println("[Scheduler] WARN: Queue pleine!");
    return;
  }
  
  Event& evt = eventQueue[queueTail];
  strncpy(evt.sample, sample, MAX_TOKEN_LENGTH - 1);
  evt.sample[MAX_TOKEN_LENGTH - 1] = '\0';
  evt.velocity = velocity;
  evt.timestamp = micros();
  
  queueTail = nextTail;
  
  // Debug
  Serial.print("[Scheduler] Event: ");
  Serial.print(sample);
  Serial.print(" @ ");
  Serial.println(getCurrentCyclePosition(), 3);
}

bool Scheduler::hasEvents() {
  return queueHead != queueTail;
}

Event Scheduler::getNextEvent() {
  Event evt = eventQueue[queueHead];
  queueHead = (queueHead + 1) % EVENT_QUEUE_SIZE;
  return evt;
}

bool Scheduler::setPattern(int channel, const char* name, PatternEvent* events, int eventCount) {
  if (channel < 0 || channel >= MAX_PATTERNS) return false;
  
  Pattern& pattern = patterns[channel];
  
  strncpy(pattern.name, name, 15);
  pattern.name[15] = '\0';
  
  // Copier les événements
  int copyCount = (eventCount > MAX_EVENTS) ? MAX_EVENTS : eventCount;
  for (int i = 0; i < copyCount; i++) {
    pattern.events[i] = events[i];
  }
  pattern.eventCount = copyCount;
  pattern.active = true;
  
  Serial.print("[Scheduler] Pattern '");
  Serial.print(name);
  Serial.print("' chargé sur canal ");
  Serial.println(channel);
  
  return true;
}

void Scheduler::clearPattern(int channel) {
  if (channel >= 0 && channel < MAX_PATTERNS) {
    patterns[channel].active = false;
    patterns[channel].eventCount = 0;
    Serial.print("[Scheduler] Canal ");
    Serial.print(channel);
    Serial.println(" effacé");
  }
}

void Scheduler::clearAllPatterns() {
  for (int i = 0; i < MAX_PATTERNS; i++) {
    clearPattern(i);
  }
  Serial.println("[Scheduler] Tous les patterns effacés");
}
