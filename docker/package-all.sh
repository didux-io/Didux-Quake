# Make sure all builds are run
# ./docker/build-all.sh

# Package Debian x86_64
tar -cvzf ./output/debian_x86_64.tar.gz -C ./output/debian/x86_64 . -C ../../../assets .

# Package Ubuntu x86_64
tar -cvzf ./output/ubuntu_x86_64.tar.gz -C ./output/ubuntu/x86_64 . -C ../../../assets .

# Package Fedora x86_64
tar -cvzf ./output/fedora_x86_64.tar.gz -C ./output/fedora/x86_64 . -C ../../../assets .

# Package Windows x86_64
tar -cvzf ./output/windows_x86_64.tar.gz -C ./output/windows/x86_64 . -C ../../../assets .

# Package Darwin x86_64
tar -cvzf ./output/darwin_x86_64.tar.gz -C ./output/darwin/x86_64 . -C ../../../assets .
