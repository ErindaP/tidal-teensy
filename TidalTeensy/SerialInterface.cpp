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
  Serial.println("=== TidalTeensy Commands ===");
  Serial.println();
  Serial.println("PERCUSSIONS:");
  Serial.println("  d1 bd sd hh cp      - Drums on channel 1");
  Serial.println("  d2 bd*4             - bd played 4 times");
  Serial.println("  d3 bd sd ~ hh       - ~ = silence");
  Serial.println("  Samples: bd/kick, sd/snare, hh/hat, cp/clap");
  Serial.println("           tom, rim, cymbal/crash/ride");
  Serial.println();
  Serial.println("NOTES MUSICALES:");
  Serial.println("  d4 sine:c4 sine:e4 sine:g4   - Sine wave chord");
  Serial.println("  d5 bass:a2*4                 - Bass line");
  Serial.println("  d6 lead:c4 lead:e4           - Lead melody");
  Serial.println();
  Serial.println("  Instruments: sine, saw, square, triangle,");
  Serial.println("               bass, lead, pad, pluck");
  Serial.println("  Notes: c3-c5, d3-d5, e3-e5, etc.");
  Serial.println("         Use # for sharp, b for flat");
  Serial.println("         Ex: c#4, db3, f#5");
  Serial.println();
  Serial.println("CONTROLS:");
  Serial.println("  bpm 140             - Change tempo");
  Serial.println("  clear / hush        - Clear all patterns");
  Serial.println("  d1 silence          - Clear channel 1");
  Serial.println("  help                - Show this help");
  Serial.println();
  Serial.println("EXAMPLES:");
  Serial.println("  d1 bd sd hh cp");
  Serial.println("  d2 bass:c2 bass:c2 bass:g2 bass:f2");
  Serial.println("  d3 lead:c4 ~ lead:e4 lead:g4");
  Serial.println("  d4 hh*8");
  Serial.println("  bpm 128");
  Serial.println();
  Serial.println("Current BPM: " + String(scheduler ? scheduler->getBPM() : 120.0f));
  Serial.println();
}
