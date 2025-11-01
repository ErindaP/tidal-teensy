/*
 * SerialInterface.h
 * 
 * Gère la communication série pour le live coding
 * Commandes:
 * - d1 "bd sd hh cp" -> définit pattern sur canal 1
 * - d2 "bd*4" -> définit pattern sur canal 2
 * - bpm 140 -> change le BPM
 * - clear -> efface tous les patterns
 * - hush -> alias pour clear
 */

#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H

#include <Arduino.h>
#include "PatternParser.h"
#include "Scheduler.h"

#define SERIAL_BUFFER_SIZE 256

class SerialInterface {
private:
  char buffer[SERIAL_BUFFER_SIZE];
  int bufferPos;
  
  PatternParser* parser;
  Scheduler* scheduler;
  
  // Parse et exécute une commande
  void executeCommand(const char* cmd);
  
  // Commandes spécifiques
  void cmdPattern(int channel, const char* pattern);
  void cmdBPM(float bpm);
  void cmdClear();
  void cmdHelp();
  
public:
  SerialInterface();
  
  void begin(PatternParser* p, Scheduler* s);
  void update();
  void printHelp();
  
  // Setter pour connecter les composants
  void setParser(PatternParser* p) { parser = p; }
  void setScheduler(Scheduler* s) { scheduler = s; }
};

// Instance globale
extern SerialInterface serialInterface;
extern PatternParser parser;
extern Scheduler scheduler;

#endif
