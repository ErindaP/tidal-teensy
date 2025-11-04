# Serveur HTTP local pour tester l'interface TidalTeensy
# Usage: python serve_interface.py
# Puis ouvrir: http://localhost:8000/web_interface.html

import http.server
import socketserver
import os

PORT = 8000
DIRECTORY = os.path.dirname(os.path.abspath(__file__))

class MyHTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=DIRECTORY, **kwargs)

print(f"🎹 TidalTeensy Interface Server")
print(f"📂 Serving directory: {DIRECTORY}")
print(f"🌐 Open in browser: http://localhost:{PORT}/web_interface.html")
print(f"⚠️  Use Chrome, Edge or Opera (Web Serial API required)")
print(f"🛑 Press Ctrl+C to stop\n")

with socketserver.TCPServer(("", PORT), MyHTTPRequestHandler) as httpd:
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\n✓ Server stopped")
