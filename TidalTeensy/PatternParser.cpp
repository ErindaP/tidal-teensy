/*
 * PatternParser.cpp
 * 
 * Implémentation du parser de patterns
 */

#include "PatternParser.h"

PatternParser::PatternParser() {
  tokenCount = 0;
}

void PatternParser::begin() {
  tokenCount = 0;
  Serial.println("[Parser] Initialisé");
}

bool PatternParser::parse(const char* pattern, PatternEvent* events, int* eventCount) {
  if (!pattern || strlen(pattern) == 0) {
    *eventCount = 0;
    return false;
  }
  
  Serial.print("[Parser] Parsing: ");
  Serial.println(pattern);
  
  // Étape 1: Tokenization
  tokenize(pattern);
  
  // Étape 2: Conversion en événements
  tokensToEvents(events, eventCount);
  
  Serial.print("[Parser] Généré ");
  Serial.print(*eventCount);
  Serial.println(" événements");
  
  return (*eventCount > 0);
}

void PatternParser::tokenize(const char* pattern) {
  tokenCount = 0;
  int len = strlen(pattern);
  int i = 0;
  
  while (i < len && tokenCount < MAX_EVENTS) {
    // Skip whitespace
    while (i < len && (pattern[i] == ' ' || pattern[i] == '\t')) {
      i++;
    }
    
    if (i >= len) break;
    
    Token& token = tokens[tokenCount];
    token.multiplier = 1;
    
    // Silence
    if (pattern[i] == '~') {
      token.type = TOKEN_SILENCE;
      strcpy(token.value, "~");
      i++;
      tokenCount++;
      continue;
    }
    
    // Group start
    if (pattern[i] == '[') {
      token.type = TOKEN_GROUP_START;
      strcpy(token.value, "[");
      i++;
      tokenCount++;
      continue;
    }
    
    // Group end
    if (pattern[i] == ']') {
      token.type = TOKEN_GROUP_END;
      strcpy(token.value, "]");
      i++;
      tokenCount++;
      continue;
    }
    
    // Sample name
    int j = 0;
    while (i < len && pattern[i] != ' ' && pattern[i] != '*' && 
           pattern[i] != '[' && pattern[i] != ']' && pattern[i] != '~' &&
           j < MAX_TOKEN_LENGTH - 1) {
      token.value[j++] = pattern[i++];
    }
    token.value[j] = '\0';
    
    // Check for multiplier
    if (i < len && pattern[i] == '*') {
      i++; // skip '*'
      int mult = 0;
      while (i < len && pattern[i] >= '0' && pattern[i] <= '9') {
        mult = mult * 10 + (pattern[i] - '0');
        i++;
      }
      token.multiplier = (mult > 0) ? mult : 1;
    }
    
    token.type = TOKEN_SAMPLE;
    tokenCount++;
  }
}

void PatternParser::tokensToEvents(PatternEvent* events, int* eventCount) {
  *eventCount = 0;
  
  if (tokenCount == 0) return;
  
  // Version simple: divise le cycle également entre tous les samples
  // (ignore les groupes pour l'instant)
  int sampleCount = 0;
  
  // Compter les samples effectifs (avec multiplicateurs)
  for (int i = 0; i < tokenCount; i++) {
    if (tokens[i].type == TOKEN_SAMPLE) {
      sampleCount += tokens[i].multiplier;
      Serial.print("[Parser] Token: ");
      Serial.print(tokens[i].value);
      Serial.print(" x");
      Serial.println(tokens[i].multiplier);
    } else if (tokens[i].type == TOKEN_SILENCE) {
      sampleCount += 1;
      Serial.println("[Parser] Token: ~");
    }
  }
  
  if (sampleCount == 0) return;
  
  Serial.print("[Parser] Total samples: ");
  Serial.println(sampleCount);
  
  float step = 1.0f / sampleCount;
  float currentPos = 0.0f;
  
  for (int i = 0; i < tokenCount; i++) {
    if (tokens[i].type == TOKEN_SAMPLE) {
      for (int m = 0; m < tokens[i].multiplier; m++) {
        if (*eventCount >= MAX_EVENTS) break;
        
        PatternEvent& evt = events[*eventCount];
        strncpy(evt.sample, tokens[i].value, MAX_TOKEN_LENGTH - 1);
        evt.sample[MAX_TOKEN_LENGTH - 1] = '\0';
        evt.start = currentPos;
        evt.duration = step;
        evt.velocity = 0.8f;
        evt.active = true;
        
        Serial.print("[Parser] Event #");
        Serial.print(*eventCount);
        Serial.print(": ");
        Serial.print(evt.sample);
        Serial.print(" @ ");
        Serial.println(evt.start, 3);
        
        (*eventCount)++;
        currentPos += step;
      }
    } else if (tokens[i].type == TOKEN_SILENCE) {
      currentPos += step;
    }
  }
}

bool PatternParser::isSampleName(const char* str) {
  // Liste de samples reconnus
  const char* knownSamples[] = {
    "bd", "sd", "hh", "cp", "sn", "tom", "kick", "snare", "hat", "clap",
    "perc", "rim", "ride", "crash", "cymbal"
  };
  
  for (int i = 0; i < 15; i++) {
    if (strcmp(str, knownSamples[i]) == 0) {
      return true;
    }
  }
  return false;
}

int PatternParser::getSampleId(const char* name) {
  // Convertit un nom de sample en ID (pour la banque de sons)
  if (strcmp(name, "bd") == 0 || strcmp(name, "kick") == 0) return 0;
  if (strcmp(name, "sd") == 0 || strcmp(name, "snare") == 0 || strcmp(name, "sn") == 0) return 1;
  if (strcmp(name, "hh") == 0 || strcmp(name, "hat") == 0) return 2;
  if (strcmp(name, "cp") == 0 || strcmp(name, "clap") == 0) return 3;
  
  return 0; // Default
}
