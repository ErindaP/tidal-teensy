/*
 * Scheduler.h
 * 
 * Gère le timing et les cycles
 * - Maintient un compteur de temps précis
 * - Gère les patterns actifs
 * - Génère les événements au bon moment
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>
#include "PatternParser.h"

#define MAX_PATTERNS 8
#define EVENT_QUEUE_SIZE 64

struct Event {
  char sample[MAX_TOKEN_LENGTH];
  float velocity;
  unsigned long timestamp;
};

struct Pattern {
  char name[16];
  PatternEvent events[MAX_EVENTS];
  int eventCount;
  bool active;
  int channel; // 0-7, permet d'avoir plusieurs patterns simultanés
  bool eventTriggered[MAX_EVENTS]; // Track quels événements ont été déclenchés ce cycle
};

class Scheduler {
private:
  float bpm;
  unsigned long cycleStartMicros;
  unsigned long cycleDurationMicros;
  float currentCycle;
  
  Pattern patterns[MAX_PATTERNS];
  Event eventQueue[EVENT_QUEUE_SIZE];
  int queueHead;
  int queueTail;
  
  // Calcule la position actuelle dans le cycle (0.0 - 1.0)
  float getCurrentCyclePosition();
  
  // Vérifie si des événements doivent être déclenchés
  void checkPatterns();
  
  // Ajoute un événement à la queue
  void enqueueEvent(const char* sample, float velocity);
  
  // Dernier cycle traité pour chaque pattern
  int lastCycleProcessed[MAX_PATTERNS];
  
public:
  Scheduler();
  
  void begin(float bpm);
  void setBPM(float bpm);
  void update();
  
  // Gestion des patterns
  bool setPattern(int channel, const char* name, PatternEvent* events, int eventCount);
  void clearPattern(int channel);
  void clearAllPatterns();
  
  // Queue d'événements
  bool hasEvents();
  Event getNextEvent();
  
  // Info
  float getBPM() { return bpm; }
  float getCurrentCycle() { return currentCycle; }
};

#endif
