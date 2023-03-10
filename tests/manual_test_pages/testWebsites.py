import os
import sys
import http.server
import socketserver

PORT = 8000
Handler = http.server.SimpleHTTPRequestHandler

source_dir = "arduino/"
dest_dir = "tests/manual_test_pages/"

if not os.path.exists(source_dir):
    sys.exit("Source directory not available")

if not os.path.exists(dest_dir):
    sys.exit("Target directory not available")


for filename in os.listdir(source_dir):
    if filename.endswith(".h"):
        with open(os.path.join(source_dir, filename)) as f:
            lines = f.readlines()
            if len(lines) > 0:
                lines.pop(0)   # remove first line
                lines.pop()    # remove last line
                new_filename = os.path.splitext(filename)[0] + ".html"
                new_file_path = os.path.join(dest_dir, new_filename)
                with open(new_file_path, "w") as f_out:
                    f_out.writelines(lines)
                print(f"Copied and modified {filename} to {new_file_path}")

print("Done copiying, starting to serve the files.")

os.chdir(dest_dir)

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Serving directory {dest_dir} at http://localhost:{PORT}/")
    httpd.serve_forever()



