/*
 * PatternParser.h
 * 
 * Parse les patterns de type Tidal Cycles
 * Exemples:
 * - "bd sd hh cp" -> 4 sons également espacés
 * - "bd*4" -> bd joué 4 fois par cycle
 * - "bd sd ~ hh" -> ~ = silence
 * - "[bd sd] hh" -> groupe (bd et sd partagent 1 temps)
 */

#ifndef PATTERN_PARSER_H
#define PATTERN_PARSER_H

#include <Arduino.h>

// Nombre maximum d'événements par pattern
#define MAX_EVENTS 32
#define MAX_TOKEN_LENGTH 16

enum TokenType {
  TOKEN_SAMPLE,      // ex: "bd", "sd", "hh"
  TOKEN_SILENCE,     // ~
  TOKEN_MULTIPLY,    // * (ex: bd*4)
  TOKEN_GROUP_START, // [
  TOKEN_GROUP_END,   // ]
  TOKEN_END
};

struct Token {
  TokenType type;
  char value[MAX_TOKEN_LENGTH];
  int multiplier;
};

struct PatternEvent {
  char sample[MAX_TOKEN_LENGTH];
  float start;     // Position dans le cycle (0.0 - 1.0)
  float duration;  // Durée relative
  float velocity;  // Volume (0.0 - 1.0)
  bool active;
};

class PatternParser {
private:
  Token tokens[MAX_EVENTS];
  int tokenCount;
  
  // Tokenize la chaîne d'entrée
  void tokenize(const char* pattern);
  
  // Convertit les tokens en événements temporels
  void tokensToEvents(PatternEvent* events, int* eventCount);
  
public:
  PatternParser();
  
  void begin();
  
  // Parse un pattern et retourne les événements
  // pattern: "bd sd hh cp"
  // events: tableau de sortie
  // eventCount: nombre d'événements générés
  bool parse(const char* pattern, PatternEvent* events, int* eventCount);
  
  // Helpers
  bool isSampleName(const char* str);
  int getSampleId(const char* name);
};

#endif
