/*
 * SerialInterface.cpp
 * 
 * Implémentation de l'interface série
 */

#include "SerialInterface.h"

SerialInterface::SerialInterface() {
  bufferPos = 0;
  parser = nullptr;
  scheduler = nullptr;
}

void SerialInterface::begin(PatternParser* p, Scheduler* s) {
  parser = p;
  scheduler = s;
  bufferPos = 0;
  Serial.println("[SerialInterface] Prêt");
}

void SerialInterface::update() {
  // Lire les données série disponibles
  while (Serial.available() > 0) {
    char c = Serial.read();
    
    // Fin de ligne
    if (c == '\n' || c == '\r') {
      if (bufferPos > 0) {
        buffer[bufferPos] = '\0';
        executeCommand(buffer);
        bufferPos = 0;
      }
    }
    // Ajouter au buffer
    else if (bufferPos < SERIAL_BUFFER_SIZE - 1) {
      buffer[bufferPos++] = c;
    }
  }
}

void SerialInterface::executeCommand(const char* cmd) {
  Serial.print("> ");
  Serial.println(cmd);
  
  // Trim leading spaces
  while (*cmd == ' ') cmd++;
  
  if (strlen(cmd) == 0) return;
  
  // Pattern: d1 "bd sd hh"
  if (cmd[0] == 'd' && cmd[1] >= '1' && cmd[1] <= '8') {
    int channel = cmd[1] - '1';
    
    // Trouver le début du pattern (après d1 et espaces)
    const char* pattern = cmd + 2;
    while (*pattern == ' ') pattern++;
    
    // Enlever les guillemets si présents
    if (*pattern == '"') {
      pattern++;
      char* end = strchr((char*)pattern, '"');
      if (end) *end = '\0';
    }
    
    cmdPattern(channel, pattern);
  }
  // BPM: bpm 140
  else if (strncmp(cmd, "bpm ", 4) == 0) {
    float bpm = atof(cmd + 4);
    cmdBPM(bpm);
  }
  // Clear / Hush
  else if (strcmp(cmd, "clear") == 0 || strcmp(cmd, "hush") == 0) {
    cmdClear();
  }
  // Help
  else if (strcmp(cmd, "help") == 0 || strcmp(cmd, "?") == 0) {
    cmdHelp();
  }
  // Silence pattern: d1 silence
  else if (cmd[0] == 'd' && cmd[1] >= '1' && cmd[1] <= '8') {
    // Vérifier si c'est une commande silence
    const char* rest = cmd + 2;
    while (*rest == ' ') rest++;
    
    if (strcmp(rest, "silence") == 0 || strlen(rest) == 0) {
      int channel = cmd[1] - '1';
      if (scheduler) {
        scheduler->clearPattern(channel);
        Serial.print("✓ Canal d");
        Serial.print(channel + 1);
        Serial.println(" silencé");
      }
    } else {
      Serial.println("Format: d1 <pattern> ou d1 silence");
    }
  }
  else {
    Serial.println("Commande inconnue. Tapez 'help' pour l'aide.");
  }
}

void SerialInterface::cmdPattern(int channel, const char* pattern) {
  if (!parser || !scheduler) {
    Serial.println("Erreur: composants non initialisés");
    return;
  }
  
  PatternEvent events[MAX_EVENTS];
  int eventCount;
  
  if (parser->parse(pattern, events, &eventCount)) {
    char name[16];
    snprintf(name, 16, "d%d", channel + 1);
    scheduler->setPattern(channel, name, events, eventCount);
    Serial.print("✓ Pattern chargé sur d");
    Serial.println(channel + 1);
  } else {
    Serial.println("✗ Erreur de parsing");
  }
}

void SerialInterface::cmdBPM(float bpm) {
  if (!scheduler) return;
  
  scheduler->setBPM(bpm);
  Serial.print("✓ BPM: ");
  Serial.println(bpm);
}

void SerialInterface::cmdClear() {
  if (!scheduler) return;
  
  scheduler->clearAllPatterns();
  Serial.println("✓ Tous les patterns effacés");
}

void SerialInterface::cmdHelp() {
  printHelp();
}

void SerialInterface::printHelp() {
  Serial.println();
  Serial.println("=== Commandes TidalTeensy ===");
  Serial.println();
  Serial.println("Patterns:");
  Serial.println("  d1 bd sd hh cp      - Pattern sur canal 1");
  Serial.println("  d2 bd*4             - bd joué 4 fois");
  Serial.println("  d3 bd sd ~ hh       - ~ = silence");
  Serial.println("  d1 silence          - Efface le canal 1");
  Serial.println();
  Serial.println("Contrôles:");
  Serial.println("  bpm 140             - Change le tempo");
  Serial.println("  clear / hush        - Efface tous les patterns");
  Serial.println("  help                - Affiche cette aide");
  Serial.println();
  Serial.println("Samples disponibles:");
  Serial.println("  bd/kick, sd/snare/sn, hh/hat, cp/clap");
  Serial.println();
  Serial.println("BPM actuel: " + String(scheduler ? scheduler->getBPM() : 120.0f));
  Serial.println();
}
