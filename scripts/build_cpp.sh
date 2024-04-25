for i in $(ls src/*.cpp); do
  g++ -c $i -o build/$(basename $i.o) -ffreestanding -O2 -Wall -Wextra \
      -fno-stack-protector -fno-exceptions -fno-rtti -Wl,build-id=none;
done;
