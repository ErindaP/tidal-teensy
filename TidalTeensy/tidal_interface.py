"""
Interface Python pour TidalTeensy
Envoie des commandes au Teensy via port série
"""

import serial
import time
import sys

class TidalTeensyInterface:
    def __init__(self, port='COM3', baudrate=115200):
        """
        Initialise la connexion avec le Teensy
        
        Args:
            port: Port série (COM3, COM4... sur Windows, /dev/ttyACM0 sur Linux)
            baudrate: Vitesse de communication (115200 par défaut)
        """
        try:
            self.ser = serial.Serial(port, baudrate, timeout=1)
            time.sleep(2)  # Attendre que le Teensy soit prêt
            print(f"✓ Connecté à {port}")
            
            # Lire les messages de démarrage
            time.sleep(0.5)
            while self.ser.in_waiting:
                print(self.ser.readline().decode('utf-8', errors='ignore').strip())
                
        except serial.SerialException as e:
            print(f"✗ Erreur de connexion: {e}")
            print("\nPorts série disponibles:")
            self.list_ports()
            sys.exit(1)
    
    def send(self, command):
        """Envoie une commande au Teensy"""
        if not command.endswith('\n'):
            command += '\n'
        
        self.ser.write(command.encode('utf-8'))
        time.sleep(0.05)  # Petit délai
        
        # Lire la réponse
        response = ""
        while self.ser.in_waiting:
            line = self.ser.readline().decode('utf-8', errors='ignore').strip()
            if line:
                response += line + "\n"
        
        if response:
            print(response.strip())
    
    def pattern(self, channel, pattern):
        """
        Envoie un pattern sur un canal
        
        Args:
            channel: Numéro du canal (1-8)
            pattern: Pattern textuel (ex: "bd sd hh cp")
        """
        cmd = f"d{channel} {pattern}"
        self.send(cmd)
    
    def bpm(self, tempo):
        """Change le BPM"""
        self.send(f"bpm {tempo}")
    
    def clear(self):
        """Efface tous les patterns"""
        self.send("clear")
    
    def silence(self, channel):
        """Coupe un canal spécifique"""
        self.send(f"d{channel} silence")
    
    def help(self):
        """Affiche l'aide"""
        self.send("help")
    
    def close(self):
        """Ferme la connexion"""
        self.ser.close()
        print("✓ Connexion fermée")
    
    @staticmethod
    def list_ports():
        """Liste les ports série disponibles"""
        from serial.tools import list_ports
        ports = list_ports.comports()
        for port in ports:
            print(f"  - {port.device}: {port.description}")


def interactive_mode():
    """Mode interactif: REPL pour TidalTeensy"""
    print("=== TidalTeensy Interface Python ===")
    print("Entrez le port série (ex: COM3 ou /dev/ttyACM0)")
    
    # Liste les ports disponibles
    print("\nPorts disponibles:")
    TidalTeensyInterface.list_ports()
    
    port = input("\nPort: ").strip()
    if not port:
        port = "COM3"  # Défaut
    
    try:
        teensy = TidalTeensyInterface(port)
        
        print("\n✓ Mode interactif activé")
        print("Tapez vos commandes (ou 'quit' pour quitter):")
        print("Exemples:")
        print("  d1 bd sd hh cp")
        print("  bpm 140")
        print("  clear")
        print()
        
        while True:
            try:
                cmd = input("tidal> ").strip()
                
                if not cmd:
                    continue
                
                if cmd.lower() in ['quit', 'exit', 'q']:
                    break
                
                teensy.send(cmd)
                
            except KeyboardInterrupt:
                print("\n")
                break
        
        teensy.close()
        
    except Exception as e:
        print(f"✗ Erreur: {e}")


def demo():
    """Démonstration des fonctionnalités"""
    print("=== Démonstration TidalTeensy ===")
    
    teensy = TidalTeensyInterface('COM3')
    
    print("\n1. Pattern simple sur d1")
    teensy.pattern(1, "bd sd hh cp")
    time.sleep(4)
    
    print("\n2. Ajout d'un pattern sur d2")
    teensy.pattern(2, "bd*4")
    time.sleep(4)
    
    print("\n3. Changement de BPM")
    teensy.bpm(160)
    time.sleep(4)
    
    print("\n4. Pattern avec silences")
    teensy.pattern(3, "bd ~ sd ~")
    time.sleep(4)
    
    print("\n5. Clear tout")
    teensy.clear()
    time.sleep(2)
    
    print("\n6. Pattern complexe")
    teensy.pattern(1, "bd sd cp hh")
    teensy.pattern(2, "bd*2")
    teensy.pattern(3, "hh*8")
    time.sleep(8)
    
    teensy.clear()
    teensy.close()
    
    print("\n✓ Démonstration terminée")


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "demo":
        demo()
    else:
        interactive_mode()
