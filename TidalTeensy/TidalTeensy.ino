/*
 * TidalTeensy - Live Coding System for Teensy 4.0
 * 
 * Un système de live coding inspiré de Tidal Cycles
 * pour Teensy 4.0 avec AudioStream.h
 * 
 * Architecture:
 * 1. PatternParser - Parse les patterns textuels (ex: "bd sd hh cp")
 * 2. Scheduler - Gère le timing et les cycles
 * 3. AudioEngine - Interface avec AudioStream.h
 * 4. SerialInterface - Reçoit les commandes en temps réel
 */

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "PatternParser.h"
#include "Scheduler.h"
#include "AudioEngine.h"
#include "SerialInterface.h"

// Objets Audio
AudioEngine audioEngine;
AudioOutputI2S i2s1;           // Sortie vers DAC Teensy
AudioOutputUSB usb1;           // Sortie vers USB (ordinateur)
AudioConnection patchCord1(audioEngine, 0, i2s1, 0);  // Left → I2S
AudioConnection patchCord2(audioEngine, 0, i2s1, 1);  // Right → I2S
AudioConnection patchCord3(audioEngine, 0, usb1, 0);  // Left → USB
AudioConnection patchCord4(audioEngine, 0, usb1, 1);  // Right → USB
AudioControlSGTL5000 audioShield;

// Composants du système
PatternParser parser;
Scheduler scheduler;
SerialInterface serialInterface;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("=== TidalTeensy v1.1 - USB Audio Edition ===");
  Serial.println("Live Coding System pour Teensy 4.0");
  Serial.println();
  
  // Configuration Audio
  AudioMemory(25);  // Augmenté pour supporter USB + I2S
  audioShield.enable();
  audioShield.volume(0.5);
  
  Serial.println("[Audio] Configuration:");
  Serial.println("  - Sortie I2S (DAC Teensy)");
  Serial.println("  - Sortie USB (vers ordinateur)");
  Serial.println("  Configurez 'Teensy Audio' comme peripherique de sortie sur votre PC");
  Serial.println();
  
  // Initialisation du scheduler
  scheduler.begin(120.0f); // 120 BPM par défaut
  
  // Configuration du parser
  parser.begin();
  
  // Connexion des composants à l'interface série
  serialInterface.setParser(&parser);
  serialInterface.setScheduler(&scheduler);
  
  // Affichage des commandes disponibles
  serialInterface.printHelp();
}

void loop() {
  // Traiter les commandes série entrantes
  serialInterface.update();
  
  // Mettre à jour le scheduler
  scheduler.update();
  
  // Récupérer les événements à jouer
  while (scheduler.hasEvents()) {
    Event evt = scheduler.getNextEvent();
    audioEngine.triggerSound(evt.sample, evt.velocity);
  }
  
  // Small delay pour ne pas surcharger le CPU
  delayMicroseconds(100);
}
