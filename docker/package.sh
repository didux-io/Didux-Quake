# Make sure all builds are run
./docker/build.sh

# Remove previous packages
rm ./output/*.tar.gz

# Package Debian x86_64
tar -cvzf ./output/debian_x86_64.tar.gz -C ./output/debian/x86_64 . -C ../../.. ./baseq2 -C ./ ./manifest.json

# Package Ubuntu x86_64
tar -cvzf ./output/ubuntu_x86_64.tar.gz -C ./output/ubuntu/x86_64 . -C ../../.. ./baseq2 -C ./ ./manifest.json

# Package Fedora x86_64
tar -cvzf ./output/fedora_x86_64.tar.gz -C ./output/fedora/x86_64 . -C ../../.. ./baseq2 -C ./ ./manifest.json

# Package Windows x86_64
tar -cvzf ./output/windows_x86_64.tar.gz -C ./output/windows/x86_64 . -C ../../.. ./baseq2 -C ./ ./manifest.json

# Package Darwin x86_64
tar -cvzf ./output/darwin_x86_64.tar.gz -C ./output/darwin/x86_64 . -C ../../.. ./baseq2 -C ./ ./manifest.json
